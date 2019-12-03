#include <stdio.h>
#include <windows.h>
using namespace std;

class Proyectil
{
private:
    /* data */
protected:
    int code;
    void gotoxy(int x,int y){
        HANDLE hCon;
        hCon=GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwPos;
        dwPos.X=x;
        dwPos.Y=y;

        SetConsoleCursorPosition(hCon,dwPos);
    };
public:
    int posx,posy,vel,time;
    Proyectil(){};
    ~Proyectil(){};
    void borrar(){
            gotoxy(posx,posy);    
            printf(" ");
    };
    void dibujar(){
        gotoxy(posx,posy);    
            printf("%c",code);
    };

    
};
