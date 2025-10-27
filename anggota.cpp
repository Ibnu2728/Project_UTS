#include <iostream>
#include <string>
using namespace std;

struct Anggota {
    string id;
    string nama;
    string alamat;
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
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            cout << "\nMasukkan Nama: ";
            getline(cin, daftar[jumlah].nama);
            cout << "Masukkan Alamat: ";
            getline(cin, daftar[jumlah].alamat);

            // 🔹 Membuat ID otomatis dari 2 huruf pertama nama + 3 huruf alamat + nomor urut
            string idNama = daftar[jumlah].nama.substr(0, 2);
            string idAlamat = daftar[jumlah].alamat.substr(0, 3);
            daftar[jumlah].id = idNama + idAlamat + to_string(jumlah + 1);

            cout << "✅ ID Anggota otomatis: " << daftar[jumlah].id << endl;

            jumlah++;
            cout << "Anggota berhasil ditambahkan!\n";
        }

        else if (pilih == 2) {
            cout << "\n=== DAFTAR ANGGOTA ===\n";
            if (jumlah == 0) {
                cout << "Belum ada anggota terdaftar.\n";
            } else {
                for (int i = 0; i < jumlah; i++) {
                    cout << i + 1 << ". "
                         << daftar[i].nama
                         << " | Alamat: " << daftar[i].alamat
                         << " | ID: " << daftar[i].id << endl;

                    // 🔹 Contoh substring tambahan (3 huruf pertama nama)
                    cout << "   Awalan Nama: " << daftar[i].nama.substr(0, 3) << endl;
                }
            }
        }

        else if (pilih == 3) {
            cout << "\nMasukkan ID yang dicari: ";
            string cariID;
            getline(cin, cariID);
            bool ditemukan = false;

            for (int i = 0; i < jumlah; i++) {
                if (daftar[i].id == cariID) {
                    cout << "\n=== DATA ANGGOTA DITEMUKAN ===\n";
                    cout << "Nama   : " << daftar[i].nama << endl;
                    cout << "Alamat : " << daftar[i].alamat << endl;
                    cout << "ID     : " << daftar[i].id << endl;
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                cout << "❌ Anggota dengan ID '" << cariID << "' tidak ditemukan.\n";
            }
        }

    } while (pilih != 0);
}
