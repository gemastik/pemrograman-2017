# Operasi Bitwise (Mudah)

Carilah N bilangan bulat S[1], S[2], ..., S[N] yang memenuhi seluruh syarat berikut ini:

- 0 ≤ S[i] < 2^31
- S[1] AND S[2] AND ... AND S[N] = A
- S[1] OR S[2] OR ... OR S[N] = B
- S[1] XOR S[2] XOR ... XOR S[N] = C

dengan AND, OR, XOR merupakan operasi _bitwise_ `&`, `|`, dan `^` secara berturut-turut pada C, C++, maupun Java.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N A B C
```

### Format Keluaran

Untuk setiap kasus uji:

Jika tidak mungkin terdapat N bilangan bulat yang memenuhi seluruh syarat tersebut, keluarkan:

```
-1
```

Jika mungkin, keluarkan:

```
S[1] S[2] .. S[N]
```

Jika terdapat lebih dari satu solusi, keluarkan yang mana saja.

### Contoh Masukan

```
2
2 8 14 6
2 4 6 6
```

### (Salah Satu) Contoh Keluaran

```
14 8
-1
```

### Batasan

- 1 ≤ T ≤ 20

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- N = 2
- 0 ≤ A, B, C < 2^20
