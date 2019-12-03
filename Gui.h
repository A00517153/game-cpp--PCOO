// Objeto tipo Gui para delimitar zona de juego.
class Gui{
    public:
        int height,width,xini,yini;

        Gui(){
            xini=2;
            yini=2;
            height=25;
            width=78;
            pintar_limites();
        }
        // Dibuja los limites de la zona de juego.
        void pintar_limites(){
            for (int i = xini+1; i < xini+width; i++)
            {
                gotoxy(i,yini);printf("%c",205);
                gotoxy(i,yini+height);printf("%c",205);
            }
            for (int i = yini+1; i < yini+height; i++)
            {
                gotoxy(xini,i);printf("%c",186);
                gotoxy(xini+width,i);printf("%c",186);
            }
            gotoxy(xini,yini);printf("%c",201);
            gotoxy(xini,yini+height);printf("%c",200);
            gotoxy(xini+width,yini);printf("%c",187);
            gotoxy(xini+width,yini+height);printf("%c",188);
            
        }
};