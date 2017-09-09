# Fotografer Wisuda (Mudah)

Pak Chanek sedang mengunjungi perayaan wisuda teman-temannya di Balairung Universitas Indonesia. Seperti biasa, ia sering diminta untuk memotret teman-temannya di halaman Balairung.

Kali ini, terdapat A teman laki-laki dan B teman perempuan Pak Chanek yang meminta untuk difoto. Bosan dengan pose foto pada umumnya, Pak Chanek ingin menjejerkan mereka dalam sebuah barisan lurus yang memenuhi seluruh syarat berikut ini:

- Tidak ada subbarisan yang terdiri atas lebih dari 2 teman laki-laki yang bersebelahan.
- Tidak ada subbarisan yang terdiri atas lebih dari K teman perempuan yang bersebelahan.

Bantulah Pak Chanek untuk mencarikan sebuah barisan yang memenuhi syarat-syarat tersebut, atau laporkan apabila hal tersebut mustahil.

### Format Masukan

Baris pertama berisi sebuah bilangan bulat T yang menyatakan banyaknya kasus uji. Baris-baris berikutnya berisi T kasus uji, yang masing-masing diberikan dalam format berikut ini:

```
A B K
```

### Format Keluaran

Untuk setiap kasus uji, keluarkan sebuah baris berisi sebuah string yang terdiri atas A + B karakter yang menyatakan sebuah barisan yang memenuhi seluruh syarat. Nyatakan teman laki-laki dengan karakter `L`, dan teman perempuan dengan karakter `P`.

Apabila terdapat lebih dari satu barisan yang mungkin, **keluarkan yang mana saja**.

Apabila tidak ada barisan yang mungkin, keluarkan `mustahil`.

### Contoh Masukan

```
3
0 4 4
0 4 3
1 3 3
```

### (Salah Satu) Contoh Keluaran

```
PPPP
mustahil
LPPP
```

### Penjelasan

Pada contoh kedua, satu-satunya barisan yang mungkin, `PPPP`,  merupakan barisan yang tidak diperbolehkan karena terdapat 4 (yakni, lebih dari K=3) teman perempuan yang bersebelahan.

### Batasan

- 1 ≤ T ≤ 20
- 1 ≤ B ≤ 1.000
- 1 ≤ K ≤ B

### Batasan Khusus Versi Mudah

**Soal ini adalah soal versi mudah**. Batasan di bawah ini juga berlaku, namun akan berbeda pada soal versi sulit:

- 0 ≤ A ≤ 1
