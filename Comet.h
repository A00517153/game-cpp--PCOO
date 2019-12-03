// Objeto tipo cometa / asteroide.
class Comet:public Proyectil{
    public:

        Comet(Gui &v):Proyectil(){
            restart(v);
            code=184;            
        };
        // Reinicia el cometa para volver a caer.
        void restart(Gui &v){
            time=0;
            vel=(2+rand()%7);
            posx= v.xini+1+rand()%77;
            posy= v.yini+1;
        };
        // Mueve el cometa por la pantalla.
        void mover(Gui &v,Nave &c){
            time++;
            if((time%vel)==0){
                borrar();
                if(posy==v.yini+v.height-1){
                    restart(v);
                }
                posy++;
                dibujar();
            }
            if(((posx==c.posx && posy==c.posy+2)
            ||(posx==c.posx+1 && posy==c.posy+2)
            ||(posx==c.posx+1 && posy==c.posy+1)
            ||(posx==c.posx+2 && posy==c.posy+1)
            ||(posx==c.posx+2 && posy==c.posy)
            ||(posx==c.posx+3 && posy==c.posy+2)
            ||(posx==c.posx+3 && posy==c.posy+1)
            ||(posx==c.posx+4 && posy==c.posy+2))
            && c.exploted<-25){
                c.vida--;
                c.puntos=c.puntos-10;
                restart(v);
            }
            

        };


};