#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CLASS: HopDongThue
// ================================================================
class HopDongThue {
private:
    int maHopDong, maPhong, maNguoiThue;
    Date ngayLap;
    int thoiHan;
    double giaThue;

public:
    HopDongThue()
        : maHopDong(0), maPhong(0), maNguoiThue(0), ngayLap(Date()), thoiHan(0), giaThue(0.0) {}
    HopDongThue(int maHopDong, int maPhong, int maNguoiThue, const Date& ngayLap, int thoiHan, double giaThue)
        : maHopDong(maHopDong), maPhong(maPhong), maNguoiThue(maNguoiThue), ngayLap(ngayLap), thoiHan(thoiHan), giaThue(giaThue) {
        if (maHopDong <= 0) throw LoiDoiSo("Ma hop dong phai la so nguyen duong (> 0)!");
        if (thoiHan <= 0 || thoiHan > 120) throw LoiDoiSo("Thoi han hop dong phai tu 1 den 120 thang!");
        if (giaThue <= 0) throw LoiDoiSo("Gia thue phai lon hon 0 VND!");
    }
    HopDongThue(int maHopDong, const Date& ngayLap, int thoiHan, double giaThue)
        : maHopDong(maHopDong), maPhong(0), maNguoiThue(0), ngayLap(ngayLap), thoiHan(thoiHan), giaThue(giaThue) {
        if (maHopDong <= 0) throw LoiDoiSo("Ma hop dong phai la so nguyen duong (> 0)!");
        if (thoiHan <= 0 || thoiHan > 120) throw LoiDoiSo("Thoi han hop dong phai tu 1 den 120 thang!");
        if (giaThue <= 0) throw LoiDoiSo("Gia thue phai lon hon 0 VND!");
    }

    int getMaHopDong() const { return maHopDong; }
    int getMaPhong() const { return maPhong; }
    int getMaNguoiThue() const { return maNguoiThue; }
    Date getNgayLap() const { return ngayLap; }
    int getThoiHan() const { return thoiHan; }
    double getGiaThue() const { return giaThue; }

    void setMaHopDong(int maHopDong) {
        if (maHopDong <= 0) throw LoiDoiSo("Ma hop dong phai la so nguyen duong (> 0)!");
        this->maHopDong = maHopDong;
    }
    void setMaPhong(int maPhong) { this->maPhong = maPhong; }
    void setMaNguoiThue(int maNguoiThue) { this->maNguoiThue = maNguoiThue; }
    void setNgayLap(const Date& ngayLap) { this->ngayLap = ngayLap; }
    void setThoiHan(int thoiHanMoi) {
        if (thoiHanMoi <= 0 || thoiHanMoi > 120) throw LoiDoiSo("Thoi han hop dong phai tu 1 den 120 thang!");
        this->thoiHan = thoiHanMoi;
    }
    void setGiaThue(double giaMoi) {
        if (giaMoi <= 0) throw LoiDoiSo("Gia thue phai lon hon 0 VND!");
        this->giaThue = giaMoi;
    }

    Date getNgayKetThuc() const {
        return ngayLap.congThang(thoiHan);
    }

    // Kiem tra giao nhau giua 2 khoang thoi gian [ngayLap, ngayKetThuc) va [bdKhac, bdKhac + thoiHanKhac)
    bool kiemTraTrungKhoangThoiGian(const Date& bdKhac, int thoiHanKhac) const {
        Date ktKhac = bdKhac.congThang(thoiHanKhac);
        Date bd1 = ngayLap;
        Date kt1 = getNgayKetThuc();
        return (bd1 < ktKhac && bdKhac < kt1);
    }

    // Kiem tra mot ngay co nam trong thoi gian thue cua hop dong khong
    bool chuaNgay(const Date& d) const {
        return (ngayLap <= d && d < getNgayKetThuc());
    }

    // Kiem tra mot ky thang/nam co nam trong thoi gian thue cua hop dong khong
    bool chuaKy(int thang, int nam) const {
        Date ngayDauThang(1, thang, nam);
        Date ngayCuoiThang(Date::soNgayTrongThang(thang, nam), thang, nam);
        Date kt = getNgayKetThuc();
        return (ngayLap <= ngayCuoiThang && ngayDauThang < kt);
    }

    void xuat(ostream& os = cout) const {
        os << "Ma HD: " << maHopDong
           << " | Ma Phong: " << maPhong
           << " | Ma NT: " << maNguoiThue
           << " | Tu: " << ngayLap
           << " | Den: " << getNgayKetThuc()
           << " | Thoi han: " << thoiHan << " thang"
           << " | Gia thue: " << (long long)giaThue;
    }

    string toFileString() const {
        // MA_HD|MA_PHONG|MA_NT|NGAY_LAP|THOI_HAN|GIA_THUE
        return to_string(maHopDong) + "|" + to_string(maPhong) + "|" + to_string(maNguoiThue) + "|" +
               ngayLap.toString() + "|" + to_string(thoiHan) + "|" + to_string((long long)giaThue);
    }

    friend ostream& operator<<(ostream& os, const HopDongThue& hd) {
        hd.xuat(os);
        return os;
    }
};
