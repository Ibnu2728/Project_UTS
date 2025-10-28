#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

// ==================== DEKLARASI STRUCT & EXTERN ====================
struct Anggota {
    string id;
    string nama;
    string alamat;
    double saldo;
};

struct Pinjaman {
    string idPinjaman;
    string idAnggota;
    string tanggal;
    double jumlahPinjaman;
    double bunga;
    int lamaCicilan;
    double totalPinjaman;
    double sisaPinjaman;
    string status;
};

struct Simpanan {
    string idSimpanan;
    string idAnggota;
    string tanggal;
    string jenisSimpanan;
    double jumlah;
    double saldoAkhir;
};

struct Pembayaran {
    string idPembayaran;
    string idAnggota;
    string idPinjaman;
    string tanggal;
    double jumlahPokok;
    double bunga;
    double totalBayar;
    double sisaPinjaman;
    string status;
};

extern vector<Anggota> dataAnggota;
extern vector<Pinjaman> dataPinjaman;
extern vector<Simpanan> daftarSimpanan;
extern vector<Pembayaran> dataBayar;

// ==================== STRUCT LAPORAN ====================
struct Laporan {
    string jenis;
    int jumlahTransaksi;
    double totalUang;
    string keterangan;
};

// ==================== FUNGSI GENERATE LAPORAN REAL-TIME ====================
Laporan generateLaporanSimpanan() {
    Laporan laporan;
    laporan.jenis = "Simpanan";
    laporan.jumlahTransaksi = daftarSimpanan.size();
    laporan.totalUang = 0;
    
    for (auto& simpanan : daftarSimpanan) {
        laporan.totalUang += simpanan.jumlah;
    }
    
    laporan.keterangan = "Total dana yang disimpan anggota (Real-time)";
    return laporan;
}

Laporan generateLaporanPinjaman() {
    Laporan laporan;
    laporan.jenis = "Pinjaman";
    laporan.jumlahTransaksi = 0;
    laporan.totalUang = 0;
    
    for (auto& pinjaman : dataPinjaman) {
        if (pinjaman.status == "Belum Lunas") {
            laporan.jumlahTransaksi++;
            laporan.totalUang += pinjaman.sisaPinjaman;
        }
    }
    
    laporan.keterangan = "Dana yang masih dalam masa cicilan (Real-time)";
    return laporan;
}

Laporan generateLaporanPembayaran() {
    Laporan laporan;
    laporan.jenis = "Pembayaran";
    laporan.jumlahTransaksi = dataBayar.size();
    laporan.totalUang = 0;
    
    for (auto& bayar : dataBayar) {
        laporan.totalUang += bayar.totalBayar;
    }
    
    laporan.keterangan = "Total pembayaran angsuran (Real-time)";
    return laporan;
}

Laporan generateLaporanAnggota() {
    Laporan laporan;
    laporan.jenis = "Anggota";
    laporan.jumlahTransaksi = dataAnggota.size();
    laporan.totalUang = 0;
    
    for (auto& anggota : dataAnggota) {
        laporan.totalUang += anggota.saldo;
    }
    
    laporan.keterangan = "Total saldo semua anggota (Real-time)";
    return laporan;
}

// ==================== FUNGSI TAMPILKAN LAPORAN DETAIL ====================
void tampilkanLaporanSimpananDetail() {
    cout << "\n📊 [LAPORAN SIMPANAN DETAIL]\n";
    cout << "==========================================\n";
    
    if (daftarSimpanan.empty()) {
        cout << "Belum ada data simpanan.\n";
        return;
    }
    
    double totalPokok = 0, totalWajib = 0, totalSukarela = 0;
    
    for (auto& simpanan : daftarSimpanan) {
        if (simpanan.jenisSimpanan == "Pokok") totalPokok += simpanan.jumlah;
        else if (simpanan.jenisSimpanan == "Wajib") totalWajib += simpanan.jumlah;
        else if (simpanan.jenisSimpanan == "Sukarela") totalSukarela += simpanan.jumlah;
    }
    
    cout << "Total Simpanan Pokok    : Rp " << totalPokok << endl;
    cout << "Total Simpanan Wajib    : Rp " << totalWajib << endl;
    cout << "Total Simpanan Sukarela : Rp " << totalSukarela << endl;
    cout << "Total Semua Simpanan    : Rp " << (totalPokok + totalWajib + totalSukarela) << endl;
    cout << "Jumlah Transaksi        : " << daftarSimpanan.size() << " transaksi\n";
}

void tampilkanLaporanPinjamanDetail() {
    cout << "\n📊 [LAPORAN PINJAMAN DETAIL]\n";
    cout << "==========================================\n";
    
    if (dataPinjaman.empty()) {
        cout << "Belum ada data pinjaman.\n";
        return;
    }
    
    int jumlahLunas = 0, jumlahBelumLunas = 0;
    double totalPinjamanAktif = 0, totalPinjamanLunas = 0;
    
    for (auto& pinjaman : dataPinjaman) {
        if (pinjaman.status == "Lunas") {
            jumlahLunas++;
            totalPinjamanLunas += pinjaman.totalPinjaman;
        } else {
            jumlahBelumLunas++;
            totalPinjamanAktif += pinjaman.sisaPinjaman;
        }
    }
    
    cout << "Pinjaman Lunas         : " << jumlahLunas << " pinjaman\n";
    cout << "Pinjaman Aktif         : " << jumlahBelumLunas << " pinjaman\n";
    cout << "Total Pinjaman Lunas   : Rp " << totalPinjamanLunas << endl;
    cout << "Total Pinjaman Aktif   : Rp " << totalPinjamanAktif << endl;
    cout << "Total Semua Pinjaman   : Rp " << (totalPinjamanLunas + totalPinjamanAktif) << endl;
}

void tampilkanLaporanPembayaranDetail() {
    cout << "\n📊 [LAPORAN PEMBAYARAN DETAIL]\n";
    cout << "==========================================\n";
    
    if (dataBayar.empty()) {
        cout << "Belum ada data pembayaran.\n";
        return;
    }
    
    double totalPokok = 0, totalBunga = 0, totalDenda = 0;
    
    for (auto& bayar : dataBayar) {
        totalPokok += bayar.jumlahPokok;
        totalBunga += bayar.bunga;
        // Denda dihitung dari selisih total bayar dikurangi pokok dan bunga
        totalDenda += (bayar.totalBayar - bayar.jumlahPokok - bayar.bunga);
    }
    
    cout << "Total Pokok Dibayar    : Rp " << totalPokok << endl;
    cout << "Total Bunga Dibayar    : Rp " << totalBunga << endl;
    cout << "Total Denda Dibayar    : Rp " << totalDenda << endl;
    cout << "Total Semua Pembayaran : Rp " << (totalPokok + totalBunga + totalDenda) << endl;
    cout << "Jumlah Transaksi       : " << dataBayar.size() << " transaksi\n";
}

void tampilkanLaporanAnggotaDetail() {
    cout << "\n📊 [LAPORAN ANGGOTA DETAIL]\n";
    cout << "==========================================\n";
    
    if (dataAnggota.empty()) {
        cout << "Belum ada data anggota.\n";
        return;
    }
    
    double totalSaldo = 0;
    double saldoTertinggi = 0;
    string anggotaTerbanyak = "";
    
    for (auto& anggota : dataAnggota) {
        totalSaldo += anggota.saldo;
        if (anggota.saldo > saldoTertinggi) {
            saldoTertinggi = anggota.saldo;
            anggotaTerbanyak = anggota.nama;
        }
    }
    
    cout << "Jumlah Anggota         : " << dataAnggota.size() << " orang\n";
    cout << "Total Saldo Semua      : Rp " << totalSaldo << endl;
    cout << "Rata-rata Saldo        : Rp " << (totalSaldo / dataAnggota.size()) << endl;
    cout << "Saldo Tertinggi        : Rp " << saldoTertinggi << endl;
    cout << "Anggota Saldo Tertinggi: " << anggotaTerbanyak << endl;
}

// ==================== MENU LAPORAN ====================
void menuLaporan() {
    int pilih;
    do {
        cout << "\n=== MENU LAPORAN ===\n";
        cout << "1. Laporan Simpanan\n";
        cout << "2. Laporan Pinjaman\n";
        cout << "3. Laporan Pembayaran\n";
        cout << "4. Laporan Anggota\n";
        cout << "5. Rekap Semua Laporan\n";
        cout << "6. Laporan Detail Lengkap\n";
        cout << "0. Kembali ke Menu Utama\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: {
                Laporan simpanan = generateLaporanSimpanan();
                cout << "\n📄 [LAPORAN SIMPANAN]\n";
                cout << "Jenis: " << simpanan.jenis << endl;
                cout << "Jumlah Transaksi : " << simpanan.jumlahTransaksi << endl;
                cout << "Total Uang       : Rp " << fixed << setprecision(0) << simpanan.totalUang << endl;
                cout << "Keterangan       : " << simpanan.keterangan << endl;
                break;
            }

            case 2: {
                Laporan pinjaman = generateLaporanPinjaman();
                cout << "\n📄 [LAPORAN PINJAMAN]\n";
                cout << "Jenis: " << pinjaman.jenis << endl;
                cout << "Jumlah Peminjam  : " << pinjaman.jumlahTransaksi << endl;
                cout << "Total Pinjaman   : Rp " << fixed << setprecision(0) << pinjaman.totalUang << endl;
                cout << "Keterangan       : " << pinjaman.keterangan << endl;
                break;
            }

            case 3: {
                Laporan pembayaran = generateLaporanPembayaran();
                cout << "\n📄 [LAPORAN PEMBAYARAN]\n";
                cout << "Jenis: " << pembayaran.jenis << endl;
                cout << "Jumlah Transaksi : " << pembayaran.jumlahTransaksi << endl;
                cout << "Total Pembayaran : Rp " << fixed << setprecision(0) << pembayaran.totalUang << endl;
                cout << "Keterangan       : " << pembayaran.keterangan << endl;
                break;
            }

            case 4: {
                Laporan anggota = generateLaporanAnggota();
                cout << "\n📄 [LAPORAN ANGGOTA]\n";
                cout << "Jenis: " << anggota.jenis << endl;
                cout << "Jumlah Anggota   : " << anggota.jumlahTransaksi << endl;
                cout << "Total Saldo      : Rp " << fixed << setprecision(0) << anggota.totalUang << endl;
                cout << "Keterangan       : " << anggota.keterangan << endl;
                break;
            }

            case 5: {
                Laporan simpanan = generateLaporanSimpanan();
                Laporan pinjaman = generateLaporanPinjaman();
                Laporan pembayaran = generateLaporanPembayaran();
                Laporan anggota = generateLaporanAnggota();

                cout << "\n=== REKAP SEMUA LAPORAN ===\n";
                cout << left << setw(12) << "Jenis"
                     << setw(18) << "Jumlah Transaksi"
                     << setw(20) << "Total (Rp)" 
                     << "Keterangan" << endl;
                cout << "-----------------------------------------------------------------\n";
                
                cout << left << setw(12) << simpanan.jenis
                     << setw(18) << simpanan.jumlahTransaksi
                     << setw(20) << fixed << setprecision(0) << simpanan.totalUang
                     << simpanan.keterangan << endl;
                     
                cout << left << setw(12) << pinjaman.jenis
                     << setw(18) << pinjaman.jumlahTransaksi
                     << setw(20) << pinjaman.totalUang
                     << pinjaman.keterangan << endl;
                     
                cout << left << setw(12) << pembayaran.jenis
                     << setw(18) << pembayaran.jumlahTransaksi
                     << setw(20) << pembayaran.totalUang
                     << pembayaran.keterangan << endl;
                     
                cout << left << setw(12) << anggota.jenis
                     << setw(18) << anggota.jumlahTransaksi
                     << setw(20) << anggota.totalUang
                     << anggota.keterangan << endl;

                double totalSemua = simpanan.totalUang + pinjaman.totalUang + pembayaran.totalUang + anggota.totalUang;
                cout << "-----------------------------------------------------------------\n";
                cout << setw(30) << "TOTAL KESELURUHAN" << "Rp " << totalSemua << endl;
                break;
            }

            case 6: {
                cout << "\n=== LAPORAN DETAIL LENGKAP ===\n";
                tampilkanLaporanAnggotaDetail();
                tampilkanLaporanSimpananDetail();
                tampilkanLaporanPinjamanDetail();
                tampilkanLaporanPembayaranDetail();
                break;
            }

            case 0:
                cout << "Kembali ke menu utama...\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);
}