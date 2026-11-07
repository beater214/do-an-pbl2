#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;

// ================================================================
//  BANG MAU CONSOLE WINDOWS (WIN32 API)
// ================================================================
enum MauConsole {
    MAU_DEN             = 0,
    MAU_XANH_DUONG      = 1,
    MAU_XANH_LA         = 2,
    MAU_XANH_NGOC       = 3,
    MAU_DO              = 4,
    MAU_TIM             = 5,
    MAU_VANG_CAM        = 6,
    MAU_XAM_SANG        = 7,
    MAU_XAM_TOI         = 8,
    MAU_XANH_DUONG_SANG = 9,
    MAU_XANH_LA_SANG    = 10,
    MAU_XANH_NGOC_SANG  = 11,
    MAU_DO_SANG         = 12,
    MAU_TIM_SANG        = 13,
    MAU_VANG_SANG       = 14,
    MAU_TRANG_SANG      = 15
};

// ================================================================
//  CAC HAM TIEN ICH DIEU KHIEN CONSOLE
// ================================================================

// Dat toa do con tro tai vi tri (x, y)
inline void gotoXY(int x, int y) {
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Lay toa do X hien tai
inline int whereX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.dwCursorPosition.X;
    }
    return 0;
}

// Lay toa do Y hien tai
inline int whereY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.dwCursorPosition.Y;
    }
    return 0;
}

// An hoac hien con tro nhap nhay tren man hinh
inline void anConTro(bool an) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 25;
    info.bVisible = !an;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Thiet lap mau chu va mau nen
inline void datMau(int mauChu, int mauNen = 0) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((mauNen << 4) | mauChu));
}

// Khoi phuc mau chu mac dinh (Trang xam tren nen den)
inline void khoiPhucMau() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MAU_XAM_SANG);
}

// Cai dat che do console (UTF-8, Tieu de, Buffer rong de khong gay bang)
inline void caiDatConsole() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    SetConsoleTitleA("HE THONG QUAN LY PHONG TRO - DH BACH KHOA DA NANG");

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        COORD newSize;
        newSize.X = (csbi.dwSize.X < 150) ? 150 : csbi.dwSize.X;
        newSize.Y = (csbi.dwSize.Y < 50) ? 1000 : csbi.dwSize.Y;
        SetConsoleScreenBufferSize(hOut, newSize);
    }
}

// Tam dung man hinh cho nguoi dung nhan phim bat ky de tiep tuc
inline void dungManHinh(const string& msg = "Nhan phim bat ky de tiep tuc...") {
    while (_kbhit()) _getch(); // Xoa phim thua con trong bo dem
    cout << "\n";
    datMau(MAU_VANG_SANG, 0);
    cout << "  ➔  " << msg;
    khoiPhucMau();
    _getch();
    cout << "\n";
}

// Xoa mot dong tai toa do y
inline void xoaDong(int y, int rong = 120) {
    gotoXY(0, y);
    for (int i = 0; i < rong; ++i) cout << " ";
    gotoXY(0, y);
}

// Dem so o ky tu hien thi thuc te tren man hinh (bo qua cac continuation bytes cua UTF-8)
inline int demKyTuHienThi(const string& s) {
    int dem = 0;
    for (size_t i = 0; i < s.length(); ++i) {
        unsigned char c = (unsigned char)s[i];
        if ((c & 0xC0) != 0x80) {
            dem++;
        }
    }
    return dem;
}

// In chuoi ky tu canh trai voi do rong cot chinh xac tren console UTF-8
inline void inCanhTrai(const string& s, int doRong) {
    cout << s;
    int thucTe = demKyTuHienThi(s);
    for (int i = 0; i < doRong - thucTe; ++i) cout << " ";
}

// In chuoi ky tu canh phai voi do rong cot chinh xac tren console UTF-8
inline void inCanhPhai(const string& s, int doRong) {
    int thucTe = demKyTuHienThi(s);
    for (int i = 0; i < doRong - thucTe; ++i) cout << " ";
    cout << s;
}

// In chuoi ky tu duoc can giua trong mot khoang do rong
inline void inCanGiua(const string& text, int doRong, int mauChu = MAU_TRANG_SANG, int mauNen = 0) {
    int len = demKyTuHienThi(text);
    int leftPad = (doRong - len) / 2;
    if (leftPad < 0) leftPad = 0;
    int rightPad = doRong - len - leftPad;
    if (rightPad < 0) rightPad = 0;

    datMau(mauChu, mauNen);
    for (int i = 0; i < leftPad; ++i) cout << " ";
    cout << text;
    for (int i = 0; i < rightPad; ++i) cout << " ";
    khoiPhucMau();
}

// ================================================================
//  VE KHUNG & HOP THOAI DO HOA
// ================================================================

// Ve khung chu nhat tai toa do (x, y)
inline void veKhung(int x, int y, int rong, int cao, int mauVien = MAU_XANH_NGOC_SANG, bool vienDoi = true) {
    datMau(mauVien, 0);
    const char* cTL = vienDoi ? "╔" : "┌";
    const char* cTR = vienDoi ? "╗" : "┐";
    const char* cBL = vienDoi ? "╚" : "└";
    const char* cBR = vienDoi ? "╝" : "┘";
    const char* cH  = vienDoi ? "═" : "─";
    const char* cV  = vienDoi ? "║" : "│";

    // Canh tren
    gotoXY(x, y);
    cout << cTL;
    for (int i = 0; i < rong - 2; ++i) cout << cH;
    cout << cTR;

    // Hai canh ben
    for (int i = 1; i < cao - 1; ++i) {
        gotoXY(x, y + i);
        cout << cV;
        gotoXY(x + rong - 1, y + i);
        cout << cV;
    }

    // Canh duoi
    gotoXY(x, y + cao - 1);
    cout << cBL;
    for (int i = 0; i < rong - 2; ++i) cout << cH;
    cout << cBR;

    khoiPhucMau();
}

// Ve hop thoai co tieu de noi bat
inline void veHopThoai(int x, int y, int rong, int cao, const string& tieuDe,
                       int mauVien = MAU_XANH_NGOC_SANG, int mauTieuDe = MAU_VANG_SANG) {
    veKhung(x, y, rong, cao, mauVien, true);
    if (!tieuDe.empty()) {
        string titleStr = " [ " + tieuDe + " ] ";
        int pos = x + (rong - (int)titleStr.length()) / 2;
        if (pos < x + 2) pos = x + 2;
        gotoXY(pos, y);
        datMau(mauTieuDe, 0);
        cout << titleStr;
        khoiPhucMau();
    }
}

// In hop thong bao thanh cong
inline void inHopThongBaoThanhCong(const string& msg) {
    string prefix = "✔ [THÀNH CÔNG] ";
    int prefixLen = demKyTuHienThi(prefix);
    int msgLen = demKyTuHienThi(msg);
    int noiDungLen = prefixLen + msgLen;
    int innerWidth = noiDungLen + 4; // 2 o dem trai, 2 o dem phai
    if (innerWidth < 50) innerWidth = 50;

    cout << "\n";
    datMau(MAU_XANH_LA_SANG, 0);
    cout << "  ┌";
    for (int i = 0; i < innerWidth; ++i) cout << "─";
    cout << "┐\n";

    cout << "  │  " << prefix << msg;
    int padRight = innerWidth - 2 - noiDungLen;
    for (int i = 0; i < padRight; ++i) cout << " ";
    cout << "│\n";

    cout << "  └";
    for (int i = 0; i < innerWidth; ++i) cout << "─";
    cout << "┘\n";
    khoiPhucMau();
}

// In hop thong bao loi
inline void inHopThongBaoLoi(const string& msg) {
    string prefix = "✖ [THÔNG BÁO LỖI] ";
    int prefixLen = demKyTuHienThi(prefix);
    int msgLen = demKyTuHienThi(msg);
    int noiDungLen = prefixLen + msgLen;
    int innerWidth = noiDungLen + 4;
    if (innerWidth < 50) innerWidth = 50;

    cout << "\n";
    datMau(MAU_DO_SANG, 0);
    cout << "  ┌";
    for (int i = 0; i < innerWidth; ++i) cout << "─";
    cout << "┐\n";

    cout << "  │  " << prefix << msg;
    int padRight = innerWidth - 2 - noiDungLen;
    for (int i = 0; i < padRight; ++i) cout << " ";
    cout << "│\n";

    cout << "  └";
    for (int i = 0; i < innerWidth; ++i) cout << "─";
    cout << "┘\n";
    khoiPhucMau();
}

// In hop thong bao thong tin / huong dan
inline void inHopThongBaoThongTin(const string& msg) {
    string prefix = "ℹ [THÔNG TIN] ";
    int prefixLen = demKyTuHienThi(prefix);
    int msgLen = demKyTuHienThi(msg);
    int noiDungLen = prefixLen + msgLen;
    int innerWidth = noiDungLen + 4;
    if (innerWidth < 50) innerWidth = 50;

    cout << "\n";
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "  ┌";
    for (int i = 0; i < innerWidth; ++i) cout << "─";
    cout << "┐\n";

    cout << "  │  " << prefix << msg;
    int padRight = innerWidth - 2 - noiDungLen;
    for (int i = 0; i < padRight; ++i) cout << " ";
    cout << "│\n";

    cout << "  └";
    for (int i = 0; i < innerWidth; ++i) cout << "─";
    cout << "┘\n";
    khoiPhucMau();
}

// ================================================================
//  BANNER CHINH & MINI DASHBOARD
// ================================================================
inline void veBannerPBL2(int tongPhong = -1, int tongNT = -1, int tongHD = -1, int tongHoaDon = -1) {
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "\n";

    // Canh tren
    cout << "  ╔";
    for (int i = 0; i < 103; ++i) cout << "═";
    cout << "╗\n";

    // Dong trong
    cout << "  ║";
    for (int i = 0; i < 103; ++i) cout << " ";
    cout << "║\n";

    // Tieu de he thong noi bat
    cout << "  ║";
    inCanGiua("★   HỆ THỐNG QUẢN LÝ PHÒNG TRỌ VÀ HÓA ĐƠN TIỀN TRỌ   ★", 103, MAU_VANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "║\n";

    // Dong trong
    cout << "  ║";
    for (int i = 0; i < 103; ++i) cout << " ";
    cout << "║\n";

    // Phu de 1
    cout << "  ║";
    inCanGiua("Đồ Án Cơ Sở Lập Trình (PBL2)", 103, MAU_TRANG_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "║\n";

    // Phu de 2
    cout << "  ║";
    inCanGiua("KHOA CÔNG NGHỆ THÔNG TIN - ĐẠI HỌC BÁCH KHOA", 103, MAU_XANH_LA_SANG, 0);
    datMau(MAU_XANH_NGOC_SANG, 0);
    cout << "║\n";

    // Dong trong
    cout << "  ║";
    for (int i = 0; i < 103; ++i) cout << " ";
    cout << "║\n";

    // Phan Dashboard mini duoc dong bo lien mach thanh 1 khung duy nhat
    if (tongPhong >= 0 && tongNT >= 0 && tongHD >= 0 && tongHoaDon >= 0) {
        // Duong noi giua banner va dashboard
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "  ╠";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╦";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╦";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╦";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╣\n";

        // Hang du lieu thong ke dashboard
        cout << "  ║";
        inCanGiua("Phòng trọ : " + to_string(tongPhong) + " phòng", 25, MAU_TRANG_SANG, 0);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "║";
        inCanGiua("Người thuê: " + to_string(tongNT) + " người", 25, MAU_TRANG_SANG, 0);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "║";
        inCanGiua("Hợp đồng  : " + to_string(tongHD) + " bản", 25, MAU_TRANG_SANG, 0);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "║";
        inCanGiua("Hóa đơn   : " + to_string(tongHoaDon) + " hóa đơn", 25, MAU_TRANG_SANG, 0);
        datMau(MAU_XANH_NGOC_SANG, 0);
        cout << "║\n";

        // Canh duoi
        cout << "  ╚";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╩";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╩";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╩";
        for (int i = 0; i < 25; ++i) cout << "═";
        cout << "╝\n";
    } else {
        // Neu khong co thong ke, dong khung binh thuong
        cout << "  ╚";
        for (int i = 0; i < 103; ++i) cout << "═";
        cout << "╝\n";
    }
    khoiPhucMau();
}

// ================================================================
//  MENU DIEU HUONG DONG DUNG PHIM MUI TEN (ARROW KEY MENU ENGINE)
// ================================================================
struct MucLuaChon {
    int maSo;
    string nhan;
    string moTa;
};

inline int menuDieuHuongDong(const string& tieuDe,
                             const MucLuaChon* dsMuc,
                             int soLuong,
                             int x = 6,
                             int y = -1,
                             int rong = 84,
                             int macDinh = 0) {
    if (soLuong <= 0) return 0;
    if (macDinh < 0 || macDinh >= soLuong) macDinh = 0;

    anConTro(true);

    if (y < 0) {
        y = whereY() + 1;
    }

    int caoHop = soLuong + 4;
    veHopThoai(x, y, rong, caoHop, tieuDe, MAU_XANH_NGOC_SANG, MAU_VANG_SANG);

    int viTriHienTai = macDinh;

    auto veDong = [&](int index, bool dangChon) {
        gotoXY(x + 2, y + 2 + index);
        if (dangChon) {
            // Dong dang duoc chon: Highlight mau nen Xanh Duong, Chu Trang Sang
            datMau(MAU_TRANG_SANG, MAU_XANH_DUONG);
            cout << " ▶ ";
            cout << left << setw(rong - 10) << dsMuc[index].nhan;
            cout << " ◀ ";
        } else {
            // Dong binh thuong
            datMau(MAU_TRANG_SANG, MAU_DEN);
            cout << "   ";
            cout << left << setw(rong - 10) << dsMuc[index].nhan;
            cout << "   ";
        }
        khoiPhucMau();
    };

    // Ve tat ca cac dong lan dau
    for (int i = 0; i < soLuong; ++i) {
        veDong(i, (i == viTriHienTai));
    }

    // Dong huong dan duoi cung
    gotoXY(x + 2, y + caoHop - 1);
    datMau(MAU_XAM_SANG, MAU_DEN);
    cout << " [↑/↓: Di chuyển  |  Enter: Chọn  |  0/ESC: Quay lại] ";
    khoiPhucMau();

    // Vong lap bat su kien phim
    while (true) {
        int ch = _getch();

        if (ch == 224 || ch == 0) {
            // Phim dac biet (Mui ten)
            int ch2 = _getch();
            if (ch2 == 72) { // Mui ten len
                int viTriCu = viTriHienTai;
                viTriHienTai = (viTriHienTai - 1 + soLuong) % soLuong;
                veDong(viTriCu, false);
                veDong(viTriHienTai, true);
            } else if (ch2 == 80) { // Mui ten xuong
                int viTriCu = viTriHienTai;
                viTriHienTai = (viTriHienTai + 1) % soLuong;
                veDong(viTriCu, false);
                veDong(viTriHienTai, true);
            } else if (ch2 == 71) { // Phim Home: ve dau
                int viTriCu = viTriHienTai;
                viTriHienTai = 0;
                veDong(viTriCu, false);
                veDong(viTriHienTai, true);
            } else if (ch2 == 79) { // Phim End: ve cuoi
                int viTriCu = viTriHienTai;
                viTriHienTai = soLuong - 1;
                veDong(viTriCu, false);
                veDong(viTriHienTai, true);
            }
        } else if (ch == 'w' || ch == 'W') { // W: Len
            int viTriCu = viTriHienTai;
            viTriHienTai = (viTriHienTai - 1 + soLuong) % soLuong;
            veDong(viTriCu, false);
            veDong(viTriHienTai, true);
        } else if (ch == 's' || ch == 'S') { // S: Xuong
            int viTriCu = viTriHienTai;
            viTriHienTai = (viTriHienTai + 1) % soLuong;
            veDong(viTriCu, false);
            veDong(viTriHienTai, true);
        } else if (ch == 13) { // Phim ENTER: Chon
            anConTro(false);
            gotoXY(0, y + caoHop + 1);
            return dsMuc[viTriHienTai].maSo;
        } else if (ch == 27) { // Phim ESC: Quay lai / Thoat
            anConTro(false);
            gotoXY(0, y + caoHop + 1);
            return 0;
        } else if (ch >= '0' && ch <= '9') {
            // Bam so truc tiep (vi du bam 1, 2, ..., 0)
            int so = ch - '0';
            for (int i = 0; i < soLuong; ++i) {
                if (dsMuc[i].maSo == so) {
                    anConTro(false);
                    gotoXY(0, y + caoHop + 1);
                    return dsMuc[i].maSo;
                }
            }
        }
    }
}
