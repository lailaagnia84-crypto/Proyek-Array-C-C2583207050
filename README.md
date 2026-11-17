# Proyek-Array-C-C2583207050
## UTS ALPRO_LAILA AGNIA MUBAROKAH
## Sistem Monitoring Stok dan Penjualan Kantin Kampus
# Identitas Mahasiswa
- Nama : Laila Agnia Mubarokah
- NIM : C2583207050
- Kelas : PTI 3A
- Mata Kuliah : Algoritma dan Pemrograman Dasar Lanjutan
- Dosen Pengampu : Muhammad Taufik, M.Kom
- Nama Proyek : Sistem Monitoring Stok dan Penjualan Kantin Kampus
# Deskripsi Singkat
Sistem Monitoring Stok dan Penjualan Kantin Kampus ini berfungsi untuk membantu pengelola kantin kampus dalam mencatat dan memantau stok serta penjualan produk tanpa harus melakukan pencatatan secara manual. Aplikasi ini memudahkan pengelola untuk menambahkan dan mengedit data produk, memproses pembelian beberapa barang sekaligus dengan menghitung jumlah belanjaan dan total pembayaran secara otomatis, serta mengupdate stok setiap kali transaksi berhasil dilakukan. Pengelola juga bisa mencari produk dengan nama, mengurutkan produk berdasarkan harga atau jumlah yang terjual, melihat laporan penjualan beserta produk yang paling laris, serta menerima peringatan untuk produk yang stoknya sudah di bawah 5. Semua data disimpan dalam array selama program berjalan, yaitu array dua dimensi untuk menyimpan nama produk dan array satu dimensi untuk harga, stok, serta jumlah produk yang terjual, dengan kapasitas maksimal 50 produk.
# Daftar Fitur
1. Lihat Daftar Produk: menampilkan nomor, nama, harga, stok, dan jumlah terjual seluruh produk.
2. Tambah Produk: menambah produk baru (nama, harga, stok awal). Program menolak nama kosong, nama yang sudah ada, harga atau stok negatif, dan menolak jika kapasitas 50 produk sudah penuh.
3. Ubah Produk: mengubah harga dan stok produk berdasarkan nomor produk. Nilai negatif ditolak.
4. Transaksi Penjualan: memproses pembelian beberapa jenis produk dalam satu transaksi. Program memeriksa stok, menghitung subtotal dan total pembayaran, lalu mengurangi stok dan menambah jumlah terjual setelah transaksi berhasil. Pembelian melebihi stok atau berjumlah nol/negatif ditolak.
5. Tambah Stok: menambah stok produk yang sudah ada. Jumlah tambahan harus lebih dari nol.
6. Cari Produk: mencari produk berdasarkan nama (tidak membedakan huruf besar/kecil, cukup sebagian nama).
7. Urutkan Produk: mengurutkan produk berdasarkan harga dari termurah, atau berdasarkan jumlah terjual dari terbanyak.
8. Laporan Penjualan: menampilkan jumlah terjual dan pendapatan tiap produk, total unit terjual, total pendapatan, dan produk terlaris.
9. Cek Stok Menipis: menampilkan peringatan untuk produk yang stoknya kurang dari 5.
10. Keluar: menutup program.
# Penjelasan Penggunaan Array
Array menjadi struktur data utama program. Data produk disimpan dalam empat array dengan kapasitas maksimal 50 produk (MAKS_PRODUK = 50).
Array yang digunakan
- namaProduk[50][30]: array karakter 2 dimensi untuk nama produk. Baris menunjukkan produk ke-i, kolom menyimpan karakter nama (maksimal 29 karakter + \0).
- hargaProduk[50]: array 1 dimensi (int) untuk harga tiap produk.
- stokProduk[50]: array 1 dimensi (int) untuk stok tiap produk.
- terjualProduk[50]: array 1 dimensi (int) untuk jumlah unit terjual tiap produk.
Pengelolaan indeks dan jumlah data aktif
- Variabel jumlahProduk menyimpan banyaknya produk yang sedang aktif. Data valid berada pada indeks 0 sampai jumlahProduk - 1.
- Keempat array memakai indeks yang sama. Misalnya data produk ke-3 ada di namaProduk[2], hargaProduk[2], stokProduk[2], dan terjualProduk[2].
- Saat produk ditambah, data diisi pada indeks jumlahProduk, lalu jumlahProduk bertambah satu. Jika jumlahProduk sudah 50, penambahan ditolak.
- Nomor produk yang dilihat pengguna (mulai dari 1) diubah menjadi indeks array (mulai dari 0) dengan mengurangi 1, dan diperiksa agar tidak keluar dari rentang.
Perulangan pada array
- Menampilkan daftar, mencari produk, membuat laporan, dan mengecek stok menipis memakai perulangan for yang menelusuri indeks 0 sampai jumlahProduk - 1.
- Pengurutan memakai bubble sort. Saat dua produk ditukar, fungsi tukarProduk() menukar data di keempat array sekaligus, supaya nama, harga, stok, dan jumlah terjual tetap cocok untuk setiap produk.
# Petunjuk Kompilasi dan Menjalankan Program
Untuk mengompilasi dan menjalankan program ini, diperlukan compiler bahasa C seperti GCC. Sebagai alternatif, dapat digunakan aplikasi seperti Code::Blocks yang sudah menyertakan GCC di dalamnya. Selain itu, pastikan file main.c berada di satu folder agar proses kompilasi dapat berjalan dengan benar.
1. Windows (MinGW/GCC)
Buka Command Prompt atau PowerShell, lalu masuk ke folder proyek:
cd path\ke\Proyek-Array-C-NIM
Kompilasi:
gcc main.c -o kantin.exe
Jalankan:
kantin.exe
2. Memakai Code::Blocks 
Buka main.c lewat menu File → Open.
Klik Build and Run (Code::Blocks: F9).
Cara memakai program
- Setelah program berjalan, menu utama tampil. Ketik angka menu (0-9), lalu tekan Enter.
- Ikuti perintah yang muncul di layar, misalnya nomor produk dan jumlah beli.
- Ketik 0 di menu utama untuk keluar.
# Dokumentasi Pengujian dan Skenario
## Skenario 1: Tambah Produk
- Input/tindakan: pilih menu 2, lalu masukkan nama Teh Tarik, harga 7000, dan stok awal 15. Setelah itu pilih menu 1.
- Proses: program memeriksa kapasitas, nama, harga, dan stok, lalu menyimpan data ke indeks berikutnya pada keempat array.
- Hasil yang diharapkan: muncul pesan berhasil, dan Teh Botol tampil di daftar produk (jumlah produk menjadi 7/50).
- Bukti:
<img width="1366" height="768" alt="7d780828-ab50-4414-b716-36c71c6c6b64" src="https://github.com/user-attachments/assets/c0e0abbe-9033-4b57-9376-cfd0d0ad4135" />
## Skenario 2: Transaksi
- Input/tindakan: pilih menu 4, beli 6 Es Teh (nomor 3) dan 4 Nasi Goreng (nomor 1), lalu pilih selesai.
- Proses: program menghitung subtotal tiap produk (jumlah x harga), lalu menjumlahkannya menjadi total pembayaran.
- Hasil yang diharapkan: subtotal Es Teh Rp24.000, subtotal Nasi Goreng Rp60.000, dan total pembayaran Rp84.000.
- Bukti:
<img width="1366" height="768" alt="4fc290bd-daa2-4cd3-89a8-8ec501206ceb" src="https://github.com/user-attachments/assets/27b5143e-6ebe-4f2f-bc0b-544e9efc62fb" />
## Skenario 3: Pembaruan Stok
- Input/tindakan: setelah transaksi selesai, pilih menu 1.
- Proses: setelah transaksi berhasil, program mengurangi stok dan menambah jumlah terjual sesuai jumlah pembelian.
- Hasil yang diharapkan: stok Es Teh berubah dari 30 menjadi 24 dan terjual 6. Stok Nasi Goreng berubah dari 20 menjadi 16 dan terjual 4.
- Bukti:
<img width="1366" height="768" alt="4c6b2a36-b9a4-4575-8035-b6b3478909b1" src="https://github.com/user-attachments/assets/e59597e6-4acd-45dc-b0d7-4b00054a22db" />
## Skenario 4: Stok Tidak Cukup
- Input/tindakan: pilih menu 4, beli 10 Kopi Hitam (nomor 4) yang stoknya hanya 4.
- Proses: program membandingkan jumlah pembelian dengan stok yang tersedia sebelum memasukkan item ke transaksi.
- Hasil yang diharapkan: muncul pesan bahwa stok tidak cukup, pembelian ditolak, dan stok Kopi Hitam tetap 4.
- Bukti:
<img width="1366" height="768" alt="938b696c-a159-47e1-a031-5c68c8c2f0ea" src="https://github.com/user-attachments/assets/603055aa-fb05-475d-b3f7-68208ed1393d" />
## Skenario 5: Laporan
- Input/tindakan: pilih menu 8.
- Proses: program menelusuri seluruh produk untuk menjumlahkan unit terjual dan pendapatan (jumlah terjual x harga), lalu mencari produk dengan jumlah terjual terbanyak.
- Hasil yang diharapkan: total unit terjual 10, total pendapatan Rp84.000, dan produk terlaris Es Teh (6 unit).
- Bukti:
<img width="1366" height="768" alt="b700b3dc-40eb-42ce-8553-96cbf05d8bc5" src="https://github.com/user-attachments/assets/07521ea7-1a9a-4659-b42e-13074def5340" />
## Skenario 6: Pengurutan
- Input/tindakan: pilih menu 7, pilih urutan harga termurah. Ulangi menu 7 dan pilih urutan jumlah terjual terbanyak.
- Proses: program mengurutkan dengan bubble sort, dan menukar data di keempat array sekaligus agar data tiap produk tetap cocok.
- Hasil yang diharapkan: urutan harga dimulai dari Air Mineral (Rp3.000) dan diakhiri Nasi Goreng (Rp15.000). Urutan terjual dimulai dari Es Teh (6), lalu Nasi Goreng (4).
Bukti:
<img width="1366" height="768" alt="1b57bf3b-25ac-42d1-9f09-1b6ce9769eb1" src="https://github.com/user-attachments/assets/11bf39d2-b43a-4ad4-bcda-a286f355607f" />
<img width="1366" height="768" alt="69eb6553-1802-41b1-9343-b4f2d02d0c17" src="https://github.com/user-attachments/assets/60aa301e-e4d9-42aa-a193-5f1fbdeaf0d0" />
## Skenario 7: Pencarian dan Stok Menipis
- Input/tindakan: pilih menu 6 dan cari kata Teh. Setelah itu pilih menu 9.
- Proses: pencarian mencocokkan kata kunci dengan nama produk tanpa membedakan huruf besar/kecil. Cek stok menampilkan produk yang stoknya kurang dari 5.
- Hasil yang diharapkan: pencarian menemukan Es Teh dan Teh Tarik. Menu 9 menampilkan peringatan untuk Kopi Hitam (stok tinggal 4).
- Bukti:
<img width="1366" height="768" alt="199c6728-2861-414d-b665-c4bb8ae57709" src="https://github.com/user-attachments/assets/2684c458-d5fd-427a-a104-bb5263a70cf2" />
