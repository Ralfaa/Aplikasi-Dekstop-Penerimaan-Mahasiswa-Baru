void LoginAkun();
void LoginCamaba();
void selectLogin();
void LoginInput();

// Deklarasi
char username[20], password[10];

void selectLogin(){

    login:
    // Algoritma
    DesainSelectLogin();

    // Ambil pilihan dari pengguna
    int pilihan;
    gotoxy(48, 39);printf("=========================");
    gotoxy(48, 40);printf("Pilih menu (1-4) = [ ]");
    gotoxy(68, 40); getnum(&pilihan, 1);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (pilihan == 0){
        system("cls");
        return;
    }
    char *audioFile = "Terima kasih telah menggunakan aplikasi ini, sampai jumpa kembali .wav";

    // Berdasarkan pilihan, lakukan aksi yang sesuai
    switch (pilihan) {
        case 1:
            LoginAkun();
            break;
        case 2:
            LoginCamaba();
            break;
        case 3:
            BikinAkunCamaba();
            break;
        case 4:
            sound(audioFile);
            MessageBox(NULL, "Terima Kasih Telah Menggunakan Aplikasi Ini...","Sistem Penerimaan Mahasiswa Baru",MB_OK | MB_ICONINFORMATION);
            exit(0);
        default:
            // Tambahkan pesan jika pilihan tidak valid
            MessageBox(NULL, "Inputan Tidak Valid","PERINGATAN", MB_OK | MB_ICONWARNING );
            goto login;
            break;
    }
}

void LoginAkun(){

    // Deklarasi
    int sukses = 0;

    // Algoritma
    DesainLoginKaryawan();

    gotoxy(84,41); printf("Ketik '0' untuk ke kembali");
    SetColor(241);

    gotoxy(85,33); printf("        		  ");
    gotoxy(85,38); printf("			      ");
    gotoxy(85,33); printf(" "); fflush(stdin); getteks(username,20);
    gotoxy(85,38); printf(" "); fflush(stdin); getpass(password,20);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if ((strcmp(username, "0")==0) || (strcmp(password, "0")==0)){
        system("cls");
        selectLogin();
    }

    ArsKaryawan = fopen("FileKaryawan.dat", "rb");

    // Cari Username dan Password

    fread(&Mkaryawan, sizeof(Mkaryawan),1 , ArsKaryawan);
    while(!feof(ArsKaryawan))
    {
        if((strcmp(Mkaryawan.Username,username)==0) && (strcmp(Mkaryawan.Password,password)==0))
        {
            if (Mkaryawan.ID_Jabatan==1)
            {

                MessageBox(NULL, "Selamat datang Bapak/Ibu Finance Committe!","Sistem Penerimaan Mahasiswa Baru",MB_OK | MB_ICONINFORMATION);
                sukses=1;
                char *audioFile1 = "Selamat datang Bapak_Ibu Finance Committe!.wav";
                sound(audioFile1);
                break;
            }
            else if (Mkaryawan.ID_Jabatan==2)
            {
                MessageBox(NULL, "Selamat datang Bapak/Ibu Admissions Committee!","Sistem Penerimaan Mahasiswa Baru",MB_OK | MB_ICONINFORMATION);
                sukses=2;
                char *audioFile2 = "Selamat datang Bapak_Ibu Admissions Committee!.wav";
                sound(audioFile2);
                break;
            }else if (Mkaryawan.ID_Jabatan==3)
            {
                MessageBox(NULL, "Selamat datang Bapak/Ibu Academic Committee!","Sistem Penerimaan Mahasiswa Baru",MB_OK | MB_ICONINFORMATION);
                sukses=3;
                char *audioFile3 = "Selamat datang Bapak_Ibu Academic Committee!.wav";
                sound(audioFile3);
                break;
            }else if (Mkaryawan.ID_Jabatan==4)
            {
                MessageBox(NULL, "Selamat datang Bapak/Ibu Assessment Committee!","Sistem Penerimaan Mahasiswa Baru",MB_OK | MB_ICONINFORMATION);
                sukses=4;
                char *audioFile4 = "Selamat datang Bapak_Ibu Assessment Committee!.wav";
                sound(audioFile4);
                break;
            }
        }
        fread(&Mkaryawan, sizeof(Mkaryawan),1 , ArsKaryawan);
    }

    if  (sukses == 1){
        system("cls");
        gotoxy(8,10); printf("[FINANCE COMMITTEE]");
        gotoxy(11,12); puts(Mkaryawan.Nama);
        FinanceMenu();
    } else if  (sukses == 2){
        system("cls");
        gotoxy(7,10); printf("[ADMISSIONS COMMITTEE]");
        gotoxy(11,12); puts(Mkaryawan.Nama);
        AdminMenu();
        char *audioFile = "Selamat datang Bapak_Ibu Admissions Committee!.wav";
        sound(audioFile);
    } else if  (sukses == 3){
        system("cls");
        gotoxy(7,10); printf("[ACADEMIC COMMITTEE]");
        gotoxy(11,12); puts(Mkaryawan.Nama);
        KemahasiswaanMenu();
        char *audioFile = "Selamat datang Bapak_Ibu Academic Committee!.wav";
        sound(audioFile);
    } else if  (sukses == 4){
        system("cls");
        gotoxy(7,10); printf("[ASSESSMENT COMMITTEE]");
        gotoxy(11,12); puts(Mkaryawan.Nama);
        PenilaianMenu();
        char *audioFile = "Selamat datang Bapak_Ibu Assessment Committee!.wav";
        sound(audioFile);
    } else {
        MessageBox(NULL, " Username/Password salah! ", "Perhatian", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
        gotoxy(86,31); printf("                      ");
        gotoxy(86,35); printf("                      ");
        LoginAkun();
    }
}

void LoginCamaba(){

    // Deklarasi
    int sukses = 0;

    // Algoritma
    DesainLoginCamaba();

    gotoxy(84,41); printf("Ketik '0' untuk ke kembali");
    SetColor(241);

    gotoxy(85,33); printf("        		  ");
    gotoxy(85,38); printf("			      ");
    gotoxy(85,33); printf(" "); fflush(stdin); getteks(username,20);
    gotoxy(85,38); printf(" "); fflush(stdin); getpass(password,20);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if ((strcmp(username, "0")==0) || (strcmp(password, "0")==0)){
        system("cls");
        selectLogin();
    }

    ArsCamaba = fopen("FileCamaba.dat", "rb");

    // Cari Username dan Password
    fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
    while(!feof(ArsCamaba))
    {
        if((strcmp(Mcamaba.username,username)==0) && (strcmp(Mcamaba.password,password)==0))
        {
            sukses=1;
            break;
        }
        fread(&Mcamaba, sizeof(Mcamaba),1 , ArsCamaba);
    }

    if  (sukses == 1){
        system("cls");
        char *audioFile = "Selamat datang Camaba.wav";

        MessageBox(NULL, "Selamat datang Calon Mahasiswa Baru!","Sistem Penerimaan Mahasiswa Baru",MB_OK | MB_ICONINFORMATION);
        sound(audioFile);
        gotoxy(2,10); printf("SELAMAT DATANG......");
        gotoxy(2,11); printf("CALON MAHASISWA CMB%.5d", Mcamaba.ID);
        gotoxy(2,12); puts(Mcamaba.nama_lengkap);
        CamabaMenu();
    } else {
        MessageBox(NULL, " Username/Password salah! ", "Perhatian", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
        gotoxy(86,31); printf("                      ");
        gotoxy(86,35); printf("                      ");
        LoginCamaba();
    }
}

void LoginInput(){

    //ALGORITHM
    gotoxy(85,33); printf("        		  ");
    gotoxy(85,38); printf("			      ");
    gotoxy(85,33); printf(" "); getteks(username,20);
    gotoxy(85,38); printf(" "); getpass(password,20);

}