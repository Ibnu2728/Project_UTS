#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

struct Simpanan {
    string idSimpanan;
    string idAnggota;
    string tanggal;
    string jenisSimpanan;
    double jumlah;
    double saldoAkhir;
};

// ====================== UTILITAS ======================
string getTanggalSekarang1() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

double ambilSaldoTerakhir(string idAnggota) {
    ifstream file("simpanan.txt");
    if (!file.is_open()) return 0.0;

    Simpanan s;
    string line;
    double saldoTerakhir = 0.0;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, s.idSimpanan, ',');
        getline(ss, s.idAnggota, ',');
        getline(ss, s.tanggal, ',');
        getline(ss, s.jenisSimpanan, ',');
        ss >> s.jumlah;
        ss.ignore();
        ss >> s.saldoAkhir;

        if (s.idAnggota == idAnggota) {
            saldoTerakhir = s.saldoAkhir;
        }
    }
    file.close();
    return saldoTerakhir;
}

void simpanKeFile(Simpanan s) {
    ofstream file("simpanan.txt", ios::app);
    file << s.idSimpanan << ","
         << s.idAnggota << ","
         << s.tanggal << ","
         << s.jenisSimpanan << ","
         << s.jumlah << ","
         << s.saldoAkhir << "\n";
    file.close();
}

// 🧾 CETAK STRUK SIMPANAN
void tampilkanStruk(Simpanan s) {
    cout << "\n=====================================\n";
    cout << "          STRUK SIMPANAN            \n";
    cout << "=====================================\n";
    cout << "ID Simpanan  : " << s.idSimpanan << "\n";
    cout << "ID Anggota   : " << s.idAnggota << "\n";
    cout << "Tanggal      : " << s.tanggal << "\n";
    cout << "Jenis Simpan : " << s.jenisSimpanan << "\n";
    cout << fixed << setprecision(0);
    cout << "Jumlah       : Rp " << s.jumlah << "\n";
    cout << "Saldo Akhir  : Rp " << s.saldoAkhir << "\n";
    cout << "=====================================\n";
}

// ====================== FITUR SIMPANAN ======================
void tambahSimpanan() {
    Simpanan s;

    cout << "\n=== TAMBAH SIMPANAN ===\n";
    cout << "Masukkan ID Simpanan    : ";
    cin >> s.idSimpanan;
    cout << "Masukkan ID Anggota     : ";
    cin >> s.idAnggota;
    cout << "Masukkan Jenis Simpanan (Pokok/Wajib/Sukarela): ";
    cin >> s.jenisSimpanan;
    cout << "Masukkan Jumlah Simpanan: ";
    cin >> s.jumlah;

    double saldoSebelum = ambilSaldoTerakhir(s.idAnggota);
    s.saldoAkhir = saldoSebelum + s.jumlah;
    s.tanggal = getTanggalSekarang1();

    simpanKeFile(s);
    cout << "\n✅ Simpanan berhasil dicatat!\n";
    tampilkanStruk(s);
}

void lihatRiwayatSimpanan() {
    ifstream file("simpanan.txt");
    if (!file.is_open()) {
        cout << "Belum ada data simpanan.\n";
        return;
    }

    vector<Simpanan> list;
    Simpanan s;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, s.idSimpanan, ',');
        getline(ss, s.idAnggota, ',');
        getline(ss, s.tanggal, ',');
        getline(ss, s.jenisSimpanan, ',');
        ss >> s.jumlah;
        ss.ignore();
        ss >> s.saldoAkhir;
        list.push_back(s);
    }
    file.close();

    cout << "\n=== RIWAYAT SIMPANAN ===\n";
    cout << "Masukkan ID Anggota untuk filter: ";
    string idCari;
    cin >> idCari;

    bool ditemukan = false;
    double totalSimpan = 0;
    double saldoAkhir = 0;

    for (auto& i : list) {
        if (i.idAnggota == idCari) {
            ditemukan = true;
            cout << "\n----------------------------------\n";
            cout << "ID Simpanan  : " << i.idSimpanan << "\n";
            cout << "Tanggal      : " << i.tanggal << "\n";
            cout << "Jenis        : " << i.jenisSimpanan << "\n";
            cout << "Jumlah       : Rp " << i.jumlah << "\n";
            cout << "Saldo Akhir  : Rp " << i.saldoAkhir << "\n";
            totalSimpan += i.jumlah;
            saldoAkhir = i.saldoAkhir;
        }
    }

    if (!ditemukan) {
        cout << "Data simpanan untuk ID tersebut tidak ditemukan.\n";
    } else {
        cout << "\n=== RINGKASAN SIMPANAN ===\n";
        cout << "Total Simpanan : Rp " << totalSimpan << "\n";
        cout << "Saldo Akhir    : Rp " << saldoAkhir << "\n";
    }
}

// ====================== MENU SIMPANAN ======================
void menuSimpanan() {
    int pilih;
    do {
        cout << "\n=== MENU SIMPANAN ===\n";
        cout << "1. Tambah Simpanan\n";
        cout << "2. Lihat Riwayat Simpanan\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahSimpanan(); break;
            case 2: lihatRiwayatSimpanan(); break;
            case 3: cout << "Kembali ke menu utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 3);
}
