#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

struct Pembayaran {
    string idPembayaran;
    string idAnggota;
    string idPinjaman;
    string tanggal;
    double jumlahPokok;
    double bunga;
    double totalBayar;
    double sisaPinjaman;
    string status;
};

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

void simpanKeFile(Pembayaran p) {
    ofstream file("pembayaran.txt", ios::app);
    file << p.idPembayaran << ","
         << p.idAnggota << ","
         << p.idPinjaman << ","
         << p.tanggal << ","
         << p.jumlahPokok << ","
         << p.bunga << ","
         << p.totalBayar << ","
         << p.sisaPinjaman << ","
         << p.status << "\n";
    file.close();
}

// 🧾 CETAK STRUK LANGSUNG DI TERMINAL
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
    cout << "Masukkan ID Pembayaran  : ";
    cin >> p.idPembayaran;
    cout << "Masukkan ID Anggota     : ";
    cin >> p.idAnggota;
    cout << "Masukkan ID Pinjaman    : ";
    cin >> p.idPinjaman;
    cout << "Masukkan Jumlah Pokok   : ";
    cin >> p.jumlahPokok;
    cout << "Masukkan Sisa Pinjaman Sebelum Bayar : ";
    cin >> p.sisaPinjaman;

    cout << "Masukkan Jumlah Hari Keterlambatan (jika ada): ";
    cin >> hariTerlambat;

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

    // Simpan data
    simpanKeFile(p);

    cout << "\n✅ Pembayaran berhasil dicatat!\n";
    tampilkanStruk(p); // tampilkan langsung di terminal
}

void lihatRiwayatPembayaran() {
    ifstream file("pembayaran.txt");
    if (!file.is_open()) {
        cout << "Belum ada data pembayaran.\n";
        return;
    }

    vector<Pembayaran> list;
    Pembayaran p;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, p.idPembayaran, ',');
        getline(ss, p.idAnggota, ',');
        getline(ss, p.idPinjaman, ',');
        getline(ss, p.tanggal, ',');
        ss >> p.jumlahPokok;
        ss.ignore();
        ss >> p.bunga;
        ss.ignore();
        ss >> p.totalBayar;
        ss.ignore();
        ss >> p.sisaPinjaman;
        ss.ignore();
        getline(ss, p.status, ',');
        list.push_back(p);
    }
    file.close();

    cout << "\n=== RIWAYAT PEMBAYARAN ===\n";
    cout << "Masukkan ID Anggota untuk filter: ";
    string idCari;
    cin >> idCari;

    double totalBayar = 0, totalBunga = 0;
    bool ditemukan = false;

    for (auto& i : list) {
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

void menuPembayaran() {
    int pilih;
    do {
        cout << "\n=== MENU PEMBAYARAN ===\n";
        cout << "1. Bayar Angsuran\n";
        cout << "2. Lihat Riwayat Pembayaran\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: bayarAngsuran(); break;
            case 2: lihatRiwayatPembayaran(); break;
            case 3: cout << "Kembali ke menu utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 3);
}
