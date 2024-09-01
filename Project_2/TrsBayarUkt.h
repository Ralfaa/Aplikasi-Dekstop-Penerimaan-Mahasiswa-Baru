void InputBuktiUkt(); // oleh camaba, input bukti resi pembayaran dan tanggal pembayaran
void LihatPengajuanBayarUkt1(); // untuk bagian finance, menampilkan tabel pembayaran Ukt bagi camaba yang sudah input bukti resi pembayaran
void LihatPembayaranUkt(); // untuk bagian finance, menampilkan tabel semua Ukt pembayaran
void VerifikasiBayarUkt(); // oleh finance melakukan verifikasi terhadap konfirmasi pembayaran yang dilakukan camaba
int HitungTotalPengajuanUkt();

void InputBuktiUkt(){

    int ID; // menyimpan inputan id pendaftaran
    int ID_Camaba;
    int sukses = 0;
    bool found, found1, found2;
    char buktiresi[50];

    lihat:
    CleanTengah();
    CleanKanan();
    LihatFormulir2();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");

    SetColor(241);
    gotoxy(133,20); printf("  KONFIRMASI PEMBAYARAN UKT");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Pendaftaran : FRM"); getnum(&ID, 2);

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        CamabaMenu();
    }

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

        ArsBayarUkt = fopen("FileBayarUkt.dat","rb");
        TempBayarUkt = fopen("TempBayarUkt.dat", "wb");

        found1 = false;

        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        while((!found1) && (!feof(ArsBayarUkt))) {
            if(TrsbayarUkt.ID_Pendaftaran == Trspendaftaran.ID){
                found1 = true;
                break;
            }
            else{
                fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
            }
            fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        }

        if((found1 == true) && ((TrsbayarUkt.StatusUkt == 0)||(TrsbayarUkt.StatusUkt == 3))){
            CleanKanan();
            CleanTengah();
            DesainData();

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            gotoxy(63,19); printf("===========================================");
            gotoxy(63,20); printf("|K|O|N|F|I|R|M|A|S|I| |B|A|Y|A|R| |U|K|T|");
            gotoxy(63,21); printf("===========================================");

            gotoxy(60,28); printf(" ID Pembayaran Ukt  : TRSU%.5d",TrsbayarUkt.ID);
            gotoxy(60,29); printf(" No Virtual Account : %s",TrsbayarUkt.VaUkt);
            gotoxy(60,30); printf(" Tanggal Pembayaran : "); fflush(stdin);
            getnum(&TrsbayarUkt.TanggalBayar.tgl, 2); printf(" / ");
            getnum(&TrsbayarUkt.TanggalBayar.bulan, 2); printf(" / ");
            getnum(&TrsbayarUkt.TanggalBayar.tahun, 4);


            found2 = false;

            if(datevalid(TrsbayarUkt.TanggalBayar)){
                ArsGelombang = fopen("FileGelombang.dat","rb");
                while (fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang) == 1) {
                    if(Mgelombang.ID == Trspendaftaran.ID_Gelombang){
                        if ((TrsbayarUkt.TanggalBayar.tahun > Trspendaftaran.tanggalDaftar.tahun ||
                             (TrsbayarUkt.TanggalBayar.tahun == Trspendaftaran.tanggalDaftar.tahun &&
                              TrsbayarUkt.TanggalBayar.bulan > Trspendaftaran.tanggalDaftar.bulan) ||
                             (TrsbayarUkt.TanggalBayar.tahun == Trspendaftaran.tanggalDaftar.tahun &&
                              TrsbayarUkt.TanggalBayar.bulan == Trspendaftaran.tanggalDaftar.bulan &&
                              TrsbayarUkt.TanggalBayar.tgl >= Trspendaftaran.tanggalDaftar.tgl)) &&
                            (TrsbayarUkt.TanggalBayar.tahun < tm.tm_year + 1900 ||
                             (TrsbayarUkt.TanggalBayar.tahun == tm.tm_year + 1900 &&
                              TrsbayarUkt.TanggalBayar.bulan < tm.tm_mon + 1) ||
                             (TrsbayarUkt.TanggalBayar.tahun == tm.tm_year + 1900 &&
                              TrsbayarUkt.TanggalBayar.bulan == tm.tm_mon + 1&&
                              TrsbayarUkt.TanggalBayar.tgl <= tm.tm_mday))) {
                            found2 = true;
                            break;
                        }
                    }
                }
            }

            if(found2 == true) {
                gotoxy(60, 31);
                printf(" Bukti Resi         : ");
                fflush(stdin);
                getteks(buktiresi, 15);

                strcpy(TrsbayarUkt.ResiBukti, buktiresi);
                TrsbayarUkt.StatusUkt = 1;
                Trspendaftaran.StatusPendaftaran = 9;
                fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
                fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);

                fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
                while (!feof(ArsBayarUkt)) {
                    fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
                    fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
                }

                fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
                while (!feof(ArsPendaftaran)) {
                    fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
                    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
                }
            }else{
                MessageBox(NULL, "Tanggal Pembayaran Tidak Sesuai dengan tanggal pendaftaran, tanggal Hari Ini!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto lihat;
            }
        } else if ((found1 == true) && ((TrsbayarUkt.StatusUkt == 1)||(TrsbayarUkt.StatusUkt == 2))){
            MessageBox(NULL, " Pembayaran Ukt Formulir Ini sudah Dikonfirmasi!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanTengah();
            CleanKanan();
            CleanKiri();
            CamabaMenu();
        } else{
            MessageBox(NULL, "Formulir Pendaftaran ini belum Lulus Seleksi Tahap 3 !! Belum Memiliki VA Pembayaran Ukt !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanTengah();
            CleanKanan();
            CleanKiri();
            CamabaMenu();
        }

        fclose(ArsBayarUkt);
        fclose(TempBayarUkt);
        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);

        ArsBayarUkt = fopen("FileBayarUkt.dat", "wb");
        TempBayarUkt = fopen("TempBayarUkt.dat", "rb");

        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
        while (!feof(TempBayarUkt)) {
            fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
            fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
        }
        fclose(ArsBayarUkt);
        fclose(TempBayarUkt);

        ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        while (!feof(TempPendaftaran)) {
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        }
        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);
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

void LihatPembayaranUkt(){

    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsBayarUkt = fopen("FileBayarUkt.dat", "rb");

    // Jika Data Bayar Ukt
    if (ArsBayarUkt == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Pembayaran Ukt masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        FinanceMenu();
    }else {
        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16);
        printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Ukt", "Va Ukt", "Tanggal Bayar", "Status");
        while (!feof(ArsBayarUkt)) {
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
                   TrsbayarUkt.ID,
                   TrsbayarUkt.VaUkt,
                   TrsbayarUkt.TanggalBayar.tgl, TrsbayarUkt.TanggalBayar.bulan, TrsbayarUkt.TanggalBayar.tahun,
                   StatusUkt[TrsbayarUkt.StatusUkt]);
            SetColor(241);

            fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);

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
                printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Ukt", "Va Ukt", "Tanggal Bayar", "Status");
            }
        }
        fclose(ArsBayarUkt);
        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            CleanTengah();
            FinanceMenu();
            getch();
        } else {
            LihatPembayaranUkt();
        }
    }
}

void LihatPengajuanBayarUkt1(){

    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsBayarUkt = fopen("FileBayarUkt.dat", "rb");

    // Jika Data Bayar UKT
    if (ArsBayarUkt == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Pembayaran Ukt masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        FinanceMenu();
    }else {
        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16);
        printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Ukt", "Va Ukt", "Tanggal Bayar", "Status");
        while (!feof(ArsBayarUkt)) {
            if (TrsbayarUkt.StatusUkt == 1) {
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
                printf(" TRSU%-11.5d | %-20s | %.2d-%.2d-%-9.4d | %-10s",
                       TrsbayarUkt.ID,
                       TrsbayarUkt.VaUkt,
                       TrsbayarUkt.TanggalBayar.tgl, TrsbayarUkt.TanggalBayar.bulan, TrsbayarUkt.TanggalBayar.tahun,
                       StatusUkt[TrsbayarUkt.StatusUkt]);
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
                    printf(" %-15s | %-20s | %-15s | %-15s", "ID Trs Ukt", "Va Ukt", "Tanggal Bayar", "Status");
                }
            }
            fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        }
        fclose(ArsBayarUkt);
        SetColor(252);
    }
}

// Fungsi untuk menghitung total pengajuan UKT
int HitungTotalPengajuanUkt() {
    int totalPengajuanUkt = 0;

    ArsBayarUkt = fopen("FileBayarUkt.dat", "rb");
    if (ArsBayarUkt == NULL) {
        return 0; // Jika file tidak ditemukan atau kosong
    }

    while (fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt) == 1) {
        if (TrsbayarUkt.StatusUkt == 1) {
            totalPengajuanUkt++;
        }
    }

    fclose(ArsBayarUkt);
    return totalPengajuanUkt;
}

void VerifikasiBayarUkt(){

    int ID;
    char kf;
    bool found, found1, found2;

    CleanTengah();
    CleanKanan();

    LihatPengajuanBayarUkt1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  VERIFIKASI PEMBAYARAN UKT");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Tansaksi Ukt   : TRSU"); getnum(&ID, 5);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        FinanceMenu();
    }

    ArsBayarUkt = fopen("FileBayarUkt.dat","rb");
    TempBayarUkt = fopen("TempBayarUkt.dat", "wb");

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    ArsCamaba = fopen("FileCamaba.dat", "rb");
    TempCamaba = fopen("TempCamaba.dat", "wb");

    found = false;
    found1 = false;
    found2 = false;

    fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
    while((!found)&&(!feof(ArsBayarUkt)))
    {
        if(TrsbayarUkt.ID == ID && TrsbayarUkt.StatusUkt == 1) {
            found = true;
            break;
        }else{
            fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
        }
        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
    }

    // Jika Data ditemukan
    if (found == true) {
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        while((!found1)&&(!feof(ArsPendaftaran)))
        {
            if(Trspendaftaran.ID == TrsbayarUkt.ID_Pendaftaran) {
                found1 = true;
                break;
            }else{
                fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
            }
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        }
    } else{
        MessageBox(NULL, "Data Pembayaran UKT Tidak Tersedia!","PERINGATAN", MB_OK | MB_ICONWARNING );
        CleanTengah();
        CleanKanan();
        FinanceMenu();
    }

    if (found1 == true){

        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        while((!found2) && (!feof(ArsCamaba)))
        {
            if(Mcamaba.ID == Trspendaftaran.ID_Camaba) {
                found2 = true;
                break;
            } else {
                fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
            }
            fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        }

    }

    if(found2 == true){

        CleanTengah();
        DesainData();

        gotoxy(70, 19); printf("===============================");
        gotoxy(70, 20); printf("|D|A|T|A| |B|A|Y|A|R| |U|K|T|");
        gotoxy(70, 21); printf("===============================");

        gotoxy(60, 25); printf(" ID Pembayaran Ukt    : TRSU%.5d", TrsbayarUkt.ID);
        gotoxy(60, 26); printf(" Virtual Account Ukt  : %s", TrsbayarUkt.VaUkt);
        gotoxy(60, 27); printf(" Bukti Resi           : %s", TrsbayarUkt.ResiBukti);
        gotoxy(60, 28); printf(" Tanggal Pembayaran   : %.2d/%.2d/%.4d", TrsbayarUkt.TanggalBayar.tgl, TrsbayarUkt.TanggalBayar.bulan, TrsbayarUkt.TanggalBayar.tahun);
        gotoxy(60, 29); printf(" Status Pembayaran    : %s", StatusUkt[TrsbayarUkt.StatusUkt]);

        verif:
        CleanKanan();
        gotoxy(133,20); printf("  VERIFIKASI PEMBAYARAN UKT");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Input verifikasi? [Y/N] = [ ]");
        gotoxy(162, 22); getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            TrsbayarUkt.StatusUkt = 2;
            Trspendaftaran.StatusPendaftaran = 11;
            Mcamaba.StatusAkun = 3;
            Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
        } else if (kf == 'N' || kf == 'n'){
            TrsbayarUkt.StatusUkt = 3;
            Trspendaftaran.StatusPendaftaran = 14;
            Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
        }else {
            goto verif;
        }

        fwrite(&TrsbayarUkt,sizeof(TrsbayarUkt), 1, TempBayarUkt);
        fwrite(&Trspendaftaran,sizeof(Trspendaftaran), 1, TempPendaftaran);
        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);

        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        while (!feof(ArsCamaba)) {
            fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
            fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        }

        fread(&TrsbayarUkt, sizeof (TrsbayarUkt), 1, ArsBayarUkt);
        while (!feof(ArsBayarUkt)){
            fwrite(&TrsbayarUkt, sizeof (TrsbayarUkt), 1, TempBayarUkt);
            fread(&TrsbayarUkt, sizeof (TrsbayarUkt), 1, ArsBayarUkt);
        }

        fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)){
            fwrite(&Trspendaftaran, sizeof (Trspendaftaran), 1, TempPendaftaran);
            fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        }

    }

    fclose(ArsBayarUkt);
    fclose(TempBayarUkt);
    fclose(ArsPendaftaran);
    fclose(TempPendaftaran);
    fclose(ArsCamaba);
    fclose(TempCamaba);

    ArsBayarUkt = fopen("FileBayarUkt.dat", "wb");
    TempBayarUkt = fopen("TempBayarUkt.dat", "rb");

    fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
    while (!feof(TempBayarUkt)) {
        fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);
        fread(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, TempBayarUkt);
    }
    fclose(ArsBayarUkt);
    fclose(TempBayarUkt);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
    while (!feof(TempPendaftaran)) {
        fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
    }
    fclose(ArsPendaftaran);
    fclose(TempPendaftaran);

    ArsCamaba = fopen("FileCamaba.dat", "wb");
    TempCamaba = fopen("TempCamaba.dat", "rb");

    fread(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
    while (!feof(TempCamaba)) {
        fwrite(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        fread(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
    }
    fclose(ArsCamaba);
    fclose(TempCamaba);

    lagi:
    CleanTengah();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI VERIF KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Verif lagi? [Y/N] = [ ]");
    gotoxy(162, 22);getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        VerifikasiBayarUkt();
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