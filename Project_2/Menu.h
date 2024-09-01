void AdminMenu();
void FinanceMenu();
void PenilaianMenu();
void LihatNilaiSeleksiMenu();
void PassingGradeMenu();
void KemahasiswaanMenu();
void PerangkinganMenu();
void CamabaMenu();


void AdminMenu()
{
    CleanKanan();
    CleanTengah();
    CleanKiri();
    //DECLARATION
    int pilihan;

    //ALGORITHM
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(13,22); printf(" MENU ADMISSIONS");
    gotoxy(13,25); printf(" [1]  Info Akun");
    gotoxy(13,26); printf(" [2]  Karyawan");
    gotoxy(13,27); printf(" [3]  Camaba");
    gotoxy(13,28); printf(" [4]  Gelombang");
    gotoxy(13,29); printf(" [5]  Jalur");
    gotoxy(13,30); printf(" [6]  Prodi");
    gotoxy(13,31); printf(" [7]  Tahun Ajar");
    gotoxy(13,32); printf(" [8]  Jabatan");
    gotoxy(13,33); printf(" [9]  Keluar");
    gotoxy(17,37); printf("Pilih [ ] ");
    SetColor(241);
    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan)
    {
        case 1:
            InfoAkunKaryawan();
            break;
        case 2:
            MasterKaryawan();
            break;
        case 3:
            DetailAkunCamaba();
            break;
        case 4:
            MasterGelombang();
            break;
        case 5:
            MasterJalurPenerimaan();
            break;
        case 6:
            MasterProgramStudi();
            break;
        case 7:
            MasterTahunAjar();
            break;
        case 8:
            MasterJabatan();
            break;
        case 9:
            LoginAkun();
            break;
        default:
            MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
            AdminMenu();
            break;
    }
}

void FinanceMenu()
{
    CleanKanan();
    CleanTengah();
    CleanKiri();
    //DECLARATION
    int pilihan;
    int totalpengajuanform = HitungTotalPengajuan();
    int totalpengajuanukt = HitungTotalPengajuanUkt();

    //ALGORITHM
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(14,22); printf(" Menu Finance");
    gotoxy(13,24); printf(" Verf Pembayaran");
    gotoxy(13,25); printf(" ===============");
    gotoxy(13,26); printf(" [1] Formulir");
    gotoxy(13,27); printf(" [2] Ukt");
    gotoxy(13,29); printf(" Laporan Bayar");
    gotoxy(13,30); printf(" ===============");
    gotoxy(13,31); printf(" [3] Formulir");
    gotoxy(13,32); printf(" [4] Ukt");
    gotoxy(13,34); printf(" [5] Info Akun");
    gotoxy(13,35); printf(" [6] Log Out");
    gotoxy(17,37); printf("Pilih [ ] ");

    SetColor(241);
    gotoxy(134, 20); printf("   INFORMASI PENGAJUAN PEMBAYARAN");
    gotoxy(134,21);  printf("=====================================");
    DesainBnykForm(); gotoxy(136, 24); printf("Total Formulir : %d pengajuan", totalpengajuanform);
    DesainBnykUkt(); gotoxy(136, 28); printf("Total Ukt      : %d pengajuan", totalpengajuanukt);

    SetColor(241);

    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan)
    {
        case 1:
            VerifikasiBayarForm();
            break;
        case 2:
            VerifikasiBayarUkt();
            break;
        case 3:
            CleanKanan();
            LihatPembayaranForm();
            break;
        case 4:
            CleanKanan();
            LihatPembayaranUkt();
            break;
        case 5:
            InfoAkunKaryawan();
            break;
        case 6:
            selectLogin();
            break;
        default:
            MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
            FinanceMenu();
            break;
    }
}

void PenilaianMenu()
{
    CleanKanan();
    CleanTengah();
    CleanKiri();
    //DECLARATION
    int pilihan;

    //ALGORITHM
    system("cls");
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(13,22); printf(" MENU ASSESSMENT");
    gotoxy(13,25); printf(" [1] Info Akun");
    gotoxy(13,26); printf(" [2] Input PSGD");
    gotoxy(13,27); printf(" [3] Lihat Nilai");
    gotoxy(13,28); printf(" [4] Pengumuman 1");
    gotoxy(13,29); printf(" [5] Pengumuman 2");
    gotoxy(13,30); printf(" [6] Pengumuman 3");
    gotoxy(13,31); printf(" [7] Skor Thp 2");
    gotoxy(13,32); printf(" [8] Skor Thp 3");
    gotoxy(13,33); printf(" [9] Log Out");
    gotoxy(17,37); printf("Pilih [ ] ");
    SetColor(241);

    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan)
    {
        case 1:
            InfoAkunKaryawan();
            break;
        case 2:
            PassingGradeMenu();
            break;
        case 3:
            LihatNilaiSeleksiMenu();
            break;
        case 4:
            InputPengumumanTahap1();
            break;
        case 5:
            InputPengumumanTahap2();
            break;
        case 6:
            InputPengumumanTahap3();
            break;
        case 7:
            InputNilai2();
            break;
        case 8:
            InputNilai3();
            break;
        case 9:
            selectLogin();
            break;
        default:
            MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
            PenilaianMenu();
            break;
    }
}

void LihatNilaiSeleksiMenu(){
    //DECLARATION
    int pilihan;
    int pilih;
    int ID_TahunAjar;
    bool found;
    balik:
    CleanKanan();
    CleanTengah();
    DesainAdmin();
    found = false;

    LihatTahunAjar2();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  LIHAT NILAI SELEKSI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133, 22);printf("  ID Tahun Ajar : TAJ"); getnum(&ID_TahunAjar, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID_TahunAjar == 0) {
        CleanKanan();
        CleanTengah();
        PenilaianMenu();
    }

    CleanTengah();
    fflush(stdin);

    // Memanggil Data Tahun Ajaran
    ArsTahunAjar = fopen("FileTahunAjar.dat", "rb");

    fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    while ((!feof(ArsTahunAjar))) {
        if (MTahunAjar.ID == ID_TahunAjar) {
            found = true;
            break;
        }
        fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
    }

    if(found!= true){
        MessageBox(NULL, "Tahun Ajaran Tidak Tersedia", "PERINGATAN", MB_OK | MB_ICONWARNING);
        goto balik;
    }

    CleanKiri();
    CleanKanan();
    CleanTengah();
    //ALGORITHM
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(13,22); printf(" MENU ASSESSMENT");
    gotoxy(13,25); printf(" [1] Nilai Thp 1");
    gotoxy(13,26); printf(" [2] Nilai Thp 2");
    gotoxy(13,27); printf(" [3] Nilai Thp 3");
    gotoxy(13,28); printf(" [4] Kembali");
    gotoxy(17,37); printf("Pilih [ ] ");
    SetColor(241);

    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan) {
        case 1:

            CleanTengah();
            DesainData();

            gotoxy(70,19); printf("=======================");
            gotoxy(70,20); printf("|L|I|H|A|T| |N|I|L|A|I|");
            gotoxy(70,21); printf("=======================");

            gotoxy(60,26); printf(" Nilai Tahap 1 Yang Ingin di lihat?");
            gotoxy(60,28); printf(" [1] Camaba Nilai Keseluruhan");
            gotoxy(60,29); printf(" [2] Camaba Nilai Menunggu pengumuman");
            gotoxy(60,30); printf(" [3] Camaba Nilai Lulus Seleksi");
            gotoxy(60,31); printf(" [4] Camaba Nilai Tidak Lulus Seleksi");
            gotoxy(60,32); printf(" [5] Kembali");
            gotoxy(60,34); printf(" Pilih = [ ]");
            gotoxy(70,34); fflush(stdin); getnum(&pilih, 9);

            switch (pilih) {
                case 1:
                    LihatNilai1Keseluruhan();
                    break;
                case 2:
                    LihatNilai1TungguPengumuman();
                    break;
                case 3:
                    LihatNilai1LulusSeleksi();
                    break;
                case 4:
                    LihatNilai1TidakLulus();
                    break;
                case 5:
                    LihatNilaiSeleksiMenu();
                    break;
                default:
                    MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
                    LihatNilaiSeleksiMenu();
                    break;

            }

            break;
        case 2:

            CleanTengah();
            DesainData();

            gotoxy(70,19); printf("=======================");
            gotoxy(70,20); printf("|L|I|H|A|T| |N|I|L|A|I|");
            gotoxy(70,21); printf("=======================");

            gotoxy(60,26); printf(" Nilai Tahap 1 Yang Ingin di lihat?");
            gotoxy(60,28); printf(" [1] Camaba Nilai Keseluruhan");
            gotoxy(60,29); printf(" [2] Camaba Nilai Menunggu pengumuman");
            gotoxy(60,30); printf(" [3] Camaba Nilai Lulus Seleksi");
            gotoxy(60,31); printf(" [4] Camaba Nilai Tidak Lulus Seleksi");
            gotoxy(60,32); printf(" [5] Kembali");
            gotoxy(60,34); printf(" Pilih = [ ]");
            gotoxy(70,34); fflush(stdin); getnum(&pilih, 9);

            switch (pilih) {
                case 1:
                    LihatNilai2Keseluruhan();
                    break;
                case 2:
                    LihatNilai2TungguPengumuman();
                    break;
                case 3:
                    LihatNilai2LulusSeleksi();
                    break;
                case 4:
                    LihatNilai2TidakLulus();
                    break;
                case 5:
                    LihatNilaiSeleksiMenu();
                    break;
                default:
                    MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
                    LihatNilaiSeleksiMenu();
                    break;
            }
            break;
        case 3:
            CleanTengah();
            DesainData();

            gotoxy(70,19); printf("=======================");
            gotoxy(70,20); printf("|L|I|H|A|T| |N|I|L|A|I|");
            gotoxy(70,21); printf("=======================");

            gotoxy(60,26); printf(" Nilai Tahap 1 Yang Ingin di lihat?");
            gotoxy(60,28); printf(" [1] Camaba Nilai Keseluruhan");
            gotoxy(60,29); printf(" [2] Camaba Nilai Menunggu pengumuman");
            gotoxy(60,30); printf(" [3] Camaba Nilai Lulus Passing Grade");
            gotoxy(60,31); printf(" [4] Camaba Nilai Lulus Seleksi");
            gotoxy(60,32); printf(" [5] Camaba Nilai Tidak Lulus Seleksi");
            gotoxy(60,33); printf(" [6] Kembali");
            gotoxy(60,35); printf(" Pilih = [ ]");
            gotoxy(70,35); fflush(stdin); getnum(&pilih, 9);

            switch (pilih) {
                case 1:
                    LihatNilai3Keseluruhan();
                    break;
                case 2:
                    LihatNilai3TungguPengumuman();
                    break;
                case 3:
                    LihatNilai3LulusPassingGrade();
                    break;
                case 4:
                    LihatNilai3LulusSeleksi();
                    break;
                case 5:
                    LihatNilai3TidakLulus();
                    break;
                case 6:
                    LihatNilaiSeleksiMenu();
                    break;
                default:
                    MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
                    LihatNilaiSeleksiMenu();
                    break;
            }
            break;
        case 4:
            PenilaianMenu();
            break;
        default:
            MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
            LihatNilaiSeleksiMenu();
            break;
    }
}

void PassingGradeMenu(){

    CleanKanan();
    CleanTengah();
    CleanKiri();
    //DECLARATION
    int pilihan;

    CleanKiri();
    CleanKanan();
    CleanTengah();
    //ALGORITHM
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(13,22); printf(" MENU ASSESSMENT");
    gotoxy(13,25); printf(" [1] Ps Grade 1");
    gotoxy(13,26); printf(" [2] Ps Grade 2");
    gotoxy(13,27); printf(" [3] Ps Grade 3");
    gotoxy(13,28); printf(" [4] Kembali");
    gotoxy(17,37); printf("Pilih [ ] ");
    SetColor(241);

    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan) {
        case 1:
            InputPsg1();
            break;
        case 2:
            InputPsg2();
            break;
        case 3:
            InputPsg3();
            break;
        case 4:
            PenilaianMenu();
            break;
        default:
            MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
            PassingGradeMenu();
            break;
    }

}

void KemahasiswaanMenu()
{
    CleanKanan();
    CleanTengah();
    CleanKiri();
    //DECLARATION
    int pilihan;

    //ALGORITHM
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(13,22); printf("  MENU ACADEMIC");
    gotoxy(13,24); printf("Laporan");
    gotoxy(13,25); printf("===============");
    gotoxy(13,26); printf("[1] Bayar Form");
    gotoxy(13,27); printf("[2] Bayar Ukt");
    gotoxy(13,28); printf("[3] Pendaftar");
    gotoxy(13,29); printf("[4] Di terima");
    gotoxy(13,31); printf("Perangkingan");
    gotoxy(13,32); printf("===============");
    gotoxy(13,33); printf("[5] Input Hasil");
    gotoxy(13,34); printf("[6] Info Akun");
    gotoxy(13,35); printf("[7] Log Out");
    gotoxy(17,37); printf("Pilih [ ] ");
    SetColor(241);
    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan)
    {
        case 1:
            LaporanBayarForm();
            break;
        case 2:
            LaporanBayarUkt();
            break;
        case 3:
            LaporanPendaftar();
            break;
        case 4:
            LaporanDiterima();
            break;
        case 5:
            PerangkinganMenu();
            break;
        case 6:
            InfoAkunKaryawan();
            break;
        case 7:
            selectLogin();
            break;
        default:
            MessageBox(NULL, "Inputan Menu Tidak Sesuai","PERINGATAN", MB_OK | MB_ICONWARNING );
            KemahasiswaanMenu();
            break;
    }
}

void PerangkinganMenu() {

    CleanKanan();
    CleanTengah();
    CleanKiri();
    //DECLARATION
    int pilihan;
    menuperangkingan:
    CleanKiri();
    CleanTengah();
    CleanKanan();

    //ALGORITHM
    DesainAdmin();
    PrintFile("txt/MataIkan.txt",38,15);
    PrintFile("txt/Hello.txt",86,20);
    SetColor(240);
    gotoxy(13,22); printf("  MENU ACADEMIC");
    gotoxy(13,24); printf("[1] Kuota Sisa");
    gotoxy(13,25); printf("[2] Perangkingan");
    gotoxy(13,26); printf("[3] Input Seleksi");
    gotoxy(13,27); printf("[4] Kembali");
    gotoxy(17,37); printf("Pilih [ ] ");
    SetColor(241);
    gotoxy(24,37); getnum(&pilihan, 1);
    switch(pilihan) {
        case 1:
            LihatKuotaProdi();
            break;
        case 2:
            lihatcamabaperangkingan();
            break;
        case 3:
            inputcamabaperangkingan();
            break;
        case 4:
            KemahasiswaanMenu();
            break;
        default:
            MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
            PerangkinganMenu();
            break;
    }


}

void CamabaMenu() {

    //DECLARATION
    CleanKanan();
    CleanTengah();
    CleanKiri();
    int pilihan;
        //ALGORITHM
        DesainAdmin();
        PrintFile("txt/MataIkan.txt",38,15);
        PrintFile("txt/Hello.txt",86,20);
        SetColor(240);
        //TampilanStatus();
        gotoxy(13, 22);
        printf("   MENU CAMABA");
        gotoxy(13, 25);
        printf("[1] Info Akun");
        gotoxy(13, 26);
        printf("[2] Perbarui Akun");
        gotoxy(13, 27);
        printf("[3] Buat Form");
        gotoxy(13, 28);
        printf("[4] Info Form");
        gotoxy(13, 29);
        printf("[5] Konf. Form");
        gotoxy(13, 30);
        printf("[6] Input Nilai");
        gotoxy(13, 31);
        printf("[7] Pengumuman");
        gotoxy(13, 32);
        printf("[8] Konf. Ukt");
        gotoxy(13, 33);
        printf("[9] Log Out");
        gotoxy(17, 37);
        printf("Pilih [ ] ");
        SetColor(241);
        gotoxy(24, 37);
        getnum(&pilihan, 1);
        switch (pilihan) {
            case 1:
                InfoAkun();
                break;
            case 2:
                UbahAkunCamaba();
                break;
            case 3:
                BuatFormulir();
                break;
            case 4:
                DetailFormulir();
                break;
            case 5:
                InputBuktiForm();
                break;
            case 6:
                InputNilai1();
                break;
            case 7:
                PengumumanCamaba();
                break;
            case 8:
                InputBuktiUkt();
                break;
            case 9:
                selectLogin();
                break;
            default:
                MessageBox(NULL, "Menu yang dipilih salah!","PERINGATAN", MB_OK | MB_ICONWARNING );
                CamabaMenu();
                break;

        }
}

