#include <iostream>
#include <string>

using namespace std;

// ================================================================
//  HE THONG DOC GHI FILE TXT (DATA PERSISTENCE)
// ================================================================

// Tu dong tim duong dan den thu muc data (Ho tro ca khi chay tu project/, tu code/, hoac double-click exe)
inline string timDuongDanThuMucData() {
    ifstream f1("data/phongtro.txt");
    if (f1.is_open()) {
        f1.close();
        return "data/";
    }
    ifstream f2("../data/phongtro.txt");
    if (f2.is_open()) {
        f2.close();
        return "../data/";
    }

    // Thu tim theo vi tri thuc te cua file exe tren Windows (ho tro double click ngoai Explorer)
    char buffer[MAX_PATH];
    if (GetModuleFileNameA(NULL, buffer, MAX_PATH) > 0) {
        string exePath(buffer);
        size_t pos = exePath.find_last_of("\\/");
        if (pos != string::npos) {
            string exeDir = exePath.substr(0, pos + 1);
            ifstream f3(exeDir + "data/phongtro.txt");
            if (f3.is_open()) {
                f3.close();
                return exeDir + "data/";
            }
            ifstream f4(exeDir + "../data/phongtro.txt");
            if (f4.is_open()) {
                f4.close();
                return exeDir + "../data/";
            }
        }
    }
    return "data/";
}

inline bool docTatCaDuLieu(QuanLyPhong& qlPhong, QuanLyNguoiThue& qlNguoiThue,
                          QuanLyHopDong& qlHopDong, QuanLyHoaDon& qlHoaDon,
                          const string& thuMucData = "") {
    string dir = thuMucData.empty() ? timDuongDanThuMucData() : thuMucData;
    bool okP  = qlPhong.docFile(dir + "phongtro.txt");
    bool okNT = qlNguoiThue.docFile(dir + "nguoithue.txt");
    bool okHD = qlHopDong.docFile(dir + "hopdong.txt");
    bool okBL = qlHoaDon.docFile(dir + "hoadon.txt");
    return okP && okNT && okHD && okBL;
}

inline bool luuTatCaDuLieu(const QuanLyPhong& qlPhong, const QuanLyNguoiThue& qlNguoiThue,
                          const QuanLyHopDong& qlHopDong, const QuanLyHoaDon& qlHoaDon,
                          const string& thuMucData = "") {
    string dir = thuMucData.empty() ? timDuongDanThuMucData() : thuMucData;
    bool okP  = qlPhong.ghiFile(dir + "phongtro.txt");
    bool okNT = qlNguoiThue.ghiFile(dir + "nguoithue.txt");
    bool okHD = qlHopDong.ghiFile(dir + "hopdong.txt");
    bool okBL = qlHoaDon.ghiFile(dir + "hoadon.txt");
    return okP && okNT && okHD && okBL;
}

inline void khoiTaoDuLieuMau(QuanLyPhong& qlPhong, QuanLyNguoiThue& qlNguoiThue,
                            QuanLyHopDong& qlHopDong, QuanLyHoaDon& qlHoaDon) {
    qlPhong.themPhongTro(new PhongTroThuong(101, "Phong 101", "Da thue", "20m2", 1500000.0, true));
    qlPhong.themPhongTro(new PhongTroThuong(102, "Phong 102", "Con trong", "22m2", 1800000.0, false));
    qlPhong.themPhongTro(new PhongTroVip(201, "Phong VIP 201", "Con trong", "35m2", 3000000.0, 500000.0));
    qlPhong.themPhongTro(new PhongTroVip(202, "Phong VIP 202", "Da thue", "40m2", 3500000.0, 600000.0));

    qlNguoiThue.themNguoiThue(new NguoiThue(1, "Nguyen Van A", Date(15, 5, 2002), "0912345678"));
    qlNguoiThue.themNguoiThue(new NguoiThue(2, "Tran Thi B", Date(20, 10, 2003), "0987654321"));
    qlNguoiThue.themNguoiThue(new NguoiThue(3, "Le Van C", Date(1, 1, 2001), "0933445566"));

    qlHopDong.themHopDong(HopDongThue(1001, 101, 1, Date(1, 10, 2026), 12, 1500000.0));
    qlHopDong.themHopDong(HopDongThue(1002, 202, 3, Date(1, 9, 2026), 6, 4100000.0));

    qlHoaDon.themHoaDon(HoaDon("HD01", 101, 1, Date(5, 10, 2026), 10, 2026, 1500000.0, 350000.0, 80000.0));
    qlHoaDon.themHoaDon(HoaDon("HD02", 202, 3, Date(5, 9, 2026), 9, 2026, 4100000.0, 480000.0, 120000.0));

    luuTatCaDuLieu(qlPhong, qlNguoiThue, qlHopDong, qlHoaDon);
}
