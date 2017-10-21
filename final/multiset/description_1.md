# Pak Grandi (Mudah)

Pak Grandi memiliki papan tulis yang besar sekali.

Pak Chanek menantang Pak Grandi untuk melakukan N aksi, yang masing-masing berbentuk:

```
P[i] L[i] R[i] K[i]
```

Makna dari aksi di atas adalah sebagai berikut:

- Jika P[i] = 1: Pak Grandi harus menuliskan bilangan x sebanyak tepat K[i] buah pada papan tulis, untuk seluruh bilangan bulat L[i] ≤ x ≤ R[i].
- Jika P[i] = 2: Misalkan cnt(x) menyatakan banyaknya bilangan x pada papan tulis. Pak Grandi harus menghapus bilangan x sebanyak tepat min(cnt(x), K[i]) buah dari papan tulis, untuk seluruh bilangan bulat L[i] ≤ x ≤ R[i].

Segera setelah melakukan aksi yang diminta, Pak Grandi harus menghitung G[i], yang merupakan bilangan bulat positif terkecil yang tidak tertulis pada papan tulis.

Bantulah Pak Grandi untuk melakukan tantangan yang diminta Pak Chanek.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N
P[1] L[1] R[1] K[1]
P[2] L[2] R[2] K[2]
.
.
P[N] L[N] R[N] K[N]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan:

```
G[1]
G[2]
.
.
G[N]
```

### Contoh Masukan

TBA

### Contoh Keluaran

TBA

### Batasan

- 1 ≤ T ≤ 10
- 1 ≤ P[i] ≤ 2
- 1 ≤ L[i], R[i] ≤ 1.000.000.000
- 1 ≤ K[i] ≤ 1.000.000.000
- 1 ≤ N ≤ 50.000

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- L[i] = R[i]
