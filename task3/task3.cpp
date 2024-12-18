#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "myerrors.h"
#define uint unsigned int
#define MAX_SIZE 18

class LogicalValuesArray {
private:
    unsigned int value;
    int size;
public:

    int GetSize() const{
        return size;
    }

    unsigned int GetValue() const{
        return value;
    }

    void SetValue(LogicalValuesArray a) {
        value = a.GetValue();
        int i = 0;
        //while ((1 << i) <= value) { i++; }
        size = a.GetSize();
    }

    LogicalValuesArray(unsigned int val = 0, int _size=-1) {
        value = val;
        if (_size != -1) {
            size = _size;
            return;
        }
        if (value > UINT_MAX / 2) {
            size = sizeof(unsigned int) * 8;
        }
        else {
            unsigned int i = 0;
            while ((1 << i) < value) { i++; }
            size = i - 1;
        }
    }

    LogicalValuesArray MNot(const LogicalValuesArray& l) const {
        return LogicalValuesArray(~l.GetValue(), l.size);
    }

    LogicalValuesArray MAnd(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            throw std::invalid_argument("Different size");
        }
        return LogicalValuesArray(a.GetValue() & b.GetValue(), a.size) ;
    }

    LogicalValuesArray MOr(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            throw std::invalid_argument("Different size");
        }
        return MNot(MAnd(MNot(a), MNot(b)));
    }

    LogicalValuesArray MXor(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            throw std::invalid_argument("Different size");
        }
        return MOr(MAnd(MNot(a), b), MAnd(a, MNot(b)));
    }

    LogicalValuesArray MIm(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            printf("Operations on array different length are undefined\n");
            throw std::invalid_argument("Different size");
        }
        return MNot(MAnd(a, MNot(b)));
    }

    LogicalValuesArray MKoim(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            printf("Operations on array different length are undefined\n");
            throw std::invalid_argument("Different size");
        }
        return MNot(MIm(a, b));
    }

    LogicalValuesArray MEq(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            printf("Operations on array different length are undefined\n");
            throw std::invalid_argument("Different size");
        }
        return MOr(MAnd(a, b), MAnd(MNot(a), MNot(b)));
    }

    LogicalValuesArray MPirs(const LogicalValuesArray& a, const LogicalValuesArray b) const{
        if (a.GetSize() != b.GetSize()) {
            printf("Operations on array different length are undefined\n");
            throw std::invalid_argument("Different size");
        }
        return MNot(MOr(a, b));
    }
    LogicalValuesArray MSheffer(const LogicalValuesArray& a, const LogicalValuesArray& b) const{
        if (a.GetSize() != b.GetSize()) {
            printf("Operations on array different length are undefined\n");
            throw std::invalid_argument("Different size");
        }
        return MNot(MAnd(a, b));
    }

    static bool Equ als(const LogicalValuesArray& a, const LogicalValuesArray& b) {
        if (a.GetSize() != b.GetSize()) {
            printf("Operations on array different length are undefined\n");
            throw std::invalid_argument("Different size");
        }
        return a.MXor(a, b).GetValue() == 0;
    }

    int GetBit(int pos) {
        return (value & (1 << (pos - 1))) > 0 ? 1 : 0;
    }

    void SetValueByString(const char* s) {
        uint res = UINT_MAX;
        uint cur = 1;
        size = strlen(s);
        for (int i = 0; i < strlen(s); i++) {
            if (s[i] == '1') {
                res = res | (1 << i);
            }
            else if (s[i] == '0') {
                if (res & (1 << i)){
                    res = res ^ (1 << i);
                }
            }
            else {
                throw std::invalid_argument("Inorrect input strung\n");
            }
        }
        value = res;
    }

    std::ostream& PrintValue(std::ostream& os) {
        uint i;
        for (i = 0; i < size; i++) {
            os << GetBit(i+1);
        }
        if (i == 0) {
            os << 0;
        }
        return os;
    }

    
};

std::ostream& operator << (std::ostream& os, LogicalValuesArray& a)
{
    return a.PrintValue(os);
}

int main()
{
    char example[10];
    strcpy(example, "101\0");
    LogicalValuesArray c = LogicalValuesArray();
    

    LogicalValuesArray a = LogicalValuesArray(1010);
    LogicalValuesArray b = LogicalValuesArray(1018);
    LogicalValuesArray res = LogicalValuesArray();

    c.SetValueByString(example);
    a.SetValueByString("110110");
    b.SetValueByString("100010");    
   
    try {
        res.SetValue(a.MAnd(a, b));
        std::cout << "And: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MOr(a, b));
        std::cout << "Or: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MEq(a, b));
        std::cout << "Equal: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MIm(a, b));
        std::cout << "Implication: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MKoim(a, b));
        std::cout << "Koimplication: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MXor(a, b));
        std::cout << "Xor: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MPirs(a, b));
        std::cout << "Pirs: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MSheffer(a, b));
        std::cout << "Sheffer: " << a << ' ' << b << ' ' << res << '\n';

        res.SetValue(a.MNot(a));
        std::cout << "Not: " << a << ' ' << res << '\n';

        std::cout << LogicalValuesArray::Equals(a, b) << '\n';
    }
    catch(std::invalid_argument exc){
        std::cout << exc.what();
    }
}

