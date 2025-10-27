#include <iostream>
#include <string>
using namespace std;

struct DataLaporan {
    int totalTransaksi;
    double totalUang;
    string keterangan;
};

// Simulasi data laporan (sementara manual, bisa dikembangkan nanti)
void menuLaporan() {
    int pilih;
    DataLaporan simpanan = {15, 5000000, "Total simpanan anggota aktif"};
    DataLaporan pinjaman = {4, 8000000, "Total pinjaman yang masih berjalan"};
    DataLaporan pembayaran = {6, 2500000, "Total pembayaran bulan ini"};

    do {
        cout << "\n=== MENU LAPORAN ===\n";
        cout << "1. Laporan Simpanan\n";
        cout << "2. Laporan Pinjaman\n";
        cout << "3. Laporan Pembayaran\n";
        cout << "4. Laporan Data Anggota\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                cout << "\n📄 [LAPORAN SIMPANAN]\n";
                cout << "Jumlah Transaksi : " << simpanan.totalTransaksi << endl;
                cout << "Total Uang       : Rp " << simpanan.totalUang << endl;
                cout << "Keterangan       : " << simpanan.keterangan << endl;
                break;

            case 2:
                cout << "\n📄 [LAPORAN PINJAMAN]\n";
                cout << "Jumlah Peminjam  : " << pinjaman.totalTransaksi << endl;
                cout << "Total Pinjaman   : Rp " << pinjaman.totalUang << endl;
                cout << "Keterangan       : " << pinjaman.keterangan << endl;
                break;

            case 3:
                cout << "\n📄 [LAPORAN PEMBAYARAN]\n";
                cout << "Jumlah Pembayaran: " << pembayaran.totalTransaksi << endl;
                cout << "Total Pembayaran : Rp " << pembayaran.totalUang << endl;
                cout << "Keterangan       : " << pembayaran.keterangan << endl;
                break;

            case 4: {
                cout << "\n📄 [LAPORAN DATA ANGGOTA]\n";
                cout << "Menampilkan daftar anggota yang sudah terdaftar...\n";
                cout << "(Untuk versi ini, data anggota bisa dilihat langsung di menu anggota)\n";
                cout << "Integrasi penuh bisa ditambahkan jika data anggota dibuat global.\n";
                break;
            }

            case 0:
                cout << "Kembali ke menu utama...\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);
}
