#include "Jugador1.h"
#include "Mapa.h"
#include "iostream"

using namespace std;

Jugador1::Jugador1() : Jugador()
{
    //ctor
    Texture *texture = new Texture();
    /*
    texture->loadFromFile("azul.png");
    sprite->setTexture(*texture);
    */

    // Sara
    texture->loadFromFile("resources/todoSara.png");
    sprite->setTexture(*texture);
    sprite->setTextureRect(IntRect(0*64, 3*64, 64, 64));

    animacionStopUp->anyadirFrames(0, 1, 0, 64);
    animacionStopUp->anyadirFrame(IntRect(0*64, 0*64, 64, 64));
    animacionStopUp->anyadirFrame(IntRect(0*64, 0*64, 64, 64));
    animacionStopUp->anyadirFrame(IntRect(0*64, 0*64, 64, 64));
    animacionStopLeft->anyadirFrames(0, 1, 1, 64);
    animacionStopLeft->anyadirFrame(IntRect(0*64, 1*64, 64, 64));
    animacionStopLeft->anyadirFrame(IntRect(0*64, 1*64, 64, 64));
    animacionStopLeft->anyadirFrame(IntRect(0*64, 1*64, 64, 64));
    animacionStopDown->anyadirFrames(0, 1, 2, 64);
    animacionStopDown->anyadirFrame(IntRect(0*64, 2*64, 64, 64));
    animacionStopDown->anyadirFrame(IntRect(0*64, 2*64, 64, 64));
    animacionStopDown->anyadirFrame(IntRect(0*64, 2*64, 64, 64));
    animacionStopRight->anyadirFrames(0, 1, 3, 64);
    animacionStopRight->anyadirFrame(IntRect(0*64, 3*64, 64, 64));
    animacionStopRight->anyadirFrame(IntRect(0*64, 3*64, 64, 64));
    animacionStopRight->anyadirFrame(IntRect(0*64, 3*64, 64, 64));

    animacionUpArcoChachi->anyadirFrames(0, 12, 21, 64);
    animacionLeftArcoChachi->anyadirFrames(0, 12, 22, 64);
    animacionDownArcoChachi->anyadirFrames(0, 12, 23, 64);
    animacionRightArcoChachi->anyadirFrames(0, 12, 24, 64);

    animacionMuerte->anyadirFrames(4, 5, 20, 64);


    teclaArriba = Keyboard::W;
    teclaAbajo  = Keyboard::S;
    teclaIzquierda = Keyboard::A;
    teclaDerecha   = Keyboard::D;

    teclaDisparo = Keyboard::Q;
    teclaInteractuar = Keyboard::E;
    teclaCambioArma = Keyboard::R;

    teclaDios = Keyboard::F1;

    enElectricidad = false;
    //tiempoElectricidad = 0;

    nombre = "sara";

    posSigX=sprite->getPosition().x;
    posSigY=sprite->getPosition().y;
    posAntX=posSigX;
    posAntY=posSigY;
}

Jugador1::~Jugador1()
{
    //dtor
}

void Jugador1::update(sf::Time timeElapsed)
{
    posAntX=posSigX;
    posAntY=posSigY;

    Jugador::update(timeElapsed);

    comprobarElectricidad(mapa->getRectangulosElectricidad());
    //cout << "Hemos llamado al update de jugador 1" << endl;


    if(Keyboard::isKeyPressed((sf::Keyboard::Key)sf::Keyboard::G)){
        if((jugadorClock.getElapsedTime() - tiempoCambioArma).asSeconds() > 0.25){
            if(!modoDios) modoDios = true;
            else modoDios = false;
            tiempoCambioArma = jugadorClock.getElapsedTime();
        }
    }

    *direccion *= getVelocidad();
    //cout << "Vamos a mover al monigote en una velocidad x de " << direccion->x << " y una velocidad y de " << direccion->y << endl;
    //sprite->move(*direccion);
    //std::cout << direccion->x << std::endl;
    //std::cout << "jugador 1 --> " << direccion->x << std::endl;
    posSigX=posAntX+direccion->x*timeElapsed.asMilliseconds()*0.02;
    posSigY=posAntY+direccion->y*timeElapsed.asMilliseconds()*0.02;
    Jugador::comprobarColisiones(mapa->getRectangulosParedes());
    Jugador::comprobarRocas();
    Jugador::comprobarCajas();
    //sprite->setPosition(sprite->getPosition().x + direccion->x, sprite->getPosition().y + direccion->y);
}

void Jugador1::comprobarElectricidad(vector<RectangleShape *> *electricidad) {
    for(unsigned int i = 0; i < electricidad->size(); i++) { //Recorre el array de electricidad
        comprobarElectricidadEnUnaDireccion((*electricidad)[i]); //Comprueba la colision con cada uno de ellos
    }

    if(enElectricidad){ //Si se encuentra en la electricidad
        if((jugadorClock.getElapsedTime() - tiempoElectricidadDeceleracion).asSeconds() > 0.4){ //y pasan 0.4 segundos
            tiempoElectricidadDeceleracion = jugadorClock.getElapsedTime(); //actualiza la variable tiempo
            modificarVida(kDanyoElectricidad); //le baja vida
            modificarVelocidad(-2.25f); //lo ralentiza
            cout << "Ugh, electricidad. Me queda: " << getVida() << " de vida. Mi velocidad es: " << getVelocidad() << endl;
        }
    } else if((jugadorClock.getElapsedTime() - tiempoElectricidadAceleracion).asSeconds() > 0.4) { //si no esta en la electricidad y pasan 0.4 segundos
        tiempoElectricidadAceleracion = jugadorClock.getElapsedTime(); //actualiza la variable tiempo
        modificarVelocidad(2.5f); //lo acelera
        //cout << "Ah, no electricidad. Mi velocidad es: " << getVelocidad() << endl;
    }

    enElectricidad = false; //Tras comprobar las colisiones, reiniciamos la variable
}

void Jugador1::comprobarElectricidadEnUnaDireccion(RectangleShape *otro) {

    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height)); //Crea un rectangulo de colision
    auxRect.setPosition(body->getGlobalBounds().left, body->getGlobalBounds().top); //Lo coloca

    if(auxRect.getGlobalBounds().intersects(otro->getGlobalBounds())) {
        enElectricidad = true; //Si intersecta es que esta en la electricidad
    }
}
