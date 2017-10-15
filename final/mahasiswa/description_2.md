# Organisasi Kemahasiswaan (Sulit)

Terdapat N organisasi kemahasiswaan di Fasilkom UI. Organisasi ke-i terdiri atas tepat M[i] mahasiswa. Menurut peraturan fakultas, setiap mahasiswa hanya boleh tergabung pada paling banyak K organisasi.

Berapakah banyaknya mahasiswa Fasilkom UI paling sedikit yang mungkin?

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N K
M[1] M[2] .. M[N]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi banyaknya mahasiswa Fasilkom UI paling sedikit yang mungkin.

### Contoh Masukan

```
3
2 2
10 12
2 1
10 12
3 2
3 2 1
```

### Contoh Keluaran

```
12
22
3
```

### Penjelasan

Misalkan mahasiswa-mahasiswa dinomori dengan bilangan bulat positif.

Untuk contoh pertama, salah satu struktur keanggotaan organisasi yang mungkin adalah:

- anggota-anggota organisasi 1: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
- anggota-anggota organisasi 2: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}

Untuk contoh kedua, salah satu struktur keanggotaan organisasi yang mungkin adalah:

- anggota-anggota organisasi 1: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
- anggota-anggota organisasi 2: {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22}

Untuk contoh ketiga, salah satu struktur keanggotaan organisasi yang mungkin adalah:

- anggota-anggota organisasi 1: {1, 2, 3}
- anggota-anggota organisasi 2: {1, 3}
- anggota-anggota organisasi 3: {2}

### Batasan

- 1 ≤ T ≤ 10
- 1 ≤ K ≤ N
- 1 ≤ M[i] ≤ 100.000

### Batasan Khusus Versi Sulit

**Soal ini adalah soal versi sulit**. Batasan khusus untuk soal versi sulit:

- 1 ≤ N ≤ 100.000
