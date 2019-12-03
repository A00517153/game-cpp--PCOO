// Objeto tipo Nave de jugador.
class Nave{
    private:
        int t_exp=24;
        bool move,bonus;
    
    public:
        int posx,posy,vida,n_vidas,exploted,test,shoot;
        int puntos;

        Nave(Gui &v){
            vida=3;
            n_vidas=3;
            posx=(v.xini+v.width)/2;
            posy=v.yini+v.height-5;
            exploted=-30;
            shoot=0;
            puntos=0;
            move=true;
        };
        // Pinta la nave en la posicion que se encuentra.
        void pintar(){
            gotoxy(posx,posy);    
            printf("  %c",193);
            gotoxy(posx,posy+1);  
            printf(" %c%c%c ",40,207,41);
            gotoxy(posx,posy+2);  
            printf("%c%c %c%c",65,190,190,65);
            pintar_corazones();
            pintar_puntaje();
        };
        // Borra la nave de la pantalla.
        void borrar(){
            gotoxy(posx,posy);    printf("     ");
            gotoxy(posx,posy+1);  printf("     ");
            gotoxy(posx,posy+2);  printf("     ");
        };
        // Permite mover la nave por la pantalla.
        void mover(Gui &v,bool a){ 
            shoot=false;
            if(kbhit()){
                char tecla=getch();
                borrar();
                if ((tecla=='q'||tecla=='Q'||tecla==' ') && a==true){
                    shoot=true;
                    /*mover(v,!a);
                    shoot=true;*/
                }
                if ((tecla=='a'||tecla=='A') && posx > v.xini+1){
                    posx--;
                }
                if ((tecla=='d'||tecla=='D') && posx + 5 < v.xini+v.width){
                    posx++;
                }
                if ((tecla=='w'||tecla=='W') && posy > v.yini+1){
                    posy--;
                }
                if ((tecla=='s'||tecla=='S') && posy+3<v.yini+v.height){
                    posy++;
                }
                /*
                if (tecla==27){
                    vida++;
                }//*/ 
                ///*
                if (tecla==48){
                    vida--;
                }//*/
                move=true;
            }
            
        };
        // Pinta la Vida en la pantalla.
        void pintar_corazones(){
            gotoxy(64,1);printf("SALUD:");
            gotoxy(70,1);printf(" ");
            cout<<vida;
            printf(" HP");
            gotoxy(52,1);printf("VIDAS: ");
            cout<<n_vidas<<"V ";
        };
        // Pinta el puntaje en la pantalla.
        void pintar_puntaje(){
            gotoxy(2,1);cout<<"Puntos:            ";
            gotoxy(9,1);
            cout<<puntos;
        };
        // Realiza la animacion de explocion.
        void explotar(){
            if(exploted>20){
                gotoxy(posx,posy);    printf("     ");
                gotoxy(posx,posy+1);  printf("  *  ");
                gotoxy(posx,posy+2);  printf("     ");
            }
            else if(exploted>16){
                gotoxy(posx,posy);    printf("  *  ");
                gotoxy(posx,posy+1);  printf(" *** ");
                gotoxy(posx,posy+2);  printf("  *  ");
            }
            else if (exploted>12)
            {
                gotoxy(posx,posy);    printf(" *** ");
                gotoxy(posx,posy+1);  printf("** **");
                gotoxy(posx,posy+2);  printf(" *** ");
            }
            else if (exploted>8)
            {
                gotoxy(posx,posy);    printf("** **");
                gotoxy(posx,posy+1);  printf("*   *");
                gotoxy(posx,posy+2);  printf("** **");
            }
            else if (exploted>4)
            {
                gotoxy(posx,posy);    printf("*   *");
                gotoxy(posx,posy+1);  printf("     ");
                gotoxy(posx,posy+2);  printf("*   *");
            }
            else if(exploted>3 && exploted>0) 
            {   
                test=1;
                borrar();
            }
        };
        // Se encarga de los modificadores de vida.
        void d_vida(int slip_tim){
            if(puntos>50 && abs(puntos%750)-5<=0 && !bonus){
                vida++;
                bonus=true;
            }

            if((puntos%750!=0)&& bonus){
                bonus=false;
            }

            if(vida==0){
                borrar();
                if(n_vidas!=0){
                    n_vidas--;
                    Sleep(slip_tim);
                    vida=3;
                }                
                exploted=t_exp;
            }
            if(puntos>150 && vida>3){
                vida--;vida--;vida--;
                n_vidas++;
            }
        };
        // Se encarga de llamar las funciones tipicas usadas.
        void asist(Gui &v,int slip_tim){
            mover(v,1);
            pintar();
            d_vida(slip_tim);
        };
        void m_puntos(int _m_puntos){
            puntos=puntos+_m_puntos;
        };
};