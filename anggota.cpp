#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ==================== DEKLARASI STRUCT & EXTERN ====================
struct Anggota {
    string id;
    string nama;
    string alamat;
    double saldo;
};

extern vector<Anggota> dataAnggota;

// ==================== MENU ANGGOTA ====================
void menuAnggota() {
    int pilih;

    do {
        cout << "\n=== MENU ANGGOTA ===\n";
        cout << "1. Tambah Anggota\n";
        cout << "2. Lihat Semua Anggota\n";
        cout << "3. Cari Anggota Berdasarkan ID\n";
        cout << "4. Ubah Data Anggota\n";
        cout << "5. Hapus Anggota\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            Anggota a;
            cout << "\nMasukkan Nama: ";
            getline(cin, a.nama);
            cout << "Masukkan Alamat: ";
            getline(cin, a.alamat);

            int modeID;
            cout << "\nPilih cara membuat ID:\n";
            cout << "1. Otomatis (berdasarkan nama & alamat)\n";
            cout << "2. Input manual\n";
            cout << "Pilihan: ";
            cin >> modeID;
            cin.ignore();

            if (modeID == 1) {
                string idNama = a.nama.substr(0, 2);
                string idAlamat = a.alamat.substr(0, 3);
                a.id = idNama + idAlamat + to_string(dataAnggota.size() + 1);
            } else {
                cout << "Masukkan ID manual: ";
                getline(cin, a.id);
            }

            cout << "Masukkan saldo awal: Rp ";
            cin >> a.saldo;
            cin.ignore();

            dataAnggota.push_back(a);
            cout << "Anggota berhasil ditambahkan! ID: " << a.id << "\n";
        }

        else if (pilih == 2) {
            cout << "\n=== DAFTAR ANGGOTA ===\n";
            if (dataAnggota.empty()) cout << "Belum ada anggota.\n";
            else {
                for (size_t i = 0; i < dataAnggota.size(); i++) {
                    cout << i + 1 << ". " << dataAnggota[i].nama
                         << " | ID: " << dataAnggota[i].id
                         << " | Alamat: " << dataAnggota[i].alamat
                         << " | Saldo: Rp " << dataAnggota[i].saldo << endl;
                }
            }
        }

        else if (pilih == 3) {
            cout << "\nMasukkan ID yang dicari: ";
            string cari;
            getline(cin, cari);
            bool ketemu = false;
            for (auto &a : dataAnggota) {
                if (a.id == cari) {
                    cout << "\n=== DATA ANGGOTA ===\n";
                    cout << "Nama   : " << a.nama << endl;
                    cout << "Alamat : " << a.alamat << endl;
                    cout << "ID     : " << a.id << endl;
                    cout << "Saldo  : Rp " << a.saldo << endl;
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << "Anggota tidak ditemukan.\n";
        }

        else if (pilih == 4) {
            cout << "\nMasukkan ID anggota yang ingin diubah: ";
            string idUbah;
            getline(cin, idUbah);
            bool ketemu = false;

            for (auto &a : dataAnggota) {
                if (a.id == idUbah) {
                    cout << "Nama lama: " << a.nama << "\nMasukkan nama baru: ";
                    getline(cin, a.nama);
                    cout << "Alamat lama: " << a.alamat << "\nMasukkan alamat baru: ";
                    getline(cin, a.alamat);
                    cout << "Saldo lama: Rp " << a.saldo << "\nMasukkan saldo baru: Rp ";
                    cin >> a.saldo;
                    cin.ignore();
                    cout << "Data berhasil diperbarui!\n";
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << "ID tidak ditemukan.\n";
        }

        else if (pilih == 5) {
            cout << "\nMasukkan ID anggota yang ingin dihapus: ";
            string idHapus;
            getline(cin, idHapus);
            bool ketemu = false;

            for (size_t i = 0; i < dataAnggota.size(); i++) {
                if (dataAnggota[i].id == idHapus) {
                    dataAnggota.erase(dataAnggota.begin() + i);
                    ketemu = true;
                    cout << "Anggota berhasil dihapus!\n";
                    break;
                }
            }
            if (!ketemu) cout << "ID tidak ditemukan.\n";
        }

    } while (pilih != 0);
}