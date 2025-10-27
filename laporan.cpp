#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Laporan {
    string jenis;
    int jumlahTransaksi;
    double totalUang;
    string keterangan;
};

void menuLaporan() {
    Laporan simpanan = {"Simpanan", 15, 5000000, "Total dana yang disimpan anggota"};
    Laporan pinjaman = {"Pinjaman", 4, 8000000, "Dana yang masih dalam masa cicilan"};
    Laporan pembayaran = {"Pembayaran", 6, 2500000, "Pembayaran angsuran bulan ini"};

    int pilih;
    do {
        cout << "\n=== MENU LAPORAN ===\n";
        cout << "1. Laporan Simpanan\n";
        cout << "2. Laporan Pinjaman\n";
        cout << "3. Laporan Pembayaran\n";
        cout << "4. Rekap Semua Laporan\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                cout << "\n📄 [LAPORAN SIMPANAN]\n";
                cout << "Jenis: " << simpanan.jenis << endl;
                cout << "Jumlah Transaksi : " << simpanan.jumlahTransaksi << endl;
                cout << "Total Uang       : Rp " << simpanan.totalUang << endl;
                cout << "Keterangan       : " << simpanan.keterangan << endl;
                break;

            case 2:
                cout << "\n📄 [LAPORAN PINJAMAN]\n";
                cout << "Jenis: " << pinjaman.jenis << endl;
                cout << "Jumlah Peminjam  : " << pinjaman.jumlahTransaksi << endl;
                cout << "Total Pinjaman   : Rp " << pinjaman.totalUang << endl;
                cout << "Keterangan       : " << pinjaman.keterangan << endl;
                break;

            case 3:
                cout << "\n📄 [LAPORAN PEMBAYARAN]\n";
                cout << "Jenis: " << pembayaran.jenis << endl;
                cout << "Jumlah Transaksi : " << pembayaran.jumlahTransaksi << endl;
                cout << "Total Pembayaran : Rp " << pembayaran.totalUang << endl;
                cout << "Keterangan       : " << pembayaran.keterangan << endl;
                break;

            case 4:
                cout << "\n=== REKAP SEMUA LAPORAN ===\n";
                cout << left << setw(15) << "Jenis"
                     << setw(20) << "Jumlah Transaksi"
                     << setw(15) << "Total (Rp)" << endl;
                cout << "----------------------------------------------------\n";
                cout << left << setw(15) << simpanan.jenis
                     << setw(20) << simpanan.jumlahTransaksi
                     << setw(15) << simpanan.totalUang << endl;
                cout << left << setw(15) << pinjaman.jenis
                     << setw(20) << pinjaman.jumlahTransaksi
                     << setw(15) << pinjaman.totalUang << endl;
                cout << left << setw(15) << pembayaran.jenis
                     << setw(20) << pembayaran.jumlahTransaksi
                     << setw(15) << pembayaran.totalUang << endl;

                double totalSemua = simpanan.totalUang + pinjaman.totalUang + pembayaran.totalUang;
                cout << "----------------------------------------------------\n";
                cout << setw(35) << "TOTAL KESELURUHAN" << "Rp " << totalSemua << endl;
                break;
        }

    } while (pilih != 0);
}
