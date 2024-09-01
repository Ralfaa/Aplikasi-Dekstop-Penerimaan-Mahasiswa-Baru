void InputNilai3();
void InputPsg3();
void InputPengumumanTahap3();
void LihatCamabaSeleksi3();
void AkunVaUkt();
void LihatNilai3Keseluruhan();
void LihatNilai3TungguPengumuman();
void LihatNilai3LulusPassingGrade();
void LihatNilai3LulusSeleksi();
void LihatNilai3TidakLulus();

void LihatCamabaSeleksi3(){

    // Deklarasi
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
        while ((!feof(ArsPendaftaran)) ) {
            if(Trspendaftaran.StatusPendaftaran == 6) {
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

void InputNilai3(){

    int ID;
    bool found;
    float Nilai_Wawancara;
    char kf;

    lihat:
    CleanTengah();
    CleanKanan();
    LihatCamabaSeleksi3();

    SetColor(252);
    gotoxy(133, 44);
    printf(" Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  INPUT NILAI SELEKSI TAHAP 3");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Pendaftaran : FRM");
    getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    while((!found)&&(!feof(ArsPendaftaran)))
    {
        if(Trspendaftaran.ID == ID) {
            if(Trspendaftaran.StatusPendaftaran == 6){
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

        ArsTrsNilai3 = fopen("FileNilai3.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

        while(!feof(ArsTrsNilai3))
        {
            fread(&Trsnilai3, sizeof(Trsnilai3),1 , ArsTrsNilai3);
        }
        Trsnilai3.ID++;

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

        while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
            if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                break;
            }
        }

        Trsnilai3.ID_BayarForm = TrsbayarForm.ID;

        inputnilai:
        CleanTengah();
        CleanKanan();
        DesainData();

        gotoxy(66, 19);printf("===============================");
        gotoxy(66, 20);printf("|N|I|L|A|I| |S|E|L|E|K|S|I| |3|");
        gotoxy(66, 21);printf("===============================");

        gotoxy(60,41); printf(" Input Rentang Nilai yaitu 1 - 100");
        SetColor(241);


        gotoxy(60, 25); printf(" ID Pendaftaran         : FRM%.5d", Trspendaftaran.ID);
        gotoxy(60, 26); printf(" ID Transaksi Nilai 3   : TRSW%.5d", Trsnilai3.ID);
        gotoxy(60, 27); printf(" ID Camaba              : CMB%.5d", Trspendaftaran.ID_Camaba);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        Trsnilai3.TanggalWawancara.tgl = tm.tm_mday;
        Trsnilai3.TanggalWawancara.bulan = tm.tm_mon + 1;
        Trsnilai3.TanggalWawancara.tahun = tm.tm_year + 1900;

        gotoxy(60, 27); printf(" Tanggal Transaksi 3    : %.2d/%.2d/%.4d", Trsnilai3.TanggalWawancara.tgl, Trsnilai3.TanggalWawancara.bulan, Trsnilai3.TanggalWawancara.tahun);
        gotoxy(60, 28); printf(" Skor Wawancara         : ");
        gotoxy(86, 28);fflush(stdin); getnum1(&Nilai_Wawancara, 3);

        if(Nilai_Wawancara > 160){
            MessageBox(NULL, "Rentang Nilai Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto inputnilai;
        }

        Trspendaftaran.StatusPendaftaran = 7;
        fwrite(&Trspendaftaran,sizeof(Trspendaftaran), 1, TempPendaftaran);

        Trsnilai3.SkorWawancara = Nilai_Wawancara;
        Trsnilai3.Status = 0;
        fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
        fclose(ArsTrsNilai3);

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
        InputNilai3();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto input;
    }
}

void InputPsg3(){

    float psg3;
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
        gotoxy(60,41); printf(" Input Rentang Nilai Passing Grade yaitu 1 - 100");
        SetColor(241);

        gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");

        gotoxy(60,28); printf(" ID Prodi        :   PRD%.3d",Mprodi.ID);
        gotoxy(60,29); printf(" Nama Prodi      :   %s",Mprodi.nama_prodi);
        gotoxy(60,30); printf(" Kuota Prodi     :   %d",Mprodi.kuota);
        gotoxy(60,31); printf(" Tahun Berdiri   :   %s",Mprodi.tahun_berdiri);
        gotoxy(60,32); printf(" Status          :   %s",StatusProdi[Mprodi.status]);
        gotoxy(60,33); printf(" Passing Grade 3 :   ");

        gotoxy(81,33); getnum1(&psg3, 3);

        if(psg3 > 100){
            MessageBox(NULL, "Rentang Nilai Passing Grade Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto inputpsg;
        }

        Mprodi.psg3 = psg3;

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
        InputPsg3();
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
        InputPsg3();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }else {
        CleanKanan();
        goto update;
    }
}


void InputPengumumanTahap3(){

    char kf;
    bool found1;
    int jumlahditerima;

    pengumuman:
    CleanTengah();
    CleanKanan();
    LihatPassingGrade();

    gotoxy(133,20); printf("  KONFIRMASI PENGUMUMAN TAHAP 3");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Input Pengumuman? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);

    if (kf == 'y' || kf == 'Y') {

        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)) {

            if(Trspendaftaran.StatusPendaftaran == 7) {

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

                    ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");
                    TempTrsNilai3 = fopen("TempNilai3.dat", "wb");

                    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

                    while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
                        if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                            break;
                        }
                    }

                    while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3) == 1) {
                            if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                                if (Trsnilai3.SkorWawancara > Mprodi.psg3) {
                                    Trsnilai3.Status = 1;
                                    Trspendaftaran.StatusPendaftaran = 8;
                                    Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                                } else {
                                    Trsnilai3.Status = 3;
                                    Trspendaftaran.StatusPendaftaran = 12;
                                    Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                                }
                            }
                            fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3);
                        }

                        // Tutup file yang sudah dibuka sebelumnya
                        fclose(ArsTrsNilai3);
                        fclose(TempTrsNilai3);

                        // Buka kembali file-file yang telah diolah
                        ArsTrsNilai3 = fopen("FileNilai3.dat", "wb");
                        TempTrsNilai3 = fopen("TempNilai3.dat", "rb");

                        // Salin isi file temporer ke file utama
                        while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3) == 1) {
                            fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
                        }

                        // Tutup file yang sudah selesai diproses
                        fclose(ArsTrsNilai3);
                        fclose(TempTrsNilai3);

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

        MessageBox(NULL, "Pengumuman Tahap 3 Selesai di lakukan !!","INFORMASI", MB_OK | MB_ICONINFORMATION );
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

void AkunVaUkt(){

    // Membuat virtual account
    ArsBayarUkt = fopen("FileBayarUkt.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsBayarUkt))
    {
        fread(&TrsbayarUkt, sizeof(TrsbayarUkt),1 , ArsBayarUkt);
    }
    TrsbayarUkt.ID++;

    strcpy(TrsbayarUkt.VaUkt, "VA1814");
    strcat(TrsbayarUkt.VaUkt, Mcamaba.no_telepon);
    TrsbayarUkt.StatusUkt = 0;

    TrsbayarUkt.ID_Pendaftaran = Trspendaftaran.ID;

    fwrite(&TrsbayarUkt, sizeof(TrsbayarUkt), 1, ArsBayarUkt);

    fclose(ArsBayarUkt);

}


void LihatNilai3Keseluruhan() {

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
    printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
           "Nilai Wawancara", "Status");

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

            while (!feof(ArsTrsNilai3)) {
                if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                    trs[n] = Trsnilai3;
                    n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                    break;
                }
                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }
            fclose(ArsTrsNilai3);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
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
               trs[i].SkorWawancara,
               StatusSeleksi3[trs[i].Status]);
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
            printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
                   "Nilai Wawancara", "Status");
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

void LihatNilai3TungguPengumuman() {

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
    printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
           "Nilai Wawancara", "Status");

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

            while (!feof(ArsTrsNilai3)) {
                if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai3.Status == 0) {
                        trs[n] = Trsnilai3;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }
            fclose(ArsTrsNilai3);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
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
               trs[i].SkorWawancara,
               StatusSeleksi3[Trsnilai3.Status]);
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
            printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
                   "Nilai Wawancara", "Status");
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

void LihatNilai3LulusSeleksi() {

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
    printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
           "Nilai Wawancara", "Status");

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

            while (!feof(ArsTrsNilai3)) {
                if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai3.Status == 2) {
                        trs[n] = Trsnilai3;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }
            fclose(ArsTrsNilai3);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
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
               trs[i].SkorWawancara,
               StatusSeleksi3[Trsnilai3.Status]);
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
            printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
                   "Nilai Wawancara", "Status");
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

void LihatNilai3TidakLulus() {

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
    printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
           "Nilai Wawancara", "Status");

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

            while (!feof(ArsTrsNilai3)) {
                if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai3.Status == 3) {
                        trs[n] = Trsnilai3;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }
            fclose(ArsTrsNilai3);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
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
               trs[i].SkorWawancara,
               StatusSeleksi3[Trsnilai3.Status]);
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
            printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
                   "Nilai Wawancara", "Status");
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

void LihatNilai3LulusPassingGrade() {

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
    gotoxy(133, 20); printf("  LIHAT NILAI LULUS PASSING GRADE");
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
    printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
           "Nilai Wawancara", "Status");

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

            while (!feof(ArsTrsNilai3)) {
                if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai3.Status == 1) {
                        trs[n] = Trsnilai3;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }
            fclose(ArsTrsNilai3);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
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
               trs[i].SkorWawancara,
               StatusSeleksi3[Trsnilai3.Status]);
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
            printf(" %-15s | %-15s | %-18s | %-10s ", "ID Pendaftaran", "ID Nilai 3",
                   "Nilai Wawancara", "Status");
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



