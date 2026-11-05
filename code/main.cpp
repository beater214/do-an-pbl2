#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

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
#include "GiaoDien.h"
#include "Menu.h"

// ================================================================
//  MAIN
// ================================================================
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

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

    cout << "\n[+] Da ket noi va nap du lieu thanh cong tu thu muc: " << dirData << "\n";
    cout << "    + Phong tro : " << qlPhong.layDanhSachPhong().size() << " phong\n";
    cout << "    + Nguoi thue: " << qlNguoiThue.layDanhSachNguoiThue().size() << " nguoi\n";
    cout << "    + Hop dong  : " << qlHopDong.layDanhSachHopDong().size() << " hop dong\n";
    cout << "    + Hoa don   : " << qlHoaDon.layDanhSachHoaDon().size() << " hoa don\n";

    int luaChonChinh = -1;
    while (luaChonChinh != 0) {
        cout << "\n";
        cout << "===============================================================\n";
        cout << "|              HE THONG QUAN LY PHONG TRO (PBL2)              |\n";
        cout << "|           KHOA CONG NGHE THONG TIN - DH BACH KHOA           |\n";
        cout << "===============================================================\n";
        cout << "|                                                             |\n";
        cout << "|   [1]  Quan ly danh sach phong tro (Kem thong tin khach)    |\n";
        cout << "|   [2]  Quan ly danh sach nguoi thue                         |\n";
        cout << "|   [3]  Quan ly hop dong thue (Lien ket phong & nguoi thue)  |\n";
        cout << "|   [4]  Quan ly hoa don thanh toan (Ky thanh toan & cong no) |\n";
        cout << "|   [5]  Luu toan bo du lieu ra file txt (Thu cong)           |\n";
        cout << "|   [6]  Nap lai du lieu tu file txt                          |\n";
        cout << "|   [7]  Xoa man hinh console (Clear)                         |\n";
        cout << "|   [0]  Thoat chuong trinh (Tu dong luu du lieu)             |\n";
        cout << "|                                                             |\n";
        cout << "===============================================================\n";
        cout << ">> Nhap lua chon cua ban [0-7]: ";
        if (!(cin >> luaChonChinh)) { xoaBoDem(); continue; }

        switch (luaChonChinh) {
            case 1:
                xoaManHinh();
                menuPhongTro(qlPhong, qlHopDong, qlNguoiThue, qlHoaDon);
                xoaManHinh();
                break;
            case 2:
                xoaManHinh();
                menuNguoiThue(qlNguoiThue, qlHopDong, qlPhong, qlHoaDon);
                xoaManHinh();
                break;
            case 3:
                xoaManHinh();
                menuHopDong(qlHopDong, qlPhong, qlNguoiThue, qlHoaDon);
                xoaManHinh();
                break;
            case 4:
                xoaManHinh();
                menuHoaDon(qlHoaDon, qlPhong, qlNguoiThue, qlHopDong);
                xoaManHinh();
                break;
            case 5:
                if (luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData)) {
                    inThongBaoThanhCong("Da luu toan bo du lieu ra cac file txt trong " + dirData);
                } else {
                    inThongBaoLoi("Loi khi ghi du lieu ra file!");
                }
                break;
            case 6:
                if (docTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData)) {
                    inThongBaoThanhCong("Da nap lai toan bo du lieu thanh cong tu " + dirData);
                } else {
                    inThongBaoLoi("Khong the doc du lieu tu file!");
                }
                break;
            case 7:
                xoaManHinh();
                break;
            case 0:
                // Tu dong luu toan bo du lieu truoc khi ket thuc chuong trinh
                luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon, dirData);
                cout << "\n===============================================================\n";
                cout << "| [+] DA TU DONG LUU TOAN BO DU LIEU VAO FOLDER DATA!         |\n";
                cout << "|         CAM ON BAN DA SU DUNG CHUONG TRINH! TAM BIET!       |\n";
                cout << "===============================================================\n\n";
                break;
            default:
                inThongBaoLoi("Lua chon khong hop le, vui long chon lai!");
                break;
        }
    }

    return 0;
}
