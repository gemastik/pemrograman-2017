# Sirkus Keliling (Mudah)

Terdapat N kota di Negeri Asgem, yang dinomori dari 1 hingga N. Masyarakat Asgem menyenangi sirkus. Terdapat satu tim sirkus lokal pada setiap kota. Biaya pertahun untuk menggaji tim sirkus lokal pada kota ke-i adalah S[i].

Negeri Astik menawarkan tim-tim sirkus keliling untuk beroperasi di Negeri Asgem. Setiap tim sirkus keliling memiliki rute tertentu yang harus memenuhi seluruh syarat di bawah ini:

- Melalui 2 hingga N kota. Misalkan X adalah banyaknya kota yang dilalui oleh rute tersebut.
- Rute tersebut sirkular: secara berurutan, mulai dari kota K[1], kemudian menempuh sebuah ruas jalan menuju kota K[2], ..., kemudian menempuh sebuah ruas jalan menuju kota K[X], kemudian menempuh sebuah ruas jalan menuju kota K[1], dan seterusnya.
- {K[1], K[2], ..., K[X]} adalah kota-kota yang berbeda-beda.

Juga, agar masyarakat tidak bosan, setiap kota hanya boleh dilalui oleh paling banyak satu rute tim sirkus keliling.

Terdapat M ruas jalan **satu arah** di Negeri Asgem. Ruas jalan ke-i menghubungkan kota U[i] menuju kota V[i]. Untuk melewati ruas jalan tersebut, sebuah tim sirkus keliling akan dibebani ongkos tahunan sebesar W[i].

Pak Chanek, presiden Asgem, ingin melakukan penghematan anggaran tahunan pertunjukan sirkus. Oleh karena itu, ia berencana untuk merekrut nol atau lebih tim sirkus keliling, kemudian menghentikan operasi tim-tim sirkus lokal pada seluruh kota yang dilalui oleh rute-rute tim sirkus keliling tersebut. Anggaran tahunan pertunjukan sirkus akan menjadi total dari:

- jumlah gaji seluruh tim sirkus lokal yang masih beroperasi, dan
- jumlah seluruh ongkos ruas jalan yang dilewati oleh seluruh rute tim sirkus keliling.

Bantulah Pak Chanek untuk meminimumkan anggaran tahunan pertunjukan sirkus, serta menentukan banyaknya tim sirkus keliling yang direkrut dan rute masing-masing tim sirkus keliling untuk mencapai anggaran minimum tersebut.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N M
S[1] S[2] .. S[N]
U[1] V[1] W[1]
U[2] V[2] W[2]
.
.
U[M] V[M] W[M]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan jawaban dalam format berikut ini:

C R
X[1] K[1][1] K[1][2] .. K[1][X[1]]
X[2] K[2][1] K[2][2] .. K[2][X[2]]
.
.
X[R] K[R][1] K[R][2] .. K[R][X[R]]

dengan:

- C merupakan anggaran tahunan pertunjukan sirkus minimum.
- R merupakan banyaknya tim sirkus keliling yang direkrut.
- X[i] merupakan banyaknya kota yang dilalui oleh rute tim sirkus keliling ke-i.
- K[i][j] merupakan nomor kota urutan ke-j pada rute tim sirkus keliling ke-i.

Jika terdapat lebih dari satu cara yang menghasilkan anggaran minimum yang sama, keluarkan yang mana saja. Perhatikan bahwa Pak Chanek tidak harus meminimumkan banyaknya tim sirkus keliling yang direkrut.

### Contoh Masukan

```
4
2 2
9 10
1 2 3
2 1 4
3 6
2 2 2
1 2 1
2 3 1
3 1 1
2 1 1
3 2 1
1 3 1
2 2
1 2
1 2 3
2 1 4
4 4
2 2 2 2
1 2 1
2 1 1
3 4 1
4 3 1
```

### (Salah Satu) Contoh Keluaran

```
7 1
2 1 2
3 1
3 1 2 3
3 0
4 2
2 3 4
2 2 1
```

### Penjelasan

Untuk contoh pertama, anggaran sebesar 7 satuan adalah anggaran minimum yang mungkin dicapai. Berikut adalah ilustrasi penentuan sirkus yang sesuai dengan contoh keluaran (warna hijau menandakan sirkus yang ditentukan dalam anggaran minimum).

{Sample_1_OK.png}

Perhatikan bahwa terdapat penganggaran yang tidak optimal yaitu jika kedua kota menggunakan sirkus lokal yang membutuhkan anggaran sebesar 19 satuan, seperti pada ilustrasi berikut.

{Sample_1_NOT_OK.png}

Untuk contoh kedua, anggaran sebesar 3 satuan adalah anggaran minimum yang mungkin dicapai. Terdapat tepat dua penentuan sirkus yang menghasilkan anggaran minimum, yaitu sesuai dengan dua ilustrasi berikut.

{Sample_2_OK_1.png}

{Sample_2_OK_2.png}

Berikut adalah contoh penentuan sirkus yang tidak optimal.

{Sample_2_NOT_OK.png}

Untuk contoh ketiga, anggaran sebesar 3 satuan adalah anggaran minimum yang mungkin dicapai yaitu dengan tetap menggunakan sirkus lokal dari kedua kota.

{Sample_3_OK.png}

Untuk contoh keempat, anggaran sebesar 4 satuan adalah anggaran minimum yang mungkin dicapai, yaitu dengan menggunakan sirkus keliling untuk pasangan kota 1 dan 2 serta pasangan kota 3 dan 4.

{Sample_4_OK.png}

### Batasan

- 1 ≤ T ≤ 5
- 0 ≤ M ≤ N × (N-1)
- 1 ≤ S[i], W[i] ≤ 8.000.000
- 1 ≤ U[i], V[i] ≤ N
- U[i] ≠ V[i]
- (U[i], V[i]) ≠ (U[j], V[j]) untuk i ≠ j

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- 1 ≤ N ≤ 12
