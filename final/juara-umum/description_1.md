# Juara Umum (Mudah)

Tahun ini, Gemastik terdiri atas N cabang lomba, yang dinomori dari 1 hingga N. Terdapat M universitas sebagai peserta Gemastik, yang dinomori dari 1 hingga M. Setiap universitas mengirimkan tepat satu tim untuk setiap cabang lomba.

Untuk setiap cabang lomba, akan diambil tiga tim berbeda sebagai pemenang, yang berturut-turut akan memperoleh medali emas, perak, dan perunggu. Setelah semua cabang lomba dipertandingkan, peringkat seluruh universitas akan diurutkan berdasarkan perolehan medali. Universitas A akan meraih peringkat yang lebih baik daripada universitas B, apabila:

- perolehan emas A > perolehan emas B, atau
- perolehan emas A = perolehan emas B dan perolehan perak A > perolehan perak B, atau
- perolehan emas A = perolehan emas B, perolehan perak A = perolehan perak B, dan perolehan perunggu A > perolehan perunggu B.

Akhirnya, universitas yang memiliki peringkat terbaik akan mendapatkan gelar juara umum.

Perhatikan bahwa menurut sistem pemeringkatan di atas, mungkin saja terdapat lebih dari satu juara umum. Mungkinkah terdapat tepat K universitas sebagai juara umum?

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N M K
```

### Format Keluaran

Untuk setiap kasus uji:

Jika tidak mungkin terdapat tepat K universitas sebagai juara umum, keluarkan:

```
mustahil
```

Jika mungkin, keluarkan:

```
mungkin
G[1] S[1] B[1]
G[2] S[2] B[2]
.
.
G[N] S[N] B[N]
```

dengan G[i], S[i], B[i] masing-masing merupakan nomor universitas yang mendapatkan medali emas, perak, dan perunggu pada cabang lomba ke-i. Jika terdapat lebih dari satu kemungkinan, keluarkan yang mana saja.

### Contoh Masukan

```
2
3 3 2
5 10 2
```

### (Salah Satu) Contoh Keluaran

```
mustahil
mungkin
1 9 10
1 9 10
2 6 7
2 6 7
5 9 10
```

### Penjelasan

Untuk contoh kedua, universitas 1 dan universitas 2 menjadi juara umum bersama, karena masing-masing memperoleh 2 medali emas.

### Batasan

- 1 ≤ T ≤ 10
- 1 ≤ N ≤ 50.000
- 3 ≤ M ≤ 50.000
- K ≤ N

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- K = 2
