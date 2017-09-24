# Berbalas Pantun (Sulit)

Murid-murid kelas 6 SD Chanek terbagi atas kelas 6A dan kelas B, yang masing-masing terdiri atas N murid. Murid ke-i di kelas 6A memiliki pantun sepanjang A[i] detik, dan murid ke-i di kelas 6B memiliki pantun sepanjang B[i] detik.

Pada acara perpisahan, setiap murid di kelas 6A akan berbalas pantun dengan setiap murid di kelas 6B. Untuk sepasang murid ke-i di kelas 6A dan murid ke-j di kelas 6B, total waktu yang dibutuhkan mereka untuk berbalas pantun adalah A[i] + B[j].

Panggung perpisahan hanya dapat menampilkan sepasang murid untuk berbalas pantun dalam satu waktu. Tentukan total waktu yang dibutuhkan seluruh kemungkinan pasang murid kelas 6A dan 6B untuk berbalas pantun pada panggung.

### Format Masukan

Masukan diberikan dalam format berikut ini:

```
N
A[1] A[2] .. A[N]
B[1] B[2] .. B[N]
```

### Format Keluaran

Keluarkan sebuah baris berisi total waktu yang dibutuhkan, dalam detik.

### Contoh Masukan 1

```
1
3
5
```

### Contoh Keluaran 1

```
8
```

### Contoh Masukan 2

```
2
1 2
3 4
```

### Contoh Keluaran 2

```
20
```

### Penjelasan

Untuk contoh pertama, terdapat 1 kemungkinan pasangan murid yang akan tampil: satu-satunya murid kelas 6A dan satu-satunya murid kelas 6B. Total waktu yang dibutuhkan adalah 3 + 5 = 8 detik.

Untuk contoh kedua, terdapat 4 kemungkinan pasangan murid yang akan tampil:

- murid 1 kelas 6A dan murid 1 kelas 6B; total waktu = 1 + 3 = 4 detik
- murid 1 kelas 6A dan murid 2 kelas 6B; total waktu = 1 + 4 = 5 detik
- murid 2 kelas 6A dan murid 1 kelas 6B; total waktu = 2 + 3 = 5 detik
- murid 2 kelas 6A dan murid 2 kelas 6B; total waktu = 2 + 4 = 6 detik

Total waktu yang dibutuhkan adalah 4 + 5 + 5 + 6 = 20 detik.

### Batasan

- 1 ≤ A[i], B[i] ≤ 100

### Batasan Khusus Versi Sulit

**Soal ini adalah soal versi sulit**. Batasan khusus untuk soal versi sulit:

- 1 ≤ N ≤ 100.000
