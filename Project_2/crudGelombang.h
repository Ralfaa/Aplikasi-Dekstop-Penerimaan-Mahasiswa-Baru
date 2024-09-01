#include <windows.h>

// Global Deklarasi
int x,y;

// Prosedur
void MasterGelombang();
void TambahGelombang();
void LihatGelombang();
void LihatGelombang1();
void HapusGelombang();
void UbahGelombang();
void detailGelombang();
void HitungGelombang();

void MasterGelombang(){

    // Deklarasi
    int menu;

    // Algoritma
    CleanKiri();
    CleanTengah();
    CleanKanan();

    HitungGelombang();

    SetColor(240);
    gotoxy(13,22); printf(" MASTER GELOMBANG ");
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
            TambahGelombang();
            break;
        case 2:
            LihatGelombang();
            break;
        case 3:
            HapusGelombang();
            break;
        case 4:
            UbahGelombang();
            break;
        case 5:
            detailGelombang();
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

void TambahGelombang(){
    char nama_gelombang[50];
    int IDterakhir;
    char jawaban;
    Date BukaGel;
    Date TutupGel;
    bool found1 = false;
    bool found2 = false;
    bool found3 = false;
    bool found4 = false;

    // Algoritma
    fflush(stdin);
    CleanTengah();
    CleanKanan();
    LihatGelombang1();
    gotoxy(133,44); printf("  Ketik apapun untuk lanjut");
    getch();

    CleanTengah();
    CleanKanan();
    gotoxy(140,20); printf("             ");
    DesainData();

    ArsGelombang = fopen("FileGelombang.dat", "ab+"); /*Membuka arsip untuk ditambahkan*/

    while(!feof(ArsGelombang))
    {
        fread(&Mgelombang, sizeof(Mgelombang),1 , ArsGelombang);
    }
    Mgelombang.ID++;

    gelombang:
    CleanTengah();
    DesainData();

    gotoxy(68,19); printf("=================================");
    gotoxy(68,20); printf("|T|A|M|B|A|H| |G|E|L|O|M|B|A|N|G|");
    gotoxy(68,21); printf("=================================");

    gotoxy(41,41);  printf(" - Tanggal Pembukaan Gelombang > 10 hari Tanggal Penutupan Gelombang Terakhir ");
    gotoxy(41,42);  printf(" - Tanggal Penutupan Gelombang > 10 hari Tanggal Pembukaan Gelombang ");
    gotoxy(41,43);  printf(" - Tanggal Penutupan Gelombang < 2 bulan Tanggal Pembukaan Gelombang ");
    gotoxy(65,26);  printf(" ID Gelombang      : GEL%.3d\n", Mgelombang.ID);
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);


    gotoxy(65,27); printf(" Nama Gelombang    : "); fflush(stdin); getteks(nama_gelombang, 50);

    // Untuk Kembali ke menu jika tidak jadi menginputkan
    if (strcmp(nama_gelombang, "0")==0){
        CleanKanan();
        MasterGelombang();
    }
    // Jika Nama Gelombang sudah ada, maka akan mengulang
    ArsGelombang1 = fopen("FileGelombang.dat", "rb");

    while (fread(&Mgelombang1, sizeof(Mgelombang1), 1, ArsGelombang1)==1)
    {
        if (strcmp(Mgelombang1.nama_gelombang, nama_gelombang)==0)
        {
            MessageBox(NULL, "Data tidak boleh sama"," perhatian",MB_OK);
            goto gelombang;
        }
    }
    fclose(ArsGelombang1);

    // jika tidak sama maka bisa lanjut
    ArsGelombang1 = fopen("FileGelombang.dat", "rb");

    gotoxy(65,28);  printf(" Tanggal Pembukaan : "); fflush(stdin);
    getnum(&BukaGel.tgl, 2); printf(" / ");
    getnum(&BukaGel.bulan, 2); printf(" / ");
    getnum(&BukaGel.tahun, 4);

    IDterakhir = Mgelombang.ID - 1;

    if(IDterakhir == 0 ){
        found1 = true;
    }else {
        ArsGelombang1 = fopen("FileGelombang.dat", "rb");
        while (fread(&Mgelombang1, sizeof(Mgelombang1), 1, ArsGelombang1) == 1) {
            if (Mgelombang1.ID == IDterakhir) {
                int selisihHari = (BukaGel.tahun - Mgelombang1.tutupGel.tahun) * 365 +
                                  (BukaGel.bulan - Mgelombang1.tutupGel.bulan) * 30 +
                                  (BukaGel.tgl - Mgelombang1.tutupGel.tgl);

                // Jika selisih hari lebih dari 10, set found1 menjadi true
                if (selisihHari > 10) {
                    found1 = true;
                }
            }
        }
        fclose(ArsGelombang1);
    }

    BukaGel.tgl;
    BukaGel.bulan;
    BukaGel.tahun;

    Mgelombang1.tutupGel.tgl;
    Mgelombang1.tutupGel.bulan;
    Mgelombang1.tutupGel.tahun;


    if(found1 == true){
        if(datevalid(BukaGel)){
            found2 = true;
        }
    }

    if (found2 == true) {
        Mgelombang.bukaGel.tgl = BukaGel.tgl;
        Mgelombang.bukaGel.bulan = BukaGel.bulan;
        Mgelombang.bukaGel.tahun = BukaGel.tahun;

        gotoxy(65, 29);
        printf(" Tanggal Penutupan : ");
        fflush(stdin);
        getnum(&Mgelombang.tutupGel.tgl, 2);
        printf(" / ");
        getnum(&Mgelombang.tutupGel.bulan, 2);
        printf(" / ");
        getnum(&Mgelombang.tutupGel.tahun, 4);

        if (datevalid(Mgelombang.tutupGel)) {
            int selisihHari = (Mgelombang.tutupGel.tahun - Mgelombang.bukaGel.tahun) * 365 +
                              (Mgelombang.tutupGel.bulan - Mgelombang.bukaGel.bulan) * 30 +
                              (Mgelombang.tutupGel.tgl - Mgelombang.bukaGel.tgl);

            // Mengecek apakah selisih hari memenuhi kriteria
            if (selisihHari >= 10 && selisihHari <= 60) {
                found3 = true;
            }
        }
    } else{
        MessageBox(0, "Tanggal Pembukaan Gelombang Tidak Sesuai", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
        goto gelombang;
    }

    if (!found3){
        MessageBox(0, "Tanggal Penutupan Gelombang Tidak Sesuai", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
        goto gelombang;
    }

    ArsGelombang = fopen("FileGelombang.dat", "ab+");
    strcpy(Mgelombang.nama_gelombang, nama_gelombang);
    Mgelombang.status = 0;

    CleanTengah();
    CleanKanan();
    LihatJalurPenerimaan1();

    SetColor(241);
    gotoxy(133, 20); printf("  PILIH JALUR PENERIMAAN");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22);  printf("  Jalur Pendaftaran : JLR"); getnum(&Mgelombang.ID_Jalur, 3);

    // Memanggil Data Jalur Penerimaan
    ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");
    found4 = false;

    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    while(!feof(ArsJalurPenerimaan)) {
        if(Mjalur.ID == Mgelombang.ID_Jalur) {
            found4 = true;
            break;
        }
        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
    }

    if (found4 == true){
        if(Mjalur.Status == 0){
            fwrite(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            fclose(ArsGelombang);
            MessageBox(NULL, "Data Gelombang berhasil ditambahkan!","INFORMASI", MB_OK | MB_ICONINFORMATION);
        }else{
            MessageBox(NULL, "Jalur Penerimaan Tidak Aktif!","PERINGATAN", MB_OK | MB_ICONWARNING );
            CleanTengah();
            CleanKanan();
            TambahGelombang();
        }
    }else{
        MessageBox(NULL, "Jalur Penerimaan Ini Tidak Tersedia!","PERINGATAN", MB_OK | MB_ICONWARNING );
        CleanTengah();
        CleanKanan();
        TambahGelombang();
    }
    fclose(ArsGelombang);
    CleanKanan();
    CleanTengah();

    // Untuk Konfirmasi menambahkan data
    konfir:
    LihatGelombang1();
    SetColor(241);
    gotoxy(133,20); printf("  KONFIRMASI TAMBAH GELOMBANG");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Tambah lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&jawaban,1);
    if (jawaban=='y' || jawaban=='Y'){
        CleanKanan();
        CleanTengah();
        TambahGelombang();
    }else if(jawaban=='n' || jawaban=='N'){
        CleanKanan();
        CleanTengah();
        MasterGelombang();
    }else{
        CleanKanan();
        CleanTengah();
        goto konfir;
    }
}

void LihatGelombang(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found;
    char jawaban;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsGelombang = fopen("FileGelombang.dat","rb");

    // Jika Data Gelombang Kosong
    if(ArsGelombang == NULL)
    {
        SetColor(240);
        MessageBox(NULL, "Data Gelombang masih kosong!","PERINGATAN", MB_OK | MB_ICONWARNING );
        gotoxy(65,44); printf("Klik apa saja untuk kembali ke menu utama... "); getch();
        MasterGelombang();
    }else {

        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15); printf("%c", 205);
            gotoxy(x, 17); printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-15s | %-15s | %-10s","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur Pendaftaran");
        while (!feof(ArsGelombang)) {
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
            printf(" GEL%.3d | %-15s | %.2d-%-.2d-%-9.4d |  %-.2d-%-.2d-%-8.4d |",
                   Mgelombang.ID,
                   Mgelombang.nama_gelombang,
                   Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun,
                   Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            found = false;

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while((!found)&&(!feof(ArsJalurPenerimaan))) {
                if(Mjalur.ID == Mgelombang.ID_Jalur) {
                    found = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }

            if (found == true){
                gotoxy(Kolom + 65, Baris);
                printf("%s", Mjalur.nama_jalur);
            }

            SetColor(241);
            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-15s | %-15s | %-10s","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur Pendaftaran");
            }
        }

        fclose(ArsGelombang);
        SetColor(252);
        gotoxy(133, 20);
        printf("  Ketik 'Y' untuk kembali [ ]");
        gotoxy(160, 20);
        getteks(&jawaban, 1);
        SetColor(241);
        if (jawaban == 'y' || jawaban == 'Y') {
            CleanKanan();
            MasterGelombang();
            getch();
        } else {
            LihatGelombang();
        }
    }
}

void LihatGelombang1() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsGelombang = fopen("FileGelombang.dat", "rb");

    // Jika Data Gelombang Kosong
    if (ArsGelombang == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Gelombang masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterGelombang();
    } else {

        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-15s | %-15s | %-10s","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur Pendaftaran");
        while (!feof(ArsGelombang)) {
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
            printf(" GEL%.3d | %-15s | %.2d-%-.2d-%-9.4d |  %-.2d-%-.2d-%-8.4d |",
                   Mgelombang.ID,
                   Mgelombang.nama_gelombang,
                   Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun,
                   Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            found = false;

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while((!found)&&(!feof(ArsJalurPenerimaan))) {
                if(Mjalur.ID == Mgelombang.ID_Jalur) {
                    found = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }

            if (found == true){
                gotoxy(Kolom + 65, Baris);
                printf("%s", Mjalur.nama_jalur);
            }

            SetColor(241);
            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-15s | %-15s | %-10s","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur Pendaftaran");
            }
        }

        fclose(ArsGelombang);
        SetColor(252);
    }
}

void HapusGelombang() {

    // Deklarasi
    bool found1, found2;
    int ID;
    char konfirm, kf;

    // Algoritma
    CleanTengah();
    CleanKanan();
    LihatGelombang1();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133, 20); printf("  HAPUS DATA GELOMBANG");
    gotoxy(133, 21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Gelombang  : GEL"); getnum(&ID,3);
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        MasterGelombang();
    }

    ArsGelombang = fopen("FileGelombang.dat", "rb");
    TempGelombang = fopen("TempGelombang.dat", "wb");

    fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    found1 = false;

    while((!found1) && (!feof(ArsGelombang)))
    {
        if(Mgelombang.ID == ID) {
            found1 = true;
            break;
        }
        else {
            fwrite(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
        }
        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    }

    if (found1 == true) {

        if (Mgelombang.status == 0) {
            MessageBox(NULL, "Gelombang Ini Masih Aktif!", "PERINGATAN", MB_OK | MB_ICONWARNING);
            CleanKanan();
            MasterGelombang();
        } else if (Mgelombang.status != 1) {
            CleanTengah();
            DesainData();
            gotoxy(68,19); printf("=========================");
            gotoxy(68,20); printf("|D|A|T|A| |G|E|L|O|M|B|A|N|G|");
            gotoxy(68,21); printf("=========================");
            gotoxy(69,28); printf(" ID Gelombang       :   GEL%.3d",Mgelombang.ID);
            gotoxy(69,29); printf(" Nama Gelombang     :   %s",Mgelombang.nama_gelombang);
            gotoxy(69,30); printf(" Tanggal Pembukaan  :   %d / %d / %d",Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun);
            gotoxy(69,31); printf(" Tanggal Penutupan  :   %d / %d / %d ",Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            found2 = false;

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while((!found2)&&(!feof(ArsJalurPenerimaan))) {
                if(Mjalur.ID == Mgelombang.ID_Jalur) {
                    found2 = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }

            if (found2 == true){
                gotoxy(69,32);
                printf(" Jalur Penerimaan   :   %s", Mjalur.nama_jalur);
            }

            gotoxy(69,33); printf(" Status             :   %s",StatusGelombang[Mgelombang.status]);
            gotoxy(133,44); printf("                           ");
            fflush(stdin);
        }

        fread(&Mgelombang,sizeof(Mgelombang), 1, ArsGelombang);
        while(!feof(ArsGelombang))
        {
            fwrite(&Mgelombang,sizeof(Mgelombang), 1, TempGelombang);
            fread(&Mgelombang,sizeof(Mgelombang), 1, ArsGelombang);
        }

    } else {
        MessageBox(NULL, "ID Gelombang tidak ditemukan di arsip", "PERINGATAN", MB_OK | MB_ICONWARNING);
        konfir:
        CleanKanan();
        gotoxy(133,20); printf("  KONFIRMASI PENCARIAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin Cari Lagi? [Y/N] = [ ]");
        gotoxy(161, 22); getteks(&konfirm, 1);
        if (konfirm == 'y' || konfirm == 'Y') {
            CleanKanan();
            HapusGelombang();
        } else if (konfirm == 'N' || konfirm == 'n'){
            CleanKanan();
            CleanTengah();
            MasterGelombang();
        }else{
            CleanKanan();
            goto konfir;
        }
    }

    fclose(ArsGelombang);
    fclose(TempGelombang);

    // Konfirmasi data yang akan dihapus
    gotoxy(133, 25); printf("  KONFIRMASI PENGHAPUSAN");
    gotoxy(133, 26); printf("  ===============================");
    gotoxy(133, 27); printf("  Yakin hapus data? [Y/N] = [ ]");
    gotoxy(162, 27); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        CleanKanan();
        CleanTengah();
        ArsGelombang = fopen("FileGelombang.dat", "wb");
        TempGelombang = fopen("TempGelombang.dat", "rb");

        fread(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
        while (!feof(TempGelombang)) {
            fwrite(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
            fread(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
        }
        fclose(ArsGelombang);
        fclose(TempGelombang);

        MessageBox(NULL, "Data Gelombang berhasil dihapus", "INFORMASI", MB_OK | MB_ICONINFORMATION);

        hapus:
        LihatGelombang1();

        // Konfirmasi untuk hapus data lagi
        gotoxy(133,20); printf("  KONFIRMASI PENGHAPUSAN KEMBALI");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  Ingin hapus lagi? [Y/N] = [ ]");
        gotoxy(162, 22);getteks(&kf, 1);

        if (kf == 'y' || kf == 'Y') {
            CleanKanan();
            CleanTengah();
            HapusGelombang();
        } else if (kf == 'n' || kf == 'N') {
            CleanKanan();
            CleanTengah();
            MasterGelombang();
        } else {
            CleanKanan();
            CleanTengah();
            goto hapus;
        }
    } else{
        MessageBox(NULL, "Data Gelombang batal dihapus","INFORMASI", MB_OK | MB_ICONINFORMATION );
        CleanTengah();
        CleanKanan();
        MasterGelombang();
    }
    CleanKanan();
    LihatGelombang1();
}

void UbahGelombang(){

    // Deklarasi
    typedef enum {false=0, true=1} boolean;
    int ID, pilihan, pil2;
    char nama_gelombangB[50];
    int ID_JalurB;
    int StatusB;
    boolean found, found2, found1, found3;
    char kf;
    Date baru;

    // Algoritma
    found1 = false;
    found = false;
    found2 = false;
    found3 = false;
    fflush(stdin);
    LihatGelombang1();
    gotoxy(139,20); printf("               ");
    CleanKanan();

    // Jika ingin kembali ke menu
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  UPDATE DATA GELOMBANG");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  ID Gelombang  : GEL"); getnum(&ID,3);
    if (ID==0)
    {
        CleanKanan();
        CleanTengah();
        MasterGelombang();
    }

    ArsGelombang = fopen("FileGelombang.dat","rb");
    TempGelombang = fopen("TempGelombang.dat", "wb");

    fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    while((!found) && (!feof(ArsGelombang)))
    {
        if(Mgelombang.ID == ID){
            found = true;
            break;
        }
        else{
            fwrite(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
        }
        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    }

    if(found==true) {
        CleanKanan();
        CleanTengah();
        DesainData();
        // DATA YANG AKAN DIUBAH
        gotoxy(68,19); printf("=============================");
        gotoxy(68,20); printf("|D|A|T|A| |G|E|L|O|M|B|A|N|G|");
        gotoxy(68,21); printf("=============================");
        gotoxy(69,28); printf(" ID Gelombang       :   GEL%.3d",Mgelombang.ID);
        gotoxy(69,29); printf(" Nama Gelombang     :   %s",Mgelombang.nama_gelombang);
        gotoxy(69,30); printf(" Tanggal Pembukaan  :   %d / %d / %d",Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun);
        gotoxy(69,31); printf(" Tanggal Penutupan  :   %d / %d / %d ",Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

        // Memanggil Data Jalur Penerimaan
        ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);

        while((!found2)&&(!feof(ArsJalurPenerimaan))) {
            if(Mjalur.ID == Mgelombang.ID_Jalur) {
                found2 = true;
                break;
            }
            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
        }

        if (found2 == true){
            gotoxy(69,32);
            printf(" Jalur Penerimaan   :   %s", Mjalur.nama_jalur);
        }

        gotoxy(69,33); printf(" Status             :   %s",StatusGelombang[Mgelombang.status]);

        CleanKanan();
        SetColor(241);
        gotoxy(133,20); printf("  PILIHAN MENU UPDATE");
        gotoxy(133,21); printf("  ===============================");
        gotoxy(133,22); printf("  [1] Nama Gelombang");
        gotoxy(133,23); printf("  [2] Jalur Pendaftaran");
        gotoxy(133,24); printf("  [3] Tanggal Penutupan");
        gotoxy(133,25); printf("  [4] Status");
        gotoxy(133,26); printf("  [5] Kembali");

        gotoxy(133,28); printf("  Pilihan [ ]");
        gotoxy(144,28); getnum(&pilihan, 1);
        fflush(stdin);

        gotoxy(133,31); printf("  MASUKKAN DATA UPDATE !!");
        gotoxy(133,32); printf("  ===============================");

        switch (pilihan) {
            case 1:
                gotoxy(133,33);	printf("  Nama : "); getteks(nama_gelombangB, 16);
                if (strcmp(nama_gelombangB, Mgelombang.nama_gelombang)==0)
                {
                    MessageBox(NULL, "Nama tidak boleh sama!","PERINGATAN", MB_OK | MB_ICONWARNING );
                    CleanKanan();
                    UbahGelombang();
                }
                strcpy(Mgelombang.nama_gelombang, nama_gelombangB);
                fwrite(&Mgelombang,sizeof(Mgelombang), 1, TempGelombang);
                break;
            case 2:
                gotoxy(133,33);	printf("  Jalur : "); getnum(&ID_JalurB, 2);

                if (ID_JalurB == Mgelombang.ID_Jalur) {
                    MessageBox(NULL, "Jalur Penerimaan tidak boleh sama!", "PERINGATAN", MB_OK | MB_ICONWARNING);
                    CleanKanan();
                    UbahGelombang();
                }

                // Memanggil Data Jalur Penerimaan
                ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");
                found1 = false;

                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                while((!found1)&&(!feof(ArsJalurPenerimaan))) {
                    if(Mjalur.ID == Mgelombang.ID_Jalur) {
                        found1 = true;
                        break;
                    }
                    fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
                }

                if (found1 == true){
                    if(Mjalur.Status == 0){
                        Mgelombang.ID_Jalur = ID_JalurB;
                    }else{
                        MessageBox(NULL, "Jalur Pendaftaran Tidak Aktif!","PERINGATAN", MB_OK | MB_ICONWARNING );
                        CleanTengah();
                        CleanKanan();
                        UbahGelombang();
                    }
                }
                fwrite(&Mgelombang,sizeof(Mgelombang), 1, TempGelombang);
                break;
            case 3:
                gotoxy(55,41);  printf(" - Tanggal Penutupan Gelombang > 10 hari setelah Pembukaan ");
                gotoxy(55,42);  printf(" - Tanggal Penutupan Gelombang < 2 bulan setelah Pembukaan ");
                gotoxy(133,33);	printf(" Tanggal tutup : ");
                getnum(&baru.tgl, 2); printf(" / ");
                getnum(&baru.bulan, 2); printf(" / ");
                getnum(&baru.tahun, 4);

                if (datevalid(baru)) {
                    if (baru.tahun == Mgelombang.bukaGel.tahun) {
                        if (baru.bulan == Mgelombang.bukaGel.bulan) {
                            if (baru.tgl >= Mgelombang.bukaGel.tgl + 10) {
                                found3 = true;
                            }
                        } else if (baru.bulan > Mgelombang.bukaGel.bulan &&
                                   baru.bulan < Mgelombang.bukaGel.bulan + 2) {
                            found3 = true;
                        }
                    } else if (baru.tahun > Mgelombang.bukaGel.tahun) {
                        if (baru.bulan <= Mgelombang.bukaGel.bulan - 10) {
                            found3 = true;
                        } else if (baru.bulan <= Mgelombang.bukaGel.bulan - 9) {
                            if (baru.tgl <= Mgelombang.bukaGel.tgl - 30) {
                                found3 = true;
                            }
                        }
                    }
                }

                if (!found3){
                    MessageBox(0, "Tanggal Salah", "Pemberitahuan", MB_OK | MB_ICONINFORMATION | MB_DEFAULT_DESKTOP_ONLY);
                    CleanKanan();
                    CleanTengah();
                    UbahGelombang();
                }

                Mgelombang.tutupGel.tgl = baru.tgl;
                Mgelombang.tutupGel.bulan = baru.bulan;
                Mgelombang.tutupGel.tahun = baru.tahun;

                fwrite(&Mgelombang,sizeof(Mgelombang), 1, TempGelombang);
                break;
            case 4:
                gotoxy(133,34); printf("  PILIHAN STATUS");
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
                        UbahGelombang();
                        break;
                }
                Mgelombang.status = StatusB;
                fwrite(&Mgelombang,sizeof(Mgelombang), 1, TempGelombang);
                break;
            case 5:
                gotoxy(133,22); printf("               ");
                CleanKanan();
                MasterGelombang();
                fwrite(&Mgelombang,sizeof(Mgelombang), 1, TempGelombang);
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CleanKanan();
                gotoxy(139,20); printf("                    ");
                UbahGelombang();
                break;
        }
        fread(&Mgelombang, sizeof (Mgelombang), 1, ArsGelombang);
        while (!feof(ArsGelombang)){
            fwrite(&Mgelombang, sizeof (Mgelombang), 1, TempGelombang);
            fread(&Mgelombang, sizeof (Mgelombang), 1, ArsGelombang);
        }
        CleanTengah();
        MessageBox(NULL, "Update data berhasil!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    } else{
        MessageBox(NULL, "ID Gelombang tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
        UbahGelombang();
    }
    fclose(ArsGelombang);
    fclose(TempGelombang);

    ArsGelombang = fopen("FileGelombang.dat", "wb");
    TempGelombang = fopen("TempGelombang.dat", "rb");

    fread(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
    while (!feof(TempGelombang)) {
        fwrite(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        fread(&Mgelombang, sizeof(Mgelombang), 1, TempGelombang);
    }
    fclose(ArsGelombang);
    fclose(TempGelombang);

    CleanTengah();
    CleanKanan();

    update:
    LihatGelombang1();
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI UPDATE DATA KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Update lagi? [Y/N] = [ ]");
    gotoxy(163,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        UbahGelombang();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        MasterGelombang();
    }else {
        CleanKanan();
        goto update;
    }
}

void detailGelombang(){

    // Deklarasi
    typedef enum {false=0,true=1}boolean;
    boolean found, found2;
    char kf;
    int ID;

    // Algoritma
    LihatGelombang1();
    SetColor(252);
    gotoxy(133,44); printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  DETAIL DATA KARYAWAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy (133,22); printf("  ID Gelombang : GEL"); getnum(&ID, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0)
    {
        CleanKanan();
        CleanTengah();
        MasterGelombang();
    }

    ArsGelombang = fopen("FileGelombang.dat","rb");

    found = false;

    fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    while((!found)&&(!feof(ArsGelombang)))
    {
        if(Mgelombang.ID == ID)
        {
            found = true;
            break;
        }
        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    }

    // Jika Data ditemukan
    if (found == true){
        CleanTengah();
        DesainData();
        gotoxy(68,19); printf("=============================");
        gotoxy(68,20); printf("|D|A|T|A| |G|E|L|O|M|B|A|N|G|");
        gotoxy(68,21); printf("=============================");
        gotoxy(69,28); printf(" ID Gelombang       :   GEL%.3d",Mgelombang.ID);
        gotoxy(69,29); printf(" Nama Gelombang     :   %s",Mgelombang.nama_gelombang);
        gotoxy(69,30); printf(" Tanggal Pembukaan  :   %d / %d / %d",Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun);
        gotoxy(69,31); printf(" Tanggal Penutupan  :   %d / %d / %d ",Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

        // Memanggil Data Jalur Penerimaan
        ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

        found2 = false;

        fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
        while((!found2)&&(!feof(ArsJalurPenerimaan))) {
            if(Mjalur.ID == Mgelombang.ID_Jalur) {
                found2 = true;
                break;
            }
            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
        }

        if (found2 == true){
            gotoxy(69,32);
            printf(" Jalur Penerimaan   :   %s", Mjalur.nama_jalur);
        }

        gotoxy(69,33); printf(" Status             :   %s",StatusGelombang[Mgelombang.status]);
        gotoxy(133,44); printf("                           ");
        fflush(stdin);
        fread(&Mgelombang, sizeof(Mgelombang),1 , ArsGelombang);
        fclose(ArsGelombang);
    }else {
        MessageBox(NULL, "ID Gelombang tidak terdapat di arsip!","PERINGATAN", MB_OK | MB_ICONWARNING );
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
        detailGelombang();
    }
    else if (kf == 'n' || kf == 'N')
    {
        CleanKanan();
        CleanTengah();
        MasterGelombang();
    }
    else
    {
        CleanKanan();
        goto carilagi;
    }
}

void HitungGelombang(){

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
    ArsGelombang = fopen("FileGelombang.dat","rb");
    fread(&Mgelombang, sizeof(Mgelombang),1 , ArsGelombang);
    while (!feof(ArsGelombang))
    {
        jumlah++;
        if (Mgelombang.status==0)
        {
            aktif++;
        }else{
            nonaktif++;
        }

        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
    }
    fclose(ArsGelombang);
    SetColor(240);
    gotoxy(70,28); printf ("JUMLAH");
    gotoxy(70,30); printf ("AKTIF");
    gotoxy(70,32); printf ("NON AKTIF");
    gotoxy(79,26); printf("DATA GELOMBANG");
    gotoxy(93,28); printf("%d",jumlah);
    gotoxy(93,30); printf("%d",aktif);
    gotoxy(93,32); printf("%d",nonaktif);
    SetColor(241);
}

void LihatGelombang2() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsGelombang = fopen("FileGelombang.dat", "rb");

    // Jika Data Gelombang Kosong
    if (ArsGelombang == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Gelombang masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterGelombang();
    } else {

        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-14s | %-13s | %-13s | %-10s | %-9s |","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur", "Pendaftar");

        while (!feof(ArsGelombang)) {
            int jumlahpendaftargelombang = 0;
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
                if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Gelombang == Mgelombang.ID) {
                    jumlahpendaftargelombang++;
                }
            }

            gotoxy(Kolom, Baris);
            printf(" GEL%.3d | %-14s | %.2d-%-.2d-%-7.4d |  %-.2d-%-.2d-%-6.4d |",
                   Mgelombang.ID,
                   Mgelombang.nama_gelombang,
                   Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun,
                   Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            found = false;

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while((!found)&&(!feof(ArsJalurPenerimaan))) {
                if(Mjalur.ID == Mgelombang.ID_Jalur) {
                    found = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }

            if (found == true){
                gotoxy(Kolom + 58, Baris);
                printf("%s |", Mjalur.nama_jalur);
            }

            gotoxy(Kolom + 72, Baris);
            printf("%9d |", jumlahpendaftargelombang);

            SetColor(241);
            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-14s | %-13s | %-13s | %-10s | %-9s |","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur", "Pendaftar");
            }
        }

        fclose(ArsGelombang);
        SetColor(252);
    }
}

void LihatGelombang3() {

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found;

    // Algoritma
    CleanTengah();
    fflush(stdin);
    ArsGelombang = fopen("FileGelombang.dat", "rb");

    // Jika Data Gelombang Kosong
    if (ArsGelombang == NULL) {
        SetColor(240);
        MessageBox(NULL, "Data Gelombang masih kosong!", "PERINGATAN", MB_OK | MB_ICONWARNING);
        gotoxy(65, 44);
        printf("Klik apa saja untuk kembali ke menu utama... ");
        getch();
        MasterGelombang();
    } else {

        fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);
        for (x = Kolom; x <= 129; x++) {
            SetColor(249);
            gotoxy(x, 15);
            printf("%c", 205);
            gotoxy(x, 17);
            printf("%c", 205);
        }
        SetColor(241);

        gotoxy(Kolom, 16); printf(" %-6s | %-14s | %-13s | %-13s | %-10s | %-12s |","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur", "Jumlah Lulus");

        while (!feof(ArsGelombang)) {
            int jumlahditerimagelombang = 0;
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
                if (Trspendaftaran.ID_TahunAjar == MTahunAjar.ID && Trspendaftaran.ID_Gelombang == Mgelombang.ID && Trspendaftaran.StatusPendaftaran == 9) {
                    jumlahditerimagelombang++;
                }
            }

            gotoxy(Kolom, Baris);
            printf(" GEL%.3d | %-14s | %.2d-%-.2d-%-7.4d |  %-.2d-%-.2d-%-6.4d |",
                   Mgelombang.ID,
                   Mgelombang.nama_gelombang,
                   Mgelombang.bukaGel.tgl, Mgelombang.bukaGel.bulan, Mgelombang.bukaGel.tahun,
                   Mgelombang.tutupGel.tgl, Mgelombang.tutupGel.bulan, Mgelombang.tutupGel.tahun);

            // Memanggil Data Jalur Penerimaan
            ArsJalurPenerimaan = fopen("FileJalurPenerimaan.dat", "rb");

            found = false;

            fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            while((!found)&&(!feof(ArsJalurPenerimaan))) {
                if(Mjalur.ID == Mgelombang.ID_Jalur) {
                    found = true;
                    break;
                }
                fread(&Mjalur, sizeof(Mjalur), 1, ArsJalurPenerimaan);
            }

            if (found == true){
                gotoxy(Kolom + 58, Baris);
                printf("%s |", Mjalur.nama_jalur);
            }

            gotoxy(Kolom + 72, Baris);
            printf("%12d |", jumlahditerimagelombang);

            SetColor(241);
            fread(&Mgelombang, sizeof(Mgelombang), 1, ArsGelombang);

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
                gotoxy(Kolom, 16); printf(" %-6s | %-14s | %-13s | %-13s | %-10s | %-12s |","ID Gel", "Nama Gelombang", "Tgl Pembukaan", "Tgl Penutupan", "Jalur", "Jumlah Lulus");
            }
        }

        fclose(ArsGelombang);
        SetColor(252);
    }
}

