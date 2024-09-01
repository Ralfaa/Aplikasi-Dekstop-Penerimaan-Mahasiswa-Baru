#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>

void getinputmin(char input[], int min, int max, int type){
    char strcurrent;
    int i,n,x,m;
    n = 0;
    x=0;
    do
    {
        strcurrent = getch();

        if(strcurrent == '\b' && n != 0) //backspace
        {
            printf("\b \b");
            n--;
            input[n]='\0';
        }
            //else if(current >= 32 && current <= 122){
        else if(isprint(strcurrent)){ //karakter yang bisa di print
            if(n == max) {
                continue;
            }
            else{
                if(type == 3){ //isdigit = hanya angka
                    if(isdigit(strcurrent)) {
                        printf("%c", strcurrent);
                        input[n]=strcurrent;
                        n++;
                    }
                    else printf("\a");
                }
                else if(type == 2){ //isalpha = alpabet dan spasi co : nama
                    if(isalpha(strcurrent) || strcurrent == ' ') {
                        printf("%c", strcurrent);
                        input[n]=strcurrent;
                        n++;
                    }
                    else printf("\a");
                }
                else {
                    if(type == 1) // password //0= bebas
                    {
                        if(strcurrent==35||x>0)
                        {
                            if(strcurrent==35)
                            {
                                x=x+1;
                                for(m=0;m<n;m++)
                                {
                                    printf("\b \b");
                                }
                                for(m=0;m<n;m++)
                                {
                                    printf("%c",input[m]);
                                }

                            }
                            else if(strcurrent==64)
                            {
                                x=0;
                                for(m=0;m<n;m++)
                                {
                                    printf("\b \b");
                                }
                                for(m=0;m<n;m++)
                                {
                                    printf("*");
                                }
                            }
                            else
                            {
                                printf("%c", strcurrent);
                                input[n]=strcurrent;
                                n++;
                            }
                        }
                        else
                        {
                            printf("*");
                            input[n]=strcurrent;
                            n++;
                        }

                    }
                    else
                    {
                        printf("%c", strcurrent);
                        input[n]=strcurrent;
                        n++;
                    }
                }
            }
        }
        else if(strcurrent == 13)
        {
            if(n < min) {
                printf("\a");
                strcurrent = 0;
            }
            else input[n]='\0';
        }
        //else if(current == 27) end();
    }
    while(strcurrent != 13);
}

void getinput(char input[], int max, int type){
    getinputmin(input, 1, max, type);
}

void getteks(char input[], int max){
    getinput(input, max, 0);
}

void getnum(int *dest, int max){
    char input[max];
    getinput(input, max, 3);
    *dest = atoi(input);
}

void getnum1(float *dest, int max){
    char input[max];
    getinput(input, max, 3);
    *dest = atoi(input);
}

void getnummin(int *dest, int min, int max){
    char input[max];
    getinputmin(input, min, max, 3);
    *dest = atoi(input);
}

void getteksnum(char input[], int max){
    getinput(input, max, 3);
}

void getteksnummin(char input[], int min, int max){
    getinputmin(input, min, max, 1);
}

void getpass(char input[], int max){
    getinput(input, max, 1);
}

void getletter(char input[], int max){
    getinput(input, max, 2);
}

void rupiah(int number, char output[])
{
    // menampilkan Bentuk Rupiah
    if(number < 1000) sprintf(output, "%d", number);
    else if(number < 1000000) sprintf(output, "%d.%03d", number/1000, number%1000);
    else if(number < 1000000000) sprintf(output, "%d.%03d.%03d", number/1000000, (number%1000000)/1000, number%1000);
    else sprintf(output, "%d.%03d.%03d.%03d", number/1000000000, (number%1000000000)/1000, (number%1000000)/1000, number%1000);
}

void formatID(char tipe[4], int id, char newID[]) {

    if(id < 10) {
        sprintf(newID, "%s00%d", tipe, id);
    } else if(id < 100) {
        sprintf(newID, "%s0%d", tipe, id);
    } else {
        sprintf(newID, "%s%d", tipe, id);
    }
}

// Deklarasi Tanggal
typedef struct {
    int tgl, bulan, tahun;
}Date;


typedef enum {
    false = 0,
    true = 1
}bool;

typedef struct {
    int tgl, bulan, tahun, hour, min, sec;
} DateTime;

DateTime datesekarang;

void DateTimeNow(Date *TglOutput) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    TglOutput->tgl = tm.tm_mday;
    TglOutput->bulan = tm.tm_mon+1;
    TglOutput->tahun = tm.tm_year+1900;
}

bool datevalid(Date Tgl) {
    bool valid;
    //check year
    if(Tgl.tahun>=1900 && Tgl.tahun<=9999)
    {
        //check month
        if(Tgl.bulan>=1 && Tgl.bulan<=12)
        {
            //check days
            if((Tgl.tgl>=1 && Tgl.tgl<=31) && (Tgl.bulan==1 || Tgl.bulan==3 || Tgl.bulan==5 || Tgl.bulan==7 || Tgl.bulan==8 || Tgl.bulan==10 || Tgl.bulan==12))
                valid = true;
            else if((Tgl.tgl>=1 && Tgl.tgl<=30) && (Tgl.bulan==4 || Tgl.bulan==6 || Tgl.bulan==9 || Tgl.bulan==11))
                valid = true;
            else if((Tgl.tgl>=1 && Tgl.tgl<=28) && (Tgl.bulan==2))
                valid = true;
            else if(Tgl.tgl==29 && Tgl.bulan==2 && (Tgl.tahun%400==0 ||(Tgl.tahun%4==0 && Tgl.tahun%100!=0)))
                valid = true;
            else
                valid = false;
        }
        else
        {
            valid = false;
        }
    }
    else
    {
        valid = false;
    }

    return valid;
}

void sound(char *audioFile) {
    PlaySound(audioFile, NULL, SND_FILENAME | SND_ASYNC);
}
