# Berbalas Pantun (Mudah)

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

### Contoh Masukan

```
1
3
5
```

### Contoh Keluaran

```
8
```

### Penjelasan

Terdapat 1 kemungkinan pasangan murid yang akan tampil: satu-satunya murid kelas 6A dan satu-satunya murid kelas 6B. Total waktu yang dibutuhkan adalah 3 + 5 = 8 detik.

### Batasan

- 1 ≤ T ≤ 10
- 1 ≤ A[i], B[i] ≤ 100

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan di bawah ini juga berlaku, namun akan berbeda pada soal versi sulit:

- N = 1

