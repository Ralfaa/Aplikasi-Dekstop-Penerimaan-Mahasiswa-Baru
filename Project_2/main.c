#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>

#include "Lib.h"
#include "Desain.h"
#include "Clean.h"
#include "Deklarasi.h"
#include "Menu.h"


#include "crudKaryawan.h"
#include "crudJabatan.h"
#include "crudGelombang.h"
#include "crudJalurPenerimaan.h"
#include "crudProgramStudi.h"
#include "crudTahunAjar.h"
#include "crudCamaba.h"
#include "SebelumLogin.h"
#include "login.h"

#include "TrsPendaftaran.h"
#include "TrsBayarFormulir.h"
#include "TrsNilai1.h"
#include "TrsNilai2.h"
#include "TrsNilai3.h"
#include "TrsBayarUkt.h"
#include "TrsPerangkingan.h"
#include "Laporan.h"


int main() {
    fullscreeen();
    sebelumLogin();
    char *audioFile = "Selamat Datang di Aplikasi Penerimaan Mahasiswa Baru Politeknik Ralfa hisnaf, Silahkan pilih menu login anda !.wav";
    sound(audioFile);
    selectLogin();
    return 0;
}
