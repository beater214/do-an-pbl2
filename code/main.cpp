#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;

// Nap cac file header theo dung thu tu phu thuoc (khong dung ifndef hay pragma once)
#include "DinhNghia.h"
#include "LinkedList.h"
#include "Date.h"
#include "PhongTro.h"
#include "NguoiThue.h"
#include "HopDongThue.h"
#include "HoaDon.h"
#include "QuanLyPhong.h"
#include "QuanLyNguoiThue.h"
#include "QuanLyHopDong.h"
#include "QuanLyHoaDon.h"
#include "DocGhiFile.h"
#include "DoHoa.h"
#include "GiaoDien.h"
#include "Menu.h"

// ================================================================
//  MAIN
// ================================================================
int main() {
    caiDatConsole();

    QuanLyPhong qlPhong;
    QuanLyNguoiThue qlNguoiThue;
    QuanLyHopDong qlHopDong;
    QuanLyHoaDon qlHoaDon;

    // 1. Tu dong doc du lieu tu folder data/ khi bat chuong trinh
    string dirData = timDuongDanThuMucData();
    bool daDocThanhCong = docTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData);

    // Neu chua co du lieu (chay lan dau), khoi tao du lieu mau va ghi ra file
    if (!daDocThanhCong || qlPhong.layDanhSachPhong().empty()) {
        khoiTaoDuLieuMau(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
    }

    const MucLuaChon dsMenuChinh[] = {
        {1, "[1]  Quan ly danh sach phong tro (Kem thong tin khach)", ""},
        {2, "[2]  Quan ly danh sach nguoi thue (Khach hang)", ""},
        {3, "[3]  Quan ly hop dong thue (Lien ket phong & nguoi thue)", ""},
        {4, "[4]  Quan ly hoa don thanh toan (Ky thanh toan & cong no)", ""},
        {5, "[5]  Luu toan bo du lieu ra file txt (Thu cong)", ""},
        {6, "[6]  Nap lai du lieu tu file txt", ""},
        {7, "[7]  Xoa man hinh console (Clear)", ""},
        {0, "[0]  Thoat chuong trinh (Tu dong luu du lieu)", ""}
    };
    int soMuc = sizeof(dsMenuChinh) / sizeof(dsMenuChinh[0]);

    int luaChonChinh = -1;
    while (luaChonChinh != 0) {
        xoaManHinh();
        veBannerPBL2(
            qlPhong.layDanhSachPhong().size(),
            qlNguoiThue.layDanhSachNguoiThue().size(),
            qlHopDong.layDanhSachHopDong().size(),
            qlHoaDon.layDanhSachHoaDon().size()
        );

        luaChonChinh = menuDieuHuongDong("HỆ THỐNG QUẢN LÝ PHÒNG TRỌ - MENU CHÍNH", dsMenuChinh, soMuc, 12, -1, 84);

        switch (luaChonChinh) {
            case 1:
                menuPhongTro(qlPhong, qlHopDong, qlNguoiThue, qlHoaDon);
                break;
            case 2:
                menuNguoiThue(qlNguoiThue, qlHopDong, qlPhong, qlHoaDon);
                break;
            case 3:
                menuHopDong(qlHopDong, qlPhong, qlNguoiThue, qlHoaDon);
                break;
            case 4:
                menuHoaDon(qlHoaDon, qlPhong, qlNguoiThue, qlHopDong);
                break;
            case 5:
                xoaManHinh();
                if (luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData)) {
                    inThongBaoThanhCong("Da luu toan bo du lieu ra cac file txt trong " + dirData);
                } else {
                    inThongBaoLoi("Loi khi ghi du lieu ra file!");
                }
                dungManHinh();
                break;
            case 6:
                xoaManHinh();
                if (docTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData)) {
                    inThongBaoThanhCong("Da nap lai toan bo du lieu thanh cong tu " + dirData);
                } else {
                    inThongBaoLoi("Khong the doc du lieu tu file!");
                }
                dungManHinh();
                break;
            case 7:
                xoaManHinh();
                break;
            case 0:
                // Tu dong luu toan bo du lieu truoc khi ket thuc chuong trinh
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData);
                xoaManHinh();
                cout << "\n";
                datMau(MAU_XANH_LA_SANG, 0);
                cout << "  ╔═══════════════════════════════════════════════════════════════════════════╗\n";
                cout << "  ║     [✔] ĐÃ TỰ ĐỘNG LƯU TOÀN BỘ DỮ LIỆU AN TOÀN VÀO THƯ MỤC DATA!          ║\n";
                cout << "  ║             CẢM ƠN BẠN ĐÃ SỬ DỤNG CHƯƠNG TRÌNH! TẠM BIỆT!                 ║\n";
                cout << "  ╚═══════════════════════════════════════════════════════════════════════════╝\n\n";
                khoiPhucMau();
                break;
            default:
                break;
        }
    }

    return 0;
}
