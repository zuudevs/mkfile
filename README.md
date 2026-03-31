
# mkfile

Proyek ini menyediakan utilitas bawaan untuk membangun dan menjalankan contoh kecil C++.

Ringkasan cepat:

- Bahasa: C++
- Sistem build: CMake + Ninja

Prerequisites:

- CMake (>= 3.15)
- Ninja
- Compiler C++ (MSVC / Clang / GCC)

Build dan jalankan (Windows, Command Prompt):

1. Buat direktori build:

```
mkdir build
cd build
```

2. Konfigurasi dan generate dengan CMake:

```
cmake -G Ninja ..
```

3. Bangun proyek:

```
ninja
```

4. Jalankan executable (contoh):

```
./bin/mkfile.exe
```

Dokumentasi lengkap dan panduan cepat tersedia di folder `docs/`.
