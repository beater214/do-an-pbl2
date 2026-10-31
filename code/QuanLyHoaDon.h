#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CLASS: QuanLyHoaDon
// ================================================================
class QuanLyHoaDon {
private:
    LinkedList<HoaDon> danhSachHoaDon;

public:
    QuanLyHoaDon() {}

    void themHoaDon(const HoaDon& hoaDon) { danhSachHoaDon.push_back(hoaDon); }

    void xoaHoaDon(const string& maHoaDon) {
        for (auto it = danhSachHoaDon.begin(); it != danhSachHoaDon.end(); ++it) {
            if (it->getMaHoaDon() == maHoaDon) {
                danhSachHoaDon.erase(it);
                break;
            }
        }
    }

    void capNhatHoaDon(const HoaDon& hoaDon) {
        for (auto it = danhSachHoaDon.begin(); it != danhSachHoaDon.end(); ++it) {
            if (it->getMaHoaDon() == hoaDon.getMaHoaDon()) {
                *it = hoaDon;
                return;
            }
        }
    }

    HoaDon timKiemHoaDon(const string& maHoaDon) const {
        for (const HoaDon& hd : danhSachHoaDon)
            if (hd.getMaHoaDon() == maHoaDon) return hd;
        return HoaDon();
    }

    const LinkedList<HoaDon>& layDanhSachHoaDon() const { return danhSachHoaDon; }

    double tinhTongDoanhThu() const {
        double tong = 0.0;
        for (const HoaDon& hd : danhSachHoaDon) tong += hd.getTongTien();
        return tong;
    }

    double tinhTongTienPhong(int thang = 0, int nam = 0) const {
        double tong = 0.0;
        for (const HoaDon& hd : danhSachHoaDon) {
            if ((thang == 0 || hd.getNgayLap().getThang() == thang) &&
                (nam == 0 || hd.getNgayLap().getNam() == nam)) {
                tong += hd.getTienPhong();
            }
        }
        return tong;
    }

    double tinhTongTienDien(int thang = 0, int nam = 0) const {
        double tong = 0.0;
        for (const HoaDon& hd : danhSachHoaDon) {
            if ((thang == 0 || hd.getNgayLap().getThang() == thang) &&
                (nam == 0 || hd.getNgayLap().getNam() == nam)) {
                tong += hd.getTienDien();
            }
        }
        return tong;
    }

    double tinhTongTienNuoc(int thang = 0, int nam = 0) const {
        double tong = 0.0;
        for (const HoaDon& hd : danhSachHoaDon) {
            if ((thang == 0 || hd.getNgayLap().getThang() == thang) &&
                (nam == 0 || hd.getNgayLap().getNam() == nam)) {
                tong += hd.getTienNuoc();
            }
        }
        return tong;
    }

    double tinhTongDoanhThuThang(int thang, int nam) const {
        double tong = 0.0;
        for (const HoaDon& hd : danhSachHoaDon) {
            if (hd.getNgayLap().getThang() == thang && hd.getNgayLap().getNam() == nam) {
                tong += hd.getTongTien();
            }
        }
        return tong;
    }

    LinkedList<HoaDon> timHoaDonTienDienCaoHon(double mucTien, int thang = 0, int nam = 0) const {
        LinkedList<HoaDon> ds;
        for (const HoaDon& hd : danhSachHoaDon) {
            bool hopLeThoiGian = true;
            if (thang != 0 && hd.getNgayLap().getThang() != thang) hopLeThoiGian = false;
            if (nam != 0 && hd.getNgayLap().getNam() != nam) hopLeThoiGian = false;
            if (hopLeThoiGian && hd.getTienDien() > mucTien) {
                ds.push_back(hd);
            }
        }
        return ds;
    }

    LinkedList<HoaDon> layHoaDonTheoThang(int thang, int nam) const {
        LinkedList<HoaDon> ds;
        for (const HoaDon& hd : danhSachHoaDon) {
            if (hd.getNgayLap().getThang() == thang && hd.getNgayLap().getNam() == nam) {
                ds.push_back(hd);
            }
        }
        return ds;
    }

    bool daDongTienThang(int maPhong, int maNT, int thang, int nam) const {
        for (const HoaDon& hd : danhSachHoaDon) {
            bool hopLePhong = (hd.getMaPhong() == maPhong);
            bool hopLeNT = (maNT == 0 || hd.getMaNguoiThue() == maNT);
            bool hopLeKy = (hd.getThangThanhToan() == thang && hd.getNamThanhToan() == nam);
            if (hopLePhong && hopLeNT && hopLeKy) {
                return true;
            }
        }
        return false;
    }

    HoaDon timHoaDonTheoKy(int maPhong, int thang, int nam) const {
        for (const HoaDon& hd : danhSachHoaDon) {
            if (hd.getMaPhong() == maPhong &&
                hd.getThangThanhToan() == thang &&
                hd.getNamThanhToan() == nam) {
                return hd;
            }
        }
        return HoaDon();
    }

    // ------------------------------------------------------------
    //  CAC PHUONG THUC SAP XEP (THUAT TOAN INTERCHANGE SORT)
    // ------------------------------------------------------------
    template <typename Compare>
    void sapXep(Compare cmp) {
        danhSachHoaDon.sort(cmp);
    }

    void sapXepTheoNgayLap(bool tangDan = true) {
        if (tangDan) {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getNgayLap() < b.getNgayLap();
            });
        } else {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return b.getNgayLap() < a.getNgayLap();
            });
        }
    }

    void sapXepTheoTienPhong(bool tangDan = true) {
        if (tangDan) {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTienPhong() < b.getTienPhong();
            });
        } else {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTienPhong() > b.getTienPhong();
            });
        }
    }

    void sapXepTheoTienDien(bool tangDan = true) {
        if (tangDan) {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTienDien() < b.getTienDien();
            });
        } else {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTienDien() > b.getTienDien();
            });
        }
    }

    void sapXepTheoTienNuoc(bool tangDan = true) {
        if (tangDan) {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTienNuoc() < b.getTienNuoc();
            });
        } else {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTienNuoc() > b.getTienNuoc();
            });
        }
    }

    void sapXepTheoTongTien(bool tangDan = true) {
        if (tangDan) {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTongTien() < b.getTongTien();
            });
        } else {
            danhSachHoaDon.sort([](const HoaDon& a, const HoaDon& b) {
                return a.getTongTien() > b.getTongTien();
            });
        }
    }

    bool docFile(const string& filePath) {
        ifstream fin(filePath);
        if (!fin.is_open()) return false;
        danhSachHoaDon.clear();
        string line;
        while (getline(fin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            stringstream ss(line);
            string maHD, sMaP, sMaNT, sNgayLap, sThangTT, sNamTT, sPhong, sDien, sNuoc;
            if (getline(ss, maHD, '|') &&
                getline(ss, sMaP, '|') &&
                getline(ss, sMaNT, '|') &&
                getline(ss, sNgayLap, '|') &&
                getline(ss, sThangTT, '|') &&
                getline(ss, sNamTT, '|') &&
                getline(ss, sPhong, '|') &&
                getline(ss, sDien, '|') &&
                getline(ss, sNuoc, '|')) {
                int maP = stoi(sMaP);
                int maNT = stoi(sMaNT);
                Date nl = Date::fromString(sNgayLap);
                int thangTT = stoi(sThangTT);
                int namTT = stoi(sNamTT);
                double phong = stod(sPhong);
                double dien = stod(sDien);
                double nuoc = stod(sNuoc);
                danhSachHoaDon.push_back(HoaDon(maHD, maP, maNT, nl, thangTT, namTT, phong, dien, nuoc));
            }
        }
        fin.close();
        return true;
    }

    bool ghiFile(const string& filePath) const {
        ofstream fout(filePath);
        if (!fout.is_open()) return false;
        fout << "# MA_HD|MA_PHONG|MA_NT|NGAY_LAP|THANG_TT|NAM_TT|TIEN_PHONG|TIEN_DIEN|TIEN_NUOC\n";
        for (const HoaDon& hd : danhSachHoaDon) {
            fout << hd.toFileString() << "\n";
        }
        fout.close();
        return true;
    }
};
