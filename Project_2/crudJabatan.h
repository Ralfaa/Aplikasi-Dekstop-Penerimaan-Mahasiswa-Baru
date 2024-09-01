#include <windows.h>

// Global Deklarasi
int x,y;

// Prosedur
void MasterJabatan();
void TambahJabatan();
void LihatJabatan();
void LihatJabatan1();
void HapusJabatan();
void UbahJabatan();
void detailJabatan();
void HitungJabatan();

void MasterJabatan(){

    // Deklarasi
    int menu;

    // Algoritma
    CleanKiri();
    CleanTengah();
    CleanKanan();

    HitungJabatan();

    SetColor(240);
    gotoxy(14,22); printf(" MASTER JABATAN ");
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
            TambahJabatan();
            break;
        case 2:
            LihatJabatan();
            break;
        case 3:
            HapusJabatan();
            break;
        case 4:
            UbahJabatan();
            break;
        case 5:
            detailJabatan();
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

void TambahJabatan(){
    char NamaJabatan[50];
    char departemen[50];
    char jawaban;

    // Algoritma
    fflush(stdin);
    CleanTengah();
    CleanKanan();
    LihatJabatan1();
    gotoxy(133,44); printf("  Ketik apapun untuk lanjut");
    getch();

    jabatan:
    CleanTengah();
    CleanKanan();
    gotoxy(140,20); printf("             ");
    DesainData();

    ArsJabatan = fopen("FileJabatan.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsJabatan))
    {
        fread(&Mjabatan, sizeof(Mjabatan),1 , ArsJabatan);
    }
    Mjabatan.ID++;

    gotoxy(69,19); printf("=============================");
    gotoxy(69,20); printf("|T|A|M|B|A|H| |J|A|B|A|T|A|N|");
    gotoxy(69,21); printf("=============================");

    gotoxy(65,26); printf(" ID Jabatan   : RL%.2d\n", Mjabatan.ID);
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);


    gotoxy(65,27); printf(" Nama Jabatan : "); fflush(stdin); getteks(NamaJabatan, 50);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (strcmp(NamaJabatan, "0")==0){
        CleanKanan();
        MasterJabatan();
    }
    // Jika Nama Jabatan sudah ada, maka akan mengulang
    ArsJabatan1 = fopen("FileJabatan.dat", "rb");

    while (fread(&Mjabatan1, sizeof(Mjabatan1), 1, ArsJabatan1)==1)
    {
        if (strcmp(Mjabatan1.NamaJabatan, NamaJabatan)==0)
        {
            MessageBox(NULL, "Data tidak boleh sama"," perhatian",MB_OK);
            goto jabatan;
        }
    }
    fclose(ArsJabatan1);

    // jika tidak sama maka bisa lanjut
    gotoxy(65,28);  printf(" Departemen   : "); fflush(stdin); getteks(departemen, 50);

    ArsJabatan = fopen("FileJabatan.dat", "ab+");
    strcpy(Mjabatan.NamaJabatan, NamaJabatan);
    strcpy(Mjabatan.Departemen, departemen);
    Mjabatan.Status = 0;
    fwrite(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    fclose(ArsJabatan);

    CleanKanan();

    // Untuk Konfirmasi menambahkan data
    konfir:
    LihatJabatan1();
    CleanKanan();
    gotoxy(133,20); printf("  KONFIRMASI TAMBAH JABATAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Tambah lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&jawaban,1);
    if (jawaban=='y' || jawaban=='Y'){
        CleanKanan();
        CleanTengah();
        TambahJabatan();
    }else if(jawaban=='n' || jawaban=='N'){
        CleanKanan();
        CleanTengah();
        MasterJabatan();
    }else{
        CleanKanan();
        CleanTengah();
        goto konfir;
    }
}

void LihatJabatan(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsJabatan = fopen("FileJabatan.dat","rb");

    // Jika Data Jabatan Kosong
    if(ArsJabatan == NULL)
    {
        SetColor(240);
        MessageBox(NULL, "Data Jabatan masih kosong!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(65,44); printf("Klik apa saja untuk kembali ke menu utama... "); getch();
        MasterJabatan();
    }else {

        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15); printf("%c", 205);
            gotoxy(x, 17); printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-15s | %-25s | %-20s | %-15s","ID Jabatan", "Nama Jabatan", "Departement", "Status");
        while (!feof(ArsJabatan)) {
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
            printf(" RPL%-12.2d | %-25s | %-20s | %-15s",
                   Mjabatan.ID,
                   Mjabatan.NamaJabatan,
                   Mjabatan.Departemen,
                   StatusJabatan[Mjabatan.Status]);

            SetColor(241);
            fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);

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
                gotoxy(Kolom, 16); printf(" %-15s | %-25s | %-20s | %-15s","ID Jabatan", "Nama Jabatan", "Departement", "Status");
            }
        }

        fclose(ArsJabatan);
        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            MasterJabatan();
            getch();
        } else {
            LihatJabatan();
        }
    }
}

void LihatJabatan1() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsJabatan = fopen("FileJabatan.dat", "rb");

    // Jika Data Jabatan Kosong
    if (ArsJabatan == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Jabatan masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterJabatan();
    } else {

        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-15s | %-25s | %-20s | %-15s","ID Jabatan", "Nama Jabatan", "Departement", "Status");
        while (!feof(ArsJabatan)) {
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
            printf(" RPL%-12.2d | %-25s | %-20s | %-15s",
                   Mjabatan.ID,
                   Mjabatan.NamaJabatan,
                   Mjabatan.Departemen,
                   StatusJabatan[Mjabatan.Status]);

            SetColor(241);
            fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);

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
                gotoxy(Kolom, 16); printf(" %-15s | %-25s | %-20s | %-15s","ID Jabatan", "Nama Jabatan", "Departement", "Status");
            }
        }

        fclose(ArsJabatan);
        SetColor(252);
    }
}

void HapusJabatan() {

    // Deklarasi
    typedef enum {
        false = 0, true = 1
    } boolean;
    boolean found;
    int ID;
    char konfirm, kf;

    // Algoritma
    CleanTengah();
    CleanKanan();
    LihatJabatan1();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133, 44); printf("  Ketik '0' untuk ke kembali");

    SetColor(241);
    gotoxy(133, 20); printf("  HAPUS DATA JABATAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133, 22); printf("  ID Jabatan  : RL"); getnum(&ID, 2);
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        MasterJabatan();
    }

    ArsJabatan = fopen("FileJabatan.dat", "rb");
    TempJabatan = fopen("TempJabatan.dat", "wb");

    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    found = false;

    while((!found) && (!feof(ArsJabatan)))
    {
        if(Mjabatan.ID == ID) {
            found = true;
            break;
        }
        else {
            fwrite(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
        }
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    }

    if (found == true) {

        if (Mjabatan.Status == 0) {
            MessageBox(NULL, "Jabatan Ini Masih Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanKanan();
            MasterJabatan();
        } else if (Mjabatan.Status != 0) {
            CleanTengah();
            DesainData();
            gotoxy(71,19); printf("=========================");
            gotoxy(71,20); printf("|D|A|T|A| |J|A|B|A|T|A|N|");
            gotoxy(71,21); printf("=========================");
            gotoxy(69,28); printf(" ID Jabatan    :   RL%.2d",Mjabatan.ID);
            gotoxy(69,29); printf(" Nama Jabatan  :   %s",Mjabatan.NamaJabatan);
            gotoxy(69,30); printf(" Departement   :   %s",Mjabatan.Departemen);
            gotoxy(69,31); printf(" Status        :   %s",StatusJabatan[Mjabatan.Status]);
            gotoxy(133,44); printf("                           ");
            fflush(stdin);
        }

        fread(&Mjabatan,sizeof(Mjabatan), 1, ArsJabatan);
        while(!feof(ArsJabatan))
        {
            fwrite(&Mjabatan,sizeof(Mjabatan), 1, TempJabatan);
            fread(&Mjabatan,sizeof(Mjabatan), 1, ArsJabatan);
        }

    } else {
        MessageBox(NULL, "ID Jabatan tidak ditemukan di arsip", "PERINGATAN", MB_OK | MB_ICONWARNING);
        konfir:
        CleanKanan();
        gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
        gotoxy(161,22); getteks(&konfirm,1);
        if (konfirm == 'y' || konfirm == 'Y') {
            CleanKanan();
            HapusJabatan();
        } else if(konfirm == 'N' || konfirm == 'n'){
            CleanKanan();
            CleanTengah();
            MasterJabatan();
        } else {
            CleanKanan();
            goto konfir;
        }
    }

    fclose(ArsJabatan);
    fclose(TempJabatan);

    // Konfirmasi data yang akan dihapus
    gotoxy(133, 25); printf("  KONFIRMASI PENGHAPUSAN");
    gotoxy(133, 26); printf("  ===============================");
    gotoxy(133, 27); printf("  Yakin hapus data? [Y/N] = [ ]");
    gotoxy(162, 27); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        CleanKanan();
        CleanTengah();
        ArsJabatan = fopen("FileJabatan.dat", "wb");
        TempJabatan = fopen("TempJabatan.dat", "rb");

        fread(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
        while (!feof(TempJabatan)) {
            fwrite(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
            fread(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
        }
        fclose(ArsJabatan);
        fclose(TempJabatan);

        MessageBox(NULL, "Data Jabatan berhasil dihapus", "INFORMASI", MB_OK | MB_ICONINFORMATION);

        hapus:
        LihatJabatan1();

        // Konfirmasi untuk hapus data lagi
        gotoxy(133,20); printf("  KONFIRMASI PENGHAPUSAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin hapus lagi? [Y/N] = [ ]");
        gotoxy(162, 22);getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            CleanKanan();
            CleanTengah();
            HapusJabatan();
        } else if (kf == 'n' || kf == 'N') {
            CleanKanan();
            CleanTengah();
            MasterJabatan();
        } else {
            CleanKanan();
            CleanTengah();
            goto hapus;
        }
    } else{
        MessageBox(NULL, "Data Jabatan batal dihapus","INFORMASI", MB_OK | MB_ICONINFORMATION );
        CleanTengah();
        CleanKanan();
        MasterJabatan();
    }
    CleanKanan();
    LihatJabatan1();
}

void UbahJabatan(){

    // Deklarasi
    typedef enum {false=0, true=1} boolean;
    int ID, pilihan, pil2;
    char NamaB[50];
    char DepartementB[50];
    int StatusB;
    boolean found;
    char kf;

    // Algoritma
    fflush(stdin);
    LihatJabatan1();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  UPDATE DATA JABATAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Jabatan  : RL"); getnum(&ID,2);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        MasterJabatan();
    }

    ArsJabatan = fopen("FileJabatan.dat","rb");
    TempJabatan = fopen("TempJabatan.dat", "wb");

    found = false;

    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    while((!found) && (!feof(ArsJabatan)))
    {
        if(Mjabatan.ID == ID){
            found = true;
            break;
        }
        else{
            fwrite(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
        }
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    }

    if(found==true) {
        CleanKanan();
        CleanTengah();
        DesainData();
        // DATA YANG AKAN DIUBAH
        gotoxy(71,19); printf("==========================");
        gotoxy(71,20); printf("|D|A|T|A| |J|A|B|A|T|A|N|");
        gotoxy(71,21); printf("==========================");
        gotoxy(65,26); printf(" ID Jabatan   :   RL%.2d",Mjabatan.ID);
        gotoxy(65,27); printf(" Nama Jabatan :   %s",Mjabatan.NamaJabatan);
        gotoxy(65,28); printf(" Departement  :   %s",Mjabatan.Departemen);
        gotoxy(65,29); printf(" Status       :   %s",StatusJabatan[Mjabatan.Status]);

        CleanKanan();
        SetColor(241);
        gotoxy(133,20); printf("  PILIHAN MENU UPDATE");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  [1] Nama Jabatan");
        gotoxy(133,23); printf("  [2] Departement");
        gotoxy(133,24); printf("  [3] Status");
        gotoxy(133,25); printf("  [4] Kembali");

        gotoxy(133,27); printf("  Pilihan [ ]");
        gotoxy(144,27); getnum(&pilihan, 1);
        fflush(stdin);

        gotoxy(133,30); printf("  MASUKKAN DATA UPDATE !!");
        gotoxy(133,31); printf("  ===============================");


        switch (pilihan) {
            case 1:
                gotoxy(133,32);	printf("  Nama Jabatan : "); getletter(NamaB, 50);
                if (strcmp(NamaB, Mjabatan.NamaJabatan)==0)
                {
                    MessageBox(NULL, "Nama tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahJabatan();
                }
                strcpy(Mjabatan.NamaJabatan, NamaB);
                fwrite(&Mjabatan,sizeof(Mjabatan), 1, TempJabatan);
                break;
            case 2:
                gotoxy(133,32);	printf("  Deptartemen : "); scanf("%s", DepartementB);
                if (strcmp(DepartementB, Mjabatan.Departemen)==0) {
                    MessageBox(NULL, "Departement tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahJabatan();
                    break;
                }
                strcpy(Mjabatan.Departemen, DepartementB);
                fwrite(&Mjabatan,sizeof(Mjabatan), 1, TempJabatan);
                break;
            case 3:
                gotoxy(133,33); printf("  PILIHAN STATUS");
                gotoxy(133,34); printf("  ===============");
                gotoxy(133,35); printf("  [1] Aktif");
                gotoxy(133,36); printf("  [2] Non Aktif");
                gotoxy(133,38); printf("  Pilihan = [ ]");
                gotoxy(146,38); getnum(&pil2, 1);

                switch(pil2)
                {
                    case 1:
                        StatusB = 0; break;

                    case 2:
                        StatusB = 1; break;

                    default:
                        MessageBox(NULL, "Status yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        CleanKanan();
                        UbahJabatan();
                        break;
                }
                Mjabatan.Status = StatusB;
                fwrite(&Mjabatan,sizeof(Mjabatan), 1, TempJabatan);
                break;
            case 4:
                gotoxy(133,22); printf("               ");
                CleanKanan();
                MasterJabatan();
                fwrite(&Mjabatan,sizeof(Mjabatan), 1, TempJabatan);
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CleanKanan();
                gotoxy(139,20); printf("                    ");
                UbahJabatan();
                break;
        }
        fread(&Mjabatan, sizeof (Mjabatan), 1, ArsJabatan);
        while (!feof(ArsJabatan)){
            fwrite(&Mjabatan, sizeof (Mjabatan), 1, TempJabatan);
            fread(&Mjabatan, sizeof (Mjabatan), 1, ArsJabatan);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    } else{
        MessageBox(NULL, "ID Jabatan tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        UbahJabatan();
    }
    fclose(ArsJabatan);
    fclose(TempJabatan);

    ArsJabatan = fopen("FileJabatan.dat", "wb");
    TempJabatan = fopen("TempJabatan.dat", "rb");

    fread(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
    while (!feof(TempJabatan)) {
        fwrite(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
        fread(&Mjabatan, sizeof(Mjabatan), 1, TempJabatan);
    }
    fclose(ArsJabatan);
    fclose(TempJabatan);

    CleanTengah();
    CleanKanan();

    update:
    LihatJabatan1();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI UPDATE DATA KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Update lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        UbahJabatan();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        MasterJabatan();
    }else {
        CleanKanan();
        CleanTengah();
        goto update;
    }
}

void detailJabatan(){

    // Deklarasi
    typedef enum {false=0,true=1}boolean;
    boolean found;
    char kf;
    int ID;

    // Algoritma
    LihatJabatan1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  DETAIL DATA JABATAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Jabatan : RPL"); getnum(&ID, 2);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        MasterJabatan();
    }

    ArsJabatan = fopen("FileJabatan.dat","rb");

    found = false;

    fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    while((!found)&&(!feof(ArsJabatan)))
    {
        if(Mjabatan.ID == ID)
        {
            found = true;
            break;
        }
        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    }

    // Jika Data ditemukan
    if (found == true){
        CleanTengah();
        DesainData();
        gotoxy(71,19); printf("=========================");
        gotoxy(71,20); printf("|D|A|T|A| |J|A|B|A|T|A|N|");
        gotoxy(71,21); printf("=========================");
        gotoxy(69,28); printf(" ID Jabatan    :   RL%.2d",Mjabatan.ID);
        gotoxy(69,29); printf(" Nama Jabatan  :   %s",Mjabatan.NamaJabatan);
        gotoxy(69,30); printf(" Departement   :   %s",Mjabatan.Departemen);
        gotoxy(69,31); printf(" Status        :   %s",StatusJabatan[Mjabatan.Status]);
        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&Mjabatan, sizeof(Mjabatan),1 , ArsJabatan);
        fclose(ArsJabatan);
    }else {
        MessageBox(NULL, "ID Jabatan tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
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
        detailJabatan();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        MasterJabatan();
    }
    else
    {
        CleanKanan();
        goto carilagi;
    }
}

void HitungJabatan(){

    int jumlah=0, aktif=0, nonaktif=0;
    char jawaban;

    // DESAIN KOTAK

    gotoxy(65,25); printf("%c",201); //  atas kiri
    gotoxy(102,25); printf("%c",187); //atas kanan
    gotoxy(102,33); printf("%c",188); // bawah kanan
    gotoxy(65,33); printf("%c",200); // bawah kiri

    // GARIS HORIZONTAL
    for (x=66; x<=101; x++)
    {
        gotoxy(x,25); printf("%c",205);
        gotoxy(x,27); printf("%c",205);
        gotoxy(x,29); printf("%c",205);
        gotoxy(x,31); printf("%c",205);
        gotoxy(x,33); printf("%c",205);
    }

    // GARIS VERTIKAL KIRI KANAN
    for(y=26; y<=32; y++)
    {
        gotoxy(65,y); printf("%c",186);
        gotoxy(102,y); printf("%c",186);
    }

    // GARIS VERTIKAL TENGAH
    for (y=28; y<=32; y++)
    {
        gotoxy(83,y); printf("%c",186);
    }

    // GARIS DIATAS DATA
    for(x=7; x<=161; x++)
    {
        gotoxy(x,14); printf("%c",219);
    }

    // Hitung Data Jabatan
    ArsJabatan = fopen("FileJabatan.dat","rb");
    fread(&Mjabatan, sizeof(Mjabatan),1 , ArsJabatan);
    while (!feof(ArsJabatan))
    {
        jumlah++;
        if (Mjabatan.Status==0)
        {
            aktif++;
        }else{
            nonaktif++;
        }

        fread(&Mjabatan, sizeof(Mjabatan), 1, ArsJabatan);
    }
    fclose(ArsJabatan);
    SetColor(240);
    gotoxy(70,28); printf ("JUMLAH");
    gotoxy(70,30); printf ("AKTIF");
    gotoxy(70,32); printf ("NON AKTIF");
    gotoxy(79,26); printf("DATA JABATAN");
    gotoxy(93,28); printf("%d",jumlah);
    gotoxy(93,30); printf("%d",aktif);
    gotoxy(93,32); printf("%d",nonaktif);
    SetColor(241);

}

