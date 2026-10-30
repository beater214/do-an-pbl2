#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CLASS: Nguoi (abstract)
// ================================================================
class Nguoi {
protected:
    string hoTen;
    Date ngaySinh;
    string soDienThoai;

public:
    static void kiemTraSoDienThoai(const string& sdt) {
        if (sdt.empty())
            throw LoiDoiSo("So dien thoai khong duoc de trong!");
        if (sdt.length() != 10)
            throw LoiDoiSo("So dien thoai phai co dung 10 chu so (hien tai co " + to_string(sdt.length()) + " ky tu)!");
        if (sdt[0] != '0')
            throw LoiDoiSo("So dien thoai phai bat dau bang chu so 0!");
        for (char c : sdt) {
            if (!laChuSo(c))
                throw LoiDoiSo("So dien thoai chi duoc chua ky tu so (0-9)!");
        }
    }

    static void kiemTraHoTen(const string& ten) {
        if (ten.empty())
            throw LoiDoiSo("Ho va ten khong duoc de trong!");
    }

    Nguoi() : hoTen(""), ngaySinh(Date()), soDienThoai("") {}
    Nguoi(const string& hoTen, const Date& ngaySinh, const string& soDienThoai)
        : hoTen(hoTen), ngaySinh(ngaySinh), soDienThoai(soDienThoai) {
        if (!hoTen.empty()) kiemTraHoTen(hoTen);
        if (!soDienThoai.empty()) kiemTraSoDienThoai(soDienThoai);
    }
    virtual ~Nguoi() {}

    string getHoTen() const { return hoTen; }
    Date getNgaySinh() const { return ngaySinh; }
    string getSoDienThoai() const { return soDienThoai; }

    void setHoTen(const string& hoTen) {
        kiemTraHoTen(hoTen);
        this->hoTen = hoTen;
    }
    void setNgaySinh(const Date& ngaySinh) { this->ngaySinh = ngaySinh; }
    void setSoDienThoai(const string& soDienThoai) {
        kiemTraSoDienThoai(soDienThoai);
        this->soDienThoai = soDienThoai;
    }

    virtual void xuatThongTin(ostream& os = cout) const = 0;

    friend ostream& operator<<(ostream& os, const Nguoi& n) {
        n.xuatThongTin(os);
        return os;
    }
};

// ================================================================
//  CLASS: NguoiThuePhong
// ================================================================
class NguoiThuePhong : public Nguoi {
private:
    int maNguoiThue;
public:
    NguoiThuePhong() : Nguoi(), maNguoiThue(0) {}
    NguoiThuePhong(int maNguoiThue, const string& hoTen, const Date& ngaySinh, const string& soDienThoai)
        : Nguoi(hoTen, ngaySinh, soDienThoai), maNguoiThue(maNguoiThue) {
        if (maNguoiThue <= 0)
            throw LoiDoiSo("Ma nguoi thue phai la so nguyen duong (> 0)!");
        kiemTraHoTen(hoTen);
        kiemTraSoDienThoai(soDienThoai);
    }

    int getMaNguoiThue() const { return maNguoiThue; }
    void setMaNguoiThue(int maNguoiThue) {
        if (maNguoiThue <= 0)
            throw LoiDoiSo("Ma nguoi thue phai la so nguyen duong (> 0)!");
        this->maNguoiThue = maNguoiThue;
    }

    void xuatThongTin(ostream& os = cout) const override {
        os << "Ma NT: " << maNguoiThue
           << " | Ho ten: " << hoTen
           << " | Ngay sinh: " << ngaySinh
           << " | SDT: " << soDienThoai;
    }

    string toFileString() const {
        // MA_NT|HO_TEN|NGAY_SINH|SO_DIEN_THOAI
        return to_string(maNguoiThue) + "|" + hoTen + "|" + ngaySinh.toString() + "|" + soDienThoai;
    }
};

using NguoiThue = NguoiThuePhong;
