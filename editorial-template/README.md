# Panduan Pembuatan Editorial

## Struktur Berkas

```
[ronde]/
 |--soal1/
 |   |--spec.cpp
 |   |--soln.cpp
 |   |--scorer.cpp
 |   \--editorial.tex
 |--soal2/
 |   |--spec.cpp
 |   |--soln.cpp
 |   |--scorer.cpp
 |   \--editorial.tex
 \--main_editorial.tex
```

Keterangan:

* Berkas `main_editorial.tex` dibuat dengan cara menyalin berkas `editorial_template.tex` yang terdapat dalam direktori `editorial-template/`.
* Setiap soal memiliki berkas `editorial.tex` yang dibuat dengan cara menyalin berkas `editorial.tex` yang terdapat dalam direktori `editorial-template/problem-name/`.

## Cara Kerja

1. Salin `editorial.tex` dari dalam direktori `editorial-template/problem-name/` ke dalam direktori soal yang editorialnya ingin dibuat.
2. Sunting isi dari `editorial.tex` sesuai dengan kebutuhan.
3. Tambahkan berkas editorial tersebut ke dalam berkas utama (`main_editorial.tex`) dengan cara menambahkan perintah `\include{nama-soal/editorial}`.
4. Lakukan kompilasi/_build_ untuk melihat perubahan yang terjadi.

## Saran

* Pada saat penyuntingan berkas editorial dari suatu soal, agar kompilasi/_build_ dilakukan pada berkas utama editorial (dan bukan berkas editorial yang sedang disunting), tetapkan berkas utama editorial sebagai _master document_.
    * Pada TexStudio, klik kanan pada berkas utama editorial lalu klik "Set this document as master document".