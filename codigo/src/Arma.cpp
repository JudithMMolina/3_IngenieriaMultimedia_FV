#include "Arma.h"
#include "Jugador.h"
#include "Bala.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Enemigo;

Arma::Arma(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    //ctor
    string archivo = "resources/arma1.png";
    if (tipo == 2)
        archivo = "resources/arma2.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);

    tipoArma = tipo;
    balas = new vector<Bala *>;
    duenyo = nullptr;

    if(tipoArma == 1)
        tiempoCadencia = 1.3f;
    else
        tiempoCadencia = .55f;

    clockGun = new sf::Clock();

}

Arma::~Arma()
{
    //dtor
}

void Arma::disparar(vector<Enemigo *> *enemigos) {
    if(duenyo != nullptr) {
        //cout << "Me ha disparado el jugador " << duenyo->getNombre() << endl;
        Bala* newbala;

        if(clockGun->getElapsedTime().asSeconds() >= tiempoCadencia){

            clockGun->restart();

            int danyo = 25;

            if(tipoArma == 2)
                danyo = 15;

            newbala = new Bala(this, enemigos, danyo);
            balas->push_back(newbala);
        }

    }
}

void Arma::update() {
    for(int i = 0; i < balas->size(); i++)
    {
        Bala *bala = (*balas)[i];
        if(bala->isVisible())
        {
            if(bala->getColisionado()){
                delete (*balas)[i];
                balas->erase((*balas).begin()+i);
            }
            else{
                Bala *balaActual = (*balas)[i];
                balaActual->update();
            }
        } else {
            delete (*balas)[i];
            balas->erase((*balas).begin()+i);
        }
    }
}

void Arma::render() {
    for(int i = 0; i < balas->size(); i++) {
        Bala *balaActual = (*balas)[i];
        balaActual->render();
    }
}
