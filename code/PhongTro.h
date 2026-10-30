#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CLASS: PhongTro (abstract)
// ================================================================
class PhongTro {
protected:
    int maPhong;
    string tenPhong;
    string tinhTrang;
    double dienTich;
    double giaThue;

public:
    static double chuyenDienTichSangSo(const string& s) {
        try {
            size_t idx = 0;
            double val = stod(s, &idx);
            return val > 0 ? val : 20.0;
        } catch (...) {
            return 20.0;
        }
    }

    PhongTro()
        : maPhong(0), tenPhong(""), tinhTrang(""), dienTich(0.0), giaThue(0.0) {}
    PhongTro(int maPhong, const string& tenPhong, const string& tinhTrang, double dienTich, double giaThue)
        : maPhong(maPhong), tenPhong(tenPhong), tinhTrang(tinhTrang), dienTich(dienTich), giaThue(giaThue) {
        if (maPhong <= 0) throw LoiDoiSo("Ma phong phai la so nguyen duong (> 0)!");
        if (tenPhong.empty()) throw LoiDoiSo("Ten phong khong duoc de trong!");
        if (dienTich <= 0) throw LoiDoiSo("Dien tich phai la con so lon hon 0 m2!");
        if (giaThue <= 0) throw LoiDoiSo("Gia thue phai lon hon 0 VND!");
    }
    PhongTro(int maPhong, const string& tenPhong, const string& tinhTrang, const string& sDienTich, double giaThue)
        : maPhong(maPhong), tenPhong(tenPhong), tinhTrang(tinhTrang), dienTich(chuyenDienTichSangSo(sDienTich)), giaThue(giaThue) {
        if (maPhong <= 0) throw LoiDoiSo("Ma phong phai la so nguyen duong (> 0)!");
        if (tenPhong.empty()) throw LoiDoiSo("Ten phong khong duoc de trong!");
        if (dienTich <= 0) throw LoiDoiSo("Dien tich phai la con so lon hon 0 m2!");
        if (giaThue <= 0) throw LoiDoiSo("Gia thue phai lon hon 0 VND!");
    }
    virtual ~PhongTro() {}

    int getMaPhong() const { return maPhong; }
    string getTenPhong() const { return tenPhong; }
    string getTinhTrang() const { return tinhTrang; }
    double getDienTich() const { return dienTich; }
    string getDienTichStr() const {
        if ((long long)(dienTich * 10) % 10 == 0) {
            return to_string((long long)dienTich) + "m2";
        } else {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.1fm2", dienTich);
            return string(buf);
        }
    }
    double getGiaThue() const { return giaThue; }

    void setMaPhong(int maPhong) {
        if (maPhong <= 0) throw LoiDoiSo("Ma phong phai la so nguyen duong (> 0)!");
        this->maPhong = maPhong;
    }
    void setTenPhong(const string& tenPhong) {
        if (tenPhong.empty()) throw LoiDoiSo("Ten phong khong duoc de trong!");
        this->tenPhong = tenPhong;
    }
    void setTinhTrang(const string& tinhTrangMoi) { this->tinhTrang = tinhTrangMoi; }
    void setDienTich(double dienTich) {
        if (dienTich <= 0) throw LoiDoiSo("Dien tich phai lon hon 0 m2!");
        this->dienTich = dienTich;
    }
    void setDienTich(const string& sDienTich) {
        this->dienTich = chuyenDienTichSangSo(sDienTich);
    }
    void setGiaThue(double giaMoi) {
        if (giaMoi <= 0) throw LoiDoiSo("Gia thue phai lon hon 0 VND!");
        this->giaThue = giaMoi;
    }

    virtual double tinhGiaThue() const = 0;
    virtual void xuat(ostream& os = cout) const = 0;
    virtual string toString() const = 0;
    virtual string toFileString() const = 0;

    friend ostream& operator<<(ostream& os, const PhongTro& pt) {
        pt.xuat(os);
        return os;
    }
};

// ================================================================
//  CLASS: PhongTroThuong
// ================================================================
class PhongTroThuong : public PhongTro {
private:
    bool coGac;
public:
    PhongTroThuong() : PhongTro(), coGac(false) {}
    PhongTroThuong(int maPhong, const string& tenPhong, const string& tinhTrang, double dienTich, double giaThue, bool coGac = false)
        : PhongTro(maPhong, tenPhong, tinhTrang, dienTich, giaThue), coGac(coGac) {}
    PhongTroThuong(int maPhong, const string& tenPhong, const string& tinhTrang, const string& dienTich, double giaThue, bool coGac = false)
        : PhongTro(maPhong, tenPhong, tinhTrang, dienTich, giaThue), coGac(coGac) {}

    bool getCoGac() const { return coGac; }
    void setCoGac(bool coGac) { this->coGac = coGac; }

    double tinhGiaThue() const override { return giaThue; }

    void xuat(ostream& os = cout) const override {
        os << "Phong Thuong [Ma: " << maPhong << " | Ten: " << tenPhong
           << " | Tinh trang: " << tinhTrang << " | Dien tich: " << getDienTichStr()
           << " | Gia goc: " << (long long)giaThue
           << " | Gac lung: " << (coGac ? "Co" : "Khong")
           << " | Tong gia: " << (long long)tinhGiaThue() << "]";
    }

    string toString() const override {
        return "Phong Thuong [Ma: " + to_string(maPhong) + " | Ten: " + tenPhong + "]";
    }

    string toFileString() const override {
        // THUONG|maPhong|tenPhong|tinhTrang|dienTich|giaThue|coGacLung
        return "THUONG|" + to_string(maPhong) + "|" + tenPhong + "|" + tinhTrang + "|" +
               getDienTichStr() + "|" + to_string((long long)giaThue) + "|" + (coGac ? "1" : "0");
    }
};

// ================================================================
//  CLASS: PhongTroVip
// ================================================================
class PhongTroVip : public PhongTro {
private:
    double phiDichVu;
public:
    PhongTroVip() : PhongTro(), phiDichVu(0.0) {}
    PhongTroVip(int maPhong, const string& tenPhong, const string& tinhTrang, double dienTich, double giaThue, double phiDichVu = 0.0)
        : PhongTro(maPhong, tenPhong, tinhTrang, dienTich, giaThue), phiDichVu(phiDichVu) {}
    PhongTroVip(int maPhong, const string& tenPhong, const string& tinhTrang, const string& dienTich, double giaThue, double phiDichVu = 0.0)
        : PhongTro(maPhong, tenPhong, tinhTrang, dienTich, giaThue), phiDichVu(phiDichVu) {}

    double getPhiDichVu() const { return phiDichVu; }
    void setPhiDichVu(double phiDichVu) { this->phiDichVu = phiDichVu; }

    double tinhGiaThue() const override { return giaThue + phiDichVu; }

    void xuat(ostream& os = cout) const override {
        os << "Phong VIP [Ma: " << maPhong << " | Ten: " << tenPhong
           << " | Tinh trang: " << tinhTrang << " | Dien tich: " << getDienTichStr()
           << " | Gia goc: " << (long long)giaThue
           << " | Phi DV: " << (long long)phiDichVu
           << " | Tong gia: " << (long long)tinhGiaThue() << "]";
    }

    string toString() const override {
        return "Phong VIP [Ma: " + to_string(maPhong) + " | Ten: " + tenPhong + "]";
    }

    string toFileString() const override {
        // VIP|maPhong|tenPhong|tinhTrang|dienTich|giaThue|phiDichVu
        return "VIP|" + to_string(maPhong) + "|" + tenPhong + "|" + tinhTrang + "|" +
               getDienTichStr() + "|" + to_string((long long)giaThue) + "|" + to_string((long long)phiDichVu);
    }
};
