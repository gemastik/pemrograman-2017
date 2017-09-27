# Rubrik Petakata (Mudah)

Petakata adalah sebuah rubrik teka-teki pada koran langganan Pak Chanek. Sebuah petakata terdiri atas petak-petak berukuran 2 baris dan N kolom. Setiap petak berisi sebuah huruf dari K huruf kecil pertama pada alfabet.

Tujuan pembaca adalah untuk menemukan sebuah string S pada petakata tersebut. Sebuah string S dikatakan terdapat pada petakata, apabila terdapat serangkaian petak yang memenuhi seluruh syarat di bawah ini:

- dimulai pada sebuah petak yang mana saja,
- setiap petak, selain petak pertama, berada tepat di sebelah atas, bawah, kanan, kanan-atas, atau kanan-bawah dari petak sebelumnya (perhatikan bahwa setiap petak **tidak boleh berada di sebelah kiri** petak sebelumnya),
- tidak ada petak yang dikunjungi lebih dari satu kali, dan
- huruf-huruf pada petak-petak yang dikunjungi tepat membentuk string S (yakni, petak pertama berisi huruf pertama dari S, petak kedua berisi huruf kedua, dan seterusnya).

Merasa bosan mengerjakan petakata setiap minggu, Pak Chanek malah penasaran: diberikan S, N, dan K, ada berapa petakata berbeda sedemikian sehingga pembaca dapat menemukan string S pada petakata? Dua buah petakata dikatakan berbeda apabila terdapat setidaknya sebuah petak pada posisi yang sama namun berisi huruf yang berbeda di antara kedua petakata tersebut.

Bantulah Pak Chanek menghitung banyaknya petakata yang dimaksud, modulo 1.000.000.007.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
S N K
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi banyaknya petakata yang mungkin, modulo 1.000.000.007.

### Contoh Masukan

```
2
ab 1 2
aa 2 2
```

### Contoh Keluaran

```
2
11
```

### Penjelasan

Untuk contoh pertama, terdapat 2 petakata yang mungkin:

```
 a  |  b
 b  |  a
```

Untuk contoh kedua, terdapat 11 petakata yang mungkin:

```
 aa  |  aa  |  aa  |  aa
 aa  |  ab  |  ba  |  bb
-----+------+------+-----
 ab  |  ab  |  ab  |  ba
 aa  |  ab  |  ba  |  aa
-----+------+------+-----
 ba  |  ba  |  bb
 ab  |  ba  |  aa
```

### Batasan

- 1 ≤ T ≤ 5
- 1 ≤ N ≤ 50
- 1 ≤ K ≤ 26
- Setiap huruf pada S termasuk dalam K huruf kecil pertama pada alfabet

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan khusus untuk soal versi mudah:

- S terdiri atas tepat 2 huruf

