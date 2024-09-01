#include <windows.h>

// Global Deklarasi
int x,y;

// Prosedur
void MasterJalurPenerimaan();
void TambahJalurPenerimaan();
void LihatJalurPenerimaan();
void LihatJalurPenerimaan1();
void HapusJalurPenerimaan();
void UbahJalurPenerimaan();
void detailJalurPenerimaan();
void HitungJalurPenerimaan();

void MasterJalurPenerimaan(){

    // Deklarasi
    int menu;

    // Algoritma
    CleanKiri();
    CleanTengah();
    CleanKanan();

    HitungJalurPenerimaan();

    SetColor(240);
    gotoxy(14,22); printf(" MASTER JALUR ");
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
            TambahJalurPenerimaan();
            break;
        case 2:
            LihatJalurPenerimaan();
            break;
        case 3:
            HapusJalurPenerimaan();
            break;
        case 4:
            UbahJalurPenerimaan();
            break;
        case 5:
            detailJalurPenerimaan();
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

void TambahJalurPenerimaan(){
    char nama_jalur[50];
    float biaya_pendaftaran;
    char jawaban;

    // Algoritma
    fflush(stdin);
    CleanTengah();
    CleanKanan();
    LihatJalurPenerimaan1();
    gotoxy(133,44); printf("  Ketik apapun untuk lanjut");
    getch();

    CleanTengah();
    CleanKanan();
    gotoxy(140,20); printf("             ");
    DesainData();

    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsJalurPenerimaan))
    {
        fread(&Mjalur, sizeof(Mjalur),1 , ArsJalurPenerimaan);
    }
    Mjalur.ID++;

    gotoxy(72,19); printf("=========================");
    gotoxy(72,20); printf("|T|A|M|B|A|H| |J|A|L|U|R|");
    gotoxy(72,21); printf("=========================");

    gotoxy(65,26); printf(" ID Jalur          : JLR%.3d\n", Mjalur.ID);
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);

    jalur:
    gotoxy(65,27); printf(" Nama Jalur        : "); fflush(stdin); getteks(nama_jalur, 50);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (strcmp(nama_jalur, "0")==0){
        CleanKanan();
        MasterJalurPenerimaan();
    }
    // Jika Nama Jalur sudah ada, maka akan mengulang
    ArsJalurPenerimaan1 = fopen("FileJalurPenerimaan.dat", "rb");

    while (fread(&Mjalur1, sizeof(Mjalur1), 1, ArsJalurPenerimaan1)==1)
    {
        if (strcmp(Mjalur1.nama_jalur, nama_jalur)==0)
        {
            MessageBox(NULL, "Data tidak boleh sama"," perhatian",MB_OK);
            goto jalur;
        }
    }
    fclose(ArsJalurPenerimaan1);

    // jika tidak sama maka bisa lanjut
    gotoxy(65,28);  printf(" Biaya Pendaftaran : Rp. "); fflush(stdin); scanf("%f", &biaya_pendaftaran);

    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "ab+");
    strcpy(Mjalur.nama_jalur, nama_jalur);
    Mjalur.biaya_pendaftaran = biaya_pendaftaran;
    Mjalur.Status = 0;

    fwrite(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    fclose(ArsJalurPenerimaan);

    CleanKanan();

    // Untuk Konfirmasi menambahkan data
    konfir:
    LihatJalurPenerimaan1();
    gotoxy(133,20); printf("  KONFIRMASI TAMBAH JALUR");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Tambah lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&jawaban,1);
    if (jawaban=='y' || jawaban=='Y'){
        CleanKanan();
        CleanTengah();
        TambahJalurPenerimaan();
    }else if(jawaban=='n' || jawaban=='N'){
        CleanKanan();
        CleanTengah();
        MasterJalurPenerimaan();
    }else{
        CleanKanan();
        CleanTengah();
        goto konfir;
    }
}

void LihatJalurPenerimaan(){

    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat","rb");

    // Jika Data Jalur Kosong
    if(ArsJalurPenerimaan == NULL)
    {
        SetColor(240);
        MessageBox(NULL, "Data Jalur Penerimaan masih kosong!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(65,44); printf("Klik apa saja untuk kembali ke menu utama... "); getch();
        MasterJalurPenerimaan();
    }else {

        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15); printf("%c", 205);
            gotoxy(x, 17); printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-20s | %-20s | %-10s","ID JLR", "Nama Jalur", "Biaya Pendaftaran", "Status");
        while (!feof(ArsJalurPenerimaan)) {
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
            printf(" JLR%.3d | %-20s | Rp. %'16.2f | %5s",
                   Mjalur.ID,
                   Mjalur.nama_jalur,
                   Mjalur.biaya_pendaftaran,
                   StatusJalur[Mjalur.Status]);
            SetColor(241);
            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-20s | %-20s | %-10s","ID JLR", "Nama Jalur", "Biaya Pendaftaran", "Status");
            }
        }

        fclose(ArsJalurPenerimaan);
        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            MasterJalurPenerimaan();
            getch();
        } else {
            LihatJalurPenerimaan();
        }
    }
}

void LihatJalurPenerimaan1() {
    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan
    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

    // Jika Data Jalur Kosong
    if (ArsJalurPenerimaan == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Jalur Penerimaan masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterJalurPenerimaan();
    } else {

        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-20s | %-20s | %-10s","ID JLR", "Nama Jalur", "Biaya Pendaftaran", "Status");
        while (!feof(ArsJalurPenerimaan)) {
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
            printf(" JLR%.3d | %-20s | Rp. %'16.2f | %5s",
                   Mjalur.ID,
                   Mjalur.nama_jalur,
                   Mjalur.biaya_pendaftaran,
                   StatusJalur[Mjalur.Status]);
            SetColor(241);
            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);

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
}

void HapusJalurPenerimaan() {
    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan
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
    LihatJalurPenerimaan1();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  HAPUS DATA JALUR PENERIMAAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22);  printf("  ID Jalur  : JLR"); getnum(&ID,3);
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        MasterJalurPenerimaan();
    }

    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");
    TempJalurPenerimaan = fopen("TempJalurPenerimaan.dat", "wb");

    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    found = false;

    while((!found) && (!feof(ArsJalurPenerimaan)))
    {
        if(Mjalur.ID == ID) {
            found = true;
            break;
        }
        else {
            fwrite(&Mjalur, sizeof(Mjalur), 1, TempJalurPenerimaan);
        }
        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    }

    if (found == true) {

        if (Mjalur.Status == 0) {
            MessageBox(NULL, "Jalur Ini Masih Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanKanan();
            MasterJalurPenerimaan();
        } else{
            CleanTengah();
            DesainData();
            gotoxy(74, 19); printf("=====================");
            gotoxy(74, 20); printf("|D|A|T|A| |J|A|L|U|R|");
            gotoxy(74, 21); printf("=====================");
            gotoxy(64, 28); printf(" ID Jalur          :   JLR%.3d", Mjalur.ID);
            gotoxy(64, 29); printf(" Nama Jalur        :   %s", Mjalur.nama_jalur);
            gotoxy(64, 30);
            printf(" Biaya Pendaftaran :   Rp. %'.2f", Mjalur.biaya_pendaftaran);
            gotoxy(64,31);
            printf(" Status            :   %s",StatusJalur[Mjalur.Status]);
            gotoxy(133, 44);
            printf("                           ");
            fflush(stdin);
        }

        fread(&Mjalur,sizeof(Mjalur), 1, ArsJalurPenerimaan);
        while(!feof(ArsJalurPenerimaan))
        {
            fwrite(&Mjalur,sizeof(Mjalur), 1, TempJalurPenerimaan);
            fread(&Mjalur,sizeof(Mjalur), 1, ArsJalurPenerimaan);
        }

    } else {
        MessageBox(NULL, "ID Jalur tidak ditemukan di arsip", "PERINGATAN", MB_OK | MB_ICONWARNING);

        konfir :
        gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
        gotoxy(161, 22); getteks(&konfirm, 1);
        if (konfirm == 'y' || konfirm == 'Y') {
            CleanKanan();
            HapusJalurPenerimaan();
        } else if (konfirm == 'N' || konfirm == 'n'){
            CleanKanan();
            CleanTengah();
            MasterJalurPenerimaan();
        }else{
            CleanKanan();
            goto konfir;
        }
    }

    fclose(ArsJalurPenerimaan);
    fclose(TempJalurPenerimaan);

    // Konfirmasi data yang akan dihapus
    gotoxy(133, 25); printf("  KONFIRMASI PENGHAPUSAN");
    gotoxy(133, 26); printf("  ===============================");
    gotoxy(133, 27); printf("  Yakin hapus data? [Y/N] = [ ]");
    gotoxy(162, 27); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        CleanKanan();
        CleanTengah();
        ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "wb");
        TempJalurPenerimaan = fopen("TempJalurPenerimaan.dat", "rb");

        fread(&Mjalur, sizeof(Mjalur), 1, TempJalurPenerimaan);
        while (!feof(TempJalurPenerimaan)) {
            fwrite(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            fread(&Mjalur, sizeof(Mjalur), 1, TempJalurPenerimaan);
        }
        fclose(ArsJalurPenerimaan);
        fclose(TempJalurPenerimaan);

        MessageBox(NULL, "Data Jalur berhasil dihapus", "INFORMASI", MB_OK | MB_ICONINFORMATION);

        hapus:
        CleanKanan();
        CleanTengah();
        LihatJalurPenerimaan1();

        // Konfirmasi untuk hapus data lagi
        gotoxy(133,20); printf("  KONFIRMASI PENGHAPUSAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin hapus lagi? [Y/N] = [ ]");
        gotoxy(162, 22);getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            CleanKanan();
            CleanTengah();
            HapusJalurPenerimaan();
        } else if (kf == 'n' || kf == 'N') {
            CleanKanan();
            CleanTengah();
            MasterJalurPenerimaan();
        } else {
            CleanKanan();
            CleanTengah();
            goto hapus;
        }
    } else{
        MessageBox(NULL, "Data Jalur batal dihapus","INFORMASI", MB_OK | MB_ICONINFORMATION );
        CleanTengah();
        CleanKanan();
        MasterJalurPenerimaan();
    }
    CleanKanan();
    LihatJalurPenerimaan1();
}

void UbahJalurPenerimaan(){
    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan
    // Deklarasi
    typedef enum {false=0, true=1} boolean;
    int ID, pilihan, pil2, StatusB;
    char nama_jalurB[50];
    float biaya_pendaftaranB;
    boolean found;
    char kf;

    // Algoritma
    fflush(stdin);
    LihatJalurPenerimaan1();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  UPDATE DATA JALUR PENERIMAAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Jalur  : JLR"); getnum(&ID,3);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        MasterJalurPenerimaan();
    }

    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat","rb");
    TempJalurPenerimaan = fopen("TempJalurPenerimaan.dat", "wb");

    found = false;

    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    while((!found) && (!feof(ArsJalurPenerimaan)))
    {
        if(Mjalur.ID == ID){
            found = true;
            break;
        }
        else{
            fwrite(&Mjalur, sizeof(Mjalur), 1, TempJalurPenerimaan);
        }
        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    }

    if(found==true) {
        CleanKanan();
        CleanTengah();
        DesainData();
        // DATA YANG AKAN DIUBAH
        gotoxy(74,19); printf("=====================");
        gotoxy(74,20); printf("|D|A|T|A| |J|A|L|U|R|");
        gotoxy(74,21); printf("=====================");
        gotoxy(64,28); printf(" ID Jalur          :   JLR%.3d",Mjalur.ID);
        gotoxy(64,29); printf(" Nama Jalur        :   %s",Mjalur.nama_jalur);
        gotoxy(64,30); printf(" Biaya Pendaftaran :   Rp. %'.2f",Mjalur.biaya_pendaftaran);
        gotoxy(64,31); printf(" Status            :   %s",StatusJalur[Mjalur.Status]);

        CleanKanan();
        SetColor(241);
        gotoxy(133,20); printf("  PILIHAN MENU UPDATE");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  [1] Nama Jalur");
        gotoxy(133,23); printf("  [2] Biaya Pendaftaran");
        gotoxy(133,24); printf("  [3] Status");
        gotoxy(133,25); printf("  [4] Kembali");

        gotoxy(133,27); printf("  Pilihan [ ]");
        gotoxy(144,27); getnum(&pilihan, 1);
        fflush(stdin);

        gotoxy(133,30); printf("  MASUKKAN DATA UPDATE !!");
        gotoxy(133,31); printf("  ===============================");


        switch (pilihan) {
            case 1:
                gotoxy(133,32);	printf("  Nama : "); getteks(nama_jalurB, 16);
                if (strcmp(nama_jalurB, Mjalur.nama_jalur)==0)
                {
                    MessageBox(NULL, "Nama tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahJalurPenerimaan();
                }
                strcpy(Mjalur.nama_jalur, nama_jalurB);
                fwrite(&Mjalur,sizeof(Mjalur), 1, TempJalurPenerimaan);
                break;
            case 2:
                gotoxy(133,32);	printf("  Biaya Jalur : Rp. "); scanf("%f", &biaya_pendaftaranB);
                if (biaya_pendaftaranB == Mjalur.biaya_pendaftaran) {
                    MessageBox(NULL, "Biaya pendaftaran tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahJalurPenerimaan();
                    break;
                }
                Mjalur.biaya_pendaftaran = biaya_pendaftaranB;
                fwrite(&Mjalur,sizeof(Mjalur), 1, TempJalurPenerimaan);
                break;
            case 3:
                gotoxy(133,33); printf("  PILIHAN STATUS");
                gotoxy(133,34); printf("  [1] Aktif");
                gotoxy(133,35); printf("  [2] Non Aktif");
                gotoxy(133,37); printf("  Pilihan = [ ]");
                gotoxy(146,37); getnum(&pil2, 1);

                switch(pil2)
                {
                    case 1:
                        StatusB = 0; break;
                    case 2:
                        StatusB = 1; break;
                    default:
                        MessageBox(NULL, "Status yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        CleanKanan();
                        UbahJalurPenerimaan();
                        break;
                }
                Mjalur.Status = StatusB;
                fwrite(&Mjalur,sizeof(Mjalur), 1, TempJalurPenerimaan);
                break;
            case 4:
                gotoxy(133,22); printf("               ");
                CleanKanan();
                MasterJalurPenerimaan();
                fwrite(&Mjalur,sizeof(Mjalur), 1, TempJalurPenerimaan);
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CleanKanan();
                gotoxy(139,20); printf("                    ");
                UbahJalurPenerimaan();
                break;
        }
        fread(&Mjalur, sizeof (Mjalur), 1, ArsJalurPenerimaan);
        while (!feof(ArsJalurPenerimaan)){
            fwrite(&Mjalur, sizeof (Mjalur), 1, TempJalurPenerimaan);
            fread(&Mjalur, sizeof (Mjalur), 1, ArsJalurPenerimaan);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    } else{
        MessageBox(NULL, "ID Jalur tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        UbahJalurPenerimaan();
    }
    fclose(ArsJalurPenerimaan);
    fclose(TempJalurPenerimaan);

    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "wb");
    TempJalurPenerimaan = fopen("TempJalurPenerimaan.dat", "rb");

    fread(&Mjalur, sizeof(Mjalur), 1, TempJalurPenerimaan);
    while (!feof(TempJalurPenerimaan)) {
        fwrite(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
        fread(&Mjalur, sizeof(Mjalur), 1, TempJalurPenerimaan);
    }
    fclose(ArsJalurPenerimaan);
    fclose(TempJalurPenerimaan);

    CleanTengah();
    CleanKanan();

    update:
    LihatJalurPenerimaan1();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI UPDATE DATA KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Update lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        UbahJalurPenerimaan();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        MasterJalurPenerimaan();
    }else {
        CleanKanan();
        goto update;
    }
}

void detailJalurPenerimaan(){
    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan
    // Deklarasi
    typedef enum {false=0,true=1}boolean;
    boolean found;
    char kf;
    int ID;

    // Algoritma
    LihatJalurPenerimaan1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  DETAIL DATA JALUR PENERIMAAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Jalur : JLR"); getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        MasterJalurPenerimaan();
    }

    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat","rb");

    found = false;

    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    while((!found)&&(!feof(ArsJalurPenerimaan)))
    {
        if(Mjalur.ID == ID)
        {
            found = true;
            break;
        }
        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    }

    // Jika Data ditemukan
    if (found == true){
        CleanTengah();
        DesainData();
        gotoxy(74,19); printf("=====================");
        gotoxy(74,20); printf("|D|A|T|A| |J|A|L|U|R|");
        gotoxy(74,21); printf("=====================");
        gotoxy(64,28); printf(" ID Jalur          :   JLR%.3d",Mjalur.ID);
        gotoxy(64,29); printf(" Nama Jalur        :   %s",Mjalur.nama_jalur);
        gotoxy(64,30); printf(" Biaya Pendaftaran :   Rp. %'.2f",Mjalur.biaya_pendaftaran);
        gotoxy(64,31); printf(" Status            :   %s",StatusJalur[Mjalur.Status]);
        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&Mjalur, sizeof(Mjalur),1 , ArsJalurPenerimaan);
        fclose(ArsJalurPenerimaan);
    }else {
        MessageBox(NULL, "ID Jalur tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
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
        detailJalurPenerimaan();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        MasterJalurPenerimaan();
    }
    else
    {
        CleanKanan();
        goto carilagi;
    }
}

void HitungJalurPenerimaan(){

    int jumlah=0, aktif=0, nonaktif=0;

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


    // Hitung Data Jalur
    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat","rb");
    fread(&Mjalur, sizeof(Mjalur),1 , ArsJalurPenerimaan);
    while (!feof(ArsJalurPenerimaan))
    {
        jumlah++;
        if (Mjalur.Status==0)
        {
            aktif++;
        }else{
            nonaktif++;
        }

        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    }
    fclose(ArsJalurPenerimaan);
    SetColor(240);
    gotoxy(70,28); printf ("JUMLAH");
    gotoxy(70,30); printf ("AKTIF");
    gotoxy(70,32); printf ("NON AKTIF");
    gotoxy(79,26); printf("DATA JALUR");
    gotoxy(93,28); printf("%d",jumlah);
    gotoxy(93,30); printf("%d",aktif);
    gotoxy(93,32); printf("%d",nonaktif);
    SetColor(241);
}

