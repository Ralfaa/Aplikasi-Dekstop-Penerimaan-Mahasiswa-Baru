#include <windows.h>

// Global Deklarasi
int x,y;

// Prosedur
void MasterTahunAjar();
void TambahTahunAjar();
void LihatTahunAjar();
void LihatTahunAjar1();
void HapusTahunAjar();
void UbahTahunAjar();
void detailTahunAjar();

void MasterTahunAjar(){

    // Deklarasi
    int menu;

    // Algoritma
    CleanKiri();
    CleanTengah();
    CleanKanan();

//    HitungProgramStudi();
    LihatTahunAjar1();

    SetColor(240);
    gotoxy(12,22); printf(" MASTER TAHUN AJAR ");
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
            TambahTahunAjar();
            break;
        case 2:
            LihatTahunAjar();
            break;
        case 3:
            HapusTahunAjar();
            break;
        case 4:
            UbahTahunAjar();
            break;
        case 5:
            detailTahunAjar();
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

void TambahTahunAjar(){
    char tahun_ajaran[50];
    float nominalUkt;
    char banyak_pendaftar[50];
    char jumlah_diterima[50];

    char jawaban;

    // Algoritma
    fflush(stdin);
    CleanTengah();
    CleanKanan();
    LihatTahunAjar1();
    gotoxy(133,44); printf("  Ketik apapun untuk lanjut");
    getch();

    TahunAJar:
    CleanTengah();
    CleanKanan();
    gotoxy(140,20); printf("             ");
    DesainData();

    ArsTahunAjar = fopen("FileTahunAjar.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsTahunAjar))
    {
        fread(&MTahunAjar, sizeof(MTahunAjar),1 , ArsTahunAjar);
    }
    MTahunAjar.ID++;

    gotoxy(67,19); printf("===================================");
    gotoxy(67,20); printf("|T|A|M|B|A|H| |T|A|H|U|N| |A|J|A|R|");
    gotoxy(67,21); printf("===================================");
    gotoxy(65,26); printf(" ID Tahun Ajaran    : TAJ%.3d\n", MTahunAjar.ID);
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);

    gotoxy(65,27); printf(" Tahun Ajaran       : "); fflush(stdin); getteks(tahun_ajaran, 50);
    gotoxy(65,28); printf(" Nominal Ukt        : Rp. "); fflush(stdin); scanf("%f", &nominalUkt);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (strcmp(tahun_ajaran, "0")==0){
        CleanKanan();
        MasterTahunAjar();
    }
    // Jika Nama Tahun Ajaran sudah ada, maka akan mengulang
    ArsTahunAjar1 = fopen("FileTahunAjar.dat", "rb");

    while (fread(&MTahunAjar1, sizeof(MTahunAjar1), 1, ArsTahunAjar1)==1)
    {
        if (strcmp(MTahunAjar1.tahun_ajaran, tahun_ajaran)==0)
        {
            MessageBox(NULL, "Data Sudah Ada, Data tidak boleh sama !!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            goto TahunAJar;
        }
    }
    fclose(ArsTahunAjar);
    // jika tidak sama maka bisa lanjut

    ArsTahunAjar = fopen("FileTahunAjar.dat", "ab+");
    strcpy(MTahunAjar.tahun_ajaran, tahun_ajaran);
    MTahunAjar.NominalUkt = nominalUkt;
    MTahunAjar.status = 0;

    fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    fclose(ArsTahunAjar);

    CleanKanan();

    // Untuk Konfirmasi menambahkan data
    konfir:
    LihatTahunAjar1();
    CleanKanan();
    gotoxy(133,20); printf("  KONFIRMASI TAMBAH TAHUN AJARAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Tambah lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&jawaban,1);
    if (jawaban=='y' || jawaban=='Y'){
        CleanKanan();
        CleanTengah();
        TambahTahunAjar();
    }else if(jawaban=='n' || jawaban=='N'){
        CleanKanan();
        CleanTengah();
        MasterTahunAjar();
    }else{
        CleanKanan();
        CleanTengah();
        goto konfir;
    }
}

void LihatTahunAjar(){
    setlocale(LC_NUMERIC, "");  // Mengaktifkan pengaturan lokal untuk pemisah ribuan
    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsTahunAjar = fopen("FileTahunAjar.dat","rb");

    // Jika Data Tahun Ajaran Kosong
    if(ArsTahunAjar == NULL)
    {
        SetColor(240);
        MessageBox(NULL, "Data Tahun Ajaran masih kosong!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(65,44); printf("Klik apa saja untuk kembali ke menu utama... "); getch();
        MasterTahunAjar();
    }else {

        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15); printf("%c", 205);
            gotoxy(x, 17); printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-10s | %-15s | %-14s | %-10s","ID TAJ", "Tahun Ajaran", "Pendaftar", "Jumlah Diterima", "Nominal Ukt", "Status");
        while (!feof(ArsTahunAjar)) {
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
            printf(" TAJ%.3d | %-12s | %-10d | %-15d | RP. %'10.2f | %-10s ",
                   MTahunAjar.ID,
                   MTahunAjar.tahun_ajaran,
                   MTahunAjar.banyak_pendaftar,
                   MTahunAjar.jumlah_diterima,
                   MTahunAjar.NominalUkt,
                   StatusTahunAjaran[MTahunAjar.status]);
            SetColor(241);
            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-10s | %-15s | %-14s | %-10s","ID TAJ", "Tahun Ajaran", "Pendaftar", "Jumlah Diterima", "Nominal Ukt", "Status");
            }
        }

        fclose(ArsTahunAjar);
        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            MasterTahunAjar();
            getch();
        } else {
            LihatTahunAjar();
        }
    }
}

void LihatTahunAjar1() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsTahunAjar = fopen("FileTahunAjar.dat","rb");

    // Jika Data Tahun Ajaran Kosong
    if(ArsTahunAjar == NULL)
    {
        SetColor(240);
        MessageBox(NULL, "Data Tahun Ajaran masih kosong!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(65,44); printf("Klik apa saja untuk kembali ke menu utama... "); getch();
        MasterTahunAjar();
    }else {

        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15); printf("%c", 205);
            gotoxy(x, 17); printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-10s | %-15s | %-14s | %-10s","ID TAJ", "Tahun Ajaran", "Pendaftar", "Jumlah Diterima", "Nominal Ukt", "Status");
        while (!feof(ArsTahunAjar)) {
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
            printf(" TAJ%.3d | %-12s | %-10d | %-15d | RP. %'10.2f | %-10s ",
                   MTahunAjar.ID,
                   MTahunAjar.tahun_ajaran,
                   MTahunAjar.banyak_pendaftar,
                   MTahunAjar.jumlah_diterima,
                   MTahunAjar.NominalUkt,
                   StatusTahunAjaran[MTahunAjar.status]);
            SetColor(241);
            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-10s | %-15s | %-14s | %-10s","ID TAJ", "Tahun Ajaran", "Pendaftar", "Jumlah Diterima", "Nominal Ukt", "Status");
            }
        }

        fclose(ArsTahunAjar);
        SetColor(252);
    }
}


void LihatTahunAjar2() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

    // Jika Data Tahun Ajaran Kosong
    if (ArsTahunAjar == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Tahun Ajaran masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterTahunAjar();
    } else {

        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-19s | %-10s","ID TAJ", "Tahun Ajaran", "Nominal Ukt", "Status");
        while (!feof(ArsTahunAjar)) {
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
            printf(" TAJ%.3d | %-15s | Rp. %'15.2f | %-10s ",
                   MTahunAjar.ID,
                   MTahunAjar.tahun_ajaran,
                   MTahunAjar.NominalUkt,
                   StatusTahunAjaran[MTahunAjar.status]);
            SetColor(241);

            fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-19s | %-10s","ID TAJ", "Tahun Ajaran", "Nominal Ukt", "Status");
            }
        }
        fclose(ArsTahunAjar);
        SetColor(252);
    }
}


void HapusTahunAjar() {

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
    LihatTahunAjar1();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133, 44);
    printf(" Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  HAPUS DATA JABATAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Tahun Ajar : TAJ"); getnum(&ID,3);
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        MasterTahunAjar();
    }

    ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");
    TempTahunAjar = fopen("TempTahunAjar.dat", "wb");

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    found = false;

    while((!found) && (!feof(ArsTahunAjar)))
    {
        if(MTahunAjar.ID == ID) {
            found = true;
            break;
        }
        else {
            fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
        }
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    }

    if (found == true) {

        if (MTahunAjar.status== 0) {
            MessageBox(NULL, "Tahun Ajaran Ini Masih Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanKanan();
            MasterTahunAjar();
        }else if (MTahunAjar.status !=0) {
            CleanTengah();
            DesainData();
            gotoxy(67, 19); printf("==================================");
            gotoxy(67, 20); printf("|D|A|T|A| |T|A|H|U|N| |A|J|A|R|A|N|");
            gotoxy(67, 21); printf("===================================");
            gotoxy(69, 28); printf(" ID Tahun Ajaran :   TAJ%.3d", MTahunAjar.ID);
            gotoxy(69, 29); printf(" Tahun Ajaran    :   %s", MTahunAjar.tahun_ajaran);
            gotoxy(69, 30); printf(" Banyak Pendaftar:   %d", MTahunAjar.banyak_pendaftar);
            gotoxy(69, 31); printf(" Jumlah Diterima :   %d", MTahunAjar.jumlah_diterima);
            gotoxy(69, 32); printf(" Status          :   %s", StatusTahunAjaran[MTahunAjar.status]);
            gotoxy(133, 44); printf("                           ");
            fflush(stdin);
        }

        fread(&MTahunAjar,sizeof(MTahunAjar), 1, ArsTahunAjar);
        while(!feof(ArsTahunAjar))
        {
            fwrite(&MTahunAjar,sizeof(MTahunAjar), 1, TempTahunAjar);
            fread(&MTahunAjar,sizeof(MTahunAjar), 1, ArsTahunAjar);
        }

    } else {
        MessageBox(NULL, "ID Tahun AJaran tidak ditemukan di arsip", "PERINGATAN", MB_OK | MB_ICONWARNING);
        konfir :
        CleanKanan();
        gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
        gotoxy(161, 22); getteks(&konfirm, 1);
        if (konfirm == 'y' || konfirm == 'Y') {
            CleanKanan();
            HapusTahunAjar();
        } else if (konfirm == 'N' || konfirm == 'n'){
            CleanKanan();
            CleanTengah();
            MasterTahunAjar();
        }else{
            CleanKanan();
            goto konfir;
        }
    }

    fclose(ArsTahunAjar);
    fclose(TempTahunAjar);

    // Konfirmasi data yang akan dihapus
    // Konfirmasi data yang akan dihapus
    gotoxy(133, 25); printf("  KONFIRMASI PENGHAPUSAN");
    gotoxy(133, 26); printf("  ===============================");
    gotoxy(133, 27); printf("  Yakin hapus data? [Y/N] = [ ]");
    gotoxy(162, 27); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        CleanKanan();
        CleanTengah();
        ArsTahunAjar = fopen("FileTahunAjar.dat", "wb");
        TempTahunAjar = fopen("TempTahunAjar.dat", "rb");

        fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
        while (!feof(TempTahunAjar)) {
            fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
            fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
        }
        fclose(ArsTahunAjar);
        fclose(TempTahunAjar);

        MessageBox(NULL, "Data Tahun Ajaran berhasil dihapus", "INFORMASI", MB_OK | MB_ICONINFORMATION);

        hapus:
        LihatTahunAjar1();

        // Konfirmasi untuk hapus data lagi
        gotoxy(133,20); printf("  KONFIRMASI PENGHAPUSAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin hapus lagi? [Y/N] = [ ]");
        gotoxy(162, 22);getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            CleanKanan();
            CleanTengah();
            HapusTahunAjar();
        } else if (kf == 'n' || kf == 'N') {
            CleanKanan();
            CleanTengah();
            MasterTahunAjar();
        } else {
            CleanKanan();
            CleanTengah();
            goto hapus;
        }
    } else{
        MessageBox(NULL, "Data Tahun Ajaran batal dihapus","INFORMASI", MB_OK | MB_ICONINFORMATION );
        CleanTengah();
        CleanKanan();
        MasterTahunAjar();
    }
    CleanKanan();
    LihatTahunAjar1();
}

void UbahTahunAjar(){

    // Deklarasi
    typedef enum {false=0, true=1} boolean;
    int ID, pilihan, pil2, StatusB;
    char tahun_ajaranB[50];
    char banyak_pendaftarB[50];
    char jumlahDiterimaB[20];
    boolean found;
    char kf;

    // Algoritma
    fflush(stdin);
    LihatTahunAjar1();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  UPDATE DATA TAHUN AJARAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Tahun Ajaran : TAJ"); getnum(&ID,3);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        MasterTahunAjar();
    }

    ArsTahunAjar = fopen("FileTahunAjar.dat","rb");
    TempTahunAjar = fopen("TempTahunAjar.dat", "wb");

    found = false;

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    while((!found) && (!feof(ArsTahunAjar)))
    {
        if(MTahunAjar.ID == ID){
            found = true;
            break;
        }
        else{
            fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
        }
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    }

    if(found==true) {
        CleanKanan();
        CleanTengah();
        DesainData();
        // DATA YANG AKAN DIUBAH
        gotoxy(67,19); printf("===================================");
        gotoxy(67,20); printf("|D|A|T|A| |T|A|H|U|N| |A|J|A|R|A|N|");
        gotoxy(67,21); printf("===================================");
        gotoxy(69,28); printf(" ID Tahun Ajaran  :   TAJ%.3d",MTahunAjar.ID);
        gotoxy(69,29); printf(" Tahun Ajaran     :   %s",MTahunAjar.tahun_ajaran);
        gotoxy(69,30); printf(" Banyak Pendaftar :   %d",MTahunAjar.banyak_pendaftar);
        gotoxy(69,31); printf(" Jumlah Diterima  :   %d",MTahunAjar.jumlah_diterima);
        gotoxy(69,32); printf(" Status           :   %s", StatusTahunAjaran[MTahunAjar.status]);

        CleanKanan();
        SetColor(241);
        gotoxy(139,20); printf("  PILIHAN MENU UPDATE");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  [1] Tahun Ajaran");
        gotoxy(133,23); printf("  [2] Status");
        gotoxy(133,24); printf("  [3] Kembali");

        gotoxy(133,26); printf("  Pilihan = [ ]");
        gotoxy(146,26); getnum(&pilihan, 1);
        fflush(stdin);

        gotoxy(133,29); printf("  MASUKKAN DATA UPDATE !!");
        gotoxy(133,30); printf("  ===============================");

        switch (pilihan) {
            case 1:
                gotoxy(133,31);	printf("  Tahun Ajaran : "); getteks(tahun_ajaranB, 16);
                if (strcmp(tahun_ajaranB, MTahunAjar.tahun_ajaran)==0)
                {
                    MessageBox(NULL, "Nama tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahTahunAjar();
                }
                strcpy(MTahunAjar.tahun_ajaran, tahun_ajaranB);
                fwrite(&MTahunAjar,sizeof(MTahunAjar), 1, TempTahunAjar);
                break;
            case 2:
                gotoxy(133,32); printf("  PILIHAN STATUS");
                gotoxy(133,33); printf("  [1] Aktif");
                gotoxy(133,34); printf("  [2] Non Aktif");
                gotoxy(133,36); printf("  Pilihan = [ ]");
                gotoxy(146,36); getnum(&pil2, 1);

                switch(pil2)
                {
                    case 1:
                        StatusB = 0; break;

                    case 2:
                        StatusB = 1; break;

                    default:
                        MessageBox(NULL, "Status yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        CleanKanan();
                        UbahTahunAjar();
                        break;
                }
                MTahunAjar.status = StatusB;
                fwrite(&MTahunAjar,sizeof(MTahunAjar), 1, TempTahunAjar);
                break;
            case 3:
                gotoxy(133,22); printf("               ");
                CleanKanan();
                MasterTahunAjar();
                fwrite(&MTahunAjar,sizeof(MTahunAjar), 1, TempTahunAjar);
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CleanKanan();
                gotoxy(139,20); printf("                    ");
                UbahTahunAjar();
                break;
        }
        fread(&MTahunAjar, sizeof (MTahunAjar), 1, ArsTahunAjar);
        while (!feof(ArsTahunAjar)){
            fwrite(&MTahunAjar, sizeof (MTahunAjar), 1, TempTahunAjar);
            fread(&MTahunAjar, sizeof (MTahunAjar), 1, ArsTahunAjar);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    } else{
        MessageBox(NULL, "ID Tahun Ajaran tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        UbahTahunAjar();
    }
    fclose(ArsTahunAjar);
    fclose(TempTahunAjar);

    ArsTahunAjar = fopen("FileTahunAjar.dat", "wb");
    TempTahunAjar = fopen("TempTahunAjar.dat", "rb");

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
    while (!feof(TempTahunAjar)) {
        fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
    }
    fclose(ArsTahunAjar);
    fclose(TempTahunAjar);

    CleanTengah();
    CleanKanan();

    update:
    LihatTahunAjar1();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI UPDATE DATA KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Update lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        UbahTahunAjar();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        MasterTahunAjar();
    }else {
        CleanKanan();
        goto update;
    }
}

void detailTahunAjar(){

    // Deklarasi
    typedef enum {false=0,true=1}boolean;
    boolean found;
    char kf;
    int ID;

    // Algoritma
    LihatTahunAjar1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  DETAIL DATA PROGRAM STUDI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Tahun Ajar : TAJ"); getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        MasterTahunAjar();
    }

    ArsTahunAjar = fopen("FileTahunAjar.dat","rb");

    found = false;

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    while((!found)&&(!feof(ArsTahunAjar)))
    {
        if(MTahunAjar.ID == ID)
        {
            found = true;
            break;
        }
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    }

    // Jika Data ditemukan
    if (found == true){
        CleanTengah();
        DesainData();
        gotoxy(67,19); printf("===================================");
        gotoxy(67,20); printf("|D|A|T|A| |T|A|H|U|N| |A|J|A|R|A|N|");
        gotoxy(67,21); printf("===================================");
        gotoxy(69,28); printf(" ID Tahun Ajaran    :   TAJ%.3d",MTahunAjar.ID);
        gotoxy(69,29); printf(" Tahun Ajaran       :   %s",MTahunAjar.tahun_ajaran);
        gotoxy(69,30); printf(" Banyak Pendaftar   :   %d",MTahunAjar.banyak_pendaftar);
        gotoxy(69,31); printf(" Jumlah Diterima    :   %d",MTahunAjar.jumlah_diterima);
        gotoxy(69,32); printf(" Status             :   %s", StatusTahunAjaran[MTahunAjar.status]);
        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&MTahunAjar, sizeof(MTahunAjar),1 , ArsTahunAjar);
        fclose(ArsTahunAjar);
    }else {
        MessageBox(NULL, "ID Tahun Ajaran tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
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
        detailTahunAjar();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        MasterTahunAjar();
    }
    else
    {
        CleanKanan();
        goto carilagi;
    }
}

