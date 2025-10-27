#include <iostream>
#include <string>
using namespace std;

void menuLaporan() {
    int pilih;
    do {
        cout << "\n=== MENU LAPORAN ===\n";
        cout << "1. Laporan Simpanan\n";
        cout << "2. Laporan Pinjaman\n";
        cout << "3. Laporan Pembayaran\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                cout << "\n📄 [LAPORAN SIMPANAN]\n";
                cout << "Total simpanan anggota: Rp 5.000.000\n";
                cout << "Jumlah transaksi: 15\n";
                break;
            case 2:
                cout << "\n📄 [LAPORAN PINJAMAN]\n";
                cout << "Total pinjaman aktif: Rp 8.000.000\n";
                cout << "Jumlah peminjam: 4\n";
                break;
            case 3:
                cout << "\n📄 [LAPORAN PEMBAYARAN]\n";
                cout << "Total pembayaran bulan ini: Rp 2.500.000\n";
                cout << "Transaksi berhasil: 6\n";
                break;
        }
    } while (pilih != 0);
}
