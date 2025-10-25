#include <iostream>
using namespace std;

void menuAnggota();
void menuSimpanan();
void menuPinjaman();
void menuPembayaran();
void menuLaporan();

int main() {
    int pilihan;
    do {
        cout << "\n=== SISTEM SIMPAN PINJAM ===\n";
        cout << "1. Data Anggota\n";
        cout << "2. Data Simpanan\n";
        cout << "3. Data Pinjaman\n";
        cout << "4. Pembayaran\n";
        cout << "5. Laporan\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: menuAnggota(); break;
            case 2: menuSimpanan(); break;
            case 3: menuPinjaman(); break;
            case 4: menuPembayaran(); break;
            case 5: menuLaporan(); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
    return 0;
}
