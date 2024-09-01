void InputNilai1();
void LihatPassingGrade();
void InputPsg1();
void InputPengumumanTahap1();
void LihatNilai1Keseluruhan();
void LihatNilai1TungguPengumuman();
void LihatNilai1LulusSeleksi();
void LihatNilai1TidakLulus();

void InputNilai1(){

    int ID_Camaba;
    bool found, found1, found2;
    int sukses = 0;

    // deklarasi nilai utbk
    float Lba; // Literasi Bahasa Indonesia
    float Lbi; // Literasi Bahasa Inggris
    float Pm; // Penalaran Matematika
    float Kpu; // Kemampuan Penalaran Umum
    float Pk; // Pengetahuan Kuantitatif
    float Pu; // Pengetahuan dan pemahaman Umum
    float Kbm; // Kemampuan memahami bacaan dan menulis

    // deklarasi Nilai Rapor
    float Mtk;
    float Bindo;
    float Binggris;
    float RtNilaiRapor;

    // deklarasi total & rata rata
    float total;
    float rata_rata;

    int ID;

    lihat:
    CleanTengah();
    CleanKanan();
    LihatFormulir2();

    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");

    SetColor(241);
    gotoxy(133,20); printf("  INPUT NILAI SELEKSI TAHAP 1");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Pendaftaran : FRM"); getnum(&ID, 2);

    SetColor(241);

    if(ID == 0){
        CleanTengah();
        CleanKanan();
        CleanKiri();
        CamabaMenu();
    }

    ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
    TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

    found = false;
    found1 = false;
    found2 = false;

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

    //jika formulir pendaftarannya dengan id camaba tersebut, maka lanjut
    if((found == true) && Trspendaftaran.StatusPendaftaran == 2){

        ArsTrsNilai1 = fopen("FileNilai1.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

        while(!feof(ArsTrsNilai1))
        {
            fread(&Trsnilai1, sizeof(Trsnilai1),1 , ArsTrsNilai1);
        }
        Trsnilai1.ID++;

        ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

        while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
            if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                found2 = true;
                break;
            }
        }

        Trsnilai1.ID_BayarForm = TrsbayarForm.ID;

        CleanTengah();
        CleanKanan();
        DesainData();

        gotoxy(66, 19);printf("===============================");
        gotoxy(66, 20);printf("|N|I|L|A|I| |S|E|L|E|K|S|I| |1|");
        gotoxy(66, 21);printf("===============================");

        gotoxy(60, 25); printf(" ID Pendaftaran         : FRM%.5d", Trspendaftaran.ID);
        gotoxy(60, 26); printf(" ID Transaksi Nilai 1   : TRSN%.5d", Trsnilai1.ID);
        gotoxy(60, 27); printf(" ID Camaba              : CMB%.5d", Trspendaftaran.ID_Camaba);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        Trsnilai1.TanggalInput.tgl = tm.tm_mday;
        Trsnilai1.TanggalInput.bulan = tm.tm_mon + 1;
        Trsnilai1.TanggalInput.tahun = tm.tm_year + 1900;

        gotoxy(60, 27); printf(" Tanggal Transaksi 1    : %.2d/%.2d/%.4d", Trsnilai1.TanggalInput.tgl, Trsnilai1.TanggalInput.bulan, Trsnilai1.TanggalInput.tahun);
        gotoxy(60, 37); printf(" Klik Apapun Untuk Lanjut");
        getch();

        inputnilai:
        CleanTengah();
        DesainData();

        gotoxy(66, 19);printf("===============================");
        gotoxy(66, 20);printf("|N|I|L|A|I| |S|E|L|E|K|S|I| |1|");
        gotoxy(66, 21);printf("===============================");

        // Memanggil Data Gelombang untuk melihat jalur
        ArsGelombang = fopen("FileGelombang.dat", "rb");
        TempGelombang = fopen("TempGelombang.dat", "wb");

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

        if(found1 == true){
            if(Mgelombang.ID_Jalur == 1){
                SetColor(244);
                gotoxy(60,37); printf(" Input Rentang Nilai yaitu 1 - 100");
                SetColor(241);

                gotoxy(60, 25); printf(" [SELEKSI NILAI RAPOR]");
                gotoxy(60, 26); printf(" =========================");
                gotoxy(60, 27); printf(" Matematika Wajib      : ");
                gotoxy(60, 28); printf(" Bahasa Indonesia      : ");
                gotoxy(60, 29); printf(" Bahasa Inggris        : ");
                gotoxy(60, 30); printf(" Rata-rata Nilai Rapor : ");

                gotoxy(85, 27);fflush(stdin); getnum1(&Mtk, 3);
                gotoxy(85, 28);fflush(stdin); getnum1(&Bindo, 3);
                gotoxy(85, 29);fflush(stdin); getnum1(&Binggris, 3);
                gotoxy(85, 30);fflush(stdin); getnum1(&RtNilaiRapor, 3);

                if(Mtk > 100 || Bindo > 100 || Binggris > 100 || RtNilaiRapor > 100 ){
                    MessageBox(NULL, "Rentang Nilai Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    goto inputnilai;
                }

                total = Mtk + Binggris + Bindo + RtNilaiRapor;
                rata_rata = ((5 * RtNilaiRapor / 10) + (5 * ((Mtk+Bindo+Binggris)/3)/10));

                Trsnilai1.Mtk = Mtk;
                Trsnilai1.Bindo = Bindo;
                Trsnilai1.Binggris = Binggris;
                Trsnilai1.total = total;
                Trsnilai1.rata_rata = rata_rata;

            }else if(Mgelombang.ID_Jalur == 2){

                gotoxy(60,41); printf(" Input Rentang Nilai yaitu 1 - 1000");
                SetColor(241);

                gotoxy(60, 25); printf(" [SELEKSI NILAI UTBK]");
                gotoxy(60, 26); printf(" =========================");
                gotoxy(60, 27); printf(" Literasi B.Indonesia       : ");
                gotoxy(60, 28); printf(" Literasi B.Inggris         : ");
                gotoxy(60, 29); printf(" Penalaran Matematika       : ");
                gotoxy(60, 30); printf(" Kemampuan Penalaran Umum   : ");
                gotoxy(60, 31); printf(" Pengetahuan Kuantitatif    : ");
                gotoxy(60, 32); printf(" Pengetahuan Umum           : ");
                gotoxy(60, 33); printf(" Kemampuan Pemahaman Bacaan : ");

                gotoxy(90, 27);fflush(stdin); getnum1(&Lba, 3);
                gotoxy(90, 28);fflush(stdin); getnum1(&Lbi, 3);
                gotoxy(90, 29);fflush(stdin); getnum1(&Pm, 3);
                gotoxy(90, 30);fflush(stdin); getnum1(&Kpu, 3);
                gotoxy(90, 31);fflush(stdin); getnum1(&Pk, 3);
                gotoxy(90, 32);fflush(stdin); getnum1(&Pu, 3);
                gotoxy(90, 33);fflush(stdin); getnum1(&Kbm, 3);

                if(Lba > 1000 || Lbi > 1000 || Pm > 1000 || Kpu > 1000 || Pk > 1000 || Pu > 1000 || Kbm > 1000 ){
                    MessageBox(NULL, "Rentang Nilai Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    goto inputnilai;
                }

                total = Lba + Lbi + Pm + Kpu + Pk + Pu + Kbm;
                rata_rata = total / 70;

                Trsnilai1.Lba = Lba;
                Trsnilai1.Lbi = Lbi;
                Trsnilai1.Pm = Pm;
                Trsnilai1.Kpu = Kpu;
                Trsnilai1.Pk = Pk;
                Trsnilai1.Pu = Pu;
                Trsnilai1.Kbm = Kbm;
                Trsnilai1.total = total;
                Trsnilai1.rata_rata = rata_rata;

            }
        }

        Trspendaftaran.StatusPendaftaran = 3;
        fwrite(&Trspendaftaran,sizeof(Trspendaftaran), 1, TempPendaftaran);

        Trsnilai1.Status = 0;
        fwrite(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
        fclose(ArsTrsNilai1);

        fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)){
            fwrite(&Trspendaftaran, sizeof (Trspendaftaran), 1, TempPendaftaran);
            fread(&Trspendaftaran, sizeof (Trspendaftaran), 1, ArsPendaftaran);
        }

        MessageBox(NULL, "Seleksi Tahap 1 Berhasil Dilaksanakan, Silahkan Cek Jadwal Psikotest pada SMS dan Cek Pengumuman secara Berkala!", "PEMBERITAHUAN", MB_OK | MB_ICONINFORMATION);
    }else if (found == false){
        MessageBox(NULL, "Data Formulir Tidak Tersedia !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        InputNilai1();
    }else if (found == true && Trspendaftaran.StatusPendaftaran == 0 || Trspendaftaran.StatusPendaftaran == 1){
        MessageBox(NULL, "Data Formulir ini belum Melakukan Pembayaran !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        InputNilai1();
    }else if (found == true && Trspendaftaran.StatusPendaftaran != 2){
        MessageBox(NULL, "Data Formulir ini telah terisi !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        CleanTengah();
        CleanKanan();
        InputNilai1();
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

void InputPsg1(){

    float psg1;
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
        gotoxy(60,33); printf(" Passing Grade 1 :   ");

        gotoxy(81,33); getnum1(&psg1, 2);

        if(psg1 > 100){
            MessageBox(NULL, "Rentang Nilai Passing Grade Tidak Sesuai Ketentuan !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto inputpsg;
        }

        Mprodi.psg1 = psg1;

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
        InputPsg1();
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
        InputPsg1();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }else {
        CleanKanan();
        CleanTengah();
        goto update;
    }
}

void InputPengumumanTahap1(){
    char kf;
    bool found1, found2, found3;

    pengumuman:
    CleanTengah();
    CleanKanan();
    LihatPassingGrade();

    found3 = false;

    gotoxy(133,20); printf("  KONFIRMASI PENGUMUMAN TAHAP 1");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Input Pengumuman? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);

    if (kf == 'y' || kf == 'Y') {

        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        while (!feof(ArsPendaftaran)) {

            if (Trspendaftaran.StatusPendaftaran == 3) {

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
                    ArsTrsNilai1 = fopen("FileNilai1.dat", "rb");
                    TempTrsNilai1 = fopen("TempNilai1.dat", "wb");

                    ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

                    while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
                        if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                            break;
                        }
                    }

                    while (fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1) == 1) {
                        if (Trsnilai1.ID_BayarForm == TrsbayarForm.ID) {
                            if (Trsnilai1.rata_rata > Mprodi.psg1) {
                                Trsnilai1.Status = 1;
                                Trspendaftaran.StatusPendaftaran = 4;
                                Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                            } else {
                                Trsnilai1.Status = 2;
                                Trspendaftaran.StatusPendaftaran = 12;
                                Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                            }
                        }
                        fwrite(&Trsnilai1, sizeof(Trsnilai1), 1, TempTrsNilai1);
                    }

                    // Tutup file yang sudah dibuka sebelumnya
                    fclose(ArsTrsNilai1);
                    fclose(TempTrsNilai1);

                    // Buka kembali file-file yang telah diolah
                    ArsTrsNilai1 = fopen("FileNilai1.dat", "wb");
                    TempTrsNilai1 = fopen("TempNilai1.dat", "rb");

                    // Salin isi file temporer ke file utama
                    while (fread(&Trsnilai1, sizeof(Trsnilai1), 1, TempTrsNilai1) == 1) {
                        fwrite(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
                    }

                    // Tutup file yang sudah selesai diproses
                    fclose(ArsTrsNilai1);
                    fclose(TempTrsNilai1);

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
            } else {
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

        MessageBox(NULL, "Pengumuman Tahap 1 Selesai di lakukan !!","INFORMASI", MB_OK | MB_ICONINFORMATION );

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

void LihatPassingGrade() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");

    // Jika Data Program Studi Kosong
    if (ArsProgramStudi == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Program Studi masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterProgramStudi();
    } else {

        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-10s | %-15s | %-10s | %-10s | %-10s | %-10s ","ID Prodi", "Nama Prodi", "Psg 1", "Psg2", "Psg 3", "Status");
        while (!feof(ArsProgramStudi)) {
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
            printf(" PRD%-7.5d | %-15s | %-10.2f | %-10.2f | %-10.2f | %-10s",
                   Mprodi.ID,
                   Mprodi.nama_singkat,
                   Mprodi.psg1,
                   Mprodi.psg2,
                   Mprodi.psg3,
                   StatusProdi[Mprodi.status]);
            SetColor(241);

            fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);

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
                gotoxy(Kolom, 16); printf(" %-15s | %-10s | %-10s | %-10s | %-10s ","Nama Prodi", "Psg 1", "Psg2", "Psg 3", "Status");
            }
        }
        fclose(ArsProgramStudi);
        SetColor(252);
    }
}

void LihatNilai1Keseluruhan() {

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
    printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
           "Rata-rata Nilai", "Status");

    // membuat array untuk tempat sorting
    TrsNilai1 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai1 = fopen("FileNilai1.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);

            while (!feof(ArsTrsNilai1)) {
                if (Trsnilai1.ID_BayarForm == TrsbayarForm.ID) {
                        trs[n] = Trsnilai1;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                }
                fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
            }
            fclose(ArsTrsNilai1);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].rata_rata < trs[j + 1].rata_rata) {
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
        printf(" FRM%-12.5d | TRSN%-11.5d | %12.2f | %15.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].total,
               trs[i].rata_rata,
               StatusSeleksi1[trs[i].Status]);
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
            printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
                   "Rata-rata Nilai", "Status");
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


void LihatNilai1TungguPengumuman() {

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
    printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
           "Rata-rata Nilai", "Status");

    // membuat array untuk tempat sorting
    TrsNilai1 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai1 = fopen("FileNilai1.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);

            while (!feof(ArsTrsNilai1)) {
                if (Trsnilai1.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai1.Status == 0) {
                        trs[n] = Trsnilai1;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
            }
            fclose(ArsTrsNilai1);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].rata_rata < trs[j + 1].rata_rata) {
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
        printf(" FRM%-12.5d | TRSN%-11.5d | %12.2f | %15.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].total,
               trs[i].rata_rata,
               StatusSeleksi1[Trsnilai1.Status]);
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
            printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
                   "Rata-rata Nilai", "Status");
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

void LihatNilai1LulusSeleksi() {

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
    printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
           "Rata-rata Nilai", "Status");

    // membuat array untuk tempat sorting
    TrsNilai1 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai1 = fopen("FileNilai1.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);

            while (!feof(ArsTrsNilai1)) {
                if (Trsnilai1.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai1.Status == 1) {
                        trs[n] = Trsnilai1;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
            }
            fclose(ArsTrsNilai1);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].rata_rata < trs[j + 1].rata_rata) {
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
        printf(" FRM%-12.5d | TRSN%-11.5d | %12.2f | %15.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].total,
               trs[i].rata_rata,
               StatusSeleksi1[Trsnilai1.Status]);
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
            printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
                   "Rata-rata Nilai", "Status");
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

void LihatNilai1TidakLulus() {

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
    printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
           "Rata-rata Nilai", "Status");

    // membuat array untuk tempat sorting
    TrsNilai1 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if (Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == MTahunAjar.ID) {

            ArsTrsNilai1 = fopen("FileNilai1.dat", "rb");

            ArsBayarFormulir = fopen("FileBayarFormulir.dat","rb");

            while(fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1) {
                if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                    break;
                }
            }

            fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);

            while (!feof(ArsTrsNilai1)) {
                if (Trsnilai1.ID_BayarForm == TrsbayarForm.ID) {
                    if(Trsnilai1.Status == 2) {
                        trs[n] = Trsnilai1;
                        n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                        break;
                    }
                }
                fread(&Trsnilai1, sizeof(Trsnilai1), 1, ArsTrsNilai1);
            }
            fclose(ArsTrsNilai1);
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }

    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].rata_rata < trs[j + 1].rata_rata) {
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
        printf(" FRM%-12.5d | TRSN%-11.5d | %12.2f | %15.2f | %-10s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].total,
               trs[i].rata_rata,
               StatusSeleksi1[Trsnilai1.Status]);
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
            printf(" %-15s | %-15s | %-12s | %-15s | %-10s ", "ID Pendaftaran", "ID Nilai 1", "Total Nilai",
                   "Rata-rata Nilai", "Status");
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
