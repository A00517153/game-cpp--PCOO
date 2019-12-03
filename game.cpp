/*

título          :game.cpp
descripción     :Juego para entretenimiento.
autor           :Johann Palomino
===============================================================

*/

/* Librerias*/
    #include <stdio.h>
    #include <windows.h>
    #include <conio.h>
    #include <iostream>
    #include <stdlib.h>
    #include <time.h>
    #include <math.h>
    #include <ctime>
    #include <unistd.h>
    #include <chrono>
/**/

/* Reguladores de escritura */
    using namespace std;
    using namespace chrono;
/**/

/* Funciones 1 */
    // Inicializa la funcion random.
    void init_rnd(){
        srand(time(NULL));
    };

    // Ubica el puntero en las cordenadas x y.
    void gotoxy(int x,int y){
        HANDLE hCon;
        hCon=GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwPos;
        dwPos.X=x;
        dwPos.Y=y;

        SetConsoleCursorPosition(hCon,dwPos);
    };

    // Hace invisible el puntero para que no moleste al usuario.
    void OcultarCursor(){
        HANDLE hCon;
        hCon=GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cci;
        cci.dwSize=100;
        cci.bVisible=FALSE;

        SetConsoleCursorInfo(hCon,&cci);
    };
/**/

/* Objetos */
    #include "Gui.h"
    #include "Nave.h"
    #include "Proyectil.h"
    #include "Comet.h"
    #include "Bala.h"
/**/

/* Funciones 2 */
    // Funcion encargada de disparar una bala de la nave.
    void disparo(Nave c,Bala b[],int N_BAL){
        
        bool test=true;/* Se encarga de que solo una bala sea disparada. */

        for(int i=0;i<N_BAL;i++){
            if(test==true && b[i].posx==2 && b[i].posy==2){
                b[i].restart(c);
                test=false;
            }
        }
    };
    // Funcion que permite retrasar el proceso por determinada cantidad de tiempo.
    int wait(float ms){
        int sleep_ns=(int)(1e6*ms);/*Tiempo de retraso*/
        auto start = high_resolution_clock::now(); 
            timespec tspec = {0, sleep_ns};
            nanosleep(&tspec, NULL);
            auto end = high_resolution_clock::now();
            duration<int64_t, nano> dur_ns = (end - start);
            int64_t measured_ns = dur_ns.count();
            int64_t diff = measured_ns - sleep_ns;
            /*gotoxy(0,0);
            cout << "diff: " << diff
                << " sleep_ns: " << sleep_ns
                << " measured_ns: " << measured_ns << endl;
            //system("pause");*/
            return (measured_ns/1e6);
    };
    // Funcion limpia pantalla.
    void cln_scrn(Gui ventana){
        for(int i=ventana.xini+1;i<ventana.xini+ventana.width;i++){
            for(int j=ventana.yini+1;j<ventana.yini+ventana.height;j++){
                gotoxy(i,j);printf(" ");
            }
        }
    };
    // Funcion que corre el juego.
    void game(){
        float slip_tim=30; // Tiempo de las funciones Sleep en milisegundos.
        int t_shoot=0; // Ciclos antes de poder volver a disparar.
        int tim=0; // Ciclos de juego
        bool run=true; // Define si el juego continua corriendo.
        float modif_puntos=1;// Puntos Obtenidos en funcion de la velocidad
        // Encargado de proveer el tiempo/velocidad del juego para calcular los puntos por dificultad
        float multi=30; 

        /* Generar objetos */
            // Ventana del juego.
            Gui ventana; 
            // Objeto controlado por el jugador.
            Nave jugador(ventana); 
            jugador.asist(ventana,slip_tim);
            //Cometas.
            Comet c1(ventana),c2(ventana),c3(ventana),c4(ventana),//Cometa generado en el mapa.
                c5(ventana),c6(ventana),c7(ventana),c8(ventana),//Cometa generado en el mapa.
                c9(ventana),c10(ventana),c11(ventana),c12(ventana),//Cometa generado en el mapa.
                c13(ventana),c14(ventana),c15(ventana),c16(ventana),//Cometa generado en el mapa.
                c17(ventana),c18(ventana),c19(ventana),c20(ventana);//Cometa generado en el mapa.
            //Balas
            Bala b1(jugador),b2(jugador),b3(jugador),// Proyectil tipo Bala disparado por el usuario.
                b4(jugador),b5(jugador),b6(jugador),b7(jugador),// Proyectil tipo Bala disparado por el usuario.
                b8(jugador),b9(jugador),b10(jugador);// Proyectil tipo Bala disparado por el usuario.
            //Lista de cometas
            Comet com[20]={c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,
                c11,c12,c13,c14,c15,c16,c17,c18,c19,c20};
            //Lista de Balas
            Bala bal[10]={b1,b2,b3,b4,b5,b6,b7,b8,b9,b10};
        /**/   

        int N_COM=20,N_BAL=10;//Numero de elementos en la lista
         
        /* Ciclado de inicio de objetos tipo bala.*/
            for(int i=0;i<N_BAL;i++){
                bal[i].restart(jugador);
                bal[i].ocult(ventana);
            }
        /**/
        
        cln_scrn(ventana);

        while(run){
            multi=wait(slip_tim);
            tim++;
            modif_puntos=30/multi;
            if (tim%100==0 && slip_tim>=.001){
                slip_tim=slip_tim/1.05; 
            };
            
            if(tim%3==0){
                jugador.m_puntos(1*(int)modif_puntos);
            }

            for(int i=0;i<N_COM;i++){
                com[i].mover(ventana,jugador);
            }

            for(int i=0;i<N_BAL;i++){
                bal[i].mover(ventana,com,N_COM,jugador,modif_puntos);
            }

            if(jugador.exploted<=0){
                jugador.test=0;
                jugador.asist(ventana,slip_tim);
                if((jugador.shoot)==true && t_shoot<=0){
                    disparo(jugador,bal,N_BAL);
                    t_shoot=10;
                }
                if(t_shoot>-10){
                    t_shoot--;
                }
            }

            if(jugador.exploted>=-35){
                jugador.exploted--;
                jugador.explotar();
            }

            if(jugador.n_vidas==0 && jugador.vida==0 && jugador.test==1){
                run=false;
            };        
        }
        
        Sleep(1000);// Retrasa los procesos por 1 segundo.
        
        cln_scrn(ventana);

        gotoxy(ventana.xini+ventana.width/2-19,ventana.yini+ventana.height/2);
        cout<<"Presiona una tecla para continuar. . .";
        getch();

        cln_scrn(ventana);

        gotoxy(ventana.xini+ventana.width/2-4,ventana.yini+ventana.height/2-1);
        cout<<"GAMEOVER";
        gotoxy(ventana.xini+ventana.width/2-13,ventana.yini+ventana.height/2);
        cout<<"Presiona R para reiniciar.";
        gotoxy(ventana.xini+ventana.width/2-20,ventana.yini+ventana.height/2+1);
        cout<<"Presiona cualquer otra tecla para salir.";
        Sleep(100);
    }
/**/

/* Funcion Main */
    int main(){
        init_rnd();
        OcultarCursor();
        // Encargada de correr siempre el juego y reiniciarlo 
        // posteriormente si asi se desea.
        bool run=true;
        while (run)
        {
            game();// Corrre el juego.

            bool test=true;// Es la encargada de correr la funcion de reinicio.
            while (test)// Funcion de reinicio/salida.
            {
                if(kbhit()){
                    char m=getch();
                    if(!(m=='r' || m=='R' )) {run=false;test=false;}
                    else{test=false;}
                }
            }
            
        }
    }
/**/

