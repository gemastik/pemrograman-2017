# Foto Wisuda (Sulit)

UI baru saja melaksanakan wisuda di Balairung. Seperti biasa, mendadak halaman _newsfeed_ Facebook dipenuhi oleh foto-foto para sarjana. Iseng-iseng, Anda ingin memperkirakan seberapa banyak orang yang hadir di Balairung pada wisuda tersebut.

Anda membuka-buka _newsfeed_ Facebook Anda. Anda mengamati bahwa terdapat N buah foto. Untuk setiap foto, diketahui:

- Siapa saja orang yang terdapat pada foto tersebut (menggunakan fitur _tag_ Facebook).
- Apakah foto tersebut merupakan _selfie_ atau bukan (menggunakan aplikasi _selfie detector_ dari salah satu lab riset di UI). Apabila foto tersebut bukan _selfie_, berarti ada tepat satu orang lain yang memotret orang-orang pada foto.

Dengan berasumsi tidak ada dua orang dengan nama yang sama, ada berapa maksimum orang yang Anda yakini hadir di Balairung pada wisuda yang lalu? Dengan kata lain, paling sedikit ada berapa orang yang dipotret atau memotret setidaknya sekali di Balairung pada wisuda yang lalu?

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N
S[1] K[1] P[1][1] P[1][2] .. P[1][K[1]]
S[2] K[2] P[2][1] P[2][2] .. P[2][K[2]]
.
.
S[N] K[N] P[N][1] P[N][2] .. P[N][K[N]]
```

dengan:

- S[i] adalah `selfie` bila foto ke-i diambil secara _selfie_, dan `dibantu` bila foto ke-i diambil dengan bantuan tepat satu orang lain
- K[i] menyatakan banyak orang pada foto ke-i
- P[i][j] menyatakan nama orang ke-j pada foto ke-i

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi banyaknya orang maksimum yang Anda yakini hadir di Balairung pada wisuda yang lalu.

### Contoh Masukan

```
3
1
selfie 2 ani budi
1
dibantu 1 ani
3
dibantu 3 ani budi candra
dibantu 1 budi
selfie 3 ani candra budi
```

### Contoh Keluaran

```
2
2
4
```

### Penjelasan

Untuk contoh masukan pertama, Anda yakin terdapat setidaknya 2 orang yang hadir: ani dan budi.

Untuk contoh masukan kedua, Anda yakin terdapat setidaknya 2 orang yang hadir: ani dan satu orang lain yang tidak diketahui namanya berdasarkan informasi yang ada.

Untuk contoh masukan ketiga, Anda yakin terdapat setidaknya 4 orang yang hadir: ani, budi, candra, dan satu orang lain yang tidak diketahui namanya berdasarkan informasi yang ada.

### Batasan

- 1 ≤ T ≤ 5
- 1 ≤ K[i] ≤ 10
- S[i] adalah salah satu dari `selfie` dan `dibantu`
- Setiap nama orang (P[i][j]) terdiri atas 1 sampai dengan 8 karakter `a` hingga `z`
- Dalam masing-masing foto, dijamin tidak ada nama yang tertera lebih dari sekali

### Batasan Khusus Versi Sulit

**Soal ini adalah soal versi sulit**. Batasan di bawah ini juga berlaku, namun akan berbeda pada soal versi mudah:

- 1 ≤ N ≤ 100
