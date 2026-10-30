#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

// ================================================================
//  HAM TIEN ICH & GIAO DIEN BANG
// ================================================================
void xoaManHinh() {
    system("cls");
}

void xoaBoDem() {
    cin.clear();
    string rac;
    getline(cin, rac);
}

void inThongBaoThanhCong(const string& msg) {
    cout << "\n[+] " << msg << "\n";
}

void inThongBaoLoi(const string& msg) {
    cout << "\n[-] " << msg << "\n";
}

void hienThiBangPhongTro(const LinkedList<PhongTro*>& ds, const QuanLyHopDong& qlHopDong, const QuanLyNguoiThue& qlNguoiThue) {
    cout << "\n+------+----------------------+------------+-----------+---------------+---------------+------------------------------------------+\n";
    cout << "| " << left << setw(4) << "MA"
         << " | " << left << setw(20) << "TEN PHONG"
         << " | " << left << setw(10) << "TINH TRANG"
         << " | " << left << setw(9) << "DIEN TICH"
         << " | " << right << setw(13) << "GIA GOC (VND)"
         << " | " << right << setw(13) << "TONG GIA (VND)"
         << " | " << left << setw(40) << "NGUOI THUE (MA - HO TEN - SDT)" << " |\n";
    cout << "+------+----------------------+------------+-----------+---------------+---------------+------------------------------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(122) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (PhongTro* pt : ds) {
            string thongTinNguoiThue = "--- (Con trong) ---";
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
                    thongTinNguoiThue = "Chua cap nhat nguoi thue";
                }
            }

            cout << "| " << left << setw(4) << pt->getMaPhong()
                 << " | " << left << setw(20) << pt->getTenPhong()
                 << " | " << left << setw(10) << pt->getTinhTrang()
                 << " | " << left << setw(9) << pt->getDienTichStr()
                 << " | " << right << setw(13) << (long long)pt->getGiaThue()
                 << " | " << right << setw(13) << (long long)pt->tinhGiaThue()
                 << " | " << left << setw(40) << thongTinNguoiThue << " |\n";
        }
    }
    cout << "+------+----------------------+------------+-----------+---------------+---------------+------------------------------------------+\n";
}

// Giu ham cu de tuong thich neu can
void hienThiBangPhongTro(const LinkedList<PhongTro*>& ds) {
    cout << "\n+------+----------------------+------------+-----------+---------------+---------------+\n";
    cout << "| " << left << setw(4) << "MA"
         << " | " << left << setw(20) << "TEN PHONG"
         << " | " << left << setw(10) << "TINH TRANG"
         << " | " << left << setw(9) << "DIEN TICH"
         << " | " << right << setw(13) << "GIA GOC (VND)"
         << " | " << right << setw(13) << "TONG GIA (VND)" << " |\n";
    cout << "+------+----------------------+------------+-----------+---------------+---------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(85) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (PhongTro* pt : ds) {
            cout << "| " << left << setw(4) << pt->getMaPhong()
                 << " | " << left << setw(20) << pt->getTenPhong()
                 << " | " << left << setw(10) << pt->getTinhTrang()
                 << " | " << left << setw(9) << pt->getDienTichStr()
                 << " | " << right << setw(13) << (long long)pt->getGiaThue()
                 << " | " << right << setw(13) << (long long)pt->tinhGiaThue() << " |\n";
        }
    }
    cout << "+------+----------------------+------------+-----------+---------------+---------------+\n";
}

void hienThiBangNguoiThue(const LinkedList<NguoiThue*>& ds, const QuanLyHopDong& qlHopDong) {
    cout << "\n+------+--------------------------------+------------+----------------+--------------------+\n";
    cout << "| " << left << setw(4) << "MA"
         << " | " << left << setw(30) << "HO VA TEN"
         << " | " << left << setw(10) << "NGAY SINH"
         << " | " << left << setw(14) << "SO DIEN THOAI"
         << " | " << left << setw(18) << "PHONG DANG THUE" << " |\n";
    cout << "+------+--------------------------------+------------+----------------+--------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(87) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (NguoiThue* nt : ds) {
            int maP = qlHopDong.timMaPhongTheoNguoiThue(nt->getMaNguoiThue());
            string phongStr = (maP != 0) ? ("Phong " + to_string(maP)) : "Chua thue";
            cout << "| " << left << setw(4) << nt->getMaNguoiThue()
                 << " | " << left << setw(30) << nt->getHoTen()
                 << " | " << left << setw(10) << nt->getNgaySinh().toString()
                 << " | " << left << setw(14) << nt->getSoDienThoai()
                 << " | " << left << setw(18) << phongStr << " |\n";
        }
    }
    cout << "+------+--------------------------------+------------+----------------+--------------------+\n";
}

void hienThiBangNguoiThue(const LinkedList<NguoiThue*>& ds) {
    QuanLyHopDong dummyHD;
    hienThiBangNguoiThue(ds, dummyHD);
}

void hienThiBangHopDong(const LinkedList<HopDongThue>& ds, const QuanLyNguoiThue& qlNguoiThue) {
    cout << "\n+--------+----------+-------+--------------------------------+------------+---------------+----------------------+\n";
    cout << "| " << left << setw(6) << "MA HD"
         << " | " << left << setw(8) << "MA PHONG"
         << " | " << left << setw(5) << "MA NT"
         << " | " << left << setw(30) << "HO VA TEN NGUOI THUE"
         << " | " << left << setw(10) << "NGAY LAP"
         << " | " << left << setw(13) << "THOI HAN"
         << " | " << right << setw(20) << "GIA THUE (VND)" << " |\n";
    cout << "+--------+----------+-------+--------------------------------+------------+---------------+----------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(104) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (const HopDongThue& hd : ds) {
            string tenNT = "Chua xac dinh";
            if (hd.getMaNguoiThue() != 0) {
                NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                if (nt != nullptr) tenNT = nt->getHoTen();
                else tenNT = "Ma NT: " + to_string(hd.getMaNguoiThue());
            }
            string th = to_string(hd.getThoiHan()) + " thang";
            cout << "| " << left << setw(6) << hd.getMaHopDong()
                 << " | " << left << setw(8) << hd.getMaPhong()
                 << " | " << left << setw(5) << hd.getMaNguoiThue()
                 << " | " << left << setw(30) << tenNT
                 << " | " << left << setw(10) << hd.getNgayLap().toString()
                 << " | " << left << setw(13) << th
                 << " | " << right << setw(20) << (long long)hd.getGiaThue() << " |\n";
        }
    }
    cout << "+--------+----------+-------+--------------------------------+------------+---------------+----------------------+\n";
}

void hienThiBangHopDong(const LinkedList<HopDongThue>& ds) {
    cout << "\n+--------+------------+---------------+----------------------+\n";
    cout << "| " << left << setw(6) << "MA HD"
         << " | " << left << setw(10) << "NGAY LAP"
         << " | " << left << setw(13) << "THOI HAN"
         << " | " << right << setw(20) << "GIA THUE (VND)" << " |\n";
    cout << "+--------+------------+---------------+----------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(57) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (const HopDongThue& hd : ds) {
            string th = to_string(hd.getThoiHan()) + " thang";
            cout << "| " << left << setw(6) << hd.getMaHopDong()
                 << " | " << left << setw(10) << hd.getNgayLap().toString()
                 << " | " << left << setw(13) << th
                 << " | " << right << setw(20) << (long long)hd.getGiaThue() << " |\n";
        }
    }
    cout << "+--------+------------+---------------+----------------------+\n";
}

void hienThiBangHoaDon(const LinkedList<HoaDon>& ds, double tongDoanhThu, const QuanLyNguoiThue& qlNguoiThue) {
    cout << "\n+------------+----------+-------+----------------------+------------+---------+---------------+---------------+---------------+-------------------+\n";
    cout << "| " << left << setw(10) << "MA HOA DON"
         << " | " << left << setw(8) << "MA PHONG"
         << " | " << left << setw(5) << "MA NT"
         << " | " << left << setw(20) << "HO VA TEN"
         << " | " << left << setw(10) << "NGAY LAP"
         << " | " << left << setw(7)  << "KY TT"
         << " | " << right << setw(13) << "TIEN PHONG"
         << " | " << right << setw(13) << "TIEN DIEN"
         << " | " << right << setw(13) << "TIEN NUOC"
         << " | " << right << setw(17) << "TONG TIEN (VND)" << " |\n";
    cout << "+------------+----------+-------+----------------------+------------+---------+---------------+---------------+---------------+-------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(141) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (const HoaDon& hd : ds) {
            string tenNT = "Chua xac dinh";
            if (hd.getMaNguoiThue() != 0) {
                NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
                if (nt != nullptr) tenNT = nt->getHoTen();
                else tenNT = "Ma NT: " + to_string(hd.getMaNguoiThue());
            }
            if (tenNT.length() > 20) tenNT = tenNT.substr(0, 17) + "...";
            cout << "| " << left << setw(10) << hd.getMaHoaDon()
                 << " | " << left << setw(8) << hd.getMaPhong()
                 << " | " << left << setw(5) << hd.getMaNguoiThue()
                 << " | " << left << setw(20) << tenNT
                 << " | " << left << setw(10) << hd.getNgayLap().toString()
                 << " | " << left << setw(7)  << hd.getKyThanhToan()
                 << " | " << right << setw(13) << (long long)hd.getTienPhong()
                 << " | " << right << setw(13) << (long long)hd.getTienDien()
                 << " | " << right << setw(13) << (long long)hd.getTienNuoc()
                 << " | " << right << setw(17) << (long long)hd.getTongTien() << " |\n";
        }
    }
    cout << "+------------+----------+-------+----------------------+------------+---------+---------------+---------------+---------------+-------------------+\n";
    cout << "| " << left << setw(121) << "TONG DOANH THU"
         << " | " << right << setw(17) << (long long)tongDoanhThu << " |\n";
    cout << "+-----------------------------------------------------------------------------------------------------------------------------+-------------------+\n";
}

void hienThiBangHoaDon(const LinkedList<HoaDon>& ds, double tongDoanhThu) {
    cout << "\n+------------+----------+-------+------------+---------+---------------+---------------+---------------+-------------------+\n";
    cout << "| " << left << setw(10) << "MA HOA DON"
         << " | " << left << setw(8) << "MA PHONG"
         << " | " << left << setw(5) << "MA NT"
         << " | " << left << setw(10) << "NGAY LAP"
         << " | " << left << setw(7)  << "KY TT"
         << " | " << right << setw(13) << "TIEN PHONG"
         << " | " << right << setw(13) << "TIEN DIEN"
         << " | " << right << setw(13) << "TIEN NUOC"
         << " | " << right << setw(17) << "TONG TIEN (VND)" << " |\n";
    cout << "+------------+----------+-------+------------+---------+---------------+---------------+---------------+-------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(118) << "Danh sach hien dang trong!" << " |\n";
    } else {
        for (const HoaDon& hd : ds) {
            cout << "| " << left << setw(10) << hd.getMaHoaDon()
                 << " | " << left << setw(8) << hd.getMaPhong()
                 << " | " << left << setw(5) << hd.getMaNguoiThue()
                 << " | " << left << setw(10) << hd.getNgayLap().toString()
                 << " | " << left << setw(7)  << hd.getKyThanhToan()
                 << " | " << right << setw(13) << (long long)hd.getTienPhong()
                 << " | " << right << setw(13) << (long long)hd.getTienDien()
                 << " | " << right << setw(13) << (long long)hd.getTienNuoc()
                 << " | " << right << setw(17) << (long long)hd.getTongTien() << " |\n";
        }
    }
    cout << "+------------+----------+-------+------------+---------+---------------+---------------+---------------+-------------------+\n";
    cout << "| " << left << setw(98) << "TONG DOANH THU"
         << " | " << right << setw(17) << (long long)tongDoanhThu << " |\n";
    cout << "+---------------------------------------------------------------------------------------------------------+-------------------+\n";
}

// Struct ho tro hien thi danh sach khach chua dong tien
struct ThongTinChuaDongTien {
    int maNguoiThue;
    string hoTen;
    string soDienThoai;
    int maPhong;
    string tenPhong;
    double tienCanDong;
};

void hienThiBangKhachChuaDongTien(const LinkedList<ThongTinChuaDongTien>& ds, int thang, int nam) {
    cout << "\n+------+----------------------+----------------+----------+----------------------+--------------------+\n";
    cout << "| " << left << setw(4) << "MANT"
         << " | " << left << setw(20) << "HO VA TEN"
         << " | " << left << setw(14) << "SO DIEN THOAI"
         << " | " << left << setw(8) << "MA PHONG"
         << " | " << left << setw(20) << "TEN PHONG"
         << " | " << right << setw(18) << "TIEN CAN DONG(VND)" << " |\n";
    cout << "+------+----------------------+----------------+----------+----------------------+--------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(98) << "Tat ca khach hang deu da dong tien phong thang nay!" << " |\n";
    } else {
        for (const auto& item : ds) {
            cout << "| " << left << setw(4) << item.maNguoiThue
                 << " | " << left << setw(20) << item.hoTen
                 << " | " << left << setw(14) << item.soDienThoai
                 << " | " << left << setw(8) << item.maPhong
                 << " | " << left << setw(20) << item.tenPhong
                 << " | " << right << setw(18) << (long long)item.tienCanDong << " |\n";
        }
    }
    cout << "+------+----------------------+----------------+----------+----------------------+--------------------+\n";
}

void hienThiThongKeDoanhThuThang(int thang, int nam, double tongPhong, double tongDien, double tongNuoc, double tongCong) {
    cout << "\n+-------------------------------------------------------------+\n";
    cout << "|             BAO CAO DOANH THU THANG " << setfill('0') << setw(2) << thang << "/" << setw(4) << nam << setfill(' ') << "                |\n";
    cout << "+-------------------------------------------------------------+\n";
    cout << "|  1. Tong doanh thu tien phong:     " << right << setw(20) << (long long)tongPhong << " VND  |\n";
    cout << "|  2. Tong doanh thu tien dien:      " << right << setw(20) << (long long)tongDien << " VND  |\n";
    cout << "|  3. Tong doanh thu tien nuoc:      " << right << setw(20) << (long long)tongNuoc << " VND  |\n";
    cout << "+-------------------------------------------------------------+\n";
    cout << "|  => TONG CONG DOANH THU THANG:     " << right << setw(20) << (long long)tongCong << " VND  |\n";
    cout << "+-------------------------------------------------------------+\n";
}

void hienThiBangTienDienCao(const LinkedList<HoaDon>& ds, const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue, double mucTien) {
    cout << "\n+------------+----------+----------------------+-------+----------------------+------------+-------------------+\n";
    cout << "| " << left << setw(10) << "MA HOA DON"
         << " | " << left << setw(8) << "MA PHONG"
         << " | " << left << setw(20) << "TEN PHONG"
         << " | " << left << setw(5) << "MA NT"
         << " | " << left << setw(20) << "NGUOI THUE"
         << " | " << left << setw(10) << "NGAY LAP"
         << " | " << right << setw(17) << "TIEN DIEN (VND)" << " |\n";
    cout << "+------------+----------+----------------------+-------+----------------------+------------+-------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(106) << "Khong co phong nao co tien dien cao hon muc quy dinh!" << " |\n";
    } else {
        for (const HoaDon& hd : ds) {
            string tenP = "Phong " + to_string(hd.getMaPhong());
            PhongTro* pt = qlPhong.timKiemPhongTro(hd.getMaPhong());
            if (pt != nullptr) tenP = pt->getTenPhong();
            if (tenP.length() > 20) tenP = tenP.substr(0, 17) + "...";

            string tenNT = "Chua xac dinh";
            NguoiThue* nt = qlNguoiThue.timKiemNguoiThue(hd.getMaNguoiThue());
            if (nt != nullptr) tenNT = nt->getHoTen();
            if (tenNT.length() > 20) tenNT = tenNT.substr(0, 17) + "...";

            cout << "| " << left << setw(10) << hd.getMaHoaDon()
                 << " | " << left << setw(8) << hd.getMaPhong()
                 << " | " << left << setw(20) << tenP
                 << " | " << left << setw(5) << hd.getMaNguoiThue()
                 << " | " << left << setw(20) << tenNT
                 << " | " << left << setw(10) << hd.getNgayLap().toString()
                 << " | " << right << setw(17) << (long long)hd.getTienDien() << " |\n";
        }
    }
    cout << "+------------+----------+----------------------+-------+----------------------+------------+-------------------+\n";
}

// ================================================================
//  SO THEO DOI THANH TOAN TUNG THANG CUA PHONG (LICH SU & CONG NO)
// ================================================================
void hienThiSoTheoDoiThanhToanPhong(int maPhong, const string& tenPhong, const string& tenNT, const string& sdtNT,
                                   const HopDongThue& hd, const QuanLyHoaDon& qlHoaDon,
                                   int thangHienTai, int namHienTai) {
    cout << "\n========================================================================================================================\n";
    cout << "                    SO THEO DOI THANH TOAN CAC THANG - MA PHONG: " << maPhong << " (" << tenPhong << ")\n";
    cout << "  Nguoi thue  : " << tenNT << " (Ma NT: " << hd.getMaNguoiThue() << ") - SDT: " << sdtNT << "\n";
    cout << "  Hop dong    : Ma HD: " << hd.getMaHopDong()
         << " | Bat dau: " << hd.getNgayLap().toString()
         << " | Thoi han: " << hd.getThoiHan() << " thang"
         << " | Gia thue: " << (long long)hd.getGiaThue() << " VND/thang\n";
    cout << "  Moc tra cuu : Thang " << (thangHienTai < 10 ? "0" : "") << thangHienTai << "/" << namHienTai << "\n";
    cout << "========================================================================================================================\n";

    cout << "+-----+---------+----------------------+------------+------------+---------------+---------------+---------------+-------------------+\n";
    cout << "| " << left << setw(3)  << "STT"
         << " | " << left << setw(7)  << "KY TT"
         << " | " << left << setw(20) << "TRANG THAI"
         << " | " << left << setw(10) << "MA HOA DON"
         << " | " << left << setw(10) << "NGAY TT"
         << " | " << right << setw(13) << "TIEN PHONG"
         << " | " << right << setw(13) << "TIEN DIEN"
         << " | " << right << setw(13) << "TIEN NUOC"
         << " | " << right << setw(17) << "TONG TIEN (VND)" << " |\n";
    cout << "+-----+---------+----------------------+------------+------------+---------------+---------------+---------------+-------------------+\n";

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
        string maHD = "---";
        string ngayTT = "---";
        double tPhong = 0.0;
        double tDien = 0.0;
        double tNuoc = 0.0;
        double tTong = 0.0;

        if (bill.getMaHoaDon() != "") {
            trangThai = "[DA THANH TOAN]";
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
                trangThai = "[CHUA TRA - CON NO]";
                soThangNo++;
                tongTienConNo += tPhong;
            } else {
                trangThai = "[CHUA DEN KY]";
                soThangChuaDen++;
            }
        }

        cout << "| " << left << setw(3)  << (i + 1)
             << " | " << left << setw(7)  << kyStr
             << " | " << left << setw(20) << trangThai
             << " | " << left << setw(10) << maHD
             << " | " << left << setw(10) << ngayTT
             << " | " << right << setw(13) << (long long)tPhong
             << " | " << right << setw(13) << (long long)tDien
             << " | " << right << setw(13) << (long long)tNuoc
             << " | " << right << setw(17) << (long long)tTong << " |\n";
    }

    cout << "+-----+---------+----------------------+------------+------------+---------------+---------------+---------------+-------------------+\n";
    cout << "\n [TONG KET THANH TOAN CUA PHONG]:\n";
    cout << "   - So thang DA THANH TOAN : " << setw(2) << soThangDaTra  << " thang | Tong so tien da thu : " << right << setw(15) << (long long)tongTienDaThu << " VND\n";
    cout << "   - So thang CHUA TRA (NO) : " << setw(2) << soThangNo     << " thang | Tong tien phong con no: " << right << setw(15) << (long long)tongTienConNo << " VND\n";
    cout << "   - So thang CHUA DEN KY   : " << setw(2) << soThangChuaDen << " thang\n";
    cout << "========================================================================================================================\n";
}

// Struct ho tro hien thi tinh trang thanh toan tat ca phong
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
    cout << "\n+----------+----------------------+-------+----------------------+----------------+----------------------+------------+------------+-------------------+\n";
    cout << "| " << left << setw(8)  << "MA PHONG"
         << " | " << left << setw(20) << "TEN PHONG"
         << " | " << left << setw(5)  << "MA NT"
         << " | " << left << setw(20) << "HO VA TEN"
         << " | " << left << setw(14) << "SO DIEN THOAI"
         << " | " << left << setw(20) << "TRANG THAI"
         << " | " << left << setw(10) << "MA HOA DON"
         << " | " << left << setw(10) << "NGAY TT"
         << " | " << right << setw(17) << "SO TIEN (VND)" << " |\n";
    cout << "+----------+----------------------+-------+----------------------+----------------+----------------------+------------+------------+-------------------+\n";

    if (ds.empty()) {
        cout << "| " << left << setw(147) << "Khong co phong nao dang duoc thue trong he thong!" << " |\n";
    } else {
        int soPhongDaThu = 0;
        int soPhongChuaThu = 0;
        double tongDaThu = 0.0;
        double tongConNo = 0.0;

        for (const auto& item : ds) {
            string trangThaiStr = item.daThanhToan ? "[DA THANH TOAN]" : "[CHUA TRA - NO]";
            string maHDStr = item.daThanhToan ? item.maHoaDon : "---";
            string ngayTTStr = item.daThanhToan ? item.ngayThanhToan.toString() : "---";

            if (item.daThanhToan) {
                soPhongDaThu++;
                tongDaThu += item.soTien;
            } else {
                soPhongChuaThu++;
                tongConNo += item.soTien;
            }

            cout << "| " << left << setw(8)  << item.maPhong
                 << " | " << left << setw(20) << item.tenPhong
                 << " | " << left << setw(5)  << item.maNT
                 << " | " << left << setw(20) << item.tenNT
                 << " | " << left << setw(14) << item.sdtNT
                 << " | " << left << setw(20) << trangThaiStr
                 << " | " << left << setw(10) << maHDStr
                 << " | " << left << setw(10) << ngayTTStr
                 << " | " << right << setw(17) << (long long)item.soTien << " |\n";
        }

        cout << "+----------+----------------------+-------+----------------------+----------------+----------------------+------------+------------+-------------------+\n";
        cout << "\n [TONG HOP CONG NO THANG " << (thang < 10 ? "0" : "") << thang << "/" << nam << "]:\n";
        cout << "   - Tong so phong dang thue: " << ds.size() << " phong\n";
        cout << "   - So phong DA DONG TIEN  : " << soPhongDaThu << " phong | Tong tien da thu: " << (long long)tongDaThu << " VND\n";
        cout << "   - So phong CON NO TIEN   : " << soPhongChuaThu << " phong | Tong tien con no: " << (long long)tongConNo << " VND\n";
    }
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------------------+\n";
}
