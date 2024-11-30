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

    int GetSize() {
        return size;
    }

    unsigned int GetValue() {
        return value;
    }

    void SetValue(uint val, int _size) {
        value = val;
        int i = 0;
        //while ((1 << i) <= value) { i++; }
        size = _size;
    }

    LogicalValuesArray(unsigned int val = 0, int _size=0) {
        value = val;
        unsigned int i = 0;
        //while ((1 << i) < value) { i++; }
        size = _size;
    }

    unsigned int MNot(LogicalValuesArray l) {
        return ~l.GetValue();
    }

    unsigned int MAnd(LogicalValuesArray a, LogicalValuesArray b) {
        return a.GetValue() & b.GetValue();
    }

    unsigned int MOr(LogicalValuesArray a, LogicalValuesArray b) {
        return MNot(MAnd(MNot(a), MNot(b)));
    }

    unsigned int MXor(LogicalValuesArray a, LogicalValuesArray b) {
        return MOr(MAnd(MNot(a), b), MAnd(a, MNot(b)));
    }

    unsigned int MIm(LogicalValuesArray a, LogicalValuesArray b) {
        return MNot(MAnd(a, MNot(b)));
    }

    unsigned int MKoim(LogicalValuesArray a, LogicalValuesArray b) {
        return MNot(MIm(a, b));
    }

    unsigned int MEq(LogicalValuesArray a, LogicalValuesArray b) {
        return MOr(MAnd(a, b), MAnd(MNot(a), MNot(b)));
    }

    unsigned int MPirs(LogicalValuesArray a, LogicalValuesArray b) {
        return MNot(MOr(a, b));
    }
    unsigned int MSheffer(LogicalValuesArray a, LogicalValuesArray b) {
        return MNot(MAnd(a, b));
    }

    static bool Equals(LogicalValuesArray a, LogicalValuesArray b) {
        return a.MXor(a, b) == 0;
    }

    int GetBit(int pos) {
        return (value & (1 << (pos - 1))) > 0 ? 1 : 0;
    }

    kErrors SetValueByString(const char* s) {
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
                return INC_ARGS;
            }
        }
        value = res;
        return SUCCESS;
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
    c.SetValueByString(example);

    LogicalValuesArray a = LogicalValuesArray();
    LogicalValuesArray b = LogicalValuesArray();
    LogicalValuesArray res = LogicalValuesArray();

    a.SetValueByString("110110");
    b.SetValueByString("100010");    
   
    res.SetValue(a.MAnd(a, b), a.GetSize());
    std::cout << "And: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MOr(a, b), a.GetSize());
    std::cout << "Or: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MEq(a, b), a.GetSize());
    std::cout << "Equal: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MIm(a, b), a.GetSize());
    std::cout << "Implication: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MKoim(a, b), a.GetSize());
    std::cout << "Koimplication: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MXor(a, b), a.GetSize());
    std::cout << "Xor: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MPirs(a, b), a.GetSize());
    std::cout << "Pirs: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MSheffer(a, b), a.GetSize());
    std::cout << "Sheffer: " << a << ' ' << b << ' ' << res << '\n';

    res.SetValue(a.MNot(a), a.GetSize());
    std::cout << "Not: " << a << ' ' << res << '\n';

    std::cout << LogicalValuesArray::Equals(a, b) << '\n';
}

