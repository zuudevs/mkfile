
# Quickstart

Panduan singkat untuk membangun dan menjalankan proyek di mesin Windows.

1. Pasang prasyarat: `CMake`, `Ninja`, dan compiler C++.

2. Dari direktori proyek utama:

```
mkdir build
cd build
cmake -G Ninja ..
ninja
```

3. Jalankan binari yang dihasilkan, mis.:

```
..\bin\mkfile.exe
```

Catatan:
- Jika menggunakan MSYS/MinGW atau WSL, gunakan path dan perintah shell yang sesuai.
- Untuk mode debug atau release, tambahkan `-DCMAKE_BUILD_TYPE=Debug` atau `Release` saat menjalankan `cmake`.
