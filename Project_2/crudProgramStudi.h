#include <windows.h>

// Global Deklarasi
int x,y;

// Prosedur
void MasterProgramStudi();
void TambahProgramStudi();
void LihatProgramStudi();
void LihatProgramStudi1();
void HapusProgramStudi();
void UbahProgramStudi();
void detailProgramStudi();
void HitungProgramStudi();
void LihatProgramStudi2();
void LihatProgramStudi3();
void LihatProgramStudi4();


void MasterProgramStudi(){

    // Deklarasi
    int menu;

    // Algoritma
    CleanKiri();
    CleanTengah();
    CleanKanan();

    HitungProgramStudi();

    SetColor(240);
    gotoxy(15,22); printf(" MASTER PRODI ");
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
            TambahProgramStudi();
            break;
        case 2:
            LihatProgramStudi();
            break;
        case 3:
            HapusProgramStudi();
            break;
        case 4:
            UbahProgramStudi();
            break;
        case 5:
            detailProgramStudi();
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

void TambahProgramStudi(){
    char nama_prodi[50];
    char nama_singkat[10];
    int kuota;
    char tahun_berdiri[50];

    char jawaban;

    // Algoritma
    fflush(stdin);
    CleanTengah();
    CleanKanan();
    LihatProgramStudi1();
    gotoxy(133,44); printf("  Ketik apapun untuk lanjut");
    getch();

    prodi:
    CleanTengah();
    CleanKanan();
    gotoxy(140,20); printf("             ");
    DesainData();

    ArsProgramStudi = fopen("FileProgramStudi.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsProgramStudi))
    {
        fread(&Mprodi, sizeof(Mprodi),1 , ArsProgramStudi);
    }
    Mprodi.ID++;

    gotoxy(72,19); printf("=========================");
    gotoxy(72,20); printf("|T|A|M|B|A|H| |P|R|O|D|I|");
    gotoxy(72,21); printf("=========================");

    gotoxy(60,26); printf(" ID Prodi           : PRD%.3d\n", Mprodi.ID);
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);

    gotoxy(60,27); printf(" Nama Prodi         : "); fflush(stdin); getteks(nama_prodi, 50);
    gotoxy(60,28); printf(" Nama Singkatan     : "); fflush(stdin); getteks(nama_singkat, 3);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (strcmp(nama_prodi, "0")==0){
        CleanKanan();
        MasterProgramStudi();
    }
    // Jika Nama Program Studi sudah ada, maka akan mengulang
    ArsProgramStudi1 = fopen("FileProgramStudi.dat", "rb");

    while (fread(&Mprodi1, sizeof(Mprodi1), 1, ArsProgramStudi1)==1)
    {
        if (strcmp(Mprodi1.nama_prodi, nama_prodi)==0)
        {
            MessageBox(NULL, "Data tidak boleh sama"," perhatian",MB_OK);
            goto prodi;
        }
    }
    fclose(ArsProgramStudi);

    // jika tidak sama maka bisa lanjut
    gotoxy(60,29);  printf(" Kuota              : "); fflush(stdin); scanf("%d", &kuota);
    gotoxy(60,30);  printf(" Tahun Berdiri      : "); fflush(stdin); getteksnum(tahun_berdiri, 4);

    ArsProgramStudi = fopen("FileProgramStudi.dat", "ab+");
    strcpy(Mprodi.nama_prodi, nama_prodi);
    strcpy(Mprodi.nama_singkat, nama_singkat);
    Mprodi.kuota = kuota;
    Mprodi.status = 0;
    Mprodi.kuotasisa = Mprodi.kuota;
    strcpy(Mprodi.tahun_berdiri, tahun_berdiri);

    fwrite(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    fclose(ArsProgramStudi);

    CleanKanan();

    // Untuk Konfirmasi menambahkan data
    konfir:
    LihatProgramStudi1();
    gotoxy(133,20); printf("  KONFIRMASI TAMBAH PROGRAM STUDI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Tambah lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&jawaban,1);
    if (jawaban=='y' || jawaban == 'Y'){
        CleanKanan();
        CleanTengah();
        TambahProgramStudi();
    }else if(jawaban=='n' || jawaban == 'N'){
        CleanKanan();
        CleanTengah();
        MasterProgramStudi();
    }else{
        CleanKanan();
        CleanTengah();
        goto konfir;
    }
}

void LihatProgramStudi(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsProgramStudi = fopen("FileProgramStudi.dat","rb");

    // Jika Data Program Studi Kosong
    if(ArsProgramStudi == NULL)
    {
        SetColor(240);
        MessageBox(NULL, "Data Program Studi masih kosong!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(65,44); printf("Klik apa saja untuk kembali ke menu utama... "); getch();
        MasterProgramStudi();
    }else {

        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15); printf("%c", 205);
            gotoxy(x, 17); printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-10s | %-15s | %-10s | %-10s |","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota");
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
            printf(" PRD%.3d | %-15s | %10d | %-15s | %-10s | %10d |",
                   Mprodi.ID,
                   Mprodi.nama_singkat,
                   Mprodi.kuota,
                   Mprodi.tahun_berdiri,
                   StatusProdi[Mprodi.status],
                   Mprodi.kuotasisa);
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
                    gotoxy(x, 15);
                    printf("%c", 205);
                    gotoxy(x, 17);
                    printf("%c", 205);
                }
                SetColor(241);
                gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-10s | %-15s | %-10s | %-10s |","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota");
            }
        }

        fclose(ArsProgramStudi);
        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            MasterProgramStudi();
            getch();
        } else {
            LihatProgramStudi();
        }
    }
}

void LihatProgramStudi1() {

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

        gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-10s | %-15s | %-10s | %-10s |","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota");
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
            printf(" PRD%.3d | %-15s | %10d | %-15s | %-10s | %10d |",
                   Mprodi.ID,
                   Mprodi.nama_singkat,
                   Mprodi.kuota,
                   Mprodi.tahun_berdiri,
                   StatusProdi[Mprodi.status],
                   Mprodi.kuotasisa);
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
                gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-10s | %-15s | %-10s | %-10s ","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota");
            }
        }
        fclose(ArsProgramStudi);
        SetColor(252);
    }
}

void HapusProgramStudi() {

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
    LihatProgramStudi1();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  HAPUS DATA PROGRAM STUDI");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Prodi  : PRD"); getnum(&ID,3);
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        MasterProgramStudi();
    }

    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    TempProgramStudi = fopen("TempProgramStudi.dat", "wb");

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    found = false;

    while((!found) && (!feof(ArsProgramStudi)))
    {
        if(Mprodi.ID == ID) {
            found = true;
            break;
        }
        else {
            fwrite(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    if (found == true) {

        if (Mprodi.status== 0) {
            MessageBox(NULL, "Program Studi Ini Masih Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanKanan();
            MasterProgramStudi();
        }else if(Mprodi.status !=0) {
            CleanTengah();
            DesainData();
            gotoxy(73,19); printf("=====================");
            gotoxy(73,20); printf("|D|A|T|A| |P|R|O|D|I|");
            gotoxy(73,21); printf("=====================");
            gotoxy(60,26); printf(" ID Prodi        : PRD%.3d",Mprodi.ID);
            gotoxy(60,27); printf(" Nama Prodi      : %s",Mprodi.nama_prodi);
            gotoxy(60,28); printf(" Kuota Prodi     : %d",Mprodi.kuota);
            gotoxy(60,29); printf(" Tahun Berdiri   : %s",Mprodi.tahun_berdiri);
            gotoxy(60,30); printf(" Status          : %s",StatusProdi[Mprodi.status]);
            gotoxy(60,31); printf(" Passing Grade 1 : %.2f", Mprodi.psg1);
            gotoxy(60,32); printf(" Passing Grade 3 : %.2f", Mprodi.psg2);
            gotoxy(60,33); printf(" Passing Grade 3 : %.2f", Mprodi.psg3);
            gotoxy(133,44); printf("                           ");
            fflush(stdin);
        }

        fread(&Mprodi,sizeof(Mprodi), 1, ArsProgramStudi);
        while(!feof(ArsProgramStudi))
        {
            fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
            fread(&Mprodi,sizeof(Mprodi), 1, ArsProgramStudi);
        }

    } else {
        MessageBox(NULL, "ID Prodi tidak ditemukan di arsip", "PERINGATAN", MB_OK | MB_ICONWARNING);
        konfir:
        CleanKanan();
        gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
        gotoxy(161, 22); getteks(&konfirm, 1);
        if (konfirm == 'y' || konfirm == 'Y') {
            CleanKanan();
            HapusProgramStudi();
        } else if (konfirm == 'N' || konfirm == 'n'){
            CleanKanan();
            CleanTengah();
            MasterProgramStudi();
        }else{
            CleanKanan();
            goto konfir;
        }
    }

    fclose(ArsProgramStudi);
    fclose(TempProgramStudi);

    // Konfirmasi data yang akan dihapus
    gotoxy(133, 25); printf("  KONFIRMASI PENGHAPUSAN");
    gotoxy(133, 26); printf("  ===============================");
    gotoxy(133, 27); printf("  Yakin hapus data? [Y/N] = [ ]");
    gotoxy(162, 27); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        CleanKanan();
        CleanTengah();
        ArsProgramStudi = fopen("FileProgramStudi.dat", "wb");
        TempProgramStudi = fopen("TempProgramStudi.dat", "rb");

        fread(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
        while (!feof(TempProgramStudi)) {
            fwrite(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
            fread(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
        }
        fclose(ArsProgramStudi);
        fclose(TempProgramStudi);

        MessageBox(NULL, "Data Program Studi berhasil dihapus", "INFORMASI", MB_OK | MB_ICONINFORMATION);

        hapus:
        CleanKanan();
        CleanTengah();
        LihatProgramStudi1();

        // Konfirmasi untuk hapus data lagi
        gotoxy(133,20); printf("  KONFIRMASI PENGHAPUSAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin hapus lagi? [Y/N] = [ ]");
        gotoxy(162, 22);getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            CleanKanan();
            CleanTengah();
            HapusProgramStudi();
        } else if (kf == 'n' || kf == 'N') {
            CleanKanan();
            CleanTengah();
            MasterProgramStudi();
        } else {
            CleanKanan();
            CleanTengah();
            goto hapus;
        }
    } else{
        MessageBox(NULL, "Data Program Studi batal dihapus","INFORMASI", MB_OK | MB_ICONINFORMATION );
        CleanTengah();
        CleanKanan();
        MasterProgramStudi();
    }
    CleanKanan();
    LihatProgramStudi1();
}

void UbahProgramStudi(){

    // Deklarasi
    typedef enum {false=0, true=1} boolean;
    int ID, pilihan, pil2, StatusB;
    char nama_prodiB[50];
    char nama_singkatanB[50];
    int kuotaB;
    char tahun_berdiriB[20];
    boolean found;
    char kf;

    // Algoritma
    fflush(stdin);
    LihatProgramStudi1();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  UPDATE DATA PROGRAM STUDI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Prodi  : PRD"); getnum(&ID,3);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        MasterProgramStudi();
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

    if(found==true) {
        CleanKanan();
        CleanTengah();
        DesainData();
        // DATA YANG AKAN DIUBAH
        gotoxy(73,19); printf("=====================");
        gotoxy(73,20); printf("|D|A|T|A| |P|R|O|D|I|");
        gotoxy(73,21); printf("=====================");
        gotoxy(69,28); printf(" ID Prodi      :   PRD%.3d",Mprodi.ID);
        gotoxy(69,29); printf(" Nama Prodi    :   %s",Mprodi.nama_prodi);
        gotoxy(69,30); printf(" Nama Singkat  :   %s",Mprodi.nama_singkat);
        gotoxy(69,31); printf(" Kuota Prodi   :   %d",Mprodi.kuota);
        gotoxy(69,32); printf(" Tahun Berdiri :   %s",Mprodi.tahun_berdiri);
        gotoxy(69,33); printf(" Status        :   %s",StatusProdi[Mprodi.status]);

        CleanKanan();
        SetColor(241);
        gotoxy(133,20); printf("  PILIHAN MENU UPDATE");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  [1] Nama Prodi");
        gotoxy(133,23); printf("  [2] Nama Singkatan");
        gotoxy(133,24); printf("  [3] Kuota Prodi");
        gotoxy(133,25); printf("  [4] Tahun Berdiri");
        gotoxy(133,26); printf("  [5] Status");
        gotoxy(133,27); printf("  [6] Kembali");

        gotoxy(133,29); printf("  Pilihan = [ ]");
        gotoxy(146,29); getnum(&pilihan, 1);
        fflush(stdin);

        gotoxy(133,32); printf("  MASUKKAN DATA UPDATE !!");
        gotoxy(133,33); printf("  ===============================");

        switch (pilihan) {
            case 1:
                gotoxy(133,34);	printf("  Nama Prodi : "); getteks(nama_prodiB, 16);
                if (strcmp(nama_prodiB, Mprodi.nama_prodi)==0)
                {
                    MessageBox(NULL, "Nama tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahProgramStudi();
                }
                strcpy(Mprodi.nama_prodi, nama_prodiB);
                fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
                break;
            case 2:
                gotoxy(133,34);	printf("  Nama Singkatan : "); getteks(nama_singkatanB, 3);
                if (strcmp(nama_singkatanB, Mprodi.nama_singkat)==0)
                {
                    MessageBox(NULL, "Nama tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahProgramStudi();
                }
                strcpy(Mprodi.nama_singkat, nama_singkatanB);
                fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
                break;
            case 3:
                gotoxy(133,34);	printf("  Kuota Prodi : "); scanf("%d", &kuotaB);
                if (Mprodi.kuota == kuotaB) {
                    MessageBox(NULL, "Jenis prodi tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahProgramStudi();
                    break;
                }
                Mprodi.kuota = kuotaB;
                Mprodi.kuotasisa = kuotaB;
                fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
                break;
            case 4:
                gotoxy(133,34);	printf("  Tahun Berdiri : ");  getteksnum(tahun_berdiriB, 4);
                if (strcmp(tahun_berdiriB, Mprodi.tahun_berdiri)==0) {
                    MessageBox(NULL, "Tanggal Pembukaan tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahProgramStudi();
                    break;
                }
                strcpy(Mprodi.tahun_berdiri, tahun_berdiriB);
                fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
                break;
            case 5:
                gotoxy(133,35); printf("  PILIHAN MENU STATUS");
                gotoxy(133,36); printf("  [1] Aktif");
                gotoxy(133,37); printf("  [2] Non Aktif");
                gotoxy(133,39); printf("  Pilihan = [ ]");
                gotoxy(146,39); getnum(&pil2, 1);

                switch(pil2)
                {
                    case 1:
                        StatusB = 0; break;

                    case 2:
                        StatusB = 1; break;

                    default:
                        MessageBox(NULL, "Status yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        CleanKanan();
                        UbahProgramStudi();
                        break;
                }
                Mprodi.status = StatusB;
                fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
                break;
            case 6:
                gotoxy(133,22); printf("               ");
                CleanKanan();
                MasterProgramStudi();
                fwrite(&Mprodi,sizeof(Mprodi), 1, TempProgramStudi);
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CleanKanan();
                gotoxy(139,20); printf("                    ");
                UbahProgramStudi();
                break;
        }
        fread(&Mprodi, sizeof (Mprodi), 1, ArsProgramStudi);
        while (!feof(ArsProgramStudi)){
            fwrite(&Mprodi, sizeof (Mprodi), 1, TempProgramStudi);
            fread(&Mprodi, sizeof (Mprodi), 1, ArsProgramStudi);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    } else{
        MessageBox(NULL, "ID Prodi tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        UbahProgramStudi();
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

    CleanTengah();
    CleanKanan();

    update:
    LihatProgramStudi1();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI UPDATE DATA KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Update lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        UbahProgramStudi();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        MasterProgramStudi();
    }else {
        CleanKanan();
        goto update;
    }
}

void detailProgramStudi(){

    // Deklarasi
    typedef enum {false=0,true=1}boolean;
    boolean found;
    char kf;
    int ID;

    // Algoritma
    LihatProgramStudi1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  DETAIL DATA PROGRAM STUDI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Prodi : PRD"); getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        MasterProgramStudi();
    }

    ArsProgramStudi = fopen("FileProgramStudi.dat","rb");

    found = false;

    fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    while((!found)&&(!feof(ArsProgramStudi)))
    {
        if(Mprodi.ID == ID)
        {
            found = true;
            break;
        }
        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    // Jika Data ditemukan
    if (found == true){
        CleanTengah();
        DesainData();
        gotoxy(73,19); printf("=====================");
        gotoxy(73,20); printf("|D|A|T|A| |P|R|O|D|I|");
        gotoxy(73,21); printf("=====================");
        gotoxy(60,26); printf(" ID Prodi        : PRD%.3d",Mprodi.ID);
        gotoxy(60,27); printf(" Nama Prodi      : %s",Mprodi.nama_prodi);
        gotoxy(60,28); printf(" Kuota Prodi     : %d",Mprodi.kuota);
        gotoxy(60,29); printf(" Tahun Berdiri   : %s",Mprodi.tahun_berdiri);
        gotoxy(60,30); printf(" Status          : %s",StatusProdi[Mprodi.status]);
        gotoxy(60,31); printf(" Passing Grade 1 : %.2f", Mprodi.psg1);
        gotoxy(60,32); printf(" Passing Grade 3 : %.2f", Mprodi.psg2);
        gotoxy(60,33); printf(" Passing Grade 3 : %.2f", Mprodi.psg3);
        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&Mprodi, sizeof(Mprodi),1 , ArsProgramStudi);
        fclose(ArsProgramStudi);
    }else {
        MessageBox(NULL, "ID Prodi tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
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
        detailProgramStudi();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        MasterProgramStudi();
    }
    else
    {
        CleanKanan();
        goto carilagi;
    }
}

void HitungProgramStudi(){

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

    // Hitung Data Gelombang
    ArsProgramStudi = fopen("FileProgramStudi.dat","rb");
    fread(&Mprodi, sizeof(Mprodi),1 , ArsProgramStudi);
    while (!feof(ArsProgramStudi))
    {
        jumlah++;
        if (Mprodi.status==0)
        {
            aktif++;
        }else{
            nonaktif++;
        }

        fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }
    fclose(ArsProgramStudi);
    SetColor(240);
    gotoxy(70,28); printf ("JUMLAH");
    gotoxy(70,30); printf ("AKTIF");
    gotoxy(70,32); printf ("NON AKTIF");
    gotoxy(76,26); printf("DATA PROGRAM STUDI");
    gotoxy(93,28); printf("%d",jumlah);
    gotoxy(93,30); printf("%d",aktif);
    gotoxy(93,32); printf("%d",nonaktif);
    SetColor(241);

}


void LihatProgramStudi2() {

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

        gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-5s | %-13s | %-10s | %-10s | %-9s |","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota", "Pendaftar");

        while (!feof(ArsProgramStudi)) {
            int jumlahPendaftarProdi = 0;
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

            ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

            while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Prodi == Mprodi.ID) {
                    jumlahPendaftarProdi++;
                }
            }

            gotoxy(Kolom, Baris);
            printf(" PRD%.3d | %-10s | %5d | %-13s | %-10s | %10d | %9d | ",
                   Mprodi.ID,
                   Mprodi.nama_singkat,
                   Mprodi.kuota,
                   Mprodi.tahun_berdiri,
                   StatusProdi[Mprodi.status],
                   Mprodi.kuotasisa,
                   jumlahPendaftarProdi);
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
                gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-5s | %-13s | %-10s | %-10s | %-10s","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota", "Pendaftar");
            }
        }
        fclose(ArsProgramStudi);
        SetColor(252);
    }
}

void LihatProgramStudi3() {

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

        gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-5s | %-13s | %-10s | %-10s | %-12s |","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota", "Jumlah Lulus");

        while (!feof(ArsProgramStudi)) {
            int jumlahditerima = 0;
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

            ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

            while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
                if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Prodi == Mprodi.ID &&  Trspendaftaran.StatusPendaftaran == 9) {
                    jumlahditerima++;
                }
            }

            gotoxy(Kolom, Baris);
            printf(" PRD%.3d | %-10s | %5d | %-13s | %-10s | %10d | %12d | ",
                   Mprodi.ID,
                   Mprodi.nama_singkat,
                   Mprodi.kuota,
                   Mprodi.tahun_berdiri,
                   StatusProdi[Mprodi.status],
                   Mprodi.kuotasisa,
                   jumlahditerima);
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
                gotoxy(Kolom, 16); printf(" %-6s | %-10s | %-5s | %-13s | %-10s | %-10s | %-12s","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota", "Jumlah Lulus");
            }
        }
        fclose(ArsProgramStudi);
        SetColor(252);
    }
}


void LihatProgramStudi4() {

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

        gotoxy(Kolom, 16); printf(" %-10s | %-30s | %-15s | %-15s |","ID Prd", "Nama Prodi", "Tahun Berdiri", "Status");
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
            printf(" PRD%.7d | %-30s | %-15s | %-15s |",
                   Mprodi.ID,
                   Mprodi.nama_prodi,
                   Mprodi.tahun_berdiri,
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
                gotoxy(Kolom, 16); printf(" %-10s | %-30s | %-15s | %-15s |","ID Prd", "Nama Prodi", "Tahun Berdiri", "Status");
            }
        }
        fclose(ArsProgramStudi);
        SetColor(252);
    }
}

