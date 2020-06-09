#include "Roca.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Arma.h"
#include "Bomba.h"
#include "Llave.h"
#include "Roca.h"
#include "Pocion.h"

using namespace sf;
using namespace std;



Roca::Roca(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    //ctor
    cogible = true;
    string archivo = "resources/roca.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
}

Roca::~Roca()
{
    //dtor
}

void Roca::mover(int x, int y, vector<RectangleShape *> *rectangulos, vector<ObjetoMapa *> *objetos, Jugador *jugador){
    for(int i = 0; i < rectangulos->size(); i++){
        comprobarParedesEnUnaDireccion((*rectangulos)[i], 'x', x, y);
        comprobarParedesEnUnaDireccion((*rectangulos)[i], 'y', x, y);
    }
    for(int i = 0; i < objetos->size(); i++){
        if(sprite->getPosition().x != objetos->at(i)->getSprite()->getPosition().x && sprite->getPosition().y != objetos->at(i)->getSprite()->getPosition().y){
            if(objetos->at(i)->getPintable()){
                comprobarObjetosEnUnaDireccion(& *objetos->at(i), 'x', x, y);
                comprobarObjetosEnUnaDireccion(& *objetos->at(i), 'y', x, y);
            }
        }
    }

    comprobarParedesEnUnaDireccion(jugador->getBody(), 'x', x, y);
    comprobarParedesEnUnaDireccion(jugador->getBody(), 'y', x, y);

    cout << "Anterior: x " << sprite->getPosition().x << "| y " << sprite->getPosition().y << endl;
    if(movible) {
        //sprite->move(x*32, y*32);
        sprite->move(x*32, y*32);
        movible = false;
    }
    cout << "Posterior: x " << sprite->getPosition().x << "| y " << sprite->getPosition().y << endl;
}

void Roca::comprobarParedesEnUnaDireccion(RectangleShape *otro, char direccionEstudiada, int x, int y) {
    Vector2f auxDireccion;
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X') {
        auxDireccion = Vector2f(x, 0.f);
    } else {
        auxDireccion = Vector2f(0.f, y);
    }

    RectangleShape auxRect(Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height));
    auxRect.setPosition(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top);

    auxRect.move(auxDireccion * 32.f);
    if(auxRect.getGlobalBounds().intersects(otro->getGlobalBounds())) {
//        cout << "El jugador está en la posición " << sprite->getPosition().x << "," << sprite->getPosition().y << endl;
//        cout << "El auxRect está en la posición " << auxRect.getPosition().x << "," << auxRect.getPosition().y << endl;
//        cout << ". Ha encontrado una colisión con el rect que está en "
//            << otro->getGlobalBounds().left << ","
//            << otro->getGlobalBounds().top << " con una altura de "
//            << otro->getGlobalBounds().height << " y una anchura de "
//            << otro->getGlobalBounds().width << endl;
        /*
        if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
            direccion->x = 0.f;
        else
            direccion->y = 0.f;
        */
        movible = false;
    }
}

void Roca::comprobarObjetosEnUnaDireccion(ObjetoMapa *otro, char direccionEstudiada, int x, int y) {
    Vector2f auxDireccion;
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X') {
        auxDireccion = Vector2f(x, 0.f);
    } else {
        auxDireccion = Vector2f(0.f, y);
    }

    RectangleShape auxRect(Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height));
    auxRect.setPosition(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top);

    auxRect.move(auxDireccion * 32.f);
    if(auxRect.getGlobalBounds().intersects(otro->getSprite()->getGlobalBounds())) {
        movible = false;

        if(Arma* v = dynamic_cast<Arma*>(otro)) {
           cout << "Roca: hay un arma" << endl;
        }
        if(Llave* l = dynamic_cast<Llave*>(otro)){
            cout << "Roca: hay una llave" << endl;
        }
        if(Bomba* b = dynamic_cast<Bomba*>(otro)){
            cout << "Roca: hay una bomba" << endl;
        }
        if(Pocion* p = dynamic_cast<Pocion*>(otro)){
            cout << "Roca: hay una pocion" << endl;
        }
        if(Roca* r = dynamic_cast<Roca*>(otro)){
            cout << "Roca: hay una roca" << endl;
        }
        if(Puerta* pu = dynamic_cast<Puerta*>(otro)){
            cout << "Roca: hay una puerta" << endl;
        }
        if(Caja* ca = dynamic_cast<Caja*>(otro)){
            cout << "Roca: hay una caja" << endl;
        }
    }
}

