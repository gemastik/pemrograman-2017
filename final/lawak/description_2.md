# Berbagi Lawakan (Sulit)

Suatu komunitas pelawak terdiri atas N anggota, yang dinomori dari 1 hingga N. Setiap pelawak memiliki standar tingkat kelucuan humor masing-masing. Pelawak ke-i menyukai sebuah lawakan apabila tingkat kelucuan lawakan tersebut berada di antara A[i] hingga B[i], inklusif.

Setiap pelawak memiliki akun media sosial. Akun media sosial setiap pelawak memiliki oleh nol atau lebih pengikut. Terdapat M informasi pengikut akun media sosial, yang masing-masing menyatakan bahwa akun media sosial pelawak U[i] diikuti oleh akun media sosial pelawak V[i].

Pelawak-pelawak tersebut senang menuliskan lawakan pada akun media sosial masing-masing. Setiap kali seorang pelawak menuliskan lawakan, pengikut-pengikutnya di media sosial akan langsung membaca lawakan tersebut. Untuk setiap pengikut, jika ia belum pernah membaca lawakan tersebut dan ia menyukai lawakan tersebut, maka ia akan menulis ulang lawakan tersebut pada akun media sosialnya. Proses ini berulang terus sampai tidak ada lagi pelawak yang menulis lawakan pada akun media sosialnya.

Sekarang, terdapat Q buah pertanyaan. Pertanyaan ke-i berbunyi: jika pelawak X[i] menulis lawakan dengan tingkat kelucuan H[i], pada akhirnya ada berapa pelawak yang pernah menulis lawakan tersebut?

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N M
A[1] A[2] .. A[N]
B[1] B[2] .. B[N]
U[1] V[1]
U[2] V[2]
.
.
U[M] V[M]
Q
X[1] H[1]
X[2] H[2]
.
.
X[Q] H[Q]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan Q buah baris. Baris ke-i berisi jawaban dari pertanyaan ke-i.

### Contoh Masukan

```
1
5 5
20 10 50 60 40
80 50 90 80 60
1 2
1 3
2 4
2 5
5 2
3
1 45
2 45
1 70
```

### Contoh Keluaran

```
5
3
3
```

### Penjelasan

Pada pertanyaan pertama, pada akhirnya seluruh pelawak akan menulis lawakan yang mulanya ditulis oleh pelawak 1.

Pada pertanyaan kedua, pada akhirnya pelawak-pelawak {2, 4, 5} akan menulis lawakan yang mulanya ditulis oleh pelawak 2.

Pada pertanyaan pertama, pada akhirnya pelawak-pelawak {1, 2, 3} akan menulis lawakan yang mulanya ditulis oleh pelawak 1.

### Batasan

- 1 ≤ T ≤ 10
- 0 ≤ A[i] ≤ B[i] ≤ 100
- 1 ≤ U[i], V[i] ≤ N
- U[i] ≠ V[i]
- (U[i], V[i]) ≠ (U[j], V[j]) untuk setiap i ≠ j
- 1 ≤ X[i] ≤ N
- 0 ≤ H[i] ≤ 100

### Batasan Khusus Versi Sulit

**Soal ini adalah soal versi sulit**. Batasan khusus untuk soal versi sulit:

- 1 ≤ N ≤ 100.000
- 1 ≤ M ≤ 100.000
- 1 ≤ Q ≤ 100.000
