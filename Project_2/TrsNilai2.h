void InputNilai2();
void InputPsg2();
void InputPengumumanTahap2();
void LihatCamabaSeleksi2();
void LihatNilai2Keseluruhan();
void LihatNilai2TungguPengumuman();
void LihatNilai2LulusSeleksi();
void LihatNilai2TidakLulus();

void LihatCamabaSeleksi2(){

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
            if(Trspendaftaran.StatusPendaftaran == 4) {
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
                    gotoxy(Kolom, 16); printf(" %-15s | %-15s | %-15s | %-15s","ID Pendaftaran", "Tahun Ajaran", "Gelombang", "Jalur Penerimaan");
                }
            }
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            SetColor(252);
        }fclose(ArsPendaftaran);
    }

}

void InputNilai2(){

    int ID;
    bool found;
    float Nilai_Psikotest;
    char kf;

    lihat:
    CleanTengah();
    CleanKanan();
    LihatCamabaSeleksi2();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  INPUT NILAI SELEKSI TAHAP 2");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Pendaftaran : FRM");
    getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }

    found = false;

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    while((!found)&&(!feof(ArsPendaftaran)))
    {
        if(Trspendaftaran.ID == ID) {
            if(Trspendaftaran.StatusPendaftaran == 4){
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

    //jika formulir pendaftarannya dengan id yang di input dan sudah lulus tahap 1
    if(found == true){

        ArsTrsNilai2 = fopen("FileNilai2.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

        while(!feof(ArsTrsNilai2))
        {
            fread(&Trsnilai2, sizeof(Trsnilai2),1 , ArsTrsNilai2);
        }
        Trsnilai2.ID++;

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

        while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
            if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                break;
            }
        }

        Trsnilai2.ID_BayarForm = TrsbayarForm.ID;

        inputnilai:
        CleanTengah();
        CleanKanan();
        DesainData();

        gotoxy(66, 19);printf("===============================");
        gotoxy(66, 20);printf("|N|I|L|A|I| |S|E|L|E|K|S|I| |2|");
        gotoxy(66, 21);printf("===============================");

        gotoxy(60,41); printf(" Input Rentang Nilai yaitu 1 - 160");
        SetColor(241);

        gotoxy(60, 25); printf(" ID Pendaftaran         : FRM%.5d", Trspendaftaran.ID);
        gotoxy(60, 26); printf(" ID Transaksi Nilai 2   : TRSN%.5d", Trsnilai2.ID);
        gotoxy(60, 27); printf(" ID Camaba              : CMB%.5d", Trspendaftaran.ID_Camaba);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        Trsnilai2.TanggalPsikotest.tgl = tm.tm_mday;
        Trsnilai2.TanggalPsikotest.tahun = tm.tm_mon + 1;
        Trsnilai2.TanggalPsikotest.bulan = tm.tm_year + 1900;

        gotoxy(60, 28); printf(" Tanggal Transaksi 2    : %.2d/%.2d/%.4d", Trsnilai2.TanggalPsikotest.tgl, Trsnilai2.TanggalPsikotest.bulan, Trsnilai2.TanggalPsikotest.tahun);
        gotoxy(60, 29); printf(" Skor IQ Psikotest      : ");
        gotoxy(86, 29);fflush(stdin); getnum1(&Nilai_Psikotest, 3);

        if(Nilai_Psikotest > 160){
            MessageBox(NULL, "Rentang Nilai Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto inputnilai;
        }

        Trspendaftaran.StatusPendaftaran = 5;
        fwrite(&Trspendaftaran,sizeof(Trspendaftaran), 1, TempPendaftaran);

        Trsnilai2.SkorPsikotest = Nilai_Psikotest;
        Trsnilai2.Status = 0;
        fwrite(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
        fclose(ArsTrsNilai2);

        fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)){
            fwrite(&Trspendaftaran, sizeof (Trspendaftaran), 1, TempPendaftaran);
            fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        }
    }else {
        MessageBox(NULL, "Data Formulir Tidak Tersedia Karena Belum Melakukan Pembayaran atau Telah mengisi nilai Formulir ini!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        CleanKiri();
        PenilaianMenu();
    }

    fclose(ArsPendaftaran);
    fclose(TempPendaftaran);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
    while (!feof(TempPendaftaran)) {
        fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
    }
    fclose(ArsPendaftaran);
    fclose(TempPendaftaran);

    input:
    CleanTengah();
    CleanKanan();

    SetColor(241);
    gotoxy(133,20); printf("  KONFIRMASI INPUT NILAI KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin input lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        InputNilai2();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto input;
    }
}

void InputPsg2(){

    float psg2;
    int ID;
    bool found;
    char kf;

    // Algoritma
    fflush(stdin);
    LihatPassingGrade();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  INPUT PASSING GRADE");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Prodi  : PRD"); getnum(&ID,3);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }

    ArsProgramStudi = fopen("FileProgramStudi.dat","rb");
    TempProgramStudi = fopen("TempProgramStudi.dat", "wb");

    found = false;

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    while((!found) && (!feof(ArsProgramStudi)))
    {
        if(Mprodi.ID == ID){
            found = true;
            break;
        }
        else{
            fwrite(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    if(found == true){

        inputpsg:
        CleanKanan();
        CleanTengah();
        DesainData();
        // DATA YANG AKAN DIUBAH
        gotoxy(73,19); printf("=====================");
        gotoxy(73,20); printf("|D|A|T|A| |P|R|O|D|I|");
        gotoxy(73,21); printf("=====================");

        SetColor(252);
        gotoxy(60,41); printf(" Input Rentang Nilai Passing Grade yaitu 1 - 160");
        SetColor(241);

        gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");

        gotoxy(60,28); printf(" ID Prodi        :   PRD%.3d",Mprodi.ID);
        gotoxy(60,29); printf(" Nama Prodi      :   %s",Mprodi.nama_prodi);
        gotoxy(60,30); printf(" Kuota Prodi     :   %d",Mprodi.kuota);
        gotoxy(60,31); printf(" Tahun Berdiri   :   %s",Mprodi.tahun_berdiri);
        gotoxy(60,32); printf(" Status          :   %s",StatusProdi[Mprodi.status]);
        gotoxy(60,33); printf(" Passing Grade 2 :   ");

        gotoxy(81,33); getnum1(&psg2, 3);

        if(psg2 > 160){
            MessageBox(NULL, "Rentang Nilai Passing Grade Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto inputpsg;
        }

        Mprodi.psg2 = psg2;

        fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);

        fread(&Mprodi, sizeof (Mprodi), 1, ArsProgramStudi);
        while (!feof(ArsProgramStudi)){
            fwrite(&Mprodi, sizeof (Mprodi), 1, TempProgramStudi);
            fread(&Mprodi, sizeof (Mprodi), 1, ArsProgramStudi);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    }else{
        MessageBox(NULL, "ID Prodi tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        InputPsg2();
    }

    fclose(ArsProgramStudi);
    fclose(TempProgramStudi);

    ArsProgramStudi = fopen("FileProgramStudi.dat", "wb");
    TempProgramStudi = fopen("TempProgramStudi.dat", "rb");

    fread(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
    while (!feof(TempProgramStudi)) {
        fwrite(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
        fread(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
    }
    fclose(ArsProgramStudi);
    fclose(TempProgramStudi);

    update:
    CleanTengah();
    CleanKanan();
    LihatProgramStudi1();

    SetColor(241);
    gotoxy(133,20); printf("  KONFIRMASI INPUT PSG KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin input lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        InputPsg2();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto update;
    }
}

void InputPengumumanTahap2(){

    char kf;
    bool found1;

    pengumuman:
    CleanTengah();
    CleanKanan();
    LihatPassingGrade();

    gotoxy(133,20); printf("  KONFIRMASI PENGUMUMAN TAHAP 2");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Input Pengumuman? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);

    if (kf == 'y' || kf == 'Y') {

        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)) {

            if(Trspendaftaran.StatusPendaftaran == 5) {

                ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
                TempProgramStudi = fopen("TempProgramStudi.dat", "wb");
                found1 = false;

                fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
                while ((!found1) && (!feof(ArsProgramStudi))) {
                    if (Mprodi.ID == Trspendaftaran.ID_Prodi) {
                        found1 = true;
                        break;
                    } else {
                        fwrite(&MasterProgramStudi, sizeof(Mprodi), 1, TempProgramStudi);
                    }
                    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
                }

                if (found1 == true) {

                        ArsTrsNilai2 = fopen("FileNilai2.dat", "rb");
                        TempTrsNilai2 = fopen("TempNilai2.dat", "wb");

                    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

                    while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
                        if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                            break;
                        }
                    }

                        while (fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2) == 1) {
                            if (Trsnilai2.ID_BayarForm == TrsbayarForm.ID) {
                                if (Trsnilai2.SkorPsikotest > Mprodi.psg2) {
                                    Trsnilai2.Status = 1;
                                    Trspendaftaran.StatusPendaftaran = 6;
                                    Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                                } else {
                                    Trsnilai2.Status = 2;
                                    Trspendaftaran.StatusPendaftaran = 12;
                                    Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                                }
                            }
                            fwrite(&Trsnilai2, sizeof(Trsnilai2), 1, TempTrsNilai2);
                        }

                        // Tutup file yang sudah dibuka sebelumnya
                        fclose(ArsTrsNilai2);
                        fclose(TempTrsNilai2);

                        // Buka kembali file-file yang telah diolah
                        ArsTrsNilai2 = fopen("FileNilai2.dat", "wb");
                        TempTrsNilai2 = fopen("TempNilai2.dat", "rb");

                        // Salin isi file temporer ke file utama
                        while (fread(&Trsnilai2, sizeof(Trsnilai2), 1, TempTrsNilai2) == 1) {
                            fwrite(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
                        }

                        // Tutup file yang sudah selesai diproses
                        fclose(ArsTrsNilai2);
                        fclose(TempTrsNilai2);

                        ArsCamaba = fopen("FileCamaba.dat", "rb");
                        TempCamaba = fopen("TempCamaba.dat", "wb");

                        while (fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba) == 1) {
                            if (Mcamaba.ID == Trspendaftaran.ID_Camaba) {
                                if (Trspendaftaran.StatusPendaftaran == 12) {
                                    Mcamaba.StatusAkun = 0;
                                }
                            }
                            fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        }

                        // Tutup file yang sudah dibuka sebelumnya
                        fclose(ArsCamaba);
                        fclose(TempCamaba);

                        // Buka kembali file-file yang telah diolah
                        ArsCamaba = fopen("FileCamaba.dat", "wb");
                        TempCamaba = fopen("TempCamaba.dat", "rb");

                        // Salin isi file temporer ke file utama
                        while (fread(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba) == 1) {
                            fwrite(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
                        }

                        // Tutup file yang sudah selesai diproses
                        fclose(ArsCamaba);
                        fclose(TempCamaba);

                }
            }else {
                Trspendaftaran.StatusPendaftaran = 12;
            }
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        }

        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);

        ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        while (!feof(TempPendaftaran)) {
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
            fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        }
        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);
        MessageBox(NULL, "Pengumuman Tahap 2 Selesai di lakukan !!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    }else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }else {
        CleanKanan();
        CleanTengah();
        goto pengumuman;
    }

    CleanTengah();
    CleanKanan();
    CleanKiri();
    PenilaianMenu();

}

void LihatNilai2Keseluruhan() {

    // Deklarasi
    int ID;
    char kf;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found2,found3;

    balik:

    LihatProgramStudi1();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  LIHAT NILAI KESELURUHAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Prodi : PRD");
    getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        LihatNilaiSeleksiMenu();
    }

    CleanTengah();
    fflush(stdin);

    // Memanggil Data Program Studi
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    found2 = false;

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    while ((!found2) && (!feof(ArsProgramStudi))) {
        if (Mprodi.ID == ID) {
            found2 = true;
            break;
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    if (found2 != true) {
        MessageBox(NULL, "Program Studi ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        goto balik;

    }

    fclose(ArsProgramStudi);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    gotoxy(Kolom, 16);
    printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
           "Nilai IQ Psikotest", "Status");

    // membuat array untuk tempat sorting
    TrsNilai2 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai2 = fopen("FileNilai2.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);

            while (!feof(ArsTrsNilai2)) {
                if (Trsnilai2.ID_BayarForm == TrsbayarForm.ID) {
                    trs[n] = Trsnilai2;
                    n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                    break;
                }
                fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
            }
            fclose(ArsTrsNilai2);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorPsikotest < trs[j + 1].SkorPsikotest) {
                tmp = trs[j];
                trs[j] = trs[j + 1];
                trs[j + 1] = tmp;
            }
        }
    }

    // Menampilkan data
    for (int i = 0; i < n; i++) {
        Baris++;
        Hal++;
        if (Baris % 2 == 0) {
            gotoxy(Kolom, Baris);
            SetColor(31);
        } else {
            gotoxy(Kolom, Baris);
            SetColor(233);
        }
        for (int j = 1; j <= Kolom + 54; j++) {
            printf(" ");
        }

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");
        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
                fclose(ArsPendaftaran);  // menutup file setelah digunakan
                break;
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-12.5d | TRSN%-11.5d | %18.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorPsikotest,
               StatusSeleksi2[trs[i].Status]);
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
            printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
                   "Nilai IQ Psikotest", "Status");
        }
    }
    fclose(ArsBayarFormulir);
    SetColor(252);

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LIHAT NILAI KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LihatNilaiSeleksiMenu();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto lihat;
    }
}

void LihatNilai2TungguPengumuman() {

    // Deklarasi
    int ID;
    char kf;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found2, found3;

    balik:
    LihatProgramStudi1();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  LIHAT NILAI TUNGGU PENGUMUMAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Prodi : PRD");
    getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        LihatNilaiSeleksiMenu();
    }

    CleanTengah();
    fflush(stdin);

    // Memanggil Data Program Studi
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    found2 = false;

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    while ((!found2) && (!feof(ArsProgramStudi))) {
        if (Mprodi.ID == ID) {
            found2 = true;
            break;
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    if (found2 != true) {
        MessageBox(NULL, "Program Studi ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        goto balik;

    }

    fclose(ArsProgramStudi);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    gotoxy(Kolom, 16);
    printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
           "Nilai IQ Psikotest", "Status");

    // membuat array untuk tempat sorting
    TrsNilai2 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai2 = fopen("FileNilai2.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);

            while (!feof(ArsTrsNilai2)) {
                if (Trsnilai2.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai2.Status == 0) {
                        trs[n] = Trsnilai2;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
            }
            fclose(ArsTrsNilai2);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorPsikotest < trs[j + 1].SkorPsikotest) {
                tmp = trs[j];
                trs[j] = trs[j + 1];
                trs[j + 1] = tmp;
            }
        }
    }

    // Menampilkan data
    for (int i = 0; i < n; i++) {
        Baris++;
        Hal++;
        if (Baris % 2 == 0) {
            gotoxy(Kolom, Baris);
            SetColor(31);
        } else {
            gotoxy(Kolom, Baris);
            SetColor(233);
        }
        for (int j = 1; j <= Kolom + 54; j++) {
            printf(" ");
        }

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");
        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
                fclose(ArsPendaftaran);  // menutup file setelah digunakan
                break;
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-12.5d | TRSN%-11.5d | %18.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorPsikotest,
               StatusSeleksi2[Trsnilai2.Status]);
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
            printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
                   "Nilai IQ Psikotest", "Status");
        }
    }
    fclose(ArsBayarFormulir);
    SetColor(252);

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LIHAT NILAI KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LihatNilaiSeleksiMenu();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto lihat;
    }
}

void LihatNilai2LulusSeleksi() {

    // Deklarasi
    int ID;
    char kf;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found2, found3;

    balik:
    LihatProgramStudi1();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  LIHAT NILAI LULUS SELEKSI");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Prodi : PRD");
    getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        LihatNilaiSeleksiMenu();
    }

    CleanTengah();
    fflush(stdin);

    // Memanggil Data Program Studi
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    found2 = false;

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    while ((!found2) && (!feof(ArsProgramStudi))) {
        if (Mprodi.ID == ID) {
            found2 = true;
            break;
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    if (found2 != true) {
        MessageBox(NULL, "Program Studi ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        goto balik;

    }

    fclose(ArsProgramStudi);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    gotoxy(Kolom, 16);
    printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
           "Nilai IQ Psikotest", "Status");

    // membuat array untuk tempat sorting
    TrsNilai2 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai2 = fopen("FileNilai2.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);

            while (!feof(ArsTrsNilai2)) {
                if (Trsnilai2.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai2.Status == 1) {
                        trs[n] = Trsnilai2;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
            }
            fclose(ArsTrsNilai2);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorPsikotest < trs[j + 1].SkorPsikotest) {
                tmp = trs[j];
                trs[j] = trs[j + 1];
                trs[j + 1] = tmp;
            }
        }
    }

    // Menampilkan data
    for (int i = 0; i < n; i++) {
        Baris++;
        Hal++;
        if (Baris % 2 == 0) {
            gotoxy(Kolom, Baris);
            SetColor(31);
        } else {
            gotoxy(Kolom, Baris);
            SetColor(233);
        }
        for (int j = 1; j <= Kolom + 54; j++) {
            printf(" ");
        }

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");
        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
                fclose(ArsPendaftaran);  // menutup file setelah digunakan
                break;
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-12.5d | TRSN%-11.5d | %18.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorPsikotest,
               StatusSeleksi2[Trsnilai2.Status]);
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
            printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
                   "Nilai IQ Psikotest", "Status");
        }
    }
    fclose(ArsBayarFormulir);
    SetColor(252);

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LIHAT NILAI KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LihatNilaiSeleksiMenu();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto lihat;
    }
}

void LihatNilai2TidakLulus() {

    // Deklarasi
    int ID;
    char kf;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found2, found3;

    balik:
    LihatProgramStudi1();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  LIHAT NILAI GAGAL SELEKSI");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Prodi : PRD");
    getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        LihatNilaiSeleksiMenu();
    }

    CleanTengah();
    fflush(stdin);

    // Memanggil Data Program Studi
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    found2 = false;

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    while ((!found2) && (!feof(ArsProgramStudi))) {
        if (Mprodi.ID == ID) {
            found2 = true;
            break;
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    if (found2 != true) {
        MessageBox(NULL, "Program Studi ini Tidak Tersedia!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        goto balik;

    }

    fclose(ArsProgramStudi);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    gotoxy(Kolom, 16);
    printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
           "Nilai IQ Psikotest", "Status");

    // membuat array untuk tempat sorting
    TrsNilai2 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai2 = fopen("FileNilai2.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);

            while (!feof(ArsTrsNilai2)) {
                if (Trsnilai2.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai2.Status == 2) {
                        trs[n] = Trsnilai2;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai2, sizeof(Trsnilai2), 1, ArsTrsNilai2);
            }
            fclose(ArsTrsNilai2);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorPsikotest < trs[j + 1].SkorPsikotest) {
                tmp = trs[j];
                trs[j] = trs[j + 1];
                trs[j + 1] = tmp;
            }
        }
    }

    // Menampilkan data
    for (int i = 0; i < n; i++) {
        Baris++;
        Hal++;
        if (Baris % 2 == 0) {
            gotoxy(Kolom, Baris);
            SetColor(31);
        } else {
            gotoxy(Kolom, Baris);
            SetColor(233);
        }
        for (int j = 1; j <= Kolom + 54; j++) {
            printf(" ");
        }

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");
        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
                fclose(ArsPendaftaran);  // menutup file setelah digunakan
                break;
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-12.5d | TRSN%-11.5d | %18.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorPsikotest,
               StatusSeleksi2[Trsnilai2.Status]);
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
            printf(" %-15s | %-15s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 2",
                   "Nilai IQ Psikotest", "Status");
        }
    }
    fclose(ArsBayarFormulir);
    SetColor(252);

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI LIHAT NILAI KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        LihatNilaiSeleksiMenu();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto lihat;
    }
}


