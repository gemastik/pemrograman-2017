# Harta Kekayaan (Sulit)

Perusahaan Astik terdiri atas N karyawan, yang dinomori dari 1 hingga N. Setiap karyawan, kecuali karyawan 1, memiliki tepat seorang manajer, yang juga merupakan salah satu dari N karyawan tersebut. Manajer karyawan i adalah karyawan P[i]. Hubungan manajer-karyawan ini membentuk sebuah struktur _tree_ yang berakar pada karyawan 1.

Karyawan j adalah atasan dari karyawan i apabila j merupakan salah satu dari {P[i], P[P[i]], P[P[P[i]]], ..., 1}.

Pak Chanek adalah auditor keuangan untuk perusahaan Astik. Setiap karyawan melaporkan harta kekayaan masing-masing kepada Pak Chanek. Karyawan ke-i memiliki harta sebesar R[i].

Pak Chanek mendefinisikan fungsi audit(x, y) sebagai banyaknya karyawan z yang memenuhi seluruh syarat di bawah ini:

- Karyawan z merupakan atasan karyawan x
- Karyawan z merupakan atasan karyawan y
- R[z] > R[x]
- R[z] > R[y]

Untuk laporan tahun ini, Pak Chanek harus menghitung jumlah dari audit(x, y) untuk seluruh 1 ≤ x < y ≤ N. Bantulah dia!

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N
P[2] P[3] .. P[N]
R[1] R[2] R[3] .. R[N]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi jumlah dari audit(x, y) untuk seluruh 1 ≤ x < y ≤ N.

### Contoh Masukan

```
1
6
1 1 1 4 4
3 6 1 4 2 1
```

### Contoh Keluaran

```
4
```

### Penjelasan

Berikut ini adalah ilustrasi _tree_ untuk contoh tersebut. Harta setiap karyawan tertera di sebelah kanan _node_.

{1.png}

- audit(3, 5) = 1 (himpunan z yang memenuhi adalah {1})
- audit(3, 6) = 1 (himpunan z yang memenuhi adalah {1})
- audit(5, 6) = 2 (himpunan z yang memenuhi adalah {1, 4})
- audit(x, y) untuk pasangan (x, y) yang lain = 0

Maka, jumlahannya adalah 1 + 1 + 2 = 4.

### Batasan

- 1 ≤ T ≤ 10
- 1 ≤ P[i] < i, untuk i > 1
- 1 ≤ R[i] ≤ 100.000

### Batasan Khusus Versi Sulit

**Soal ini adalah soal versi sulit**. Batasan khusus untuk soal versi sulit:

- 2 ≤ N ≤ 100.000
