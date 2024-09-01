#include <ctype.h>

void LaporanBayarForm();
void LaporanBayarUkt();
void LaporanPendaftar();
void LaporanDiterima();


// Fungsi untuk membuat singkatan dari nama
void SingkatanNama(char nama[]) {
    // Cek apakah string kosong
    if (strlen(nama) == 0) {
        printf("String kosong.\n");
        return;
    }

    // Cetak huruf pada kata pertama tanpa disingkat
    for (int i = 0; i < strlen(nama) && nama[i] != ' '; i++) {
        printf("%c", nama[i]);
    }

    // Loop untuk mencari spasi dan mencetak huruf depan setiap kata berikutnya
    for (int i = 1; i < strlen(nama); i++) {
        if (nama[i] == ' ') {
            printf(" .%c", nama[i + 1]);
        }
    }

    printf("\n");
}


void LaporanPendaftar() {


    int Baris = 17, Kolom = 38, Hal = 0, i;
    int pilih, ID_TahunAjar, ID_Prodi, pendaftar, ID_Gelombang, bulan, ID_Jalur;
    char jawaban, kf;
    bool found, found1;

    laporan:
    found = false;
    found1 = false;

    // Algoritma
    CleanKanan();
    CleanTengah();
    fflush(stdin);
    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    pendaftar = 0;

    gotoxy(133, 20); printf("   LAPORAN PENDAFTAR");
    gotoxy(133,21);  printf("   ==============================");
    gotoxy(133, 22); printf("   Pilihan Menu Berdasarkan");
    gotoxy(133, 23); printf("   [1] Program Studi");
    gotoxy(133, 24); printf("   [2] Gelombang Pendaftaran");
    gotoxy(133, 25); printf("   [3] Bulan");
    gotoxy(133, 26); printf("   [4] Jalur Penerimaan");
    gotoxy(133, 27); printf("   [5] Kembali");

    gotoxy(133, 29); printf("   Pilihan = [ ]");
    gotoxy(147, 29); getnum(&pilih,1);

    CleanKanan();

    switch (pilih) {
        case 1:
            gotoxy(133, 20); printf("   LAPORAN PENDAFTAR (PRODI)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23); printf("   Program Studi : PRD");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            LihatProgramStudi2();
            gotoxy(155, 23); fflush(stdin); getnum(&ID_Prodi, 2);

            found = false;

            // Memanggil Data Program Studi
            ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");

            fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            while ((!feof(ArsProgramStudi))) {
                if (Mprodi.ID == ID_Prodi) {
                    found = true;
                    break;
                }
                fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            }
            fclose(ArsProgramStudi);

            if(found!= true){
                MessageBox(NULL, "Program Studi Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Program Studi", "Tanggal", "Status Pendaftaran");

            if(found == true) {

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Prodi == ID_Prodi) {

                        ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");

                        while(fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi)==1) {
                            if (Mprodi.ID == Trspendaftaran.ID_Prodi) {

                                ArsCamaba = fopen("FileCamaba.dat", "rb");

                                while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                                    if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                        break;
                                    }
                                }

                                Baris++;
                                Hal++;
                                if (Baris % 2 == 0) {
                                    gotoxy(Kolom, Baris);
                                    SetColor(31);
                                } else {
                                    gotoxy(Kolom, Baris);
                                    SetColor(233);
                                }
                                for (i = 1; i <= Kolom + 54; i++) {
                                    printf(" ");
                                }

                                gotoxy(Kolom, Baris);
                                printf(" FRM%.5d       |               | %-13s | %.2d-%.2d-%-5.4d | %-15s",
                                       Trspendaftaran.ID,
                                       Mprodi.nama_singkat,
                                       Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                                       Trspendaftaran.tanggalDaftar.tahun,
                                       StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                                gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                                SetColor(241);
                                pendaftar = pendaftar + 1;

                                fflush(stdin);
                                fclose(ArsCamaba);

                                SetColor(241);
                                if (Hal == 25) {
                                    gotoxy(65, 44);
                                    SetColor(252);
                                    printf("Klik apa saja untuk lihat data selanjutnya... ");
                                    getch();
                                    Baris = 17;
                                    Kolom = 38;
                                    Hal = 0;
                                    CleanTengah();
                                    for (x = Kolom; x <= 129; x++) {
                                        SetColor(249);
                                        gotoxy(x, 15);
                                        printf("%c", 205);
                                        gotoxy(x, 17);
                                        printf("%c", 205);
                                    }
                                    SetColor(241);
                                    gotoxy(Kolom, 16);
                                    printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Program Studi", "Tanggal", "Status Pendaftaran");
                                }
                            }
                            DesainPendapatan();
                            gotoxy(136,43); printf("Total Pendaftar = %d Camaba", pendaftar);
                        }
                        fclose(ArsProgramStudi);
                    }
                }
                DesainPendapatan();
                gotoxy(136,43); printf("Total Pendaftar = %d Camaba", pendaftar);
                fclose(ArsPendaftaran);
            }
            break;
        case 2:
            gotoxy(133, 20); printf("   LAPORAN PENDAFTAR (GELOMBANG)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23); printf("   Gelombang     : GEL");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            LihatGelombang2();
            gotoxy(155, 23); fflush(stdin); getnum(&ID_Gelombang, 2);

            CleanTengah();

            found = false;

            // Memanggil Data Gelombang
            ArsGelombang = fopen("FileGelombang.dat", "rb");

            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            while ((!feof(ArsGelombang))) {
                if (Mgelombang.ID == ID_Gelombang) {
                    found = true;
                    break;
                }
                fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            }
            fclose(ArsGelombang);

            if(found!= true){
                MessageBox(NULL, "Gelombang Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Gelombang", "Tanggal", "Status Pendaftaran");

            if(found == true) {

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Gelombang == ID_Gelombang) {

                        ArsGelombang = fopen("FileGelombang.dat", "rb");

                        while(fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang)==1) {
                            if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {

                                ArsCamaba = fopen("FileCamaba.dat", "rb");

                                while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                                    if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                        break;
                                    }
                                }

                                Baris++;
                                Hal++;
                                if (Baris % 2 == 0) {
                                    gotoxy(Kolom, Baris);
                                    SetColor(31);
                                } else {
                                    gotoxy(Kolom, Baris);
                                    SetColor(233);
                                }
                                for (i = 1; i <= Kolom + 54; i++) {
                                    printf(" ");
                                }

                                gotoxy(Kolom, Baris);
                                printf(" FRM%.5d       |               | %-13s | %.2d-%.2d-%-5.4d | %-15s",
                                       Trspendaftaran.ID,
                                       Mgelombang.nama_gelombang,
                                       Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                                       Trspendaftaran.tanggalDaftar.tahun,
                                       StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                                gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                                SetColor(241);
                                pendaftar = pendaftar + 1;
                                fflush(stdin);
                                fclose(ArsCamaba);

                                SetColor(241);
                                if (Hal == 25) {
                                    gotoxy(65, 44);
                                    SetColor(252);
                                    printf("Klik apa saja untuk lihat data selanjutnya... ");
                                    getch();
                                    Baris = 17;
                                    Kolom = 38;
                                    Hal = 0;
                                    CleanTengah();
                                    for (x = Kolom; x <= 129; x++) {
                                        SetColor(249);
                                        gotoxy(x, 15);
                                        printf("%c", 205);
                                        gotoxy(x, 17);
                                        printf("%c", 205);
                                    }
                                    SetColor(241);
                                    gotoxy(Kolom, 16);
                                    printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Gelombang", "Tanggal", "Status Pendaftaran");
                                }
                            }

                            DesainPendapatan();
                            gotoxy(136,43); printf("Total Pendaftar = %d Camaba", pendaftar);
                        }
                        fclose(ArsGelombang);
                    }
                }
                DesainPendapatan();
                gotoxy(136,43); printf("Total Pendaftar = %d Camaba", pendaftar);
                fclose(ArsPendaftaran);
            }
            break;
        case 3:
            gotoxy(133, 20); printf("   LAPORAN PENDAFTAR (BULAN)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23); printf("   Bulan         : ");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            DesainData();
            gotoxy(71,19); printf("=========================");
            gotoxy(71,20); printf("|D|A|F|T|A|R| |B|U|L|A|N|");
            gotoxy(71,21); printf("=========================");

            gotoxy(65,28); printf(" [01] Januari");
            gotoxy(65,29); printf(" [02] Februari");
            gotoxy(65,30); printf(" [03] Maret");
            gotoxy(65,31); printf(" [04] April");
            gotoxy(65,32); printf(" [05] Mei");
            gotoxy(65,33); printf(" [06] Juni");
            gotoxy(85,28); printf(" [07] Juli");
            gotoxy(85,29); printf(" [08] Agustus");
            gotoxy(85,30); printf(" [09] September");
            gotoxy(85,31); printf(" [10] Oktober");
            gotoxy(85,32); printf(" [11] November");
            gotoxy(85,33); printf(" [12] Desember");

            gotoxy(152, 23); fflush(stdin); getnum(&bulan, 2);

            CleanTengah();

            if( bulan > 12 || bulan < 1){
                MessageBox(NULL, "Daftar Bulan Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-15s | %-15s ", "ID Pendaftaran", "Nama Camaba", "Tanggal Daftar", "Status");

            if(found == true) {

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.tanggalDaftar.bulan == bulan) {


                        ArsCamaba = fopen("FileCamaba.dat", "rb");

                        while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                            if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                break;
                            }
                        }


                        Baris++;
                        Hal++;
                        if (Baris % 2 == 0) {
                            gotoxy(Kolom, Baris);
                            SetColor(31);
                        } else {
                            gotoxy(Kolom, Baris);
                            SetColor(233);
                        }
                        for (i = 1; i <= Kolom + 54; i++) {
                            printf(" ");
                        }

                        gotoxy(Kolom, Baris);
                        printf(" FRM%.5d       |               | %.2d-%.2d-%-9.4d | %-15s",
                               Trspendaftaran.ID,
                               Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                               Trspendaftaran.tanggalDaftar.tahun,
                               StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                        gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                        SetColor(241);
                        pendaftar = pendaftar + 1;
                        fflush(stdin);
                        fclose(ArsCamaba);

                        SetColor(241);
                        if (Hal == 25) {
                            gotoxy(65, 44);
                            SetColor(252);
                            printf("Klik apa saja untuk lihat data selanjutnya... ");
                            getch();
                            Baris = 17;
                            Kolom = 38;
                            Hal = 0;
                            CleanTengah();
                            for (x = Kolom; x <= 129; x++) {
                                SetColor(249);
                                gotoxy(x, 15);
                                printf("%c", 205);
                                gotoxy(x, 17);
                                printf("%c", 205);
                            }
                            SetColor(241);
                            gotoxy(Kolom, 16);
                            printf(" %-14s | %-13s | %-15s | %-15s ", "ID Pendaftaran", "Nama Camaba", "Tanggal Daftar", "Status");

                        }
                    }
                    DesainPendapatan();
                    gotoxy(136, 43);
                    printf("Total Pendaftar = %d Camaba", pendaftar);
                }
                DesainPendapatan();
                gotoxy(136, 43);
                printf("Total Pendaftar = %d Camaba", pendaftar);
                fclose(ArsPendaftaran);
            }
            break;
        case 4:
            gotoxy(133, 20); printf("   LAPORAN PENDAFTAR (JALUR)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran     : TAJ");
            gotoxy(133, 23); printf("   Jalur Penerimaan : ");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(158, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            LihatJalurPenerimaan1();
            gotoxy(155, 23); fflush(stdin); getnum(&ID_Jalur, 2);

            CleanTengah();

            // Memanggil Data Jalur
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while ((!feof(ArsJalurPenerimaan))) {
                if (Mjalur.ID == ID_Jalur) {
                    found = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }
            fclose(ArsJalurPenerimaan);

            if(found!= true){
                MessageBox(NULL, "Jalur Penerimaan Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            if(found == true) {
                // Memanggil Data Tahun Ajaran
                ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                while ((!feof(ArsJalurPenerimaan))) {
                    if (Mjalur.ID == ID_Jalur) {
                        found1 = true;
                        break;
                    }
                    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                }
            }

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Jalur",
                   "Tanggal", "Status");

            if(found1 == true){

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

                        ArsGelombang = fopen("FileGelombang.dat", "rb");

                        while(fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang)==1) {
                            if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                                if (Mgelombang.ID_Jalur == Mjalur.ID) {

                                    ArsCamaba = fopen("FileCamaba.dat", "rb");

                                    while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                                        if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                            break;
                                        }
                                    }

                                    Baris++;
                                    Hal++;
                                    if (Baris % 2 == 0) {
                                        gotoxy(Kolom, Baris);
                                        SetColor(31);
                                    } else {
                                        gotoxy(Kolom, Baris);
                                        SetColor(233);
                                    }
                                    for (i = 1; i <= Kolom + 54; i++) {
                                        printf(" ");
                                    }

                                    gotoxy(Kolom, Baris);
                                    printf(" FRM%.5d       |               | %-13s | %.2d-%.2d-%-5.4d | %-15s",
                                           Trspendaftaran.ID,
                                           Mjalur.nama_jalur,
                                           Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                                           Trspendaftaran.tanggalDaftar.tahun,
                                           StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                                    gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                                    SetColor(241);
                                    pendaftar = pendaftar + 1;
                                    fflush(stdin);

                                    fclose(ArsCamaba);

                                    SetColor(241);
                                    if (Hal == 25) {
                                        gotoxy(65, 44);
                                        SetColor(252);
                                        printf("Klik apa saja untuk lihat data selanjutnya... ");
                                        getch();
                                        Baris = 17;
                                        Kolom = 38;
                                        Hal = 0;
                                        CleanTengah();
                                        for (x = Kolom; x <= 129; x++) {
                                            SetColor(249);
                                            gotoxy(x, 15);
                                            printf("%c", 205);
                                            gotoxy(x, 17);
                                            printf("%c", 205);
                                        }
                                        SetColor(241);

                                        gotoxy(Kolom, 16);
                                        printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Jalur",
                                               "Tanggal", "Status");
                                    }
                                }
                            }

                            DesainPendapatan();
                            gotoxy(136,43); printf("Total Pendaftar = %d Camaba", pendaftar);
                        }
                        fclose(ArsGelombang);
                    }
                }
                DesainPendapatan();
                gotoxy(136,43); printf("Total Pendaftar = %d Camaba", pendaftar);
                fclose(ArsPendaftaran);
            }
            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);
            break;
        case 5:
            KemahasiswaanMenu();
            break;
        default:
            goto laporan;
            break;
    }
    gotoxy(133,40);printf("  Klik Apapun Untuk Lanjut...");
    getch();

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LAPORAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LaporanPendaftar();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        KemahasiswaanMenu();
    }else {
        CleanKanan();
        goto lihat;
    }

}

void LaporanDiterima() {


    int Baris = 17, Kolom = 38, Hal = 0, i;
    int pilih, ID_TahunAjar, ID_Prodi, Diterima, ID_Gelombang, bulan, ID_Jalur;
    char jawaban, kf;
    bool found, found1;

    laporan:
    found = false;
    found1 = false;

    // Algoritma
    CleanKanan();
    CleanTengah();
    fflush(stdin);
    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    Diterima = 0;

    gotoxy(133, 20); printf("   LAPORAN DITERIMA");
    gotoxy(133,21);  printf("   ==============================");

    gotoxy(133, 22); printf("   Pilihan Menu Berdasarkan");
    gotoxy(133, 23); printf("   [1] Program Studi");
    gotoxy(133, 24); printf("   [2] Gelombang Pendaftaran");
    gotoxy(133, 25); printf("   [3] Bulan");
    gotoxy(133, 26); printf("   [4] Jalur Penerimaan");
    gotoxy(133, 27); printf("   [5] Kembali");

    gotoxy(133, 29); printf("   Pilihan = [ ]");
    gotoxy(147, 29); getnum(&pilih,1);

    CleanKanan();

    switch (pilih) {
        case 1:
            gotoxy(133, 20); printf("   LAPORAN DITERIMA (PRODI)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23); printf("   Program Studi : PRD");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            LihatProgramStudi3();
            gotoxy(155, 23); fflush(stdin); getnum(&ID_Prodi, 2);

            found = false;

            // Memanggil Data Program Studi
            ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");

            fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            while ((!feof(ArsProgramStudi))) {
                if (Mprodi.ID == ID_Prodi) {
                    found = true;
                    break;
                }
                fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            }
            fclose(ArsProgramStudi);

            if(found!= true){
                MessageBox(NULL, "Program Studi Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Program Studi", "Tanggal", "Status Pendaftaran");

            if(found == true) {

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Prodi == ID_Prodi && ((Trspendaftaran.StatusPendaftaran == 9) || (Trspendaftaran.StatusPendaftaran == 10) || (Trspendaftaran.StatusPendaftaran ==11))) {

                        ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");

                        while(fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi)==1) {
                            if (Mprodi.ID == Trspendaftaran.ID_Prodi) {

                                ArsCamaba = fopen("FileCamaba.dat", "rb");

                                while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                                    if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                        break;
                                    }
                                }

                                Baris++;
                                Hal++;
                                if (Baris % 2 == 0) {
                                    gotoxy(Kolom, Baris);
                                    SetColor(31);
                                } else {
                                    gotoxy(Kolom, Baris);
                                    SetColor(233);
                                }
                                for (i = 1; i <= Kolom + 54; i++) {
                                    printf(" ");
                                }

                                gotoxy(Kolom, Baris);
                                printf(" FRM%.5d       |               | %-13s | %.2d-%.2d-%-5.4d | %-15s",
                                       Trspendaftaran.ID,
                                       Mprodi.nama_singkat,
                                       Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                                       Trspendaftaran.tanggalDaftar.tahun,
                                       StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                                gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                                SetColor(241);
                                Diterima = Diterima + 1;
                                fflush(stdin);
                                fclose(ArsCamaba);

                                SetColor(241);
                                if (Hal == 25) {
                                    gotoxy(65, 44);
                                    SetColor(252);
                                    printf("Klik apa saja untuk lihat data selanjutnya... ");
                                    getch();
                                    Baris = 17;
                                    Kolom = 38;
                                    Hal = 0;
                                    CleanTengah();
                                    for (x = Kolom; x <= 129; x++) {
                                        SetColor(249);
                                        gotoxy(x, 15);
                                        printf("%c", 205);
                                        gotoxy(x, 17);
                                        printf("%c", 205);
                                    }
                                    SetColor(241);
                                    gotoxy(Kolom, 16);
                                    printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Program Studi", "Tanggal", "Status Pendaftaran");
                                }
                            }
                            DesainPendapatan();
                            gotoxy(136,43); printf("Total Diterima = %d Camaba", Diterima);
                        }
                        fclose(ArsProgramStudi);
                    }
                }
                DesainPendapatan();
                gotoxy(136,43); printf("Total Diterima = %d Camaba", Diterima);
                fclose(ArsPendaftaran);
            }
            break;
        case 2:
            gotoxy(133, 20); printf("   LAPORAN DITERIMA (GELOMBANG)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23); printf("   Gelombang     : GEL");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            LihatGelombang3();
            gotoxy(155, 23); fflush(stdin); getnum(&ID_Gelombang, 2);

            CleanTengah();

            found = false;

            // Memanggil Data Gelombang
            ArsGelombang = fopen("FileGelombang.dat", "rb");

            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            while ((!feof(ArsGelombang))) {
                if (Mgelombang.ID == ID_Gelombang) {
                    found = true;
                    break;
                }
                fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            }
            fclose(ArsGelombang);

            if(found!= true){
                MessageBox(NULL, "Gelombang Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Gelombang", "Tanggal", "Status Pendaftaran");

            if(found == true) {

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Gelombang == ID_Gelombang && ((Trspendaftaran.StatusPendaftaran == 9) || (Trspendaftaran.StatusPendaftaran == 10) || (Trspendaftaran.StatusPendaftaran ==11))) {

                        ArsGelombang = fopen("FileGelombang.dat", "rb");

                        while(fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang)==1) {
                            if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {

                                ArsCamaba = fopen("FileCamaba.dat", "rb");

                                while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                                    if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                        break;
                                    }
                                }

                                Baris++;
                                Hal++;
                                if (Baris % 2 == 0) {
                                    gotoxy(Kolom, Baris);
                                    SetColor(31);
                                } else {
                                    gotoxy(Kolom, Baris);
                                    SetColor(233);
                                }
                                for (i = 1; i <= Kolom + 54; i++) {
                                    printf(" ");
                                }

                                gotoxy(Kolom, Baris);
                                printf(" FRM%.5d       |               | %-13s | %.2d-%.2d-%-5.4d | %-15s",
                                       Trspendaftaran.ID,
                                       Mgelombang.nama_gelombang,
                                       Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                                       Trspendaftaran.tanggalDaftar.tahun,
                                       StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                                gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                                SetColor(241);
                                Diterima = Diterima + 1;
                                fflush(stdin);
                                fclose(ArsCamaba);

                                SetColor(241);
                                if (Hal == 25) {
                                    gotoxy(65, 44);
                                    SetColor(252);
                                    printf("Klik apa saja untuk lihat data selanjutnya... ");
                                    getch();
                                    Baris = 17;
                                    Kolom = 38;
                                    Hal = 0;
                                    CleanTengah();
                                    for (x = Kolom; x <= 129; x++) {
                                        SetColor(249);
                                        gotoxy(x, 15);
                                        printf("%c", 205);
                                        gotoxy(x, 17);
                                        printf("%c", 205);
                                    }
                                    SetColor(241);
                                    gotoxy(Kolom, 16);
                                    printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Gelombang", "Tanggal", "Status Pendaftaran");
                                }
                            }

                            DesainPendapatan();
                            gotoxy(136,43); printf("Total Diterima = %d Camaba", Diterima);
                        }
                        fclose(ArsGelombang);
                    }
                }
                DesainPendapatan();
                gotoxy(136,43); printf("Total Diterima = %d Camaba", Diterima);
                fclose(ArsPendaftaran);
            }
            break;
        case 3:
            gotoxy(133, 20); printf("   LAPORAN DITERIMA (BULAN)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23); printf("   Bulan         : ");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            DesainData();
            gotoxy(71,19); printf("=========================");
            gotoxy(71,20); printf("|D|A|F|T|A|R| |B|U|L|A|N|");
            gotoxy(71,21); printf("=========================");

            gotoxy(65,28); printf(" [01] Januari");
            gotoxy(65,29); printf(" [02] Februari");
            gotoxy(65,30); printf(" [03] Maret");
            gotoxy(65,31); printf(" [04] April");
            gotoxy(65,32); printf(" [05] Mei");
            gotoxy(65,33); printf(" [06] Juni");
            gotoxy(85,28); printf(" [07] Juli");
            gotoxy(85,29); printf(" [08] Agustus");
            gotoxy(85,30); printf(" [09] September");
            gotoxy(85,31); printf(" [10] Oktober");
            gotoxy(85,32); printf(" [11] November");
            gotoxy(85,33); printf(" [12] Desember");

            gotoxy(152, 23); fflush(stdin); getnum(&bulan, 2);

            CleanTengah();

            if( bulan > 12 || bulan < 1){
                MessageBox(NULL, "Daftar Bulan Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-15s | %-15s ", "ID Pendaftaran", "Nama Camaba", "Tanggal Daftar", "Status");

            if(found == true) {

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.tanggalDaftar.bulan == bulan && ((Trspendaftaran.StatusPendaftaran == 9) || (Trspendaftaran.StatusPendaftaran == 10) || (Trspendaftaran.StatusPendaftaran ==11))) {

                        ArsCamaba = fopen("FileCamaba.dat", "rb");

                        while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                            if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                break;
                            }
                        }

                        Baris++;
                        Hal++;
                        if (Baris % 2 == 0) {
                            gotoxy(Kolom, Baris);
                            SetColor(31);
                        } else {
                            gotoxy(Kolom, Baris);
                            SetColor(233);
                        }
                        for (i = 1; i <= Kolom + 54; i++) {
                            printf(" ");
                        }

                        gotoxy(Kolom, Baris);
                        printf(" FRM%.5d       |               | %.2d-%.2d-%-9.4d | %-15s",
                               Trspendaftaran.ID,
                               Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                               Trspendaftaran.tanggalDaftar.tahun,
                               StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                        gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                        SetColor(241);
                        Diterima = Diterima + 1;
                        fflush(stdin);
                        fclose(ArsCamaba);

                        SetColor(241);
                        if (Hal == 25) {
                            gotoxy(65, 44);
                            SetColor(252);
                            printf("Klik apa saja untuk lihat data selanjutnya... ");
                            getch();
                            Baris = 17;
                            Kolom = 38;
                            Hal = 0;
                            CleanTengah();
                            for (x = Kolom; x <= 129; x++) {
                                SetColor(249);
                                gotoxy(x, 15);
                                printf("%c", 205);
                                gotoxy(x, 17);
                                printf("%c", 205);
                            }
                            SetColor(241);
                            gotoxy(Kolom, 16);
                            printf(" %-14s | %-13s | %-15s | %-15s ", "ID Pendaftaran", "Nama Camaba", "Tanggal Daftar", "Status");

                        }
                    }
                    DesainPendapatan();
                    gotoxy(136, 43);
                    printf("Total Diterima = %d Camaba", Diterima);
                }
                DesainPendapatan();
                gotoxy(136, 43);
                printf("Total Diterima = %d Camaba", Diterima);
                fclose(ArsPendaftaran);
            }
            break;
        case 4:
            gotoxy(133, 20); printf("   LAPORAN DITERIMA (JALUR)");
            gotoxy(133,21);  printf("   ==============================");
            gotoxy(133, 22); printf("   Tahun Ajaran     : TAJ");
            gotoxy(133, 23); printf("   Jalur Penerimaan : ");

            CleanTengah();
            LihatTahunAjar2();
            gotoxy(158, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == ID_TahunAjar) {
                    found = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found!= true){
                MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            CleanTengah();
            LihatJalurPenerimaan1();
            gotoxy(155, 23); fflush(stdin); getnum(&ID_Jalur, 2);

            CleanTengah();

            // Memanggil Data Jalur
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while ((!feof(ArsJalurPenerimaan))) {
                if (Mjalur.ID == ID_Jalur) {
                    found = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }
            fclose(ArsJalurPenerimaan);

            if(found!= true){
                MessageBox(NULL, "Jalur Penerimaan Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto laporan;
            }

            if(found == true) {
                // Memanggil Data Tahun Ajaran
                ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                while ((!feof(ArsJalurPenerimaan))) {
                    if (Mjalur.ID == ID_Jalur) {
                        found1 = true;
                        break;
                    }
                    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                }
            }

            gotoxy(Kolom, 16);
            printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Jalur",
                   "Tanggal", "Status");

            if(found1 == true){

                ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                    if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && ((Trspendaftaran.StatusPendaftaran == 9) || (Trspendaftaran.StatusPendaftaran == 10) || (Trspendaftaran.StatusPendaftaran ==11))) {

                        ArsGelombang = fopen("FileGelombang.dat", "rb");

                        while(fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang)==1) {
                            if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                                if (Mgelombang.ID_Jalur == Mjalur.ID) {

                                    ArsCamaba = fopen("FileCamaba.dat", "rb");

                                    while(fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba)==1) {
                                        if(Mcamaba.ID == Trspendaftaran.ID_Camaba){
                                            break;
                                        }
                                    }

                                    Baris++;
                                    Hal++;
                                    if (Baris % 2 == 0) {
                                        gotoxy(Kolom, Baris);
                                        SetColor(31);
                                    } else {
                                        gotoxy(Kolom, Baris);
                                        SetColor(233);
                                    }
                                    for (i = 1; i <= Kolom + 54; i++) {
                                        printf(" ");
                                    }

                                    gotoxy(Kolom, Baris);
                                    printf(" FRM%.5d       |               | %-13s | %.2d-%.2d-%-5.4d | %-15s",
                                           Trspendaftaran.ID,
                                           Mjalur.nama_jalur,
                                           Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan,
                                           Trspendaftaran.tanggalDaftar.tahun,
                                           StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);
                                    gotoxy(Kolom+19, Baris); SingkatanNama(Mcamaba.nama_lengkap);
                                    SetColor(241);
                                    Diterima = Diterima + 1;
                                    fflush(stdin);

                                    fclose(ArsCamaba);
                                    SetColor(241);
                                    if (Hal == 25) {
                                        gotoxy(65, 44);
                                        SetColor(252);
                                        printf("Klik apa saja untuk lihat data selanjutnya... ");
                                        getch();
                                        Baris = 17;
                                        Kolom = 38;
                                        Hal = 0;
                                        CleanTengah();
                                        for (x = Kolom; x <= 129; x++) {
                                            SetColor(249);
                                            gotoxy(x, 15);
                                            printf("%c", 205);
                                            gotoxy(x, 17);
                                            printf("%c", 205);
                                        }
                                        SetColor(241);

                                        gotoxy(Kolom, 16);
                                        printf(" %-14s | %-13s | %-13s | %-11s | %-15s", "ID Pendaftaran", "Nama Camaba", "Jalur",
                                               "Tanggal", "Status");
                                    }
                                }
                            }

                            DesainPendapatan();
                            gotoxy(136,43); printf("Total Diterima = %d Camaba", Diterima);
                        }
                        fclose(ArsGelombang);
                    }
                }
                DesainPendapatan();
                gotoxy(136,43); printf("Total Diterima = %d Camaba", Diterima);
                fclose(ArsPendaftaran);
            }

            for (x = Kolom; x <= 129; x++) {
                SetColor(249);
                gotoxy(x, 15);
                printf("%c", 205);
                gotoxy(x, 17);
                printf("%c", 205);
            }
            SetColor(241);
            break;
        case 5:
            KemahasiswaanMenu();
            break;
        default:
            goto laporan;
            break;
    }

    gotoxy(133,40);printf("  Klik Apapun Untuk Lanjut...");
    getch();

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LAPORAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LaporanDiterima();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        KemahasiswaanMenu();
    }else {
        CleanKanan();
        goto lihat;
    }

}

void LaporanBayarForm(){

    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan

    int Baris = 17, Kolom = 38, Hal = 0, i;

    int ID_TahunAjar;
    int bulan;
    float hargaformulir;
    float pendapatan = 0;
    char jawaban, kf;
    bool found = false;

    // Algoritma
    laporan:
    CleanKanan();
    CleanTengah();
    fflush(stdin);
    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

    gotoxy(133, 20); printf("   LAPORAN PEMBAYARAN FORMULIR");
    gotoxy(133,21);  printf("   ==============================");
    gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
    gotoxy(133, 23); printf("   Bulan         : ");

    LihatTahunAjar2();

    gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);

    // Memanggil Data Tahun Ajaran
    ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    while ((!feof(ArsTahunAjar))) {
        if (MTahunAjar.ID == ID_TahunAjar) {
            found = true;
            break;
        }
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    }

    if(found!= true){
        MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto laporan;
    }

    CleanTengah();
    DesainData();
    gotoxy(71,19); printf("=========================");
    gotoxy(71,20); printf("|D|A|F|T|A|R| |B|U|L|A|N|");
    gotoxy(71,21); printf("=========================");

    gotoxy(65,28); printf(" [01] Januari");
    gotoxy(65,29); printf(" [02] Februari");
    gotoxy(65,30); printf(" [03] Maret");
    gotoxy(65,31); printf(" [04] April");
    gotoxy(65,32); printf(" [05] Mei");
    gotoxy(65,33); printf(" [06] Juni");
    gotoxy(85,28); printf(" [07] Juli");
    gotoxy(85,29); printf(" [08] Agustus");
    gotoxy(85,30); printf(" [09] September");
    gotoxy(85,31); printf(" [10] Oktober");
    gotoxy(85,32); printf(" [11] November");
    gotoxy(85,33); printf(" [12] Desember");

    gotoxy(152, 23); fflush(stdin); getnum(&bulan, 2);

    CleanTengah();

    if( bulan > 12 || bulan < 1){
        MessageBox(NULL, "Daftar Bulan Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto laporan;
    }

    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    gotoxy(Kolom, 16);
    printf(" %-15s | %-15s | %-15s | %-15s | %-15s", "ID Pendaftaran", "ID Trs Form", "Tanggal Bayar", "Harga Form", "Status");

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    while(fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1){
        if(Trspendaftaran.ID_TahunAjar == MTahunAjar.ID){

            // Memanggil Data Gelombang dan Jalur Penerimaan
            ArsGelombang = fopen("FileGelombang.dat", "rb");

            while(fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang)==1){
                if(Mgelombang.ID == Trspendaftaran.ID_Gelombang){
                    break;
                }
            }

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            while(fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan)==1){
                if(Mjalur.ID == Mgelombang.ID_Jalur){
                    hargaformulir = Mjalur.biaya_pendaftaran;
                    break;
                }
            }

            ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
                if(TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID){

                    if(TrsbayarForm.TanggalBayar.bulan == bulan && TrsbayarForm.StatusFormulir == 2){

                        Baris++;
                        Hal++;
                        if (Baris % 2 == 0) {
                            gotoxy(Kolom, Baris);
                            SetColor(31);
                        } else {
                            gotoxy(Kolom, Baris);
                            SetColor(233);
                        }
                        for (i = 1; i <= Kolom + 54; i++) {
                            printf(" ");
                        }

                        gotoxy(Kolom, Baris);
                        printf(" FRM%.5d        | TRSF%.5d       | %.2d-%.2d-%-9.4d | Rp.      %'.2f | %-10s",
                               TrsbayarForm.ID_Pendaftaran,
                               TrsbayarForm.ID,
                               TrsbayarForm.TanggalBayar.tgl, TrsbayarForm.TanggalBayar.bulan, TrsbayarForm.TanggalBayar.tahun,
                               hargaformulir,
                               StatusFormulir[TrsbayarForm.StatusFormulir]);
                        SetColor(241);
                        pendapatan = pendapatan + hargaformulir;
                        fflush(stdin);

                        SetColor(241);
                        if (Hal == 25) {
                            gotoxy(65, 44);
                            SetColor(252);
                            printf("Klik apa saja untuk lihat data selanjutnya... ");
                            getch();
                            Baris = 17;
                            Kolom = 38;
                            Hal = 0;
                            CleanTengah();
                            for (x = Kolom; x <= 129; x++) {
                                SetColor(249);
                                gotoxy(x, 15);
                                printf("%c", 205);
                                gotoxy(x, 17);
                                printf("%c", 205);
                            }
                            SetColor(241);
                            gotoxy(Kolom, 16);
                            printf(" %-15s | %-15s | %-15s | %-15s | %-15s", "ID Pendaftaran", "ID Trs Form",
                                   "Tanggal Bayar", "Harga Form", "Status");
                        }
                    }
                }

            } fclose(ArsBayarFormulir);
            DesainPendapatan();
            gotoxy(136,43); printf("Total = Rp. %'.2f", pendapatan);
        }
    }fclose(ArsPendaftaran);
    DesainPendapatan();
    gotoxy(136,43); printf("Total = Rp. %'.2f", pendapatan);

    gotoxy(133,40);printf("  Klik Apapun Untuk Lanjut...");
    getch();

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LAPORAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LaporanBayarForm();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        KemahasiswaanMenu();
    }else {
        CleanKanan();
        goto lihat;
    }
}

void LaporanBayarUkt(){

    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan

    int Baris = 17, Kolom = 38, Hal = 0, i;

    int ID_TahunAjar;
    int bulan;
    float hargaUkt;
    float pendapatan = 0;
    char jawaban, kf;
    bool found = false;


    // Algoritma
    laporan:
    CleanKanan();
    CleanTengah();
    fflush(stdin);
    ArsBayarUkt = fopen("FileBayarUkt.dat", "rb");

    gotoxy(133, 20); printf("   LAPORAN PEMBAYARAN UKT");
    gotoxy(133,21);  printf("   ==============================");
    gotoxy(133, 22); printf("   Tahun Ajaran  : TAJ");
    gotoxy(133, 23); printf("   Bulan         : ");

    LihatTahunAjar2();

    gotoxy(155, 22); fflush(stdin); getnum(&ID_TahunAjar, 2);


    // Memanggil Data Tahun Ajaran
    ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    while ((!feof(ArsTahunAjar))) {
        if (MTahunAjar.ID == ID_TahunAjar) {
            found = true;
            break;
        }
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    }

    if(found!= true){
        MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto laporan;
    }

    CleanTengah();
    DesainData();
    gotoxy(71,19); printf("=========================");
    gotoxy(71,20); printf("|D|A|F|T|A|R| |B|U|L|A|N|");
    gotoxy(71,21); printf("=========================");

    gotoxy(65,28); printf(" [01] Januari");
    gotoxy(65,29); printf(" [02] Februari");
    gotoxy(65,30); printf(" [03] Maret");
    gotoxy(65,31); printf(" [04] April");
    gotoxy(65,32); printf(" [05] Mei");
    gotoxy(65,33); printf(" [06] Juni");
    gotoxy(85,28); printf(" [07] Juli");
    gotoxy(85,29); printf(" [08] Agustus");
    gotoxy(85,30); printf(" [09] September");
    gotoxy(85,31); printf(" [10] Oktober");
    gotoxy(85,32); printf(" [11] November");
    gotoxy(85,33); printf(" [12] Desember");

    gotoxy(152, 23); fflush(stdin); getnum(&bulan, 2);

    CleanTengah();

    if( bulan > 12 || bulan < 1){
        MessageBox(NULL, "Daftar Bulan Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto laporan;
    }

    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    gotoxy(Kolom, 16);
    printf(" %-15s | %-15s | %-15s | %-15s | %-15s", "ID Pendaftaran", "ID Trs Ukt", "Tanggal Bayar", "Harga Ukt", "Status");


    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    while(fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1){
        if(Trspendaftaran.ID_TahunAjar == MTahunAjar.ID){
            hargaUkt = MTahunAjar.NominalUkt;

            ArsBayarUkt= fopen("FileBayarUkt.dat", "rb");

            while(fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt)==1){
                if(TrsbayarUkt.ID_Pendaftaran == Trspendaftaran.ID){

                    if(TrsbayarUkt.TanggalBayar.bulan == bulan && TrsbayarUkt.StatusUkt == 2){

                        Baris++;
                        Hal++;
                        if (Baris % 2 == 0) {
                            gotoxy(Kolom, Baris);
                            SetColor(31);
                        } else {
                            gotoxy(Kolom, Baris);
                            SetColor(233);
                        }
                        for (i = 1; i <= Kolom + 54; i++) {
                            printf(" ");
                        }

                        gotoxy(Kolom, Baris);
                        printf(" FRM%.5d        | TRSU%.5d       | %.2d-%.2d-%-9.4d | Rp.      %'.2f | %-10s",
                               TrsbayarUkt.ID_Pendaftaran,
                               TrsbayarUkt.ID,
                               TrsbayarUkt.TanggalBayar.tgl, TrsbayarUkt.TanggalBayar.bulan, TrsbayarUkt.TanggalBayar.tahun,
                               hargaUkt,
                               StatusUkt[TrsbayarUkt.StatusUkt]);
                        SetColor(241);
                        pendapatan = pendapatan + hargaUkt;
                        fflush(stdin);

                        SetColor(241);
                        if (Hal == 25) {
                            gotoxy(65, 44);
                            SetColor(252);
                            printf("Klik apa saja untuk lihat data selanjutnya... ");
                            getch();
                            Baris = 17;
                            Kolom = 38;
                            Hal = 0;
                            CleanTengah();
                            for (x = Kolom; x <= 129; x++) {
                                SetColor(249);
                                gotoxy(x, 15);
                                printf("%c", 205);
                                gotoxy(x, 17);
                                printf("%c", 205);
                            }
                            SetColor(241);
                            gotoxy(Kolom, 16);
                            printf(" %-15s | %-15s | %-15s | %-15s | %-15s", "ID Pendaftaran", "ID Trs Ukt",
                                   "Tanggal Bayar", "Harga Ukt", "Status");
                        }
                    }
                }
            } fclose(ArsBayarUkt);
            DesainPendapatan();
            gotoxy(136,43); printf("Total = Rp. %'.2f", pendapatan);
        }
    }fclose(ArsPendaftaran);

    DesainPendapatan();
    gotoxy(136,43); printf("Total = Rp. %'.2f", pendapatan);


    gotoxy(133,40);printf("  Klik Apapun Untuk Lanjut...");
    getch();

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LAPORAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LaporanBayarUkt();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        KemahasiswaanMenu();
    }else {
        CleanKanan();
        goto lihat;
    }

}