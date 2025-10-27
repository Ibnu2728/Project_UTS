#include <iostream>
#include <string>
using namespace std;

struct Anggota {
    string id;
    string nama;
    string alamat;
    double saldo = 0; // Tambahan: saldo simpanan awal
};

void menuAnggota() {
    static Anggota daftar[100];
    static int jumlah = 0;
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
            cout << "\nMasukkan Nama: ";
            getline(cin, daftar[jumlah].nama);
            cout << "Masukkan Alamat: ";
            getline(cin, daftar[jumlah].alamat);

            int modeID;
            cout << "\nPilih cara membuat ID:\n";
            cout << "1. Otomatis (berdasarkan nama & alamat)\n";
            cout << "2. Input manual\n";
            cout << "Pilihan: ";
            cin >> modeID;
            cin.ignore();

            if (modeID == 1) {
                string idNama = daftar[jumlah].nama.substr(0, 2);
                string idAlamat = daftar[jumlah].alamat.substr(0, 3);
                daftar[jumlah].id = idNama + idAlamat + to_string(jumlah + 1);
            } else {
                cout << "Masukkan ID manual: ";
                getline(cin, daftar[jumlah].id);
            }

            cout << "Masukkan saldo awal: Rp ";
            cin >> daftar[jumlah].saldo;
            cin.ignore();

            cout << "✅ Anggota berhasil ditambahkan! ID: " << daftar[jumlah].id << "\n";
            jumlah++;
        }

        else if (pilih == 2) {
            cout << "\n=== DAFTAR ANGGOTA ===\n";
            if (jumlah == 0) cout << "Belum ada anggota.\n";
            else {
                for (int i = 0; i < jumlah; i++) {
                    cout << i + 1 << ". " << daftar[i].nama
                         << " | ID: " << daftar[i].id
                         << " | Alamat: " << daftar[i].alamat
                         << " | Saldo: Rp " << daftar[i].saldo << endl;
                }
            }
        }

        else if (pilih == 3) {
            cout << "\nMasukkan ID yang dicari: ";
            string cari;
            getline(cin, cari);
            bool ketemu = false;
            for (int i = 0; i < jumlah; i++) {
                if (daftar[i].id == cari) {
                    cout << "\n=== DATA ANGGOTA ===\n";
                    cout << "Nama   : " << daftar[i].nama << endl;
                    cout << "Alamat : " << daftar[i].alamat << endl;
                    cout << "ID     : " << daftar[i].id << endl;
                    cout << "Saldo  : Rp " << daftar[i].saldo << endl;
                    ketemu = true;
                    break;
                }
            }
            if (!ketemu) cout << "❌ Anggota tidak ditemukan.\n";
        }

        else if (pilih == 4) {
            cout << "\nMasukkan ID anggota yang ingin diubah: ";
            string idUbah;
            getline(cin, idUbah);
            bool ketemu = false;

            for (int i = 0; i < jumlah; i++) {
                if (daftar[i].id == idUbah) {
                    cout << "Nama lama: " << daftar[i].nama << "\nMasukkan nama baru: ";
                    getline(cin, daftar[i].nama);
                    cout << "Alamat lama: " << daftar[i].alamat << "\nMasukkan alamat baru: ";
                    getline(cin, daftar[i].alamat);
                    cout << "Saldo lama: Rp " << daftar[i].saldo << "\nMasukkan saldo baru: Rp ";
                    cin >> daftar[i].saldo;
                    cin.ignore();

                    cout << "✅ Data berhasil diperbarui!\n";
                    ketemu = true;
                    break;
                }
            }

            if (!ketemu) cout << "❌ ID tidak ditemukan.\n";
        }

        else if (pilih == 5) {
            cout << "\nMasukkan ID anggota yang ingin dihapus: ";
            string idHapus;
            getline(cin, idHapus);
            bool ketemu = false;

            for (int i = 0; i < jumlah; i++) {
                if (daftar[i].id == idHapus) {
                    for (int j = i; j < jumlah - 1; j++) {
                        daftar[j] = daftar[j + 1];
                    }
                    jumlah--;
                    ketemu = true;
                    cout << "✅ Anggota berhasil dihapus!\n";
                    break;
                }
            }

            if (!ketemu) cout << "❌ ID tidak ditemukan.\n";
        }

    } while (pilih != 0);
}
