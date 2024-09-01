void BuatFormulir();
void LihatFormulir1();
void LihatFormulir2();
void AkunVaForm();
void DetailFormulir();



void BuatFormulir(){
    bool found, found1, found2, found3, found4, found5;
    int sukses = 0;
    int ID_Akun;

    ID_Akun = Mcamaba.ID;

    ArsCamaba = fopen("FileCamaba.dat", "rb");
    TempCamaba = fopen("TempCamaba.dat", "wb");

    found4 = false;

    fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    while((!found4) && (!feof(ArsCamaba)))
    {
        if(Mcamaba.ID == ID_Akun) {
            found4 = true;
            break;
        } else {
            fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
        }
        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    }

    CleanTengah();

    if(found4 == true) {
        DesainData();

        if (Mcamaba.StatusAkun == 0) {

            ArsPendaftaran = fopen("FilePendaftaran.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

            while (!feof(ArsPendaftaran)) {
                fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            }
            Trspendaftaran.ID++;

            gotoxy(73, 19);
            printf("===========================");
            gotoxy(73, 20);
            printf("|B|U|A|T| |F|O|R|M|U|L|I|R|");
            gotoxy(73, 21);
            printf("===========================");

            gotoxy(60, 26);
            printf(" ID Pendaftaran          : FRM%.5d", Trspendaftaran.ID);

            Trspendaftaran.ID_Camaba = Mcamaba.ID;

            gotoxy(60, 27);
            printf(" ID Camaba               : CMB%.5d", Trspendaftaran.ID_Camaba);

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            Trspendaftaran.tanggalDaftar.tgl = tm.tm_mday;
            Trspendaftaran.tanggalDaftar.bulan = tm.tm_mon + 1;
            Trspendaftaran.tanggalDaftar.tahun = tm.tm_year + 1900;

            gotoxy(60, 27);
            printf(" Tangggal Pendaftaran    : %.2d/%.2d/%.4d", Trspendaftaran.tanggalDaftar.tgl,
                   Trspendaftaran.tanggalDaftar.bulan, Trspendaftaran.tanggalDaftar.tahun);
            gotoxy(60, 37);
            printf(" Klik Apapun Untuk Lanjut");
            getch();

            CleanTengah();

            gotoxy(133,20); printf("  TRANSAKSI PENDAFTARAN FORMULIR");
            gotoxy(133,21); printf("  ===============================");

            gotoxy(133, 22);
            printf("   Tahun Ajaran  : TAJ");
            gotoxy(133, 23);
            printf("   Gelombang     : GEL");
            gotoxy(133, 24);
            printf("   Program Studi : PRD");

            // Memilih Tahun Ajar, Gelombang, dan Prodi

            LihatTahunAjar2();
            gotoxy(155, 22);
            fflush(stdin);
            getnum(&Trspendaftaran.ID_TahunAjar, 2);

            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");
            TempTahunAjar = fopen("TempTahunAjar.dat", "wb");
            found = false;

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while ((!found) && (!feof(ArsTahunAjar))) {
                if (MTahunAjar.ID == Trspendaftaran.ID_TahunAjar) {
                    found = true;
                    fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
                    break;
                } else {
                    fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if (found == true) {
                if (MTahunAjar.status != 0) {
                    MessageBox(NULL, "Tahun Ajaran ini Tidak Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanTengah();
                    CleanKanan();
                    BuatFormulir();
                }
            } else {
                MessageBox(NULL, "Tahun Ajaran ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                CleanTengah();
                CleanKanan();
                BuatFormulir();
            }

            CleanTengah();
            LihatGelombang1();
            gotoxy(155, 23);
            fflush(stdin);
            getnum(&Trspendaftaran.ID_Gelombang, 2);

            // Memanggil Data Gelombang
            ArsGelombang = fopen("FileGelombang.dat", "rb");
            TempGelombang = fopen("TempGelombang.dat", "wb");
            found1 = false;
            found3 = false;

            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            while ((!found1) && (!feof(ArsGelombang))) {
                if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                    found1 = true;
                    fwrite(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
                    break;
                } else {
                    fwrite(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
                }
                fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            }

            if (found1 == true) {
                if (Mgelombang.status != 0) {
                    MessageBox(NULL, "Gelombang ini Tidak Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanTengah();
                    CleanKanan();
                    BuatFormulir();
                }

                if ((Trspendaftaran.tanggalDaftar.tahun > Mgelombang.bukaGel.tahun ||
                (Trspendaftaran.tanggalDaftar.tahun == Mgelombang.bukaGel.tahun && Trspendaftaran.tanggalDaftar.bulan > Mgelombang.bukaGel.bulan) ||
                (Trspendaftaran.tanggalDaftar.tahun == Mgelombang.bukaGel.tahun && Trspendaftaran.tanggalDaftar.bulan == Mgelombang.bukaGel.bulan && Trspendaftaran.tanggalDaftar.tgl >= Mgelombang.bukaGel.tgl)) &&
                (Trspendaftaran.tanggalDaftar.tahun < Mgelombang.tutupGel.tahun || (Trspendaftaran.tanggalDaftar.tahun == Mgelombang.tutupGel.tahun && Trspendaftaran.tanggalDaftar.bulan < Mgelombang.tutupGel.bulan) ||
                (Trspendaftaran.tanggalDaftar.tahun == Mgelombang.tutupGel.tahun && Trspendaftaran.tanggalDaftar.bulan == Mgelombang.tutupGel.bulan && Trspendaftaran.tanggalDaftar.tgl <= Mgelombang.tutupGel.tgl))) {
                    found3 = true;
                }
            } else {
                MessageBox(NULL, "Gelombang ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                CleanTengah();
                CleanKanan();
                BuatFormulir();
            }

            if (found3 != true) {
                MessageBox(NULL, "Gelombang Tidak Sesuai dengan Tanggal Pendaftaran!", "PERINGATAN",
                           MB_OK | MB_ICONWARNING);
                CleanTengah();
                CleanKanan();
                BuatFormulir();
            }

            CleanTengah();
            LihatProgramStudi4();
            gotoxy(155, 24);
            fflush(stdin);
            getnum(&Trspendaftaran.ID_Prodi, 2);

            // Memanggil Data Program Studi
            ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
            TempProgramStudi = fopen("TempProgramStudi.dat", "wb");
            found2 = false;

            fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            while ((!found2) && (!feof(ArsProgramStudi))) {
                if (Mprodi.ID == Trspendaftaran.ID_Prodi) {
                    found2 = true;
                    fwrite(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
                    break;
                } else {
                    fwrite(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
                }
                fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            }

            if (found2 == true) {
                if (Mprodi.status != 0) {
                    MessageBox(NULL, "Program Studi ini Tidak Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanTengah();
                    CleanKanan();
                    BuatFormulir();
                }
            } else {
                MessageBox(NULL, "Program Studi ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                CleanTengah();
                CleanKanan();
                BuatFormulir();
            }

            Trspendaftaran.StatusPendaftaran = 0;

            Mcamaba.StatusAkun = 1;

            AkunVaForm();

            // update atribut jumlah pendaftar di tabel tahun ajaran, saat ada pembuatan akun baru
            ArsTahunAjar = fopen("FileTahunAjar.dat","rb");
            TempTahunAjar = fopen("TempTahunAjar.dat", "wb");

            found5 = false;

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while((!found5) && (!feof(ArsTahunAjar)))
            {
                if(MTahunAjar.ID == Trspendaftaran.ID_TahunAjar){
                    found5 = true;
                    break;
                }
                else{
                    fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if(found5 == true){
                MTahunAjar.banyak_pendaftar++;
            }

            fwrite(&MTahunAjar,sizeof(MTahunAjar), 1, TempTahunAjar);

            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            fclose(ArsPendaftaran);

            MessageBox(0, "Pendaftaran berhasil, Silahkan Membayar Formulir dengan No Virtual Account di Info Formulir", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);

        }else if(Mcamaba.StatusAkun == 1){
            MessageBox(0, "Anda Tidak Bisa Mendaftar Karena Sedang Dalam Tahap Seleksi", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
            CleanTengah();
            CleanKanan();
            CamabaMenu();
        }else {
            MessageBox(0, "Anda Tidak Bisa Mendaftar Karena Anda Sudah Lulus Seleksi", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
            CleanTengah();
            CleanKanan();
            CamabaMenu();
        }
    }

    fread(&MTahunAjar, sizeof (MTahunAjar), 1, ArsTahunAjar);
    while (!feof(ArsTahunAjar)){
        fwrite(&MTahunAjar, sizeof (MTahunAjar), 1, TempTahunAjar);
        fread(&MTahunAjar, sizeof (MTahunAjar), 1, ArsTahunAjar);
    }

    fclose(ArsTahunAjar);
    fclose(TempTahunAjar);

    ArsTahunAjar = fopen("FileTahunAjar.dat", "wb");
    TempTahunAjar = fopen("TempTahunAjar.dat", "rb");

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
    while (!feof(TempTahunAjar)) {
        fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
    }
    fclose(ArsTahunAjar);
    fclose(TempTahunAjar);

    fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
    fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    while (!feof(ArsCamaba)) {
        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    }

    fclose(ArsCamaba);
    fclose(TempCamaba);

    ArsCamaba = fopen("FileCamaba.dat", "wb");
    TempCamaba = fopen("TempCamaba.dat", "rb");

    fread(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
    while (!feof(TempCamaba)) {
        fwrite(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        fread(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
    }
    fclose(ArsCamaba);
    fclose(TempCamaba);

    // Masuk ke akun lagi
    ArsCamaba = fopen("FileCamaba.dat", "rb");
    fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
    while(!feof(ArsCamaba))
    {
        if(Mcamaba.ID == ID_Akun)
        {
            sukses=1;
            break;
        }
        fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
    }

    if  (sukses == 1){
        system("cls");
        CleanTengah();
        CleanKanan();
        CleanKiri();
        gotoxy(2,10); printf("SELAMAT DATANG......");
        gotoxy(2,11); printf("CALON MAHASISWA BARU");
        gotoxy(2,12); puts(Mcamaba.nama_lengkap);
        CamabaMenu();
    }
}

void AkunVaForm(){

    // Membuat virtual account
    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsBayarFormulir))
    {
        fread(&TrsbayarForm, sizeof(TrsbayarForm),1 , ArsBayarFormulir);
    }
    TrsbayarForm.ID++;


    strcpy(TrsbayarForm.VaFormulir, "VA0198");
    strcat(TrsbayarForm.VaFormulir, Mcamaba.no_telepon);
    TrsbayarForm.StatusFormulir = 0;

    TrsbayarForm.ID_Pendaftaran = Trspendaftaran.ID;

    fwrite(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);

    fclose(ArsBayarFormulir);

}

void LihatFormulir1(){

    // Deklarasi1
    bool found1, found2, found3;
    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    // Jika Data Jalur Kosong
    if (ArsPendaftaran == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Formulir Pendaftaran masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        CamabaMenu();
    } else {

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-15s | %-15s | %-15s | %-15s","ID Pendaftaran", "Tahun Ajaran", "Gelombang", "Jalur Penerimaan");
        while (!feof(ArsPendaftaran)) {
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

            gotoxy(Kolom, Baris); printf(" FRM%.5d", Trspendaftaran.ID);


            // Memanggil Data Tahun Ajaran
            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

            found1 = false;

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            while((!found1)&&(!feof(ArsTahunAjar))) {
                if(MTahunAjar.ID == Trspendaftaran.ID_TahunAjar) {
                    found1 = true;
                    break;
                }
                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            }

            if (found1 == true){
                gotoxy(Kolom + 17, Baris); printf(" %s", MTahunAjar.tahun_ajaran);
            }

            // Memanggil Data Gelombang
            ArsGelombang = fopen("FileGelombang.dat", "rb");

            found2 = false;

            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            while((!found2)&&(!feof(ArsGelombang))) {
                if(Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                    found2 = true;
                    break;
                }
                fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            }

            if (found2 == true){
                gotoxy(Kolom + 35, Baris); printf(" %s", Mgelombang.nama_gelombang);

                // Memanggil Data Jalur Penerimaan
                ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

                found3 = false;

                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                while((!found3)&&(!feof(ArsJalurPenerimaan))) {
                    if(Mjalur.ID == Mgelombang.ID) {
                        found3 = true;
                        break;
                    }
                    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                }

                if(found3 == true){
                    gotoxy(Kolom + 53, Baris); printf(" %s", Mjalur.nama_jalur);
                }
            }
            SetColor(241);

            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);

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
                    gotoxy(x, 15); printf("%c", 205);
                    gotoxy(x, 17); printf("%c", 205);
                }
                SetColor(241);
                gotoxy(Kolom, 16); printf(" %-6s | %-20s | %-20s | %-10s","ID JLR", "Nama Jalur", "Biaya Pendaftaran", "Status");
            }
        }
        fclose(ArsJalurPenerimaan);
        SetColor(252);
    }

    gotoxy(65, 44);
    SetColor(252);
    printf("Klik apapun untuk Keluar... ");
    getch();

    CleanTengah();
    CleanKanan();
    CleanKiri();
    CamabaMenu();
}


void LihatFormulir2(){

    // Deklarasi
    bool found1, found2, found3;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    int ID_akun;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");
    ID_akun = Mcamaba.ID;

    // Jika Data Jalur Kosong
    if (ArsPendaftaran == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Formulir Pendaftaran masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        CamabaMenu();
    } else {

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-15s | %-15s | %-15s | %-15s","ID Pendaftaran", "Tahun Ajaran", "Gelombang", "Jalur Penerimaan");
        while ((!feof(ArsPendaftaran)) ) {
            if(Trspendaftaran.ID_Camaba == Mcamaba.ID) {
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
                printf(" FRM%.5d", Trspendaftaran.ID);

                // Memanggil Data Tahun Ajaran
                ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

                found1 = false;

                fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
                while ((!found1) && (!feof(ArsTahunAjar))) {
                    if (MTahunAjar.ID == Trspendaftaran.ID_TahunAjar) {
                        found1 = true;
                        break;
                    }
                    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
                }

                if (found1 == true) {
                    gotoxy(Kolom + 17, Baris);
                    printf("| %s", MTahunAjar.tahun_ajaran);
                }

                // Memanggil Data Gelombang
                ArsGelombang = fopen("FileGelombang.dat", "rb");

                found2 = false;

                fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
                while ((!found2) && (!feof(ArsGelombang))) {
                    if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                        found2 = true;
                        break;
                    }
                    fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
                }

                if (found2 == true) {
                    gotoxy(Kolom + 35, Baris);
                    printf("| %s", Mgelombang.nama_gelombang);

                    // Memanggil Data Jalur Penerimaan
                    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

                    found3 = false;

                    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                    while ((!found3) && (!feof(ArsJalurPenerimaan))) {
                        if (Mjalur.ID == Mgelombang.ID_Jalur) {
                            found3 = true;
                            break;
                        }
                        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                    }

                    if (found3 == true) {
                        gotoxy(Kolom + 53, Baris);
                        printf("| %s", Mjalur.nama_jalur);
                    }
                }
                SetColor(241);

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
                    printf(" %-6s | %-20s | %-20s | %-10s", "ID JLR", "Nama Jalur", "Biaya Pendaftaran", "Status");
                }
            }
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            SetColor(252);
        } fclose(ArsPendaftaran);
    }
}

void DetailFormulir(){
    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan
    int ID;
    bool found, found1, found2, found3, found4, found5, found6, found7, found8, found9, ketemu;

    lihat:
    CleanTengah();
    CleanKanan();
    // Algoritma
    LihatFormulir2();
    SetColor(252);
    gotoxy(133,44); printf(" Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  LIHAT DETAIL FORMULIR");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Pendaftaran : FRM"); getnum(&ID, 2);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        CamabaMenu();
    }

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");

    found = false;
    ketemu = false;

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    while((!found)&&(!feof(ArsPendaftaran)))
    {
        if(Trspendaftaran.ID == ID) {
            if(Trspendaftaran.ID_Camaba == Mcamaba.ID){
            found = true;
            break;
            }
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }


    // Jika Data ditemukan
    if (found == true) {

        CleanTengah();

        if(Trspendaftaran.StatusPendaftaran == 0){
            MessageBox(NULL, "Formulir Pendaftaran Telah Terisi, Silahkan melakukan pembayaran Formulir dengan VA yang tersedia dan lakukan konfirmasi pembayaran!!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 1){
            MessageBox(NULL, "Pembayaran Formulir Pendaftaran Telah Di konfirmasi, Silahkan Tunggu Proses Verifikasi Pembayaran Anda !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 2){
            MessageBox(NULL, "Pembayaran Formulir Pendaftaran Telah Lunas, Silahkan melakukan Input Nilai Seleksi Tahap 1 !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 3){
            MessageBox(NULL, "Formulir Pendaftaran Sedang Dalam Seleksi Tahap 1, Silahkan Tunggu Pengumuman Seleksi Tahap 1!!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 4){
            MessageBox(NULL, "Selamat Anda Lulus Seleksi Tahap 1, Silahkan melakukan test Psikotest sesuai dengan jadwal yang dikirimkan melalui SMS atau Email !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 5) {
            MessageBox(NULL, "Formulir Pendaftaran Sedang Dalam Seleksi Tahap 2, Silahkan Tunggu Pengumuman Seleksi Tahap 2!!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 6){
            MessageBox(NULL, "Selamat Anda Lulus Seleksi Tahap 2, Silahkan melakukan test Wawancara sesuai dengan jadwal yang dikirimkan melalui SMS atau Email !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 7) {
            MessageBox(NULL, "Formulir Pendaftaran Sedang Dalam Seleksi Tahap 3, Silahkan Tunggu Pengumuman Seleksi Tahap 3!!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 8){
            MessageBox(NULL, "Selamat Anda Lulus Passing Grade Tahap 3, Silahkan Tunggu Pengumuman Perangkingan Seleksi Tahap 3 !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 9){
            MessageBox(NULL, "Selamat Anda Lulus Seleksi Tahap 3, Silahkan melakukan pembayaran Ukt dengan VA yang tersedia dan lakukan konfirmasi pembayaran !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 10){
            MessageBox(NULL, "Pembayaran Ukt Pendaftaran Telah Di konfirmasi, Silahkan Tunggu Proses Verifikasi Pembayaran Anda !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 11){
            MessageBox(NULL, "Pembayaran Ukt Pendaftaran telah Lunas, SELAMAT ANDA SUDAH MENJADI CALON MAHASISWA BARU POLITEKNIK RALFAHISNAF, See You In PKKMB!!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 12){
            MessageBox(NULL, "Mohon Maaf Anda Tidak Lulus Seleksi, TETAP SEMANGAT DAN PANTANG MENYERAH, Silahkan mendaftar lagi di gelombang selanjutnya !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 13){
            MessageBox(NULL, "Pembayaran Formulir Pendaftaran Anda Gagal di Verifikasi, silahkan lakukan pembayaran kembali !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }else if(Trspendaftaran.StatusPendaftaran == 14){
            MessageBox(NULL, "Pembayaran Ukt Anda Gagal di Verifikasi, silahkan lakukan pembayaran kembali !!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
        }

        CleanTengah();
        DesainData();
        gotoxy(73, 19); printf("===========================");
        gotoxy(73, 20); printf("|D|A|T|A| |F|O|R|M|U|L|I|R|");
        gotoxy(73, 21); printf("===========================");

        gotoxy(60, 25); printf(" ID Pendaftaran      : FRM%.5d", Trspendaftaran.ID);
        gotoxy(60, 26); printf(" ID Camaba           : CMB%.5d", Trspendaftaran.ID_Camaba);
        gotoxy(60, 27); printf(" Tanggal Pendaftaran : %.2d/%.2d/%.4d", Trspendaftaran.tanggalDaftar.tgl, Trspendaftaran.tanggalDaftar.bulan, Trspendaftaran.tanggalDaftar.tahun );
        gotoxy(60, 32); printf(" Status Pendaftaran  : %s", StatusPendaftaran[Trspendaftaran.StatusPendaftaran]);


        // Memanggil Data Tahun Ajaran
        ArsTahunAjar = fopen("FileTahunAjaran.dat", "rb");
        found1 = false;
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        while ((!found1) && (!feof(ArsTahunAjar))) {
            if (MTahunAjar.ID == Trspendaftaran.ID_TahunAjar) {
                found1 = true;
                break;
            }
            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        }

        if (found1 == true) {
            gotoxy(65, 34);
            gotoxy(60, 28); printf(" Tahun Ajaran        : %s", MTahunAjar.tahun_ajaran);
        }

        // Memanggil Data Gelombang dan Jalur Penerimaan
        ArsGelombang = fopen("FileGelombang.dat", "rb");

        found2 = false;

        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        while((!found2)&&(!feof(ArsGelombang))) {
            if(Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                found2 = true;
                break;
            }
            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        }

        if (found2 == true){
            gotoxy(60, 29); printf(" Gelombang           : %s", Mgelombang.nama_gelombang);

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            found3 = false;

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while((!found3)&&(!feof(ArsJalurPenerimaan))) {
                if(Mjalur.ID == Mgelombang.ID_Jalur) {
                    found3 = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }

            if(found3 == true){
                gotoxy(60, 30); printf(" Jalur Penerimaan    : %s", Mjalur.nama_jalur);
            }
        }

        // Memanggil Data Program Studi
        ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
        found4 = false;
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
        while ((!found4) && (!feof(ArsProgramStudi))) {
            if (Mprodi.ID == Trspendaftaran.ID_Prodi) {
                found4 = true;
                break;
            }
            fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
        }

        if (found4 == true) {
            gotoxy(60, 31); printf(" Program Studi       : %s", Mprodi.nama_prodi);
        }

        gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
        getch();

        CleanTengah();
        DesainData();
        gotoxy(73, 19); printf("===========================");
        gotoxy(73, 20); printf("|D|A|T|A| |F|O|R|M|U|L|I|R|");
        gotoxy(73, 21); printf("===========================");

        gotoxy(60, 25); printf(" [Pembayaran Formulir]");
        gotoxy(60, 26); printf(" ========================");
        gotoxy(60, 27); printf(" No Virtual Account     : ");
        gotoxy(60, 28); printf(" Status Bayar Form      : ");
        gotoxy(60, 29); printf(" Biaya Formulir         : ");

        gotoxy(60, 31); printf(" [Pembayaran Ukt]");
        gotoxy(60, 32); printf(" ========================");
        gotoxy(60, 33); printf(" No Virtual Account     : ");
        gotoxy(60, 34); printf(" Status Bayar Form      : ");
        gotoxy(60, 35); printf(" Biaya Ukt              : ");

        // Memanggil Data Pembayaran Formulir
        ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");
        found5 = false;
        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        while ((!found5) && (!feof(ArsBayarFormulir))) {
            if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                found5 = true;
                break;
            }
            fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        }

        ArsGelombang = fopen("FileGelombang.dat", "rb");
        ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");
        if (found5 == true) {
            gotoxy(86, 27); printf(" %s", TrsbayarForm.VaFormulir);
            gotoxy(86, 28); printf(" %s", StatusFormulir[TrsbayarForm.StatusFormulir]);

            while(fread(&Mgelombang,sizeof(Mgelombang), 1, ArsGelombang)==1)
            {
                if (Mgelombang.ID == Trspendaftaran.ID_Gelombang) {
                    ketemu = true;
                    break;
                }
            }

            if(ketemu == true) {
                while (fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan) == 1) {
                    if (Mjalur.ID == Mgelombang.ID_Jalur) {
                        gotoxy(86, 29);
                        printf(" %'.2f", Mjalur.biaya_pendaftaran);
                        break;
                    }
                }
            }

        }

        // Memanggil Data Pembayaran Ukt
        ArsBayarUkt = fopen("FileBayarUkt.dat", "rb");
        found6 = false;
        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        while ((!found6) && (!feof(ArsBayarUkt))) {
            if (TrsbayarUkt.ID_Pendaftaran == Trspendaftaran.ID) {
                found6 = true;
                break;
            }
            fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        }

        if (found6 == true) {
            gotoxy(86, 33); printf(" %s", TrsbayarUkt.VaUkt);
            gotoxy(86, 34); printf(" %s", StatusUkt[TrsbayarUkt.StatusUkt]);

            ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");
            while(fread(&MTahunAjar,sizeof(MTahunAjar), 1, ArsTahunAjar)==1)
            {
                if (MTahunAjar.ID == Trspendaftaran.ID_TahunAjar) {
                    gotoxy(86, 35); printf(" %'.2f", MTahunAjar.NominalUkt);
                    break;
                }
            }

        }

        gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
        getch();

        CleanTengah();
        DesainData();
        gotoxy(73, 19); printf("===========================");
        gotoxy(73, 20); printf("|D|A|T|A| |F|O|R|M|U|L|I|R|");
        gotoxy(73, 21); printf("===========================");

        gotoxy(60, 25); printf(" [Seleksi Tahap 1]");
        gotoxy(60, 26); printf(" ========================");
        gotoxy(60, 27); printf(" Total Nilai            : ");
        gotoxy(60, 28); printf(" Total Nilai Akhir      : ");
        gotoxy(60, 29); printf(" Tanggal Input          : ");
        gotoxy(60, 30); printf(" Status Seleksi         : ");

        ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
            if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                break;
            }
        }

        // Memanggil Data Seleksi Tahap 1
        ArsTrsNilai1 = fopen("FileNilai1.dat", "rb");
        found9 = false;
        fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
        while ((!found9) && (!feof(ArsTrsNilai1))) {
            if (Trsnilai1.ID_BayarForm == TrsbayarForm.ID) {
                found9 = true;
                break;
            }
            fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
        }

        if (found9 == true) {
            gotoxy(86, 27); printf(" %.2f", Trsnilai1.total);
            gotoxy(86, 28); printf(" %.2f", Trsnilai1.rata_rata);
            gotoxy(86, 29); printf(" %.2d/%.2d/%.2d",Trsnilai1.TanggalInput.tgl, Trsnilai1.TanggalInput.bulan, Trsnilai1.TanggalInput.tahun  );
            gotoxy(86, 30); printf(" %s", StatusSeleksi1[Trsnilai1.Status]);
        }

        gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
        getch();

        CleanTengah();
        DesainData();
        gotoxy(73, 19); printf("===========================");
        gotoxy(73, 20); printf("|D|A|T|A| |F|O|R|M|U|L|I|R|");
        gotoxy(73, 21); printf("===========================");

        gotoxy(60, 25); printf(" [Seleksi Tahap 2]");
        gotoxy(60, 26); printf(" ========================");
        gotoxy(60, 27); printf(" Nilai Psikotest        : ");
        gotoxy(60, 28); printf(" Tanggal Psikotest      : ");
        gotoxy(60, 29); printf(" Status Seleksi         : ");

        gotoxy(60, 31); printf(" [Seleksi Tahap 3]");
        gotoxy(60, 32); printf(" ========================");
        gotoxy(60, 33); printf(" Nilai Wawancara        : ");
        gotoxy(60, 34); printf(" Tanggal Wawancara      : ");
        gotoxy(60, 35); printf(" Status Seleksi         : ");

        // Memanggil Data Seleksi Tahap 2
        ArsTrsNilai2 = fopen("FileNilai2.dat", "rb");
        found7 = false;
        fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
        while ((!found7) && (!feof(ArsTrsNilai2))) {
            if (Trsnilai2.ID_BayarForm == TrsbayarForm.ID) {
                found7 = true;
                break;
            }
            fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
        }

        if (found7 == true) {
            gotoxy(86, 27); printf(" %.2f", Trsnilai2.SkorPsikotest);
            gotoxy(86, 28); printf(" %.2d/%.2d/%.2d",Trsnilai2.TanggalPsikotest.tgl, Trsnilai2.TanggalPsikotest.bulan, Trsnilai2.TanggalPsikotest.tahun  );
            gotoxy(86, 29); printf(" %s", StatusSeleksi2[Trsnilai2.Status]);
        }

        // Memanggil Data Seleksi Tahap 3
        ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");
        found8 = false;
        fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
        while ((!found8) && (!feof(ArsTrsNilai3))) {
            if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                found8 = true;
                break;
            }
            fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
        }

        if (found8 == true) {
            gotoxy(86, 33); printf(" %.2f", Trsnilai3.SkorWawancara);
            gotoxy(86, 34); printf(" %.2d/%.2d/%.2d",Trsnilai3.TanggalWawancara.tgl, Trsnilai3.TanggalWawancara.bulan, Trsnilai3.TanggalWawancara.tahun  );
            gotoxy(86, 35); printf(" %s", StatusSeleksi3[Trsnilai3.Status]);
        }

        gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
        getch();
        fflush(stdin);

        CleanTengah();
        CleanKanan();
        CleanKiri();
        CamabaMenu();
    }else{
        MessageBox(NULL, "Data Formulir Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto lihat;
    }

}

