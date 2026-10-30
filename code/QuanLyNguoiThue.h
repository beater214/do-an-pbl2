#include <iostream>

using namespace std;

// ================================================================
//  CLASS: QuanLyNguoiThue
// ================================================================
class QuanLyNguoiThue {
private:
    LinkedList<NguoiThue*> danhSachNguoiThue;

public:
    QuanLyNguoiThue() {}
    virtual ~QuanLyNguoiThue() {
        giaiPhongBoNho();
    }

    void giaiPhongBoNho() {
        for (NguoiThue* nt : danhSachNguoiThue) delete nt;
        danhSachNguoiThue.clear();
    }

    void themNguoiThue(NguoiThue* nguoiThue) {
        if (nguoiThue != nullptr) danhSachNguoiThue.push_back(nguoiThue);
    }

    void xoaNguoiThue(int maNguoiThue) {
        for (auto it = danhSachNguoiThue.begin(); it != danhSachNguoiThue.end(); ++it) {
            if ((*it)->getMaNguoiThue() == maNguoiThue) {
                delete *it;
                danhSachNguoiThue.erase(it);
                break;
            }
        }
    }

    void capNhatThongTin(NguoiThue* nguoiThue) {
        if (nguoiThue == nullptr) return;
        for (auto it = danhSachNguoiThue.begin(); it != danhSachNguoiThue.end(); ++it) {
            if ((*it)->getMaNguoiThue() == nguoiThue->getMaNguoiThue()) {
                delete *it;
                *it = nguoiThue;
                return;
            }
        }
    }

    const LinkedList<NguoiThue*>& layDanhSachNguoiThue() const { return danhSachNguoiThue; }

    NguoiThue* timKiemNguoiThue(int maNguoiThue) const {
        for (NguoiThue* nt : danhSachNguoiThue)
            if (nt->getMaNguoiThue() == maNguoiThue) return nt;
        return nullptr;
    }

    bool docFile(const string& filePath) {
        ifstream fin(filePath);
        if (!fin.is_open()) return false;
        giaiPhongBoNho();
        string line;
        while (getline(fin, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            stringstream ss(line);
            string sMa, hoTen, sNgaySinh, sdt;
            if (getline(ss, sMa, '|') &&
                getline(ss, hoTen, '|') &&
                getline(ss, sNgaySinh, '|') &&
                getline(ss, sdt, '|')) {
                int ma = stoi(sMa);
                Date ns = Date::fromString(sNgaySinh);
                danhSachNguoiThue.push_back(new NguoiThue(ma, hoTen, ns, sdt));
            }
        }
        fin.close();
        return true;
    }

    bool ghiFile(const string& filePath) const {
        ofstream fout(filePath);
        if (!fout.is_open()) return false;
        fout << "# MA_NT|HO_TEN|NGAY_SINH|SO_DIEN_THOAI\n";
        for (NguoiThue* nt : danhSachNguoiThue) {
            fout << nt->toFileString() << "\n";
        }
        fout.close();
        return true;
    }
};
