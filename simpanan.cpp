#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <sstream>
#include <cstdlib>
using namespace std;

// ==================== DEKLARASI STRUCT & EXTERN ====================
struct Anggota {
    string id;
    string nama;
    string alamat;
    double saldo;
};

struct Simpanan {
    string idSimpanan;
    string idAnggota;
    string tanggal;
    string jenisSimpanan;
    double jumlah;
    double saldoAkhir;
};

extern vector<Simpanan> daftarSimpanan;
extern vector<Anggota> dataAnggota;

// ==================== FUNGSI UTILITAS ====================
string getTanggalSekarangSimpanan() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
       << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
       << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

// GENERATE ID SIMPANAN OTOMATIS
string generateIdSimpanan() {
    return "SMP" + to_string(daftarSimpanan.size() + 1) + 
           to_string(rand() % 9000 + 1000); // Menambahkan random 4 digit
}

// TAMPILKAN DAFTAR ANGGOTA UNTUK DIPILIH
void tampilkanDaftarAnggota() {
    if (dataAnggota.empty()) {
        cout << "Belum ada anggota. Tambah anggota terlebih dahulu.\n";
        return;
    }
    
    cout << "\n=== DAFTAR ANGGOTA ===\n";
    for (size_t i = 0; i < dataAnggota.size(); i++) {
        cout << i + 1 << ". " << dataAnggota[i].nama 
             << " (ID: " << dataAnggota[i].id 
             << ", Saldo: Rp " << dataAnggota[i].saldo << ")\n";
    }
}

// AMBIL SALDO TERAKHIR BERDASARKAN ID ANGGOTA
double ambilSaldoTerakhir(string idAnggota) {
    double saldoTerakhir = 0.0;
    for (auto& s : daftarSimpanan) {
        if (s.idAnggota == idAnggota) {
            saldoTerakhir = s.saldoAkhir;
        }
    }
    
    // Jika belum ada simpanan, ambil dari saldo anggota
    if (saldoTerakhir == 0.0) {
        for (auto& a : dataAnggota) {
            if (a.id == idAnggota) {
                saldoTerakhir = a.saldo;
                break;
            }
        }
    }
    
    return saldoTerakhir;
}

// 🧾 CETAK STRUK SIMPANAN
void tampilkanStrukSimpanan(Simpanan s) {
    cout << "\n=====================================\n";
    cout << "          STRUK SIMPANAN            \n";
    cout << "=====================================\n";
    cout << "ID Simpanan  : " << s.idSimpanan << "\n";
    cout << "ID Anggota   : " << s.idAnggota << "\n";
    
    // Tampilkan nama anggota
    string namaAnggota = "Tidak Diketahui";
    for (auto& a : dataAnggota) {
        if (a.id == s.idAnggota) {
            namaAnggota = a.nama;
            break;
        }
    }
    cout << "Nama Anggota : " << namaAnggota << "\n";
    
    cout << "Tanggal      : " << s.tanggal << "\n";
    cout << "Jenis Simpan : " << s.jenisSimpanan << "\n";
    cout << fixed << setprecision(0);
    cout << "Jumlah       : Rp " << s.jumlah << "\n";
    cout << "Saldo Akhir  : Rp " << s.saldoAkhir << "\n";
    cout << "=====================================\n";
}

// ==================== FITUR SIMPANAN ====================
void tambahSimpanan() {
    if (dataAnggota.empty()) {
        cout << "Belum ada anggota. Tambah anggota terlebih dahulu di menu Anggota.\n";
        return;
    }

    Simpanan s;
    
    cout << "\n=== TAMBAH SIMPANAN ===\n";
    
    // Auto-generate ID Simpanan
    s.idSimpanan = generateIdSimpanan();
    cout << "ID Simpanan (auto)  : " << s.idSimpanan << endl;
    
    // Pilih anggota dari daftar
    tampilkanDaftarAnggota();
    cout << "\nPilih nomor anggota: ";
    int pilihanAnggota;
    cin >> pilihanAnggota;
    
    if (pilihanAnggota < 1 || pilihanAnggota > dataAnggota.size()) {
        cout << "Pilihan tidak valid!\n";
        return;
    }
    
    s.idAnggota = dataAnggota[pilihanAnggota - 1].id;
    cout << "ID Anggota (auto)   : " << s.idAnggota << endl;
    cout << "Nama Anggota        : " << dataAnggota[pilihanAnggota - 1].nama << endl;
    
    // Pilih jenis simpanan
    cout << "\nPilih Jenis Simpanan:\n";
    cout << "1. Pokok\n";
    cout << "2. Wajib\n";
    cout << "3. Sukarela\n";
    cout << "Pilihan (1-3): ";
    int pilihanJenis;
    cin >> pilihanJenis;
    
    switch (pilihanJenis) {
        case 1: s.jenisSimpanan = "Pokok"; break;
        case 2: s.jenisSimpanan = "Wajib"; break;
        case 3: s.jenisSimpanan = "Sukarela"; break;
        default: 
            cout << "Pilihan tidak valid, default ke Sukarela.\n";
            s.jenisSimpanan = "Sukarela";
    }
    
    cout << "Masukkan Jumlah Simpanan: Rp ";
    cin >> s.jumlah;

    // Hitung saldo akhir
    double saldoSebelum = ambilSaldoTerakhir(s.idAnggota);
    s.saldoAkhir = saldoSebelum + s.jumlah;
    s.tanggal = getTanggalSekarangSimpanan();

    daftarSimpanan.push_back(s);
    
    // Update saldo anggota
    for (auto& a : dataAnggota) {
        if (a.id == s.idAnggota) {
            a.saldo = s.saldoAkhir;
            break;
        }
    }

    cout << "\n✅ Simpanan berhasil dicatat!\n";
    tampilkanStrukSimpanan(s);
}

void lihatRiwayatSimpanan() {
    if (daftarSimpanan.empty()) {
        cout << "Belum ada data simpanan.\n";
        return;
    }

    cout << "\n=== RIWAYAT SIMPANAN ===\n";
    cout << "1. Lihat semua simpanan\n";
    cout << "2. Filter berdasarkan ID Anggota\n";
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 1) {
        // Tampilkan semua simpanan
        cout << "\n=== SEMUA DATA SIMPANAN ===\n";
        cout << left << setw(12) << "ID Simpanan" 
             << setw(10) << "ID Anggota"
             << setw(15) << "Nama"
             << setw(12) << "Jenis"
             << setw(15) << "Jumlah"
             << setw(15) << "Saldo Akhir" << endl;
        cout << "--------------------------------------------------------------------\n";
        
        for (auto& i : daftarSimpanan) {
            string namaAnggota = "Tidak Diketahui";
            for (auto& a : dataAnggota) {
                if (a.id == i.idAnggota) {
                    namaAnggota = a.nama;
                    break;
                }
            }
            
            cout << left << setw(12) << i.idSimpanan 
                 << setw(10) << i.idAnggota
                 << setw(15) << namaAnggota.substr(0, 14) // Batasi panjang nama
                 << setw(12) << i.jenisSimpanan
                 << setw(15) << fixed << setprecision(0) << i.jumlah
                 << setw(15) << i.saldoAkhir << endl;
        }
    }
    else if (pilihan == 2) {
        // Filter berdasarkan ID Anggota
        cout << "Masukkan ID Anggota untuk filter: ";
        string idCari;
        cin >> idCari;

        bool ditemukan = false;
        double totalSimpan = 0;
        double saldoAkhir = 0;
        string namaAnggota = "Tidak Diketahui";

        // Cari nama anggota
        for (auto& a : dataAnggota) {
            if (a.id == idCari) {
                namaAnggota = a.nama;
                break;
            }
        }

        cout << "\n=== RIWAYAT SIMPANAN - " << namaAnggota << " (" << idCari << ") ===\n";
        
        for (auto& i : daftarSimpanan) {
            if (i.idAnggota == idCari) {
                if (!ditemukan) {
                    cout << left << setw(12) << "ID Simpanan" 
                         << setw(12) << "Tanggal"
                         << setw(12) << "Jenis"
                         << setw(15) << "Jumlah"
                         << setw(15) << "Saldo Akhir" << endl;
                    cout << "----------------------------------------------------\n";
                }
                
                ditemukan = true;
                cout << left << setw(12) << i.idSimpanan 
                     << setw(12) << i.tanggal
                     << setw(12) << i.jenisSimpanan
                     << setw(15) << fixed << setprecision(0) << i.jumlah
                     << setw(15) << i.saldoAkhir << endl;
                
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
    else {
        cout << "Pilihan tidak valid.\n";
    }
}

// ==================== MENU SIMPANAN ====================
void menuSimpanan() {
    // Initialize random seed
    srand(time(nullptr));
    
    int pilih;
    do {
        cout << "\n=== MENU SIMPANAN ===\n";
        cout << "1. Tambah Simpanan\n";
        cout << "2. Lihat Riwayat Simpanan\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahSimpanan(); break;
            case 2: lihatRiwayatSimpanan(); break;
            case 0: cout << "Kembali ke menu utama...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}