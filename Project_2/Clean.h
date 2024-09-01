

//Global Deklarasi
int x,y;
int i;
int lebar,tinggi;

void CleanKanan();
void CleanKiri();
void CleanTengah();
void cleanRight();
void CleanKiriTransaksi();
void CleanTengahTransaksi();
void CleanTengahManager();
void CleanKiriKasir();

void console(int *lebar, int *tinggi)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);

    *lebar = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *tinggi = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void cleanRight()
{
    console(&lebar, &tinggi);
    for (int i = 0; i < lebar; ++i) {
        for (int j = 0; j < tinggi; ++j) {
            gotoxy(i,j);
            printf("  ");
        }
    }
}

void CleanKanan()
{
    SetColor(241);
    x=133; y=20;
    for (i=1; i<=25; i++)
    {
        gotoxy(x,y); printf("                                       ");
        y++;
    }
}

void CleanKiri()
{
    SetColor(241);
    x=13; y=24;
    gotoxy(13,22); printf("                 ");
    for (i=1; i<=12; i++)
    {
        gotoxy(x,y); printf("                 ");
        y++;
    }
    gotoxy(13,37); printf("                 ");
}

void CleanTengah()
{
    SetColor(241);
    x=38,y=15;

    for (i=1; i<=31; i++)
    {
        gotoxy(x,y); printf("                                                                                             ");
        y++;
    }
}

void CleanKiriTransaksi()
{
    SetColor(241);
    x=9; y=20;
    for (i=1; i<=23; i++)
    {
        gotoxy(x,y); printf("                          ");
        y++;
    }
    gotoxy(9,44); printf("                          ");
    gotoxy(9,45); printf("                          ");
}

void CleanTengahTransaksi()
{
    SetColor(241);
    x=41; y=15;
    for (i=1; i<=28; i++)
    {
        gotoxy(x,y); printf("                                                                                                                        ");
        y++;
    }
}

void CleanTengahManager()
{
    SetColor(241);
    int a,b;
    a=36; b=15;
    for (i=1; i<=31; i++)
    {
        gotoxy(a,b); printf("                                                                                                                             ");
        b++;
    }
}

void CleanKiriKasir()
{
    SetColor(241);
    x=8; y=19;
    for (i=1; i<=22; i++)
    {
        gotoxy(x,y); printf("                                ");
        y++;
    }
    gotoxy(8,44); printf("                                ");
}

