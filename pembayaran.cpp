#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

struct Pinjaman {
    string idPinjaman;
    string idAnggota;
    string tanggal;
    double jumlahPinjaman;
    double bunga;
    int lamaCicilan;
    double totalPinjaman;
    double sisaPinjaman;
    string status; // "Lunas" atau "Belum Lunas"
};

// ====================== UTILITAS ======================
string getTanggalSekarang() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

<<<<<<< HEAD
void simpanKeFile(Pinjaman p) {
    ofstream file("pinjaman.txt", ios::app);
    file << p.idPinjaman << ","
         << p.idAnggota << ","
         << p.tanggal << ","
         << p.jumlahPinjaman << ","
         << p.bunga << ","
         << p.lamaCicilan << ","
         << p.totalPinjaman << ","
         << p.sisaPinjaman << ","
         << p.status << "\n";
    file.close();
}

// 🧾 CETAK STRUK PINJAMAN LANGSUNG DI TERMINAL
void tampilkanStruk(Pinjaman p) {
=======
// 🧾 CETAK STRUK LANGSUNG DI TERMINAL
void tampilkanStruk(Pembayaran p) {
>>>>>>> 8d7a3ebad840ab1b94ac73e6701f0ff09eb2a7b3
    cout << "\n=====================================\n";
    cout << "          STRUK PINJAMAN            \n";
    cout << "=====================================\n";
    cout << "ID Pinjaman   : " << p.idPinjaman << "\n";
    cout << "ID Anggota    : " << p.idAnggota << "\n";
    cout << "Tanggal       : " << p.tanggal << "\n";
    cout << fixed << setprecision(0);
    cout << "Jumlah Pinjam : Rp " << p.jumlahPinjaman << "\n";
    cout << "Bunga         : Rp " << p.bunga << "\n";
    cout << "Total Pinjaman: Rp " << p.totalPinjaman << "\n";
    cout << "Sisa Pinjaman : Rp " << p.sisaPinjaman << "\n";
    cout << "Lama Cicilan  : " << p.lamaCicilan << " bulan\n";
    cout << "Status        : " << p.status << "\n";
    cout << "=====================================\n";
}

<<<<<<< HEAD
// ====================== FITUR PINJAMAN ======================
void ajukanPinjaman() {
    Pinjaman p;

    cout << "\n=== AJUKAN PINJAMAN ===\n";
    cout << "Masukkan ID Pinjaman     : ";
    cin >> p.idPinjaman;
    cout << "Masukkan ID Anggota      : ";
    cin >> p.idAnggota;
    cout << "Masukkan Jumlah Pinjaman : ";
    cin >> p.jumlahPinjaman;
    cout << "Masukkan Lama Cicilan (bulan): ";
    cin >> p.lamaCicilan;

    // Hitung bunga 5% dari jumlah pinjaman
    p.bunga = 0.05 * p.jumlahPinjaman;
    p.totalPinjaman = p.jumlahPinjaman + p.bunga;
    p.sisaPinjaman = p.totalPinjaman;
    p.status = "Belum Lunas";
    p.tanggal = getTanggalSekarang();

    simpanKeFile(p);

    cout << "\n✅ Pinjaman berhasil dicatat!\n";
    tampilkanStruk(p);
}

void lihatDaftarPinjaman() {
    ifstream file("pinjaman.txt");
    if (!file.is_open()) {
        cout << "Belum ada data pinjaman.\n";
        return;
    }

    vector<Pinjaman> list;
    Pinjaman p;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, p.idPinjaman, ',');
        getline(ss, p.idAnggota, ',');
        getline(ss, p.tanggal, ',');
        ss >> p.jumlahPinjaman;
        ss.ignore();
        ss >> p.bunga;
        ss.ignore();
        ss >> p.lamaCicilan;
        ss.ignore();
        ss >> p.totalPinjaman;
        ss.ignore();
        ss >> p.sisaPinjaman;
        ss.ignore();
        getline(ss, p.status, ',');
        list.push_back(p);
    }
    file.close();

    cout << "\n=== DAFTAR PINJAMAN ===\n";
=======
// ====================== FITUR PEMBAYARAN ======================
void bayarAngsuran(vector<Pembayaran>& dataBayar) {
    Pembayaran p;
    double denda = 0;
    int hariTerlambat = 0;

    cout << "\n=== BAYAR ANGSURAN ===\n";
    cout << "Masukkan ID Pembayaran  : "; cin >> p.idPembayaran;
    cout << "Masukkan ID Anggota     : "; cin >> p.idAnggota;
    cout << "Masukkan ID Pinjaman    : "; cin >> p.idPinjaman;
    cout << "Masukkan Jumlah Pokok   : "; cin >> p.jumlahPokok;
    cout << "Masukkan Sisa Pinjaman Sebelum Bayar : "; cin >> p.sisaPinjaman;
    cout << "Masukkan Jumlah Hari Keterlambatan (jika ada): "; cin >> hariTerlambat;

    // Hitung bunga dan denda
    p.bunga = 0.02 * p.jumlahPokok; // bunga 2%
    if (hariTerlambat > 0) {
        denda = hariTerlambat * 0.01 * p.jumlahPokok;
        cout << "Denda Keterlambatan : Rp " << denda << "\n";
    }

    p.totalBayar = p.jumlahPokok + p.bunga + denda;
    p.sisaPinjaman -= p.totalBayar;
    if (p.sisaPinjaman <= 0) {
        p.status = "Lunas";
        p.sisaPinjaman = 0;
    } else {
        p.status = "Belum Lunas";
    }

    p.tanggal = getTanggalHariIni();
    dataBayar.push_back(p); // simpan ke memori

    cout << "\n✅ Pembayaran berhasil dicatat!\n";
    tampilkanStruk(p); // tampil langsung
}

void lihatRiwayatPembayaran(const vector<Pembayaran>& dataBayar) {
    if (dataBayar.empty()) {
        cout << "Belum ada data pembayaran.\n";
        return;
    }

    cout << "\n=== RIWAYAT PEMBAYARAN ===\n";
>>>>>>> 8d7a3ebad840ab1b94ac73e6701f0ff09eb2a7b3
    cout << "Masukkan ID Anggota untuk filter: ";
    string idCari;
    cin >> idCari;

    bool ditemukan = false;
    double totalPinjaman = 0, totalSisa = 0;

    for (const auto& i : dataBayar) {
        if (i.idAnggota == idCari) {
            ditemukan = true;
            cout << "\n----------------------------------\n";
            cout << "ID Pinjaman   : " << i.idPinjaman << "\n";
            cout << "Tanggal       : " << i.tanggal << "\n";
            cout << "Total Pinjaman: Rp " << i.totalPinjaman << "\n";
            cout << "Sisa Pinjaman : Rp " << i.sisaPinjaman << "\n";
            cout << "Status        : " << i.status << "\n";
            totalPinjaman += i.totalPinjaman;
            totalSisa += i.sisaPinjaman;
        }
    }

    if (!ditemukan) {
        cout << "Data pinjaman untuk ID tersebut tidak ditemukan.\n";
    } else {
        cout << "\n=== RINGKASAN PINJAMAN ===\n";
        cout << "Total Pinjaman : Rp " << totalPinjaman << "\n";
        cout << "Sisa Pinjaman  : Rp " << totalSisa << "\n";
    }
}

<<<<<<< HEAD
// ====================== MENU PINJAMAN ======================
void menuPinjaman() {
=======
// ====================== MENU PEMBAYARAN ======================
void menuPembayaran() {
    vector<Pembayaran> dataBayar;
>>>>>>> 8d7a3ebad840ab1b94ac73e6701f0ff09eb2a7b3
    int pilih;
    do {
        cout << "\n=== MENU PINJAMAN ===\n";
        cout << "1. Ajukan Pinjaman\n";
        cout << "2. Lihat Daftar Pinjaman\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilih: "; cin >> pilih;

        switch (pilih) {
<<<<<<< HEAD
            case 1: ajukanPinjaman(); break;
            case 2: lihatDaftarPinjaman(); break;
=======
            case 1: bayarAngsuran(dataBayar); break;
            case 2: lihatRiwayatPembayaran(dataBayar); break;
>>>>>>> 8d7a3ebad840ab1b94ac73e6701f0ff09eb2a7b3
            case 3: cout << "Kembali ke menu utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 3);
}

// ====================== MAIN ======================
int main() {
    menuPembayaran();
    return 0;
}
