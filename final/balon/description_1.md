# Balon Poligon (Mudah)

Pak Chanek memiliki sebuah balon 2D yang berbentuk poligon segi-M beraturan. Pada mulanya, balon tersebut kempes dan dapat dianggap sebagai sebuah titik. Awalnya, balon kempes tersebut terletak pada sebuah bidang Kartesius 2D, pada koordinat (0, 0).

Pada bidang Kartesius yang sama, terdapat N titik. Titik ke-i memiliki koordinat (X[i], Y[i]).

Apabila dipompa, balon akan terus mengembang dengan titik pusat (0, 0), sampai salah satu sisinya mengenai salah satu titik yang ada. Ukuran balon tersebut didefinisikan sebagai jarak antara titik pusat ke salah satu titik sudut balon.

Sebelum memompa, Pak Chanek dapat merotasi balon kempes tersebut sesuka hati.

Tentukan ukuran balon terbesar yang mungkin setelah dipompa!

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N M
X[1] Y[1]
X[2] Y[2]
.
.
X[N] Y[N]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi ukuran terbesar yang mungkin setelah dipompa. Jawaban akan dianggap benar apabila memiliki selisih absolut atau relatif dengan jawaban juri paling banyak sebesar 10^-8.

### Contoh Masukan

```
1
1 3
2 4
```

### Contoh Keluaran

```
8.944271909999
```

### Penjelasan

Berikut ini adalah ilustrasi untuk contoh tersebut:

{1.png}

### Batasan

- 1 ≤ T ≤ 10
- 3 ≤ M ≤ 10
- -1.000.000 ≤ X[i], Y[i] ≤ 1.000.000
- (0, 0), (X[1], Y[1]), (X[2], Y[2]), ..., (X[N], Y[N]) dijamin merupakan titik-titik yang berbeda-beda

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- N = 1
