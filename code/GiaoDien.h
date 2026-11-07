#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// ================================================================
//  HAM TIEN ICH CO BAN & DINH DANG
// ================================================================
void xoaManHinh() {
    khoiPhucMau();
    system("cls");
}

void xoaBoDem() {
    cin.clear();
    string rac;
    getline(cin, rac);
}

// Dinh dang so tien sang chuoi co cham phan cach hang nghin (vd: 2500000 -> 2.500.000)
inline string dinhDangTien(long long tien) {
    if (tien == 0) return "0";
    bool am = false;
    if (tien < 0) {
        am = true;
        tien = -tien;
    }
    string s = to_string(tien);
    int n = (int)s.length();
    string res = "";
    int dem = 0;
    for (int i = n - 1; i >= 0; --i) {
        res = s[i] + res;
        dem++;
        if (dem == 3 && i != 0) {
            res = "." + res;
            dem = 0;
        }
    }
    if (am) res = "-" + res;
    return res;
}

void inThongBaoThanhCong(const string& msg) {
    inHopThongBaoThanhCong(msg);
}

void inThongBaoLoi(const string& msg) {
    inHopThongBaoLoi(msg);
}

// ================================================================
//  1. BANG HIEN THI PHONG TRO
// ================================================================
void hienThiBangPhongTro(const LinkedList<PhongTro*>& ds, const QuanLyHopDong& qlHopDong, const QuanLyNguoiThue& qlNguoiThue) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌──────┬──────────────────────┬────────────┬───────────┬─────────────────┬─────────────────┬──────────────────────────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ", 4);    cout << " │ ";
    inCanhTrai("TÊN PHÒNG", 20); cout << " │ ";
    inCanhTrai("TÌNH TRẠNG", 10); cout << " │ ";
    inCanhTrai("DIỆN TÍCH", 9);  cout << " │ ";
    inCanhPhai("GIÁ GỐC (VND)", 15); cout << " │ ";
    inCanhPhai("TỔNG GIÁ (VND)", 15); cout << " │ ";
    inCanhTrai("NGƯỜI THUÊ (MÃ - HỌ TÊN - SĐT)", 40);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├──────┼──────────────────────┼────────────┼───────────┼─────────────────┼─────────────────┼──────────────────────────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Danh sách phòng trọ hiện đang trống!", 131);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        for (PhongTro* pt : ds) {
            stt++;
            string thongTinNguoiThue = "--- (Còn trống) ---";
            if (pt->getTinhTrang() == "Da thue") {
                int maNT = qlHopDong.timMaNguoiThueTheoPhong(pt->getMaPhong());
                if (maNT != 0) {
                    NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(maNT);
                    if (nt != nullptr) {
                        thongTinNguoiThue = to_string(maNT) + " - " + nt->getHoTen() + " (" + nt->getSoDienThoai() + ")";
                    } else {
                        thongTinNguoiThue = "Ma NT: " + to_string(maNT);
                    }
                } else {
                    thongTinNguoiThue = "Chưa cập nhật người thuê";
                }
            }
            if (demKyTuHienThi(thongTinNguoiThue) > 40) {
                while (demKyTuHienThi(thongTinNguoiThue) > 37) thongTinNguoiThue.pop_back();
                thongTinNguoiThue += "...";
            }

            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(pt->getMaPhong()), 4);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(pt->getTenPhong(), 20);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";

            // Tô màu trạng thái phòng
            if (pt->getTinhTrang() == "Con trong") {
                datMau(MAU_XANH_LA_SANG, 0);
                inCanhTrai("Còn trống", 10);
            } else {
                datMau(MAU_VANG_CAM, 0);
                inCanhTrai("Đã thuê", 10);
            }

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(pt->getDienTichStr(), 9);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)pt->getGiaThue()), 15);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)pt->tinhGiaThue()), 15);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(thongTinNguoiThue, 40);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────┴──────────────────────┴────────────┴───────────┴─────────────────┴─────────────────┴──────────────────────────────────────────┘\n";
        khoiPhucMau();
    }
    datMau(MAU_XAM_SANG, 0);
    cout << "  (Tổng số phòng: " << ds.size() << " phòng)\n";
    khoiPhucMau();
}

void hienThiBangPhongTro(const LinkedList<PhongTro*>& ds) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌──────┬──────────────────────┬────────────┬───────────┬─────────────────┬─────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ", 4);    cout << " │ ";
    inCanhTrai("TÊN PHÒNG", 20); cout << " │ ";
    inCanhTrai("TÌNH TRẠNG", 10); cout << " │ ";
    inCanhTrai("DIỆN TÍCH", 9);  cout << " │ ";
    inCanhPhai("GIÁ GỐC (VND)", 15); cout << " │ ";
    inCanhPhai("TỔNG GIÁ (VND)", 15);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├──────┼──────────────────────┼────────────┼───────────┼─────────────────┼─────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Danh sách phòng trọ hiện đang trống!", 88);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        for (PhongTro* pt : ds) {
            stt++;
            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(pt->getMaPhong()), 4);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(pt->getTenPhong(), 20);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";

            if (pt->getTinhTrang() == "Con trong") {
                datMau(MAU_XANH_LA_SANG, 0);
                inCanhTrai("Còn trống", 10);
            } else {
                datMau(MAU_VANG_CAM, 0);
                inCanhTrai("Đã thuê", 10);
            }

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(pt->getDienTichStr(), 9);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)pt->getGiaThue()), 15);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)pt->tinhGiaThue()), 15);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────┴──────────────────────┴────────────┴───────────┴─────────────────┴─────────────────┘\n";
        khoiPhucMau();
    }
    khoiPhucMau();
}

// ================================================================
//  2. BANG HIEN THI NGUOI THUE
// ================================================================
void hienThiBangNguoiThue(const LinkedList<NguoiThue*>& ds, const QuanLyHopDong& qlHopDong) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌──────┬────────────────────────────────┬────────────┬────────────────┬──────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ", 4); cout << " │ ";
    inCanhTrai("HỌ VÀ TÊN KHÁCH HÀNG", 30); cout << " │ ";
    inCanhTrai("NGÀY SINH", 10); cout << " │ ";
    inCanhTrai("SỐ ĐIỆN THOẠI", 14); cout << " │ ";
    inCanhTrai("PHÒNG ĐANG THUÊ", 20);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├──────┼────────────────────────────────┼────────────┼────────────────┼──────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Danh sách khách thuê hiện đang trống!", 90);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        for (NguoiThue* nt : ds) {
            stt++;
            int maP = qlHopDong.timMaPhongTheoNguoiThue(nt->getMaNguoiThue());
            string phongStr = (maP != 0) ? ("Phòng " + to_string(maP)) : "Chưa thuê phòng";

            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(nt->getMaNguoiThue()), 4);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(nt->getHoTen(), 30);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(nt->getNgaySinh().toString(), 10);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(nt->getSoDienThoai(), 14);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";

            if (maP != 0) {
                datMau(MAU_XANH_LA_SANG, 0);
            } else {
                datMau(MAU_XAM_SANG, 0);
            }
            inCanhTrai(phongStr, 20);

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────┴────────────────────────────────┴────────────┴────────────────┴──────────────────────┘\n";
        khoiPhucMau();
    }
    datMau(MAU_XAM_SANG, 0);
    cout << "  (Tổng số khách thuê: " << ds.size() << " người)\n";
    khoiPhucMau();
}

void hienThiBangNguoiThue(const LinkedList<NguoiThue*>& ds) {
    QuanLyHopDong dummyHD;
    hienThiBangNguoiThue(ds, dummyHD);
}

// ================================================================
//  3. BANG HIEN THI HOP DONG THUE
// ================================================================
void hienThiBangHopDong(const LinkedList<HopDongThue>& ds, const QuanLyNguoiThue& qlNguoiThue) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌────────┬──────────┬───────┬────────────────────────────────┬────────────┬───────────────┬─────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ HĐ", 6); cout << " │ ";
    inCanhTrai("MÃ PHÒNG", 8); cout << " │ ";
    inCanhTrai("MÃ NT", 5); cout << " │ ";
    inCanhTrai("HỌ VÀ TÊN NGƯỜI THUÊ", 30); cout << " │ ";
    inCanhTrai("NGÀY LẬP", 10); cout << " │ ";
    inCanhTrai("THỜI HẠN", 13); cout << " │ ";
    inCanhPhai("GIÁ THUÊ (VND)", 19);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├────────┼──────────┼───────┼────────────────────────────────┼────────────┼───────────────┼─────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Danh sách hợp đồng hiện đang trống!", 109);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└───────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        for (const HopDongThue& hd : ds) {
            stt++;
            string tenNT = "Chưa xác định";
            if (hd.getMaNguoiThue() != 0) {
                NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                if (nt != nullptr) tenNT = nt->getHoTen();
                else tenNT = "Ma NT: " + to_string(hd.getMaNguoiThue());
            }
            string th = to_string(hd.getThoiHan()) + " tháng";

            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaHopDong()), 6);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaPhong()), 8);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaNguoiThue()), 5);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(tenNT, 30);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(hd.getNgayLap().toString(), 10);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(th, 13);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)hd.getGiaThue()), 19);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└────────┴──────────┴───────┴────────────────────────────────┴────────────┴───────────────┴─────────────────────┘\n";
        khoiPhucMau();
    }
    datMau(MAU_XAM_SANG, 0);
    cout << "  (Tổng số hợp đồng: " << ds.size() << " hợp đồng)\n";
    khoiPhucMau();
}

void hienThiBangHopDong(const LinkedList<HopDongThue>& ds) {
    QuanLyNguoiThue dummyNT;
    hienThiBangHopDong(ds, dummyNT);
}

// ================================================================
//  4. BANG HIEN THI HOA DON THANH TOAN
// ================================================================
void hienThiBangHoaDon(const LinkedList<HoaDon>& ds, double tongDoanhThu, const QuanLyNguoiThue& qlNguoiThue) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌────────────┬──────────┬───────┬──────────────────────┬────────────┬─────────┬────────────────┬────────────────┬────────────────┬─────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ HÓA ĐƠN", 10); cout << " │ ";
    inCanhTrai("MÃ PHÒNG", 8);   cout << " │ ";
    inCanhTrai("MÃ NT", 5);      cout << " │ ";
    inCanhTrai("HỌ VÀ TÊN", 20); cout << " │ ";
    inCanhTrai("NGÀY LẬP", 10);  cout << " │ ";
    inCanhTrai("KỲ TT", 7);      cout << " │ ";
    inCanhPhai("TIỀN PHÒNG", 14); cout << " │ ";
    inCanhPhai("TIỀN ĐIỆN", 14);  cout << " │ ";
    inCanhPhai("TIỀN NƯỚC", 14);  cout << " │ ";
    inCanhPhai("TỔNG TIỀN (VND)", 19);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├────────────┼──────────┼───────┼──────────────────────┼────────────┼─────────┼────────────────┼────────────────┼────────────────┼─────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Danh sách hóa đơn hiện đang trống!", 148);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        for (const HoaDon& hd : ds) {
            stt++;
            string tenNT = "Chưa xác định";
            if (hd.getMaNguoiThue() != 0) {
                NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                if (nt != nullptr) tenNT = nt->getHoTen();
                else tenNT = "Ma NT: " + to_string(hd.getMaNguoiThue());
            }
            if (demKyTuHienThi(tenNT) > 20) {
                while (demKyTuHienThi(tenNT) > 17) tenNT.pop_back();
                tenNT += "...";
            }

            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(hd.getMaHoaDon(), 10);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaPhong()), 8);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaNguoiThue()), 5);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(tenNT, 20);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(hd.getNgayLap().toString(), 10);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_XANH_LA_SANG, 0);
            inCanhTrai(hd.getKyThanhToan(), 7);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhPhai(dinhDangTien((long long)hd.getTienPhong()), 14);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhPhai(dinhDangTien((long long)hd.getTienDien()), 14);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhPhai(dinhDangTien((long long)hd.getTienNuoc()), 14);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)hd.getTongTien()), 19);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }

        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "├────────────┴──────────┴───────┴──────────────────────┴────────────┴─────────┴────────────────┴────────────────┴────────────────┼─────────────────────┤\n";
        cout << "│ ";
        datMau(MAU_VANG_SANG, 0);
        inCanhTrai("TỔNG DOANH THU TOÀN BỘ HÓA ĐƠN", 126);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(MAU_VANG_SANG, 0);
        inCanhPhai(dinhDangTien((long long)tongDoanhThu), 19);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │\n";
        cout << "└────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┴─────────────────────┘\n";
        khoiPhucMau();
    }
    datMau(MAU_XAM_SANG, 0);
    cout << "  (Tổng số hóa đơn: " << ds.size() << " hóa đơn)\n";
    khoiPhucMau();
}

void hienThiBangHoaDon(const LinkedList<HoaDon>& ds, double tongDoanhThu) {
    QuanLyNguoiThue dummyNT;
    hienThiBangHoaDon(ds, tongDoanhThu, dummyNT);
}

// ================================================================
//  5. BANG DANH SACH KHACH CHUA DONG TIEN
// ================================================================
struct ThongTinChuaDongTien {
    int maNguoiThue;
    string hoTen;
    string soDienThoai;
    int maPhong;
    string tenPhong;
    double tienCanDong;
};

void hienThiBangKhachChuaDongTien(const LinkedList<ThongTinChuaDongTien>& ds, int thang, int nam) {
    cout << "\n";
    datMau(MAU_DO_SANG, 0);
    cout << "┌──────┬──────────────────────┬────────────────┬──────────┬──────────────────────┬──────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ", 4);              cout << " │ ";
    inCanhTrai("HỌ VÀ TÊN KHÁCH", 20); cout << " │ ";
    inCanhTrai("SỐ ĐIỆN THOẠI", 14);  cout << " │ ";
    inCanhTrai("MÃ PHÒNG", 8);        cout << " │ ";
    inCanhTrai("TÊN PHÒNG", 20);      cout << " │ ";
    inCanhPhai("TIỀN CẦN ĐÓNG (VND)", 20);
    datMau(MAU_DO_SANG, 0);
    cout << " │\n";
    cout << "├──────┼──────────────────────┼────────────────┼──────────┼──────────────────────┼──────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XANH_LA_SANG, 0);
        cout << "│ ";
        inCanhTrai("✔ Tất cả khách hàng đều đã hoàn tất đóng tiền phòng tháng này!", 101);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_DO_SANG, 0);
        cout << "└───────────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        double tongNo = 0.0;
        for (const auto& item : ds) {
            stt++;
            tongNo += item.tienCanDong;
            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_DO_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(item.maNguoiThue), 4);
            datMau(MAU_DO_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(item.hoTen, 20);
            datMau(MAU_DO_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(item.soDienThoai, 14);
            datMau(MAU_DO_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(item.maPhong), 8);
            datMau(MAU_DO_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(item.tenPhong, 20);
            datMau(MAU_DO_SANG, 0);
            cout << " │ ";
            datMau(MAU_DO_SANG, 0);
            inCanhPhai(dinhDangTien((long long)item.tienCanDong), 20);
            datMau(MAU_DO_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }

        datMau(MAU_DO_SANG, 0);
        cout << "├──────┴──────────────────────┴────────────────┴──────────┴──────────────────────┼──────────────────────┤\n";
        cout << "│ ";
        datMau(MAU_VANG_SANG, 0);
        string tieuDeNo = "TỔNG TIỀN PHÒNG CÒN NỢ THÁNG " + to_string(thang) + "/" + to_string(nam);
        inCanhTrai(tieuDeNo, 78);
        datMau(MAU_DO_SANG, 0);
        cout << " │ ";
        datMau(MAU_DO_SANG, 0);
        inCanhPhai(dinhDangTien((long long)tongNo), 20);
        datMau(MAU_DO_SANG, 0);
        cout << " │\n";
        cout << "└────────────────────────────────────────────────────────────────────────────────┴──────────────────────┘\n";
        khoiPhucMau();
    }
}

// ================================================================
//  6. BAO CAO DOANH THU THANG (THE THE DANG HOP THOAI CARD)
// ================================================================
void hienThiThongKeDoanhThuThang(int thang, int nam, double tongPhong, double tongDien, double tongNuoc, double tongCong) {
    cout << "\n";
    int innerWidth = 76;
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ╔";
    for (int i = 0; i < innerWidth; ++i) cout << "═";
    cout << "╗\n";

    cout << "  ║ ";
    string titleCard = "BÁO CÁO DOANH THU THÁNG " + (thang < 10 ? string("0") : string("")) + to_string(thang) + "/" + to_string(nam);
    inCanGiua(titleCard, innerWidth - 2, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";

    cout << "  ╠";
    for (int i = 0; i < innerWidth; ++i) cout << "═";
    cout << "╣\n";

    // Hang 1
    cout << "  ║  ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai("1. Doanh thu tiền phòng trọ :", 32);
    datMau(MAU_VANG_SANG, 0);
    inCanhPhai(dinhDangTien((long long)tongPhong) + " VND", 38);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ║\n";

    // Hang 2
    cout << "  ║  ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai("2. Doanh thu tiền điện       :", 32);
    datMau(MAU_VANG_SANG, 0);
    inCanhPhai(dinhDangTien((long long)tongDien) + " VND", 38);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ║\n";

    // Hang 3
    cout << "  ║  ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai("3. Doanh thu tiền nước       :", 32);
    datMau(MAU_VANG_SANG, 0);
    inCanhPhai(dinhDangTien((long long)tongNuoc) + " VND", 38);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ║\n";

    cout << "  ╠";
    for (int i = 0; i < innerWidth; ++i) cout << "═";
    cout << "╣\n";

    // Hang Tong
    cout << "  ║  ";
    datMau(MAU_XANH_LA_SANG, 0);
    inCanhTrai("➔ TỔNG CỘNG DOANH THU THÁNG :", 32);
    datMau(MAU_XANH_LA_SANG, 0);
    inCanhPhai(dinhDangTien((long long)tongCong) + " VND", 38);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ║\n";

    cout << "  ╚";
    for (int i = 0; i < innerWidth; ++i) cout << "═";
    cout << "╝\n";
    khoiPhucMau();
}

// ================================================================
//  7. BANG PHONG CO TIEN DIEN CAO
// ================================================================
void hienThiBangTienDienCao(const LinkedList<HoaDon>& ds, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, double mucTien) {
    (void)mucTien;
    cout << "\n";
    datMau(MAU_VANG_CAM, 0);
    cout << "┌────────────┬──────────┬──────────────────────┬───────┬──────────────────────┬────────────┬─────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ HÓA ĐƠN", 10); cout << " │ ";
    inCanhTrai("MÃ PHÒNG", 8);   cout << " │ ";
    inCanhTrai("TÊN PHÒNG", 20);  cout << " │ ";
    inCanhTrai("MÃ NT", 5);       cout << " │ ";
    inCanhTrai("NGƯỜI THUÊ", 20); cout << " │ ";
    inCanhTrai("NGÀY LẬP", 10);   cout << " │ ";
    inCanhPhai("TIỀN ĐIỆN (VND)", 19);
    datMau(MAU_VANG_CAM, 0);
    cout << " │\n";
    cout << "├────────────┼──────────┼──────────────────────┼───────┼──────────────────────┼────────────┼─────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Không có phòng nào có tiền điện cao hơn mức quy định!", 110);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_VANG_CAM, 0);
        cout << "└────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int stt = 0;
        for (const HoaDon& hd : ds) {
            stt++;
            string tenP = "Phòng " + to_string(hd.getMaPhong());
            PhongTro* pt = qlPhong.timKiemPhongTro(hd.getMaPhong());
            if (pt != nullptr) tenP = pt->getTenPhong();
            if (demKyTuHienThi(tenP) > 20) {
                while (demKyTuHienThi(tenP) > 17) tenP.pop_back();
                tenP += "...";
            }

            string tenNT = "Chưa xác định";
            NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
            if (nt != nullptr) tenNT = nt->getHoTen();
            if (demKyTuHienThi(tenNT) > 20) {
                while (demKyTuHienThi(tenNT) > 17) tenNT.pop_back();
                tenNT += "...";
            }

            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_VANG_CAM, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(hd.getMaHoaDon(), 10);
            datMau(MAU_VANG_CAM, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaPhong()), 8);
            datMau(MAU_VANG_CAM, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(tenP, 20);
            datMau(MAU_VANG_CAM, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(hd.getMaNguoiThue()), 5);
            datMau(MAU_VANG_CAM, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(tenNT, 20);
            datMau(MAU_VANG_CAM, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(hd.getNgayLap().toString(), 10);
            datMau(MAU_VANG_CAM, 0);
            cout << " │ ";
            datMau(MAU_DO_SANG, 0);
            inCanhPhai(dinhDangTien((long long)hd.getTienDien()), 19);
            datMau(MAU_VANG_CAM, 0);
            cout << " │\n";
            khoiPhucMau();
        }
        datMau(MAU_VANG_CAM, 0);
        cout << "└────────────┴──────────┴──────────────────────┴───────┴──────────────────────┴────────────┴─────────────────────┘\n";
        khoiPhucMau();
    }
}

// ================================================================
//  8. SO THEO DOI THANH TOAN TUNG THANG CUA PHONG
// ================================================================
void hienThiSoTheoDoiThanhToanPhong(int maPhong, const string& tenPhong, const string& tenNT, const string& sdtNT,
                                   const HopDongThue& hd, const QuanLyHoaDon& qlHoaDon,
                                   int thangHienTai, int namHienTai) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ ";
    datMau(MAU_VANG_SANG, 0);
    string titleSo = "SỔ THEO DÕI THANH TOÁN TỪNG THÁNG - MÃ PHÒNG: " + to_string(maPhong) + " (" + tenPhong + ")";
    inCanGiua(titleSo, 135, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ ";
    datMau(MAU_TRANG_SANG, 0);
    string thongTinNT = "Người thuê : " + tenNT + " (Mã NT: " + to_string(hd.getMaNguoiThue()) + ") - SĐT: " + sdtNT;
    inCanhTrai(thongTinNT, 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "║ ";
    datMau(MAU_TRANG_SANG, 0);
    string thongTinHD = "Hợp đồng   : Mã HĐ: " + to_string(hd.getMaHopDong()) + " | Bắt đầu: " + hd.getNgayLap().toString() + 
                        " | Thời hạn: " + to_string(hd.getThoiHan()) + " tháng | Giá thuê: " + dinhDangTien((long long)hd.getGiaThue()) + " VND/tháng";
    inCanhTrai(thongTinHD, 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "║ ";
    datMau(MAU_VANG_SANG, 0);
    string thongTinMoc = "Mốc tra cứu: Tháng " + (thangHienTai < 10 ? string("0") : string("")) + to_string(thangHienTai) + "/" + to_string(namHienTai);
    inCanhTrai(thongTinMoc, 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌─────┬─────────┬──────────────────────┬────────────┬────────────┬────────────────┬────────────────┬────────────────┬─────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("STT", 3);        cout << " │ ";
    inCanhTrai("KỲ TT", 7);      cout << " │ ";
    inCanhTrai("TRẠNG THÁI", 20); cout << " │ ";
    inCanhTrai("MÃ HÓA ĐƠN", 10); cout << " │ ";
    inCanhTrai("NGÀY TT", 10);   cout << " │ ";
    inCanhPhai("TIỀN PHÒNG", 14); cout << " │ ";
    inCanhPhai("TIỀN ĐIỆN", 14);  cout << " │ ";
    inCanhPhai("TIỀN NƯỚC", 14);  cout << " │ ";
    inCanhPhai("TỔNG TIỀN (VND)", 19);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├─────┼─────────┼──────────────────────┼────────────┼────────────┼────────────────┼────────────────┼────────────────┼─────────────────────┤\n";
    khoiPhucMau();

    int startM = hd.getNgayLap().getThang();
    int startY = hd.getNgayLap().getNam();
    int thoiHan = hd.getThoiHan();

    int soThangDaTra = 0;
    int soThangNo = 0;
    int soThangChuaDen = 0;
    double tongTienDaThu = 0.0;
    double tongTienConNo = 0.0;

    for (int i = 0; i < thoiHan; ++i) {
        int curM = (startM - 1 + i) % 12 + 1;
        int curY = startY + (startM - 1 + i) / 12;

        string kyStr = (curM < 10 ? "0" : "") + to_string(curM) + "/" + to_string(curY);

        HoaDon bill = qlHoaDon.timHoaDonTheoKy(maPhong, curM, curY);

        string trangThai = "";
        int mauTrangThai = MAU_TRANG_SANG;
        string maHD = "---";
        string ngayTT = "---";
        double tPhong = 0.0;
        double tDien = 0.0;
        double tNuoc = 0.0;
        double tTong = 0.0;

        if (bill.getMaHoaDon() != "") {
            trangThai = "[✓ ĐÃ THANH TOÁN]";
            mauTrangThai = MAU_XANH_LA_SANG;
            maHD = bill.getMaHoaDon();
            ngayTT = bill.getNgayLap().toString();
            tPhong = bill.getTienPhong();
            tDien = bill.getTienDien();
            tNuoc = bill.getTienNuoc();
            tTong = bill.getTongTien();

            soThangDaTra++;
            tongTienDaThu += tTong;
        } else {
            bool daDenKy = (curY < namHienTai) || (curY == namHienTai && curM <= thangHienTai);
            tPhong = hd.getGiaThue();
            tTong = tPhong;

            if (daDenKy) {
                trangThai = "[✗ CHƯA TRẢ - NỢ]";
                mauTrangThai = MAU_DO_SANG;
                soThangNo++;
                tongTienConNo += tPhong;
            } else {
                trangThai = "[CHƯA ĐẾN KỲ]";
                mauTrangThai = MAU_XAM_SANG;
                soThangChuaDen++;
            }
        }

        int mauChu = (i % 2 == 0) ? MAU_TRANG_SANG : MAU_XAM_SANG;

        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "│ ";
        datMau(mauChu, 0);
        inCanhTrai(to_string(i + 1), 3);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauChu, 0);
        inCanhTrai(kyStr, 7);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauTrangThai, 0);
        inCanhTrai(trangThai, 20);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauChu, 0);
        inCanhTrai(maHD, 10);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauChu, 0);
        inCanhTrai(ngayTT, 10);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauChu, 0);
        inCanhPhai(dinhDangTien((long long)tPhong), 14);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauChu, 0);
        inCanhPhai(dinhDangTien((long long)tDien), 14);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(mauChu, 0);
        inCanhPhai(dinhDangTien((long long)tNuoc), 14);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │ ";
        datMau(MAU_VANG_SANG, 0);
        inCanhPhai(dinhDangTien((long long)tTong), 19);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " │\n";
        khoiPhucMau();
    }

    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "└─────┴─────────┴──────────────────────┴────────────┴────────────┴────────────────┴────────────────┴────────────────┴─────────────────────┘\n";

    // Tong ket (dong bo kich thuoc voi bang va the tieu de)
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("[TỔNG KẾT THANH TOÁN CỦA PHÒNG]:", 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "╠═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ ";
    datMau(MAU_XANH_LA_SANG, 0);
    string strDaThu = "✔ Số tháng ĐÃ THANH TOÁN : " + to_string(soThangDaTra) + " tháng | Tổng tiền đã thu : " + dinhDangTien((long long)tongTienDaThu) + " VND";
    inCanhTrai(strDaThu, 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "║ ";
    datMau(MAU_DO_SANG, 0);
    string strConNo = "✖ Số tháng CHƯA TRẢ (NỢ) : " + to_string(soThangNo) + " tháng | Tiền phòng còn nợ: " + dinhDangTien((long long)tongTienConNo) + " VND";
    inCanhTrai(strConNo, 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "║ ";
    datMau(MAU_XAM_SANG, 0);
    string strChuaDen = "ℹ Số tháng CHƯA ĐẾN KỲ   : " + to_string(soThangChuaDen) + " tháng";
    inCanhTrai(strChuaDen, 135);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " ║\n";
    cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
    khoiPhucMau();
}

// ================================================================
//  9. BANG TINH TRANG THANH TOAN TAT CA CAC PHONG TRONG THANG
// ================================================================
struct ThongTinTinhTrangPhongThang {
    int maPhong;
    string tenPhong;
    int maNT;
    string tenNT;
    string sdtNT;
    bool daThanhToan;
    string maHoaDon;
    Date ngayThanhToan;
    double soTien;
};

void hienThiBangTinhTrangThanhToanCacPhong(const LinkedList<ThongTinTinhTrangPhongThang>& ds, int thang, int nam) {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "┌──────────┬──────────────────────┬───────┬──────────────────────┬────────────────┬──────────────────────┬────────────┬────────────┬─────────────────────┐\n";
    cout << "│ ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai("MÃ PHÒNG", 8);   cout << " │ ";
    inCanhTrai("TÊN PHÒNG", 20);  cout << " │ ";
    inCanhTrai("MÃ NT", 5);       cout << " │ ";
    inCanhTrai("HỌ VÀ TÊN", 20);  cout << " │ ";
    inCanhTrai("SỐ ĐIỆN THOẠI", 14); cout << " │ ";
    inCanhTrai("TRẠNG THÁI", 20); cout << " │ ";
    inCanhTrai("MÃ HÓA ĐƠN", 10); cout << " │ ";
    inCanhTrai("NGÀY TT", 10);    cout << " │ ";
    inCanhPhai("SỐ TIỀN (VND)", 19);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "├──────────┼──────────────────────┼───────┼──────────────────────┼────────────────┼──────────────────────┼────────────┼────────────┼─────────────────────┤\n";
    khoiPhucMau();

    if (ds.empty()) {
        datMau(MAU_XAM_SANG, 0);
        cout << "│ ";
        inCanhTrai("Không có phòng nào đang được thuê trong hệ thống!", 150);
        cout << " │\n";
        khoiPhucMau();
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n";
        khoiPhucMau();
    } else {
        int soPhongDaThu = 0;
        int soPhongChuaThu = 0;
        double tongDaThu = 0.0;
        double tongConNo = 0.0;
        int stt = 0;

        for (const auto& item : ds) {
            stt++;
            string trangThaiStr = item.daThanhToan ? "[✓ ĐÃ THANH TOÁN]" : "[✗ CHƯA TRẢ - NỢ]";
            int mauTrangThai = item.daThanhToan ? MAU_XANH_LA_SANG : MAU_DO_SANG;
            string maHDStr = item.daThanhToan ? item.maHoaDon : "---";
            string ngayTTStr = item.daThanhToan ? item.ngayThanhToan.toString() : "---";

            if (item.daThanhToan) {
                soPhongDaThu++;
                tongDaThu += item.soTien;
            } else {
                soPhongChuaThu++;
                tongConNo += item.soTien;
            }

            int mauChu = (stt % 2 == 1) ? MAU_TRANG_SANG : MAU_XAM_SANG;

            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << "│ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(item.maPhong), 8);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(item.tenPhong, 20);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(to_string(item.maNT), 5);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(item.tenNT, 20);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(item.sdtNT, 14);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauTrangThai, 0);
            inCanhTrai(trangThaiStr, 20);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(maHDStr, 10);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(mauChu, 0);
            inCanhTrai(ngayTTStr, 10);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │ ";
            datMau(MAU_VANG_SANG, 0);
            inCanhPhai(dinhDangTien((long long)item.soTien), 19);
            datMau(MAU_XANH_NGOC_SANG, 0);
            cout << " │\n";
            khoiPhucMau();
        }

        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "└──────────┴──────────────────────┴───────┴──────────────────────┴────────────────┴──────────────────────┴────────────┴────────────┴─────────────────────┘\n";

        cout << "\n";
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║ ";
        datMau(MAU_VANG_SANG, 0);
        string headerCongNo = "[TỔNG HỢP CÔNG NỢ THÁNG " + (thang < 10 ? string("0") : string("")) + to_string(thang) + "/" + to_string(nam) + "]:";
        inCanhTrai(headerCongNo, 150);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " ║\n";
        cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n";
        cout << "║ ";
        datMau(MAU_TRANG_SANG, 0);
        string strSoP = "- Tổng số phòng đang thuê: " + to_string(ds.size()) + " phòng";
        inCanhTrai(strSoP, 150);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " ║\n";
        cout << "║ ";
        datMau(MAU_XANH_LA_SANG, 0);
        string strDaDong = "✔ Số phòng ĐÃ ĐÓNG TIỀN  : " + to_string(soPhongDaThu) + " phòng | Tổng tiền đã thu : " + dinhDangTien((long long)tongDaThu) + " VND";
        inCanhTrai(strDaDong, 150);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " ║\n";
        cout << "║ ";
        datMau(MAU_DO_SANG, 0);
        string strConNo = "✖ Số phòng CÒN NỢ TIỀN   : " + to_string(soPhongChuaThu) + " phòng | Tổng tiền còn nợ : " + dinhDangTien((long long)tongConNo) + " VND";
        inCanhTrai(strConNo, 150);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << " ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        khoiPhucMau();
    }
}

// ================================================================
//  10. IN THONG TIN DANG THE CARD (PHIEU IN / BIEN LAI DO HOA)
// ================================================================

// In card chi tiet mot phong tro
void inCardPhongTro(const PhongTro* pt) {
    if (pt == nullptr) return;
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
    cout << "  │ ";
    datMau(MAU_VANG_SANG, 0);
    inCanGiua("THÔNG TIN CHI TIẾT PHÒNG TRỌ", 59, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Mã phòng    : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(to_string(pt->getMaPhong()), 44);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Tên phòng   : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(pt->getTenPhong(), 44);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Tình trạng  : ";
    if (pt->getTinhTrang() == "Con trong") {
        datMau(MAU_XANH_LA_SANG, 0);
        inCanhTrai("Còn trống (Chưa có người thuê)", 44);
    } else {
        datMau(MAU_VANG_CAM, 0);
        inCanhTrai("Đã thuê (Đang có người thuê)", 44);
    }
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Diện tích   : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(pt->getDienTichStr(), 44);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Giá thuê gốc: ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai(dinhDangTien((long long)pt->getGiaThue()) + " VND", 44);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Tổng giá    : ";
    datMau(MAU_XANH_LA_SANG, 0);
    inCanhTrai(dinhDangTien((long long)pt->tinhGiaThue()) + " VND", 44);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  └─────────────────────────────────────────────────────────────┘\n";
    khoiPhucMau();
}

// In card chi tiet mot nguoi thue
void inCardNguoiThue(const NguoiThue* nt) {
    if (nt == nullptr) return;
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
    cout << "  │ ";
    datMau(MAU_VANG_SANG, 0);
    inCanGiua("THÔNG TIN KHÁCH HÀNG (NGƯỜI THUÊ)", 59, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Mã khách hàng: ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(to_string(nt->getMaNguoiThue()), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Họ và tên    : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(nt->getHoTen(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Ngày sinh    : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(nt->getNgaySinh().toString(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Số điện thoại: ";
    datMau(MAU_XANH_LA_SANG, 0);
    inCanhTrai(nt->getSoDienThoai(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  └─────────────────────────────────────────────────────────────┘\n";
    khoiPhucMau();
}

// In card chi tiet mot hop dong
void inCardHopDong(const HopDongThue& hd, const string& tenNT = "") {
    if (hd.getMaHopDong() == 0) return;
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
    cout << "  │ ";
    datMau(MAU_VANG_SANG, 0);
    inCanGiua("THÔNG TIN HỢP ĐỒNG THUÊ PHÒNG", 59, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Mã hợp đồng  : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(to_string(hd.getMaHopDong()), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Mã phòng     : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(to_string(hd.getMaPhong()), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Người thuê   : ";
    datMau(MAU_TRANG_SANG, 0);
    string ntStr = (tenNT.empty() ? "" : (tenNT + " ")) + "(Mã: " + to_string(hd.getMaNguoiThue()) + ")";
    inCanhTrai(ntStr, 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Ngày bắt đầu : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(hd.getNgayLap().toString(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Ngày kết thúc: ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(hd.getNgayKetThuc().toString(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Thời hạn thuê: ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(to_string(hd.getThoiHan()) + " tháng", 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Giá thuê     : ";
    datMau(MAU_VANG_SANG, 0);
    inCanhTrai(dinhDangTien((long long)hd.getGiaThue()) + " VND/tháng", 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  └─────────────────────────────────────────────────────────────┘\n";
    khoiPhucMau();
}

// In phieu thu hoa don chi tiet dang bien lai giay
void inPhieuThuHoaDon(const HoaDon& hd, const string& tenPhong = "", const string& tenNT = "") {
    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ┌─────────────────────────────────────────────────────────────┐\n";
    cout << "  │ ";
    datMau(MAU_VANG_SANG, 0);
    inCanGiua("PHIẾU THU TIỀN PHÒNG TRỌ", 59, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │ ";
    string subH = "MÃ HÓA ĐƠN: " + hd.getMaHoaDon();
    inCanGiua(subH, 59, MAU_TRANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << "  │  Phòng trọ    : ";
    datMau(MAU_TRANG_SANG, 0);
    string pStr = (tenPhong.empty() ? ("Phòng " + to_string(hd.getMaPhong())) : tenPhong) + " (Mã: " + to_string(hd.getMaPhong()) + ")";
    inCanhTrai(pStr, 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Khách thuê   : ";
    datMau(MAU_TRANG_SANG, 0);
    string ntStr = (tenNT.empty() ? ("Mã NT: " + to_string(hd.getMaNguoiThue())) : (tenNT + " (Mã: " + to_string(hd.getMaNguoiThue()) + ")"));
    inCanhTrai(ntStr, 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Kỳ thanh toán: ";
    datMau(MAU_XANH_LA_SANG, 0);
    inCanhTrai(hd.getKyThanhToan(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  Ngày lập HĐ  : ";
    datMau(MAU_TRANG_SANG, 0);
    inCanhTrai(hd.getNgayLap().toString(), 43);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << "  │  1. Tiền phòng : ";
    datMau(MAU_VANG_SANG, 0);
    inCanhPhai(dinhDangTien((long long)hd.getTienPhong()) + " VND", 42);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  2. Tiền điện  : ";
    datMau(MAU_VANG_SANG, 0);
    inCanhPhai(dinhDangTien((long long)hd.getTienDien()) + " VND", 42);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  │  3. Tiền nước  : ";
    datMau(MAU_VANG_SANG, 0);
    inCanhPhai(dinhDangTien((long long)hd.getTienNuoc()) + " VND", 42);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  ├─────────────────────────────────────────────────────────────┤\n";
    cout << "  │ ";
    datMau(MAU_XANH_LA_SANG, 0);
    cout << " ➔ TỔNG TIỀN PHẢI NỘP : ";
    inCanhPhai(dinhDangTien((long long)hd.getTongTien()) + " VND", 36);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << " │\n";
    cout << "  └─────────────────────────────────────────────────────────────┘\n";
    khoiPhucMau();
}
