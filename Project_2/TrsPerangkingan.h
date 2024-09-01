void lihatcamabaperangkingan();
void LihatKuotaProdi();
void inputcamabaperangkingan();

void LihatKuotaProdi(){

    // Deklarasi
    int Baris = 17, Kolom = 38, Hal = 0, i;
    char jawaban;

    // Algoritma
    CleanTengah();
    CleanKanan();
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
                gotoxy(Kolom, 16); printf(" %-6s | %-15s | %-10s | %-15s | %-10s | %-10s ","ID Prd", "Nama Prodi", "Kuota", "Tahun Berdiri", "Status", "Sisa Kuota");
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
            PerangkinganMenu();
            getch();
        } else {
            LihatKuotaProdi();
        }
    }
}

void lihatcamabaperangkingan(){

    // Deklarasi
    int ID;
    int ID_TahunAjar;
    char kf;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found, found2;

    balik :
    CleanTengah();
    CleanKanan();

    found = false;

    CleanTengah();
    LihatTahunAjar2();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  LIHAT PERANGKINGAN CAMABA");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133, 22);printf("  ID Tahun Ajar : TAJ"); getnum(&ID_TahunAjar, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID_TahunAjar == 0) {
        CleanKanan();
        CleanTengah();
        PerangkinganMenu();
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

    CleanTengah();
    CleanKanan();
    LihatProgramStudi1();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  LIHAT PERANGKINGAN CAMABA");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133, 22);printf("  ID Prodi : PRD"); getnum(&ID, 2);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        PerangkinganMenu();
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
    printf(" %-14s | %-15s | %-20s | %-15s ", "ID Pendaftaran", "ID Nilai 3", "Nilai Wawawancara", "Status");

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if(Trspendaftaran.ID_TahunAjar == ID_TahunAjar && Trspendaftaran.ID_Prodi == ID) {

            if (Trspendaftaran.ID_Prodi == ID) {

                ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

                ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

                while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
                    if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                        break;
                    }
                }

                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

                while (!feof(ArsTrsNilai3)) {
                    if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                        if (Trsnilai3.Status == 1) {
                            trs[n] = Trsnilai3;
                            n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                            break;
                        }
                    }
                    fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
                }
                fclose(ArsTrsNilai3);
            }
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }


    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
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

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-11.5d | TRSW%-11.5d | %20.2f | %-15s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorWawancara,
               StatusSeleksi3[trs[i].Status]);
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
            printf(" %-14s | %-15s | %-20s | %-15s ", "ID Pendaftaran", "ID Nilai 3", "Nilai Wawawancara", "Status");
        }
    }

    lihat:
    CleanKanan();
    gotoxy(133,20); printf("  KONFIRMASI LIHAT PERANGKINGAN");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin Lihat Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        lihatcamabaperangkingan();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PerangkinganMenu();
    }else {
        CleanKanan();
        CleanTengah();
        goto lihat;
    }
}

void inputcamabaperangkingan(){

    // Deklarasi
    char konfirm;
    int camabalulus = 0;
    int ID_TahunAjar;
    int ID;
    char kf;
    int kuota;
    int Baris = 17, Kolom = 38, Hal = 0, i;
    bool found, found1, found2;

    balik :

    CleanTengah();
    CleanKanan();

    found = false;

    CleanTengah();
    LihatTahunAjar2();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  LIHAT PERANGKINGAN CAMABA");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133, 22);printf("  ID Tahun Ajar : TAJ"); getnum(&ID_TahunAjar, 3);

    // JIKA INGIN KEMBALI KE MENU
    if (ID_TahunAjar == 0) {
        CleanKanan();
        CleanTengah();
        PerangkinganMenu();
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

    CleanTengah();
    CleanKanan();

    LihatProgramStudi1();

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);
    gotoxy(133,20); printf("  INPUT PERANGKINGAN CAMABA");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133, 22);printf("  ID Prodi : PRD");getnum(&ID, 2);

    // JIKA INGIN KEMBALI KE MENU
    if (ID == 0) {
        CleanKanan();
        CleanTengah();
        PerangkinganMenu();
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

    // membuat array untuk tempat sorting
    TrsNilai3 trs[500], tmp;
    int n = 0; // Jumlah elemen dalam array trs

    while (!feof(ArsPendaftaran)) {

        if(Trspendaftaran.ID_TahunAjar == ID_TahunAjar && Trspendaftaran.ID_Prodi == ID) {

            if (Trspendaftaran.ID_Prodi == ID) {

                ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

                ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

                while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
                    if (TrsbayarForm.ID_Pendaftaran == Trspendaftaran.ID) {
                        break;
                    }
                }

                fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);

                while (!feof(ArsTrsNilai3)) {
                    if (Trsnilai3.ID_BayarForm == TrsbayarForm.ID) {
                        if (Trsnilai3.Status == 1) {
                            trs[n] = Trsnilai3;
                            n++; // Menambah jumlah elemen setiap kali ada data yang sesuai dengan kriteria
                            break;
                        }
                    }else{
                        fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3);
                    }
                    fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
                }
                fclose(ArsTrsNilai3);
            }
        }
        fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    }


    // Sorting descending berdasarkan SkorWawancara
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (n - 1); j++) {
            if (trs[j].SkorWawancara < trs[j + 1].SkorWawancara) {
                tmp = trs[j];
                trs[j] = trs[j + 1];
                trs[j + 1] = tmp;
            }
        }
    }

    CleanKanan();

    // Menampilkan data
    gotoxy(Kolom, 16);
    printf(" %-14s | %-15s | %-20s | %-15s ", "ID Pendaftaran", "ID Nilai 3", "Nilai Wawawancara", "Status");

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

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-11.5d | TRSW%-11.5d | %20.2f | %-15s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorWawancara,
               StatusSeleksi3[trs[i].Status]);
        SetColor(241);
        camabalulus++;

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
            printf(" %-14s | %-15s | %-20s | %-15s ", "ID Pendaftaran", "ID Nilai 3", "Nilai Wawawancara", "Status");
        }
    }

    gotoxy(65, 44);
    printf("Klik apapun untuk lanjut.. ");
    getch();

    kuota:
    CleanKanan();
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    TempProgramStudi = fopen("TempProgramStudi.dat", "wb");

    SetColor(252);
    gotoxy(133, 44);
    printf("  Ketik '0' untuk ke kembali");
    SetColor(241);

    while(fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi)==1)
    {
        if(Mprodi.ID == ID) {
            gotoxy(133,20); printf("  Kuota Sisa : %d ", Mprodi.kuotasisa);
            gotoxy(133,21); printf("  ===============================");

            gotoxy(133,23); printf("  INPUT HASIL PERANGKINGAN");
            gotoxy(133,24); printf("  ===============================");
            gotoxy(133,25); printf("  Kuota Lulus Perangkingan : "); getnum(&kuota, 3);

            if(kuota == 0){
                CleanKanan();
                CleanTengah();
                PerangkinganMenu();
            }

            if(kuota > Mprodi.kuota){
                MessageBox(NULL, "Kuota Prodi Tidak Mencukupi", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto kuota;
            }else if(kuota < 1){
                MessageBox(NULL, "Kuota Lulus Tidak boleh kurang dari 1", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto kuota;
            }

            if (kuota > camabalulus){
                MessageBox(NULL, "Kuota melebihi camaba yang lulus perangkingan", "PERINGATAN", MB_OK | MB_ICONWARNING);
                goto kuota;
            } else {
                break;
            }
        }
    }

    CleanTengah();

    Baris = 17, Kolom = 38, Hal = 0, i;

    fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
    for (x = Kolom; x <= 129; x++) {
        SetColor(249);
        gotoxy(x, 15);
        printf("%c", 205);
        gotoxy(x, 17);
        printf("%c", 205);
    }
    SetColor(241);

    // Menampilkan data
    gotoxy(Kolom, 16);
    printf(" %-14s | %-15s | %-20s | %-15s ", "ID Pendaftaran", "ID Nilai 3", "Nilai Wawawancara", "Status");

    // Menampilkan data
    for (int i = 0; i < kuota; i++) {
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

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir)==1){
            if (TrsbayarForm.ID == trs[i].ID_BayarForm){
                ArsPendaftaran = fopen("FilePendaftaran.dat","rb");
                while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
                    if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                        break;
                    }
                }
            }
        }

        gotoxy(Kolom, Baris);
        printf(" FRM%-11.5d | TRSW%-11.5d | %20.2f | %-15s",
               Trspendaftaran.ID,
               trs[i].ID,
               trs[i].SkorWawancara,
               StatusSeleksi3[trs[i].Status]);
        SetColor(241);
        camabalulus++;

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
            printf(" %-14s | %-15s | %-20s | %-15s ", "ID Pendaftaran", "ID Nilai 3", "Nilai Wawawancara", "Status");
        }
    }

    kembali:
    ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");
    TempTrsNilai3 = fopen("TempNilai3.dat", "wb");

    gotoxy(133,28); printf("  KONFIRMASI PENGUMUMAN KELULUSAN");
    gotoxy(133,29); printf("  ===============================");
    gotoxy(133,30); printf("  Input Pengumuman? [Y/N] = [ ]");
    gotoxy(162,30); getteks(&konfirm, 1);

    if (konfirm == 'y' || konfirm == 'Y') {
        for (int i = 0; i < kuota; i++) {
            trs[i].Status = 2;

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");
            TempTrsNilai3 = fopen("TempNilai3.dat", "wb");

            while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3) == 1) {
                if (Trsnilai3.ID == trs[i].ID) {
                    Trsnilai3.Status = trs[i].Status;
                }
                fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3);
            }
            fclose(ArsTrsNilai3);
            fclose(TempTrsNilai3);

            ArsTrsNilai3 = fopen("FileNilai3.dat", "wb");
            TempTrsNilai3 = fopen("TempNilai3.dat", "rb");

            // Salin isi file temporer ke file utama
            while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3) == 1) {
                fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }

            // Tutup file yang sudah selesai diproses
            fclose(ArsTrsNilai3);
            fclose(TempTrsNilai3);
        }

        for (int i = 0; i < n; i++) {

            ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");
            TempTrsNilai3 = fopen("TempNilai3.dat", "wb");

            while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3) == 1) {
                if (Trsnilai3.ID == trs[i].ID && Trsnilai3.Status !=2) {
                    Trsnilai3.Status = 3;
                }
                fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3);
            }
            fclose(ArsTrsNilai3);
            fclose(TempTrsNilai3);

            ArsTrsNilai3 = fopen("FileNilai3.dat", "wb");
            TempTrsNilai3 = fopen("TempNilai3.dat", "rb");

            // Salin isi file temporer ke file utama
            while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3) == 1) {
                fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
            }

            // Tutup file yang sudah selesai diproses
            fclose(ArsTrsNilai3);
            fclose(TempTrsNilai3);
        }
    } else if (konfirm == 'n' || konfirm == 'N') {
        CleanTengah();
        CleanKanan();
        PerangkinganMenu();
    } else {
        CleanTengah();
        CleanKanan();
        goto kembali;
    }

    // Buka kembali file-file yang telah diolah
    ArsTrsNilai3 = fopen("FileNilai3.dat", "wb");
    TempTrsNilai3 = fopen("TempNilai3.dat", "rb");

    // Salin isi file temporer ke file utama
    while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, TempTrsNilai3) == 1) {
        fwrite(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3);
    }

    // Tutup file yang sudah selesai diproses
    fclose(ArsTrsNilai3);
    fclose(TempTrsNilai3);


    ArsTrsNilai3 = fopen("FileNilai3.dat", "rb");

    while (fread(&Trsnilai3, sizeof(Trsnilai3), 1, ArsTrsNilai3) == 1) {

        ArsBayarFormulir = fopen("FileBayarFormulir.dat", "rb");

        while (fread(&TrsbayarForm, sizeof(TrsbayarForm), 1, ArsBayarFormulir) == 1) {
            if (TrsbayarForm.ID == Trsnilai3.ID_BayarForm) {
                break;
            }
        }

        ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "wb");

        while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran) == 1) {
            if (Trspendaftaran.ID == TrsbayarForm.ID_Pendaftaran) {
                if (Trsnilai3.Status == 2) {
                    Trspendaftaran.StatusPendaftaran = 9;
                    Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                } else {
                    Trspendaftaran.StatusPendaftaran = 12;
                    Trspendaftaran.ID_Karyawan = Mkaryawan.ID;
                }
            }
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran);
        }

        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);

        ArsPendaftaran = fopen("FilePendaftaran.dat", "wb");
        TempPendaftaran = fopen("TempPendaftaran.dat", "rb");

        while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, TempPendaftaran) == 1) {
            fwrite(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran);
        }

        fclose(ArsPendaftaran);
        fclose(TempPendaftaran);
    }
    fclose(ArsTrsNilai3);

    int jumlahditerima = 0;
    int kuotaterpakai = 0;

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {

        // update atribut jumlah di terima di tabel tahun ajaran, saat ada formulir camaba yang lulus
        ArsTahunAjar = fopen("FileTahunAjar.dat","rb");
        TempTahunAjar = fopen("TempTahunAjar.dat", "wb");

        while (fread(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar) == 1) {
            if (MTahunAjar.ID == Trspendaftaran.ID_TahunAjar) {
                if (Trspendaftaran.StatusPendaftaran == 9) {
                    jumlahditerima++;
                }
                MTahunAjar.jumlah_diterima = jumlahditerima;
            }
            fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar);
        }

        // Tutup file yang sudah dibuka sebelumnya
        fclose(ArsTahunAjar);
        fclose(TempTahunAjar);

        // Buka kembali file-file yang telah diolah
        ArsTahunAjar = fopen("FileTahunAjar.dat", "wb");
        TempTahunAjar = fopen("TempTahunAjar.dat", "rb");

        // Salin isi file temporer ke file utama
        while (fread(&MTahunAjar, sizeof(MTahunAjar), 1, TempTahunAjar) == 1) {
            fwrite(&MTahunAjar, sizeof(MTahunAjar), 1, ArsTahunAjar);
        }

        // Tutup file yang sudah selesai diproses
        fclose(ArsTahunAjar);
        fclose(TempTahunAjar);

        // update akun camaba
        ArsCamaba = fopen("FileCamaba.dat", "rb");
        TempCamaba = fopen("TempCamaba.dat", "wb");

        while (fread(&Mcamaba, sizeof(Mcamaba), 1, ArsCamaba) == 1) {
            if (Mcamaba.ID == Trspendaftaran.ID_Camaba && Trspendaftaran.ID_Prodi == ID && Trspendaftaran.ID_TahunAjar == ID_TahunAjar) {
                if (Trspendaftaran.StatusPendaftaran == 12) {
                    Mcamaba.StatusAkun = 0;
                }else if(Trspendaftaran.StatusPendaftaran == 9){
                    Mcamaba.StatusAkun = 2;
                    AkunVaUkt();
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

    fclose(ArsPendaftaran);

    ArsPendaftaran = fopen("FilePendaftaran.dat", "rb");

    // update kuota di prodi ketika ada formulir yang lulus diterima
    ArsProgramStudi = fopen("FileProgramStudi.dat", "rb");
    TempProgramStudi = fopen("TempProgramStudi.dat", "wb");

    while (fread(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi) == 1) {
        jumlahditerima = 0;
        rewind(ArsPendaftaran);
        while (fread(&Trspendaftaran, sizeof(Trspendaftaran), 1, ArsPendaftaran)==1) {
            if (Mprodi.ID == Trspendaftaran.ID_Prodi && Trspendaftaran.StatusPendaftaran == 9){
                jumlahditerima++;
            }
        }
        Mprodi.kuotasisa = Mprodi.kuota - jumlahditerima;
        fwrite(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi);
    }

    // Tutup file yang sudah dibuka sebelumnya
    fclose(ArsProgramStudi);
    fclose(TempProgramStudi);

    // Buka kembali file-file yang telah diolah
    ArsProgramStudi = fopen("FileProgramStudi.dat", "wb");
    TempProgramStudi = fopen("TempProgramStudi.dat", "rb");

    // Salin isi file temporer ke file utama
    while (fread(&Mprodi, sizeof(Mprodi), 1, TempProgramStudi) == 1) {
        fwrite(&Mprodi, sizeof(Mprodi), 1, ArsProgramStudi);
    }

    // Tutup file yang sudah selesai diproses
    fclose(ArsProgramStudi);
    fclose(TempProgramStudi);
    fclose(ArsPendaftaran);

    MessageBox(NULL, "Pengumuman Perangkingan Berhasil dilakukan !!","INFORMASI", MB_OK | MB_ICONINFORMATION );

    lihat:
    CleanKanan();

    gotoxy(133,20); printf("  KONFIRMASI PENGUMUMAN KEMBALI");
    gotoxy(133,21); printf("  ===============================");
    gotoxy(133,22); printf("  Ingin input Lagi? [Y/N] = [ ]");
    gotoxy(162,22); getteks(&kf, 1);
    if (kf == 'y' || kf == 'Y') {
        CleanKanan();
        CleanTengah();
        inputcamabaperangkingan();
    } else if (kf == 'N' || kf == 'n'){
        CleanKanan();
        CleanTengah();
        PerangkinganMenu();
    }else {
        CleanKanan();
        CleanTengah();
        goto lihat;
    }
}