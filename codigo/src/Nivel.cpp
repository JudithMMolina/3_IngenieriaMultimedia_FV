#include "Nivel.h"
#include <iostream>
#include <Enemigo.h>

using namespace std;

Nivel::Nivel()
{
    //ctor
    mapa = new Mapa();
    enemigos = new std::vector<Enemigo *>;
    objetos = new std::vector<ObjetoMapa *>;
    balas1 = new std::vector<Bala *>;
    balas2 = new std::vector<Bala *>;
    spawns = new std::vector<sf::Vector2f *>;
}

Nivel::~Nivel()
{
    //dtor
    delete mapa;
    enemigos->clear();
    enemigos->shrink_to_fit();
    delete enemigos;
    objetos->clear();
    objetos->shrink_to_fit();
    delete objetos;
    balas1->clear();
    balas1->shrink_to_fit();
    delete balas1;
    balas2->clear();
    balas2->shrink_to_fit();
    delete balas2;
    spawns->clear();
    spawns->shrink_to_fit();
    delete spawns;
}


void Nivel::pintarEnemigos(sf::RenderWindow &window, double percentTick) {
    for(int i = 0; i < enemigos->size(); i++)
    {
        Enemigo *enemigoActual = (*enemigos)[i];
        if(enemigoActual->isVisible())
        {
            enemigoActual->render(&window);
            enemigoActual->render(&window, percentTick);
        }
    }
}

void Nivel::pintarObjetos(sf::RenderWindow &window) {
    for(int i = 0; i < objetos->size(); i++)
        if(((*objetos)[i]->getPintable()))
            window.draw((*(*objetos)[i]->getSprite()));
}

void Nivel::update(Jugador *jugador1, Jugador *jugador2, sf::Time timeElapsed)
{
    for (int i = 0; i < enemigos->size(); i++)
    {
        Enemigo *enemigoActual = (*enemigos)[i];
        if(enemigoActual->getVivo() == false){
            delete (*enemigos)[i];
            enemigos->erase((*enemigos).begin()+i);
        }
        else
        {
            if(enemigoActual->isVisible())
            {
                //cout << "analizamos este enemigo porque sí se ve" << endl;
                enemigoActual->update();
                enemigoActual->update(jugador1, jugador2, mapa, timeElapsed);
                enemigoActual->update(jugador1, jugador2, mapa);

                if(enemigoActual->getGenerarEnemigos() != 0 && enemigos->size() < 20)
                {
                    cout << "Genera los enemigos" << endl;
                    generarEnemigo(enemigoActual->getGenerarEnemigos());
                }
            }
        }
    }
    for (int i = 0; i < objetos->size(); i++)
    {
        ObjetoMapa *objetoActual = (*objetos)[i];
        if(objetoActual != nullptr && objetoActual != NULL && objetoActual->isVisible())
        {
            try
            {
                objetoActual->update();
            } catch (exception e)
            {
                cout << "Me parece haber visto un lindo gatito" << " e->" << e.what() << endl;
            }
        }
    }
}


void Nivel::generarEnemigo(int numEnemigos)
{
    for(int i=0;i<numEnemigos;i++){
        int num = int(rand()%5+1); // random entre 1 y 6
        int posSpawn = int(rand()%4); // random entre 0 y 3
        int posSpawnX=300;
        int posSpawnY=200;

        if(posSpawn==0){
            posSpawnX=494;
            posSpawnY=272;
        }else if(posSpawn==1){
            posSpawnX=494;
            posSpawnY=562;
        }else if(posSpawn==2){
            posSpawnX=912;
            posSpawnY=562;
        }else if(posSpawn==3){
            posSpawnX=912;
            posSpawnY=272;
        }

        if(num==4 || num==5 || num==3)
            num=2;

        Enemigo *enemigo = EnemigoFactory::crearEnemigo(posSpawnX, posSpawnY, num);
        enemigos->push_back(enemigo);
    }
}





