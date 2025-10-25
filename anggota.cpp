#include <iostream>
#include <string>
using namespace std;

struct Anggota {
    string nama;
    string alamat;
    string id;
};

void menuAnggota() {
    static Anggota daftar[100];
    static int jumlah = 0;
    int pilih;

    do {
        cout << "\n=== MENU ANGGOTA ===\n";
        cout << "1. Tambah Anggota\n";
        cout << "2. Lihat Data Anggota\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            cout << "Masukkan nama: ";
            getline(cin, daftar[jumlah].nama);
            cout << "Masukkan alamat: ";
            getline(cin, daftar[jumlah].alamat);

            // 🔹 Membuat ID otomatis menggunakan substring
            string idNama = daftar[jumlah].nama.substr(0, 2);  // 2 huruf pertama nama
            string idAlamat = daftar[jumlah].alamat.substr(0, 3); // 3 huruf pertama alamat
            daftar[jumlah].id = idNama + idAlamat + to_string(jumlah + 1);

            cout << "ID Anggota otomatis: " << daftar[jumlah].id << endl;
            jumlah++;

            cout << "Anggota berhasil ditambahkan!\n";
        } else if (pilih == 2) {
            cout << "\nDaftar Anggota:\n";
            for (int i = 0; i < jumlah; i++) {
                cout << i + 1 << ". "
                     << daftar[i].nama
                     << " | Alamat: " << daftar[i].alamat
                     << " | ID: " << daftar[i].id << endl;

                // 🔹 Contoh lain penggunaan substring (ambil 3 huruf pertama nama)
                cout << "   Awalan nama: " << daftar[i].nama.substr(0, 3) << endl;
            }
        }

    } while (pilih != 0);
}
