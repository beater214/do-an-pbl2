#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  CAC HAM NHAP LIEU AN TOAN (LAP LAI CHO DEN KHI DUNG - TRY CATCH)
// ================================================================

// Nhap so nguyen trong khoang [minVal, maxVal], sai bat nhap lai
int nhapSoNguyen(const string& prompt, int minVal = GIA_TRI_MIN, int maxVal = GIA_TRI_MAX) {
    while (true) {
        try {
            int val;
            cout << prompt;
            if (!(cin >> val)) {
                if (cin.eof()) exit(0);
                xoaBoDem();
                throw LoiDoiSo("Du lieu phai la so nguyen hop le!");
            }
            if (val < minVal || val > maxVal) {
                throw LoiVuotKhoang("Gia tri phai trong khoang [" + to_string(minVal) + " - " + to_string(maxVal) + "]!");
            }
            return val;
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// Nhap so thuc lon hon minVal, sai bat nhap lai
double nhapSoThuc(const string& prompt, double minVal = 0.0) {
    while (true) {
        try {
            double val;
            cout << prompt;
            if (!(cin >> val)) {
                if (cin.eof()) exit(0);
                xoaBoDem();
                throw LoiDoiSo("Du lieu phai la so thuc hop le!");
            }
            if (val <= minVal) {
                throw LoiVuotKhoang("Gia tri phai lon hon " + to_string((long long)minVal) + "!");
            }
            return val;
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// Nhap chuoi ky tu, khong duoc de trong
string nhapChuoi(const string& prompt, bool batBuoc = true) {
    while (true) {
        try {
            string val;
            cout << prompt;
            if (cin.eof()) exit(0);
            getline(cin >> ws, val);
            if (cin.eof()) exit(0);
            while (!val.empty() && laKhoangTrang(val.back())) {
                val.pop_back();
            }
            if (batBuoc && val.empty()) {
                throw LoiDoiSo("Noi dung khong duoc de trong!");
            }
            return val;
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// Nhap so dien thoai (kiem tra dung 10 so, bat dau bang 0)
string nhapSoDienThoai(const string& prompt = "-> Nhap so dien thoai (10 chu so): ") {
    while (true) {
        try {
            string sdt = nhapChuoi(prompt);
            Nguoi::kiemTraSoDienThoai(sdt); // Throws neu khong phai 10 so, khong bat dau bang 0
            return sdt;
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// Nhap ngay thang nam hop le (kiem tra ngay theo thang va nam nhuan)
Date nhapNgayThangNam(const string& moTa = "ngay thang nam") {
    while (true) {
        try {
            cout << "-> Nhap " << moTa << " (ngay thang nam, vd: 15 5 2002): ";
            int d, m, y;
            if (!(cin >> d >> m >> y)) {
                if (cin.eof()) exit(0);
                xoaBoDem();
                throw LoiDoiSo("Ngay thang nam phai la cac chu so cach nhau bang khoang trang!");
            }
            Date::kiemTraHopLe(d, m, y); // Throws neu ngay/thang/nam bat hop ly
            return Date(d, m, y);
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// Nhap ma phong moi (kiem tra khong duoc trung)
int nhapMaPhongMoi(QuanLyPhong& qlPhong) {
    while (true) {
        try {
            int ma = nhapSoNguyen("-> Nhap ma phong: ", 1);
            if (qlPhong.timKiemPhongTro(ma) != nullptr) {
                throw LoiThucThi("Ma phong " + to_string(ma) + " da ton tai trong he thong!");
            }
            return ma;
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// Nhap ma nguoi thue moi (kiem tra khong duoc trung)
int nhapMaNguoiThueMoi(QuanLyNguoiThue& qlNguoiThue) {
    while (true) {
        try {
            int ma = nhapSoNguyen("-> Nhap ma nguoi thue: ", 1);
            if (qlNguoiThue.timKiemNguoiThue(ma) != nullptr) {
                throw LoiThucThi("Ma nguoi thue " + to_string(ma) + " da ton tai trong he thong!");
            }
            return ma;
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }
}

// ================================================================
//  NGHIEP VU LIEN KET (THUE PHONG & TRA PHONG)
// ================================================================
void thuePhongTro(QuanLyPhong& qlPhong, QuanLyNguoiThue& qlNguoiThue, QuanLyHopDong& qlHopDong, QuanLyHoaDon& qlHoaDon) {
    cout << "\n===============================================================\n";
    cout << "|           NGHIEP VU THUE PHONG (TU DONG LIEN KET)           |\n";
    cout << "===============================================================\n";

    int soLuong = nhapSoNguyen("-> Nhap so luong phong/hop dong muon thue (Nhap 0 de huy): ", 0);
    if (soLuong <= 0) {
        inThongBaoLoi("Da huy thao tac thue phong.");
        return;
    }

    int daThue = 0;
    for (int k = 0; k < soLuong; ++k) {
        if (soLuong > 1) {
            cout << "\n===============================================================\n";
            cout << "|      THUE PHONG / LAP HOP DONG THU " << (k + 1) << "/" << soLuong << "                      |\n";
            cout << "===============================================================\n";
        }

        // 1. Chon phong can thue
        PhongTro* pt = nullptr;
        int maPhong = 0;
        bool boQua = false;
        while (pt == nullptr) {
            try {
                maPhong = nhapSoNguyen("-> Nhap ma phong can thue (Nhap 0 de bo qua): ", 0);
                if (maPhong == 0) {
                    boQua = true;
                    break;
                }
                pt = qlPhong.timKiemPhongTro(maPhong);
                if (pt == nullptr) {
                    throw LoiThucThi("Khong tim thay phong voi ma: " + to_string(maPhong));
                }
                // Hien thi lich su/cac hop dong hien co cua phong nay neu co
                LinkedList<HopDongThue> dsHDCu = qlHopDong.layDanhSachHopDongTheoPhong(maPhong);
                if (!dsHDCu.empty()) {
                    cout << "[i] Phong " << maPhong << " (" << pt->getTenPhong() << ") hien da co " << dsHDCu.size() << " hop dong thue:\n";
                    for (const auto& h : dsHDCu) {
                        NguoiThue* ntCu = qlNguoiThue.timKiemNguoiThue(h.getMaNguoiThue());
                        string tenCu = (ntCu != nullptr) ? ntCu->getHoTen() : ("Ma NT: " + to_string(h.getMaNguoiThue()));
                        cout << "    + Ma HD " << h.getMaHopDong() << ": Tu " << h.getNgayLap().toString()
                             << " den " << h.getNgayKetThuc().toString() << " | Nguoi thue: " << tenCu << "\n";
                    }
                    cout << "    -> Chu y: Ban can chon khoang thoi gian thue KHONG TRUNG LAP voi cac hop dong tren!\n";
                }
            } catch (const NgoaiLe& e) {
                inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
            }
        }

        if (boQua) {
            cout << "[!] Da bo qua luot thue phong nay.\n";
            if (k + 1 < soLuong) {
                int tiep = nhapSoNguyen("    Ban co muon tiep tuc luot thue tiep theo? (1: Co, 0: Dung): ", 0, 1);
                if (tiep == 0) break;
            }
            continue;
        }

        cout << "-> Tim thay: " << pt->getTenPhong() << " | Gia goc: " << (long long)pt->getGiaThue()
             << " VND | Tong gia: " << (long long)pt->tinhGiaThue() << " VND\n";

        // 2. Chon hoac tao nguoi thue
        NguoiThue* nt = nullptr;
        int maNT = 0;
        while (nt == nullptr) {
            try {
                maNT = nhapSoNguyen("-> Nhap ma nguoi thue (Nhap 0 de bo qua): ", 0);
                if (maNT == 0) {
                    boQua = true;
                    break;
                }

                nt = qlNguoiThue.timKiemNguoiThue(maNT);
                if (nt == nullptr) {
                    cout << "[!] Nguoi thue chua co trong he thong! Ban co muon tao ho so moi khong? (1: Co, 0: Nhap lai ma khac): ";
                    int taoMoi = nhapSoNguyen("", 0, 1);
                    if (taoMoi == 1) {
                        xoaBoDem();
                        string hoTen = nhapChuoi("   + Ho va ten: ");
                        Date ns = nhapNgayThangNam("ngay sinh nguoi thue");
                        string sdt = nhapSoDienThoai("   + So dien thoai (10 chu so): ");

                        nt = new NguoiThue(maNT, hoTen, ns, sdt);
                        qlNguoiThue.themNguoiThue(nt);
                        inThongBaoThanhCong("Da tao ho so nguoi thue moi: " + hoTen);
                        break;
                    }
                } else {
                    cout << "-> Xac nhan nguoi thue: " << nt->getHoTen() << " - SDT: " << nt->getSoDienThoai() << "\n";
                }
            } catch (const NgoaiLe& e) {
                inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
            }
        }

        if (boQua) {
            cout << "[!] Da bo qua luot thue phong nay.\n";
            if (k + 1 < soLuong) {
                int tiep = nhapSoNguyen("    Ban co muon tiep tuc luot thue tiep theo? (1: Co, 0: Dung): ", 0, 1);
                if (tiep == 0) break;
            }
            continue;
        }

        // 3. Thong tin hop dong (Xac minh khoang thoi gian thue khong duoc trung lap)
        Date ngayBatDau;
        int thoiHan = 0;
        while (true) {
            try {
                ngayBatDau = nhapNgayThangNam("ngay bat dau hop dong");
                if (ngayBatDau <= nt->getNgaySinh()) {
                    throw LoiDoiSo("Ngay bat dau hop dong (" + ngayBatDau.toString() + 
                                           ") khong the xay ra truoc hoac cung ngay sinh cua nguoi thue (" + 
                                           nt->getNgaySinh().toString() + ")!");
                }
                int tuoi = nt->getNgaySinh().tinhTuoi(ngayBatDau);
                if (tuoi < 18) {
                    throw LoiDoiSo("Nguoi thue moi " + to_string(tuoi) + 
                                           " tuoi tai thoi diem thue! Nguoi dung ten hop dong phai tu 18 tuoi tro len.");
                }
                thoiHan = nhapSoNguyen("-> Nhap thoi han hop dong (1 - 120 thang): ", 1, 120);

                // XAC MINH 2 KHOANG THOI GIAN THUE KHAC NHAU, KHONG BI TRUNG LAP
                const HopDongThue* biTrung = qlHopDong.timHopDongBiTrung(maPhong, ngayBatDau, thoiHan);
                if (biTrung != nullptr) {
                    Date ktMoi = ngayBatDau.congThang(thoiHan);
                    NguoiThue* ntTrung = qlNguoiThue.timKiemNguoiThue(biTrung->getMaNguoiThue());
                    string tenTrung = (ntTrung != nullptr) ? ntTrung->getHoTen() : ("Ma NT " + to_string(biTrung->getMaNguoiThue()));
                    throw LoiThucThi("Khoang thoi gian thue tu " + ngayBatDau.toString() + " den " + ktMoi.toString() +
                                     " bi TRUNG LAP voi Hop Dong Ma " + to_string(biTrung->getMaHopDong()) +
                                     " (tu " + biTrung->getNgayLap().toString() + " den " + biTrung->getNgayKetThuc().toString() +
                                     ", Nguoi thue: " + tenTrung + ")! Vui long chon thoi gian khac.");
                }
                break;
            } catch (const NgoaiLe& e) {
                inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
            }
        }

        // Tu dong sinh ma hop dong duy nhat
        int maHDMoi = 1001;
        const LinkedList<HopDongThue>& dsHD = qlHopDong.layDanhSachHopDong();
        for (const auto& h : dsHD) {
            if (h.getMaHopDong() >= maHDMoi) maHDMoi = h.getMaHopDong() + 1;
        }

        double giaThue = pt->tinhGiaThue();

        // 1. Tao Hop Dong Thue
        HopDongThue hd(maHDMoi, maPhong, maNT, ngayBatDau, thoiHan, giaThue);
        qlHopDong.themHopDong(hd);

        // 2. Cap nhat phong -> "Da thue"
        pt->setTinhTrang("Da thue");

        // 3. Tu dong tao Hoa Don thang dau tien voi ma duy nhat
        int idxBill = (int)qlHoaDon.layDanhSachHoaDon().size() + 1;
        string maHoaDon = "HD" + to_string(idxBill);
        while (qlHoaDon.timKiemHoaDon(maHoaDon).getMaHoaDon() != "") {
            idxBill++;
            maHoaDon = "HD" + to_string(idxBill);
        }
        HoaDon bill(maHoaDon, maPhong, maNT, ngayBatDau, ngayBatDau.getThang(), ngayBatDau.getNam(), giaThue, 0.0, 0.0);
        qlHoaDon.themHoaDon(bill);
        daThue++;

        cout << "\n===============================================================\n";
        cout << "|                  THUE PHONG THANH CONG!                     |\n";
        cout << "===============================================================\n";
        cout << "| [+] Phong         : " << pt->getTenPhong() << " (Ma: " << maPhong << ") -> Trang thai: Da thue\n";
        cout << "| [+] Nguoi thue    : " << nt->getHoTen() << " (Ma NT: " << maNT << ")\n";
        cout << "| [+] Tu dong lap HD: Ma HD: " << maHDMoi << " | Thoi han: " << thoiHan << " thang | Gia: " << (long long)giaThue << " VND\n";
        cout << "| [+] Tu dong lap BL: Ma Hoa Don: " << maHoaDon << " | Tong tien: " << (long long)giaThue << " VND\n";
        cout << "===============================================================\n";
    }

    if (daThue > 0) {
        luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        inThongBaoThanhCong("Da hoan tat thue " + to_string(daThue) + " phong va tu dong tao Hop dong & Hoa don (Da luu file)!");
    } else {
        inThongBaoLoi("Khong co hop dong thue phong nao duoc tao.");
    }
}

void traPhongTro(QuanLyPhong& qlPhong, QuanLyHopDong& qlHopDong, QuanLyNguoiThue& qlNguoiThue, const QuanLyHoaDon& qlHoaDon) {
    cout << "\n===============================================================\n";
    cout << "|              NGHIEP VU TRA PHONG / THANH LY                 |\n";
    cout << "===============================================================\n";

    PhongTro* pt = nullptr;
    int maPhong = 0;
    while (pt == nullptr) {
        try {
            maPhong = nhapSoNguyen("-> Nhap ma phong can tra (Nhap 0 de huy): ", 0);
            if (maPhong == 0) {
                inThongBaoLoi("Da huy thao tac tra phong.");
                return;
            }
            pt = qlPhong.timKiemPhongTro(maPhong);
            if (pt == nullptr) {
                throw LoiThucThi("Khong tim thay phong voi ma: " + to_string(maPhong));
            }
            if (pt->getTinhTrang() != "Da thue") {
                pt = nullptr;
                throw LoiThucThi("Phong " + to_string(maPhong) + " hien dang trong, khong co nguoi thue de tra!");
            }
        } catch (const NgoaiLe& e) {
            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
        }
    }

    int maNT = qlHopDong.timMaNguoiThueTheoPhong(maPhong);
    string tenNT = "Chua xac dinh";
    if (maNT != 0) {
        NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(maNT);
        if (nt != nullptr) tenNT = nt->getHoTen();
    }

    cout << "-> Xac nhan tra phong: " << pt->getTenPhong()
         << " | Nguoi dang thue: " << tenNT << " (Ma NT: " << maNT << ")\n";
    int xacNhan = nhapSoNguyen("-> Ban co chac chan muon tra phong va thanh ly hop dong? (1: Dong y, 0: Huy): ", 0, 1);
    if (xacNhan == 1) {
        pt->setTinhTrang("Con trong");
        qlHopDong.xoaHopDongTheoPhong(maPhong);
        luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        inThongBaoThanhCong("Da tra phong " + to_string(maPhong) + " va thanh ly hop dong thanh cong (Da luu file)!");
    } else {
        inThongBaoLoi("Da huy thao tac tra phong.");
    }
}

void traPhongTro(QuanLyPhong& qlPhong, QuanLyHopDong& qlHopDong, QuanLyNguoiThue& qlNguoiThue) {
    QuanLyHoaDon dummyHD;
    traPhongTro(qlPhong, qlHopDong, qlNguoiThue, dummyHD);
}

// ================================================================
//  CAC MENU CON SAP XEP (THUAT TOAN INTERCHANGE SORT)
// ================================================================

void menuSapXepPhong(QuanLyPhong& qlPhong, const QuanLyHopDong& qlHopDong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHoaDon& qlHoaDon) {
    int lc = -1;
    while (lc != 0) {
        cout << "\n+-------------------------------------------------------------+\n";
        cout << "|                 SAP XEP DANH SACH PHONG TRO                 |\n";
        cout << "|                (Thuat toan: Interchange Sort)               |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "|  [1] Theo dien tich phong tang dan (Be -> Lon)              |\n";
        cout << "|  [2] Theo dien tich phong giam dan (Lon -> Be)              |\n";
        cout << "|  [3] Theo gia thue phong tang dan (Be -> Lon)               |\n";
        cout << "|  [4] Theo gia thue phong giam dan (Lon -> Be)               |\n";
        cout << "|  [0] Quay lai menu Quan ly phong tro                        |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-4]: ";
        if (!(cin >> lc)) { xoaBoDem(); continue; }

        if (lc == 1) {
            qlPhong.sapXepTheoDienTich(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo DIEN TICH TANG DAN (Be -> Lon)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
        } else if (lc == 2) {
            qlPhong.sapXepTheoDienTich(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo DIEN TICH GIAM DAN (Lon -> Be)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
        } else if (lc == 3) {
            qlPhong.sapXepTheoGiaThue(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo GIA THUE TANG DAN (Be -> Lon)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
        } else if (lc == 4) {
            qlPhong.sapXepTheoGiaThue(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo GIA THUE GIAM DAN (Lon -> Be)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
        }
    }
}

void menuSapXepHopDong(QuanLyHopDong& qlHopDong, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHoaDon& qlHoaDon) {
    int lc = -1;
    while (lc != 0) {
        cout << "\n+-------------------------------------------------------------+\n";
        cout << "|                 SAP XEP HOP DONG THUE PHONG                 |\n";
        cout << "|                (Thuat toan: Interchange Sort)               |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "|  [1] Theo thoi gian lap hop dong: Cu -> Moi (Tang dan)      |\n";
        cout << "|  [2] Theo thoi gian lap hop dong: Moi -> Cu (Giam dan)      |\n";
        cout << "|  [3] Theo gia thue tren hop dong: Be -> Lon (Tang dan)      |\n";
        cout << "|  [4] Theo gia thue tren hop dong: Lon -> Be (Giam dan)      |\n";
        cout << "|  [0] Quay lai menu Quan ly hop dong                         |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-4]: ";
        if (!(cin >> lc)) { xoaBoDem(); continue; }

        if (lc == 1) {
            qlHopDong.sapXepTheoNgayLap(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo THOI GIAN LAP CU -> MOI!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
        } else if (lc == 2) {
            qlHopDong.sapXepTheoNgayLap(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo THOI GIAN LAP MOI -> CU!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
        } else if (lc == 3) {
            qlHopDong.sapXepTheoGiaThue(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo GIA THUE TANG DAN (Be -> Lon)!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
        } else if (lc == 4) {
            qlHopDong.sapXepTheoGiaThue(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo GIA THUE GIAM DAN (Lon -> Be)!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
        }
    }
}

void menuSapXepHoaDon(QuanLyHoaDon& qlHoaDon, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong) {
    int lc = -1;
    while (lc != 0) {
        cout << "\n+-------------------------------------------------------------------------+\n";
        cout << "|                        SAP XEP HOA DON THANH TOAN                       |\n";
        cout << "|                      (Thuat toan: Interchange Sort)                     |\n";
        cout << "+-------------------------------------------------------------------------+\n";
        cout << "|  [1]  Theo thoi gian lap hoa don: Cu -> Moi (Tang dan)                  |\n";
        cout << "|  [2]  Theo thoi gian lap hoa don: Moi -> Cu (Giam dan)                  |\n";
        cout << "|  [3]  Theo tien phong / tien tra hoa don: Be -> Lon (Tang dan)          |\n";
        cout << "|  [4]  Theo tien phong / tien tra hoa don: Lon -> Be (Giam dan)          |\n";
        cout << "|  [5]  Theo tien dien: Be -> Lon (Tang dan)                              |\n";
        cout << "|  [6]  Theo tien dien: Lon -> Be (Giam dan)                              |\n";
        cout << "|  [7]  Theo tien nuoc: Be -> Lon (Tang dan)                              |\n";
        cout << "|  [8]  Theo tien nuoc: Lon -> Be (Giam dan)                              |\n";
        cout << "|  [9]  Theo tong tien hoa don: Be -> Lon (Tang dan)                      |\n";
        cout << "|  [10] Theo tong tien hoa don: Lon -> Be (Giam dan)                      |\n";
        cout << "|  [0]  Quay lai menu Quan ly hoa don                                     |\n";
        cout << "+-------------------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-10]: ";
        if (!(cin >> lc)) { xoaBoDem(); continue; }

        if (lc == 1) {
            qlHoaDon.sapXepTheoNgayLap(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo THOI GIAN LAP CU -> MOI!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 2) {
            qlHoaDon.sapXepTheoNgayLap(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo THOI GIAN LAP MOI -> CU!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 3) {
            qlHoaDon.sapXepTheoTienPhong(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN PHONG TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 4) {
            qlHoaDon.sapXepTheoTienPhong(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN PHONG GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 5) {
            qlHoaDon.sapXepTheoTienDien(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN DIEN TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 6) {
            qlHoaDon.sapXepTheoTienDien(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN DIEN GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 7) {
            qlHoaDon.sapXepTheoTienNuoc(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN NUOC TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 8) {
            qlHoaDon.sapXepTheoTienNuoc(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN NUOC GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 9) {
            qlHoaDon.sapXepTheoTongTien(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TONG TIEN TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (lc == 10) {
            qlHoaDon.sapXepTheoTongTien(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TONG TIEN GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        }
    }
}

// ================================================================
//  MENU FUNCTIONS
// ================================================================
void menuPhongTro(QuanLyPhong& qlPhong, QuanLyHopDong& qlHopDong, QuanLyNguoiThue& qlNguoiThue, QuanLyHoaDon& qlHoaDon) {
    int luaChon = -1;
    while (luaChon != 0) {
        cout << "\n+-------------------------------------------------------------+\n";
        cout << "|                     QUAN LY PHONG TRO                       |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "|  [1]  Them phong tro thuong                                 |\n";
        cout << "|  [2]  Them phong tro VIP                                    |\n";
        cout << "|  [3]  Xoa phong tro theo ma                                 |\n";
        cout << "|  [4]  Tim kiem phong tro theo ma                            |\n";
        cout << "|  [5]  Hien thi tat ca phong tro (Kem nguoi thue)            |\n";
        cout << "|  [6]  In danh sach phong tro CON TRONG                      |\n";
        cout << "|  [7]  In danh sach phong tro DANG THUE                      |\n";
        cout << "|  [8]  Loc phong theo khoang gia thue (x - y trieu dong)     |\n";
        cout << "|  [9]  Tim kiem phong tro CO GAC LUNG                        |\n";
        cout << "|  [10] Tim kiem phong tro co DIEN TICH LON HON x (m2)        |\n";
        cout << "|  [11] Xem so theo doi thanh toan tung thang cua mot phong   |\n";
        cout << "|  [12] Thue phong tro (Tu dong tao Hop dong & Hoa don)       |\n";
        cout << "|  [13] Tra phong tro (Thanh ly hop dong)                     |\n";
        cout << "|  [14] Sap xep danh sach phong tro (Dien tich, Gia thue)     |\n";
        cout << "|  [15] Xoa man hinh console (Clear)                          |\n";
        cout << "|  [0]  Quay lai menu chinh                                   |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-15]: ";
        if (!(cin >> luaChon)) { xoaBoDem(); continue; }

        if (luaChon == 1) {
            cout << "\n--- THEM PHONG TRO THUONG ---\n";
            int soLuong = nhapSoNguyen("-> Nhap so luong phong tro thuong can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac them phong.");
            } else {
                int daThem = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n--- [Nhap phong tro thuong thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }
                    int ma = nhapMaPhongMoi(qlPhong);
                    string ten = nhapChuoi("-> Nhap ten phong: ");
                    int tt = nhapSoNguyen("-> Nhap tinh trang phong (0: Con trong, 1: Da thue): ", 0, 1);
                    string tinhTrang = (tt == 0) ? "Con trong" : "Da thue";
                    double dienTich = nhapSoThuc("-> Nhap dien tich phong (m2, vd: 25 hoac 30.5): ", 0.0);
                    double gia = nhapSoThuc("-> Nhap gia thue goc (> 0 VND): ");
                    int gacInt = nhapSoNguyen("-> Co gac lung khong (1: Co, 0: Khong): ", 0, 1);

                    qlPhong.themPhongTro(new PhongTroThuong(ma, ten, tinhTrang, dienTich, gia, gacInt == 1));
                    daThem++;
                    cout << "[+] Da them phong: " << ten << " (Ma: " << ma << ")\n";
                }
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da them thanh cong " + to_string(daThem) + " phong tro thuong (Da luu vao file)!");
            }
        } else if (luaChon == 2) {
            cout << "\n--- THEM PHONG TRO VIP ---\n";
            int soLuong = nhapSoNguyen("-> Nhap so luong phong tro VIP can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac them phong VIP.");
            } else {
                int daThem = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n--- [Nhap phong tro VIP thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }
                    int ma = nhapMaPhongMoi(qlPhong);
                    string ten = nhapChuoi("-> Nhap ten phong: ");
                    int tt = nhapSoNguyen("-> Nhap tinh trang phong (0: Con trong, 1: Da thue): ", 0, 1);
                    string tinhTrang = (tt == 0) ? "Con trong" : "Da thue";
                    double dienTich = nhapSoThuc("-> Nhap dien tich phong (m2, vd: 40 hoac 45.5): ", 0.0);
                    double gia = nhapSoThuc("-> Nhap gia thue goc (> 0 VND): ");
                    double phiDV = nhapSoThuc("-> Nhap phi dich vu dac biet (>= 0 VND): ", -0.01);

                    qlPhong.themPhongTro(new PhongTroVip(ma, ten, tinhTrang, dienTich, gia, phiDV));
                    daThem++;
                    cout << "[+] Da them phong VIP: " << ten << " (Ma: " << ma << ")\n";
                }
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da them thanh cong " + to_string(daThem) + " phong tro VIP (Da luu vao file)!");
            }
        } else if (luaChon == 3) {
            int ma = nhapSoNguyen("-> Nhap ma phong can xoa (Nhap 0 de huy): ", 0);
            if (ma != 0) {
                PhongTro* pt = qlPhong.timKiemPhongTro(ma);
                if (pt == nullptr) {
                    inThongBaoLoi("Khong tim thay phong ma " + to_string(ma));
                } else if (pt->getTinhTrang() == "Da thue") {
                    inThongBaoLoi("Phong nay dang co nguoi thue! Vui long tra phong truoc khi xoa.");
                } else {
                    qlPhong.xoaPhongTro(ma);
                    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                    inThongBaoThanhCong("Da xoa phong co ma " + to_string(ma) + " (Da cap nhat file)!");
                }
            }
        } else if (luaChon == 4) {
            int ma = nhapSoNguyen("-> Nhap ma phong can tim: ", 1);
            PhongTro* pt = qlPhong.timKiemPhongTro(ma);
            if (pt != nullptr) {
                cout << "\n[KET QUA TIM KIEM PHONG TRO]\n";
                cout << *pt << "\n";
            } else {
                inThongBaoLoi("Khong tim thay phong voi ma: " + to_string(ma));
            }
        } else if (luaChon == 5) {
            cout << "\n=== DANH SACH TAT CA PHONG TRO ===";
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
        } else if (luaChon == 6) {
            LinkedList<PhongTro*> dsTrong = qlPhong.layDanhSachPhongTheoTinhTrang("Con trong");
            cout << "\n=== DANH SACH CAC PHONG TRO CON TRONG ===";
            hienThiBangPhongTro(dsTrong, qlHopDong, qlNguoiThue);
        } else if (luaChon == 7) {
            LinkedList<PhongTro*> dsDaThue = qlPhong.layDanhSachPhongTheoTinhTrang("Da thue");
            cout << "\n=== DANH SACH CAC PHONG TRO DANG DUOC THUE ===";
            hienThiBangPhongTro(dsDaThue, qlHopDong, qlNguoiThue);
        } else if (luaChon == 8) {
            cout << "\n--- LOC PHONG THEO KHOANG GIA THUE ---\n";
            double xTrieu = nhapSoThuc("-> Nhap gia toi thieu (trieu dong, vd: 1.5): ", 0.0);
            double yTrieu = nhapSoThuc("-> Nhap gia toi da (trieu dong, vd: 4.0): ", 0.0);
            if (xTrieu > yTrieu) swap(xTrieu, yTrieu);
            double giaMin = xTrieu * 1000000.0;
            double giaMax = yTrieu * 1000000.0;
            LinkedList<PhongTro*> dsGia = qlPhong.timPhongTheoKhoangGia(giaMin, giaMax);
            cout << "\n=== DANH SACH PHONG CO GIA TU " << xTrieu << " DEN " << yTrieu << " TRIEU DONG ===";
            hienThiBangPhongTro(dsGia, qlHopDong, qlNguoiThue);
        } else if (luaChon == 9) {
            LinkedList<PhongTro*> dsGac = qlPhong.timPhongCoGacLung();
            cout << "\n=== DANH SACH PHONG TRO CO GAC LUNG ===";
            hienThiBangPhongTro(dsGac, qlHopDong, qlNguoiThue);
        } else if (luaChon == 10) {
            cout << "\n--- TIM KIEM PHONG THEO DIEN TICH LON HON X ---\n";
            double xDT = nhapSoThuc("-> Nhap dien tich toi thieu (m2, vd: 25 hoac 30.5): ", 0.0);
            LinkedList<PhongTro*> dsDT = qlPhong.timPhongTheoDienTichLonHon(xDT);
            cout << "\n=== DANH SACH PHONG CO DIEN TICH LON HON " << xDT << " m2 ===";
            hienThiBangPhongTro(dsDT, qlHopDong, qlNguoiThue);
        } else if (luaChon == 11) {
            int ma = nhapSoNguyen("-> Nhap ma phong can xem so theo doi thanh toan: ", 1);
            PhongTro* pt = qlPhong.timKiemPhongTro(ma);
            if (pt == nullptr) {
                inThongBaoLoi("Khong tim thay phong voi ma: " + to_string(ma));
            } else {
                HopDongThue hd = qlHopDong.timKiemTheoPhong(ma);
                if (hd.getMaHopDong() == 0) {
                    inThongBaoLoi("Phong " + to_string(ma) + " (" + pt->getTenPhong() + ") hien tai khong co hop dong thue hoat dong!");
                } else {
                    string tenNT = "Chua xac dinh";
                    string sdtNT = "---";
                    NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                    if (nt != nullptr) {
                        tenNT = nt->getHoTen();
                        sdtNT = nt->getSoDienThoai();
                    }
                    int thangMoc = nhapSoNguyen("-> Nhap thang moc can kiem tra (1 - 12): ", 1, 12);
                    int namMoc = nhapSoNguyen("-> Nhap nam moc can kiem tra (1900 - 2100): ", 1900, 2100);
                    hienThiSoTheoDoiThanhToanPhong(ma, pt->getTenPhong(), tenNT, sdtNT, hd, qlHoaDon, thangMoc, namMoc);
                }
            }
        } else if (luaChon == 12) {
            thuePhongTro(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        } else if (luaChon == 13) {
            traPhongTro(qlPhong, qlHopDong, qlNguoiThue, qlHoaDon);
        } else if (luaChon == 14) {
            menuSapXepPhong(qlPhong, qlHopDong, qlNguoiThue, qlHoaDon);
        } else if (luaChon == 15) {
            xoaManHinh();
        }
    }
}

void menuNguoiThue(QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong, const QuanLyPhong& qlPhong, const QuanLyHoaDon& qlHoaDon) {
    int luaChon = -1;
    while (luaChon != 0) {
        cout << "\n+-------------------------------------------------------------+\n";
        cout << "|                     QUAN LY NGUOI THUE                      |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "|  [1] Them nguoi thue                                        |\n";
        cout << "|  [2] Xoa nguoi thue theo ma                                 |\n";
        cout << "|  [3] Tim kiem khach hang theo ma                            |\n";
        cout << "|  [4] Hien thi tat ca khach hang (Bang chi tiet)             |\n";
        cout << "|  [5] In danh sach khach hang DANG THUE TRO                  |\n";
        cout << "|  [6] In danh sach khach hang CHUA THUE PHONG NAO            |\n";
        cout << "|  [7] In danh sach khach CHUA DONG TIEN trong thang nay      |\n";
        cout << "|  [8] In lich su hop dong cua mot khach hang                 |\n";
        cout << "|  [9] Xoa man hinh console (Clear)                           |\n";
        cout << "|  [0] Quay lai menu chinh                                    |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-9]: ";
        if (!(cin >> luaChon)) { xoaBoDem(); continue; }

        if (luaChon == 1) {
            cout << "\n--- THEM KHACH HANG (NGUOI THUE) ---\n";
            int soLuong = nhapSoNguyen("-> Nhap so luong khach hang can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac them khach hang.");
            } else {
                int daThem = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n--- [Nhap khach hang thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }
                    int ma = nhapMaNguoiThueMoi(qlNguoiThue);
                    string hoTen = nhapChuoi("-> Nhap ho va ten: ");
                    Date ns = nhapNgayThangNam("ngay sinh nguoi thue");
                    string sdt = nhapSoDienThoai("-> Nhap so dien thoai (10 chu so): ");

                    qlNguoiThue.themNguoiThue(new NguoiThue(ma, hoTen, ns, sdt));
                    daThem++;
                    cout << "[+] Da them khach hang: " << hoTen << " (Ma NT: " << ma << ")\n";
                }
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da them thanh cong " + to_string(daThem) + " khach hang (Da luu file)!");
            }
        } else if (luaChon == 2) {
            int ma = nhapSoNguyen("-> Nhap ma nguoi thue can xoa (Nhap 0 de huy): ", 0);
            if (ma != 0) {
                NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(ma);
                if (nt == nullptr) {
                    inThongBaoLoi("Khong tim thay nguoi thue ma " + to_string(ma));
                } else if (qlHopDong.timMaPhongTheoNguoiThue(ma) != 0) {
                    inThongBaoLoi("Nguoi thue nay dang co hop dong thue phong, khong the xoa!");
                } else {
                    qlNguoiThue.xoaNguoiThue(ma);
                    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                    inThongBaoThanhCong("Da xoa nguoi thue ma " + to_string(ma) + " (Da cap nhat file)!");
                }
            }
        } else if (luaChon == 3) {
            int ma = nhapSoNguyen("-> Nhap ma khach hang can tim: ", 1);
            NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(ma);
            if (nt != nullptr) {
                cout << "\n[KET QUA TIM KIEM KHACH HANG]\n";
                cout << *nt << "\n";
            } else {
                inThongBaoLoi("Khong tim thay khach hang voi ma: " + to_string(ma));
            }
        } else if (luaChon == 4) {
            cout << "\n=== DANH SACH TAT CA KHACH HANG ===";
            hienThiBangNguoiThue(qlNguoiThue.layDanhSachNguoiThue(), qlHopDong);
        } else if (luaChon == 5) {
            LinkedList<NguoiThue*> dsDangThue;
            for (NguoiThue* nt : qlNguoiThue.layDanhSachNguoiThue()) {
                if (qlHopDong.timMaPhongTheoNguoiThue(nt->getMaNguoiThue()) != 0) {
                    dsDangThue.push_back(nt);
                }
            }
            cout << "\n=== DANH SACH KHACH HANG DANG THUE TRO ===";
            hienThiBangNguoiThue(dsDangThue, qlHopDong);
        } else if (luaChon == 6) {
            LinkedList<NguoiThue*> dsChuaThue;
            for (NguoiThue* nt : qlNguoiThue.layDanhSachNguoiThue()) {
                if (qlHopDong.timMaPhongTheoNguoiThue(nt->getMaNguoiThue()) == 0) {
                    dsChuaThue.push_back(nt);
                }
            }
            cout << "\n=== DANH SACH KHACH HANG CHUA THUE PHONG NAO ===";
            hienThiBangNguoiThue(dsChuaThue, qlHopDong);
        } else if (luaChon == 7) {
            cout << "\n--- KIEM TRA KHACH HANG CHUA DONG TIEN TRO ---\n";
            int thang = nhapSoNguyen("-> Nhap thang can kiem tra (1 - 12): ", 1, 12);
            int nam = nhapSoNguyen("-> Nhap nam can kiem tra (1900 - 2100): ", 1900, 2100);

            LinkedList<ThongTinChuaDongTien> dsChuaDong;
            for (NguoiThue* nt : qlNguoiThue.layDanhSachNguoiThue()) {
                int maNT = nt->getMaNguoiThue();
                int maPhong = qlHopDong.timMaPhongTheoNguoiThue(maNT);
                if (maPhong != 0) {
                    if (!qlHoaDon.daDongTienThang(maPhong, maNT, thang, nam)) {
                        PhongTro* pt = qlPhong.timKiemPhongTro(maPhong);
                        string tenP = (pt != nullptr) ? pt->getTenPhong() : ("Phong " + to_string(maPhong));
                        double tien = (pt != nullptr) ? pt->tinhGiaThue() : 0.0;
                        dsChuaDong.push_back({maNT, nt->getHoTen(), nt->getSoDienThoai(), maPhong, tenP, tien});
                    }
                }
            }
            cout << "\n=== DANH SACH KHACH HANG CHUA DONG TIEN TRO THANG " << thang << "/" << nam << " ===";
            hienThiBangKhachChuaDongTien(dsChuaDong, thang, nam);
        } else if (luaChon == 8) {
            int maNT = nhapSoNguyen("-> Nhap ma khach hang can xem lich su hop dong: ", 1);
            NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(maNT);
            if (nt == nullptr) {
                inThongBaoLoi("Khong tim thay khach hang ma: " + to_string(maNT));
            } else {
                LinkedList<HopDongThue> dsLichSu = qlHopDong.layLichSuHopDongTheoNguoiThue(maNT);
                cout << "\n=== LICH SU HOP DONG CUA KHACH HANG: " << nt->getHoTen() << " (MA NT: " << maNT << ") ===";
                hienThiBangHopDong(dsLichSu, qlNguoiThue);
            }
        } else if (luaChon == 9) {
            xoaManHinh();
        }
    }
}

void menuNguoiThue(QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong) {
    QuanLyPhong dummyP;
    QuanLyHoaDon dummyHD;
    menuNguoiThue(qlNguoiThue, qlHopDong, dummyP, dummyHD);
}

void menuNguoiThue(QuanLyNguoiThue& qlNguoiThue) {
    QuanLyHopDong dummyHD;
    QuanLyPhong dummyP;
    QuanLyHoaDon dummyHD2;
    menuNguoiThue(qlNguoiThue, dummyHD, dummyP, dummyHD2);
}

void menuHopDong(QuanLyHopDong& qlHopDong, QuanLyPhong& qlPhong, QuanLyNguoiThue& qlNguoiThue, QuanLyHoaDon& qlHoaDon) {
    int luaChon = -1;
    while (luaChon != 0) {
        cout << "\n+-------------------------------------------------------------+\n";
        cout << "|                   QUAN LY HOP DONG THUE                     |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "|  [1] Lap hop dong thue phong (Tu dong lien ket phong & BL)  |\n";
        cout << "|  [2] Xoa hop dong theo ma                                   |\n";
        cout << "|  [3] Cap nhat thoi han va gia thue                          |\n";
        cout << "|  [4] Tim kiem hop dong theo ma                              |\n";
        cout << "|  [5] Hien thi danh sach hop dong (Kem ten nguoi thue & phong|\n";
        cout << "|  [6] Sap xep hop dong thue (Thoi gian lap, Gia thue)        |\n";
        cout << "|  [7] Xoa man hinh console (Clear)                           |\n";
        cout << "|  [0] Quay lai menu chinh                                    |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-7]: ";
        if (!(cin >> luaChon)) { xoaBoDem(); continue; }

        if (luaChon == 1) {
            thuePhongTro(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        } else if (luaChon == 2) {
            int ma = nhapSoNguyen("-> Nhap ma hop dong can xoa (Nhap 0 de huy): ", 0);
            if (ma != 0) {
                HopDongThue hd = qlHopDong.timKiemHopDong(ma);
                if (hd.getMaHopDong() == 0) {
                    inThongBaoLoi("Khong tim thay hop dong ma: " + to_string(ma));
                } else {
                    qlHopDong.xoaHopDong(ma);
                    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                    inThongBaoThanhCong("Da xoa hop dong ma " + to_string(ma) + " (Da cap nhat file)!");
                }
            }
        } else if (luaChon == 3) {
            int ma = nhapSoNguyen("-> Nhap ma hop dong can cap nhat: ", 1);
            HopDongThue hd = qlHopDong.timKiemHopDong(ma);
            if (hd.getMaHopDong() == 0) {
                inThongBaoLoi("Khong tim thay hop dong ma: " + to_string(ma));
            } else {
                int thoiHanMoi = nhapSoNguyen("-> Nhap thoi han moi (1 - 120 thang): ", 1, 120);
                double giaMoi = nhapSoThuc("-> Nhap gia thue moi (> 0 VND): ");
                hd.setThoiHan(thoiHanMoi);
                hd.setGiaThue(giaMoi);
                qlHopDong.capNhatThongTin(hd);
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Cap nhat hop dong thanh cong (Da luu file)!");
            }
        } else if (luaChon == 4) {
            int ma = nhapSoNguyen("-> Nhap ma hop dong can tim: ", 1);
            HopDongThue hd = qlHopDong.timKiemHopDong(ma);
            if (hd.getMaHopDong() != 0) {
                cout << "\n[KET QUA TIM KIEM]\n";
                cout << hd << "\n";
            } else {
                inThongBaoLoi("Khong tim thay hop dong ma: " + to_string(ma));
            }
        } else if (luaChon == 5) {
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
        } else if (luaChon == 6) {
            menuSapXepHopDong(qlHopDong, qlPhong, qlNguoiThue, qlHoaDon);
        } else if (luaChon == 7) {
            xoaManHinh();
        }
    }
}

void menuHoaDon(QuanLyHoaDon& qlHoaDon, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong) {
    int luaChon = -1;
    while (luaChon != 0) {
        cout << "\n+-------------------------------------------------------------------------+\n";
        cout << "|                          QUAN LY HOA DON                                |\n";
        cout << "+-------------------------------------------------------------------------+\n";
        cout << "|  [1]  Them hoa don (Ky thanh toan & chi tiet phong, dien, nuoc)         |\n";
        cout << "|  [2]  Xoa hoa don theo ma                                               |\n";
        cout << "|  [3]  Cap nhat tien phong, dien, nuoc cua hoa don                       |\n";
        cout << "|  [4]  Tim kiem hoa don theo ma                                          |\n";
        cout << "|  [5]  Hien thi tat ca hoa don (Bang chi tiet kem Ky TT)                 |\n";
        cout << "|  [6]  So theo doi thanh toan tung thang cua phong (Da tra / Con no)     |\n";
        cout << "|  [7]  Tong hop tinh trang dong tien tat ca cac phong trong thang        |\n";
        cout << "|  [8]  In danh sach phong co tien dien cao hon x dong                    |\n";
        cout << "|  [9]  Thong ke tong doanh thu tien phong, dien, nuoc thang              |\n";
        cout << "|  [10] Sap xep hoa don (Ngay lap, Tien phong, Dien, Nuoc, Tong tien)     |\n";
        cout << "|  [11] Xoa man hinh console (Clear)                                      |\n";
        cout << "|  [0]  Quay lai menu chinh                                               |\n";
        cout << "+-------------------------------------------------------------------------+\n";
        cout << ">> Nhap lua chon cua ban [0-11]: ";
        if (!(cin >> luaChon)) { xoaBoDem(); continue; }

        if (luaChon == 1) {
            cout << "\n--- THEM HOA DON ---\n";
            int soLuong = nhapSoNguyen("-> Nhap so luong hoa don can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac lap hoa don.");
            } else {
                int daLap = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n--- [Lap hoa don thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }

                    // Nhap ma hoa don moi khong trung
                    string ma;
                    bool boQua = false;
                    while (true) {
                        try {
                            ma = nhapChuoi("-> Nhap ma hoa don (vd: HD03, nhap 0 de bo qua): ");
                            if (ma == "0") {
                                boQua = true;
                                break;
                            }
                            if (qlHoaDon.timKiemHoaDon(ma).getMaHoaDon() != "") {
                                throw LoiThucThi("Ma hoa don " + ma + " da ton tai trong he thong!");
                            }
                            break;
                        } catch (const NgoaiLe& e) {
                            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
                        }
                    }
                    if (boQua) {
                        cout << "[!] Da bo qua hoa don nay.\n";
                        if (i + 1 < soLuong) {
                            int tiep = nhapSoNguyen("    Ban co muon tiep tuc lap hoa don tiep theo? (1: Co, 0: Dung): ", 0, 1);
                            if (tiep == 0) break;
                        }
                        continue;
                    }

                    // Nhap ma phong co ton tai va da co hop dong thue
                    int maPhong = 0;
                    PhongTro* pt = nullptr;
                    while (true) {
                        try {
                            maPhong = nhapSoNguyen("-> Nhap ma phong thue (Nhap 0 de bo qua): ", 0);
                            if (maPhong == 0) {
                                boQua = true;
                                break;
                            }
                            pt = qlPhong.timKiemPhongTro(maPhong);
                            if (pt == nullptr) {
                                throw LoiThucThi("Loi rang buoc: Ma phong " + to_string(maPhong) + " khong ton tai!");
                            }
                            if (qlHopDong.layDanhSachHopDongTheoPhong(maPhong).empty()) {
                                throw LoiThucThi("Phong " + to_string(maPhong) + " hien chua co bat ky hop dong thue nao trong he thong! Vui long lap hop dong truoc khi xuat hoa don.");
                            }
                            break;
                        } catch (const NgoaiLe& e) {
                            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
                        }
                    }
                    if (boQua) {
                        cout << "[!] Da bo qua hoa don nay.\n";
                        if (i + 1 < soLuong) {
                            int tiep = nhapSoNguyen("    Ban co muon tiep tuc lap hoa don tiep theo? (1: Co, 0: Dung): ", 0, 1);
                            if (tiep == 0) break;
                        }
                        continue;
                    }

                    // Nhap ngay lap hoa don va tu dong xac dinh ky thanh toan, nguoi thue theo hop dong
                    Date ngayLap;
                    int thangTT = 1, namTT = 2026;
                    HopDongThue hdHieuLuc;
                    NguoiThue* nt = nullptr;
                    int maNT = 0;

                    while (true) {
                        try {
                            ngayLap = nhapNgayThangNam("ngay lap hoa don");
                            thangTT = ngayLap.getThang();
                            namTT = ngayLap.getNam();
                            cout << "-> Ky thanh toan (dong nhat theo thang/nam cua ngay lap): Thang "
                                 << (thangTT < 10 ? "0" : "") << thangTT << "/" << namTT << "\n";

                            // Kiem tra phong co hop dong thue co hieu luc trong ky nay khong
                            hdHieuLuc = qlHopDong.timHopDongTheoPhongVaKy(maPhong, thangTT, namTT);
                            if (hdHieuLuc.getMaHopDong() == 0) {
                                cout << "[!] Phong " << maPhong << " khong co hop dong nao co hieu luc trong thang "
                                     << thangTT << "/" << namTT << "!\n";
                                cout << "    Lich su cac hop dong cua phong " << maPhong << ":\n";
                                for (const auto& h : qlHopDong.layDanhSachHopDongTheoPhong(maPhong)) {
                                    cout << "    + Ma HD " << h.getMaHopDong() << " (Ma NT: " << h.getMaNguoiThue()
                                         << "): Tu " << h.getNgayLap().toString() << " den " << h.getNgayKetThuc().toString() << "\n";
                                }
                                throw LoiThucThi("Ngay lap hoa don (" + ngayLap.toString() + ") co ky thanh toan nam ngoai thoi han hop dong!");
                            }

                            maNT = hdHieuLuc.getMaNguoiThue();
                            nt = qlNguoiThue.timKiemNguoiThue(maNT);
                            if (nt != nullptr && ngayLap <= nt->getNgaySinh()) {
                                throw LoiDoiSo("Ngay lap hoa don (" + ngayLap.toString() + 
                                               ") khong the xay ra truoc hoac cung ngay sinh cua nguoi thue (" + 
                                               nt->getNgaySinh().toString() + ")!");
                            }
                            break;
                        } catch (const NgoaiLe& e) {
                            inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
                        }
                    }

                    string tenNT = (nt != nullptr) ? nt->getHoTen() : ("Khach hang ma " + to_string(maNT));
                    cout << "-> Xac dinh nguoi thue theo hop dong (Ma HD: " << hdHieuLuc.getMaHopDong() << "): "
                         << tenNT << " (Ma NT: " << maNT << ")\n";

                    if (qlHoaDon.daDongTienThang(maPhong, maNT, thangTT, namTT)) {
                        cout << "\n[!] CANH BAO: Phong " << maPhong << " da co hoa don thanh toan cho ky thang " 
                             << (thangTT < 10 ? "0" : "") << thangTT << "/" << namTT << " roi!\n";
                        int xacNhan = nhapSoNguyen("    Ban co muon tiep tuc lap them hoa don cho ky nay khong? (1: Co, 0: Bo qua): ", 0, 1);
                        if (xacNhan == 0) {
                            cout << "[!] Da bo qua hoa don nay.\n";
                            if (i + 1 < soLuong) {
                                int tiep = nhapSoNguyen("    Ban co muon tiep tuc lap hoa don tiep theo? (1: Co, 0: Dung): ", 0, 1);
                                if (tiep == 0) break;
                            }
                            continue;
                        }
                    }

                    double tienPhongGoiY = hdHieuLuc.getGiaThue();
                    cout << "-> Tien phong theo hop dong: " << (long long)tienPhongGoiY << " VND\n";
                    double tienPhong = nhapSoThuc("-> Nhap tien phong (> 0 VND): ");
                    double tienDien = nhapSoThuc("-> Nhap tien dien (>= 0 VND): ", -0.01);
                    double tienNuoc = nhapSoThuc("-> Nhap tien nuoc (>= 0 VND): ", -0.01);

                    qlHoaDon.themHoaDon(HoaDon(ma, maPhong, maNT, ngayLap, thangTT, namTT, tienPhong, tienDien, tienNuoc));
                    daLap++;
                    string kyStr = (thangTT < 10 ? "0" : "") + to_string(thangTT) + "/" + to_string(namTT);
                    cout << "[+] Da lap hoa don " << ma << " (Ky " << kyStr << ") | Tong: " 
                         << (long long)(tienPhong + tienDien + tienNuoc) << " VND\n";
                }
                if (daLap > 0) {
                    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                    inThongBaoThanhCong("Da lap thanh cong " + to_string(daLap) + " hoa don (Da luu vao file)!");
                }
            }
        } else if (luaChon == 2) {
            string ma = nhapChuoi("-> Nhap ma hoa don can xoa: ");
            HoaDon hd = qlHoaDon.timKiemHoaDon(ma);
            if (hd.getMaHoaDon() == "") {
                inThongBaoLoi("Khong tim thay hoa don ma: " + ma);
            } else {
                qlHoaDon.xoaHoaDon(ma);
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da xoa hoa don ma " + ma + " (Da cap nhat file)!");
            }
        } else if (luaChon == 3) {
            cout << "\n--- CAP NHAT TIEN PHONG, DIEN, NUOC CUA HOA DON ---\n";
            string ma = nhapChuoi("-> Nhap ma hoa don can cap nhat (Nhap 0 de huy): ");
            if (ma != "0") {
                HoaDon hd = qlHoaDon.timKiemHoaDon(ma);
                if (hd.getMaHoaDon() == "") {
                    inThongBaoLoi("Khong tim thay hoa don voi ma: " + ma);
                } else {
                    NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                    string tenNT = (nt != nullptr) ? nt->getHoTen() : ("Ma NT: " + to_string(hd.getMaNguoiThue()));

                    cout << "\n+-------------------------------------------------------------+\n";
                    cout << "|                 THONG TIN HOA DON HIEN TAI                  |\n";
                    cout << "+-------------------------------------------------------------+\n";
                    cout << "  + Ma hoa don     : " << hd.getMaHoaDon() << "\n";
                    cout << "  + Ma phong       : " << hd.getMaPhong() << "\n";
                    cout << "  + Nguoi thue     : " << tenNT << " (Ma NT: " << hd.getMaNguoiThue() << ")\n";
                    cout << "  + Ky thanh toan  : " << hd.getKyThanhToan() << "\n";
                    cout << "  + Ngay lap       : " << hd.getNgayLap().toString() << "\n";
                    cout << "  + Tien phong     : " << (long long)hd.getTienPhong() << " VND\n";
                    cout << "  + Tien dien      : " << (long long)hd.getTienDien() << " VND\n";
                    cout << "  + Tien nuoc      : " << (long long)hd.getTienNuoc() << " VND\n";
                    cout << "  + Tong thanh toan: " << (long long)hd.getTongTien() << " VND\n";
                    cout << "+-------------------------------------------------------------+\n";

                    cout << "\nChon muc ban muon cap nhat:\n";
                    cout << "  [1] Cap nhat tat ca (Tien phong, Tien dien, Tien nuoc)\n";
                    cout << "  [2] Chi cap nhat Tien phong\n";
                    cout << "  [3] Chi cap nhat Tien dien\n";
                    cout << "  [4] Chi cap nhat Tien nuoc\n";
                    cout << "  [0] Giu nguyen / Huy thao tac\n";
                    int chonMuc = nhapSoNguyen(">> Nhap lua chon cua ban [0-4]: ", 0, 4);

                    if (chonMuc == 0) {
                        inThongBaoLoi("Da huy thao tac cap nhat hoa don.");
                    } else {
                        double phongMoi = hd.getTienPhong();
                        double dienMoi = hd.getTienDien();
                        double nuocMoi = hd.getTienNuoc();

                        if (chonMuc == 1) {
                            phongMoi = nhapSoThuc("-> Nhap tien phong moi (> 0 VND, hien tai: " + to_string((long long)hd.getTienPhong()) + "): ");
                            dienMoi = nhapSoThuc("-> Nhap tien dien moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienDien()) + "): ", -0.01);
                            nuocMoi = nhapSoThuc("-> Nhap tien nuoc moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienNuoc()) + "): ", -0.01);
                        } else if (chonMuc == 2) {
                            phongMoi = nhapSoThuc("-> Nhap tien phong moi (> 0 VND, hien tai: " + to_string((long long)hd.getTienPhong()) + "): ");
                        } else if (chonMuc == 3) {
                            dienMoi = nhapSoThuc("-> Nhap tien dien moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienDien()) + "): ", -0.01);
                        } else if (chonMuc == 4) {
                            nuocMoi = nhapSoThuc("-> Nhap tien nuoc moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienNuoc()) + "): ", -0.01);
                        }

                        hd.setChiTiet(phongMoi, dienMoi, nuocMoi);
                        qlHoaDon.capNhatHoaDon(hd);
                        luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                        inThongBaoThanhCong("Da cap nhat hoa don " + ma + " thanh cong (Da luu vao file)! Tong tien moi: " + to_string((long long)hd.getTongTien()) + " VND");
                    }
                }
            }
        } else if (luaChon == 4) {
            string ma = nhapChuoi("-> Nhap ma hoa don can tim: ");
            HoaDon hd = qlHoaDon.timKiemHoaDon(ma);
            if (hd.getMaHoaDon() != "") {
                cout << "\n[KET QUA TIM KIEM HOA DON]\n";
                cout << hd << "\n";
            } else {
                inThongBaoLoi("Khong tim thay hoa don ma: " + ma);
            }
        } else if (luaChon == 5) {
            cout << "\n=== DANH SACH TAT CA HOA DON THANH TOAN ===";
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
        } else if (luaChon == 6) {
            cout << "\n--- TRA CUU SO THEO DOI THANH TOAN TUNG THANG CUA PHONG ---\n";
            int ma = nhapSoNguyen("-> Nhap ma phong can xem (Nhap 0 de huy): ", 0);
            if (ma != 0) {
                PhongTro* pt = qlPhong.timKiemPhongTro(ma);
                if (pt == nullptr) {
                    inThongBaoLoi("Khong tim thay phong voi ma: " + to_string(ma));
                } else {
                    HopDongThue hd = qlHopDong.timKiemTheoPhong(ma);
                    if (hd.getMaHopDong() == 0) {
                        inThongBaoLoi("Phong " + to_string(ma) + " (" + pt->getTenPhong() + ") hien tai khong co hop dong thue hoat dong!");
                    } else {
                        string tenNT = "Chua xac dinh";
                        string sdtNT = "---";
                        NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                        if (nt != nullptr) {
                            tenNT = nt->getHoTen();
                            sdtNT = nt->getSoDienThoai();
                        }
                        int thangMoc = nhapSoNguyen("-> Nhap thang moc can tra cuu (1 - 12): ", 1, 12);
                        int namMoc = nhapSoNguyen("-> Nhap nam moc can tra cuu (1900 - 2100): ", 1900, 2100);
                        hienThiSoTheoDoiThanhToanPhong(ma, pt->getTenPhong(), tenNT, sdtNT, hd, qlHoaDon, thangMoc, namMoc);
                    }
                }
            }
        } else if (luaChon == 7) {
            cout << "\n--- TONG HOP TINH TRANG DONG TIEN TAT CA PHONG TRONG THANG ---\n";
            int thang = nhapSoNguyen("-> Nhap thang can kiem tra (1 - 12): ", 1, 12);
            int nam = nhapSoNguyen("-> Nhap nam can kiem tra (1900 - 2100): ", 1900, 2100);

            LinkedList<ThongTinTinhTrangPhongThang> dsTinhTrang;
            for (PhongTro* pt : qlPhong.layDanhSachPhong()) {
                if (pt->getTinhTrang() == "Da thue") {
                    HopDongThue hd = qlHopDong.timKiemTheoPhong(pt->getMaPhong());
                    int maNT = (hd.getMaHopDong() != 0) ? hd.getMaNguoiThue() : 0;
                    string tenNT = "Chua xac dinh";
                    string sdtNT = "---";
                    if (maNT != 0) {
                        NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(maNT);
                        if (nt != nullptr) {
                            tenNT = nt->getHoTen();
                            sdtNT = nt->getSoDienThoai();
                        }
                    }

                    HoaDon bill = qlHoaDon.timHoaDonTheoKy(pt->getMaPhong(), thang, nam);
                    if (bill.getMaHoaDon() != "") {
                        dsTinhTrang.push_back({pt->getMaPhong(), pt->getTenPhong(), maNT, tenNT, sdtNT, true, bill.getMaHoaDon(), bill.getNgayLap(), bill.getTongTien()});
                    } else {
                        double giaPhong = (hd.getMaHopDong() != 0) ? hd.getGiaThue() : pt->tinhGiaThue();
                        dsTinhTrang.push_back({pt->getMaPhong(), pt->getTenPhong(), maNT, tenNT, sdtNT, false, "---", Date(), giaPhong});
                    }
                }
            }
            hienThiBangTinhTrangThanhToanCacPhong(dsTinhTrang, thang, nam);
        } else if (luaChon == 8) {
            cout << "\n--- TRA CUU PHONG CO TIEN DIEN CAO ---\n";
            int thang = nhapSoNguyen("-> Nhap thang can kiem tra (Nhap 0 de xem tat ca cac thang): ", 0, 12);
            int nam = 0;
            if (thang != 0) {
                nam = nhapSoNguyen("-> Nhap nam (1900 - 2100): ", 1900, 2100);
            }
            double mucTien = nhapSoThuc("-> Nhap muc tien dien toi thieu (VND, vd: 200000): ", 0.0);

            LinkedList<HoaDon> dsTienDienCao = qlHoaDon.timHoaDonTienDienCaoHon(mucTien, thang, nam);
            if (thang != 0) {
                cout << "\n=== DANH SACH PHONG CO TIEN DIEN THANG " << thang << "/" << nam << " CAO HON " << (long long)mucTien << " VND ===";
            } else {
                cout << "\n=== DANH SACH PHONG CO TIEN DIEN CAO HON " << (long long)mucTien << " VND ===";
            }
            hienThiBangTienDienCao(dsTienDienCao, qlPhong, qlNguoiThue, mucTien);
        } else if (luaChon == 9) {
            cout << "\n--- THONG KE TONG DOANH THU THEO THANG ---\n";
            int thang = nhapSoNguyen("-> Nhap thang can thong ke (1 - 12): ", 1, 12);
            int nam = nhapSoNguyen("-> Nhap nam can thong ke (1900 - 2100): ", 1900, 2100);

            double tongPhong = qlHoaDon.tinhTongTienPhong(thang, nam);
            double tongDien = qlHoaDon.tinhTongTienDien(thang, nam);
            double tongNuoc = qlHoaDon.tinhTongTienNuoc(thang, nam);
            double tongCong = qlHoaDon.tinhTongDoanhThuThang(thang, nam);

            LinkedList<HoaDon> dsThang = qlHoaDon.layHoaDonTheoThang(thang, nam);
            cout << "\n=== CHI TIET CAC HOA DON TRONG THANG " << thang << "/" << nam << " ===";
            hienThiBangHoaDon(dsThang, tongCong, qlNguoiThue);
            hienThiThongKeDoanhThuThang(thang, nam, tongPhong, tongDien, tongNuoc, tongCong);
        } else if (luaChon == 10) {
            menuSapXepHoaDon(qlHoaDon, qlPhong, qlNguoiThue, qlHopDong);
        } else if (luaChon == 11) {
            xoaManHinh();
        }
    }
}

void menuHoaDon(QuanLyHoaDon& qlHoaDon, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue) {
    QuanLyHopDong dummyHD;
    menuHoaDon(qlHoaDon, qlPhong, qlNguoiThue, dummyHD);
}
