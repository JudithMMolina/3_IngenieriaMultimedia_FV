#include "Jugador2.h"
#include "iostream"

using namespace std;

Jugador2::Jugador2() : Jugador()
{
    //ctor
    Texture *texture = new Texture();
    /*
    texture->loadFromFile("rojo.png");
    sprite->setTexture(*texture);
    sprite->setPosition(128.0, 96.0);
    */

    // Rudolf Bot
    texture->loadFromFile("resources/todoBot.png");
    sprite->setTexture(*texture);
    sprite->setTextureRect(IntRect(0*64, 7*64, 64, 64));
    sprite->setPosition(128.0, 96.0);


    animacionStopUp->anyadirFrames(0, 1, 4, 64);
    animacionStopUp->anyadirFrame(IntRect(0*64, 4*64, 64, 64));
    animacionStopUp->anyadirFrame(IntRect(0*64, 4*64, 64, 64));
    animacionStopUp->anyadirFrame(IntRect(0*64, 4*64, 64, 64));
    animacionStopLeft->anyadirFrames(0, 1, 5, 64);
    animacionStopLeft->anyadirFrame(IntRect(0*64, 5*64, 64, 64));
    animacionStopLeft->anyadirFrame(IntRect(0*64, 5*64, 64, 64));
    animacionStopLeft->anyadirFrame(IntRect(0*64, 5*64, 64, 64));
    animacionStopDown->anyadirFrames(0, 1, 2, 64);
    animacionStopDown->anyadirFrame(IntRect(0*64, 2*64, 64, 64));
    animacionStopDown->anyadirFrame(IntRect(0*64, 2*64, 64, 64));
    animacionStopDown->anyadirFrame(IntRect(0*64, 2*64, 64, 64));
    //animacionStopDown->anyadirFrames(0, 1, 6, 64);
    animacionStopRight->anyadirFrames(0, 1, 7, 64);
    animacionStopRight->anyadirFrame(IntRect(0*64, 7*64, 64, 64));
    animacionStopRight->anyadirFrame(IntRect(0*64, 7*64, 64, 64));
    animacionStopRight->anyadirFrame(IntRect(0*64, 7*64, 64, 64));

    animacionUpArcoChachi->anyadirFrames(0, 12, 20, 64);
    animacionLeftArcoChachi->anyadirFrames(0, 12, 21, 64);
    animacionDownArcoChachi->anyadirFrames(0, 12, 22, 64);
    animacionRightArcoChachi->anyadirFrames(0, 12, 23, 64);

    animacionMuerte->anyadirFrames(4, 5, 24, 64);


    teclaArriba = Keyboard::I;
    teclaAbajo  = Keyboard::K;
    teclaIzquierda = Keyboard::J;
    teclaDerecha   = Keyboard::L;

    teclaDisparo = Keyboard::U;
    teclaInteractuar = Keyboard::O;
    teclaCambioArma = Keyboard::P;

    teclaDios = Keyboard::F2;

    enAgua = false;

    nombre = "rudolfbot";

    posSigX=sprite->getPosition().x;
    posSigY=sprite->getPosition().y;
    posAntX=posSigX;
    posAntY=posSigY;
}

Jugador2::~Jugador2()
{
    //dtor
}

void Jugador2::update(sf::Time timeElapsed)
{
    posAntX=posSigX;
    posAntY=posSigY;

    Jugador::update(timeElapsed);

    //Jugador::mover(otro);
    //comprobarColisiones(mapa->getRectangulosParedes());
    comprobarAgua(mapa->getRectangulosAgua());

    //comprobarColisiones(mapa->getRectangulosParedes());
    //cout << "Hemos llamado al update de jugador 2" << endl; //

    moverRoca();


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
    //std::cout << "jugador 1 --> " << direccion->x << std::endl;
    posSigX=posAntX+direccion->x*timeElapsed.asMilliseconds()*0.02;
    posSigY=posAntY+direccion->y*timeElapsed.asMilliseconds()*0.02;
    Jugador::comprobarColisiones(mapa->getRectangulosParedes());
    comprobarEscaleras(mapa->getRectangulosEscaleras());
    Jugador::comprobarRocas();
    Jugador::comprobarCajas();
}

void Jugador2::comprobarAgua(vector<RectangleShape *> *agua) {
    for(unsigned int i = 0; i < agua->size(); i++) { //Recorre el array de agua
        comprobarAguaEnUnaDireccion((*agua)[i]); //Comprueba la colision con cada uno de ellos
    }

    if(enAgua){ //Si se encuentra en el agua
        if((jugadorClock.getElapsedTime() - tiempoAguaDeceleracion).asSeconds() > 0.4){ //y pasan 0.4 segundos
            tiempoAguaDeceleracion = jugadorClock.getElapsedTime(); //actualiza la variable tiempo
            modificarVida(kDanyoAgua); //le baja vida
            modificarVelocidad(-2.25f); //lo ralentiza
            cout << "Ugh, agua. Me queda: " << getVida() << " de vida. Mi velocidad es: " << getVelocidad() << endl;
        }
    } else if((jugadorClock.getElapsedTime() - tiempoAguaAceleracion).asSeconds() > 0.4) { //si no esta en el agua y pasan 0.4 segundos
        tiempoAguaAceleracion = jugadorClock.getElapsedTime(); //actualiza la variable tiempo
        modificarVelocidad(2.5f); //lo acelera
        //cout << "Ah, no agua. Mi velocidad es: " << getVelocidad() << endl;
    }
    enAgua = false; //Tras comprobar las colisiones, reiniciamos la variable
}

void Jugador2::comprobarAguaEnUnaDireccion(RectangleShape *otro) {

    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height)); //Crea un rectangulo de colision
    auxRect.setPosition(body->getGlobalBounds().left, body->getGlobalBounds().top); //Lo coloca

    if(auxRect.getGlobalBounds().intersects(otro->getGlobalBounds())) {
        enAgua = true; //Si intersecta es que esta en la electricidad
    }
}

void Jugador2::comprobarEscaleras(vector<RectangleShape *> *rectangulos) {
    for(unsigned int i = 0; i < rectangulos->size(); i++) {
        comprobarEscalerasEnUnaDireccion((*rectangulos)[i], 'x');
        comprobarEscalerasEnUnaDireccion((*rectangulos)[i], 'y');
    }
}


void Jugador2::comprobarEscalerasEnUnaDireccion(RectangleShape *otro, char direccionEstudiada) {
    Vector2f auxDireccion;
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X') {
        auxDireccion = Vector2f(direccion->x, 0.f);
    } else {
        auxDireccion = Vector2f(0.f, direccion->y);
    }
     if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
        Jugador::body->setPosition(posSigX,posAntY);
    else
        Jugador::body->setPosition(posAntX,posSigY);

    //RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    //auxRect.setPosition(body->getGlobalBounds().left, body->getGlobalBounds().top);

    //auxRect.move(auxDireccion * velocidad);
    if(/*auxRect.*/body->getGlobalBounds().intersects(otro->getGlobalBounds())) {
    //cout<<"Ha colisionado"<<endl;
//        cout << "El jugador está en la posición " << sprite->getPosition().x << "," << sprite->getPosition().y << endl;
//        cout << "El auxRect está en la posición " << auxRect.getPosition().x << "," << auxRect.getPosition().y << endl;
//        cout << ". Ha encontrado una colisión con el rect que está en "
//            << otro->getGlobalBounds().left << ","
//            << otro->getGlobalBounds().top << " con una altura de "
//            << otro->getGlobalBounds().height << " y una anchura de "
//            << otro->getGlobalBounds().width << endl;
        if(direccionEstudiada == 'x' || direccionEstudiada == 'X'){
            Jugador::direccion->x = 0.f;
            Jugador::posSigX=posAntX;
            //setDireccionX(0.f);
        }else{
            Jugador::direccion->y = 0.f;
            Jugador::posSigY=posAntY;
        }
            //setDireccionY(0.f);
        //cout<<"x: "<<getDireccion()->x<<". y: "<<getDireccion()->y<<endl; //Comentario de relleno para el nombre de version
    }
}

void Jugador2::moverRoca(){
    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaInteractuar)){
        for(int i = 0; i < grupoRocas->size(); i++){
            Roca* roquita = (Roca*) grupoRocas->at(i);
            if(roquita->getMovible()){
                /*if(direccionBala.x != 0 && direccionBala.y == 0) {
                    roquita->getSprite()->move(*direccionBala);
                } else if(direccionBala.x == 0 && direccionBala.y != 0){

                }*/
                //float aux = *direccionBala->x;
               // aux*=8;
                int ejex = 0;
                int ejey = 0;
                if(abs(direccionBala->x) != abs(direccionBala->y)){
                    if((direccionBala->x) != 0) ejex = direccionBala->x;
                    if((direccionBala->y) != 0) ejey = direccionBala->y;
                    //roquita->getSprite()->move(ejex*32, ejey*32);
                    //roquita->setMovible(false); //Comentario de cambio de nombre
                    roquita->mover(ejex, ejey, mapa->getRectangulosParedes(), todosObjetos, otro);
                }


            }
        }
    }
}
