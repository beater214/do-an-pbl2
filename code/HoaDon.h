#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CLASS: HoaDon
// ================================================================
class HoaDon {
private:
    string maHoaDon;
    int maPhong, maNguoiThue;
    Date ngayLap;
    int thangThanhToan;
    int namThanhToan;
    double tienPhong;
    double tienDien;
    double tienNuoc;
    double tongTien;

public:
    HoaDon()
        : maHoaDon(""), maPhong(0), maNguoiThue(0), ngayLap(Date()),
          thangThanhToan(1), namThanhToan(2000),
          tienPhong(0.0), tienDien(0.0), tienNuoc(0.0), tongTien(0.0) {}

    // Constructor day du chi tiet kem ky thanh toan
    HoaDon(const string& maHoaDon, int maPhong, int maNguoiThue, const Date& ngayLap,
           int thangThanhToan, int namThanhToan,
           double tienPhong, double tienDien, double tienNuoc = 0.0)
        : maHoaDon(maHoaDon), maPhong(maPhong), maNguoiThue(maNguoiThue), ngayLap(ngayLap),
          thangThanhToan(thangThanhToan), namThanhToan(namThanhToan),
          tienPhong(tienPhong), tienDien(tienDien), tienNuoc(tienNuoc) {
        if (maHoaDon.empty()) throw LoiDoiSo("Ma hoa don khong duoc de trong!");
        if (thangThanhToan < 1 || thangThanhToan > 12) throw LoiDoiSo("Thang thanh toan phai tu 1 den 12!");
        if (namThanhToan < 1900 || namThanhToan > 2100) throw LoiDoiSo("Nam thanh toan phai tu 1900 den 2100!");
        if (tienPhong < 0) throw LoiDoiSo("Tien phong khong duoc am!");
        if (tienDien < 0) throw LoiDoiSo("Tien dien khong duoc am!");
        if (tienNuoc < 0) throw LoiDoiSo("Tien nuoc khong duoc am!");
        this->tongTien = tienPhong + tienDien + tienNuoc;
        if (this->tongTien <= 0) throw LoiDoiSo("Tong tien hoa don phai lon hon 0 VND!");
    }

    // Constructor tienPhong, tienDien, tienNuoc (mac dinh ky thanh toan lay theo ngayLap)
    HoaDon(const string& maHoaDon, int maPhong, int maNguoiThue, const Date& ngayLap,
           double tienPhong, double tienDien, double tienNuoc = 0.0)
        : maHoaDon(maHoaDon), maPhong(maPhong), maNguoiThue(maNguoiThue), ngayLap(ngayLap),
          thangThanhToan(ngayLap.getThang()), namThanhToan(ngayLap.getNam()),
          tienPhong(tienPhong), tienDien(tienDien), tienNuoc(tienNuoc) {
        if (maHoaDon.empty()) throw LoiDoiSo("Ma hoa don khong duoc de trong!");
        if (tienPhong < 0) throw LoiDoiSo("Tien phong khong duoc am!");
        if (tienDien < 0) throw LoiDoiSo("Tien dien khong duoc am!");
        if (tienNuoc < 0) throw LoiDoiSo("Tien nuoc khong duoc am!");
        this->tongTien = tienPhong + tienDien + tienNuoc;
        if (this->tongTien <= 0) throw LoiDoiSo("Tong tien hoa don phai lon hon 0 VND!");
    }

    // Constructor tuong thich nguoc (tong tien)
    HoaDon(const string& maHoaDon, int maPhong, int maNguoiThue, const Date& ngayLap, double tongTien)
        : maHoaDon(maHoaDon), maPhong(maPhong), maNguoiThue(maNguoiThue), ngayLap(ngayLap),
          thangThanhToan(ngayLap.getThang()), namThanhToan(ngayLap.getNam()),
          tienPhong(tongTien), tienDien(0.0), tienNuoc(0.0), tongTien(tongTien) {
        if (maHoaDon.empty()) throw LoiDoiSo("Ma hoa don khong duoc de trong!");
        if (tongTien <= 0) throw LoiDoiSo("Tong tien hoa don phai lon hon 0 VND!");
    }

    HoaDon(const string& maHoaDon, const Date& ngayLap, double tongTien)
        : maHoaDon(maHoaDon), maPhong(0), maNguoiThue(0), ngayLap(ngayLap),
          thangThanhToan(ngayLap.getThang()), namThanhToan(ngayLap.getNam()),
          tienPhong(tongTien), tienDien(0.0), tienNuoc(0.0), tongTien(tongTien) {
        if (maHoaDon.empty()) throw LoiDoiSo("Ma hoa don khong duoc de trong!");
        if (tongTien <= 0) throw LoiDoiSo("Tong tien hoa don phai lon hon 0 VND!");
    }

    string getMaHoaDon() const { return maHoaDon; }
    int getMaPhong() const { return maPhong; }
    int getMaNguoiThue() const { return maNguoiThue; }
    Date getNgayLap() const { return ngayLap; }
    int getThangThanhToan() const { return thangThanhToan; }
    int getNamThanhToan() const { return namThanhToan; }
    double getTienPhong() const { return tienPhong; }
    double getTienDien() const { return tienDien; }
    double getTienNuoc() const { return tienNuoc; }
    double getTongTien() const { return tongTien; }

    string getKyThanhToan() const {
        string s = "";
        if (thangThanhToan < 10) s += "0";
        s += to_string(thangThanhToan) + "/" + to_string(namThanhToan);
        return s;
    }

    void setMaHoaDon(const string& ma) {
        if (ma.empty()) throw LoiDoiSo("Ma hoa don khong duoc de trong!");
        this->maHoaDon = ma;
    }
    void setMaPhong(int maPhong) { this->maPhong = maPhong; }
    void setMaNguoiThue(int maNguoiThue) { this->maNguoiThue = maNguoiThue; }
    void setNgayLap(const Date& ngay) { this->ngayLap = ngay; }
    void setKyThanhToan(int thang, int nam) {
        if (thang < 1 || thang > 12) throw LoiDoiSo("Thang thanh toan phai tu 1 den 12!");
        if (nam < 1900 || nam > 2100) throw LoiDoiSo("Nam thanh toan phai tu 1900 den 2100!");
        this->thangThanhToan = thang;
        this->namThanhToan = nam;
    }

    void setChiTiet(double phong, double dien, double nuoc) {
        if (phong < 0 || dien < 0 || nuoc < 0) throw LoiDoiSo("Cac khoan tien khong duoc am!");
        this->tienPhong = phong;
        this->tienDien = dien;
        this->tienNuoc = nuoc;
        this->tongTien = phong + dien + nuoc;
        if (this->tongTien <= 0) throw LoiDoiSo("Tong tien hoa don phai lon hon 0 VND!");
    }
    void setTongTien(double tien) {
        if (tien <= 0) throw LoiDoiSo("Tong tien hoa don phai lon hon 0 VND!");
        this->tongTien = tien;
        this->tienPhong = tien;
    }

    void xuat(ostream& os = cout) const {
        os << "Hoa don [Ma: " << maHoaDon
           << " | Phong: " << maPhong
           << " | Ma NT: " << maNguoiThue
           << " | Ky: " << getKyThanhToan()
           << " | Ngay lap: " << ngayLap
           << " | Phong: " << (long long)tienPhong
           << " | Dien: " << (long long)tienDien
           << " | Nuoc: " << (long long)tienNuoc
           << " | Tong: " << (long long)tongTien << " VND]";
    }

    string xuatHoaDon() const {
        return "Hoa don [Ma: " + maHoaDon + " | Phong: " + to_string(maPhong) +
               " | Ma NT: " + to_string(maNguoiThue) +
               " | Ky: " + getKyThanhToan() +
               " | Tong tien: " + to_string((long long)tongTien) + " VND]";
    }

    string toFileString() const {
        // MA_HD|MA_PHONG|MA_NT|NGAY_LAP|THANG_TT|NAM_TT|TIEN_PHONG|TIEN_DIEN|TIEN_NUOC
        return maHoaDon + "|" + to_string(maPhong) + "|" + to_string(maNguoiThue) + "|" +
               ngayLap.toString() + "|" + to_string(thangThanhToan) + "|" + to_string(namThanhToan) + "|" +
               to_string((long long)tienPhong) + "|" + to_string((long long)tienDien) + "|" + to_string((long long)tienNuoc);
    }

    friend ostream& operator<<(ostream& os, const HoaDon& hd) {
        hd.xuat(os);
        return os;
    }
};
