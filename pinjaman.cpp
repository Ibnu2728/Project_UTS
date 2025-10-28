#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

// ==================== DEKLARASI STRUCT & EXTERN ====================
struct Anggota {
    string id;
    string nama;
    string alamat;
    double saldo;
};

struct Pinjaman {
    string idPinjaman;
    string idAnggota;
    string tanggal;
    double jumlahPinjaman;
    double bunga;
    int lamaCicilan;
    double totalPinjaman;
    double sisaPinjaman;
    string status;
};

extern vector<Anggota> dataAnggota;
extern vector<Pinjaman> dataPinjaman;

// ==================== FUNGSI UTILITAS ====================
string getTanggalSekarangPinjaman() {  // NAMA DIUBAH
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

// ==================== CETAK STRUK ====================
void tampilkanStrukPinjaman(Pinjaman p) {  // NAMA DIUBAH
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

// ==================== FITUR PINJAMAN ====================
void ajukanPinjaman() {
    if (dataAnggota.empty()) {
        cout << "Belum ada anggota. Tambah anggota dulu.\n";
        return;
    }

    Pinjaman p;
    cout << "\n=== DAFTAR ANGGOTA ===\n";
    for (size_t i = 0; i < dataAnggota.size(); i++) {
        cout << i + 1 << ". " << dataAnggota[i].nama
             << " (ID: " << dataAnggota[i].id << ")\n";
    }

    int pilihan;
    cout << "Pilih anggota (nomor): "; cin >> pilihan;
    if (pilihan < 1 || pilihan > dataAnggota.size()) {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    // Sambungan ke anggota
    p.idAnggota = dataAnggota[pilihan - 1].id;

    cout << "Masukkan Jumlah Pinjaman : "; cin >> p.jumlahPinjaman;
    cout << "Masukkan Lama Cicilan (bulan): "; cin >> p.lamaCicilan;

    p.idPinjaman = "PJ" + to_string(dataPinjaman.size() + 1);
    p.bunga = 0.05 * p.jumlahPinjaman;
    p.totalPinjaman = p.jumlahPinjaman + p.bunga;
    p.sisaPinjaman = p.totalPinjaman;
    p.status = "Belum Lunas";
    p.tanggal = getTanggalSekarangPinjaman();  // PANGGIL FUNGSI YANG BARU

    dataPinjaman.push_back(p);

    cout << "\nPinjaman berhasil dicatat!\n";
    tampilkanStrukPinjaman(p);  // PANGGIL FUNGSI YANG BARU
}

void lihatDaftarPinjaman() {
    if (dataPinjaman.empty()) {
        cout << "Belum ada data pinjaman.\n";
        return;
    }

    cout << "\n=== DAFTAR PINJAMAN ===\n";
    cout << "Masukkan ID Anggota untuk filter: ";
    string idCari; cin >> idCari;

    bool ditemukan = false;
    double totalPinjaman = 0, totalSisa = 0;

    for (auto& i : dataPinjaman) {
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

    if (!ditemukan) cout << "Data pinjaman untuk ID tersebut tidak ditemukan.\n";
    else {
        cout << "\n=== RINGKASAN PINJAMAN ===\n";
        cout << "Total Pinjaman : Rp " << totalPinjaman << "\n";
        cout << "Sisa Pinjaman  : Rp " << totalSisa << "\n";
    }
}

// ==================== MENU PINJAMAN ====================
void menuPinjaman() {
    int pilih;
    do {
        cout << "\n=== MENU PINJAMAN ===\n";
        cout << "1. Ajukan Pinjaman\n";
        cout << "2. Lihat Daftar Pinjaman\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: ajukanPinjaman(); break;
            case 2: lihatDaftarPinjaman(); break;
            case 0: cout << "Kembali ke menu utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}