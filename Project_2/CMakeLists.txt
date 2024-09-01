cmake_minimum_required(VERSION 3.26)
project(Project_2 C)

set(CMAKE_C_STANDARD 17)

add_executable(Project_2 main.c
        Lib.h
        Desain.h
        Clean.h
        Menu.h
        Deklarasi.h
        crudKaryawan.h
        crudJabatan.h
        login.h
        crudGelombang.h
        crudJalurPenerimaan.h
        crudProgramStudi.h
        crudTahunAjar.h
        crudCamaba.h
        TrsPendaftaran.h
        TrsBayarFormulir.h
        TrsNilai1.h
        TrsNilai2.h
        TrsNilai3.h
        TrsBayarUkt.h
        SebelumLogin.h
        TrsPerangkingan.h
        Laporan.h
)

target_link_libraries(Project_2 PRIVATE winmm)
