#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CLASS: Date
// ================================================================
class Date {
private:
    int ngay, thang, nam;
public:
    static bool laNamNhuan(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int soNgayTrongThang(int m, int y) {
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        if (m == 2) return laNamNhuan(y) ? 29 : 28;
        return 31;
    }

    static void kiemTraHopLe(int d, int m, int y) {
        if (y < 1900 || y > 2100)
            throw LoiDoiSo("Nam khong hop le (phai tu 1900 den 2100)!");
        if (m < 1 || m > 12)
            throw LoiDoiSo("Thang khong hop le (phai tu 1 den 12)!");
        int maxD = soNgayTrongThang(m, y);
        if (d < 1 || d > maxD)
            throw LoiDoiSo("Ngay " + to_string(d) + " khong hop le cho thang " + to_string(m) + "/" + to_string(y) + " (1 - " + to_string(maxD) + ")!");
    }

    Date(int ngay = 1, int thang = 1, int nam = 2000) {
        kiemTraHopLe(ngay, thang, nam);
        this->ngay = ngay;
        this->thang = thang;
        this->nam = nam;
    }

    int getNgay() const { return ngay; }
    int getThang() const { return thang; }
    int getNam() const { return nam; }

    void setNgay(int ngay) {
        kiemTraHopLe(ngay, this->thang, this->nam);
        this->ngay = ngay;
    }
    void setThang(int thang) {
        kiemTraHopLe(this->ngay, thang, this->nam);
        this->thang = thang;
    }
    void setNam(int nam) {
        kiemTraHopLe(this->ngay, this->thang, nam);
        this->nam = nam;
    }

    void xuat() const {
        if (ngay < 10) cout << "0";
        cout << ngay << "/";
        if (thang < 10) cout << "0";
        cout << thang << "/" << nam;
    }

    string toString() const {
        string s = "";
        if (ngay < 10) s += "0";
        s += to_string(ngay) + "/";
        if (thang < 10) s += "0";
        s += to_string(thang) + "/" + to_string(nam);
        return s;
    }

    // Chuyen chuoi "dd/mm/yyyy" hoac "d/m/y" thanh doi tuong Date
    static Date fromString(const string& s) {
        try {
            int d = 1, m = 1, y = 2000;
            char c1 = '/', c2 = '/';
            stringstream ss(s);
            if (ss >> d >> c1 >> m >> c2 >> y) {
                kiemTraHopLe(d, m, y);
                return Date(d, m, y);
            }
        } catch (...) {
            return Date(1, 1, 2000);
        }
        return Date(1, 1, 2000);
    }

    bool operator==(const Date& other) const {
        return ngay == other.ngay && thang == other.thang && nam == other.nam;
    }
    bool operator!=(const Date& other) const {
        return !(*this == other);
    }
    bool operator<(const Date& other) const {
        if (nam != other.nam) return nam < other.nam;
        if (thang != other.thang) return thang < other.thang;
        return ngay < other.ngay;
    }
    bool operator<=(const Date& other) const {
        return *this < other || *this == other;
    }
    bool operator>(const Date& other) const {
        return other < *this;
    }
    bool operator>=(const Date& other) const {
        return other <= *this;
    }

    // Tinh so tuoi tinh den ngayMoc
    int tinhTuoi(const Date& ngayMoc) const {
        int tuoi = ngayMoc.nam - nam;
        if (ngayMoc.thang < thang || (ngayMoc.thang == thang && ngayMoc.ngay < ngay)) {
            tuoi--;
        }
        return tuoi;
    }

    // Cong them so thang
    Date congThang(int soThang) const {
        int d = ngay;
        int m = thang + soThang;
        int y = nam;
        y += (m - 1) / 12;
        m = (m - 1) % 12 + 1;
        int maxD = soNgayTrongThang(m, y);
        if (d > maxD) d = maxD;
        return Date(d, m, y);
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        if (d.ngay < 10) os << "0";
        os << d.ngay << "/";
        if (d.thang < 10) os << "0";
        os << d.thang << "/" << d.nam;
        return os;
    }

    friend istream& operator>>(istream& is, Date& d) {
        is >> d.ngay >> d.thang >> d.nam;
        return is;
    }
};
