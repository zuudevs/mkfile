
# Arsitektur Singkat

Proyek ini berstruktur sederhana:

- `src/` : kode sumber aplikasi (contoh: `main.cpp`).
- `lib/` : library internal (opsional).
- `bin/` : output binary setelah build.
- `build/` : direktori build CMake/Ninja (di-generate).

Alur build:

1. `cmake` menghasilkan file build di `build/`.
2. `ninja` atau generator build lainnya menyusun source menjadi output di `bin/`.

Desain saat ini fokus pada kesederhanaan—mudah dibaca dan dikembangkan. Untuk arsitektur yang lebih kompleks, pertimbangkan menambahkan modul terpisah di `lib/` dan header publik di `include/`.
