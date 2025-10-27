#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

struct Pinjaman {
    string idPinjaman;
    string idAnggota;
    double jumlahPinjaman;
    double sisaPinjaman;
};

struct Pembayaran {
    string idPembayaran;
    string idAnggota;
    string idPinjaman;
    string tanggal;
    double jumlahPokok;
    double bunga;
    double totalBayar;
    double sisaPinjaman;
    string status; // "Lunas" atau "Belum Lunas"
};

// ====================== GLOBAL VECTOR ======================
vector<Pinjaman> dataPinjaman;
vector<Pembayaran> dataBayar;

// ====================== UTILITAS ======================
string getTanggalHariIni() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

// ====================== CETAK STRUK ======================
void tampilkanStruk(Pembayaran p) {
    cout << "\n=====================================\n";
    cout << "          STRUK PEMBAYARAN          \n";
    cout << "=====================================\n";
    cout << "ID Pembayaran : " << p.idPembayaran << "\n";
    cout << "ID Anggota    : " << p.idAnggota << "\n";
    cout << "ID Pinjaman   : " << p.idPinjaman << "\n";
    cout << "Tanggal       : " << p.tanggal << "\n";
    cout << fixed << setprecision(0);
    cout << "Pokok         : Rp " << p.jumlahPokok << "\n";
    cout << "Bunga         : Rp " << p.bunga << "\n";
    cout << "Total Bayar   : Rp " << p.totalBayar << "\n";
    cout << "Sisa Pinjaman : Rp " << p.sisaPinjaman << "\n";
    cout << "Status        : " << p.status << "\n";
    cout << "=====================================\n";
}

// ====================== FITUR PEMBAYARAN ======================
void bayarAngsuran() {
    Pembayaran p;
    double denda = 0;
    int hariTerlambat = 0;

    cout << "\n=== BAYAR ANGSURAN ===\n";
    cout << "Masukkan ID Anggota     : "; cin >> p.idAnggota;

    // auto-generate ID Pembayaran berdasarkan jumlah pembayaran
    p.idPembayaran = "BAY" + to_string(dataBayar.size() + 1);

    // cari pinjaman anggota
    bool adaPinjaman = false;
    for (auto& pin : dataPinjaman) {
        if (pin.idAnggota == p.idAnggota && pin.sisaPinjaman > 0) {
            p.idPinjaman = pin.idPinjaman;
            p.sisaPinjaman = pin.sisaPinjaman;
            p.jumlahPokok = pin.jumlahPinjaman / pin.sisaPinjaman; // contoh pembagian
            adaPinjaman = true;
            break;
        }
    }

    if (!adaPinjaman) {
        cout << "❌ Anggota tidak punya pinjaman aktif.\n";
        return;
    }

    cout << "Masukkan Jumlah Pokok Bayar   : "; cin >> p.jumlahPokok;
    cout << "Masukkan Jumlah Hari Keterlambatan (jika ada): "; cin >> hariTerlambat;

    p.bunga = 0.02 * p.jumlahPokok;
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
    dataBayar.push_back(p);

    cout << "\n✅ Pembayaran berhasil dicatat!\n";
    tampilkanStruk(p);
}

void lihatRiwayatPembayaran() {
    if (dataBayar.empty()) {
        cout << "Belum ada data pembayaran.\n";
        return;
    }

    cout << "\n=== RIWAYAT PEMBAYARAN ===\n";
    cout << "Masukkan ID Anggota untuk filter: ";
    string idCari;
    cin >> idCari;

    double totalBayar = 0, totalBunga = 0;
    bool ditemukan = false;

    for (auto& i : dataBayar) {
        if (i.idAnggota == idCari) {
            ditemukan = true;
            cout << "\n----------------------------------\n";
            cout << "ID Pembayaran : " << i.idPembayaran << "\n";
            cout << "Tanggal       : " << i.tanggal << "\n";
            cout << "Total Bayar   : Rp " << i.totalBayar << "\n";
            cout << "Sisa Pinjaman : Rp " << i.sisaPinjaman << "\n";
            cout << "Status        : " << i.status << "\n";
            totalBayar += i.totalBayar;
            totalBunga += i.bunga;
        }
    }

    if (!ditemukan) {
        cout << "Data untuk ID tersebut tidak ditemukan.\n";
    } else {
        cout << "\n=== RINGKASAN PEMBAYARAN ===\n";
        cout << "Total dibayar : Rp " << totalBayar << "\n";
        cout << "Total bunga   : Rp " << totalBunga << "\n";
    }
}

// ====================== MENU PEMBAYARAN ======================
void menuPembayaran() {
    int pilih;
    do {
        cout << "\n=== MENU PEMBAYARAN ===\n";
        cout << "1. Bayar Angsuran\n";
        cout << "2. Lihat Riwayat Pembayaran\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: bayarAngsuran(); break;
            case 2: lihatRiwayatPembayaran(); break;
            case 0: cout << "Kembali ke menu utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}