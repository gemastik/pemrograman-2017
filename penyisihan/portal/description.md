# Saklar Lhompat II

Ruang baca di perpustakaan Fasilkom UI berisi meja-meja yang tersusun atas R baris dan C kolom. Uniknya, meja-meja tersebut memiliki ketinggian berbeda-beda. Saat ini, terdapat N mahasiswa yang sedang berada di dalam ruang baca tersebut. Informasi ini dinyatakan oleh matriks G sebagai berikut:

- Jika meja (baris i, kolom j) kosong, maka G[i][j] berisi ketinggian meja tersebut, berupa sebuah bilangan bulat antara 0 - 9.
- Jika meja (baris i, kolom j) ditempati mahasiswa, maka G[i][j] berisi nama mahasiswa tersebut, berupa sebuah huruf antara A - Z. Meja ini memiliki ketinggian 0.

Mahasiswa-mahasiswa tersebut menyalakan laptop mereka di meja masing-masing. Mereka perlu untuk menyambungkan kabel laptop masing-masing ke stop kontak. Stop-stop kontak hanya terdapat pada meja-meja pada baris pertama. Setiap meja pada baris pertama berisi satu stop kontak.

Untuk menghindari rebutan stop kontak, Pak Chanek, sang kepala pustakawan, akan menentukan untuk setiap mahasiswa, stop kontak mana yang harus disambungkan ke laptopnya. Setiap stop kontak di baris pertama akan disambungkan ke paling banyak satu laptop. Oleh Pak Chanek, penentuan ini disebut dengan "konfigurasi". Konfigurasi yang dipilih Pak Chanek akan selalu sedemikian sehingga, untuk setiap dua mahasiswa A dan B, apabila nama mahasiswa A lebih kecil secara leksikografis dari mahasiswa B, maka stop kontak yang harus disambungkan ke laptop mahasiswa A akan berada di sebelah kiri dari stop kontak yang harus disambungkn ke laptop mahasiswa B.

Untuk menyambungkan sebuah laptop ke sebuah stop kontak yang ditentukan Pak Chanek, kabel laptop harus bermula pada meja tempat mahasiswa pemilik laptop tersebut berada, kemudian melewati meja-meja lain sampai pada sebuah meja pada baris pertama. Setiap meja yang dilewati, kecuali meja pertama (yang berisi laptop), harus berada tepat di sebelah kiri, atas, kanan, atau bawah dari meja sebelumnya. Kabel laptop boleh melewati meja manapun, termasuk meja-meja lain pada baris pertama, meja-meja yang berisi laptop lain, maupun meja-meja yang dilewati kabel laptop lain.

Panjang kabel efektif sebuah penyambungan didefinisikan sebagai total dari:

- banyaknya meja yang dilewati, termasuk meja pertama dan meja terakhir, dan
- jumlah dari perbedaan tinggi dari setiap meja yang bersebelahan yang dilewati.

Setiap mahasiswa akan selalu memilih cara sedemikian sehingga panjang kabel efektif untuk menyambungkan laptopnya ke stop kontak yang telah ditentukan, sependek mungkin. Panjang terpendek ini didefinisikan sebagai "tingkat efisiensi penyambungan laptop" untuk mahasiswa tersebut.

Akhirnya, "tingkat kesemrawutan konfigurasi" didefinisikan sebagai tingkat efisiensi penyambungan laptop terbesar di antara N penyambungan laptop, pada konfigurasi tersebut.

Tentu saja, terdapat banyak konfigurasi yang dapat dipilih Pak Chanek. Tentukan jumlah dari tingkat kesemrawutan konfigurasi, untuk seluruh kemungkinan konfigurasi berbeda, modulo 1.000.000.007. Dua buah konfigurasi dikatakan berbeda apabila terdapat setidaknya seorang mahasiswa yang harus menyambungkan ke stop kontak yang berbeda di antara kedua konfigurasi tersebut.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
R C N
G[1][1] G[1][2] ... G[1][C]
G[2][1] G[2][2] ... G[2][C]
.
.
.
G[R][1] G[R][2] ... G[R][C]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan jumlah dari tingkat efisiensi seluruh portal, untuk seluruh kemungkinan pemasangan portal pasangan, modulo 1.000.000.007.

### Batasan

- 1 ≤ T ≤ 10
- 2 ≤ R ≤ 100
- 1 ≤ C ≤ 26
- G[i][j] berisi huruf besar alfabet 'A' - 'Z' atau bilangan 0 - 9
- G[1][j] = '0'
- G berisi tepat N buah huruf besar alfabet berbeda, yang masing-masing termasuk dalam N huruf besar alfabet pertama

### Subsoal 1

- N = 1

### Subsoal 2

- 1 ≤ N ≤ C
