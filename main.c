/*
 * Sistem Monitoring Stok dan Penjualan Kantin Kampus
 * Mata Kuliah : Algoritma dan Pemrograman Lanjutan
 *
 * Struktur data utama (array):
 *   namaProduk[MAKS_PRODUK][PANJANG_NAMA] -> array karakter 2 dimensi (nama)
 *   hargaProduk[MAKS_PRODUK]              -> array 1 dimensi (harga)
 *   stokProduk[MAKS_PRODUK]               -> array 1 dimensi (stok)
 *   terjualProduk[MAKS_PRODUK]            -> array 1 dimensi (jumlah terjual)
 *   jumlahProduk                          -> jumlah data aktif (indeks 0..jumlahProduk-1)
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAKS_PRODUK   50
#define PANJANG_NAMA  30
#define BATAS_MENIPIS 5
#define MAKS_ITEM_TRX 50

char namaProduk[MAKS_PRODUK][PANJANG_NAMA];
int  hargaProduk[MAKS_PRODUK];
int  stokProduk[MAKS_PRODUK];
int  terjualProduk[MAKS_PRODUK];
int  jumlahProduk = 0;

/* ---------- Fungsi bantu input ---------- */

/* Membaca satu bilangan bulat dengan aman; mengulang jika input bukan angka */
int bacaInt(const char *prompt) {
    int nilai;
    char sisa;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &nilai) == 1) {
            while ((sisa = getchar()) != '\n' && sisa != EOF);
            return nilai;
        }
        printf("  [!] Input harus berupa angka bulat.\n");
        while ((sisa = getchar()) != '\n' && sisa != EOF);
        if (sisa == EOF) return 0;
    }
}

/* Membaca satu baris teks (boleh mengandung spasi) */
void bacaTeks(const char *prompt, char *tujuan, int ukuran) {
    printf("%s", prompt);
    if (fgets(tujuan, ukuran, stdin) == NULL) { tujuan[0] = '\0'; return; }
    tujuan[strcspn(tujuan, "\n")] = '\0';
}

/* Mengubah string menjadi huruf kecil (untuk pencarian tanpa membedakan huruf) */
void keKecil(const char *asal, char *hasil) {
    int i;
    for (i = 0; asal[i] != '\0'; i++) hasil[i] = (char)tolower((unsigned char)asal[i]);
    hasil[i] = '\0';
}

void garis(void) {
    printf("--------------------------------------------------------------\n");
}

/* ---------- Data awal ---------- */

void isiDataAwal(void) {
    const char *nama[] = {"Nasi Goreng", "Mie Ayam", "Es Teh", "Kopi Hitam",
                          "Roti Bakar", "Air Mineral"};
    int harga[] = {15000, 12000, 4000, 5000, 8000, 3000};
    int stok[]  = {20, 15, 30, 4, 10, 25};
    int i;
    for (i = 0; i < 6; i++) {
        strcpy(namaProduk[i], nama[i]);
        hargaProduk[i] = harga[i];
        stokProduk[i] = stok[i];
        terjualProduk[i] = 0;
    }
    jumlahProduk = 6;
}

/* ---------- Tampilan ---------- */

void tampilMenu(void) {
    printf("\n=== KANTIN KAMPUS - MONITORING STOK & PENJUALAN ===\n");
    printf("1. Lihat Daftar Produk     6. Cari Produk\n");
    printf("2. Tambah Produk           7. Urutkan Produk\n");
    printf("3. Ubah Produk             8. Laporan Penjualan\n");
    printf("4. Transaksi Penjualan     9. Cek Stok Menipis\n");
    printf("5. Tambah Stok             0. Keluar\n");
}

void tampilBaris(int i) {
    printf("%-4d %-25s Rp%-10d %-6d %-6d\n", i + 1, namaProduk[i],
           hargaProduk[i], stokProduk[i], terjualProduk[i]);
}

void lihatDaftarProduk(void) {
    int i;
    printf("\n== DAFTAR PRODUK (%d/%d) ==\n", jumlahProduk, MAKS_PRODUK);
    garis();
    printf("%-4s %-25s %-12s %-6s %-6s\n", "No", "Nama", "Harga", "Stok", "Terjual");
    garis();
    if (jumlahProduk == 0) printf("Belum ada produk.\n");
    for (i = 0; i < jumlahProduk; i++) tampilBaris(i);
    garis();
}

/* ---------- Manajemen produk ---------- */

/* Mengembalikan indeks produk dengan nama sama persis (tanpa beda huruf), atau -1 */
int cariIndeksNama(const char *nama) {
    char a[PANJANG_NAMA], b[PANJANG_NAMA];
    int i;
    keKecil(nama, a);
    for (i = 0; i < jumlahProduk; i++) {
        keKecil(namaProduk[i], b);
        if (strcmp(a, b) == 0) return i;
    }
    return -1;
}

void tambahProduk(void) {
    char nama[PANJANG_NAMA];
    int harga, stok;

    if (jumlahProduk >= MAKS_PRODUK) {
        printf("[!] Kapasitas penuh (maksimal %d produk). Produk tidak dapat ditambah.\n", MAKS_PRODUK);
        return;
    }
    bacaTeks("Nama produk : ", nama, PANJANG_NAMA);
    if (strlen(nama) == 0) { printf("[!] Nama produk tidak boleh kosong.\n"); return; }
    if (cariIndeksNama(nama) != -1) { printf("[!] Produk dengan nama tersebut sudah ada.\n"); return; }

    harga = bacaInt("Harga       : ");
    if (harga < 0) { printf("[!] Harga tidak boleh negatif.\n"); return; }
    stok = bacaInt("Stok awal   : ");
    if (stok < 0) { printf("[!] Stok tidak boleh negatif.\n"); return; }

    strcpy(namaProduk[jumlahProduk], nama);
    hargaProduk[jumlahProduk] = harga;
    stokProduk[jumlahProduk] = stok;
    terjualProduk[jumlahProduk] = 0;
    jumlahProduk++;
    printf("[OK] Produk '%s' berhasil ditambahkan.\n", nama);
}

/* Meminta nomor produk; mengembalikan indeks (0-based) atau -1 jika tidak valid */
int pilihProduk(void) {
    int no = bacaInt("Nomor produk : ");
    if (no < 1 || no > jumlahProduk) {
        printf("[!] Nomor produk %d tidak ditemukan.\n", no);
        return -1;
    }
    return no - 1;
}

void ubahProduk(void) {
    int idx, harga, stok;
    lihatDaftarProduk();
    idx = pilihProduk();
    if (idx < 0) return;
    printf("Mengubah '%s' (harga Rp%d, stok %d)\n", namaProduk[idx], hargaProduk[idx], stokProduk[idx]);
    harga = bacaInt("Harga baru   : ");
    if (harga < 0) { printf("[!] Harga tidak boleh negatif.\n"); return; }
    stok = bacaInt("Stok baru    : ");
    if (stok < 0) { printf("[!] Stok tidak boleh negatif.\n"); return; }
    hargaProduk[idx] = harga;
    stokProduk[idx] = stok;
    printf("[OK] Data produk berhasil diubah.\n");
}

void tambahStok(void) {
    int idx, jumlah;
    lihatDaftarProduk();
    idx = pilihProduk();
    if (idx < 0) return;
    jumlah = bacaInt("Jumlah stok yang ditambah : ");
    if (jumlah <= 0) { printf("[!] Jumlah tambahan harus lebih dari nol.\n"); return; }
    stokProduk[idx] += jumlah;
    printf("[OK] Stok '%s' sekarang %d.\n", namaProduk[idx], stokProduk[idx]);
}

/* ---------- Transaksi ---------- */

void transaksiPenjualan(void) {
    int itemIdx[MAKS_ITEM_TRX], itemQty[MAKS_ITEM_TRX];
    int itemSubtotal[MAKS_ITEM_TRX];
    int jumlahItem = 0, total = 0;
    int reserved[MAKS_PRODUK] = {0};   /* jumlah yang sudah masuk keranjang per produk */
    int i, lagi = 1;

    if (jumlahProduk == 0) { printf("[!] Belum ada produk.\n"); return; }
    lihatDaftarProduk();
    printf("Masukkan produk satu per satu. Stok baru berkurang jika transaksi disetujui.\n");

    while (lagi && jumlahItem < MAKS_ITEM_TRX) {
        int idx = pilihProduk();
        int qty;
        if (idx >= 0) {
            qty = bacaInt("Jumlah beli   : ");
            if (qty <= 0) {
                printf("[!] Jumlah pembelian harus lebih dari nol.\n");
            } else if (qty + reserved[idx] > stokProduk[idx]) {
                printf("[!] Stok tidak cukup. Stok '%s' tersedia %d (sudah di keranjang %d).\n",
                       namaProduk[idx], stokProduk[idx], reserved[idx]);
            } else {
                itemIdx[jumlahItem] = idx;
                itemQty[jumlahItem] = qty;
                itemSubtotal[jumlahItem] = qty * hargaProduk[idx];
                reserved[idx] += qty;
                total += itemSubtotal[jumlahItem];
                jumlahItem++;
                printf("[OK] %d x %s ditambahkan ke keranjang.\n", qty, namaProduk[idx]);
            }
        }
        lagi = bacaInt("Tambah produk lain? (1 = ya, 0 = selesai) : ");
    }

    if (jumlahItem == 0) { printf("Transaksi dibatalkan (keranjang kosong).\n"); return; }

    printf("\n== RINCIAN TRANSAKSI ==\n");
    garis();
    printf("%-25s %-6s %-10s %-10s\n", "Produk", "Qty", "Harga", "Subtotal");
    garis();
    for (i = 0; i < jumlahItem; i++) {
        printf("%-25s %-6d %-10d %-10d\n", namaProduk[itemIdx[i]], itemQty[i],
               hargaProduk[itemIdx[i]], itemSubtotal[i]);
    }
    garis();
    printf("TOTAL PEMBAYARAN : Rp%d\n", total);

    /* Kurangi stok dan tambah jumlah terjual setelah transaksi berhasil */
    for (i = 0; i < jumlahItem; i++) {
        stokProduk[itemIdx[i]] -= itemQty[i];
        terjualProduk[itemIdx[i]] += itemQty[i];
    }
    printf("[OK] Transaksi berhasil. Stok dan jumlah terjual diperbarui.\n");
}

/* ---------- Pencarian ---------- */

void cariProduk(void) {
    char kata[PANJANG_NAMA], kataKecil[PANJANG_NAMA], namaKecil[PANJANG_NAMA];
    int i, ketemu = 0;
    bacaTeks("Kata kunci nama produk : ", kata, PANJANG_NAMA);
    if (strlen(kata) == 0) { printf("[!] Kata kunci tidak boleh kosong.\n"); return; }
    keKecil(kata, kataKecil);

    printf("\n== HASIL PENCARIAN '%s' ==\n", kata);
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        keKecil(namaProduk[i], namaKecil);
        if (strstr(namaKecil, kataKecil) != NULL) { tampilBaris(i); ketemu++; }
    }
    garis();
    if (!ketemu) printf("Produk tidak ditemukan.\n");
    else printf("Ditemukan %d produk.\n", ketemu);
}

/* ---------- Pengurutan ---------- */

/* Menukar seluruh data dua produk agar keempat array tetap sinkron */
void tukarProduk(int a, int b) {
    char tmpNama[PANJANG_NAMA];
    int tmp;
    strcpy(tmpNama, namaProduk[a]);
    strcpy(namaProduk[a], namaProduk[b]);
    strcpy(namaProduk[b], tmpNama);
    tmp = hargaProduk[a];   hargaProduk[a] = hargaProduk[b];     hargaProduk[b] = tmp;
    tmp = stokProduk[a];    stokProduk[a] = stokProduk[b];       stokProduk[b] = tmp;
    tmp = terjualProduk[a]; terjualProduk[a] = terjualProduk[b]; terjualProduk[b] = tmp;
}

/* Bubble sort: mode 1 = harga termurah, mode 2 = terjual terbanyak */
void urutkan(int mode) {
    int i, j;
    for (i = 0; i < jumlahProduk - 1; i++) {
        for (j = 0; j < jumlahProduk - 1 - i; j++) {
            int tukar;
            if (mode == 1) tukar = hargaProduk[j] > hargaProduk[j + 1];
            else           tukar = terjualProduk[j] < terjualProduk[j + 1];
            if (tukar) tukarProduk(j, j + 1);
        }
    }
}

void urutkanProduk(void) {
    int pilihan;
    printf("\n1. Urutkan harga dari termurah\n2. Urutkan jumlah terjual dari terbanyak\n");
    pilihan = bacaInt("Pilihan : ");
    if (pilihan != 1 && pilihan != 2) { printf("[!] Pilihan urutan tidak tersedia.\n"); return; }
    urutkan(pilihan);
    printf("[OK] Produk berhasil diurutkan.\n");
    lihatDaftarProduk();
}

/* ---------- Laporan ---------- */

void laporanPenjualan(void) {
    int i, totalUnit = 0, totalPendapatan = 0, terlaris = 0;
    printf("\n== LAPORAN PENJUALAN ==\n");
    garis();
    printf("%-4s %-25s %-8s %-10s %-12s\n", "No", "Nama", "Terjual", "Harga", "Pendapatan");
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        int pendapatan = terjualProduk[i] * hargaProduk[i];
        printf("%-4d %-25s %-8d %-10d %-12d\n", i + 1, namaProduk[i],
               terjualProduk[i], hargaProduk[i], pendapatan);
        totalUnit += terjualProduk[i];
        totalPendapatan += pendapatan;
        if (terjualProduk[i] > terjualProduk[terlaris]) terlaris = i;
    }
    garis();
    printf("Total unit terjual : %d\n", totalUnit);
    printf("Total pendapatan   : Rp%d\n", totalPendapatan);
    if (jumlahProduk == 0 || totalUnit == 0)
        printf("Produk terlaris    : belum ada penjualan\n");
    else
        printf("Produk terlaris    : %s (%d unit)\n", namaProduk[terlaris], terjualProduk[terlaris]);
}

void cekStokMenipis(void) {
    int i, ada = 0;
    printf("\n== STOK MENIPIS (< %d) ==\n", BATAS_MENIPIS);
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        if (stokProduk[i] < BATAS_MENIPIS) {
            printf("[PERINGATAN] %-25s stok tinggal %d\n", namaProduk[i], stokProduk[i]);
            ada++;
        }
    }
    garis();
    if (!ada) printf("Semua stok aman.\n");
}

/* ---------- Program utama ---------- */

int main(void) {
    int pilihan;
    isiDataAwal();
    do {
        tampilMenu();
        pilihan = bacaInt("Pilih menu : ");
        switch (pilihan) {
            case 1: lihatDaftarProduk();  break;
            case 2: tambahProduk();       break;
            case 3: ubahProduk();         break;
            case 4: transaksiPenjualan(); break;
            case 5: tambahStok();         break;
            case 6: cariProduk();         break;
            case 7: urutkanProduk();      break;
            case 8: laporanPenjualan();   break;
            case 9: cekStokMenipis();     break;
            case 0: printf("Terima kasih. Program selesai.\n"); break;
            default: printf("[!] Pilihan menu tidak tersedia. Pilih 0-9.\n");
        }
    } while (pilihan != 0);
    return 0;
}
