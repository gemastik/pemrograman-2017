# Berbagi Lawakan (Mudah)

Suatu komunitas pelawak terdiri atas N anggota, yang dinomori dari 1 hingga N. Setiap pelawak memiliki standar tingkat kelucuan humor masing-masing. Pelawak ke-i menyukai sebuah lawakan apabila tingkat kelucuan lawakan tersebut berada di antara A[i] hingga B[i], inklusif.

Setiap pelawak memiliki akun media sosial. Akun media sosial setiap pelawak memiliki oleh nol atau lebih pengikut. Terdapat M informasi pengikut akun media sosial, yang masing-masing menyatakan bahwa akun media sosial pelawak U[i] diikuti oleh akun media sosial pelawak V[i].

Pelawak-pelawak tersebut senang menuliskan lawakan pada akun media sosial masing-masing. Setiap kali seorang pelawak menuliskan lawakan, pengikut-pengikutnya di media sosial akan langsung membaca lawakan tersebut. Untuk setiap pengikut, jika menyukai lawakan tersebut, maka ia akan menulis ulang lawakan tersebut keesokan harinya pada akun media sosialnya. Pelawak tetap akan menulis ulang lawakan sekalipun sebelumnya ia telah mengetahui lawakan tersebut.

Sebuah lawakan dikatakan abadi apabila lawakan tersebut akan terus beredar dari hari ke hari, tanpa pernah berakhir.

Sekarang, terdapat Q buah pertanyaan. Pertanyaan ke-i berbunyi: jika pelawak X[i] menulis lawakan dengan tingkat kelucuan H[i], apakah lawakan tersebut akan menjadi abadi?

### Format Masukan

Masukan diberikan dalam format berikut ini:

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

Keluarkan Q buah baris. Baris ke-i berisi jawaban dari pertanyaan ke-i, yaitu salah satu dari:

- "Ya", apabila akan menjadi abadi.
- "Tidak", apabila tidak akan menjadi abadi.

### Contoh Masukan

```
6 6
0 0 0 0 0 0
100 100 100 100 100 100
1 2
1 3
2 4
4 5
5 2
3 6
3
1 50
2 30
3 10
```

### Contoh Keluaran

```
Ya
Ya
Tidak
```

### Penjelasan

Pada pertanyaan pertama dan kedua, lawakan akan beredar pada pelawak-pelawak {2, 4, 5} secara abadi.

Pada pertanyaan ketiga, lawakan akan dibaca oleh pelawak 6 dan ia tulis ulang pada keesokan harinya. Sayangnya, tidak ada seorang pun yang membacanya. Maka, persebaran lawakan ini berakhir.

### Batasan

- 1 ≤ N ≤ 50.000
- 1 ≤ M ≤ 50.000
- 1 ≤ Q ≤ 50.000
- 1 ≤ U[i], V[i] ≤ N
- U[i] ≠ V[i]
- (U[i], V[i]) ≠ (U[j], V[j]) untuk setiap i ≠ j
- 1 ≤ X[i] ≤ N
- 0 ≤ H[i] ≤ 100

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- A[i] = 0
- B[i] = 100
