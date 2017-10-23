# Kuis Kata (Sulit)

Pak Chanek mengikuti acara kuis berhadiah bernama Kuis Kata. Pada kuis ini, Pak Chanek akan bermain melawan pembawa acara. Pada kuis ini, terdapat N buah string: S[1], S[2], ..., S[N]. Uniknya, sebelum Pak Chanek datang ke acara kuis tersebut, panitia memberitahukan S[1] kepada Pak Chanek.

String-string akan memenuhi seluruh syarat berikut ini:

- Setiap string akan memiliki antara 1 hingga L karakter abjad `a` - `z`.
- Karakter-karakter pada setiap string akan terurut tidak menurun berdasarkan abjad.

Pak Chanek dan pembawa acara mengambil langkah secara bergiliran. Pada setiap langkah, seorang pemain harus mengganti salah satu karakter pada salah satu string dengan sebuah karakter abjad lain, sedemikian sehingga seluruh syarat berikut ini terpenuhi:

- Karakter pengganti urutannya lebih belakang pada abjad daripada karakter yang diganti.
- Karakter-karakter pada string tersebut tetap terurut tidak menurun berdasarkan abjad.

Sebagai contoh, jika diberikan S = {"aku", "itu"}, maka contoh-contoh langkah yang memenuhi syarat adalah:

- mengubah "aku" menjadi "anu"
- mengubah "itu" menjadi "iuu"

Contoh-contoh langkah yang tidak memenuhi syarat adalah:

- mengubah "aku" dan "itu" menjadi "anu" dan "iuu" (hanya boleh mengubah 1 string)
- mengubah "aku" menjadi "ako" (`o` tidak lebih belakang pada abjad daripada `u`)
- mengubah "aku" menjadi "awu" (hasilnya tidak terurut menurut berdasarkan abjad)

Pemain yang tidak dapat melangkah pada gilirannya (yakni, saat seluruh karakter pada seluruh string adalah `z`) dinyatakan kalah, dan kuis berakhir.

Pak Chanek penasaran, jika Pak Chanek dan pembawa acara **selalu bermain dengan optimal**, sebenarnya ada berapa kemungkinan kuis yang mungkin sedemikian sehingga Pak Chanek akan menang? Dua kemungkinan dikatakan berbeda apabila terdapat i > 1 sedemikian sehingga S[i] pada kemungkinan yang satu berbeda dengan S[i] pada kemungkinan yang lainnya.

Bantulah Pak Chanek menghitung banyaknya kemungkinan kuis tersebut, mod 1.000.000.007.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
N L
S[1]
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi banyaknya kemungkinan modulo 1.000.000.007.

### Contoh Masukan

```
3
2 1
y
2 2
aa
20 17
aku
```

### Contoh Keluaran

```
25
350
26630817
```

### Penjelasan

Untuk contoh pertama, semua kemungkinan S[2] yang terdiri atas 1 karakter abjad, kecuali "y", akan memenangkan Pak Chanek. Dengan kata lain, S = {"y", "y"} akan membuat Pak Chanek kalah:

- Pada langkah pertama, Pak Chanek harus mengubah salah satu string "y" menjadi "z" (tidak ada cara lain).
- Pada langkah kedua, pembawa acara akan mengubah string "y" yang lain menjadi "z".
- Pak Chanek tidak dapat melangkah, dan kalah.

Untuk contoh kedua, semua kemungkinan S[2] berikut ini akan memenangkan Pak Chanek:

- "a", "b", ..., "y" (25 buah)
- "ab", ..., "az", "ba", "bc", ..., "bz", "ca", "cb", "cd", ..., "zy" (325 buah)

### Batasan

- 1 ≤ T ≤ 100
- S[1] terdiri atas 1 hingga L karakter abjad `a` - `z`
- Karakter-karakter pada S[1] terurut tidak menurun berdasarkan abjad

### Batasan Khusus Versi Sulit

**Soal ini adalah soal versi sulit**. Batasan khusus untuk soal versi sulit:

- 2 ≤ N ≤ 1.000.000.000
- 1 ≤ L ≤ 10.000
