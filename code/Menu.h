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
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << prompt;
            khoiPhucMau();
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
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << prompt;
            khoiPhucMau();
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
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << prompt;
            khoiPhucMau();
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
string nhapSoDienThoai(const string& prompt = "➔ Nhap so dien thoai (10 chu so): ") {
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
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "➔ Nhap " << moTa << " (ngay thang nam, vd: 15 5 2002): ";
            khoiPhucMau();
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
            int ma = nhapSoNguyen("➔ Nhap ma phong: ", 1);
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
            int ma = nhapSoNguyen("➔ Nhap ma nguoi thue: ", 1);
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
    xoaManHinh();
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ╔═══════════════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║ ";
    datMau(MAU_VANG_SANG, 0);
    cout << "                 NGHIỆP VỤ THUÊ PHÒNG (TỰ ĐỘNG LIÊN KẾT)                   ";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "║\n";
    cout << "  ╚═══════════════════════════════════════════════════════════════════════════╝\n\n";
    khoiPhucMau();

    int soLuong = nhapSoNguyen("➔ Nhap so luong phong/hop dong muon thue (Nhap 0 de huy): ", 0);
    if (soLuong <= 0) {
        inThongBaoLoi("Da huy thao tac thue phong.");
        dungManHinh();
        return;
    }

    int daThue = 0;
    for (int k = 0; k < soLuong; ++k) {
        if (soLuong > 1) {
            cout << "\n";
            datMau(MAU_VANG_SANG, 0);
            cout << "  ─── [THUÊ PHÒNG / LẬP HỢP ĐỒNG THỨ " << (k + 1) << "/" << soLuong << "] ───\n";
            khoiPhucMau();
        }

        // 1. Chon phong can thue
        PhongTro* pt = nullptr;
        int maPhong = 0;
        bool boQua = false;
        while (pt == nullptr) {
            try {
                maPhong = nhapSoNguyen("➔ Nhap ma phong can thue (Nhap 0 de bo qua): ", 0);
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
                    datMau(MAU_VANG_SANG, 0);
                    cout << "  [i] Phong " << maPhong << " (" << pt->getTenPhong() << ") hien da co " << dsHDCu.size() << " hop dong thue:\n";
                    for (const auto& h : dsHDCu) {
                        NguoiThue* ntCu = qlNguoiThue.timKiemNguoiThue(h.getMaNguoiThue());
                        string tenCu = (ntCu != nullptr) ? ntCu->getHoTen() : ("Ma NT: " + to_string(h.getMaNguoiThue()));
                        cout << "      + Ma HD " << h.getMaHopDong() << ": Tu " << h.getNgayLap().toString()
                             << " den " << h.getNgayKetThuc().toString() << " | Nguoi thue: " << tenCu << "\n";
                    }
                    cout << "      ➔ Chu y: Ban can chon khoang thoi gian thue KHONG TRUNG LAP voi cac hop dong tren!\n";
                    khoiPhucMau();
                }
            } catch (const NgoaiLe& e) {
                inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
            }
        }

        if (boQua) {
            inHopThongBaoThongTin("Da bo qua luot thue phong nay.");
            if (k + 1 < soLuong) {
                int tiep = nhapSoNguyen("    Ban co muon tiep tuc luot thue tiep theo? (1: Co, 0: Dung): ", 0, 1);
                if (tiep == 0) break;
            }
            continue;
        }

        datMau(MAU_XANH_LA_SANG, 0);
        cout << "  ➔ Tim thay: " << pt->getTenPhong() << " | Gia goc: " << dinhDangTien((long long)pt->getGiaThue())
             << " VND | Tong gia: " << dinhDangTien((long long)pt->tinhGiaThue()) << " VND\n";
        khoiPhucMau();

        // 2. Chon hoac tao nguoi thue
        cout << "\n  [Thong tin nguoi thue]:\n";
        cout << "    [1] Chon nguoi thue da co trong danh sach\n";
        cout << "    [2] Them nguoi thue moi hoan toan vao he thong\n";
        cout << "    [0] Bo qua luot thue phong nay\n";
        int chonNT = nhapSoNguyen("➔ Nhap lua chon [0-2]: ", 0, 2);

        if (chonNT == 0) {
            inHopThongBaoThongTin("Da bo qua luot thue phong nay.");
            if (k + 1 < soLuong) {
                int tiep = nhapSoNguyen("    Ban co muon tiep tuc luot thue tiep theo? (1: Co, 0: Dung): ", 0, 1);
                if (tiep == 0) break;
            }
            continue;
        }

        int maNT = 0;
        NguoiThue* nt = nullptr;

        if (chonNT == 1) {
            while (nt == nullptr) {
                try {
                    maNT = nhapSoNguyen("➔ Nhap ma nguoi thue da co (Nhap 0 de bo qua): ", 0);
                    if (maNT == 0) {
                        boQua = true;
                        break;
                    }
                    nt = qlNguoiThue.timKiemNguoiThue(maNT);
                    if (nt == nullptr) {
                        throw LoiThucThi("Khong tim thay nguoi thue voi ma: " + to_string(maNT));
                    }
                } catch (const NgoaiLe& e) {
                    inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
                }
            }
        } else {
            cout << "\n  --- NHAP THONG TIN NGUOI THUE MOI ---\n";
            maNT = nhapMaNguoiThueMoi(qlNguoiThue);
            string hoTen = nhapChuoi("➔ Nhap ho va ten: ");
            Date ns = nhapNgayThangNam("ngay sinh nguoi thue");
            string sdt = nhapSoDienThoai("➔ Nhap so dien thoai (10 chu so): ");

            nt = new NguoiThue(maNT, hoTen, ns, sdt);
            qlNguoiThue.themNguoiThue(nt);
            cout << "  [+] Da them nguoi thue: " << hoTen << " (Ma: " << maNT << ")\n";
        }

        if (boQua || nt == nullptr) {
            inHopThongBaoThongTin("Da bo qua luot thue phong nay.");
            if (k + 1 < soLuong) {
                int tiep = nhapSoNguyen("    Ban co muon tiep tuc luot thue tiep theo? (1: Co, 0: Dung): ", 0, 1);
                if (tiep == 0) break;
            }
            continue;
        }

        // 3. Lap hop dong thue
        cout << "\n  --- THONG TIN HOP DONG THUE PHONG ---\n";
        int maHD = 0;
        while (true) {
            try {
                maHD = nhapSoNguyen("➔ Nhap ma hop dong moi (Nhap 0 de bo qua): ", 0);
                if (maHD == 0) {
                    boQua = true;
                    break;
                }
                if (qlHopDong.timKiemHopDong(maHD).getMaHopDong() != 0) {
                    throw LoiThucThi("Ma hop dong " + to_string(maHD) + " da ton tai trong he thong!");
                }
                break;
            } catch (const NgoaiLe& e) {
                inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
            }
        }

        if (boQua) {
            inHopThongBaoThongTin("Da bo qua luot thue phong nay.");
            if (k + 1 < soLuong) {
                int tiep = nhapSoNguyen("    Ban co muon tiep tuc luot thue tiep theo? (1: Co, 0: Dung): ", 0, 1);
                if (tiep == 0) break;
            }
            continue;
        }

        Date ngayLapHD;
        int thoiHan = 0;
        while (true) {
            try {
                ngayLapHD = nhapNgayThangNam("ngay bat dau hop dong");
                if (ngayLapHD <= nt->getNgaySinh()) {
                    throw LoiDoiSo("Ngay bat dau hop dong (" + ngayLapHD.toString() + 
                                   ") khong the xay ra truoc hoac cung ngay sinh cua nguoi thue (" + 
                                   nt->getNgaySinh().toString() + ")!");
                }
                thoiHan = nhapSoNguyen("➔ Nhap thoi han thue (1 - 120 thang): ", 1, 120);

                const HopDongThue* biTrung = qlHopDong.timHopDongBiTrung(maPhong, ngayLapHD, thoiHan);
                if (biTrung != nullptr) {
                    Date ktMoi = ngayLapHD.congThang(thoiHan);
                    NguoiThue* ntTrung = qlNguoiThue.timKiemNguoiThue(biTrung->getMaNguoiThue());
                    string tenTrung = (ntTrung != nullptr) ? ntTrung->getHoTen() : ("Ma NT " + to_string(biTrung->getMaNguoiThue()));
                    throw LoiThucThi("Khoang thoi gian thue tu " + ngayLapHD.toString() + " den " + ktMoi.toString() + 
                                     " bi TRUNG LAP voi hop dong " + to_string(biTrung->getMaHopDong()) + " cua " + tenTrung + 
                                     " (Tu " + biTrung->getNgayLap().toString() + " den " + biTrung->getNgayKetThuc().toString() + ")!");
                }
                break;
            } catch (const NgoaiLe& e) {
                inThongBaoLoi(string("Loi: ") + e.what() + " Vui long nhap lai!");
            }
        }

        double giaThueHD = pt->tinhGiaThue();
        cout << "  ➔ Gia thue tong cong theo phong: " << dinhDangTien((long long)giaThueHD) << " VND/thang\n";
        int doiGia = nhapSoNguyen("    Ban co muon tuy chinh gia thue tren hop dong khong? (1: Co, 0: Mac dinh): ", 0, 1);
        if (doiGia == 1) {
            giaThueHD = nhapSoThuc("➔ Nhap gia thue hop dong moi (> 0 VND): ");
        }

        // Tao hop dong va cap nhat trang thai phong
        qlHopDong.themHopDong(HopDongThue(maHD, maPhong, maNT, ngayLapHD, thoiHan, giaThueHD));
        pt->setTinhTrang("Da thue");
        daThue++;

        datMau(MAU_XANH_LA_SANG, 0);
        cout << "\n  ✔ [HOAN TAT] Da lien ket: Phong " << pt->getTenPhong() << " (Ma " << maPhong << ")"
             << " <-> Nguoi thue: " << nt->getHoTen() << " (Ma " << maNT << ") qua Hop dong " << maHD << "!\n";
        khoiPhucMau();
    }

    if (daThue > 0) {
        luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        inThongBaoThanhCong("Da hoan tat thue " + to_string(daThue) + " phong va tu dong luu vao file!");
    } else {
        inThongBaoLoi("Khong co hop dong thue phong nao duoc tao.");
    }
    dungManHinh();
}

void traPhongTro(QuanLyPhong& qlPhong, QuanLyHopDong& qlHopDong, QuanLyNguoiThue& qlNguoiThue, const QuanLyHoaDon& qlHoaDon) {
    xoaManHinh();
    cout << "\n";
    datMau(MAU_DO_SANG, 0);
    cout << "  ╔═══════════════════════════════════════════════════════════════════════════╗\n";
    cout << "  ║ ";
    datMau(MAU_VANG_SANG, 0);
    cout << "                  NGHIỆP VỤ TRẢ PHÒNG / THANH LÝ HỢP ĐỒNG                  ";
    datMau(MAU_DO_SANG, 0);
    cout << "║\n";
    cout << "  ╚═══════════════════════════════════════════════════════════════════════════╝\n\n";
    khoiPhucMau();

    PhongTro* pt = nullptr;
    int maPhong = 0;
    while (pt == nullptr) {
        try {
            maPhong = nhapSoNguyen("➔ Nhap ma phong can tra (Nhap 0 de huy): ", 0);
            if (maPhong == 0) {
                inThongBaoLoi("Da huy thao tac tra phong.");
                dungManHinh();
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

    datMau(MAU_VANG_SANG, 0);
    cout << "\n  ➔ Xac nhan tra phong: " << pt->getTenPhong()
         << " | Nguoi dang thue: " << tenNT << " (Ma NT: " << maNT << ")\n";
    khoiPhucMau();

    int xacNhan = nhapSoNguyen("➔ Ban co chac chan muon tra phong va thanh ly hop dong? (1: Dong y, 0: Huy): ", 0, 1);
    if (xacNhan == 1) {
        pt->setTinhTrang("Con trong");
        qlHopDong.xoaHopDongTheoPhong(maPhong);
        luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        inThongBaoThanhCong("Da tra phong " + to_string(maPhong) + " va thanh ly hop dong thanh cong (Da luu file)!");
    } else {
        inThongBaoLoi("Da huy thao tac tra phong.");
    }
    dungManHinh();
}

void traPhongTro(QuanLyPhong& qlPhong, QuanLyHopDong& qlHopDong, QuanLyNguoiThue& qlNguoiThue) {
    QuanLyHoaDon dummyHD;
    traPhongTro(qlPhong, qlHopDong, qlNguoiThue, dummyHD);
}

// ================================================================
//  CAC MENU CON SAP XEP (THUAT TOAN INTERCHANGE SORT)
// ================================================================
void menuSapXepPhong(QuanLyPhong& qlPhong, const QuanLyHopDong& qlHopDong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHoaDon& qlHoaDon) {
    const MucLuaChon ds[] = {
        {1, "[1]  Theo dien tich phong: Be -> Lon (Tang dan)", ""},
        {2, "[2]  Theo dien tich phong: Lon -> Be (Giam dan)", ""},
        {3, "[3]  Theo gia thue goc: Be -> Lon (Tang dan)", ""},
        {4, "[4]  Theo gia thue goc: Lon -> Be (Giam dan)", ""},
        {0, "[0]  Quay lai menu Quan ly phong tro", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int lc = -1;
    while (lc != 0) {
        xoaManHinh();
        lc = menuDieuHuongDong("SẮP XẾP DANH SÁCH PHÒNG TRỌ (Interchange Sort)", ds, soMuc, 8, 2, 76);

        if (lc == 1) {
            xoaManHinh();
            qlPhong.sapXepTheoDienTich(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo DIEN TICH TANG DAN (Be -> Lon)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (lc == 2) {
            xoaManHinh();
            qlPhong.sapXepTheoDienTich(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo DIEN TICH GIAM DAN (Lon -> Be)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (lc == 3) {
            xoaManHinh();
            qlPhong.sapXepTheoGiaThue(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo GIA THUE TANG DAN (Be -> Lon)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (lc == 4) {
            xoaManHinh();
            qlPhong.sapXepTheoGiaThue(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep danh sach phong theo GIA THUE GIAM DAN (Lon -> Be)!");
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
            dungManHinh();
        }
    }
}

void menuSapXepHopDong(QuanLyHopDong& qlHopDong, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHoaDon& qlHoaDon) {
    const MucLuaChon ds[] = {
        {1, "[1]  Theo thoi gian lap hop dong: Cu -> Moi (Tang dan)", ""},
        {2, "[2]  Theo thoi gian lap hop dong: Moi -> Cu (Giam dan)", ""},
        {3, "[3]  Theo gia thue tren hop dong: Be -> Lon (Tang dan)", ""},
        {4, "[4]  Theo gia thue tren hop dong: Lon -> Be (Giam dan)", ""},
        {0, "[0]  Quay lai menu Quan ly hop dong", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int lc = -1;
    while (lc != 0) {
        xoaManHinh();
        lc = menuDieuHuongDong("SẮP XẾP HỢP ĐỒNG THUÊ PHÒNG (Interchange Sort)", ds, soMuc, 8, 2, 76);

        if (lc == 1) {
            xoaManHinh();
            qlHopDong.sapXepTheoNgayLap(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo THOI GIAN LAP CU -> MOI!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 2) {
            xoaManHinh();
            qlHopDong.sapXepTheoNgayLap(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo THOI GIAN LAP MOI -> CU!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 3) {
            xoaManHinh();
            qlHopDong.sapXepTheoGiaThue(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo GIA THUE TANG DAN (Be -> Lon)!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 4) {
            xoaManHinh();
            qlHopDong.sapXepTheoGiaThue(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hop dong theo GIA THUE GIAM DAN (Lon -> Be)!");
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
            dungManHinh();
        }
    }
}

void menuSapXepHoaDon(QuanLyHoaDon& qlHoaDon, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong) {
    const MucLuaChon ds[] = {
        {1,  "[1]   Theo thoi gian lap hoa don: Cu -> Moi (Tang dan)", ""},
        {2,  "[2]   Theo thoi gian lap hoa don: Moi -> Cu (Giam dan)", ""},
        {3,  "[3]   Theo tien phong / tien tra: Be -> Lon (Tang dan)", ""},
        {4,  "[4]   Theo tien phong / tien tra: Lon -> Be (Giam dan)", ""},
        {5,  "[5]   Theo tien dien: Be -> Lon (Tang dan)", ""},
        {6,  "[6]   Theo tien dien: Lon -> Be (Giam dan)", ""},
        {7,  "[7]   Theo tien nuoc: Be -> Lon (Tang dan)", ""},
        {8,  "[8]   Theo tien nuoc: Lon -> Be (Giam dan)", ""},
        {9,  "[9]   Theo tong tien hoa don: Be -> Lon (Tang dan)", ""},
        {10, "[10]  Theo tong tien hoa don: Lon -> Be (Giam dan)", ""},
        {0,  "[0]   Quay lai menu Quan ly hoa don", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int lc = -1;
    while (lc != 0) {
        xoaManHinh();
        lc = menuDieuHuongDong("SẮP XẾP HÓA ĐƠN THANH TOÁN (Interchange Sort)", ds, soMuc, 8, 2, 76);

        if (lc == 1) {
            xoaManHinh();
            qlHoaDon.sapXepTheoNgayLap(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo THOI GIAN LAP CU -> MOI!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 2) {
            xoaManHinh();
            qlHoaDon.sapXepTheoNgayLap(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo THOI GIAN LAP MOI -> CU!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 3) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTienPhong(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN PHONG TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 4) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTienPhong(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN PHONG GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 5) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTienDien(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN DIEN TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 6) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTienDien(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN DIEN GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 7) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTienNuoc(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN NUOC TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 8) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTienNuoc(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TIEN NUOC GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 9) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTongTien(true);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TONG TIEN TANG DAN (Be -> Lon)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (lc == 10) {
            xoaManHinh();
            qlHoaDon.sapXepTheoTongTien(false);
            luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
            inThongBaoThanhCong("Da sap xep hoa don theo TONG TIEN GIAM DAN (Lon -> Be)!");
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        }
    }
}

// ================================================================
//  1. MENU QUAN LY PHONG TRO
// ================================================================
void menuPhongTro(QuanLyPhong& qlPhong, QuanLyHopDong& qlHopDong, QuanLyNguoiThue& qlNguoiThue, QuanLyHoaDon& qlHoaDon) {
    const MucLuaChon ds[] = {
        {1,  "[1]   Them phong tro thuong", ""},
        {2,  "[2]   Them phong tro VIP", ""},
        {3,  "[3]   Xoa phong tro theo ma", ""},
        {4,  "[4]   Tim kiem phong tro theo ma", ""},
        {5,  "[5]   Hien thi tat ca phong tro (Kem nguoi thue)", ""},
        {6,  "[6]   In danh sach phong tro CON TRONG", ""},
        {7,  "[7]   In danh sach phong tro DANG THUE", ""},
        {8,  "[8]   Loc phong theo khoang gia thue (x - y trieu dong)", ""},
        {9,  "[9]   Tim kiem phong tro CO GAC LUNG", ""},
        {10, "[10]  Tim kiem phong tro co DIEN TICH LON HON x (m2)", ""},
        {11, "[11]  Xem so theo doi thanh toan tung thang cua mot phong", ""},
        {12, "[12]  Sap xep danh sach phong tro (Dien tich, Gia thue)", ""},
        {13, "[13]  Xoa man hinh console (Clear)", ""},
        {0,  "[0]   Quay lai menu chinh", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int luaChon = -1;
    while (luaChon != 0) {
        xoaManHinh();
        luaChon = menuDieuHuongDong("QUẢN LÝ DANH SÁCH PHÒNG TRỌ", ds, soMuc, 8, 2, 78);

        if (luaChon == 1) {
            xoaManHinh();
            cout << "\n  ═══ THÊM PHÒNG TRỌ THƯỜNG ═══\n\n";
            int soLuong = nhapSoNguyen("➔ Nhap so luong phong tro thuong can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac them phong.");
            } else {
                int daThem = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n  --- [Nhap phong tro thuong thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }
                    int ma = nhapMaPhongMoi(qlPhong);
                    string ten = nhapChuoi("➔ Nhap ten phong: ");
                    int tt = nhapSoNguyen("➔ Nhap tinh trang phong (0: Con trong, 1: Da thue): ", 0, 1);
                    string tinhTrang = (tt == 0) ? "Con trong" : "Da thue";
                    double dienTich = nhapSoThuc("➔ Nhap dien tich phong (m2, vd: 25 hoac 30.5): ", 0.0);
                    double gia = nhapSoThuc("➔ Nhap gia thue goc (> 0 VND): ");
                    int gacInt = nhapSoNguyen("➔ Co gac lung khong (1: Co, 0: Khong): ", 0, 1);

                    qlPhong.themPhongTro(new PhongTroThuong(ma, ten, tinhTrang, dienTich, gia, gacInt == 1));
                    daThem++;
                    cout << "  [+] Da them phong: " << ten << " (Ma: " << ma << ")\n";
                }
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da them thanh cong " + to_string(daThem) + " phong tro thuong (Da luu vao file)!");
            }
            dungManHinh();
        } else if (luaChon == 2) {
            xoaManHinh();
            cout << "\n  ═══ THÊM PHÒNG TRỌ VIP ═══\n\n";
            int soLuong = nhapSoNguyen("➔ Nhap so luong phong tro VIP can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac them phong VIP.");
            } else {
                int daThem = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n  --- [Nhap phong tro VIP thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }
                    int ma = nhapMaPhongMoi(qlPhong);
                    string ten = nhapChuoi("➔ Nhap ten phong: ");
                    int tt = nhapSoNguyen("➔ Nhap tinh trang phong (0: Con trong, 1: Da thue): ", 0, 1);
                    string tinhTrang = (tt == 0) ? "Con trong" : "Da thue";
                    double dienTich = nhapSoThuc("➔ Nhap dien tich phong (m2, vd: 40 hoac 45.5): ", 0.0);
                    double gia = nhapSoThuc("➔ Nhap gia thue goc (> 0 VND): ");
                    double phiDV = nhapSoThuc("➔ Nhap phi dich vu dac biet (>= 0 VND): ", -0.01);

                    qlPhong.themPhongTro(new PhongTroVip(ma, ten, tinhTrang, dienTich, gia, phiDV));
                    daThem++;
                    cout << "  [+] Da them phong VIP: " << ten << " (Ma: " << ma << ")\n";
                }
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da them thanh cong " + to_string(daThem) + " phong tro VIP (Da luu vao file)!");
            }
            dungManHinh();
        } else if (luaChon == 3) {
            xoaManHinh();
            cout << "\n  ═══ XÓA PHÒNG TRỌ THEO MÃ ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma phong can xoa (Nhap 0 de huy): ", 0);
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
            dungManHinh();
        } else if (luaChon == 4) {
            xoaManHinh();
            cout << "\n  ═══ TÌM KIẾM PHÒNG TRỌ THEO MÃ ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma phong can tim: ", 1);
            PhongTro* pt = qlPhong.timKiemPhongTro(ma);
            if (pt != nullptr) {
                datMau(MAU_XANH_LA_SANG, 0);
                cout << "\n  [✓ KẾT QUẢ TÌM KIẾM PHÒNG TRỌ]:\n";
                khoiPhucMau();
                cout << *pt << "\n";
            } else {
                inThongBaoLoi("Khong tim thay phong voi ma: " + to_string(ma));
            }
            dungManHinh();
        } else if (luaChon == 5) {
            xoaManHinh();
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH TẤT CẢ PHÒNG TRỌ (KÈM THÔNG TIN NGƯỜI THUÊ) ═══";
            khoiPhucMau();
            hienThiBangPhongTro(qlPhong.layDanhSachPhong(), qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 6) {
            xoaManHinh();
            LinkedList<PhongTro*> dsTrong = qlPhong.layDanhSachPhongTheoTinhTrang("Con trong");
            datMau(MAU_XANH_LA_SANG, 0);
            cout << "\n  ═══ DANH SÁCH CÁC PHÒNG TRỌ CÒN TRỐNG ═══";
            khoiPhucMau();
            hienThiBangPhongTro(dsTrong, qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 7) {
            xoaManHinh();
            LinkedList<PhongTro*> dsDaThue = qlPhong.layDanhSachPhongTheoTinhTrang("Da thue");
            datMau(MAU_VANG_CAM, 0);
            cout << "\n  ═══ DANH SÁCH CÁC PHÒNG TRỌ ĐANG ĐƯỢC THUÊ ═══";
            khoiPhucMau();
            hienThiBangPhongTro(dsDaThue, qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 8) {
            xoaManHinh();
            cout << "\n  ═══ LỌC PHÒNG THEO KHOẢNG GIÁ THUÊ ═══\n\n";
            double xTrieu = nhapSoThuc("➔ Nhap gia toi thieu (trieu dong, vd: 1.5): ", 0.0);
            double yTrieu = nhapSoThuc("➔ Nhap gia toi da (trieu dong, vd: 4.0): ", 0.0);
            if (xTrieu > yTrieu) swap(xTrieu, yTrieu);
            double giaMin = xTrieu * 1000000.0;
            double giaMax = yTrieu * 1000000.0;
            LinkedList<PhongTro*> dsGia = qlPhong.timPhongTheoKhoangGia(giaMin, giaMax);
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH PHÒNG CÓ GIÁ TỪ " << xTrieu << " ĐẾN " << yTrieu << " TRIỆU ĐỒNG ═══";
            khoiPhucMau();
            hienThiBangPhongTro(dsGia, qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 9) {
            xoaManHinh();
            LinkedList<PhongTro*> dsGac = qlPhong.timPhongCoGacLung();
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH PHÒNG TRỌ CÓ GÁC LỬNG ═══";
            khoiPhucMau();
            hienThiBangPhongTro(dsGac, qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 10) {
            xoaManHinh();
            cout << "\n  ═══ TÌM KIẾM PHÒNG THEO DIỆN TÍCH LỚN HƠN X ═══\n\n";
            double xDT = nhapSoThuc("➔ Nhap dien tich toi thieu (m2, vd: 25 hoac 30.5): ", 0.0);
            LinkedList<PhongTro*> dsDT = qlPhong.timPhongTheoDienTichLonHon(xDT);
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH PHÒNG CÓ DIỆN TÍCH LỚN HƠN " << xDT << " m2 ═══";
            khoiPhucMau();
            hienThiBangPhongTro(dsDT, qlHopDong, qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 11) {
            xoaManHinh();
            cout << "\n  ═══ TRA CỨU SỔ THEO DÕI THANH TOÁN TỪNG THÁNG CỦA MỘT PHÒNG ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma phong can xem so theo doi thanh toan: ", 1);
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
                    int thangMoc = nhapSoNguyen("➔ Nhap thang moc can kiem tra (1 - 12): ", 1, 12);
                    int namMoc = nhapSoNguyen("➔ Nhap nam moc can kiem tra (1900 - 2100): ", 1900, 2100);
                    hienThiSoTheoDoiThanhToanPhong(ma, pt->getTenPhong(), tenNT, sdtNT, hd, qlHoaDon, thangMoc, namMoc);
                }
            }
            dungManHinh();
        } else if (luaChon == 12) {
            menuSapXepPhong(qlPhong, qlHopDong, qlNguoiThue, qlHoaDon);
        } else if (luaChon == 13) {
            xoaManHinh();
        }
    }
}

// ================================================================
//  2. MENU QUAN LY NGUOI THUE
// ================================================================
void menuNguoiThue(QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong, const QuanLyPhong& qlPhong, const QuanLyHoaDon& qlHoaDon) {
    const MucLuaChon ds[] = {
        {1, "[1]  Them nguoi thue (Khach hang) moi", ""},
        {2, "[2]  Xoa nguoi thue theo ma", ""},
        {3, "[3]  Tim kiem khach hang theo ma", ""},
        {4, "[4]  Hien thi tat ca khach hang (Bang chi tiet)", ""},
        {5, "[5]  In danh sach khach hang DANG THUE TRO", ""},
        {6, "[6]  In danh sach khach hang CHUA THUE PHONG NAO", ""},
        {7, "[7]  In danh sach khach CHUA DONG TIEN trong thang", ""},
        {8, "[8]  In lich su hop dong cua mot khach hang", ""},
        {9, "[9]  Xoa man hinh console (Clear)", ""},
        {0, "[0]  Quay lai menu chinh", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int luaChon = -1;
    while (luaChon != 0) {
        xoaManHinh();
        luaChon = menuDieuHuongDong("QUẢN LÝ DANH SÁCH NGƯỜI THUÊ (KHÁCH HÀNG)", ds, soMuc, 8, 2, 78);

        if (luaChon == 1) {
            xoaManHinh();
            cout << "\n  ═══ THÊM KHÁCH HÀNG (NGƯỜI THUÊ) MỚI ═══\n\n";
            int soLuong = nhapSoNguyen("➔ Nhap so luong khach hang can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac them khach hang.");
            } else {
                int daThem = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n  --- [Nhap khach hang thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }
                    int ma = nhapMaNguoiThueMoi(qlNguoiThue);
                    string hoTen = nhapChuoi("➔ Nhap ho va ten: ");
                    Date ns = nhapNgayThangNam("ngay sinh nguoi thue");
                    string sdt = nhapSoDienThoai("➔ Nhap so dien thoai (10 chu so): ");

                    qlNguoiThue.themNguoiThue(new NguoiThue(ma, hoTen, ns, sdt));
                    daThem++;
                    cout << "  [+] Da them khach hang: " << hoTen << " (Ma NT: " << ma << ")\n";
                }
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da them thanh cong " + to_string(daThem) + " khach hang (Da luu file)!");
            }
            dungManHinh();
        } else if (luaChon == 2) {
            xoaManHinh();
            cout << "\n  ═══ XÓA NGƯỜI THUÊ THEO MÃ ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma nguoi thue can xoa (Nhap 0 de huy): ", 0);
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
            dungManHinh();
        } else if (luaChon == 3) {
            xoaManHinh();
            cout << "\n  ═══ TÌM KIẾM KHÁCH HÀNG THEO MÃ ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma khach hang can tim: ", 1);
            NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(ma);
            if (nt != nullptr) {
                datMau(MAU_XANH_LA_SANG, 0);
                cout << "\n  [✓ KẾT QUẢ TÌM KIẾM KHÁCH HÀNG]:\n";
                khoiPhucMau();
                cout << *nt << "\n";
            } else {
                inThongBaoLoi("Khong tim thay khach hang voi ma: " + to_string(ma));
            }
            dungManHinh();
        } else if (luaChon == 4) {
            xoaManHinh();
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH TẤT CẢ KHÁCH HÀNG TRONG HỆ THỐNG ═══";
            khoiPhucMau();
            hienThiBangNguoiThue(qlNguoiThue.layDanhSachNguoiThue(), qlHopDong);
            dungManHinh();
        } else if (luaChon == 5) {
            xoaManHinh();
            LinkedList<NguoiThue*> dsDangThue;
            for (NguoiThue* nt : qlNguoiThue.layDanhSachNguoiThue()) {
                if (qlHopDong.timMaPhongTheoNguoiThue(nt->getMaNguoiThue()) != 0) {
                    dsDangThue.push_back(nt);
                }
            }
            datMau(MAU_XANH_LA_SANG, 0);
            cout << "\n  ═══ DANH SÁCH KHÁCH HÀNG ĐANG THUÊ TRỌ ═══";
            khoiPhucMau();
            hienThiBangNguoiThue(dsDangThue, qlHopDong);
            dungManHinh();
        } else if (luaChon == 6) {
            xoaManHinh();
            LinkedList<NguoiThue*> dsChuaThue;
            for (NguoiThue* nt : qlNguoiThue.layDanhSachNguoiThue()) {
                if (qlHopDong.timMaPhongTheoNguoiThue(nt->getMaNguoiThue()) == 0) {
                    dsChuaThue.push_back(nt);
                }
            }
            datMau(MAU_VANG_CAM, 0);
            cout << "\n  ═══ DANH SÁCH KHÁCH HÀNG CHƯA THUÊ PHÒNG NÀO ═══";
            khoiPhucMau();
            hienThiBangNguoiThue(dsChuaThue, qlHopDong);
            dungManHinh();
        } else if (luaChon == 7) {
            xoaManHinh();
            cout << "\n  ═══ KIỂM TRA KHÁCH HÀNG CHƯA ĐÓNG TIỀN TRỌ ═══\n\n";
            int thang = nhapSoNguyen("➔ Nhap thang can kiem tra (1 - 12): ", 1, 12);
            int nam = nhapSoNguyen("➔ Nhap nam can kiem tra (1900 - 2100): ", 1900, 2100);

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
            datMau(MAU_DO_SANG, 0);
            cout << "\n  ═══ DANH SÁCH KHÁCH HÀNG CHƯA ĐÓNG TIỀN TRỌ THÁNG " << thang << "/" << nam << " ═══";
            khoiPhucMau();
            hienThiBangKhachChuaDongTien(dsChuaDong, thang, nam);
            dungManHinh();
        } else if (luaChon == 8) {
            xoaManHinh();
            cout << "\n  ═══ IN LỊCH SỬ HỢP ĐỒNG CỦA MỘT KHÁCH HÀNG ═══\n\n";
            int maNT = nhapSoNguyen("➔ Nhap ma khach hang can xem lich su hop dong: ", 1);
            NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(maNT);
            if (nt == nullptr) {
                inThongBaoLoi("Khong tim thay khach hang ma: " + to_string(maNT));
            } else {
                LinkedList<HopDongThue> dsLichSu = qlHopDong.layLichSuHopDongTheoNguoiThue(maNT);
                datMau(MAU_VANG_SANG, 0);
                cout << "\n  ═══ LỊCH SỬ HỢP ĐỒNG CỦA KHÁCH HÀNG: " << nt->getHoTen() << " (MÃ NT: " << maNT << ") ═══";
                khoiPhucMau();
                hienThiBangHopDong(dsLichSu, qlNguoiThue);
            }
            dungManHinh();
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

// ================================================================
//  3. MENU QUAN LY HOP DONG THUE
// ================================================================
void menuHopDong(QuanLyHopDong& qlHopDong, QuanLyPhong& qlPhong, QuanLyNguoiThue& qlNguoiThue, QuanLyHoaDon& qlHoaDon) {
    const MucLuaChon ds[] = {
        {1, "[1]  Lap hop dong thue phong (Tu dong lien ket phong & NT)", ""},
        {2, "[2]  Tra phong tro / Thanh ly hop dong thue", ""},
        {3, "[3]  Xoa hop dong theo ma", ""},
        {4, "[4]  Cap nhat thoi han va gia thue", ""},
        {5, "[5]  Tim kiem hop dong theo ma", ""},
        {6, "[6]  Hien thi danh sach hop dong (Kem ten nguoi thue & phong)", ""},
        {7, "[7]  Sap xep hop dong thue (Thoi gian lap, Gia thue)", ""},
        {8, "[8]  Xoa man hinh console (Clear)", ""},
        {0, "[0]  Quay lai menu chinh", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int luaChon = -1;
    while (luaChon != 0) {
        xoaManHinh();
        luaChon = menuDieuHuongDong("QUẢN LÝ HỢP ĐỒNG THUÊ PHÒNG", ds, soMuc, 8, 2, 78);

        if (luaChon == 1) {
            thuePhongTro(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
        } else if (luaChon == 2) {
            traPhongTro(qlPhong, qlHopDong, qlNguoiThue, qlHoaDon);
        } else if (luaChon == 3) {
            xoaManHinh();
            cout << "\n  ═══ XÓA HỢP ĐỒNG THEO MÃ ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma hop dong can xoa (Nhap 0 de huy): ", 0);
            if (ma != 0) {
                HopDongThue hd = qlHopDong.timKiemHopDong(ma);
                if (hd.getMaHopDong() == 0) {
                    inThongBaoLoi("Khong tim thay hop dong ma: " + to_string(ma));
                } else {
                    int maPhongLienQuan = hd.getMaPhong();
                    qlHopDong.xoaHopDong(ma);

                    // Dong bo trang thai phong: Neu phong nay khong con hop dong nao khac -> chuyen ve "Con trong"
                    PhongTro* pt = qlPhong.timKiemPhongTro(maPhongLienQuan);
                    if (pt != nullptr) {
                        LinkedList<HopDongThue> dsConLai = qlHopDong.layDanhSachHopDongTheoPhong(maPhongLienQuan);
                        if (dsConLai.empty()) {
                            pt->setTinhTrang("Con trong");
                            cout << "  [i] Phong " << pt->getTenPhong() << " (Ma: " << maPhongLienQuan 
                                 << ") khong con hop dong thue nao -> Da tu dong cap nhat ve: Con trong!\n";
                        }
                    }

                    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                    inThongBaoThanhCong("Da xoa hop dong ma " + to_string(ma) + " (Da cap nhat file)!");
                }
            }
            dungManHinh();
        } else if (luaChon == 4) {
            xoaManHinh();
            cout << "\n  ═══ CẬP NHẬT THỜI HẠN VÀ GIÁ THUÊ CỦA HỢP ĐỒNG ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma hop dong can cap nhat: ", 1);
            HopDongThue hd = qlHopDong.timKiemHopDong(ma);
            if (hd.getMaHopDong() == 0) {
                inThongBaoLoi("Khong tim thay hop dong ma: " + to_string(ma));
            } else {
                int thoiHanMoi = nhapSoNguyen("➔ Nhap thoi han moi (1 - 120 thang): ", 1, 120);
                double giaMoi = nhapSoThuc("➔ Nhap gia thue moi (> 0 VND): ");
                hd.setThoiHan(thoiHanMoi);
                hd.setGiaThue(giaMoi);
                qlHopDong.capNhatThongTin(hd);
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Cap nhat hop dong thanh cong (Da luu file)!");
            }
            dungManHinh();
        } else if (luaChon == 5) {
            xoaManHinh();
            cout << "\n  ═══ TÌM KIẾM HỢP ĐỒNG THEO MÃ ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma hop dong can tim: ", 1);
            HopDongThue hd = qlHopDong.timKiemHopDong(ma);
            if (hd.getMaHopDong() != 0) {
                datMau(MAU_XANH_LA_SANG, 0);
                cout << "\n  [✓ KẾT QUẢ TÌM KIẾM HỢP ĐỒNG]:\n";
                khoiPhucMau();
                cout << hd << "\n";
            } else {
                inThongBaoLoi("Khong tim thay hop dong ma: " + to_string(ma));
            }
            dungManHinh();
        } else if (luaChon == 6) {
            xoaManHinh();
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH HỢP ĐỒNG THUÊ TRONG HỆ THỐNG ═══";
            khoiPhucMau();
            hienThiBangHopDong(qlHopDong.layDanhSachHopDong(), qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 7) {
            menuSapXepHopDong(qlHopDong, qlPhong, qlNguoiThue, qlHoaDon);
        } else if (luaChon == 8) {
            xoaManHinh();
        }
    }
}

// ================================================================
//  4. MENU QUAN LY HOA DON THANH TOAN
// ================================================================
void menuHoaDon(QuanLyHoaDon& qlHoaDon, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, const QuanLyHopDong& qlHopDong) {
    const MucLuaChon ds[] = {
        {1,  "[1]   Them hoa don (Ky thanh toan & chi tiet phong, dien, nuoc)", ""},
        {2,  "[2]   Xoa hoa don theo ma", ""},
        {3,  "[3]   Cap nhat tien phong, dien, nuoc cua hoa don", ""},
        {4,  "[4]   Tim kiem hoa don theo ma", ""},
        {5,  "[5]   Hien thi tat ca hoa don (Bang chi tiet kem Ky TT)", ""},
        {6,  "[6]   So theo doi thanh toan tung thang cua phong (Da tra / Con no)", ""},
        {7,  "[7]   Tong hop tinh trang dong tien tat ca cac phong trong thang", ""},
        {8,  "[8]   In danh sach phong co tien dien cao hon x dong", ""},
        {9,  "[9]   Thong ke tong doanh thu tien phong, dien, nuoc thang", ""},
        {10, "[10]  Sap xep hoa don (Ngay lap, Tien phong, Dien, Nuoc, Tong)", ""},
        {11, "[11]  Xoa man hinh console (Clear)", ""},
        {0,  "[0]   Quay lai menu chinh", ""}
    };
    int soMuc = sizeof(ds) / sizeof(ds[0]);

    int luaChon = -1;
    while (luaChon != 0) {
        xoaManHinh();
        luaChon = menuDieuHuongDong("QUẢN LÝ HÓA ĐƠN THANH TOÁN & DOANH THU", ds, soMuc, 8, 2, 78);

        if (luaChon == 1) {
            xoaManHinh();
            cout << "\n  ═══ THÊM HÓA ĐƠN THANH TOÁN ═══\n\n";
            int soLuong = nhapSoNguyen("➔ Nhap so luong hoa don can them (Nhap 0 de huy): ", 0);
            if (soLuong <= 0) {
                inThongBaoLoi("Da huy thao tac lap hoa don.");
            } else {
                int daLap = 0;
                for (int i = 0; i < soLuong; ++i) {
                    if (soLuong > 1) {
                        cout << "\n  --- [Lap hoa don thu " << (i + 1) << "/" << soLuong << "] ---\n";
                    }

                    // Nhap ma hoa don moi khong trung
                    string ma;
                    bool boQua = false;
                    while (true) {
                        try {
                            ma = nhapChuoi("➔ Nhap ma hoa don (vd: HD03, nhap 0 de bo qua): ");
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
                        inHopThongBaoThongTin("Da bo qua hoa don nay.");
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
                            maPhong = nhapSoNguyen("➔ Nhap ma phong thue (Nhap 0 de bo qua): ", 0);
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
                        inHopThongBaoThongTin("Da bo qua hoa don nay.");
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
                            cout << "  ➔ Ky thanh toan (dong nhat theo thang/nam cua ngay lap): Thang "
                                 << (thangTT < 10 ? "0" : "") << thangTT << "/" << namTT << "\n";

                            // Kiem tra phong co hop dong thue co hieu luc trong ky nay khong
                            hdHieuLuc = qlHopDong.timHopDongTheoPhongVaKy(maPhong, thangTT, namTT);
                            if (hdHieuLuc.getMaHopDong() == 0) {
                                cout << "  [!] Phong " << maPhong << " khong co hop dong nao co hieu luc trong thang "
                                     << thangTT << "/" << namTT << "!\n";
                                cout << "      Lich su cac hop dong cua phong " << maPhong << ":\n";
                                for (const auto& h : qlHopDong.layDanhSachHopDongTheoPhong(maPhong)) {
                                    cout << "      + Ma HD " << h.getMaHopDong() << " (Ma NT: " << h.getMaNguoiThue()
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
                    cout << "  ➔ Xac dinh nguoi thue theo hop dong (Ma HD: " << hdHieuLuc.getMaHopDong() << "): "
                         << tenNT << " (Ma NT: " << maNT << ")\n";

                    if (qlHoaDon.daDongTienThang(maPhong, maNT, thangTT, namTT)) {
                        cout << "\n  [!] CANH BAO: Phong " << maPhong << " da co hoa don thanh toan cho ky thang " 
                             << (thangTT < 10 ? "0" : "") << thangTT << "/" << namTT << " roi!\n";
                        int xacNhan = nhapSoNguyen("      Ban co muon tiep tuc lap them hoa don cho ky nay khong? (1: Co, 0: Bo qua): ", 0, 1);
                        if (xacNhan == 0) {
                            inHopThongBaoThongTin("Da bo qua hoa don nay.");
                            if (i + 1 < soLuong) {
                                int tiep = nhapSoNguyen("    Ban co muon tiep tuc lap hoa don tiep theo? (1: Co, 0: Dung): ", 0, 1);
                                if (tiep == 0) break;
                            }
                            continue;
                        }
                    }

                    double tienPhongGoiY = hdHieuLuc.getGiaThue();
                    cout << "  ➔ Tien phong theo hop dong: " << dinhDangTien((long long)tienPhongGoiY) << " VND\n";
                    double tienPhong = nhapSoThuc("➔ Nhap tien phong (> 0 VND): ");
                    double tienDien = nhapSoThuc("➔ Nhap tien dien (>= 0 VND): ", -0.01);
                    double tienNuoc = nhapSoThuc("➔ Nhap tien nuoc (>= 0 VND): ", -0.01);

                    qlHoaDon.themHoaDon(HoaDon(ma, maPhong, maNT, ngayLap, thangTT, namTT, tienPhong, tienDien, tienNuoc));
                    daLap++;
                    string kyStr = (thangTT < 10 ? "0" : "") + to_string(thangTT) + "/" + to_string(namTT);
                    cout << "  [+] Da lap hoa don " << ma << " (Ky " << kyStr << ") | Tong: " 
                         << dinhDangTien((long long)(tienPhong + tienDien + tienNuoc)) << " VND\n";
                }
                if (daLap > 0) {
                    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                    inThongBaoThanhCong("Da lap thanh cong " + to_string(daLap) + " hoa don (Da luu vao file)!");
                }
            }
            dungManHinh();
        } else if (luaChon == 2) {
            xoaManHinh();
            cout << "\n  ═══ XÓA HÓA ĐƠN THEO MÃ ═══\n\n";
            string ma = nhapChuoi("➔ Nhap ma hoa don can xoa: ");
            HoaDon hd = qlHoaDon.timKiemHoaDon(ma);
            if (hd.getMaHoaDon() == "") {
                inThongBaoLoi("Khong tim thay hoa don ma: " + ma);
            } else {
                qlHoaDon.xoaHoaDon(ma);
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                inThongBaoThanhCong("Da xoa hoa don ma " + ma + " (Da cap nhat file)!");
            }
            dungManHinh();
        } else if (luaChon == 3) {
            xoaManHinh();
            cout << "\n  ═══ CẬP NHẬT TIỀN PHÒNG, ĐIỆN, NƯỚC CỦA HÓA ĐƠN ═══\n\n";
            string ma = nhapChuoi("➔ Nhap ma hoa don can cap nhat (Nhap 0 de huy): ");
            if (ma != "0") {
                HoaDon hd = qlHoaDon.timKiemHoaDon(ma);
                if (hd.getMaHoaDon() == "") {
                    inThongBaoLoi("Khong tim thay hoa don voi ma: " + ma);
                } else {
                    NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                    string tenNT = (nt != nullptr) ? nt->getHoTen() : ("Ma NT: " + to_string(hd.getMaNguoiThue()));

                    cout << "\n";
                    datMau(MAU_XANH_NGOC_SANG, 0);
                    cout << "  ┌───────────────────────────────────────────────────────────┐\n";
                    cout << "  │               THÔNG TIN HÓA ĐƠN HIỆN TẠI                  │\n";
                    cout << "  ├───────────────────────────────────────────────────────────┤\n";
                    cout << "  │  Mã hóa đơn     : " << left << setw(38) << hd.getMaHoaDon() << "│\n";
                    cout << "  │  Mã phòng       : " << left << setw(38) << hd.getMaPhong() << "│\n";
                    cout << "  │  Người thuê     : " << left << setw(38) << (tenNT + " (Mã: " + to_string(hd.getMaNguoiThue()) + ")") << "│\n";
                    cout << "  │  Kỳ thanh toán  : " << left << setw(38) << hd.getKyThanhToan() << "│\n";
                    cout << "  │  Ngày lập       : " << left << setw(38) << hd.getNgayLap().toString() << "│\n";
                    cout << "  │  Tiền phòng     : " << left << setw(34) << (dinhDangTien((long long)hd.getTienPhong()) + " VND") << "│\n";
                    cout << "  │  Tiền điện      : " << left << setw(34) << (dinhDangTien((long long)hd.getTienDien()) + " VND") << "│\n";
                    cout << "  │  Tiền nước      : " << left << setw(34) << (dinhDangTien((long long)hd.getTienNuoc()) + " VND") << "│\n";
                    cout << "  │  Tổng thanh toán: " << left << setw(34) << (dinhDangTien((long long)hd.getTongTien()) + " VND") << "│\n";
                    cout << "  └───────────────────────────────────────────────────────────┘\n";
                    khoiPhucMau();

                    cout << "\n  Chon muc ban muon cap nhat:\n";
                    cout << "    [1] Cap nhat tat ca (Tien phong, Tien dien, Tien nuoc)\n";
                    cout << "    [2] Chi cap nhat Tien phong\n";
                    cout << "    [3] Chi cap nhat Tien dien\n";
                    cout << "    [4] Chi cap nhat Tien nuoc\n";
                    cout << "    [0] Giu nguyen / Huy thao tac\n";
                    int chonMuc = nhapSoNguyen("➔ Nhap lua chon cua ban [0-4]: ", 0, 4);

                    if (chonMuc == 0) {
                        inThongBaoLoi("Da huy thao tac cap nhat hoa don.");
                    } else {
                        double phongMoi = hd.getTienPhong();
                        double dienMoi = hd.getTienDien();
                        double nuocMoi = hd.getTienNuoc();

                        if (chonMuc == 1) {
                            phongMoi = nhapSoThuc("➔ Nhap tien phong moi (> 0 VND, hien tai: " + to_string((long long)hd.getTienPhong()) + "): ");
                            dienMoi = nhapSoThuc("➔ Nhap tien dien moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienDien()) + "): ", -0.01);
                            nuocMoi = nhapSoThuc("➔ Nhap tien nuoc moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienNuoc()) + "): ", -0.01);
                        } else if (chonMuc == 2) {
                            phongMoi = nhapSoThuc("➔ Nhap tien phong moi (> 0 VND, hien tai: " + to_string((long long)hd.getTienPhong()) + "): ");
                        } else if (chonMuc == 3) {
                            dienMoi = nhapSoThuc("➔ Nhap tien dien moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienDien()) + "): ", -0.01);
                        } else if (chonMuc == 4) {
                            nuocMoi = nhapSoThuc("➔ Nhap tien nuoc moi (>= 0 VND, hien tai: " + to_string((long long)hd.getTienNuoc()) + "): ", -0.01);
                        }

                        hd.setChiTiet(phongMoi, dienMoi, nuocMoi);
                        qlHoaDon.capNhatHoaDon(hd);
                        luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
                        inThongBaoThanhCong("Da cap nhat hoa don " + ma + " thanh cong! Tong tien moi: " + dinhDangTien((long long)hd.getTongTien()) + " VND");
                    }
                }
            }
            dungManHinh();
        } else if (luaChon == 4) {
            xoaManHinh();
            cout << "\n  ═══ TÌM KIẾM HÓA ĐƠN THEO MÃ ═══\n\n";
            string ma = nhapChuoi("➔ Nhap ma hoa don can tim: ");
            HoaDon hd = qlHoaDon.timKiemHoaDon(ma);
            if (hd.getMaHoaDon() != "") {
                datMau(MAU_XANH_LA_SANG, 0);
                cout << "\n  [✓ KẾT QUẢ TÌM KIẾM HÓA ĐƠN]:\n";
                khoiPhucMau();
                cout << hd << "\n";
            } else {
                inThongBaoLoi("Khong tim thay hoa don ma: " + ma);
            }
            dungManHinh();
        } else if (luaChon == 5) {
            xoaManHinh();
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ DANH SÁCH TẤT CẢ HÓA ĐƠN THANH TOÁN ═══";
            khoiPhucMau();
            hienThiBangHoaDon(qlHoaDon.layDanhSachHoaDon(), qlHoaDon.tinhTongDoanhThu(), qlNguoiThue);
            dungManHinh();
        } else if (luaChon == 6) {
            xoaManHinh();
            cout << "\n  ═══ TRA CỨU SỔ THEO DÕI THANH TOÁN TỪNG THÁNG CỦA PHÒNG ═══\n\n";
            int ma = nhapSoNguyen("➔ Nhap ma phong can xem (Nhap 0 de huy): ", 0);
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
                        int thangMoc = nhapSoNguyen("➔ Nhap thang moc can tra cuu (1 - 12): ", 1, 12);
                        int namMoc = nhapSoNguyen("➔ Nhap nam moc can tra cuu (1900 - 2100): ", 1900, 2100);
                        hienThiSoTheoDoiThanhToanPhong(ma, pt->getTenPhong(), tenNT, sdtNT, hd, qlHoaDon, thangMoc, namMoc);
                    }
                }
            }
            dungManHinh();
        } else if (luaChon == 7) {
            xoaManHinh();
            cout << "\n  ═══ TỔNG HỢP TÌNH TRẠNG ĐÓNG TIỀN TẤT CẢ CÁC PHÒNG TRONG THÁNG ═══\n\n";
            int thang = nhapSoNguyen("➔ Nhap thang can kiem tra (1 - 12): ", 1, 12);
            int nam = nhapSoNguyen("➔ Nhap nam can kiem tra (1900 - 2100): ", 1900, 2100);

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
            dungManHinh();
        } else if (luaChon == 8) {
            xoaManHinh();
            cout << "\n  ═══ TRA CỨU PHÒNG CÓ TIỀN ĐIỆN CAO ═══\n\n";
            int thang = nhapSoNguyen("➔ Nhap thang can kiem tra (Nhap 0 de xem tat ca cac thang): ", 0, 12);
            int nam = 0;
            if (thang != 0) {
                nam = nhapSoNguyen("➔ Nhap nam (1900 - 2100): ", 1900, 2100);
            }
            double mucTien = nhapSoThuc("➔ Nhap muc tien dien toi thieu (VND, vd: 200000): ", 0.0);

            LinkedList<HoaDon> dsTienDienCao = qlHoaDon.timHoaDonTienDienCaoHon(mucTien, thang, nam);
            if (thang != 0) {
                datMau(MAU_VANG_SANG, 0);
                cout << "\n  ═══ DANH SÁCH PHÒNG CÓ TIỀN ĐIỆN THÁNG " << thang << "/" << nam << " CAO HƠN " << dinhDangTien((long long)mucTien) << " VND ═══";
            } else {
                datMau(MAU_VANG_SANG, 0);
                cout << "\n  ═══ DANH SÁCH PHÒNG CÓ TIỀN ĐIỆN CAO HƠN " << dinhDangTien((long long)mucTien) << " VND ═══";
            }
            khoiPhucMau();
            hienThiBangTienDienCao(dsTienDienCao, qlPhong, qlNguoiThue, mucTien);
            dungManHinh();
        } else if (luaChon == 9) {
            xoaManHinh();
            cout << "\n  ═══ THỐNG KÊ TỔNG DOANH THU THEO THÁNG ═══\n\n";
            int thang = nhapSoNguyen("➔ Nhap thang can thong ke (1 - 12): ", 1, 12);
            int nam = nhapSoNguyen("➔ Nhap nam can thong ke (1900 - 2100): ", 1900, 2100);

            double tongPhong = qlHoaDon.tinhTongTienPhong(thang, nam);
            double tongDien = qlHoaDon.tinhTongTienDien(thang, nam);
            double tongNuoc = qlHoaDon.tinhTongTienNuoc(thang, nam);
            double tongCong = qlHoaDon.tinhTongDoanhThuThang(thang, nam);

            LinkedList<HoaDon> dsThang = qlHoaDon.layHoaDonTheoThang(thang, nam);
            datMau(MAU_VANG_SANG, 0);
            cout << "\n  ═══ CHI TIẾT CÁC HÓA ĐƠN TRONG THÁNG " << thang << "/" << nam << " ═══";
            khoiPhucMau();
            hienThiBangHoaDon(dsThang, tongCong, qlNguoiThue);
            hienThiThongKeDoanhThuThang(thang, nam, tongPhong, tongDien, tongNuoc, tongCong);
            dungManHinh();
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
