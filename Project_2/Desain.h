#include <stdio.h>
#include <windows.h>
#include <time.h>

void gotoxy(int x,int y);
void SetColor(unsigned short color);
void PrintFile(char file[], int x, int y);
void DesainLoginKaryawan();
void DesainLoginCamaba();
void DesainSelectLogin();
void fullscreeen();
void DesainAdmin();
void DesainManager();
void DesainMgr();
void DesainTransaksi();
void DesainData();
void Tanggal();
void Tanggal1();

int x,y,i;

void Tanggal()
{
    for (x=13; x<=29; x++)
    {
        gotoxy(x,15); printf("%c", 205);
        gotoxy(x,17); printf("%c", 205);
    }

    gotoxy(12,15); printf("%c", 201); // ATAS KIRI
    gotoxy(30,15); printf("%c", 187); // ATAS KANAN
    gotoxy(12,17); printf("%c", 200); // BAWAH KIRI
    gotoxy(30,17); printf("%c", 188); // BAWAH KANAN
    gotoxy(12,16); printf("%c", 186);
    gotoxy(30,16); printf("%c", 186);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    gotoxy(16,16); printf(" %02d-%02d-%d",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void Tanggal1()
{

    for (x=135; x<=169; x++)
    {
        gotoxy(x,16); printf("%c", 205);
        gotoxy(x,18); printf("%c", 205);
    }
    for (y=16; y<=18; y++)
    {
        gotoxy(135,y); printf("%c", 186);
        gotoxy(169,y); printf("%c", 186);
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    gotoxy(139,17); printf(" ======= %02d-%02d-%d =======",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void DesainLoginCamaba()
{
    SetColor(244);
    PrintFile("text/Flower.txt",0,15);
    SetColor(241);

    PrintFile("txt/PMB.txt",20,1);
    PrintFile("txt/Login.txt",66,22);
    PrintFile("txt/Sayapkiri.txt",5,9);
    PrintFile("txt/Sayapkanan.txt",126,9);
    PrintFile("txt/Mahkota.txt",49,9);
    PrintFile("txt/CamabaLogin.txt",45,29);
    for (int i = 0; i < 172; ++i) {
        gotoxy(i,8);
        printf("%c",254);
    }
    /* Kotak */
    for(x=46;x<=125;x++){
        gotoxy(x,22);printf("%c",219);
        gotoxy(x,28);printf("%c",219);
        gotoxy(x,43);printf("%c",219);
    }

    for(y=22;y<=43;y++){
        gotoxy(45,y);printf("%c",219);
        gotoxy(126,y);printf("%c",219);
    }

    for (y=29; y<=43; y++)
    {
        gotoxy(75,y);printf("%c",219);
    }

    /* Desain Menu Login */
    for(y=29;y<=42;y++){
        gotoxy(76,y);printf("%c",176);
        gotoxy(77,y);printf("%c",176);
        gotoxy(78,y);printf("%c",176);
        gotoxy(79,y);printf("%c",176);
        gotoxy(80,y);printf("%c",176);
        gotoxy(121,y);printf("%c",176);
        gotoxy(122,y);printf("%c",176);
        gotoxy(123,y);printf("%c",176);
        gotoxy(124,y);printf("%c",176);
        gotoxy(125,y);printf("%c",176);
    }

    /* Desain Input Login */
    for(x=81; x<=125; x++)
    {
        gotoxy(x,29); printf("%c",176);
        gotoxy(x,42); printf("%c",176);
    }

    /* Design username*/
    gotoxy(84,31); printf(" USERNAME : ");
    gotoxy(84,32); printf("\xc9"); //  atas kiri
    gotoxy(110,32); printf("\xbb"); //atas kanan
    for (x=85; x<=109; x++)
    {
        gotoxy(x,32); printf("%c",205);
        gotoxy(x,34); printf("%c",205);
    }
    gotoxy(110,34); printf("\xbc"); // bawah kanan
    gotoxy(84,34); printf("\xc8"); // bawah kiri
    for (y=33; y<=33; y++)
    {
        gotoxy(84,y); printf("%c",186);
        gotoxy(110,y); printf("%c",186);
    }

    /* Design password*/
    gotoxy(84,36); printf(" PASSWORD : ");
    gotoxy(84,37); printf("\xc9");
    gotoxy(110,37); printf("\xbb");
    for (x=85; x<=109; x++)
    {
        gotoxy(x,37); printf("%c",205);
        gotoxy(x,39); printf("%c",205);
    }
    gotoxy(110,39); printf("\xbc");
    gotoxy(84,39); printf("\xc8");
    for (y=38; y<=38; y++)
    {
        gotoxy(84,y); printf("%c",186);
        gotoxy(110,y); printf("%c",186);
    }
}

void DesainLoginKaryawan()
{
    SetColor(244);
    PrintFile("text/Flower.txt",0,15);
    SetColor(241);

    PrintFile("txt/PMB.txt",20,1);
    PrintFile("txt/Login.txt",66,22);
    PrintFile("txt/Sayapkiri.txt",5,9);
    PrintFile("txt/Sayapkanan.txt",126,9);
    PrintFile("txt/Mahkota.txt",49,9);
    PrintFile("txt/AdminLogin.txt",45,29);
    for (int i = 0; i < 172; ++i) {
        gotoxy(i,8);
        printf("%c",254);
    }
    /* Kotak */
    for(x=46;x<=125;x++){
        gotoxy(x,22);printf("%c",219);
        gotoxy(x,28);printf("%c",219);
        gotoxy(x,43);printf("%c",219);
    }

    for(y=22;y<=43;y++){
        gotoxy(45,y);printf("%c",219);
        gotoxy(126,y);printf("%c",219);
    }

    for (y=29; y<=43; y++)
    {
        gotoxy(75,y);printf("%c",219);
    }

    /* Desain Menu Login */
    for(y=29;y<=42;y++){
        gotoxy(76,y);printf("%c",176);
        gotoxy(77,y);printf("%c",176);
        gotoxy(78,y);printf("%c",176);
        gotoxy(79,y);printf("%c",176);
        gotoxy(80,y);printf("%c",176);
        gotoxy(121,y);printf("%c",176);
        gotoxy(122,y);printf("%c",176);
        gotoxy(123,y);printf("%c",176);
        gotoxy(124,y);printf("%c",176);
        gotoxy(125,y);printf("%c",176);
    }

    /* Desain Input Login */
    for(x=81; x<=125; x++)
    {
        gotoxy(x,29); printf("%c",176);
        gotoxy(x,42); printf("%c",176);
    }

    /* Design username*/
    gotoxy(84,31); printf(" USERNAME : ");
    gotoxy(84,32); printf("\xc9"); //  atas kiri
    gotoxy(110,32); printf("\xbb"); //atas kanan
    for (x=85; x<=109; x++)
    {
        gotoxy(x,32); printf("%c",205);
        gotoxy(x,34); printf("%c",205);
    }
    gotoxy(110,34); printf("\xbc"); // bawah kanan
    gotoxy(84,34); printf("\xc8"); // bawah kiri
    for (y=33; y<=33; y++)
    {
        gotoxy(84,y); printf("%c",186);
        gotoxy(110,y); printf("%c",186);
    }

    /* Design password*/
    gotoxy(84,36); printf(" PASSWORD : ");
    gotoxy(84,37); printf("\xc9");
    gotoxy(110,37); printf("\xbb");
    for (x=85; x<=109; x++)
    {
        gotoxy(x,37); printf("%c",205);
        gotoxy(x,39); printf("%c",205);
    }
    gotoxy(110,39); printf("\xbc");
    gotoxy(84,39); printf("\xc8");
    for (y=38; y<=38; y++)
    {
        gotoxy(84,y); printf("%c",186);
        gotoxy(110,y); printf("%c",186);
    }
}

void DesainSelectLogin() {
    SetColor(244);
    PrintFile("text/Flower.txt", 0, 15);
    SetColor(241);

    PrintFile("txt/PMB.txt", 20, 1);
    PrintFile("txt/Login.txt", 66, 22);
    PrintFile("txt/Sayapkiri.txt", 5, 9);
    PrintFile("txt/Sayapkanan.txt", 126, 9);
    PrintFile("txt/Mahkota.txt",49,9);

    for (int i = 0; i < 172; ++i) {
        gotoxy(i, 8);
        printf("%c", 254);
    }
        /* Kotak */
        for (x = 46; x <= 125; x++) {
            gotoxy(x, 22);
            printf("%c", 219);
            gotoxy(x, 28);
            printf("%c", 219);
            gotoxy(x, 43);
            printf("%c", 219);
        }

        for (y = 22; y <= 43; y++) {
            gotoxy(45, y);
            printf("%c", 219);
            gotoxy(126, y);
            printf("%c", 219);
        }

        for (y = 29; y <= 43; y++) {
            gotoxy(75, y);
            printf("%c", 219);
        }

        /* Desain Menu Login */
        for (y = 29; y <= 42; y++) {
            gotoxy(76, y);
            printf("%c", 176);
            gotoxy(77, y);
            printf("%c", 176);
            gotoxy(78, y);
            printf("%c", 176);
            gotoxy(79, y);
            printf("%c", 176);
            gotoxy(80, y);
            printf("%c", 176);
            gotoxy(121, y);
            printf("%c", 176);
            gotoxy(122, y);
            printf("%c", 176);
            gotoxy(123, y);
            printf("%c", 176);
            gotoxy(124, y);
            printf("%c", 176);
            gotoxy(125, y);
            printf("%c", 176);
        }

        // Menampilkan pilihan menu
        gotoxy(48, 31);
        printf("1. Login Karyawan");
        gotoxy(48, 33);
        printf("2. Login Calon Mahasiswa ");
        gotoxy(48, 35);
        printf("3. Registrasi Camaba");
        gotoxy(48, 37);
        printf("4. Log Out Aplikasi");

    }


void PrintFile(char file[], int x, int y)
{
    FILE *Text;
    char Data[1000000];
    if((Text=fopen(file, "r")) == NULL)
    {
        system("cls");
    }
    while(fgets(Data, 1000000, Text))
    {
        gotoxy(x, y);
        printf("%s", Data);
        y++;
    }
    fclose(Text);
}

void SetColor(unsigned short color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput,color);
}

void gotoxy(int x,int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X=x;
    dwCursorPosition.Y=y;
    hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void fullscreeen()
{
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void DesainAdmin()
{
    PrintFile("txt/samping.txt",2,15);
    PrintFile("txt/Ralfahisnaf.txt",36,1);
    PrintFile("txt/Admin.txt",12,1);
    Tanggal1();

    // Garis Horizontal Admin
    for(x=0; x<=35; x++)
    {
    gotoxy(x,8); printf("%c",219);
    }

    //  Garis vertikal Admin


    // GARIS HORIZONTAL
    for(x=0; x<=172; x++)
    {
        gotoxy(x,0); printf("%c",219);
        gotoxy(x,14); printf("%c",219);
        gotoxy(x,46); printf("%c",219);
    }

    for(x=3; x<=9; x++)
    {
        SetColor(241); gotoxy(x,2); printf("%c",178);
        SetColor(241); gotoxy(x,4); printf("%c",178);
        SetColor(241); gotoxy(x,6); printf("%c",178);
    }

    for(x=36; x<=171; x++) {
        SetColor(241);gotoxy(x, 1);  printf("%c", 178);
        SetColor(241);gotoxy(x, 2);  printf("%c", 177);
        SetColor(241);gotoxy(x, 12);  printf("%c", 177);
        SetColor(241);gotoxy(x, 13);  printf("%c", 178);
    }

    SetColor(241);
    // GARIS VERTIKAL
    for(y=1; y<=45; y++)
    {
        gotoxy(0,y); printf("%c",219);
        gotoxy(172,y); printf("%c",219);
    }

    // GARIS VERTIKAL MENU
    for(y=15; y<=45; y++)
    {
        gotoxy(34,y); printf("%c",177);
        gotoxy(33,y); printf("%c",177);
        gotoxy(9,y); printf("%c",177);
        gotoxy(8,y); printf("%c",177);
    }

    // GARIS PENUTUP DATA
    for(y=0; y<=45; y++){
        gotoxy(35,y); printf("%c",219);

    }
    for(y=15; y<=45; y++) {
        gotoxy(132, y); printf("%c", 219);
    }
    for(y=15; y<=45; y++)
    {
        gotoxy(7,y); printf("%c",219);
        gotoxy(132,y); printf("%c",219);
    }

    // Horizontal Menu
    SetColor(243);
    for(x=10; x<=32; x++)
    {
        gotoxy(x,20); printf("%c",219);
        gotoxy(x,38); printf("%c",219);
    }
    SetColor(241);

    SetColor(243);
    for(x=13; x<=29; x++)
    {
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,36); printf("%c",205);
    }
    SetColor(241);

    for(x=10; x<=32; x++)
    {
        gotoxy(x,15); printf("%c",177);
        gotoxy(x,16); printf("%c",177);
        gotoxy(x,17); printf("%c",177);
        gotoxy(x,18); printf("%c",177);
        gotoxy(x,19); printf("%c",177);
        gotoxy(x,39); printf("%c",177);
        gotoxy(x,40); printf("%c",177);
        gotoxy(x,41); printf("%c",177);
        gotoxy(x,42); printf("%c",177);
        gotoxy(x,43); printf("%c",177);
        gotoxy(x,44); printf("%c",177);
        gotoxy(x,45); printf("%c",177);
    }

    // GARIS VERTIKAL DI MENU
    SetColor(243);
    for(y=21; y<=6; y++)
    {
        gotoxy(12,y); printf("%c",186);
        gotoxy(30,y); printf("%c",186);
    }
    SetColor(241);

    for(y=21; y<=37; y++)
    {
        gotoxy(31,y); printf("%c",177);
        gotoxy(32,y); printf("%c",177);
        gotoxy(11,y); printf("%c",177);
        gotoxy(10,y); printf("%c",177);
    }
}

void DesainManager()
{
    SetColor(252);
    PrintFile("text/Crown.txt",7,1);
    SetColor(241);

    SetColor(242);
    PrintFile("text/Judul3.txt",44,1);
    SetColor(241);

    SetColor(253);
    PrintFile("text/Castle2.txt",130,1);
    SetColor(241);

    Tanggal();

    // GARIS HORIZONTAL
    for(x=7; x<=161; x++)
    {
        gotoxy(x,0); printf("%c",219);
        gotoxy(x,14); printf("%c",219);
        gotoxy(x,46); printf("%c",219);
    }

    // GARIS VERTIKAL
    for(y=1; y<=45; y++)
    {
        gotoxy(7,y); printf("%c",219);
        gotoxy(161,y); printf("%c",219);
    }

    // GARIS PENUTUP DATA
    for(y=15; y<=45; y++)
    {
        gotoxy(35,y); printf("%c",219);
    }

    // GARIS HORIZONTAL MENU
    SetColor(243);
    for(x=10; x<=32; x++)
    {
        gotoxy(x,20); printf("%c",219);
        gotoxy(x,38); printf("%c",219);
    }
    SetColor(241);

    SetColor(243);
    for(x=12; x<=30; x++)
    {
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,36); printf("%c",205);
    }
    SetColor(241);

    // GARIS VERTIKAL DI MENU
    SetColor(243);
    for(y=21; y<=37; y++)
    {
        gotoxy(12,y); printf("%c",186);
        gotoxy(30,y); printf("%c",186);
    }
    SetColor(241);
}

void DesainData()
{
    // PENUTUP GARIS
    gotoxy(56,23); printf("%c", 204); // TENGAH KIRI
    gotoxy(111,23); printf("%c", 185); // TENGAH KANAN
    gotoxy(56,18); printf("%c", 201); // ATAS KIRI
    gotoxy(111,18); printf("%c", 187); // ATAS KANAN
    gotoxy(111,38); printf("%c", 188); // BAWAH KANAN
    gotoxy(56,38); printf("%c", 200); // BAWAH KIRI

    // GARIS HORIZONTAL
    for (x=57; x<=110; x++)
    {
        gotoxy(x,18); printf("%c",205);
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,38); printf("%c",205);
    }

    for (x=55; x<=112; x++)
    {
        gotoxy(x,17); printf("%c",219);
        gotoxy(x,39); printf("%c",219);
    }

    // GARIS VERTIKAL
    for (y=19; y<=22; y++)
    {
        gotoxy(56,y); printf("%c", 186);
        gotoxy(111,y); printf("%c", 186);
    }

    for (y=24; y<=37; y++)
    {
        gotoxy(56,y); printf("%c", 186);
        gotoxy(111,y); printf("%c", 186);
    }

    for (y=18; y<=38; y++)
    {
        gotoxy(55,y); printf("%c", 219);
        gotoxy(112,y); printf("%c", 219);
    }

    for(x=7; x<=161; x++)
    {
        gotoxy(x,14); printf("%c",219);
    }
}

void DesainTransaksi()
{

    SetColor(253);
    PrintFile("text/Money.txt",7,1);
    SetColor(241);

    SetColor(242);
    PrintFile("text/Judul4.txt",44,1);
    SetColor(241);

    SetColor(253);
    PrintFile("text/Money.txt",130,1);
    SetColor(241);
    Tanggal();

    // GARIS HORIZONTAL
    for(x=7; x<=161; x++)
    {
        gotoxy(x,0); printf("%c",219);
        gotoxy(x,14); printf("%c",219);
        gotoxy(x,46); printf("%c",219);
    }

    // GARIS VERTIKAL
    for(y=1; y<=45; y++)
    {
        gotoxy(7,y); printf("%c",219);
        gotoxy(161,y); printf("%c",219);
    }

    // GARIS PENUTUP DATA
    for(y=15; y<=45; y++)
    {
        gotoxy(35,y); printf("%c",219);
    }

    // GARIS HORIZONTAL MENU
    SetColor(243);
    for(x=10; x<=32; x++)
    {
        gotoxy(x,20); printf("%c",219);
        gotoxy(x,38); printf("%c",219);
    }
    SetColor(241);

    SetColor(243);
    for(x=12; x<=30; x++)
    {
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,36); printf("%c",205);
    }
    SetColor(241);

    // GARIS VERTIKAL DI MENU
    SetColor(243);
    for(y=21; y<=37; y++)
    {
        gotoxy(12,y); printf("%c",186);
        gotoxy(30,y); printf("%c",186);
    }
    SetColor(241);
}

void KotakTeks(int x, int y, int width, int height) {
    int i, j;

    gotoxy(x, y);
    printf("%c", 218);
    for(i = 1; i <= width; i++) {
        printf("%c", 196);
    }
    printf("%c", 191);

    for(i = 1; i <= height; i++)
    {
        gotoxy(x, y + i);
        printf("%c", 179);

        gotoxy(x + width + 1, y + i);
        printf("%c", 179);
    }

    printf("\n");
    gotoxy(x, y + height);
    printf("%c", 192);
    for(i = 1; i <= width; i++) {
        printf("%c", 196);
    }
    printf("%c", 217);
}

void DesainPendapatan()
{
    // KIRI
    gotoxy(134,42); printf("\xc9");
    gotoxy(134,44); printf("\xc8");
    // KANAN
    gotoxy(170,42); printf("\xbb");
    gotoxy(170,44); printf("\xbc");

    gotoxy(170,43); printf("%c",186);
    gotoxy(134,43); printf("%c",186);
    for (x=135; x<=169; x++)
    {
        gotoxy(x,42); printf("%c",205);
        gotoxy(x,44); printf("%c",205);
    }
}

void DesainBnykForm()
{
    // KIRI
    gotoxy(134,23); printf("\xc9");
    gotoxy(134,25); printf("\xc8");
    // KANAN
    gotoxy(170,23); printf("\xbb");
    gotoxy(170,25); printf("\xbc");

    gotoxy(170,24); printf("%c",186);
    gotoxy(134,24); printf("%c",186);
    for (x=135; x<=169; x++)
    {
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,25); printf("%c",205);
    }
}

void DesainBnykUkt()
{
    // KIRI
    gotoxy(134,27); printf("\xc9");
    gotoxy(134,29); printf("\xc8");
    // KANAN
    gotoxy(170,27); printf("\xbb");
    gotoxy(170,29); printf("\xbc");

    gotoxy(170,28); printf("%c",186);
    gotoxy(134,28); printf("%c",186);
    for (x=135; x<=169; x++)
    {
        gotoxy(x,27); printf("%c",205);
        gotoxy(x,29); printf("%c",205);
    }
}


void DesainMgr()
{
    SetColor(252);
    PrintFile("text/Crown.txt",7,1);
    SetColor(241);

    SetColor(242);
    PrintFile("text/Judul3.txt",44,1);
    SetColor(241);

    SetColor(253);
    PrintFile("text/Castle2.txt",130,1);
    SetColor(241);

    Tanggal1();

    // GARIS HORIZONTAL
    for(x=7; x<=161; x++)
    {
        gotoxy(x,0); printf("%c",219);
        gotoxy(x,14); printf("%c",219);
        gotoxy(x,46); printf("%c",219);
    }

    // GARIS VERTIKAL
    for(y=1; y<=45; y++)
    {
        gotoxy(7,y); printf("%c",219);
        gotoxy(161,y); printf("%c",219);
    }

    // GARIS VERTIKAL MENU
    for(y=15; y<=45; y++)
    {
        gotoxy(34,y); printf("%c",177);
        gotoxy(33,y); printf("%c",177);
        gotoxy(9,y); printf("%c",177);
        gotoxy(8,y); printf("%c",177);
    }


    // GARIS PENUTUP DATA
    for(y=15; y<=45; y++)
    {
        gotoxy(35,y); printf("%c",219);
        gotoxy(132,y); printf("%c",219);
    }


    // Horizontal Menu
    SetColor(243);
    for(x=10; x<=32; x++)
    {
        gotoxy(x,20); printf("%c",219);
        gotoxy(x,38); printf("%c",219);
    }
    SetColor(241);

    SetColor(243);
    for(x=13; x<=29; x++)
    {
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,36); printf("%c",205);
    }
    SetColor(241);

    for(x=10; x<=32; x++)
    {
        gotoxy(x,15); printf("%c",177);
        gotoxy(x,16); printf("%c",177);
        gotoxy(x,17); printf("%c",177);
        gotoxy(x,18); printf("%c",177);
        gotoxy(x,19); printf("%c",177);
        gotoxy(x,39); printf("%c",177);
        gotoxy(x,40); printf("%c",177);
        gotoxy(x,41); printf("%c",177);
        gotoxy(x,42); printf("%c",177);
        gotoxy(x,43); printf("%c",177);
        gotoxy(x,44); printf("%c",177);
        gotoxy(x,45); printf("%c",177);
    }

    // GARIS VERTIKAL DI MENU
    SetColor(243);
    for(y=21; y<=37; y++)
    {
        gotoxy(12,y); printf("%c",186);
        gotoxy(30,y); printf("%c",186);
    }
    SetColor(241);

    for(y=21; y<=37; y++)
    {
        gotoxy(31,y); printf("%c",177);
        gotoxy(32,y); printf("%c",177);
        gotoxy(11,y); printf("%c",177);
        gotoxy(10,y); printf("%c",177);
    }
}

void DesainPembuatanAkun()
{
    PrintFile("txt/CreateAccount.txt",13,2);
    for (int i = 0; i <= 172; ++i) {
        gotoxy(i,10);
        printf("%c", 254);
    }

    PrintFile("txt/LompatKiri.txt",5,10);
    PrintFile("txt/LompatKanan.txt",122,10);

    // PENUTUP GARIS
    gotoxy(56,23); printf("%c", 204); // TENGAH KIRI
    gotoxy(111,23); printf("%c", 185); // TENGAH KANAN
    gotoxy(56,18); printf("%c", 201); // ATAS KIRI
    gotoxy(111,18); printf("%c", 187); // ATAS KANAN
    gotoxy(111,38); printf("%c", 188); // BAWAH KANAN
    gotoxy(56,38); printf("%c", 200); // BAWAH KIRI

    // GARIS HORIZONTAL
    for (x=57; x<=110; x++)
    {
        gotoxy(x,18); printf("%c",205);
        gotoxy(x,23); printf("%c",205);
        gotoxy(x,38); printf("%c",205);
    }

    for (x=55; x<=112; x++)
    {
        gotoxy(x,17); printf("%c",219);
        gotoxy(x,39); printf("%c",219);
    }

    // GARIS VERTIKAL
    for (y=19; y<=22; y++)
    {
        gotoxy(56,y); printf("%c", 186);
        gotoxy(111,y); printf("%c", 186);
    }

    for (y=24; y<=37; y++)
    {
        gotoxy(56,y); printf("%c", 186);
        gotoxy(111,y); printf("%c", 186);
    }

    for (y=18; y<=38; y++)
    {
        gotoxy(55,y); printf("%c", 219);
        gotoxy(112,y); printf("%c", 219);
    }
}
