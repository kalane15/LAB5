#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
#include <filesystem>
#include "myerrors.h"
#define uint unsigned int

using std::filesystem::absolute;
using std::filesystem::path;
class Encoder {
private:

    std::vector<std::byte> key;

    void InitS(std::vector<std::byte>& s) {
        for (uint i = 0; i < 256; ++i) {
            s[i] = static_cast<std::byte>(i);
        }

        uint j = 0;
        for (uint i = 0; i < 256; ++i) {
            j = (j + static_cast<uint>(s[i]) + static_cast<uint>(key[i % key.size()])) % 256;
            std::swap(s[i], s[j]);
        }
    }

    std::vector<std::byte> rc4Process(const std::vector<std::byte>& data) {
        std::vector<std::byte> s(256);
        InitS(s);

        uint i = 0, j = 0;

        std::vector<std::byte> kv(data.size());

        for (uint k = 0; k < data.size(); ++k) {
            i = (i + 1) % 256;
            j = (j + static_cast<uint>(s[i])) % 256;
            std::swap(s[i], s[j]);

            uint t = static_cast<uint>(s[(static_cast<uint>(s[i]) + static_cast<uint>(s[j])) % 256]);
            kv[k] = static_cast<std::byte>(t);
        }
        for (uint i = 0; i < data.size(); i++) {
            kv[i] = data[i] ^ kv[i];
        }
        
        return kv;
    }

public:

    Encoder(const std::vector<std::byte> key_){
        key = key_;
    }


    void KeyMutator(std::vector<std::byte>& key_) {
        key = key_;
    }
    
    void Encode(path input_path, path output_path) {
        path input_full_path = absolute(input_path);
        path output_full_path = absolute(output_path);

        if (input_full_path == output_full_path) {
            throw std::invalid_argument("Incorrect file");
        }

        std::ifstream input;
        input.open(input_path, std::ios::binary);
        if (!input.is_open()) {
            throw std::invalid_argument("Incorrect file");
        }

        std::ofstream output;
        output.open(output_path, std::ios::binary);
        if (!output.is_open()) {
            throw std::invalid_argument("Incorrect file");
        }

        std::vector<std::byte> data;
        char ch;
        while (input >> ch) {
            data.push_back(static_cast<std::byte>(ch));
        }


        std::vector<std::byte> result = rc4Process(data);
        for (int i = 0; i < result.size(); i++) {
            output << static_cast<char>(result[i]);
        }
    }
};


int main() {
    std::vector<std::byte> key = { std::byte(1), std::byte(2), std::byte(3), std::byte(4) };

    Encoder enc(key);
    kErrors status;
    try {
        enc.Encode("in.txt", "in.bin");
    }
    catch(std::invalid_argument& exc){
        std::cout << exc.what() << '\n';
    }

    try {
        enc.Encode("in.bin", "in2.txt");
    }
    catch (std::invalid_argument& exc) {
        std::cout << exc.what() << '\n';
    }
    return 0;
}