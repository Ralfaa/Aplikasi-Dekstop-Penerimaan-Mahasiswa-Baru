
// Deklarasi Master Karyawan
typedef struct {int ID; //pk
    int ID_Jabatan; // fk
    char NIK[20];
    char Telp[20];
    char Nama[50];
    char Asal[50];
    char Username[20];
    char Password[20];
    char tempatLahir[50];
    Date tanggalLahir;
} DataKaryawan;
DataKaryawan Mkaryawan, Mkaryawan1;
FILE *ArsKaryawan;
FILE *ArsKaryawan1;
FILE *TempKaryawan;

char *StatusJabatan[]= {"Aktif", "Non Aktif"};
typedef struct {
    int ID; // pk
    char NamaJabatan[50];
    char Departemen[50];
    int Status
} DataJabatan;
DataJabatan Mjabatan,Mjabatan1;
FILE *ArsJabatan;
FILE *ArsJabatan1;
FILE *TempJabatan;

// Deklarasi Master Gelombang
char *StatusGelombang[]= {"Aktif", "Non Aktif"};
typedef struct {
    int ID;  // Primary Key
    int ID_Jalur; // Foreign Key
    int status;
    char nama_gelombang[50];
    Date bukaGel;
    Date tutupGel;
} DataGelombang;
DataGelombang
Mgelombang, Mgelombang1;
FILE *ArsGelombang;
FILE *ArsGelombang1;
FILE *TempGelombang;

// Deklarasi Master JalurPenerimaan
char *StatusJalur[]= {"Aktif", "Non Aktif"};
typedef struct {
    int ID;  // Pk
    char nama_jalur[50];
    float biaya_pendaftaran;
    int Status;
} DataJalurPenerimaan;
DataJalurPenerimaan Mjalur, Mjalur1;
FILE *ArsJalurPenerimaan;
FILE *ArsJalurPenerimaan1;
FILE *TempJalurPenerimaan;

// Deklrasi Master ProgramStudi
char *StatusProdi[]= {"Aktif", "Non Aktif"};
typedef struct {
    int ID; // pk
    char nama_prodi[50];
    char nama_singkat[10];
    int kuota;
    int kuotasisa;
    char tahun_berdiri[50];
    float psg1, psg2,psg3;
    int status;
} DataProgramStudi;
DataProgramStudi  Mprodi, Mprodi1;
FILE *ArsProgramStudi;
FILE *ArsProgramStudi1;
FILE *TempProgramStudi;

// Deklrasi Master TahunAjar
char *StatusTahunAjaran[]= {"Aktif", "Non Aktif"};
typedef struct {
    int ID; // pk
    char tahun_ajaran[50];
    float NominalUkt;
    int banyak_pendaftar;
    int jumlah_diterima;
    int status;
} DataTahunAjar;
DataTahunAjar  MTahunAjar, MTahunAjar1;
FILE *ArsTahunAjar;
FILE *ArsTahunAjar1;
FILE *TempTahunAjar;

//Deklarasi Master Camaba

char *StatusAkun[] = {"Tidak Terdaftar Seleksi", "Proses Seleksi", "Lulus Seleksi", "Calon Mahasiswa Baru"};
typedef struct {
    // Buat Akun
    int ID; //pk
    char nama_lengkap[50];
    char goldar[25];
    char asal_daerah[25];
    char tempatLahir[25];
    Date tanggalLahir;
    char no_telepon[25];
    char nik[25];
    char agama[25];
    char gender[10];
    char username[15];
    char password[15];

    // Data Wali
    char nama_wali[50];
    char pekerjaan_wali[50];
    char gaji_wali[50];
    char no_telepon_wali[50];
    char nik_wali[50];
    char hubungan_keluarga[50];

    // Data Sekolah
    char namaSekolah[50];
    char AlamatSekolah[50];
    char AkreSekolah[5];
    char KodePosSekolah[20];
    char JurusanSekolah[20];

    // Status Pembantu
    int StatusAkun;

} DataCamaba;
DataCamaba  Mcamaba, Mcamaba1;
FILE *ArsCamaba;
FILE *ArsCamaba1;
FILE *TempCamaba;

char *StatusPendaftaran[] = {"Formulir Terisi", "Tunggu Verifikasi Form",
                             "Formulir Lunas", "Menunggu Pengumuman Tahap 1", "Lolos Seleksi Tahap 1", "Menunggu Pengumuman Tahap 2",
                             "Lolos Seleksi Tahap 2", "Menunggu Pengumuman Tahap 3", "Lolos Passing Grade Tahap 3", "Lolos Seleksi Tahap 3",
                             "Tunggu Verifikasi Ukt", "Ukt Lunas", "Tidak Lulus Seleksi", "Pembayaran Formulir Ditolak", "Pembayaran Ukt Ditolak"};
typedef struct {
    int ID;
    Date tanggalDaftar;

    //Foreign Key
    int ID_Camaba;
    int ID_TahunAjar;
    int ID_Gelombang;
    int ID_Prodi;
    int ID_Karyawan;
    int StatusPendaftaran;
}TrsPendaftaran;
TrsPendaftaran Trspendaftaran;
FILE *ArsPendaftaran;
FILE *ArsPendaftaran1;
FILE *TempPendaftaran;

char *StatusFormulir[] = {"Belum Dibayar", "Menunggu Verifikasi", "Lunas", "Pembayaran Gagal"};
typedef struct {
    int ID;
    int ID_Pendaftaran;
    char VaFormulir[20];
    char ResiBukti[50];
    Date TanggalBayar;
    int StatusFormulir;
}TrsBayarForm;
TrsBayarForm TrsbayarForm;
FILE *ArsBayarFormulir;
FILE *ArsBayarFormulir1;
FILE *TempBayarFormulir;

char *StatusUkt[] = {"Belum Dibayar", "Menunggu Verifikasi", "Lunas", "Pembayaran Gagal"};
typedef struct {
    int ID;
    int ID_Pendaftaran;
    char VaUkt[20];
    char ResiBukti[50];
    Date TanggalBayar;
    int StatusUkt;
}TrsBayarUkt;
TrsBayarUkt TrsbayarUkt;
FILE *ArsBayarUkt;
FILE *ArsBayarUkt1;
FILE *TempBayarUkt;

char *StatusSeleksi1[] = {"Menunggu Hasil", "Lulus", "Tidak Lulus"};
typedef struct {
    int ID;
    Date TanggalInput;
    int ID_BayarForm;

    // Nilai Utbk
    float Lba; // Literasi Bahasa Indonesia
    float Lbi; // Literasi Bahasa Inggris
    float Pm; // Penalaran Matematika
    float Kpu; // Kemampuan Penalaran Umum
    float Pk; // Pengetahuan Kuantitatif
    float Pu; // Pengetahuan dan pemahaman Umum
    float Kbm; // Kemampuan memahami bacaan dan menulis

    // Nilai Rapor
    float Mtk;
    float Bindo;
    float Binggris;
    float TotalNilaiRapor;

    //hasil nilai seleksi 1
    float total;
    float rata_rata;
    int Status;

}TrsNilai1;
TrsNilai1 Trsnilai1;
FILE *ArsTrsNilai1;
FILE *TempTrsNilai1;

char *StatusSeleksi2[] = {"Menunggu Hasil", "Lulus", "Tidak Lulus"};
typedef struct {
    int ID;
    int ID_BayarForm;
    float SkorPsikotest;
    Date TanggalPsikotest;
    int Status;
}TrsNilai2;
TrsNilai2 Trsnilai2;
FILE *ArsTrsNilai2;
FILE *TempTrsNilai2;

char *StatusSeleksi3[] = {"Menunggu Hasil", "Lulus Passing Grade", "Lulus", "Tidak Lulus"};
typedef struct {
    int ID;
    int ID_BayarForm;
    float SkorWawancara;
    Date TanggalWawancara;
    int Status;
}TrsNilai3;
TrsNilai3 Trsnilai3;
FILE *ArsTrsNilai3;
FILE *TempTrsNilai3;

TrsNilai3 trsp[255], k;

//Deklarasi CRUD Kelas
char *StatusKelas[]= {"Aktif", "Non Aktif"};
typedef struct {
    int ID;  // Primary Key KD_Kelas
    char nama_Kelas[50];
    int no_Ruangan;
    int Status;
} DataKelas;
DataKelas MKelas, MKelas1;
FILE *ArsKelas;
FILE *ArsKelas1;
FILE *TempKelas;