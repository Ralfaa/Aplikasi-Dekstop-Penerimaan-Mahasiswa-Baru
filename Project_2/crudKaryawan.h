#include <windows.h>

// Global Deklarasi
int x,y;

// Prosedur
void MasterKaryawan();
void TambahKaryawan();
void LihatKaryawan();
void LihatKaryawan1();
void HapusKaryawan();
void UbahKaryawan();
void DetailKaryawan();
void HitungKaryawan();
void InfoAkunKaryawan();


void MasterKaryawan(){

    // Deklarasi
    int menu;

    // Algoritma
    CleanKiri();
    CleanTengah();

    HitungKaryawan();

    SetColor(240);
    gotoxy(14,22); printf(" MASTER KARYAWAN ");
    gotoxy(15,25); printf(" [1] Tambah ");
    gotoxy(15,26); printf(" [2] Lihat ");
    gotoxy(15,27); printf(" [3] Hapus ");
    gotoxy(15,28); printf(" [4] Ubah ");
    gotoxy(15,29); printf(" [5] Detail ");
    gotoxy(15,30); printf(" [6] Kembali");

    kembali:

    gotoxy(24,37); printf(" "); gotoxy(16,37); printf(" Pilih [ ]");
    SetColor(241);
    gotoxy(24,37); getnum(&menu,1);
    fflush(stdin);

    switch(menu)
    {
        case 1:
            TambahKaryawan();
            break;
        case 2:
            LihatKaryawan();
            gotoxy(24,37);  getch();
            MasterKaryawan();
            break;
        case 3:
            HapusKaryawan();
            break;
        case 4:
            UbahKaryawan();
            break;
        case 5:
            DetailKaryawan();
            break;
        case 6:
            CleanKiri();
            CleanTengah();
            AdminMenu();
            break;
        default :
            MessageBox(NULL, "Inputan Salah !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto kembali ;
    }
}

void TambahKaryawan(){

    // Deklarasi
    char username[16], Nik[20];
    char jawaban;
    typedef enum {false=0, true=1} boolean;
    boolean found;
    char password[20];

    // Algoritma
    fflush(stdin);
    CleanTengah();
    CleanKanan();
    LihatKaryawan1();
    gotoxy(133,44); printf("  Ketik apapun untuk lanjut");
    getch();

    karyawan:
    CleanTengah();
    CleanKanan();
    gotoxy(140,20); printf("             ");
    DesainData();

    ArsKaryawan = fopen("FileKaryawan.dat", "ab+");

    while(!feof(ArsKaryawan))
    {
        fread(&Mkaryawan, sizeof(Mkaryawan),1 , ArsKaryawan);
    }
    Mkaryawan.ID++;

    gotoxy(68,19); printf("===============================");
    gotoxy(68,20); printf("|T|A|M|B|A|H| |K|A|R|Y|A|W|A|N|");
    gotoxy(68,21); printf("===============================");

    gotoxy(61,26); printf(" ID Karyawan         : EMP%.5d\n", Mkaryawan.ID);
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);


    gotoxy(61,27); printf(" NIK                 : ");
    gotoxy(61,28); printf(" Username            : ");
    gotoxy(61,29); printf(" Nama                : ");
    gotoxy(61,30); printf(" Asal                : ");
    gotoxy(61,31); printf(" Tempat Lahir        : ");
    gotoxy(61,32); printf(" Tanggal Lahir       : ");
    gotoxy(61,33); printf(" Tlp                 : ");
    gotoxy(61,34); printf(" Password            : ");
    gotoxy(61,35); printf(" Konfirmasi Password : ");

    gotoxy(84,27); getteksnum(Nik, 16);
    gotoxy(84,28); getteks(username, 16);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if ((strcmp(Nik, "0")==0) || strcmp(username, "0")==0){
        CleanKanan();
        MasterKaryawan();
    }

    // Jika Nik atau Username sama, maka akan mengulang
    ArsKaryawan1 = fopen("FileKaryawan.dat", "rb");

    while (fread(&Mkaryawan1, sizeof(Mkaryawan1), 1, ArsKaryawan1)==1)
    {
        if ((strcmp(Mkaryawan1.NIK, Nik)==0) || (strcmp(Mkaryawan1.Username, username)==0))
        {
            MessageBox(NULL, "Data NIK dan Username Sudah Ada"," perhatian",MB_OK);
            goto karyawan;
        }
    }
    fclose(ArsKaryawan1);

    // jika tidak sama maka bisa lanjut
    ArsKaryawan = fopen("FileKaryawan.dat", "ab+");
    strcpy(Mkaryawan.NIK, Nik);
    strcpy(Mkaryawan.Username, username);

    gotoxy(84,29); getletter(Mkaryawan.Nama, 30);
    gotoxy(84,30); getteks(Mkaryawan.Asal, 15);
    gotoxy(84,31); getteks(Mkaryawan.tempatLahir, 50);
    gotoxy(84,32); fflush(stdin);getnum(&Mkaryawan.tanggalLahir.tgl, 2); printf(" / ");
    getnum(&Mkaryawan.tanggalLahir.bulan, 2); printf(" / ");
    getnum(&Mkaryawan.tanggalLahir.tahun, 4);
    if(datevalid(Mkaryawan.tanggalLahir)){
        found = true;
    }
    if (!found){
        MessageBox(0, "Tanggal Lahir Tidak Teridentifikasi", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
        goto karyawan;
    }

    gotoxy(84,33); getteksnum(Mkaryawan.Telp, 12);
    gotoxy(84,34); getpass(Mkaryawan.Password, 8);
    gotoxy(84,35); getpass(password, 8);

    if(strcmp(Mkaryawan.Password, password) != 0){
        MessageBox(NULL, "Password Anda Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
        goto karyawan;
    }

    balik:
    CleanTengah();
    CleanKanan();
    LihatJabatan1();

    SetColor(241);
    gotoxy(133, 20); printf("  PILIH JABATAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Jabatan    : RL"); getnum(&Mkaryawan.ID_Jabatan, 2);

    // Memanggil Data Jabatan
    ArsJabatan = fopen("FileJabatan.dat", "rb");
    TempJabatan = fopen("TempJabatan.dat", "wb");
    found = false;

    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    while((!found)&&(!feof(ArsJabatan))) {
        if(Mjabatan.ID == Mkaryawan.ID_Jabatan) {
            found = true;
            fwrite(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
            break;
        } else {
            fwrite(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
        }
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    }

    if (found == true){
        if(Mjabatan.Status == 0){
            fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
            fclose(ArsKaryawan);
            MessageBox(NULL, "Data karyawan berhasil ditambahkan!","INFORMASI", MB_OK | MB_ICONINFORMATION);
        }else{
            MessageBox(NULL, "Jabatan Tidak Aktif!","PERINGATAN", MB_OK | MB_ICONWARNING );
            CleanTengah();
            CleanKanan();
            goto balik;
        }
    }else{
        MessageBox(NULL, "Jabatan Ini Tidak Tersedia!","PERINGATAN", MB_OK | MB_ICONWARNING );
        CleanTengah();
        CleanKanan();
        goto balik;
    }

    fclose(ArsKaryawan);
    CleanKanan();
    CleanTengah();

    // Untuk Konfirmasi menambahkan data
    konfirkaryawan:
    gotoxy(133,20); printf("  KONFIRMASI TAMBAH KARYAWAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Tambah lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&jawaban,1);
    if (jawaban=='y' || jawaban=='Y'){
        CleanKanan();
        CleanTengah();
        TambahKaryawan();
    }else if(jawaban=='N' || jawaban=='n'){
        CleanKanan();
        CleanTengah();
        MasterKaryawan();
    }else{
        CleanKanan();
        CleanTengah();
        goto konfirkaryawan;
    }
}

void LihatKaryawan(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;
    typedef enum {false=0, true=1} boolean;
    boolean found;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsKaryawan = fopen("FileKaryawan.dat", "rb");

    // Jika Data Karyawan Kosong
    if (ArsKaryawan == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Karyawan masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterKaryawan();
    } else {
        fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-15s | %-20s | %-20s | %-15s","ID Karyawan", "Nama Karyawan", "Asal", "Jabatan");
        while (!feof(ArsKaryawan)) {


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

                printf(" EMP%-12.5d | %-20s | %-20s |",
                       Mkaryawan.ID,
                       Mkaryawan.Nama,
                       Mkaryawan.Asal);

                // Memanggil Data Jabatan
                ArsJabatan = fopen("FileJabatan.dat", "rb");

                found = false;

                fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
                while ((!found) && (!feof(ArsJabatan))) {
                    if (Mjabatan.ID == Mkaryawan.ID_Jabatan) {
                        found = true;
                        break;
                    }
                    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
                }

                if (found == true) {
                    gotoxy(Kolom + 65, Baris);
                    printf("%s", Mjabatan.NamaJabatan);
                }

                SetColor(241);


                fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
                
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
                printf("\tID Karyawan \t\t Nama Karyawan \t\t Asal \t\t Jabatan");
            }
        }
        fclose(ArsKaryawan);

        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            MasterKaryawan();
            getch();
        } else {
            LihatKaryawan();
        }
    }
}

void LihatKaryawan1(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    typedef enum {false=0, true=1} boolean;
    boolean found;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsKaryawan = fopen("FileKaryawan.dat", "rb");

    // Jika Data Jabatan Kosong
    if (ArsKaryawan == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Karyawan masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterKaryawan();
    } else {
        fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-15s | %-20s | %-20s | %-15s","ID Karyawan", "Nama Karyawan", "Asal", "Jabatan");
        while (!feof(ArsKaryawan)) {
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
            printf(" EMP%-12.5d | %-20s | %-20s |",
                   Mkaryawan.ID,
                   Mkaryawan.Nama,
                   Mkaryawan.Asal);

            // Memanggil Data Jabatan
            ArsJabatan = fopen("FileJabatan.dat", "rb");

            found = false;

            fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
            while((!found)&&(!feof(ArsJabatan))) {
                if(Mjabatan.ID == Mkaryawan.ID_Jabatan) {
                    found = true;
                    break;
                }
                fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
            }

            if (found == true){
                gotoxy(Kolom + 65, Baris);
                printf("%s", Mjabatan.NamaJabatan);
            }

            SetColor(241);
            fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);

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
                printf("\tID Karyawan \t\t Nama Karyawan \t\t Asal \t\t Jabatan");
            }
        }
        fclose(ArsKaryawan);
        SetColor(252);

    }
}

void HapusKaryawan(){

    // Deklarasi
    typedef enum {
        false = 0, true = 1
    } boolean;
    boolean found;
    boolean found1;
    int ID;
    char konfirm, kf;

    // Algoritma
    CleanTengah();
    CleanKanan();
    LihatKaryawan1();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  HAPUS DATA KARYAWAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Karyawan  : EMP");
    getnum(&ID, 5);

    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        MasterKaryawan();
    }

    ArsKaryawan = fopen("FileKaryawan.dat", "rb");
    TempKaryawan = fopen("TempKaryawan.dat", "wb");

    found = false;
    fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
    while((!found) && (!feof(ArsKaryawan)))
    {
        if(Mkaryawan.ID == ID) {
            found = true;
            break;
        } else {
            fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
        }
        fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
    }

    if (found == true){

        int ID_Jabatan;
        char NIK[20];
        char Telp[20];
        char Nama[50];
        char Asal[50];
        char Username[20];
        char Password[20];
        char ttl[50];

        CleanTengah();
        DesainData();
        gotoxy(70,19); printf("===========================");
        gotoxy(70,20); printf("|D|A|T|A| |K|A|R|Y|A|W|A|N|");
        gotoxy(70,21); printf("===========================");

        gotoxy(69,25); printf(" ID Karyawan   : EMP%.5d",Mkaryawan.ID);
        gotoxy(69,26); printf(" Nama Karyawan : %s",Mkaryawan.Nama);
        gotoxy(69,27); printf(" NIK           : %s",Mkaryawan.NIK);
        gotoxy(69,28); printf(" Asal          : %s",Mkaryawan.Asal);
        gotoxy(69,29); printf(" Tempat Lahir  : %s",Mkaryawan.tempatLahir);
        gotoxy(69,30); printf(" Tanggal Lahir : %.2d-%.2d-%.4d",Mkaryawan.tanggalLahir.tgl, Mkaryawan.tanggalLahir.bulan, Mkaryawan.tanggalLahir.tahun);
        gotoxy(69,31); printf(" No Telepon    : %s",Mkaryawan.Telp);
        gotoxy(69,32); printf(" Username      : %s",Mkaryawan.Username);
        gotoxy(69,33); printf(" Password      : %s",Mkaryawan.Password);

        // Memanggil Data Jabatan
        ArsJabatan = fopen("FileJabatan.dat", "rb");
        found1 = false;
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        while((!found1)&&(!feof(ArsJabatan))) {
            if(Mjabatan.ID == Mkaryawan.ID_Jabatan) {
                found1 = true;
                break;
            }
            fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        }

        if (found1 == true){
            gotoxy(69,34); printf(" Jabatan       : %s", Mjabatan.NamaJabatan);
        }

        fread(&Mkaryawan,sizeof(Mkaryawan), 1, ArsKaryawan);
        while(!feof(ArsKaryawan))
        {
            fwrite(&Mkaryawan,sizeof(Mkaryawan), 1, TempKaryawan);
            fread(&Mkaryawan,sizeof(Mkaryawan), 1, ArsKaryawan);
        }

    } else {
        MessageBox(NULL, "ID Karyawan tidak ditemukan di arsip", "PERINGATAN", MB_OK | MB_ICONWARNING);
        konfir:
        CleanKanan();
        gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
        gotoxy(161,22); getteks(&konfirm,1);
        if (konfirm == 'y' || konfirm == 'Y') {
            CleanKanan();
            HapusKaryawan();
        } else if(konfirm == 'N' || konfirm == 'n'){
            CleanKanan();
            CleanTengah();
            MasterKaryawan();
        } else {
            CleanKanan();
            goto konfir;
        }
    }

    fclose(ArsKaryawan);
    fclose(TempKaryawan);

    // Konfirmasi data yang akan dihapus
    gotoxy(133, 25); printf("  KONFIRMASI PENGHAPUSAN");
    gotoxy(133, 26); printf("  ===============================");
    gotoxy(133, 27); printf("  Yakin hapus data? [Y/N] = [ ]");
    gotoxy(162, 27); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        CleanKanan();
        CleanTengah();
        ArsKaryawan = fopen("FileKaryawan.dat", "wb");
        TempKaryawan = fopen("TempKaryawan.dat", "rb");

        fread(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
        while (!feof(TempKaryawan)) {
            fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
            fread(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
        }
        fclose(ArsKaryawan);
        fclose(TempKaryawan);

        MessageBox(NULL, "Data Karyawan berhasil dihapus", "INFORMASI", MB_OK | MB_ICONINFORMATION);

        hapus:
        CleanTengah();
        CleanKanan();
        LihatKaryawan1();

        // Konfirmasi untuk hapus data lagi
        gotoxy(133,20); printf("  KONFIRMASI PENGHAPUSAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin hapus lagi? [Y/N] = [ ]");
        gotoxy(162, 22);getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            CleanKanan();
            CleanTengah();
            HapusKaryawan();
        } else if (kf == 'n' || kf == 'N') {
            CleanKanan();
            CleanTengah();
            MasterKaryawan();
        } else {
            CleanKanan();
            CleanTengah();
            goto hapus;
        }
    } else{
        MessageBox(NULL, "Data Karyawan batal dihapus","INFORMASI", MB_OK | MB_ICONINFORMATION );
        CleanTengah();
        CleanKanan();
        MasterKaryawan();
    }
    CleanKanan();
    LihatKaryawan1();
}

void UbahKaryawan(){

    // Deklarasi
    typedef enum {false=0, true=1} boolean;
    boolean found;
    boolean found1;
    boolean found2;
    boolean found3;
    int ID, pilihan, pil2;
    int ID_JabatanB;
    char NIKB[20];
    char TelpB[20];
    char NamaB[50];
    char AsalB[50];
    char UsernameB[20];
    char PasswordB[20];
    char ttlB[50];
    Date tanggalLahirB;
    char kf, konfirm;
    char PasswordK[20];

    // Algoritma
    fflush(stdin);
    LihatKaryawan1();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  UPDATE DATA KARYAWAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Karyawan  : EMP"); getnum(&ID,5);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        MasterKaryawan();
    }

    ArsKaryawan = fopen("FileKaryawan.dat", "rb");
    TempKaryawan = fopen("TempKaryawan.dat", "wb");

    found = false;

    fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
    while((!found) && (!feof(ArsKaryawan)))
    {
        if(Mkaryawan.ID == ID) {
            found = true;
            break;
        } else {
            fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
        }
        fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
    }

    if (found == true) {

        CleanTengah();
        DesainData();
        gotoxy(70, 19); printf("===========================");
        gotoxy(70, 20); printf("|D|A|T|A| |K|A|R|Y|A|W|A|N|");
        gotoxy(70, 21); printf("===========================");

        gotoxy(65, 25);
        printf(" ID Karyawan   : EMP%.5d", Mkaryawan.ID);
        gotoxy(65, 26);
        printf(" Nama Karyawan : %s", Mkaryawan.Nama);
        gotoxy(65, 27);
        printf(" NIK           : %s", Mkaryawan.NIK);
        gotoxy(65, 28);
        printf(" Asal          : %s", Mkaryawan.Asal);
        gotoxy(65,29);
        printf(" Tempat Lahir  : %s",Mkaryawan.tempatLahir);
        gotoxy(65,30);
        printf(" Tanggal Lahir : %.2d-%.2d-%.4d",Mkaryawan.tanggalLahir.tgl, Mkaryawan.tanggalLahir.bulan, Mkaryawan.tanggalLahir.tahun);
        gotoxy(65, 31);
        printf(" No Telepon    : %s", Mkaryawan.Telp);
        gotoxy(65, 32);
        printf(" Username      : %s", Mkaryawan.Username);
        gotoxy(65, 33);
        printf(" Password      : %s", Mkaryawan.Password);

        // Memanggil Data Jabatan
        ArsJabatan = fopen("FileJabatan.dat", "rb");
        found1 = false;
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        while ((!found1) && (!feof(ArsJabatan))) {
            if (Mjabatan.ID == Mkaryawan.ID_Jabatan) {
                found1 = true;
                break;
            }
            fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        }

        if (found1 == true) {
            gotoxy(65, 34);
            printf(" Jabatan       : %s", Mjabatan.NamaJabatan);
        }

        CleanKanan();
        SetColor(252);
        gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
        SetColor(241);
        gotoxy(133,20); printf("  PILIHAN MENU UPDATE");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  [1] Nama Karyawan");
        gotoxy(133,23); printf("  [2] NIK");
        gotoxy(133,24); printf("  [3] Asal");
        gotoxy(133,25); printf("  [4] Tempat Lahir");
        gotoxy(133,26); printf("  [5] Tanggal Lahir");
        gotoxy(133,27); printf("  [6] No Telepon");
        gotoxy(133,28); printf("  [7] Username");
        gotoxy(133,29); printf("  [8] Password");
        gotoxy(133,30); printf("  [9] Jabatan");

        gotoxy(133,32); printf("  Pilihan [ ]");
        gotoxy(144,32); getnum(&pilihan, 1);
        fflush(stdin);
        if (pilihan==0)
        {
            CleanKanan();
            CleanTengah();
            UbahKaryawan();
        }

        gotoxy(133,35); printf("  MASUKKAN DATA UPDATE !!");
        gotoxy(133,36); printf("  ===============================");

        switch (pilihan) {
            case 1:
                gotoxy(133, 37);
                printf("  Nama Karyawan : ");
                getletter(NamaB, 16);
                if (strcmp(NamaB, Mkaryawan.Nama) == 0) {
                    MessageBox(NULL, "Nama tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.Nama, NamaB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 2:
                gotoxy(133, 37);
                printf("  NIK : ");
                getteksnum(NIKB, 17);
                if (strcmp(NIKB, Mkaryawan.NIK) == 0) {
                    MessageBox(NULL, "NIK tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.NIK, NIKB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 3:
                gotoxy(133, 37);
                printf("  Asal Daerah : ");
                getletter(AsalB, 50);
                if (strcmp(AsalB, Mkaryawan.Asal) == 0) {
                    MessageBox(NULL, "Asal tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.Asal, AsalB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 4:
                gotoxy(133, 37);
                printf("  Tempat Lahir : ");
                getletter(ttlB, 50);
                if (strcmp(ttlB, Mkaryawan.tempatLahir) == 0) {
                    MessageBox(NULL, "Tempat Lahir tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.tempatLahir, ttlB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 5:
                found3 = false;
                tanggalB:
                gotoxy(133, 37);
                printf("  Tanggal Lahir : ");
                gotoxy(135, 37);fflush(stdin);getnum(&tanggalLahirB.tgl, 2); printf(" / ");
                getnum(&tanggalLahirB.bulan, 2); printf(" / ");
                getnum(&tanggalLahirB.tahun, 4);
                if(datevalid(tanggalLahirB)){
                    found3 = true;
                }
                if (!found){
                    MessageBox(0, "Tanggal Lahir Tidak Teridentifikasi", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
                    goto tanggalB;
                }
                Mkaryawan.tanggalLahir.tgl = tanggalLahirB.tgl;
                Mkaryawan.tanggalLahir.bulan = tanggalLahirB.bulan;
                Mkaryawan.tanggalLahir.tahun = tanggalLahirB.tahun;
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 6:
                gotoxy(133, 37);
                printf("  No Telepon : ");
                getteksnum(TelpB, 13);
                if (strcmp(TelpB, Mkaryawan.Telp) == 0) {
                    MessageBox(NULL, "Nomor Telepon tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.Telp, TelpB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 7:
                gotoxy(133, 37);
                printf("  Username : ");
                getletter(UsernameB, 50);
                if (strcmp(UsernameB, Mkaryawan.Username) == 0) {
                    MessageBox(NULL, "Username tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.Username, UsernameB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 8:

                gotoxy(133, 37);
                printf("  Password : ");
                getpass(PasswordB, 10);
                gotoxy(133, 38);
                printf("  Konfir Password : ");
                getpass(PasswordB, 10);

                if(strcmp(PasswordB, PasswordK) != 0){
                    MessageBox(NULL, "Password Anda Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahKaryawan();
                }

                if (strcmp(PasswordB, Mkaryawan.Password) == 0) {
                    MessageBox(NULL, "Password tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }
                strcpy(Mkaryawan.Password, PasswordB);
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            case 9:
                CleanTengah();
                LihatJabatan1();
                SetColor(241);
                gotoxy(133, 37);
                printf("  Jabatan : RPL");
                getnum(&ID_JabatanB, 2);

                if (ID_JabatanB == Mkaryawan.ID_Jabatan) {
                    MessageBox(NULL, "Jabatan tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahKaryawan();
                }

                // Memanggil Data Jabatan
                ArsJabatan = fopen("FileJabatan.dat", "rb");
                TempJabatan = fopen("TempJabatan.dat", "wb");

                found2 = false;

                fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
                while((!found2)&&(!feof(ArsJabatan))) {
                    if(ID_JabatanB == Mjabatan.ID) {
                        found2 = true;
                        fwrite(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
                        break;
                    } else {
                        fwrite(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
                    }
                    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
                }

                if (found2 == true){
                    if(Mjabatan.Status == 0){
                        Mkaryawan.ID_Jabatan = ID_JabatanB;
                    }else{
                        MessageBox(NULL, "Jabatan Tidak Aktif!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        CleanTengah();
                        CleanKanan();
                        UbahKaryawan();
                    }
                }else{
                    MessageBox(NULL, "Jabatan Ini Tidak Tersedia!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanTengah();
                    CleanKanan();
                    UbahKaryawan();
                }
                fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CleanKanan();
                gotoxy(139,20); printf("                    ");
                UbahKaryawan();
                break;
        }

        fread(&Mkaryawan, sizeof (Mkaryawan), 1, ArsKaryawan);
        while (!feof(ArsKaryawan)){
            fwrite(&Mkaryawan, sizeof (Mkaryawan), 1, TempKaryawan);
            fread(&Mkaryawan, sizeof (Mkaryawan), 1, ArsKaryawan);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    }else{
        MessageBox(NULL, "ID Jabatan tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        UbahKaryawan();
    }
    fclose(ArsKaryawan);
    fclose(TempKaryawan);

    ArsKaryawan = fopen("FileKaryawan.dat", "wb");
    TempKaryawan = fopen("TempKaryawan.dat", "rb");

    fread(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
    while (!feof(TempKaryawan)) {
        fwrite(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
        fread(&Mkaryawan, sizeof(Mkaryawan), 1, TempKaryawan);
    }
    fclose(ArsKaryawan);
    fclose(TempKaryawan);

    CleanTengah();
    CleanKanan();

    update:
    LihatKaryawan1();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI UPDATE DATA KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Update lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        UbahKaryawan();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        MasterKaryawan();
    }else {
        CleanKanan();
        goto update;
    }
}

void DetailKaryawan(){

    // Deklarasi
    typedef enum {false=0,true=1}boolean;
    boolean found;
    boolean found1;
    char kf;
    int ID;

    // Algoritma
    LihatKaryawan1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  DETAIL DATA KARYAWAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Karyawan : EMP"); getnum(&ID, 5);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        MasterKaryawan();
    }

    ArsKaryawan = fopen("FileKaryawan.dat","rb");

    found = false;

    fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
    while((!found)&&(!feof(ArsKaryawan)))
    {
        if(Mkaryawan.ID == ID)
        {
            found = true;
            break;
        }
        fread(&Mkaryawan, sizeof(Mkaryawan), 1, ArsKaryawan);
    }

    // Jika Data ditemukan
    if (found == true){
        CleanTengah();
        DesainData();
        gotoxy(70, 19);
        printf("===========================");
        gotoxy(70, 20);
        printf("|D|A|T|A| |K|A|R|Y|A|W|A|N|");
        gotoxy(70, 21);
        printf("===========================");

        gotoxy(65, 25);
        printf(" ID Karyawan   : EMP%.5d", Mkaryawan.ID);
        gotoxy(65, 26);
        printf(" Nama Karyawan : %s", Mkaryawan.Nama);
        gotoxy(65, 27);
        printf(" NIK           : %s", Mkaryawan.NIK);
        gotoxy(65, 28);
        printf(" Asal          : %s", Mkaryawan.Asal);
        gotoxy(65, 29);
        printf(" Tempat Lahir  : %s", Mkaryawan.tempatLahir);
        gotoxy(65,30);
        printf(" Tanggal Lahir : %.2d-%.2d-%.4d",Mkaryawan.tanggalLahir.tgl, Mkaryawan.tanggalLahir.bulan, Mkaryawan.tanggalLahir.tahun);
        gotoxy(65, 31);
        printf(" No Telepon    : %s", Mkaryawan.Telp);
        gotoxy(65, 32);
        printf(" Username      : %s", Mkaryawan.Username);
        gotoxy(65, 33);
        printf(" Password      : %s", Mkaryawan.Password);

        // Memanggil Data Jabatan
        ArsJabatan = fopen("FileJabatan.dat", "rb");
        found1 = false;
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        while ((!found1) && (!feof(ArsJabatan))) {
            if (Mjabatan.ID == Mkaryawan.ID_Jabatan) {
                found1 = true;
                break;
            }
            fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        }

        if (found1 == true) {
            gotoxy(65, 34);
            printf(" Jabatan       : %s", Mjabatan.NamaJabatan);
        }
        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&Mkaryawan, sizeof(Mkaryawan),1 , ArsKaryawan);
        fclose(ArsJabatan);
        fclose(ArsKaryawan);
    }else {
        MessageBox(NULL, "ID Karyawan tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(133,22); printf("               ");
        CleanKanan();
    }

    carilagi:

    CleanKanan();
    gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
    gotoxy(161,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y')
    {
        CleanKanan();
        CleanTengah();
        DetailKaryawan();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        MasterKaryawan();
    }
    else
    {
        CleanKanan();
        goto carilagi;
    }
}

void InfoAkunKaryawan(){

    bool found1;

    CleanTengah();

    DesainData();
    gotoxy(70, 19);
    printf("===========================");
    gotoxy(70, 20);
    printf("|D|A|T|A| |K|A|R|Y|A|W|A|N|");
    gotoxy(70, 21);
    printf("===========================");

    gotoxy(65, 25);
    printf(" ID Karyawan   : EMP%.5d", Mkaryawan.ID);
    gotoxy(65, 26);
    printf(" Nama Karyawan : %s", Mkaryawan.Nama);
    gotoxy(65, 27);
    printf(" NIK           : %s", Mkaryawan.NIK);
    gotoxy(65, 28);
    printf(" Asal          : %s", Mkaryawan.Asal);
    gotoxy(65, 29);
    printf(" Tempat Lahir  : %s", Mkaryawan.tempatLahir);
    gotoxy(65,30);
    printf(" Tanggal Lahir : %.2d-%.2d-%.4d",Mkaryawan.tanggalLahir.tgl, Mkaryawan.tanggalLahir.bulan, Mkaryawan.tanggalLahir.tahun);
    gotoxy(65, 31);
    printf(" No Telepon    : %s", Mkaryawan.Telp);
    gotoxy(65, 32);
    printf(" Username      : %s", Mkaryawan.Username);
    gotoxy(65, 33);
    printf(" Password      : %s", Mkaryawan.Password);

    // Memanggil Data Jabatan
    ArsJabatan = fopen("FileJabatan.dat", "rb");
    found1 = false;
    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    while ((!found1) && (!feof(ArsJabatan))) {
        if (Mjabatan.ID == Mkaryawan.ID_Jabatan) {
            found1 = true;
            break;
        }
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    }

    if (found1 == true) {
        gotoxy(65, 34);
        printf(" Jabatan       : %s", Mjabatan.NamaJabatan);
    }
    gotoxy(133,44); printf("                           ");
    fflush(stdin);

    gotoxy(65,37); printf(" Klik Apapun Untuk Lanjut");
    getch();

    CleanTengah();

    if(Mkaryawan.ID_Jabatan == 1){
        FinanceMenu();
    }else if(Mkaryawan.ID_Jabatan == 2){
        AdminMenu();
    }else if(Mkaryawan.ID_Jabatan == 3){
        KemahasiswaanMenu();
    }else if(Mkaryawan.ID_Jabatan == 4){
        PenilaianMenu();
    }

    fclose(ArsJabatan);
}


void HitungKaryawan(){

    SetColor(241);
    int jumlah = 0, admin=0, finance=0, kemahasiswaan=0, penilaian=0;

    // Desain
    gotoxy(64,22); printf("%c",220); //  atas kiri
    gotoxy(101,22); printf("%c",220); //atas kanan
    gotoxy(101,28); printf("%c",220); // bawah kanan
    gotoxy(64,28); printf("%c",220); // bawah kiri
    gotoxy(77,26); printf("%c",220);
    for (x=50; x<=120; x++)
    {
        gotoxy(x,22); printf("%c",205); // garis horizontal atas
        gotoxy(x,24); printf("%c",205); // garis tipis dobel tengah atas
        gotoxy(x,26); printf("%c",205); // garis tipis dobel tengah bawah
        gotoxy(x,28); printf("%c",205); // garis horizontal bawah
    }
    for(y=23; y<=27; y++)
    {
        gotoxy(50,y); printf("%c",186); // garis tipis dobel paling kiri
        gotoxy(120,y); printf("%c",186); // garis tipis dobel paling kanan
    }
    for (y=25; y<=27; y++)
    {
        gotoxy(60,y); printf("%c",186); // garis tipis ke 1
        gotoxy(70,y); printf("%c",186);
        gotoxy(85,y); printf("%c",186);
        gotoxy(100,y); printf("%c",186);
    }

    ArsKaryawan = fopen("FileKaryawan.dat", "rb");
    fread(&Mkaryawan, sizeof(Mkaryawan),1 , ArsKaryawan);
    while (!feof(ArsKaryawan))
    {
        jumlah++;
        if (Mkaryawan.ID_Jabatan==1){
            admin++;
        }
        else if (Mkaryawan.ID_Jabatan==2){
            finance++;
        }
        else if (Mkaryawan.ID_Jabatan==3){
            penilaian++;
        }
        else if (Mkaryawan.ID_Jabatan==4) {
            kemahasiswaan++;
        }
        fread(&Mkaryawan, sizeof(Mkaryawan),1 , ArsKaryawan);
    }
    fclose(ArsKaryawan);
    gotoxy(52,25); printf ("JUMLAH");
    gotoxy(63,25); printf ("ADMIN");
    gotoxy(74,25); printf ("FINANCE");
    gotoxy(88,25); printf ("PENILAIAN");
    gotoxy(103,25); printf ("KEMAHASISWAAN");
    gotoxy(78,23); printf("DATA KARYAWAN");
    gotoxy(54,27); printf("%d",jumlah);
    gotoxy(65,27); printf("%d",admin);
    gotoxy(77,27); printf("%d",finance);
    gotoxy(92,27); printf("%d",penilaian);
    gotoxy(108,27); printf("%d",kemahasiswaan);
    SetColor(241);

}

