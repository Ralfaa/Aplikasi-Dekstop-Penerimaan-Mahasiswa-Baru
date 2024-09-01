
void BikinAkunCamaba();
void UbahAkunCamaba();
void InfoAkun();
void IsiDataWali();
void IsiDataPribadi();
void IsiDataSekolah();
void AkunVaForm();
void LihatDataCamaba();
void DetailAkunCamaba();
void PengumumanCamaba();

void PengumumanCamaba(){

    CleanTengah();

    bool found;
    int ID_Akun; // menyimpan id akun camaba yang akan di ubah

    ID_Akun = Mcamaba.ID;

    ArsCamaba = fopen("FileCamaba.dat", "rb");

    found = false;

    fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    while((!found)&&(!feof(ArsCamaba)))
    {
        if(Mcamaba.ID == ID_Akun)
        {
            found = true;
            break;
        }
        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    }

    if (found == true){

        if(Mcamaba.StatusAkun == 0){
            MessageBox(NULL, "Akun anda saat ini tidak terdaftar seleksi, silahkan mendaftar di Gelombang yang tersedia !!!","PERINGATAN", MB_OK | MB_ICONWARNING );
        }else if(Mcamaba.StatusAkun == 1){
            MessageBox(NULL, "Saat ini anda sedang berada dalam proses seleksi, untuk lebih detail silahkan lihat pada info formulir !!","PERINGATAN", MB_OK | MB_ICONWARNING );
        } else if(Mcamaba.StatusAkun == 2){
            MessageBox(NULL, "Selamat anda telah lulus seleksi, silahkan melakukan pembayaran Ukt !!","PERINGATAN", MB_OK | MB_ICONWARNING );
        } else if (Mcamaba.StatusAkun == 3){
            MessageBox(NULL, "Selamat Anda Sudah Resmi Menjadi Mahasiswa Baru Politeknik Ralfahisnaf !!","PERINGATAN", MB_OK | MB_ICONWARNING );
        }
    }

    CamabaMenu();
}
void BikinAkunCamaba(){
    char username[15];
    char password[15];
    bool found;

    akuncamaba:
    system("cls"); // Untuk membersihkan terminal di sistem UNIX, ganti dengan "cls" untuk Windows
    DesainPembuatanAkun();
    found = false;

    gotoxy(73,19); printf("===================");
    gotoxy(73,20); printf("|B|U|A|T| |A|K|U|N|");
    gotoxy(73,21); printf("===================");

    ArsCamaba = fopen("FileCamaba.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsCamaba))
    {
        fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
    }
    Mcamaba.ID++;

    gotoxy(60,37); printf(" Ketik '0' untuk ke kembali");

    gotoxy(60,26); printf(" ID Camaba            : CMB%.5d",Mcamaba.ID);

    gotoxy(60,28); printf(" Username             : ");
    gotoxy(60,30); printf(" Password             : ");
    gotoxy(60,32); printf(" Konfirmasi Password  : ");

    gotoxy(84,28); fflush(stdin); getteks(username, 50);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (strcmp(username, "0")==0){
        CleanTengah();
        CleanKanan();
        selectLogin();
    }

    // Jika Nama Program Studi sudah ada, maka akan mengulang
    ArsCamaba1 = fopen("FileCamaba.dat", "rb");

    while (fread(&Mcamaba1, sizeof(Mcamaba1), 1, ArsCamaba1)==1)
    {
        if (strcmp(Mcamaba1.username, username)==0)
        {
            MessageBox(NULL, "Username Sudah ada, data tidak boleh sama"," perhatian",MB_OK);
            goto akuncamaba;
        }
    }
    fclose(ArsCamaba1);

    gotoxy(84,30); fflush(stdin); getpass(Mcamaba.password, 8);
    gotoxy(84,32); fflush(stdin); getpass(password, 8);

    if(strcmp(Mcamaba.password, password) != 0){
        MessageBox(NULL, "Password Anda Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
        goto akuncamaba;
    }

    // jika username tidak sama, dan pw nya sama maka bisa lanjut
    ArsCamaba = fopen("FileCamaba.dat", "ab+");
    strcpy(Mcamaba.username, username);

    system("cls");

    DesainPembuatanAkun();
    IsiDataPribadi();
    IsiDataWali();
    IsiDataSekolah();

    Mcamaba.StatusAkun = 0;
    fwrite(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    fclose(ArsCamaba);

    system("cls");
    selectLogin();
}

void IsiDataWali(){

    CleanTengah();
    DesainPembuatanAkun();

    gotoxy(70,19); printf("=============================");
    gotoxy(70,20); printf("|D|A|T|A| |D|I|R|I| |W|A|L|I|");
    gotoxy(70,21); printf("=============================");

    gotoxy(60,26); printf(" Nama Lengkap       : ");
    gotoxy(60,27); printf(" Pekerjaan          : ");
    gotoxy(60,28); printf(" Gaji               : ");
    gotoxy(60,29); printf(" No Telepon         : ");
    gotoxy(60,30); printf(" NIK                : ");
    gotoxy(60,31); printf(" Hubungan Keluarga  : ");

    gotoxy(83,26); fflush(stdin); getteks(Mcamaba.nama_wali, 50);
    gotoxy(83,27); fflush(stdin); getteks(Mcamaba.pekerjaan_wali, 50);
    gotoxy(83,28); fflush(stdin); getteksnum(Mcamaba.gaji_wali, 50);
    gotoxy(83,29); fflush(stdin); getteksnum(Mcamaba.no_telepon_wali, 13);
    gotoxy(83,30); fflush(stdin); getteksnum(Mcamaba.nik_wali, 17);
    gotoxy(83,31); fflush(stdin); getteks(Mcamaba.hubungan_keluarga, 50);

}

void IsiDataSekolah(){

    CleanTengah();
    DesainPembuatanAkun();

    gotoxy(70,19); printf("===================================");
    gotoxy(70,20); printf("|D|A|T|A| |A|S|A|L| |S|E|K|O|L|A|H|");
    gotoxy(70,21); printf("===================================");

    gotoxy(60,26); printf(" Nama Sekolah Asal  : ");
    gotoxy(60,27); printf(" Alamat             : ");
    gotoxy(60,28); printf(" Kode Pos           : ");
    gotoxy(60,29); printf(" Akreditasi         : ");
    gotoxy(60,30); printf(" Jurusan Asal       : ");

    gotoxy(83,26); fflush(stdin); getteks(Mcamaba.namaSekolah, 50);
    gotoxy(83,27); fflush(stdin); getteks(Mcamaba.AlamatSekolah, 50);
    gotoxy(83,28); fflush(stdin); getteksnum(Mcamaba.KodePosSekolah, 5);
    gotoxy(83,29); fflush(stdin); getteks(Mcamaba.AkreSekolah, 2);
    gotoxy(83,30); fflush(stdin); getteks(Mcamaba.JurusanSekolah, 50);
}

void IsiDataPribadi() {

    bool found;
    buatakun:
    found = false;
    CleanTengah();
    DesainPembuatanAkun();

    gotoxy(67,19); printf("===================================");
    gotoxy(67,20); printf("|D|A|T|A| |D|I|R|I| |P|R|I|B|A|D|I|");
    gotoxy(67,21); printf("===================================");

    gotoxy(60,25); printf(" ID Camaba             : CMB%.5d",Mcamaba.ID);
    gotoxy(60,26); printf(" Nama Lengkap          : ");
    gotoxy(60,27); printf(" NIK                   : ");
    gotoxy(60,28); printf(" Tempat Lahir          : ");
    gotoxy(60,29); printf(" Tanggal Lahir         : ");
    gotoxy(60,30); printf(" Agama                 : ");
    gotoxy(60,31); printf(" Jenis Kelamin (P/L)   : ");
    gotoxy(60,32); printf(" Golongan Darah        : ");
    gotoxy(60,33); printf(" No Telepon            : ");
    gotoxy(60,34); printf(" Asal Daerah           : ");

    gotoxy(85,26); fflush(stdin); getteks(Mcamaba.nama_lengkap, 50);
    gotoxy(85,27); fflush(stdin); getteksnum(Mcamaba.nik, 16);
    gotoxy(85,28); fflush(stdin); getteks(Mcamaba.tempatLahir, 50);

    gotoxy(85,29); fflush(stdin);getnum(&Mcamaba.tanggalLahir.tgl, 2); printf(" / ");
    getnum(&Mcamaba.tanggalLahir.bulan, 2); printf(" / ");
    getnum(&Mcamaba.tanggalLahir.tahun, 4);
    if(datevalid(Mcamaba.tanggalLahir)){
        found = true;
    }
    if (!found){
        MessageBox(0, "Tanggal Lahir Tidak Teridentifikasi", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
        goto buatakun;
    }

    gotoxy(85,30); fflush(stdin); getteks(Mcamaba.agama, 50);
    gotoxy(85,31); fflush(stdin); getteks(Mcamaba.gender, 1);
    gotoxy(85,32); fflush(stdin); getteks(Mcamaba.goldar, 3);
    gotoxy(85,33); fflush(stdin); getteksnum(Mcamaba.no_telepon, 12);
    gotoxy(85,34); fflush(stdin); getteks(Mcamaba.asal_daerah, 50);

}

void InfoAkun(){

    CleanTengah();

    DesainData();
    gotoxy(75,19); printf("==================");
    gotoxy(75,20); printf("|I|N|FO| |A|K|U|N|");
    gotoxy(75,21); printf("==================");
    gotoxy(60,26); printf(" ID Pendaftaran  : PRD%.3d",Mcamaba.ID);
    gotoxy(60,27); printf(" Username        : %s",Mcamaba.username);
    gotoxy(60,28); printf(" Password        : %s",Mcamaba.password);

    gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
    getch();

    CleanTengah();
    DesainData();
    gotoxy(75,19); printf("===================");
    gotoxy(75,20); printf("|D|A|T|A| |D|I|R|I|");
    gotoxy(75,21); printf("===================");
    gotoxy(60,26); printf(" ID Camaba       : CMB%.5d",Mcamaba.ID);
    gotoxy(60,27); printf(" Nama Lengkap    : %s",Mcamaba.nama_lengkap);
    gotoxy(60,28); printf(" NIK             : %s",Mcamaba.nik);
    gotoxy(60,29); printf(" Tempat Lahir    : %s",Mcamaba.tempatLahir);
    gotoxy(60,30); printf(" Tanggal Lahir   : %.2d-%.2d-%.4d",Mcamaba.tanggalLahir.tgl, Mcamaba.tanggalLahir.bulan, Mcamaba.tanggalLahir.tahun);
    gotoxy(60,31); printf(" Agama           : %s",Mcamaba.agama);
    gotoxy(60,32); printf(" Jenis Kelamin   : %s",Mcamaba.gender);
    gotoxy(60,33); printf(" Golongan Darah  : %s",Mcamaba.goldar);
    gotoxy(60,34); printf(" No Telepon      : %s",Mcamaba.no_telepon);
    gotoxy(60,35); printf(" Asal Daerah     : %s",Mcamaba.asal_daerah);

    gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
    getch();

    CleanTengah();
    DesainData();
    gotoxy(75,19); printf("===================");
    gotoxy(75,20); printf("|D|A|T|A| |W|A|L|I|");
    gotoxy(75,21); printf("===================");

    gotoxy(60,26); printf(" Nama Lengkap       : %s", Mcamaba.nama_wali);
    gotoxy(60,27); printf(" Pekerjaan          : %s", Mcamaba.pekerjaan_wali);
    gotoxy(60,28); printf(" Gaji               : %s", Mcamaba.gaji_wali);
    gotoxy(60,29); printf(" No Telepon         : %s", Mcamaba.no_telepon_wali);
    gotoxy(60,30); printf(" NIK                : %s", Mcamaba.nik_wali);
    gotoxy(60,31); printf(" Hubungan Keluarga  : %s", Mcamaba.hubungan_keluarga);

    gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
    getch();

    CleanTengah();
    DesainData();
    gotoxy(66,19); printf("===================================");
    gotoxy(66,20); printf("|D|A|T|A| |A|S|A|L| |S|E|K|O|L|A|H|");
    gotoxy(66,21); printf("===================================");

    gotoxy(60,26); printf(" Nama Sekolah Asal  : %s", Mcamaba.namaSekolah);
    gotoxy(60,27); printf(" Alamat             : %s", Mcamaba.AlamatSekolah);
    gotoxy(60,28); printf(" Kode Pos           : %s", Mcamaba.KodePosSekolah);
    gotoxy(60,29); printf(" Akreditasi         : %s", Mcamaba.AkreSekolah);
    gotoxy(60,30); printf(" Jurusan Asal       : %s", Mcamaba.JurusanSekolah);


    gotoxy(60,37); printf(" Klik Apapun Untuk Lanjut");
    getch();

    CleanTengah();

    CamabaMenu();

}


void UbahAkunCamaba(){

    bool found;
    bool found1;
    int pilihan;
    int pilihan1;
    int sukses = 0;
    int ID_Akun; // menyimpan id akun camaba yang akan di ubah

    ID_Akun = Mcamaba.ID;

    ArsCamaba = fopen("FileCamaba.dat", "rb");
    TempCamaba = fopen("TempCamaba.dat", "wb");

    found = false;

    fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    while((!found) && (!feof(ArsCamaba)))
    {
        if(Mcamaba.ID == ID_Akun) {
            found = true;
            break;
        } else {
            fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
        }
        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    }

    if (found == true && Mcamaba.StatusAkun == 0){
        update:

        CleanTengah();
        DesainData();

        gotoxy(65,19); printf("===========================");
        gotoxy(65,20); printf("|P|E|R|B|A|R|U|I| |D|A|T|A|");
        gotoxy(65,21); printf("===========================");

        gotoxy(60,26); printf(" Data Apa yang ingin diubah?");
        gotoxy(60,28); printf(" [1] Data Diri Pribadi");
        gotoxy(60,29); printf(" [2] Data Diri Wali");
        gotoxy(60,30); printf(" [3] Data Asal Sekolah");
        gotoxy(60,31); printf(" [4] Kembali");
        gotoxy(60,33); printf(" Pilih = [ ]");
        gotoxy(70,33); fflush(stdin); getnum(&pilihan, 9);

        switch (pilihan) {
            case 1:
                buatakun:
                found1 = false;
                CleanTengah();
                DesainData();

                gotoxy(75,19); printf("===================");
                gotoxy(75,20); printf("|D|A|T|A| |D|I|R|I|");
                gotoxy(75,21); printf("===================");
                gotoxy(60,26); printf(" ID Camaba       : CMB%.5d",Mcamaba.ID);
                gotoxy(60,27); printf(" Nama Lengkap    : %s",Mcamaba.nama_lengkap);
                gotoxy(60,28); printf(" NIK             : %s",Mcamaba.nik);
                gotoxy(60,29); printf(" Tempat Lahir    : %s",Mcamaba.tempatLahir);
                gotoxy(60,30); printf(" Tanggal Lahir   : %.2d-%.2d-%.4d",Mcamaba.tanggalLahir.tgl, Mcamaba.tanggalLahir.bulan, Mcamaba.tanggalLahir.tahun);
                gotoxy(60,31); printf(" Agama           : %s",Mcamaba.agama);
                gotoxy(60,32); printf(" Jenis Kelamin   : %s",Mcamaba.gender);
                gotoxy(60,33); printf(" Golongan Darah  : %s",Mcamaba.goldar);
                gotoxy(60,34); printf(" No Telepon      : %s",Mcamaba.no_telepon);
                gotoxy(60,35); printf(" Asal Daerah     : %s",Mcamaba.asal_daerah);

                gotoxy(133,20); printf("  Pilih Update Data");
                gotoxy(133,22); printf("  [1] Tempat Lahir");
                gotoxy(133,23); printf("  [2] Tanggal Lahir");
                gotoxy(133,24); printf("  [3] Agama ");
                gotoxy(133,25); printf("  [4] Jenis Kelamin");
                gotoxy(133,26); printf("  [5] Golongan Darah");
                gotoxy(133,27); printf("  [6] No Telepon");
                gotoxy(133,28); printf("  [7] Asal Daerah");
                gotoxy(133,29); printf("  [8] Kembali");
                gotoxy(133,31); printf("  Pilihan = [ ]");
                gotoxy(146,31); getnum(&pilihan1, 1);
                fflush(stdin);

                gotoxy(133,33); printf("  =======================");
                gotoxy(133,34); printf("  MASUKKAN DATA UPDATE !!");
                switch (pilihan1) {
                    case 1:
                        gotoxy(133,36);	printf("  Tempat Lahir  ");
                        gotoxy(133,37);	printf("  ============  ");
                        gotoxy(135,38); fflush(stdin); getteks(Mcamaba1.tempatLahir, 50);

                        strcpy(Mcamaba.tempatLahir, Mcamaba1.tempatLahir);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 2:
                        gotoxy(133,36);	printf("  Tanggal Lahir  ");
                        gotoxy(133,37);	printf("  =============  ");

                        gotoxy(135,38); fflush(stdin);getnum(&Mcamaba1.tanggalLahir.tgl, 2); printf(" / ");
                        getnum(&Mcamaba1.tanggalLahir.bulan, 2); printf(" / ");
                        getnum(&Mcamaba1.tanggalLahir.tahun, 4);
                        if(datevalid(Mcamaba1.tanggalLahir)){
                            found1 = true;
                        }
                        if (!found1){
                            MessageBox(0, "Tanggal Lahir Tidak Teridentifikasi", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
                            goto buatakun;
                        }

                        Mcamaba.tanggalLahir.tgl = Mcamaba1.tanggalLahir.tgl;
                        Mcamaba.tanggalLahir.bulan = Mcamaba1.tanggalLahir.bulan;
                        Mcamaba.tanggalLahir.tahun = Mcamaba1.tanggalLahir.tahun;
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 3:
                        gotoxy(133,36);	printf("  Agama  ");
                        gotoxy(133,37);	printf("  ===== ");
                        gotoxy(135,38); fflush(stdin); getteks(Mcamaba1.agama, 50);
                        strcpy(Mcamaba.agama, Mcamaba1.agama);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 4:
                        gotoxy(133,36);	printf("  Jenis Kelamin  ");
                        gotoxy(133,37);	printf("  ============= ");
                        gotoxy(135,38); fflush(stdin); getteks(Mcamaba1.gender, 1);
                        strcpy(Mcamaba.gender, Mcamaba1.gender);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 5:
                        gotoxy(133,36);	printf("  Jenis Kelamin  ");
                        gotoxy(133,37);	printf("  ============= ");
                        gotoxy(135,38); fflush(stdin); getteks(Mcamaba1.goldar, 2);
                        strcpy(Mcamaba.goldar, Mcamaba1.goldar);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 6:
                        gotoxy(133,36);	printf("  No Telepon  ");
                        gotoxy(133,37);	printf("  ========== ");
                        gotoxy(135,38); fflush(stdin); getteksnum(Mcamaba1.no_telepon, 12);
                        strcpy(Mcamaba.no_telepon, Mcamaba1.no_telepon);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 7:
                        gotoxy(133,36);	printf("  Asal Daerah  ");
                        gotoxy(133,37);	printf("  ===========  ");
                        gotoxy(135,38); fflush(stdin); getteks(Mcamaba1.asal_daerah, 50);
                        strcpy(Mcamaba.asal_daerah, Mcamaba1.asal_daerah);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 8:
                        UbahAkunCamaba();
                        break;
                    default:
                        MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        goto update;
                }
                fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                break;
            case 2:

                CleanTengah();
                DesainData();

                gotoxy(75,19); printf("===================");
                gotoxy(75,20); printf("|D|A|T|A| |W|A|L|I|");
                gotoxy(75,21); printf("===================");

                gotoxy(60, 26); printf(" Nama Lengkap       : %s", Mcamaba.nama_wali);
                gotoxy(60, 27); printf(" Pekerjaan          : %s", Mcamaba.pekerjaan_wali);
                gotoxy(60, 28); printf(" Gaji               : %s", Mcamaba.gaji_wali);
                gotoxy(60, 29); printf(" No Telepon         : %s", Mcamaba.no_telepon_wali);
                gotoxy(60, 30); printf(" NIK                : %s", Mcamaba.nik_wali);
                gotoxy(60, 31); printf(" Hubungan Keluarga  : %s", Mcamaba.hubungan_keluarga);

                gotoxy(133,20); printf("  Pilih Update Data");
                gotoxy(133,22); printf("  [1] Nama Lengkap");
                gotoxy(133,23); printf("  [2] Pekerjaan");
                gotoxy(133,24); printf("  [3] Gaji ");
                gotoxy(133,25); printf("  [4] No Telepon");
                gotoxy(133,26); printf("  [5] NIK");
                gotoxy(133,27); printf("  [6] Hubungan Keluarga");
                gotoxy(133,28); printf("  [7] Kembali");

                gotoxy(133,30); printf("  Pilihan = [ ]");
                gotoxy(146,30); getnum(&pilihan1, 1);
                fflush(stdin);

                gotoxy(133,32); printf("  =======================");
                gotoxy(133,32); printf("  MASUKKAN DATA UPDATE !!");

                switch (pilihan1) {
                    case 1:
                        gotoxy(133,34);	printf("  Nama Lengkap  ");
                        gotoxy(133,35);	printf("  ============  ");
                        gotoxy(135,36); fflush(stdin); getteks(Mcamaba1.nama_wali, 50);
                        strcpy(Mcamaba.nama_wali, Mcamaba1.nama_wali);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 2:
                        gotoxy(133,34);	printf("  Pekerjaan  ");
                        gotoxy(133,35);	printf("  =========  ");
                        gotoxy(135,36); fflush(stdin); getteks(Mcamaba1.pekerjaan_wali, 50);
                        strcpy(Mcamaba.pekerjaan_wali, Mcamaba1.pekerjaan_wali);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 3:
                        gotoxy(133,34);	printf("  Gaji  ");
                        gotoxy(133,35);	printf("  ====  ");
                        gotoxy(135,36); fflush(stdin); getteksnum(Mcamaba1.gaji_wali, 50);
                        strcpy(Mcamaba.gaji_wali, Mcamaba1.gaji_wali);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 4:
                        gotoxy(133,34);	printf("  No Telepon  ");
                        gotoxy(133,35);	printf("  ==========  ");
                        gotoxy(135,36); fflush(stdin); getteksnum(Mcamaba1.no_telepon_wali, 13);
                        strcpy(Mcamaba.no_telepon_wali, Mcamaba1.no_telepon_wali);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 5:
                        gotoxy(133,34);	printf("  NIK  ");
                        gotoxy(133,35);	printf("  ===  ");
                        gotoxy(135,36); fflush(stdin); getteksnum(Mcamaba1.nik_wali, 17);
                        strcpy(Mcamaba.nik_wali, Mcamaba1.nik_wali);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 6:
                        gotoxy(133,34);	printf("  Hubungan Keluarga  ");
                        gotoxy(133,35);	printf("  =================  ");
                        gotoxy(135,36); fflush(stdin); getteks(Mcamaba1.hubungan_keluarga, 50);
                        strcpy(Mcamaba.hubungan_keluarga, Mcamaba1.hubungan_keluarga);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 7:
                        UbahAkunCamaba();
                        break;
                    default:
                        MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        goto update;
                }
                fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                break;
            case 3:

                CleanTengah();
                DesainData();

                gotoxy(66,19); printf("===================================");
                gotoxy(66,20); printf("|D|A|T|A| |A|S|A|L| |S|E|K|O|L|A|H|");
                gotoxy(66,21); printf("===================================");

                gotoxy(60, 26); printf(" Nama Sekolah Asal  : %s", Mcamaba.namaSekolah);
                gotoxy(60, 27); printf(" Alamat             : %s", Mcamaba.AlamatSekolah);
                gotoxy(60, 28); printf(" Kode Pos           : %s", Mcamaba.KodePosSekolah);
                gotoxy(60, 29); printf(" Akreditasi         : %s", Mcamaba.AkreSekolah);
                gotoxy(60, 30); printf(" Jurusan Asal       : %s", Mcamaba.JurusanSekolah);

                gotoxy(133,20); printf("  Pilih Update Data");
                gotoxy(133,22); printf("  [1] Nama Sekolah Asal");
                gotoxy(133,23); printf("  [2] Alamat");
                gotoxy(133,24); printf("  [3] Kode Pos");
                gotoxy(133,25); printf("  [4] Akreditasi");
                gotoxy(133,26); printf("  [5] Jurusan Asal");
                gotoxy(133,27); printf("  [6] Kembali");

                gotoxy(133,29); printf("  Pilihan = [ ]");
                gotoxy(146,29); getnum(&pilihan1, 1);
                fflush(stdin);

                gotoxy(133,31); printf("  =======================");
                gotoxy(133,31); printf("  MASUKKAN DATA UPDATE !!");

                switch (pilihan1) {
                    case 1:
                        gotoxy(133,33);	printf("  Nama Sekolah Asal  ");
                        gotoxy(133,34);	printf("  =================  ");
                        gotoxy(135,35); fflush(stdin); getteks(Mcamaba1.namaSekolah, 50);
                        strcpy(Mcamaba.namaSekolah, Mcamaba1.namaSekolah);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 2:
                        gotoxy(133,33);	printf("  Alamat Sekolah  ");
                        gotoxy(133,34);	printf("  ==============  ");
                        gotoxy(135,35); fflush(stdin); getteks(Mcamaba1.AlamatSekolah, 50);
                        strcpy(Mcamaba.AlamatSekolah, Mcamaba1.AlamatSekolah);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 3:
                        gotoxy(133,33);	printf("  Kode Pos Sekolah  ");
                        gotoxy(133,34);	printf("  ================  ");
                        gotoxy(135,35); fflush(stdin); getteksnum(Mcamaba1.KodePosSekolah, 6);
                        strcpy(Mcamaba.KodePosSekolah, Mcamaba1.KodePosSekolah);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 4:
                        gotoxy(133,33);	printf("  Akreditasi Sekolah  ");
                        gotoxy(133,34);	printf("  ==================  ");
                        gotoxy(135,35); fflush(stdin); getteks(Mcamaba1.AkreSekolah, 2);
                        strcpy(Mcamaba.AkreSekolah, Mcamaba1.AkreSekolah);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 5:
                        gotoxy(133,33);	printf("  Jurusan Asal  ");
                        gotoxy(133,34);	printf("  ============  ");
                        gotoxy(135,35); fflush(stdin); getteks(Mcamaba1.JurusanSekolah, 50);
                        strcpy(Mcamaba.JurusanSekolah, Mcamaba1.JurusanSekolah);
                        fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                        break;
                    case 6:
                        UbahAkunCamaba();
                        break;
                    default:
                        MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        goto update;

                }
                fwrite(&Mcamaba, sizeof(Mcamaba), 1, TempCamaba);
                break;
            case 4:
                CamabaMenu();
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                goto update;
        }

        fread(&Mcamaba, sizeof (Mcamaba), 1, ArsCamaba);
        while (!feof(ArsCamaba)){
            fwrite(&Mcamaba, sizeof (Mcamaba), 1, TempCamaba);
            fread(&Mcamaba, sizeof (Mcamaba), 1, ArsCamaba);
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

        system("cls");
        MessageBox(NULL, "Pembaruan Data Berhasil!","PERINGATAN", MB_OK | MB_ICONWARNING );

    }else{
        system("cls");
        MessageBox(NULL, "Anda Tidak Bisa Perbarui Data, Karena Sedang Melakukan Seleksi!","PERINGATAN", MB_OK | MB_ICONWARNING );
    }

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
        gotoxy(2,10); printf("SELAMAT DATANG......");
        gotoxy(2,11); printf("CALON MAHASISWA BARU");
        gotoxy(2,12); puts(Mcamaba.nama_lengkap);
        CamabaMenu();
    }
}

void LihatDataCamaba(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    int laki_laki =0;
    int perempuan = 0;
    bool found;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsCamaba = fopen("FileCamaba.dat", "rb");

    // Jika Data Gelombang Kosong
    if (ArsCamaba == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Calon Mahasiswa Baru masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        AdminMenu();
    }else {
        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16);
        printf(" %-10s | %-25s | %-15s | %-25s ", "ID Camaba", "Nama", "Jenis Kelamin", "Status");
        while (!feof(ArsCamaba)) {
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
            printf(" CMB%-7.5d | %-25s | %-15s | %-25s",
                   Mcamaba.ID,
                   Mcamaba.nama_lengkap,
                   Mcamaba.gender,
                   StatusAkun[Mcamaba.StatusAkun]);
            SetColor(241);

            if((strcmp(Mcamaba.gender, "P")==0)|| (strcmp(Mcamaba.gender, "p")==0)){
                perempuan++;
            }else if ((strcmp(Mcamaba.gender, "L")==0) || (strcmp(Mcamaba.gender, "l")==0)){
                laki_laki++;
            }


            fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);

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
                gotoxy(Kolom, 16);
                printf(" %-10s | %-25s | %-15s | %-25s ", "ID Camaba", "Nama", "Jenis Kelamin", "Status");
            }
        }
        fclose(ArsCamaba);
        SetColor(252);
    }

    gotoxy(133, 25); printf("  Laki-laki = %d", laki_laki);
    gotoxy(133, 26); printf("  Perempuan = %d", perempuan);
}

void DetailAkunCamaba(){

    boolean found;
    char kf;
    int ID;

    LihatDataCamaba();

    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  LIHAT AKUN CAMABA");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Camaba : CMB"); getnum(&ID, 5);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        AdminMenu();
    }

    ArsCamaba = fopen("FileCamaba.dat","rb");

    found = false;

    fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    while((!found)&&(!feof(ArsCamaba)))
    {
        if(Mcamaba.ID == ID)
        {
            found = true;
            break;
        }
        fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba);
    }

    if(found == true) {
        CleanTengah();
        DesainData();
        gotoxy(70, 19);
        printf("==================");
        gotoxy(70, 20);
        printf("|I|N|FO| |A|K|U|N|");
        gotoxy(70, 21);
        printf("==================");
        gotoxy(60, 26);
        printf(" ID Camaba       : CMB%.5d", Mcamaba.ID);
        gotoxy(60, 27);
        printf(" Username        : %s", Mcamaba.username);
        gotoxy(60, 28);
        printf(" Password        : %s", Mcamaba.password);

        gotoxy(60, 37);
        printf(" Klik Apapun Untuk Lanjut");
        getch();

        CleanTengah();
        DesainData();
        gotoxy(70, 19);
        printf("===================");
        gotoxy(70, 20);
        printf("|D|A|T|A| |D|I|R|I|");
        gotoxy(70, 21);
        printf("===================");
        gotoxy(60, 26);
        printf(" ID Camaba       : CMB%.5d", Mcamaba.ID);
        gotoxy(60, 27);
        printf(" Nama Lengkap    : %s", Mcamaba.nama_lengkap);
        gotoxy(60, 28);
        printf(" NIK             : %s", Mcamaba.nik);
        gotoxy(60, 29);
        printf(" Tempat Lahir    : %s", Mcamaba.tempatLahir);
        gotoxy(60, 30);
        printf(" Tanggal Lahir   : %.2d-%.2d-%.4d", Mcamaba.tanggalLahir.tgl, Mcamaba.tanggalLahir.bulan,
               Mcamaba.tanggalLahir.tahun);
        gotoxy(60, 31);
        printf(" Agama           : %s", Mcamaba.agama);
        gotoxy(60, 32);
        printf(" Jenis Kelamin   : %s", Mcamaba.gender);
        gotoxy(60, 33);
        printf(" Golongan Darah  : %s", Mcamaba.goldar);
        gotoxy(60, 34);
        printf(" No Telepon      : %s", Mcamaba.no_telepon);
        gotoxy(60, 35);
        printf(" Asal Daerah     : %s", Mcamaba.asal_daerah);

        gotoxy(60, 37);
        printf(" Klik Apapun Untuk Lanjut");
        getch();

        CleanTengah();
        DesainData();
        gotoxy(70, 19);
        printf("===================");
        gotoxy(70, 20);
        printf("|D|A|T|A| |W|A|L|I|");
        gotoxy(70, 21);
        printf("===================");

        gotoxy(60, 26);
        printf(" Nama Lengkap       : %s", Mcamaba.nama_wali);
        gotoxy(60, 27);
        printf(" Pekerjaan          : %s", Mcamaba.pekerjaan_wali);
        gotoxy(60, 28);
        printf(" Gaji               : %s", Mcamaba.gaji_wali);
        gotoxy(60, 29);
        printf(" No Telepon         : %s", Mcamaba.no_telepon_wali);
        gotoxy(60, 30);
        printf(" NIK                : %s", Mcamaba.nik_wali);
        gotoxy(60, 31);
        printf(" Hubungan Keluarga  : %s", Mcamaba.hubungan_keluarga);

        gotoxy(60, 37);
        printf(" Klik Apapun Untuk Lanjut");
        getch();

        CleanTengah();
        DesainData();
        gotoxy(70, 19);
        printf("===================================");
        gotoxy(70, 20);
        printf("|D|A|T|A| |A|S|A|L| |S|E|K|O|L|A|H|");
        gotoxy(70, 21);
        printf("===================================");

        gotoxy(60, 26);
        printf(" Nama Sekolah Asal  : %s", Mcamaba.namaSekolah);
        gotoxy(60, 27);
        printf(" Alamat             : %s", Mcamaba.AlamatSekolah);
        gotoxy(60, 28);
        printf(" Kode Pos           : %s", Mcamaba.KodePosSekolah);
        gotoxy(60, 29);
        printf(" Akreditasi         : %s", Mcamaba.AkreSekolah);
        gotoxy(60, 30);
        printf(" Jurusan Asal       : %s", Mcamaba.JurusanSekolah);

        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
        fclose(ArsCamaba);
    }else {
        MessageBox(NULL, "ID Camaba tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(133,22); printf("               ");
        CleanKanan();
    }

    carilagi:

    CleanKanan();
    gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin cari lagi? [Y/N] = [ ]");
    gotoxy(161, 22);getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y')
    {
        CleanKanan();
        DetailAkunCamaba();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        AdminMenu();
    }
    else
    {
        CleanKanan();
        CleanTengah();
        goto carilagi;
    }
}

