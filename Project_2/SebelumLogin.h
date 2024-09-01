#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//Prosedur Animasi - Delay
void delay() {
    int delay;
    delay = 1;
    while (delay < 10000000) {
        delay++;
    }
}

void sebelumLogin() {
    int i, j;

    // Garis Horizontal
    for (int i = 0; i <=172; ++i) {
        gotoxy(i,0);        printf("%c",219);
        gotoxy(i,44);       printf("%c",219);
    }

    // Garis Vertikal
    for (int i = 0; i <=43; ++i) {
        gotoxy(0,i);        printf("%c",219);
        gotoxy(172,i);      printf("%c",219);
    }
    getch();

    char *audioFile1 = "Inspiring Ambient _ Background Music for Video _ 20 Sec musicvideo royaltyfreemusic.wav";
    sound(audioFile1);

    // Loading awal
    PrintFile("txt/Memuat.txt", 65,17);
    for (i = 62; i <= 110; i++) {
        gotoxy(i, 25);
        printf("%c", 205);
        gotoxy(i, 27);
        printf("%c", 205);
    }
    gotoxy(61, 25);
    printf("%c", 201);
    gotoxy(61, 27);
    printf("%c", 200);
    gotoxy(61, 26);
    printf("%c", 186);
    gotoxy(111, 25);
    printf("%c", 187);
    gotoxy(111, 27);
    printf("%c", 188);
    gotoxy(111, 26);
    printf("%c", 186);
    system("color 1F");

    for (i = 62; i <= 110; i++) {
        gotoxy(i, 26);
        printf("%c", 219);
        delay();
    }
    system("cls");

    // Halaman Kedua
    PrintFile("txt/Orangduduk.txt",1,4);
    PrintFile("txt/Kamu.txt",80,10);
    Sleep(3000);
    cleanRight();

    // Tampilan Siluet
    system("cls");
    PrintFile("txt/KEL2.txt", 56, 15);
    PrintFile("txt/SiluetR.txt", 5, 1);
    PrintFile("txt/R.txt", 67, 5);
    PrintFile("txt/siluetF.txt", 122, 1);
    PrintFile("txt/F.txt", 98, 5);
    PrintFile("txt/siluetN.txt", 5, 25);
    PrintFile("txt/N.txt", 67, 34);
    PrintFile("txt/siluetH.txt", 122, 25);
    PrintFile("txt/H.txt", 98, 34);

    // Garis atas bawah kotak
    for (i = 54; i <= 117; i++) {
        gotoxy(i, 15);
        printf("%c", 178);
        gotoxy(i, 31);
        printf("%c", 178);
    }

    // Garis kiri kanan kotak
    for (j = 15; j <= 31; j++) {
        gotoxy(54, j);
        printf("%c", 178);
        gotoxy(117, j);
        printf("%c", 178);
    }

    // Garis lurus
    for (i = 0; i <= 172; i++) {
        if (i > 54 && i < 117) {
            printf("  ");
        } else {
            gotoxy(i, 23);
            printf("%c", 178);
        }
    }

    // Garis lurus ke bawah
    for (j = 0; j <= 45; j++) {
        if (j > 15 && j < 32) {
        } else {
            gotoxy(85, j);
            printf("%c", 178);
            gotoxy(86, j);
            printf("%c", 178);
        }
    }
    system("Color 1F");
    Sleep(3000);

////////////////////////////// Next Halaman //////////////////////////////

    system("cls");
    PrintFile("txt/Createdby.txt", 85, 24);
    PrintFile("txt/logouniv.txt", 5, 4);
    PrintFile("txt/Namauniv.txt", 85, 6);

    gotoxy(77, 40);
    printf("L  O  A  D  I  N  G");
    for (i = 6; i <= 165; i++) {
        gotoxy(i, 41);
        printf("%c", 205);
        gotoxy(i, 43);
        printf("%c", 205);
    }
    gotoxy(5, 41);
    printf("%c", 201);
    gotoxy(5, 43);
    printf("%c", 200);
    gotoxy(5, 42);
    printf("%c", 186);
    gotoxy(166, 41);
    printf("%c", 187);
    gotoxy(166, 43);
    printf("%c", 188);
    gotoxy(166, 42);
    printf("%c", 186);
    system("color 1F");

    for (i = 6; i <= 165; i++) {
        gotoxy(i, 42);
        printf("%c", 219);
        delay();
    }
    system("cls");
}

