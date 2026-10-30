#include <iostream>

using namespace std;

// ================================================================
//  CLASS: QuanLyHopDong
// ================================================================
class QuanLyHopDong {
private:
    LinkedList<HopDongThue> danhSachHopDong;

public:
    QuanLyHopDong() {}

    void themHopDong(const HopDongThue& hopDong) { danhSachHopDong.push_back(hopDong); }

    void xoaHopDong(int maHopDong) {
        for (auto it = danhSachHopDong.begin(); it != danhSachHopDong.end(); ++it) {
            if (it->getMaHopDong() == maHopDong) {
                danhSachHopDong.erase(it);
                break;
            }
        }
    }

    void capNhatThongTin(const HopDongThue& hopDong) {
        for (auto it = danhSachHopDong.begin(); it != danhSachHopDong.end(); ++it) {
            if (it->getMaHopDong() == hopDong.getMaHopDong()) {
                *it = hopDong;
                return;
            }
        }
    }

    const LinkedList<HopDongThue>& layDanhSachHopDong() const { return danhSachHopDong; }

    HopDongThue timKiemHopDong(int maHopDong) const {
        for (const HopDongThue& hd : danhSachHopDong)
            if (hd.getMaHopDong() == maHopDong) return hd;
        return HopDongThue();
    }

    void xoaHopDongTheoPhong(int maPhong) {
        for (auto it = danhSachHopDong.begin(); it != danhSachHopDong.end(); ++it) {
            if (it->getMaPhong() == maPhong) {
                danhSachHopDong.erase(it);
                break;
            }
        }
    }

    // Kiem tra xem maPhong co hop dong nao bi trung thoi gian voi [ngayBD, ngayBD + thoiHan] khong
    const HopDongThue* timHopDongBiTrung(int maPhong, const Date& ngayBD, int thoiHan, int maHDBoQua = 0) const {
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaPhong() == maPhong && hd.getMaHopDong() != maHDBoQua) {
                if (hd.kiemTraTrungKhoangThoiGian(ngayBD, thoiHan)) {
                    return &hd;
                }
            }
        }
        return nullptr;
    }

    // Lay tat ca hop dong cua mot phong tro (co the co nhieu hop dong o cac khoang thoi gian khac nhau)
    LinkedList<HopDongThue> layDanhSachHopDongTheoPhong(int maPhong) const {
        LinkedList<HopDongThue> ds;
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaPhong() == maPhong) {
                ds.push_back(hd);
            }
        }
        return ds;
    }

    // Tim hop dong cua phong co hieu luc trong ky thang/nam
    HopDongThue timHopDongTheoPhongVaKy(int maPhong, int thang, int nam) const {
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaPhong() == maPhong && hd.chuaKy(thang, nam)) {
                return hd;
            }
        }
        return HopDongThue();
    }

    int timMaPhongTheoNguoiThue(int maNguoiThue) const {
        int maP = 0;
        Date ngayMoiNhat(1, 1, 1900);
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaNguoiThue() == maNguoiThue) {
                if (hd.getNgayLap() >= ngayMoiNhat) {
                    ngayMoiNhat = hd.getNgayLap();
                    maP = hd.getMaPhong();
                }
            }
        }
        return maP;
    }

    int timMaNguoiThueTheoPhong(int maPhong) const {
        int maNT = 0;
        Date ngayMoiNhat(1, 1, 1900);
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaPhong() == maPhong) {
                if (hd.getNgayLap() >= ngayMoiNhat) {
                    ngayMoiNhat = hd.getNgayLap();
                    maNT = hd.getMaNguoiThue();
                }
            }
        }
        return maNT;
    }

    HopDongThue timKiemTheoPhong(int maPhong) const {
        HopDongThue hdMoiNhat;
        Date ngayMoiNhat(1, 1, 1900);
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaPhong() == maPhong) {
                if (hd.getNgayLap() >= ngayMoiNhat) {
                    ngayMoiNhat = hd.getNgayLap();
                    hdMoiNhat = hd;
                }
            }
        }
        return hdMoiNhat;
    }

    LinkedList<HopDongThue> layLichSuHopDongTheoNguoiThue(int maNguoiThue) const {
        LinkedList<HopDongThue> ds;
        for (const HopDongThue& hd : danhSachHopDong) {
            if (hd.getMaNguoiThue() == maNguoiThue) {
                ds.push_back(hd);
            }
        }
        return ds;
    }

    bool docFile(const string& filePath) {
        ifstream fin(filePath);
        if (!fin.is_open()) return false;
        danhSachHopDong.clear();
        string line;
        while (getline(fin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            stringstream ss(line);
            string sMaHD, sMaPhong, sMaNT, sNgayLap, sThoiHan, sGiaThue;
            if (getline(ss, sMaHD, '|') &&
                getline(ss, sMaPhong, '|') &&
                getline(ss, sMaNT, '|') &&
                getline(ss, sNgayLap, '|') &&
                getline(ss, sThoiHan, '|') &&
                getline(ss, sGiaThue, '|')) {
                int maHD = stoi(sMaHD);
                int maP = stoi(sMaPhong);
                int maNT = stoi(sMaNT);
                Date nl = Date::fromString(sNgayLap);
                int th = stoi(sThoiHan);
                double gia = stod(sGiaThue);
                danhSachHopDong.push_back(HopDongThue(maHD, maP, maNT, nl, th, gia));
            }
        }
        fin.close();
        return true;
    }

    bool ghiFile(const string& filePath) const {
        ofstream fout(filePath);
        if (!fout.is_open()) return false;
        fout << "# MA_HD|MA_PHONG|MA_NT|NGAY_LAP|THOI_HAN|GIA_THUE\n";
        for (const HopDongThue& hd : danhSachHopDong) {
            fout << hd.toFileString() << "\n";
        }
        fout.close();
        return true;
    }
};
