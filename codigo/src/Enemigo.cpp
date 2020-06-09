#include "Enemigo.h"
#include "EnemigoMSX.h"
#include "Globales.h"
#include "SFML/Graphics.hpp"
#include "Juego.h"
#include "Motor2D.h"
#include "Constantes.h"

using namespace std;
using namespace sf;

float Enemigo::VELOCIDAD_ENEMIGO_1 = 1;
float Enemigo::VELOCIDAD_BALA_ENEMIGO_2 = 2;
float Enemigo::VELOCIDAD_ENEMIGO_3 = 4;

int Enemigo::DANYO_ENEMIGO_1 = 40;
int Enemigo::DANYO_BALA_ENEMIGO_2 = 15;
int Enemigo::DANYO_ENEMIGO_3 = 1;

#define kTIledAlto 32.0
#define kTIledAncho 32.0


Enemigo::Enemigo()
{
    //ctor
    //nodoSolucion = sf::RectangleShape(sf::Vector2f(32.f, 32.f));

}

Enemigo::~Enemigo()
{
    //dtor
}


void Enemigo::update()
{
    //std::cout << "update padre MSX" << std::endl;
}

void Enemigo::update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa, sf::Time timeElapsed)
{


}

void Enemigo::update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa)
{


}

void Enemigo::render(sf::RenderWindow *window)
{

    //std::cout << "render padre" << std::endl;
}

void Enemigo::render(sf::RenderWindow *window, double percentTick){


}

void Enemigo::animacionReposo(){

}


void Enemigo::bajarVida(int vidaMenos){
    cout << "Hemos bajado vida a un enemigo" << endl;
    vida-=vidaMenos;
    if(vida <= 0)
    {
        vida=0;
        cout << "Ha muerto un enemigo" << endl;
        // si el que ha muerto es MSX nos pasamos el juego
        if (EnemigoMSX* child = dynamic_cast<EnemigoMSX*>(this)) {
            cout << "Hemos matado a MSX" << endl;
            Constantes::PUEDE_PARAR_MUSICA_INGAME = true;
            Globales::NIVEL_ANTARTIDA_SUPERADO = true;
            Juego::getInstance()->setState(State::Estados::JUEGO_SUPERADO);
        }
    }
    recibirDanyo=true;
    tiempoEnRojo.restart();
}


void Enemigo::calcularCamino(float eneX, float eneY, float jugX, float jugY, int mapDimY, int mapDimX)
{

        listaInterior.clear();
        listaFrontera.clear();
        listaNodosPadres.clear();
        //soluciones.clear();
        soyElEnemigo = false;
        meVoyaDormir = false;
        salir = false;
        distanciaNodosJugador=100;


    if(primeraVezGrid == false){
        todosNodos = new Nodo**[mapDimY];
        for(int f=0; f<mapDimY; ++f){
          todosNodos[f] = new Nodo*[mapDimX];
          for(int c=0; c<mapDimX; ++c){
           todosNodos[f][c] = new Nodo(f,c);
          }
        }
        primeraVezGrid = true;
    }



    int posDisJugX = trunc(jugX/kTIledAlto);
    int posDisJugY = trunc(jugY/kTIledAncho);
    int posDisEnemigX = trunc(eneX/kTIledAlto);
    int posDisEnemigY = trunc(eneY/kTIledAncho);
    int disEnemigJug=pow((pow((posDisJugX-posDisEnemigX),2)+pow(posDisJugY-posDisEnemigY,2)),0.5);

    //METEMOS EL NODO INICIL COMO PRIMER NODO DE LISTA FRONTERA
    Nodo *nodoEnemigo = todosNodos[posDisEnemigY][posDisEnemigX];
    //DOS NODOS NECESARIOS: EL ACTUAL PARA IR RECRRIENDO Y EL DEL JUEGADOR
    Nodo *nodoActual = todosNodos[posDisEnemigY][posDisEnemigX];

    int posMenor = 0;
    salir = false;
    int posMenorX = 0;
    int posMenorY = 0;


    listaFrontera.clear();
    listaInterior.clear();
    listaFrontera.push_back(todosNodos[posDisEnemigY][posDisEnemigX]);

    while (!listaFrontera.empty() && salir == false){
        nodoActual = listaFrontera.at(0);
        int posMenorX = nodoActual->x;
        int posMenorY = nodoActual->y;
        posMenor = 0;
        for(int i=0; i < listaFrontera.size(); i++){
            if(nodoActual->peso >listaFrontera.at(i)->peso){
                posMenor = i;
                nodoActual = listaFrontera.at(i);
                posMenorX = nodoActual->x;
                posMenorY = nodoActual->y;
            }
        }
        if(nodoActual->x == posDisJugY && nodoActual->y == posDisJugX){ //nos salimos que hemos llegado al final
            salir = true;
        }else{
            nodoActual->estaEnInterior = true;
            listaInterior.push_back(listaFrontera.at(posMenor));
            listaFrontera.erase(listaFrontera.begin()+posMenor);

            //NOS MOVEMOS HACIA ARRIBA
            if(posMenorY-1 >= 0)
            {
                if(mapa2[posMenorX][posMenorY-1]==0) //NORTE o ARRIBA
                {
                   // std::cout << "LA POSICION X ES:   " <<posMenorX<<"  LA POSICION Y ES: "<<posMenorY<<std::endl;
                    Nodo *nodoN = todosNodos[posMenorX][posMenorY-1];
                    if(nodoN->estaEnInterior == false){
                        if(nodoN->estaEnFrontera == false){
                            nodoN->padre = nodoActual;

                            nodoN->g = nodoActual->g+10;
                            nodoN->h = pow((pow((posDisJugX-posMenorX),2)+pow((posDisJugY-(posMenorY-1)),2)),0.5);
                            nodoN->peso = nodoActual->g+10 + nodoN->h;

                            nodoN->estaEnFrontera = true;
                            listaFrontera.push_back(nodoN);
                        }
                        else
                        {
                            if(nodoN->g > nodoActual->g+10)
                            {
                                nodoN->g = nodoActual->g+10;
                                nodoN->peso = nodoN->g + nodoN->h;
                                nodoN->padre = nodoActual;
                            }
                        }
                    }
                }
            }
            //NOS MOVEMO HACIA LA DERECHA
            if(posMenorX+1 < mapDimY)
            {
                if(mapa2[posMenorX+1][posMenorY]==0)
                {

                    Nodo *nodoE = todosNodos[posMenorX+1][posMenorY];
                    if(nodoE->estaEnInterior == false){
                        if(nodoE->estaEnFrontera == false){
                            nodoE->padre = nodoActual;

                            nodoE->g = nodoActual->g+10;
                            nodoE->h = pow((pow((posDisJugX-(posMenorX+1)),2)+pow((posDisJugY-posMenorY),2)),0.5);
                            nodoE->peso = nodoActual->g+10 + nodoE->h;

                            nodoE->estaEnFrontera = true;
                            listaFrontera.push_back(nodoE);

                        }
                        else
                        {
                            if(nodoE->g > nodoActual->g+10)
                            {
                                nodoE->g = nodoActual->g+10;
                                nodoE->peso = nodoActual->g+10 + nodoE->h;
                                nodoE->padre = nodoActual;
                            }

                        }
                    }
                }
            }
            //NOS MOVEMOS HACIA ABAJO
            if(posMenorY+1 < mapDimX)
            {
                if(mapa2[posMenorX][posMenorY+1]==0) // SUR o IZQUIERDA
                {
                    Nodo *nodoS = todosNodos[posMenorX][posMenorY+1];
                    if(nodoS->estaEnInterior == false){
                        if(nodoS->estaEnFrontera == false){
                            nodoS->padre = nodoActual;

                            nodoS->g = nodoActual->g+10;
                            nodoS->h = pow((pow(posDisJugX-posMenorX,2)+pow((posDisJugY-(posMenorY+1)),2)),0.5);
                            nodoS->peso = nodoActual->g+10 + nodoS->h;

                            nodoS->estaEnFrontera = true;
                            listaFrontera.push_back(nodoS);
                        }
                        else
                        {
                            if(nodoS->g > nodoActual->g+10)
                            {
                                nodoS->g = nodoActual->g+10;
                                nodoS->peso = nodoActual->g+10 + nodoS->h;
                                nodoS->padre = nodoActual;
                            }
                        }
                    }
                }
            }
            //NOS MOVEMOS A LA IZQUIERDA
            if(posMenorX-1 >= 0)
            {
                if(mapa2[posMenorX-1][posMenorY]==0) // OESTE o ABAJO
                {
                    Nodo *nodoO = todosNodos[posMenorX-1][posMenorY];
                    if(nodoO->estaEnInterior == false){
                        if(nodoO->estaEnFrontera == false){
                            nodoO->padre = nodoActual;

                            nodoO->g = nodoActual->g+10;
                            nodoO->h = pow((pow((posDisJugX-(posMenorX-1)),2)+pow((posDisJugY-posMenorY),2)),0.5);
                            nodoO->peso = nodoActual->g+10 + nodoO->h;

                            nodoO->estaEnFrontera = true;
                            listaFrontera.push_back(nodoO);
                            //std::cout<<"AÑADO 3"<<std::endl;
                        }
                        else
                        {
                            if(nodoO->g > nodoActual->g+10)
                            {
                                nodoO->g = nodoActual->g+10;
                                nodoO->peso = nodoActual->g+10 + nodoO->h;
                                nodoO->padre = nodoActual;
                            }
                        }
                    }
                }
            }
            if(posMenorX-1 >= 0 && posMenorY-1 >= 0)
            {
                if(mapa2[posMenorX-1][posMenorY-1]==0) // OESTE o ABAJO
                {
                    if(mapa2[posMenorX-1][posMenorY]==0 && mapa2[posMenorX][posMenorY+1]==0) // OESTE o ABAJO
                    {
                        Nodo *nodoNO = todosNodos[posMenorX-1][posMenorY-1];
                        if(nodoNO->estaEnInterior == false){
                            if(nodoNO->estaEnFrontera == false){
                                nodoNO->padre = nodoActual;

                                nodoNO->g = nodoActual->g+14;
                                nodoNO->h = pow((pow((posDisJugX-(posMenorX-1)),2)+pow((posDisJugY-(posMenorY-1)),2)),0.5);
                                nodoNO->peso = nodoActual->g+14 + nodoNO->h;

                                nodoNO->estaEnFrontera = true;
                                listaFrontera.push_back(nodoNO);
                            }
                            else
                            {
                                if(nodoNO->g > nodoActual->g+14)
                                {
                                    nodoNO->g = nodoActual->g+14;
                                    nodoNO->peso = nodoActual->g+14 + nodoNO->h;
                                    nodoNO->padre = nodoActual;
                                }
                            }
                        }
                    }
                }
            }
            if(posMenorX+1 < mapDimY && posMenorY+1 < mapDimX)
            {
                if(mapa2[posMenorX+1][posMenorY+1]==0) // OESTE o ABAJO
                {
                    if(mapa2[posMenorX+1][posMenorY]==0 && mapa2[posMenorX][posMenorY+1]==0)
                    {
                        Nodo *nodoSE = todosNodos[posMenorX+1][posMenorY+1];
                        if(nodoSE->estaEnInterior == false){
                            if(nodoSE->estaEnFrontera == false){
                                nodoSE->padre = nodoActual;

                                nodoSE->g = nodoActual->g+14;
                                nodoSE->h = pow((pow((posDisJugX-(posMenorX+1)),2)+pow((posDisJugY-(posMenorY+1)),2)),0.5);
                                nodoSE->peso = nodoActual->g+14 + nodoSE->h;

                                nodoSE->estaEnFrontera = true;
                                listaFrontera.push_back(nodoSE);
                            }
                            else
                            {
                                if(nodoSE->g > nodoActual->g+14)
                                {
                                    nodoSE->g = nodoActual->g+14;
                                    nodoSE->peso = nodoActual->g+14 + nodoSE->h;
                                    nodoSE->padre = nodoActual;
                                }
                            }
                        }
                    }
                }
            }
            if(posMenorX-1 >= 0 && posMenorY+1 < mapDimX)
            {
                if(mapa2[posMenorX-1][posMenorY+1]==0) // OESTE o ABAJO
                {
                    if(mapa2[posMenorX-1][posMenorY]==0 && mapa2[posMenorX][posMenorY+1]==0) // OESTE o ABAJO
                    {
                        Nodo *nodoSO = todosNodos[posMenorX-1][posMenorY+1];
                        if(nodoSO->estaEnInterior == false){
                            if(nodoSO->estaEnFrontera == false){
                                nodoSO->padre = nodoActual;

                                nodoSO->g = nodoActual->g+14;
                                nodoSO->h = pow((pow((posDisJugX-(posMenorX-1)),2)+pow((posDisJugY-(posMenorY+1)),2)),0.5);
                                nodoSO->peso = nodoActual->g+14 + nodoSO->h;

                                nodoSO->estaEnFrontera = true;
                                listaFrontera.push_back(nodoSO);
                            }
                            else
                            {
                                if(nodoSO->g > nodoActual->g+14)
                                {
                                    nodoSO->g = nodoActual->g+14;
                                    nodoSO->peso = nodoActual->g+14 + nodoSO->h;
                                    nodoSO->padre = nodoActual;
                                }
                            }
                        }
                    }
                }
            }
            if(posMenorX+1 < mapDimY && posMenorY-1 >= 0)
            {
                if(mapa2[posMenorX+1][posMenorY-1]==0) // OESTE o ABAJO
                {
                    if(mapa2[posMenorX+1][posMenorY]==0 && mapa2[posMenorX][posMenorY-1]==0) // OESTE o ABAJO
                    {
                        Nodo *nodoNE = todosNodos[posMenorX+1][posMenorY-1];
                        if(nodoNE->estaEnInterior == false){
                            if(nodoNE->estaEnFrontera == false){
                                nodoNE->padre = nodoActual;

                                nodoNE->g = nodoActual->g+14;
                                nodoNE->h = pow((pow((posDisJugX-(posMenorX+1)),2)+pow((posDisJugY-(posMenorY-1)),2)),0.5);
                                nodoNE->peso = nodoActual->g+14 + nodoNE->h;

                                nodoNE->estaEnFrontera = true;
                                listaFrontera.push_back(nodoNE);
                            }
                            else
                            {
                                if(nodoNE->g > nodoActual->g+14)
                                {
                                    nodoNE->g = nodoActual->g+14;
                                    nodoNE->peso = nodoActual->g+14 + nodoNE->h;
                                    nodoNE->padre = nodoActual;
                                }
                            }
                        }
                    }
                }
            }



        }//end else
    }//end while
    listaNodosPadres.clear();
    Nodo *EmpiezaEnNodoJugador =  todosNodos[posDisJugY][posDisJugX];
    soyElEnemigo = false;

    if(EmpiezaEnNodoJugador != NULL){
        if((EmpiezaEnNodoJugador->x == nodoEnemigo->x && EmpiezaEnNodoJugador->y == nodoEnemigo->y) || (!EmpiezaEnNodoJugador->padre))
        {
        }
        else{
            while( (EmpiezaEnNodoJugador->x != nodoEnemigo->x && EmpiezaEnNodoJugador->y != nodoEnemigo->y) || meVoyaDormir == false)
            {
                if(EmpiezaEnNodoJugador->padre != NULL){
                    listaNodosPadres.push_back(EmpiezaEnNodoJugador);
                    EmpiezaEnNodoJugador = EmpiezaEnNodoJugador->padre;
                    //std::cout<< "TOTAL DE NODOS HASTA EL JUGADOR" <<listaNodosPadres.size() << std::endl;
                }
                else
                {
                    meVoyaDormir = true;
                }
            }
            distanciaNodosJugador=listaNodosPadres.size();
        }
    }
    //std::cout<< "TAMAÑO LISTA NODOS PADRE AL FINAL:  "<< listaNodosPadres.size() <<  std::endl;
/*
    for(int i = 0; i < listaNodosPadres.size(); i++)
    {
         //std::cout<< "TOTAL:  " << listaNodosPadres.size() <<  std::endl;
         //std::cout<< "POS X DE UN NODO:  " <<listaNodosPadres.at(i)->x << "POS Y DE UN NODO: " << listaNodosPadres.at(i)->y <<  std::endl;
         nodoSolucion.setFillColor(sf::Color::Magenta);
         nodoSolucion.setPosition(listaNodosPadres.at(i)->y*32.0, listaNodosPadres.at(i)->x*32.0);
         soluciones.push_back(nodoSolucion);
    }
*/
    if(listaNodosPadres.size() > 0)
    {

        inicioX = posDisEnemigY;
        inicioY = posDisEnemigX;

        finalX = listaNodosPadres.at(listaNodosPadres.size()-1)->x;
        finalY = listaNodosPadres.at(listaNodosPadres.size()-1)->y;

        //listaNodosPadres.at(listaNodosPadres.size()-2)->padre = NULL;

        //std::cout<< "INICIO:  "<< inicioX<< ","<< inicioY<< "  FINAL:" << finalX<< ","<< finalY<<  std::endl;
        if(finalX > inicioX && finalY == inicioY)
        {
            enemigoPos=1;
            siguientePosY=eneY+kTIledAncho;//abajo
        }
        else if(finalX > inicioX && finalY > inicioY)
        {
            enemigoPos=2;//diagonal derecha bajo
            siguientePosX=eneX+kTIledAlto;//abajo
            siguientePosY=eneY+kTIledAncho;//abajo
        }
        else if(finalX == inicioX && finalY > inicioY)
        {
            enemigoPos=3;//derecha
            siguientePosX=eneX+kTIledAlto;//abajo
        }
        else if(finalX < inicioX && finalY > inicioY)
        {
            enemigoPos=4;//diagonal derecha superior
            siguientePosX=eneX+kTIledAlto;//abajo
            siguientePosY=eneY-kTIledAncho;//abajo
        }
        else if(finalX < inicioX && finalY == inicioY)
        {
            enemigoPos=5;//arriba
            siguientePosY=eneY-kTIledAncho;//abajo
        }
        else if(finalX < inicioX && finalY < inicioY)
        {
            enemigoPos=6;//diagonal izquierda superior
            siguientePosX=eneX-kTIledAlto;//abajo
            siguientePosY=eneY-kTIledAncho;//abajo
        }
        else if(finalX == inicioX && finalY < inicioY)
        {
            enemigoPos=7;//izquierda
            siguientePosX=eneX-kTIledAlto;//abajo
        }
        else if(finalX > inicioX && finalY < inicioY)
        {
            enemigoPos=8;//diagonal izquierda bajo
            siguientePosX=eneX-kTIledAlto;//abajo
            siguientePosY=eneY+kTIledAncho;//abajo
        }
        else
            enemigoPos=0; //nada

    }
    else{
        enemigoPos=0;

    }

    for(int f=0;f<mapDimY;f++){
        for(int c=0;c<mapDimX;c++){
            todosNodos[f][c]->g = 0;
            todosNodos[f][c]->h = 0;
            todosNodos[f][c]->peso = 0;
            todosNodos[f][c]->padre = NULL;
            todosNodos[f][c]->estaEnInterior = false;
            todosNodos[f][c]->estaEnFrontera = false;
        }
    }

}

void Enemigo::movimientoEnemigo(float eneX, float eneY, float jugX, float jugY, float velocidadEnemigo, int mapDimY, int mapDimX)
{
    int movimiento;
    //std::cout<< eneY << "-" << siguientePosY << " " << eneX << "-" << siguientePosX << std::endl;
    if(int(eneX) == int(siguientePosX) && int(eneY) == int(siguientePosY))
    {
        //std::cout<< "SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << std::endl;
        calcularCamino(eneX, eneY, jugX, jugY,mapDimY,mapDimX);
    }

    //moverse
    switch(enemigoPos)
    {
        case 5: sprite->move(sf::Vector2f(0, -velocidadEnemigo));
            break;
        case 4: sprite->move(sf::Vector2f(velocidadEnemigo, -velocidadEnemigo));
            break;
        case 3: sprite->move(sf::Vector2f(velocidadEnemigo, 0));
            break;
        case 2: sprite->move(sf::Vector2f(velocidadEnemigo, velocidadEnemigo));
            break;
        case 1: sprite->move(sf::Vector2f(0, velocidadEnemigo));
            break;
        case 8: sprite->move(sf::Vector2f(-velocidadEnemigo, velocidadEnemigo));
            break;
        case 7: sprite->move(sf::Vector2f(-velocidadEnemigo, 0));
            break;
        case 6: sprite->move(sf::Vector2f(-velocidadEnemigo, -velocidadEnemigo));
            break;
    }
}


bool Enemigo::isVisible()
{
    if(sprite->getGlobalBounds().intersects(Motor2D::getViewRect()))
        return true;
    return false;
}
