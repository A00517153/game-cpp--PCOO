// Objeto tipo Bala / Proyectil.
class Bala:public Proyectil{
    private:
        int vel_ini=3;
    public:

        Bala(Nave &n):Proyectil(){
            restart(n);
            code=46;
        };
        //Inicializa el objeto.
        void restart(Nave &n){
            posx=n.posx+2;
            posy=n.posy-1;
            time=0;
            vel=vel_ini;
            dibujar();
        };
        //Corre las funciones usuales del objeto.
        void asist(Gui &v,Comet c_list[],int N_COMET,Nave &c,float modif_puntos){
            mover(v,c_list,N_COMET,c,modif_puntos);
        };
        //Define el funcionamiento de del movimiento de la BALA.
        void mover(Gui &v,Comet c_list[], int N_COM,Nave &c,float modif_puntos){
            bool check=false;
            //Verifica si colisiona con un COMETa/Asteroide.
            for(int i=0;i<N_COM;i++){
                if(posx==c_list[i].posx && posy==c_list[i].posy){
                    c_list[i].restart(v);
                    check=true;
                    c.puntos=c.puntos+10*(int)modif_puntos*1.5;
                }
            };
            //Verifica si colisiona con el borde del area de vizualizacion
            if(posy==v.yini+1){
                check=true;
            }
            //Si uno de las dos condiciones anteriores se cumplen, ese lo "elimina"
            //(lo oculta para usarlo posteriormente).
            if(check==true){
                ocult(v);
            }
            //Verifica si el tiempo es multiplo del tiempo de movilidad, 
            //y si lo es, lo cambia de posicion.
            if(vel==vel_ini && check==false){
                if(time%vel==0){
                    borrar();
                    posy--;
                    dibujar();
                }
                time++;
            }
        };
        //Oculta de la visa la BALA, para que no moleste 
        //visualmente al jugador.
        void ocult(Gui &v){
            borrar();
            posx=v.xini;
            posy=v.yini;
            vel=0;
        };

};