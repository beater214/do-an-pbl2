#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// ================================================================
//  1. GIOI HAN SO NGUYEN (Tu dinh nghia - Thay the <climits>)
// ================================================================
const int GIA_TRI_MIN = -2147483648;
const int GIA_TRI_MAX =  2147483647;

// ================================================================
//  2. HAM KIEM TRA KY TU (Tu dinh nghia bang ma ASCII - Thay the <cctype>)
// ================================================================
inline bool laChuSo(char c) {
    return (c >= '0' && c <= '9');
}

inline bool laChuCai(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline bool laKhoangTrang(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

// ================================================================
//  3. HE THONG NGOAI LE THUAN OOP (Tu dinh nghia - Thay the <stdexcept>)
// ================================================================
class NgoaiLe {
protected:
    string thongBao;
public:
    NgoaiLe(const string& msg = "") : thongBao(msg) {}
    virtual ~NgoaiLe() {}
    virtual string what() const { return thongBao; }
};

// Loi doi so truyen vao khong hop le (Thay the invalid_argument)
class LoiDoiSo : public NgoaiLe {
public:
    LoiDoiSo(const string& msg) : NgoaiLe(msg) {}
};

// Loi vuot qua mien gia tri cho phep (Thay the out_of_range)
class LoiVuotKhoang : public NgoaiLe {
public:
    LoiVuotKhoang(const string& msg) : NgoaiLe(msg) {}
};

// Loi thuc thi nghiep vu / rang buoc logic (Thay the runtime_error)
class LoiThucThi : public NgoaiLe {
public:
    LoiThucThi(const string& msg) : NgoaiLe(msg) {}
};
