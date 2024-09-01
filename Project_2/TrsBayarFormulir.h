void InputBuktiForm(); // oleh camaba, input bukti resi pembayaran dan tanggal pembayaran
void LihatPengajuanBayarForm1(); // untuk bagian finance, menampilkan tabel pembayaran form bagi camaba yang sudah input bukti resi pembayaran
void LihatPembayaranForm(); // untuk bagian finance, menampilkan tabel semua form pembayaran
void VerifikasiBayarForm(); // oleh finance melakukan verifikasi terhadap konfirmasi pembayaran yang dilakukan camaba
int HitungTotalPengajuan();


void InputBuktiForm(){

    int ID; // menyimpan inputan id pendaftaran
    int ID_Camaba;
    int sukses = 0;
    bool found, found1, found2, found3;
    char buktiresi[50];
    Date Sekarang;

    lihat:
    CleanTengah();
    CleanKanan();
    LihatFormulir2();
    SetColor(252);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    gotoxy(133,44); printf(" Ketik '0' untuk ke kembali");
    SetColor(241);

    Sekarang.tgl = tm.tm_mday;
    Sekarang.bulan = tm.tm_mon + 1;
    Sekarang.tahun = tm.tm_year + 1900;

    gotoxy(133,20); printf("  KONFIRMASI PEMBAYARAN FORMULIR");
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
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    found = false;

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    while((!found)&&(!feof(ArsPendaftaran)))
    {
        if(Trspendaftaran.ID == ID) {
            if(Trspendaftaran.ID_Camaba == Mcamaba.ID){
                ID_Camaba = Mcamaba.ID;
                found = true;
                break;
            }else{
                MessageBox(NULL, "Data Formulir Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto lihat;
            }
        }else{
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    if(found == true){

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");
        TempBayarFormulir = fopen("TempBayarFormulir.dat", "wb");

        found1 = false;

        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        while((!found1) && (!feof(ArsBayarFormulir))) {
            if(TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID){
                found1 = true;
                break;
            }
            else{
                fwrite(&TrsbayarForm, sizeof(TrsbayarForm), 1, TempBayarFormulir);
            }
            fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        }

        if((found1 == true) && ((TrsbayarForm.StatusFormulir == 0)||(TrsbayarForm.StatusFormulir == 3))){
            CleanKanan();
            CleanTengah();
            DesainData();

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            gotoxy(63,19); printf("===========================================");
            gotoxy(63,20); printf("|K|O|N|F|I|R|M|A|S|I| |B|A|Y|A|R| |F|O|R|M|");
            gotoxy(63,21); printf("===========================================");

            gotoxy(60,28); printf(" ID Pembayaran Form : TRSF%.5d",TrsbayarForm.ID);
            gotoxy(60,29); printf(" No Virtual Account : %s",TrsbayarForm.VaFormulir);
            gotoxy(60,30); printf(" Tanggal Pembayaran : "); fflush(stdin);
            getnum(&TrsbayarForm.TanggalBayar.tgl, 2); printf(" / ");
            getnum(&TrsbayarForm.TanggalBayar.bulan, 2); printf(" / ");
            getnum(&TrsbayarForm.TanggalBayar.tahun, 4);

            found2 = false;

            if(datevalid(TrsbayarForm.TanggalBayar)){
                ArsGelombang = fopen("FileGelombang.dat","rb");
                while (fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang) == 1) {
                    if(Mgelombang.ID == Trspendaftaran.ID_Gelombang){

                        if ((TrsbayarForm.TanggalBayar.tahun > Trspendaftaran.tanggalDaftar.tahun ||
                             (TrsbayarForm.TanggalBayar.tahun == Trspendaftaran.tanggalDaftar.tahun &&
                              TrsbayarForm.TanggalBayar.bulan > Trspendaftaran.tanggalDaftar.bulan) ||
                             (TrsbayarForm.TanggalBayar.tahun == Trspendaftaran.tanggalDaftar.tahun &&
                              TrsbayarForm.TanggalBayar.bulan == Trspendaftaran.tanggalDaftar.bulan &&
                              TrsbayarForm.TanggalBayar.tgl >= Trspendaftaran.tanggalDaftar.tgl)) &&
                            (TrsbayarForm.TanggalBayar.tahun < Mgelombang.tutupGel.tahun ||
                             (TrsbayarForm.TanggalBayar.tahun == Mgelombang.tutupGel.tahun &&
                              TrsbayarForm.TanggalBayar.bulan < Mgelombang.tutupGel.bulan) ||
                             (TrsbayarForm.TanggalBayar.tahun == Mgelombang.tutupGel.tahun &&
                              TrsbayarForm.TanggalBayar.bulan == Mgelombang.tutupGel.bulan &&
                              TrsbayarForm.TanggalBayar.tgl <= Mgelombang.tutupGel.tgl)) &&
                            (TrsbayarForm.TanggalBayar.tahun < tm.tm_year + 1900 ||
                             (TrsbayarForm.TanggalBayar.tahun == tm.tm_year + 1900 &&
                              TrsbayarForm.TanggalBayar.bulan < tm.tm_mon + 1) ||
                             (TrsbayarForm.TanggalBayar.tahun == tm.tm_year + 1900 &&
                              TrsbayarForm.TanggalBayar.bulan == tm.tm_mon + 1 &&
                              TrsbayarForm.TanggalBayar.tgl <= tm.tm_mday))) {
                            found2 = true;
                            break;
                        }

                    }
                }
            }

            tm.tm_year + 1900;
            tm.tm_mon + 1;
            tm.tm_mday;

            if(found2 == true){
                gotoxy(60,31); printf(" Bukti Resi         : "); fflush(stdin); getteks(buktiresi, 15);
                strcpy(TrsbayarForm.ResiBukti, buktiresi);
                TrsbayarForm.StatusFormulir = 1;
                Trspendaftaran.StatusPendaftaran = 1;
                fwrite(&TrsbayarForm,sizeof(TrsbayarForm), 1, TempBayarFormulir);
                fwrite(&Trspendaftaran,sizeof(Trspendaftaran), 1, TempPendaftaran);

                fread(&TrsbayarForm, sizeof (TrsbayarForm), 1, ArsBayarFormulir);
                while (!feof(ArsBayarFormulir)){
                    fwrite(&TrsbayarForm, sizeof (TrsbayarForm), 1, TempBayarFormulir);
                    fread(&TrsbayarForm, sizeof (TrsbayarForm), 1, ArsBayarFormulir);
                }

                fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
                while (!feof(ArsPendaftaran)){
                    fwrite(&Trspendaftaran, sizeof (Trspendaftaran), 1, TempPendaftaran);
                    fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
                }
            }else{
                MessageBox(NULL, "Tanggal Pembayaran Tidak Sesuai dengan tanggal pendaftaran, tanggal tutup Gelombang, dan tanggal hari ini!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto lihat;
            }
        } else {
            MessageBox(NULL, "Formulir Ini sudah Dikonfirmasi!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanTengah();
            CleanKanan();
            CleanKiri();
            CamabaMenu();
        }

        fclose(ArsBayarFormulir);
        fclose(TempBayarFormulir);
        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);

        ArsBayarFormulir = fopen("FileBayarFormulir.dat", "wb");
        TempBayarFormulir = fopen("TempBayarFormulir.dat", "rb");

        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, TempBayarFormulir);
        while (!feof(TempBayarFormulir)) {
            fwrite(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
            fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, TempBayarFormulir);
        }
        fclose(ArsBayarFormulir);
        fclose(TempBayarFormulir);

        ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        while (!feof(TempPendaftaran)) {
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        }
        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);

        MessageBox(NULL, "Konfirmasi Pembayaran Formulir telah berhasil dilakukan, silahkan tunggu verifikasi dari Tim Keuangan", "PERINGATAN", MB_OK | MB_ICONWARNING);
    }else{
        MessageBox(NULL, "Data Formulir Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto lihat;
    }

    // Masuk ke akun lagi
    ArsCamaba = fopen("FileCamaba.dat", "rb");
    fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
    while(!feof(ArsCamaba))
    {
        if(Mcamaba.ID == ID_Camaba)
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

void LihatPembayaranForm(){

    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

    // Jika Data Bayar Formulir
    if (ArsBayarFormulir == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Pembayaran Formulir Pendaftaran masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        FinanceMenu();
    }else {
        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16);
        printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Form", "Va Formulir", "Tanggal Bayar", "Status");
        while (!feof(ArsBayarFormulir)) {
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
                printf(" PRD%-12.5d | %-20s | %.2d-%.2d-%-9.4d | %-10s",
                       TrsbayarForm.ID,
                       TrsbayarForm.VaFormulir,
                       TrsbayarForm.TanggalBayar.tgl, TrsbayarForm.TanggalBayar.bulan, TrsbayarForm.TanggalBayar.tahun,
                       StatusFormulir[TrsbayarForm.StatusFormulir]);
                SetColor(241);

                fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);

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
                    printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Form", "Va Formulir", "Tanggal Bayar", "Status");
                }
        }
        fclose(ArsBayarFormulir);
        SetColor(252);
        gotoxy(133, 21); printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(133, 22); printf("  ===========================");
        gotoxy(160, 21); getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            CleanTengah();
            FinanceMenu();
            getch();
        } else {
            LihatPembayaranForm();
        }
    }
}

void LihatPengajuanBayarForm1(){

    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

    // Jika Data Bayar Formulir
    if (ArsBayarFormulir == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Pembayaran Formulir Pendaftaran masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        AdminMenu();
    }else {
        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16);
        printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Form", "Va Formulir", "Tanggal Bayar", "Status");
        while (!feof(ArsBayarFormulir)) {
            if (TrsbayarForm.StatusFormulir == 1) {
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
                printf(" TRSF%-11.5d | %-20s | %.2d-%.2d-%-9.4d | %-10s",
                       TrsbayarForm.ID,
                       TrsbayarForm.VaFormulir,
                       TrsbayarForm.TanggalBayar.tgl, TrsbayarForm.TanggalBayar.bulan, TrsbayarForm.TanggalBayar.tahun,
                       StatusFormulir[TrsbayarForm.StatusFormulir]);
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
                    printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Form", "Va Formulir", "Tanggal Bayar", "Status");
                }
            }
            fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        }
        fclose(ArsBayarFormulir);
        SetColor(252);
    }
}

// Fungsi untuk menghitung total formulir yang diajukan
int HitungTotalPengajuan() {
    int totalPengajuan = 0;

    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");
    if (ArsBayarFormulir == NULL) {
        return 0; // Jika file tidak ditemukan atau kosong
    }

    while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
        if (TrsbayarForm.StatusFormulir == 1) {
            totalPengajuan++;
        }
    }

    fclose(ArsBayarFormulir);
    return totalPengajuan;
}

void VerifikasiBayarForm(){

    int ID;
    char kf;
    bool found, found1;

    CleanTengah();
    CleanKanan();

    LihatPengajuanBayarForm1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  VERIFIKASI PEMBAYARAN FORMULIR");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Tansaksi Form   : TRSF"); getnum(&ID, 2);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        FinanceMenu();
    }

    ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");
    TempBayarFormulir = fopen("TempBayarFormulir.dat", "wb");

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    found = false;
    found1 = false;

    fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
    while((!found)&&(!feof(ArsBayarFormulir)))
    {
        if(TrsbayarForm.ID == ID && TrsbayarForm.StatusFormulir == 1) {
            found = true;
            break;
        }else{
            fwrite(&TrsbayarForm, sizeof(TrsbayarForm), 1, TempBayarFormulir);
        }
        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
    }

    // Jika Data ditemukan
    if (found == true) {
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        while((!found1)&&(!feof(ArsPendaftaran)))
        {
            if(Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                found1 = true;
                break;
            }else{
                fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
            }
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        }
    } else{
        MessageBox(NULL, "Data Pembayaran Formulir Tidak Tersedia!","PERINGATAN", MB_OK | MB_ICONWARNING );
        CleanTengah();
        CleanKanan();
        CleanKiri();
        VerifikasiBayarForm();
    }

    if (found1 == true){

        CleanTengah();
        DesainData();

        gotoxy(70, 19); printf("===============================");
        gotoxy(70, 20); printf("|D|A|T|A| |B|A|Y|A|R| |F|O|R|M|");
        gotoxy(70, 21); printf("===============================");

        gotoxy(60, 25); printf(" ID Pembayaran Form   : TRSF%.5d", TrsbayarForm.ID);
        gotoxy(60, 26); printf(" Virtual Account Form : %s", TrsbayarForm.VaFormulir);
        gotoxy(60, 27); printf(" Bukti Resi           : %s", TrsbayarForm.ResiBukti);
        gotoxy(60, 28); printf(" Tanggal Pembayaran   : %.2d/%.2d/%.4d", TrsbayarForm.TanggalBayar.tgl, TrsbayarForm.TanggalBayar.bulan, TrsbayarForm.TanggalBayar.tahun);
        gotoxy(60, 29); printf(" Status Pembayaran    : %s", StatusFormulir[TrsbayarForm.StatusFormulir]);

        verif:
        CleanKanan();
        gotoxy(133,20); printf("  VERIFIKASI PEMBAYARAN FORMULIR");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Input verifikasi? [Y/N] = [ ]");
        gotoxy(162, 22); getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            TrsbayarForm.StatusFormulir = 2;
            Trspendaftaran.StatusPendaftaran = 2;
            Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
        } else if (kf == 'N' || kf == 'n'){
            TrsbayarForm.StatusFormulir = 0;
            Trspendaftaran.StatusPendaftaran = 0;
            Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
        }else {
            goto verif;
        }

        fwrite(&TrsbayarForm,sizeof(TrsbayarForm), 1, TempBayarFormulir);
        fwrite(&Trspendaftaran,sizeof(Trspendaftaran), 1, TempPendaftaran);

        fread(&TrsbayarForm, sizeof (TrsbayarForm), 1, ArsBayarFormulir);
        while (!feof(ArsBayarFormulir)){
            fwrite(&TrsbayarForm, sizeof (TrsbayarForm), 1, TempBayarFormulir);
            fread(&TrsbayarForm, sizeof (TrsbayarForm), 1, ArsBayarFormulir);
        }

        fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)){
            fwrite(&Trspendaftaran, sizeof (Trspendaftaran), 1, TempPendaftaran);
            fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        }

    }

    fclose(ArsBayarFormulir);
    fclose(TempBayarFormulir);
    fclose(ArsPendaftaran);
    fclose(TempPendaftaran);

    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "wb");
    TempBayarFormulir = fopen("TempBayarFormulir.dat", "rb");

    fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, TempBayarFormulir);
    while (!feof(TempBayarFormulir)) {
        fwrite(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir);
        fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, TempBayarFormulir);
    }
    fclose(ArsBayarFormulir);
    fclose(TempBayarFormulir);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
    while (!feof(TempPendaftaran)) {
        fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
    }
    fclose(ArsPendaftaran);
    fclose(TempPendaftaran);

    lagi:
    CleanTengah();
    CleanKiri();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI VERIF KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Verif lagi? [Y/N] = [ ]");
    gotoxy(162, 22);getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        VerifikasiBayarForm();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        FinanceMenu();
    }else {
        CleanKanan();
        CleanTengah();
        goto lagi;
    }
}






