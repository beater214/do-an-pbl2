#include <iostream>

using namespace std;

// ================================================================
//  CLASS: QuanLyPhong
// ================================================================
class QuanLyPhong {
private:
    LinkedList<PhongTro*> danhSachPhong;

public:
    QuanLyPhong() {}
    virtual ~QuanLyPhong() {
        giaiPhongBoNho();
    }

    void giaiPhongBoNho() {
        for (PhongTro* pt : danhSachPhong) delete pt;
        danhSachPhong.clear();
    }

    void themPhongTro(PhongTro* phongTro) {
        if (phongTro != nullptr) danhSachPhong.push_back(phongTro);
    }

    void xoaPhongTro(int maPhong) {
        for (auto it = danhSachPhong.begin(); it != danhSachPhong.end(); ++it) {
            if ((*it)->getMaPhong() == maPhong) {
                delete *it;
                danhSachPhong.erase(it);
                break;
            }
        }
    }

    void capNhatThongTin(PhongTro* phongTro) {
        if (phongTro == nullptr) return;
        for (auto it = danhSachPhong.begin(); it != danhSachPhong.end(); ++it) {
            if ((*it)->getMaPhong() == phongTro->getMaPhong()) {
                delete *it;
                *it = phongTro;
                return;
            }
        }
    }

    const LinkedList<PhongTro*>& layDanhSachPhong() const { return danhSachPhong; }

    PhongTro* timKiemPhongTro(int maPhong) const {
        for (PhongTro* pt : danhSachPhong)
            if (pt->getMaPhong() == maPhong) return pt;
        return nullptr;
    }

    LinkedList<PhongTro*> layDanhSachPhongTheoTinhTrang(const string& tinhTrang) const {
        LinkedList<PhongTro*> ds;
        for (PhongTro* pt : danhSachPhong) {
            if (pt->getTinhTrang() == tinhTrang) {
                ds.push_back(pt);
            }
        }
        return ds;
    }

    LinkedList<PhongTro*> timPhongTheoKhoangGia(double giaMin, double giaMax) const {
        LinkedList<PhongTro*> ds;
        for (PhongTro* pt : danhSachPhong) {
            double gia = pt->tinhGiaThue();
            if (gia >= giaMin && gia <= giaMax) {
                ds.push_back(pt);
            }
        }
        return ds;
    }

    // Tim kiem phong tro co gac lung (Phong tro thuong co gac)
    LinkedList<PhongTro*> timPhongCoGacLung() const {
        LinkedList<PhongTro*> ds;
        for (PhongTro* pt : danhSachPhong) {
            PhongTroThuong* ptt = dynamic_cast<PhongTroThuong*>(pt);
            if (ptt != nullptr && ptt->getCoGac()) {
                ds.push_back(pt);
            }
        }
        return ds;
    }

    // Tim kiem phong co dien tich lon hon x m2
    LinkedList<PhongTro*> timPhongTheoDienTichLonHon(double dienTichMin) const {
        LinkedList<PhongTro*> ds;
        for (PhongTro* pt : danhSachPhong) {
            if (pt->getDienTich() > dienTichMin) {
                ds.push_back(pt);
            }
        }
        return ds;
    }

    // ------------------------------------------------------------
    //  CAC PHUONG THUC SAP XEP (THUAT TOAN INTERCHANGE SORT)
    // ------------------------------------------------------------
    template <typename Compare>
    void sapXep(Compare cmp) {
        danhSachPhong.sort(cmp);
    }

    void sapXepTheoDienTich(bool tangDan = true) {
        if (tangDan) {
            danhSachPhong.sort([](const PhongTro* a, const PhongTro* b) {
                return a->getDienTich() < b->getDienTich();
            });
        } else {
            danhSachPhong.sort([](const PhongTro* a, const PhongTro* b) {
                return a->getDienTich() > b->getDienTich();
            });
        }
    }

    void sapXepTheoGiaThue(bool tangDan = true) {
        if (tangDan) {
            danhSachPhong.sort([](const PhongTro* a, const PhongTro* b) {
                return a->tinhGiaThue() < b->tinhGiaThue();
            });
        } else {
            danhSachPhong.sort([](const PhongTro* a, const PhongTro* b) {
                return a->tinhGiaThue() > b->tinhGiaThue();
            });
        }
    }

    bool docFile(const string& filePath) {
        ifstream fin(filePath);
        if (!fin.is_open()) return false;
        giaiPhongBoNho();
        string line;
        while (getline(fin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            try {
                stringstream ss(line);
                string loai, sMa, ten, tinhTrang, dienTich, sGia, sExtra;
                if (getline(ss, loai, '|') &&
                    getline(ss, sMa, '|') &&
                    getline(ss, ten, '|') &&
                    getline(ss, tinhTrang, '|') &&
                    getline(ss, dienTich, '|') &&
                    getline(ss, sGia, '|') &&
                    getline(ss, sExtra, '|')) {
                    int ma = stoi(sMa);
                    double gia = stod(sGia);
                    if (loai == "THUONG") {
                        bool gac = (sExtra == "1" || sExtra == "true");
                        danhSachPhong.push_back(new PhongTroThuong(ma, ten, tinhTrang, dienTich, gia, gac));
                    } else if (loai == "VIP") {
                        double phi = stod(sExtra);
                        danhSachPhong.push_back(new PhongTroVip(ma, ten, tinhTrang, dienTich, gia, phi));
                    }
                }
            } catch (...) {
                // Bo qua dong du lieu sai cu phap de tranh crash chuong trinh
            }
        }
        fin.close();
        return true;
    }

    bool ghiFile(const string& filePath) const {
        ofstream fout(filePath);
        if (!fout.is_open()) return false;
        fout << "# LOAI_PHONG|MA_PHONG|TEN_PHONG|TINH_TRANG|DIEN_TICH|GIA_THUE|EXTRA(GAC/PHI_DV)\n";
        for (PhongTro* pt : danhSachPhong) {
            fout << pt->toFileString() << "\n";
        }
        fout.close();
        return true;
    }
};
