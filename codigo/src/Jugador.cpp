#include "Juego.h"
#include "Jugador.h"
#include "Mapa.h"
#include "Arma.h"
#include "ObjetoMapa.h"
#include "Constantes.h"
#include "Globales.h"

#include "Arma.h"
#include "Bomba.h"
#include "Llave.h"
#include "Roca.h"
#include "Pocion.h"
#include "Enemigo.h"

#include <SFML/Graphics.hpp>
#include <iostream>



using namespace sf;
using namespace std;

Jugador::Jugador()
{
    //ctor
    objetoMetaNivel = nullptr;

    sprite = new Sprite();
    body = new sf::RectangleShape();
    body->setSize(sf::Vector2f(25.0, 32.0));
    if(Constantes::DEBUG)
        body->setFillColor(sf::Color(80.0,120.0,50.0,200.0));
    else
        body->setFillColor(sf::Color(80.0,120.0,50.0,0.0));

    body->setOrigin(sf::Vector2f(sprite->getOrigin().x - 20.0, sprite->getOrigin().y - 30.0));
    body->setPosition(sprite->getPosition());

    //sprite->setPosition(256.0, 128.0);
    //sprite->setScale(1, 1);

    //Animmaciones
    animacionStopUp = new Animacion(sprite, seconds(0.3), false);
    animacionStopLeft = new Animacion(sprite, seconds(0.3), false);
    animacionStopDown = new Animacion(sprite, seconds(0.3), false);
    animacionStopRight = new Animacion(sprite, seconds(0.3), false);

    animacionUp = new Animacion(sprite, seconds(0.08), false);
    animacionLeft = new Animacion(sprite, seconds(0.08), false);
    animacionDown = new Animacion(sprite, seconds(0.08), false);
    animacionRight = new Animacion(sprite, seconds(0.08), false);

    animacionUpCuchillo = new Animacion(sprite, seconds(0.065), false);
    animacionLeftCuchillo = new Animacion(sprite, seconds(0.065), false);
    animacionDownCuchillo = new Animacion(sprite, seconds(0.065), false);
    animacionRightCuchillo = new Animacion(sprite, seconds(0.065), false);

    animacionUpArcoCutre = new Animacion(sprite, seconds(0.1), false);
    animacionLeftArcoCutre = new Animacion(sprite, seconds(0.1), false);
    animacionDownArcoCutre = new Animacion(sprite, seconds(0.1), false);
    animacionRightArcoCutre = new Animacion(sprite, seconds(0.1), false);

    animacionUpArcoChachi = new Animacion(sprite, seconds(0.05), false);
    animacionLeftArcoChachi = new Animacion(sprite, seconds(0.05), false);
    animacionDownArcoChachi = new Animacion(sprite, seconds(0.05), false);
    animacionRightArcoChachi = new Animacion(sprite, seconds(0.05), false);

    animacionMuerte = new Animacion(sprite, seconds(0.5), false);
    /*
    animacionStopUp->anyadirFrame(IntRect(0*64, 8*64, 64, 64));
    animacionStopUp->anyadirFrame(IntRect(1*64, 8*64, 64, 64));
    animacionStopLeft->anyadirFrame(IntRect(0*64, 9*64, 64, 64));
    animacionStopLeft->anyadirFrame(IntRect(8*64, 9*64, 64, 64));
    animacionStopDown->anyadirFrame(IntRect(0*64, 10*64, 64, 64));
    animacionStopDown->anyadirFrame(IntRect(1*64, 10*64, 64, 64));
    animacionStopRight->anyadirFrame(IntRect(0*64, 11*64, 64, 64));
    animacionStopRight->anyadirFrame(IntRect(8*64, 11*64, 64, 64));
    */

    animacionUp->anyadirFrames(0, 8, 8, 64); //empieza, acaba, fila, medidas
    animacionLeft->anyadirFrames(0, 8, 9, 64);
    animacionDown->anyadirFrames(0, 8, 10, 64);
    animacionRight->anyadirFrames(0, 8, 11, 64);

    animacionUpCuchillo->anyadirFrames(0, 5, 12, 64);
    animacionLeftCuchillo->anyadirFrames(0, 5, 13, 64);
    animacionDownCuchillo->anyadirFrames(0, 5, 14, 64);
    animacionRightCuchillo->anyadirFrames(0, 5, 15, 64);

    animacionUpArcoCutre->anyadirFrames(0, 12, 16, 64);
    animacionLeftArcoCutre->anyadirFrames(0, 12, 17, 64);
    animacionDownArcoCutre->anyadirFrames(0, 12, 18, 64);
    animacionRightArcoCutre->anyadirFrames(0, 12, 19, 64);

    animMuerto = false;
    tiempoMuerto = 15;

    animacionActual = animacionStopRight;



    direccion = new Vector2f();
    direccion->x = 0;
    direccion->y = 0;

    direccionBala = new Vector2f();
    direccionBala->x = 1.f;
    direccionBala->y = 0.f;

    nombre = "";
    armaChachi = nullptr;
    //armaChachi = new Arma(0, 0, 2);
    //armaChachi->setJugador(this);
    armaCutre = nullptr;
    bomba = nullptr;
    llave = nullptr;
    //barraVida = sf::RectangleShape(50,10);
    //barraVida.setSize(50,10);
    //sf::RectangleShape barraVida(sf::Vector2f(50,10));
    //barraVida.setPosition(sprite->getPosition().x - 20, sprite->getPosition().y - 40);
    //barraVida.setOrigin(0, 10/2);


    arma = 0;
    //arma = 2;


    teclaArriba = 0;
    teclaAbajo = 0;
    teclaIzquierda = 0;
    teclaDerecha = 0;

    teclaDisparo = 0;
    teclaInteractuar = 0;
    teclaCambioArma = 0;

    //teclaDios = Keyboard::F3;
    modoDios = false;

    velocidad = 8.f;
    vida = 100;

    seleccionado = 0;

    todosObjetos = new std::vector<ObjetoMapa *>;

    grupoArmas = new std::vector<Arma *>;
    grupoLlaves = new std::vector<Llave *>;
    grupoBombas = new std::vector<Bomba *>;
    grupoPociones = new std::vector<Pocion *>;
    grupoRocas = new std::vector<Roca *>;
    grupoPuertas = new std::vector<Puerta *>;
    grupoCajas = new std::vector<Caja *>;

    objetosUpdate = false;

    tiempoCambioArma = sf::Time::Zero;
    tiempoCuchillada = sf::Time::Zero;
    tiempoEncimaEnemigo = sf::Time::Zero;
}

Jugador::~Jugador()
{
    //dtor
}

void Jugador::update(sf::Time timeElapsed)
{
    if(bomba!=nullptr && bomba->getExplotado()==true)
    {
        bomba = nullptr;
    }
    //cout << "Hemos llamado al update de jugador" << endl;
    int posAntesX = sprite->getPosition().x;
    int posAntesY = sprite->getPosition().y;
    direccion->x = 0.f;
    direccion->y = 0.f;

    //separaObjetos(objetos);


    mover(otro);
    controles();
    //comprobarColisiones(mapa->getRectangulosParedes()); -> se hace en los jugadores

    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    auxRect.setPosition(body->getGlobalBounds().left, body->getGlobalBounds().top); //Bounding box del jugador
    cogerArma(auxRect);
    cogerLlave(auxRect);
    cogerBomba(auxRect);
    cogerPocion(auxRect);
    cogerObjetoMetaNivel(auxRect);
    //comprobarRocas(); //auxRect
    comprobarEnemigos();
    comprobarPuertas();

    abrirPuerta();

    //Animacion
    if(vida <= 0)
    {
        animacionActual = animacionMuerte;
        if(tiempoMuerto == 0)
        {
            animMuerto = true;
        }
        if(tiempoMuerto > 0)
        {
            tiempoMuerto--;
        }
    }
    animacionActual->update(timeElapsed);


    //Para que puedan cerrar la ventana y no se ponga gris la pantalla //
    sf::RenderWindow *window = Juego::getInstance()->getWindow();
    // Process events
    sf::Event event;
    //input(window, event);
    while (window->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyReleased:
            {
                if(event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }

                break;
            }
        }
    }




    if(armaChachi != nullptr) {
        armaChachi->update();
    } else if(armaCutre != nullptr) {
        armaCutre->update();
    }


}


void Jugador::mover(Jugador *otro)
{
    Vector2i posMia = Juego::getInstance()->getWindow()->mapCoordsToPixel(sprite->getPosition());
    Vector2i posOtro = Juego::getInstance()->getWindow()->mapCoordsToPixel(otro->getSprite()->getPosition());

    bool debug = false;

    //cout << "Pos mapeada en ventana " << posMia.x << "," << posMia.y << endl;


    // lo que hacemos aquí es que si nos estamos moviendo, marcamos las rocas y las puertas como no abribles ni movibles
    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba)
        || Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo)
        || Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda)
        || Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha))
    {
        for(int i = 0; i < grupoRocas->size(); i++)
        {
            Roca* roquita = (Roca*) grupoRocas->at(i);
            roquita->setMovible(false);
        }
        for(int i = 0; i < grupoPuertas->size(); i++)
        {
            Puerta* puertita = (Puerta*) grupoPuertas->at(i);
            puertita->setAbrible(false);
        }
    }

    if(ataqueClock.getElapsedTime().asSeconds() > 0.3)
    {
        if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo) //Up !Down
            && posMia.y < Mapa::tamanyoZonaCalienteArriba
            && posOtro.y > Constantes::TAMANYO_VENTANA_Y - Mapa::tamanyoZonaCalienteAbajo)
        {
            if(debug) std::cout << "bloqueo movimiento arriba porque el otro está abajo" << std::endl;
            direccion->y = 0.f;
            Juego::getInstance()->getDireccionView()->y = 0.f;
            //direccionBala->y = -1.f;

        }
        else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba) //Down !Up
            && posOtro.y < Mapa::tamanyoZonaCalienteArriba
            && posMia.y > Constantes::TAMANYO_VENTANA_Y - Mapa::tamanyoZonaCalienteAbajo)
        {
            if(debug) std::cout << "bloqueo movimiento abajo porque el otro está arriba" << std::endl;
            direccion->y = 0.f;
            Juego::getInstance()->getDireccionView()->y = 0.f;
            //direccionBala->y = 1.f;

        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo) //Up !Down
            && posMia.y < Mapa::tamanyoZonaCalienteArriba) {
            if(debug) std::cout << "muevo hacia arriba monigote y ventana" << std::endl;
            direccion->y = -1.f;
            Juego::getInstance()->getDireccionView()->y = -1.f;
            //direccionBala->y = -1.f;

        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba) // Down !Up
            && posMia.y > Constantes::TAMANYO_VENTANA_Y - Mapa::tamanyoZonaCalienteAbajo) {
            if(debug) std::cout << "muevo hacia abajo monigote y ventana" << std::endl;
            direccion->y = 1.f;
            Juego::getInstance()->getDireccionView()->y = 1.f;
            //direccionBala->y = 1.f;

        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo)) { //Up !Down
            if(debug) std::cout << "muevo hacia arriba monigote" << std::endl;
            direccion->y = -1.f;
            //direccionBala->y = -1.f;

        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba)) { //Down !Up
            if(debug) std::cout << "muevo hacia abajo monigote" << std::endl;
            direccion->y = 1.f;
            //direccionBala->y = 1.f;
        }



        if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda) //Right !Left
            && posMia.x > Constantes::TAMANYO_VENTANA_X - Mapa::tamanyoZonaCalienteDch
            && posOtro.x < Mapa::tamanyoZonaCalienteIzq) {
            if(debug) std::cout << "bloqueo movimiento derecha porque el otro está izquierda" << std::endl;
            direccion->x = 0.f;
            Juego::getInstance()->getDireccionView()->x = 0.f;
            //direccionBala->x = 1.f;

        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha) //Left !Right
            && posOtro.x > Constantes::TAMANYO_VENTANA_X - Mapa::tamanyoZonaCalienteDch
            && posMia.x < Mapa::tamanyoZonaCalienteIzq) {
            if(debug) std::cout << "bloqueo movimiento izquierda porque el otro está derecha" << std::endl;
            direccion->x = 0.f;
            Juego::getInstance()->getDireccionView()->x = 0.f;
            //direccionBala->x = -1.f;

        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda) //Right !Left
            && posMia.x > Constantes::TAMANYO_VENTANA_X - Mapa::tamanyoZonaCalienteDch) {
            if(debug) std::cout << "muevo derecha monigote y ventana" << std::endl;
            direccion->x = 1.f;
            Juego::getInstance()->getDireccionView()->x = 1.f;
            //direccionBala->x = 1.f;
        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha) //Left !Right
            && posMia.x < Mapa::tamanyoZonaCalienteIzq) {
            if(debug) std::cout << "muevo izquierda monigote y ventana" << std::endl;
            direccion->x = -1.f;
            Juego::getInstance()->getDireccionView()->x = -1.f;
            //direccionBala->x = -1.f;
        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha)) { //Left !Right
            if(debug) std::cout << "muevo izquierda" << std::endl;
            direccion->x = -1.f;
            //direccionBala->x = -1.f;
        } else if (Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda)) { //Right !Left
            if(debug) std::cout << "muevo derecha" << std::endl;
            direccion->x = 1.f;
            //direccionBala->x = 1.f;
        }

    }
    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDerecha)) {
        if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba)) {
            direccionBala->x = 1.f;
            direccionBala->y = -1.f;
        } else if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo)){
            direccionBala->x = 1.f;
            direccionBala->y = 1.f;
        } else {
            direccionBala->x = 1.f;
            direccionBala->y = 0.f;
        }
    } else if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaIzquierda)){
        if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba)) {
            direccionBala->x = -1.f;
            direccionBala->y = -1.f;
        } else if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo)){
            direccionBala->x = -1.f;
            direccionBala->y = 1.f;
        } else {
            direccionBala->x = -1.f;
            direccionBala->y = 0.f;
        }
    } else if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaArriba)){
        direccionBala->x = 0.f;
        direccionBala->y = -1.f;
    } else if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaAbajo)){
        direccionBala->x = 0.f;
        direccionBala->y = 1.f;
    }

    if(debug) {
        if(direccionBala->x == 1.f) cout << "Derecha" << endl;
        if(direccionBala->x == -1.f) cout << "Izquierda" << endl;
        if(direccionBala->y == 1.f) cout << "Abajo" << endl;
        if(direccionBala->y == -1.f) cout << "Arriba" << endl;
    }


    //Animaciones
    if(direccion->x == 0.f && direccion->y == 0.f) {
        //cout << "Mirar hacia donde no me muevo con la direcion de la bala que es la que se queda hacia la ultia direcion pulsada" << endl;
        if(!Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDisparo) && !Keyboard::isKeyPressed((sf::Keyboard::Key)teclaInteractuar)) {
            if(direccionBala->x == 1.f) { //Derecha
                animacionActual = animacionStopRight;
            } else if(direccionBala->x == -1.f) { //Izquierda
                animacionActual = animacionStopLeft;
            } else if(direccionBala->y == -1.f) { //Arriba
                animacionActual = animacionStopUp;
            } else if(direccionBala->y == 1.f) { //Abajo
                animacionActual = animacionStopDown;
            }
        }
    } else if(direccion->x == 1.f) { //Derecha
        animacionActual = animacionRight;
        //cout << "Estoy en el frame " << animacionActual->getFrameActual() << endl;
    } else if(direccion->x == -1.f) { //Izquierda
        animacionActual = animacionLeft;
    } else if(direccion->y == -1.f) { //Arriba
        animacionActual = animacionUp;
    } else if(direccion->y == 1.f) { //Abajo
        animacionActual = animacionDown;
    }

}


// OK
void Jugador::controles()
{
    //Si tal poner el reloj aqui
    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDisparo))
    {
        if(armaChachi != nullptr)
        {
            if(seleccionado == armaChachi->getTipoArma())
            {
                //Animaciones
                if(direccionBala->x == 1.f) { //Derecha
                    animacionActual = animacionRightArcoChachi;
                } else if(direccionBala->x == -1.f) { //Izquierda
                    animacionActual = animacionLeftArcoChachi;
                } else if(direccionBala->y == -1.f) { //Arriba
                    animacionActual = animacionUpArcoChachi;
                } else if(direccionBala->y == 1.f) { //Abajo
                    animacionActual = animacionDownArcoChachi;
                }
                if(relojDisparo.getElapsedTime().asSeconds() > 0.4) {
                    armaChachi->disparar(enemigos);
                    //relojDisparo.restart();
                }
                //cout << "He disparado la chachi" << endl;
            } //cout << "Chachi: " << seleccionado << " y " << armaChachi->getTipoArma() << endl;
        }
        if(armaCutre != nullptr) {
            if(seleccionado == armaCutre->getTipoArma()) { //armaCutre != nullptr && //comentario para el nombre de version
                //Animaciones
                if(direccionBala->x == 1.f) { //Derecha
                    animacionActual = animacionRightArcoCutre;
                } else if(direccionBala->x == -1.f) { //Izquierda
                    animacionActual = animacionLeftArcoCutre;
                } else if(direccionBala->y == -1.f) { //Arriba
                    animacionActual = animacionUpArcoCutre;
                } else if(direccionBala->y == 1.f) { //Abajo
                    animacionActual = animacionDownArcoCutre;
                }
                if(relojDisparo.getElapsedTime().asSeconds() > 0.8) {
                    armaCutre->disparar(enemigos);
                    //relojDisparo.restart();
                }
                //cout << "He disparado la cutre" << endl;
            }//cout << "Cutre: " << seleccionado << " y " << armaCutre->getTipoArma() << endl;
        }
        if(seleccionado == 0) if((jugadorClock.getElapsedTime() - tiempoCuchillada).asSeconds() > 0.75){
            //Animaciones
            if(direccionBala->x == 1.f) { //Derecha
                animacionActual = animacionRightCuchillo;
            } else if(direccionBala->x == -1.f) { //Izquierda
                animacionActual = animacionLeftCuchillo;
            } else if(direccionBala->y == -1.f) { //Arriba
                animacionActual = animacionUpCuchillo;
            } else if(direccionBala->y == 1.f) { //Abajo
                animacionActual = animacionDownCuchillo;
            }
            acuchillar(enemigos);
            tiempoCuchillada = jugadorClock.getElapsedTime();
        }
        if(seleccionado == 3) tirarBomba();
        ataqueClock.restart();
    } else {
        relojDisparo.restart();
        //animacionRightArcoChachi->setTiempoFrame(sf::seconds(0));
        animacionRightArcoChachi->resetFrameActual();
        animacionLeftArcoChachi->resetFrameActual();
        animacionUpArcoChachi->resetFrameActual();
        animacionDownArcoChachi->resetFrameActual();

        animacionRightArcoCutre->resetFrameActual();
        animacionLeftArcoCutre->resetFrameActual();
        animacionUpArcoCutre->resetFrameActual();
        animacionDownArcoCutre->resetFrameActual();

        //cout << "Frame: " << animacionRightArcoChachi->getFrameActual() << endl;
    }



    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaCambioArma))
    {
        if((jugadorClock.getElapsedTime() - tiempoCambioArma).asSeconds() > 0.25)
        {
            tiempoCambioArma = jugadorClock.getElapsedTime();
            cambiarArma();
        }
    }
    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaDios))
    {
        if((jugadorClock.getElapsedTime() - tiempoCambioArma).asSeconds() > 0.25)
        {
            tiempoCambioArma = jugadorClock.getElapsedTime();
            if(!modoDios) modoDios = true;
            else modoDios = false;
        }
    }

    /*if(Keyboard::isKeyPressed((sf::Keyboard::Key)sf::Keyboard::G)){
        if(!modoDios) modoDios = true;
        else modoDios = false;
    }*/



}


void Jugador::comprobarColisiones(vector<RectangleShape *> *rectangulos)
{
    for(unsigned int i = 0; i < rectangulos->size(); i++)
    {
        RectangleShape *rectActual = (*rectangulos)[i];
        if(rectActual->getGlobalBounds().intersects(Motor2D::getViewRect()))
        {
            comprobarColisionesEnUnaDireccion(rectActual, 'x');
            comprobarColisionesEnUnaDireccion(rectActual, 'y');
        }
    }
}


void Jugador::comprobarColisionesEnUnaDireccion(RectangleShape *otro, char direccionEstudiada)
{
    // ELIMINADO VALDÉS
    /*Vector2f auxDireccion;
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X') {
        auxDireccion = Vector2f(direccion->x, 0.f);
    } else {
        auxDireccion = Vector2f(0.f, direccion->y);
    }*/
    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    auxRect.setOrigin(sf::Vector2f(sprite->getOrigin().x - 20.0, sprite->getOrigin().y - 30.0));
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
        auxRect.setPosition(posSigX,posAntY);
    else
        auxRect.setPosition(posAntX,posSigY);
    if(auxRect.getGlobalBounds().intersects(otro->getGlobalBounds()))
    {
        if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
        {
            direccion->x = 0.f;
            posSigX=posAntX;
        }
        else
        {
            direccion->y = 0.f;
            posSigY=posAntY;
        }
    }
}

void Jugador::modificarVida(int v){
    if(!modoDios)
    {
        vida += v;
        //barraVida.setSize(sf::Vector2f(vida / 2, barraVida.getSize().y));
        if(vida <= 0) vida = 0;
        if(vida >= 100) vida = 100;

        if(vida == 0)
        {
            cout << "Estoy muerto" << endl;
        }
    }
}

void Jugador::modificarVelocidad(float vel){
    velocidad += vel;

    if(velocidad < 2.0f) velocidad = 2.0f;
    if(velocidad > 8.f) velocidad = 8.f;
}

void Jugador::separaObjetos(vector<ObjetoMapa *> *objetos)
{
    //Si no se habian cargado previamente
    if(!objetosUpdate)
    {
        //recorre el array de objetos y los serpara en funcion del tipo
        for(int i = 0; i < objetos->size(); i++)
        {
            if(Arma* v = dynamic_cast<Arma*>(objetos->at(i))) {
               grupoArmas->push_back(v);
            }
            else if(Llave* l = dynamic_cast<Llave*>(objetos->at(i))){
                grupoLlaves->push_back(l);
            }
            else if(Bomba* b = dynamic_cast<Bomba*>(objetos->at(i))){
                grupoBombas->push_back(b);
            }
            else if(Pocion* p = dynamic_cast<Pocion*>(objetos->at(i))){
                grupoPociones->push_back(p);
            }
            else if(Roca* r = dynamic_cast<Roca*>(objetos->at(i))){
                grupoRocas->push_back(r);
            }
            else if(Puerta* pu = dynamic_cast<Puerta*>(objetos->at(i))){
                grupoPuertas->push_back(pu);
            }
            else if(Caja* ca = dynamic_cast<Caja*>(objetos->at(i))){
                grupoCajas->push_back(ca);
            }
            else if(ObjetoMetaNivel* obj = dynamic_cast<ObjetoMetaNivel*>(objetos->at(i))){
                objetoMetaNivel = obj;
            }
        }
        objetosUpdate = true;
    }
    todosObjetos = objetos;
}

void Jugador::cogerArma(RectangleShape auxRect)
{
    //Recorre el array de armas y comprueba si colisiona
    for(int i = 0; i < grupoArmas->size(); i++)
    {
        Arma *armaActual = (*grupoArmas)[i];

        //si colisiona
        if(auxRect.getGlobalBounds().intersects(armaActual->getSprite()->getGlobalBounds()))
        {
            Arma* armita = grupoArmas->at(i);
            if(arma != armita->getTipoArma() && armita->getCogible()){ //Si es cogible y no tiene ya ese arma
                if(arma == 0){ //si no tiene ningun arma
                    arma = armita->getTipoArma(); //tendra solo el que ha cogido
                    if(arma == 1){
                        armaCutre = armaActual;
                        armaCutre->setJugador(this);
                    } else if(arma == 2){
                        armaChachi = armaActual;
                        armaChachi->setJugador(this);
                    }
                    armita->setCogible(false); //ya no se puede coger
                    armita->setPintable(false);
                } else{ //implica que tiene el otro arma
                    arma = 3; //tendra ambas armas
                    if(armita->getTipoArma() == 1){
                        armaCutre = armaActual;
                        armaCutre->setJugador(this);
                    } else if(armita->getTipoArma() == 2){
                        armaChachi = armaActual;
                        armaChachi->setJugador(this);
                    }
                    armita->setCogible(false); //ya no se puede coger
                    armita->setPintable(false);
                }
                cout << "El jugador de este arma es " << armaActual->getJugador()->getNombre() << endl;
            }
        }
    }

    //cout << grupoArmas->at(0)->getSprite()->getPosition().x << endl; Comentario de excusa para cambio de version
}

void Jugador::cogerLlave(RectangleShape auxRect)
{
    for(int i = 0; i < grupoLlaves->size(); i++)
    {
        //crea el bounding box del arma
        RectangleShape auxRect2(Vector2f(grupoLlaves->at(i)->getSprite()->getGlobalBounds().width, grupoLlaves->at(i)->getSprite()->getGlobalBounds().height));
        auxRect2.setPosition(grupoLlaves->at(i)->getSprite()->getGlobalBounds().left, grupoLlaves->at(i)->getSprite()->getGlobalBounds().top);

        //si colisiona
        if(auxRect.getGlobalBounds().intersects(auxRect2.getGlobalBounds()))
        {
            Llave* llavecita = grupoLlaves->at(i);

            //Si es cogible y no tiene ya ese arma
            if(llave==nullptr && llavecita->getCogible())
            {
                llave = llavecita;
                llavecita->setCogible(false); //ya no se puede coger
                llavecita->setPintable(false);

            }
        }
    }
}

void Jugador::cogerBomba(RectangleShape auxRect)
{
    for(int i = 0; i < grupoBombas->size(); i++)
    {
        //crea el bounding box del arma
        RectangleShape auxRect2(Vector2f(grupoBombas->at(i)->getSprite()->getGlobalBounds().width, grupoBombas->at(i)->getSprite()->getGlobalBounds().height));
        auxRect2.setPosition(grupoBombas->at(i)->getSprite()->getGlobalBounds().left, grupoBombas->at(i)->getSprite()->getGlobalBounds().top);

        Bomba* bombita = grupoBombas->at(i);
        if(!bombita->getExplotado())
        {
            //si colisiona
            if(auxRect.getGlobalBounds().intersects(auxRect2.getGlobalBounds()))
            {
                //Si es cogible y no tiene ya esa bomba
                if(bomba==0 && bombita->getCogible())
                {
                    bombita->setCogible(false); //ya no se puede coger
                    bombita->setPintable(false);
                    bomba = bombita;
                    grupoBombas->erase(grupoBombas->begin() + i);
                }
            }
        } else grupoBombas->erase(grupoBombas->begin() + i);
    }
}

void Jugador::cogerPocion(RectangleShape auxRect)
{
    for(int i = 0; i < grupoPociones->size(); i++)
    {
        //crea el bounding box del arma
        RectangleShape auxRect2(Vector2f(grupoPociones->at(i)->getSprite()->getGlobalBounds().width, grupoPociones->at(i)->getSprite()->getGlobalBounds().height));
        auxRect2.setPosition(grupoPociones->at(i)->getSprite()->getGlobalBounds().left, grupoPociones->at(i)->getSprite()->getGlobalBounds().top);
        Pocion* pocioncita = grupoPociones->at(i);

        //si colisiona
        if(auxRect.getGlobalBounds().intersects(auxRect2.getGlobalBounds()) && pocioncita->getCogible())
        {
            modificarVida(pocioncita->getVida());
            pocioncita->setCogible(false);
            pocioncita->setPintable(false);

            grupoPociones->erase(grupoPociones->begin() + i);
        }
    }
}

void Jugador::cogerObjetoMetaNivel(RectangleShape auxRect)
{
    if(objetoMetaNivel != nullptr)
    {
        //si colisiona
        if(auxRect.getGlobalBounds().intersects(objetoMetaNivel->getSprite()->getGlobalBounds()) && objetoMetaNivel->getCogible())
        {
            if(Globales::JSON_NIVEL_SELECCIONADO == Constantes::JSON_NIVEL_EUROPA)
                Globales::NIVEL_EUROPA_SUPERADO = true;
            else if(Globales::JSON_NIVEL_SELECCIONADO == Constantes::JSON_NIVEL_AMERICA)
                Globales::NIVEL_AMERICA_SUPERADO = true;
            else if(Globales::JSON_NIVEL_SELECCIONADO == Constantes::JSON_NIVEL_ANTARTIDA)
                Globales::NIVEL_ANTARTIDA_SUPERADO = true;
            Utils::guardarPartida();
            Constantes::PUEDE_PARAR_MUSICA_INGAME = true;
            Juego::getInstance()->setState(State::Estados::NIVEL_SUPERADO);
        }
    }}

void Jugador::comprobarRocas()
{
    //Recorre el array de armas y comprueba si colisiona
    for(int i = 0; i < grupoRocas->size(); i++)
    {
        Roca* roquita = grupoRocas->at(i);
        if(roquita->isVisible())
        {
            comprobarRocasEnUnaDireccion(& *roquita, 'x');
            comprobarRocasEnUnaDireccion(& *roquita, 'y');
        }
    }
}

void Jugador::comprobarRocasEnUnaDireccion(Roca *roquita, char direccionEstudiada)
{
    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    auxRect.setOrigin(sf::Vector2f(sprite->getOrigin().x - 20.0, sprite->getOrigin().y - 30.0));
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
        auxRect.setPosition(posSigX,posAntY);
    else
        auxRect.setPosition(posAntX,posSigY);
    if(auxRect.getGlobalBounds().intersects(roquita->getSprite()->getGlobalBounds()))
    {
        roquita->setMovible(true);

        if(direccionEstudiada == 'x' || direccionEstudiada == 'X'){
            direccion->x = 0.f;
            posSigX=posAntX;
        }else{
            direccion->y = 0.f;
            posSigY=posAntY;
        }
    }
}

void Jugador::comprobarCajas()
{
    //Recorre el array de armas y comprueba si colisiona
    for(int i = 0; i < grupoCajas->size(); i++)
    {
        Caja* cajita = grupoCajas->at(i);
        if(cajita->getPintable())
        {
            comprobarCajasEnUnaDireccion(& *cajita, 'x');
            comprobarCajasEnUnaDireccion(& *cajita, 'y');
        }
    }
}

void Jugador::comprobarCajasEnUnaDireccion(Caja *cajita, char direccionEstudiada)
{
    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    auxRect.setOrigin(sf::Vector2f(sprite->getOrigin().x - 20.0, sprite->getOrigin().y - 30.0));
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
        auxRect.setPosition(posSigX,posAntY);
    else
        auxRect.setPosition(posAntX,posSigY);
    if(auxRect.getGlobalBounds().intersects(cajita->getSprite()->getGlobalBounds()))
    {
        if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
        {
            direccion->x = 0.f;
            posSigX=posAntX;
        }
        else
        {
            direccion->y = 0.f;
            posSigY=posAntY;
        }
    }
}

void Jugador::comprobarPuertas()
{
    for(int i = 0; i < grupoPuertas->size(); i++)
    {
        Puerta* puertita = grupoPuertas->at(i);
        if(puertita->isVisible())
        {
            comprobarPuertasEnUnaDireccion(& *puertita, 'x');
            comprobarPuertasEnUnaDireccion(& *puertita, 'y');
        }
    }
}

void Jugador::comprobarPuertasEnUnaDireccion(Puerta *puertita, char direccionEstudiada)
{
    Vector2f auxDireccion;
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X') {
        auxDireccion = Vector2f(direccion->x, 0.f);
    } else {
        auxDireccion = Vector2f(0.f, direccion->y);
    }

    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    auxRect.setPosition(body->getGlobalBounds().left, body->getGlobalBounds().top);

    auxRect.move(auxDireccion * velocidad);
    /*
    RectangleShape rect = sf::RectangleShape(Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height));
    rect.setFillColor(sf::Color::Red);
    Juego::getInstance()->getWindow()->draw(rect);
    */

    if(auxRect.getGlobalBounds().intersects(puertita->getSprite()->getGlobalBounds())) {
        puertita->setAbrible(true);
        if(!puertita->getAbierta()){
            if(direccionEstudiada == 'x' || direccionEstudiada == 'X'){
                direccion->x = 0.f;
                //posSigX=posAntX;
            }else{
                direccion->y = 0.f;
                //posSigY=posAntY;
            }
        }
    }
}

void Jugador::abrirPuerta()
{
    if(Keyboard::isKeyPressed((sf::Keyboard::Key)teclaInteractuar))
    {
        for(int i = 0; i < grupoPuertas->size(); i++){
            Puerta* puertita = (Puerta*) grupoPuertas->at(i);
            if(puertita->getAbrible() && llave != nullptr)
            {
                puertita->abrir();
                if(puertita->getTipo()==1) {
                    Puerta* auxPuerta = (Puerta*) grupoPuertas->at(i+1);
                    auxPuerta->abrir();
                }
                else if(puertita->getTipo()==2) {
                    Puerta* auxPuerta = (Puerta*) grupoPuertas->at(i-1);
                    auxPuerta->abrir();
                }
                llave = nullptr;
            }
        }
    }
}


void Jugador::comprobarEnemigos()
{
    for(int i = 0; i < enemigos->size(); i++)
    {
        Enemigo *enemigoActual = (*enemigos)[i];
        if(enemigoActual->isVisible())
        {
            comprobarEnemigosEnUnaDireccion(enemigoActual, 'y');
            comprobarEnemigosEnUnaDireccion(enemigoActual, 'x');
        }
    }
}

void Jugador::comprobarEnemigosEnUnaDireccion(Enemigo *enemigo, char direccionEstudiada)
{
    Vector2f auxDireccion;
    if(direccionEstudiada == 'x' || direccionEstudiada == 'X')
    {
        auxDireccion = Vector2f(direccion->x, 0.f);
    }
    else
    {
        auxDireccion = Vector2f(0.f, direccion->y);
    }

    RectangleShape auxRect(Vector2f(body->getGlobalBounds().width, body->getGlobalBounds().height));
    auxRect.setPosition(body->getGlobalBounds().left, body->getGlobalBounds().top);

    auxRect.move(auxDireccion * velocidad);
    if(auxRect.getGlobalBounds().intersects(enemigo->getSprite()->getGlobalBounds()))
    {
        if((jugadorClock.getElapsedTime() - tiempoEncimaEnemigo).asSeconds() > 1)
        {
            tiempoEncimaEnemigo = jugadorClock.getElapsedTime();
            modificarVida(-5);
        }
    }
}

void Jugador::render(double percentTick)
{
    posFinX=(posSigX-posAntX)*percentTick+posAntX;
    posFinY=(posSigY-posAntY)*percentTick+posAntY;
    sprite->setPosition(posFinX,posFinY);

    body->setPosition(posFinX, posFinY);
    //body->setPosition(sf::Vector2f(sprite->getPosition().x + 20.0, sprite->getPosition().y + 32.0));

    RectangleShape *DireccionBarra = new RectangleShape();
    DireccionBarra->setOrigin(Vector2f(0, 15));
    DireccionBarra->setSize(Vector2f(2, 42));
    DireccionBarra->setPosition(sprite->getPosition().x + (sprite->getGlobalBounds().width / 2), sprite->getPosition().y + (sprite->getGlobalBounds().height / 2));
    DireccionBarra->setFillColor(Color(255, 255, 255, 255));


    int rotacion = 0;

    if(direccionBala->x == 1.f){
        if(direccionBala->y == 1.f) rotacion = 315;
        if(direccionBala->y == 0.f) rotacion = 270;
        if(direccionBala->y == -1.f) rotacion = 235;

    } else if(direccionBala->x == -1.f){
        if(direccionBala->y == 1.f) rotacion = 45;
        if(direccionBala->y == 0.f) rotacion = 90;
        if(direccionBala->y == -1.f) rotacion = 135;
    } else if(direccionBala->x == 0.f){
        if(direccionBala->y == 1.f) rotacion = 0;
        if(direccionBala->y == -1.f) rotacion = 180;
    }

    DireccionBarra->setRotation(rotacion);
    //cout << direccion->x << endl;
    //Juego::getInstance()->getWindow()->draw(*DireccionBarra);
    DireccionBarra = NULL;
    delete DireccionBarra;

/*

    RectangleShape *VidaBarraMarco = new RectangleShape();
    VidaBarraMarco->setSize(Vector2f(100/2.25, 6));
    VidaBarraMarco->setPosition(sprite->getPosition().x - 7, sprite->getPosition().y -14);
    VidaBarraMarco->setFillColor(Color(128, 128, 128, 170));
    VidaBarraMarco->setOutlineColor(Color(0, 0, 0, 255));
    VidaBarraMarco->setOutlineThickness(1);
    Juego::getInstance()->getWindow()->draw(*VidaBarraMarco);
    VidaBarraMarco = NULL;
    delete VidaBarraMarco;


    //Juego::getInstance()->getWindow()->draw(*VidaBarra);
    RectangleShape *VidaBarra = new RectangleShape();
    VidaBarra->setSize(Vector2f(vida/2.25, 6));
    VidaBarra->setPosition(sprite->getPosition().x - 7, sprite->getPosition().y -14);
    if(modoDios) VidaBarra->setFillColor(Color(244, 238, 66, 255));
    else VidaBarra->setFillColor(Color(255, 255, 255, 255));
    Juego::getInstance()->getWindow()->draw(*VidaBarra);
    VidaBarra = NULL;
    delete VidaBarra;
*/

    if(seleccionado == 2)
        armaChachi->render();
    else if(seleccionado == 1)
        armaCutre->render();

    Juego::getInstance()->getWindow()->draw(*getSprite());
    Juego::getInstance()->getWindow()->draw(*body);
}

void Jugador::pintarBarras(){
    RectangleShape *VidaBarraMarco = new RectangleShape();
    VidaBarraMarco->setSize(Vector2f(100/2.25, 6));
    VidaBarraMarco->setPosition(sprite->getPosition().x + 8, sprite->getPosition().y -3);
    VidaBarraMarco->setFillColor(Color(128, 128, 128, 170));
    VidaBarraMarco->setOutlineColor(Color(0, 0, 0, 255));
    VidaBarraMarco->setOutlineThickness(1);
    Juego::getInstance()->getWindow()->draw(*VidaBarraMarco);
    VidaBarraMarco = NULL;
    delete VidaBarraMarco;


    //Juego::getInstance()->getWindow()->draw(*VidaBarra);
    RectangleShape *VidaBarra = new RectangleShape();
    VidaBarra->setSize(Vector2f(vida/2.25, 6));
    VidaBarra->setPosition(sprite->getPosition().x + 8, sprite->getPosition().y -3);
    if(modoDios) VidaBarra->setFillColor(Color(244, 238, 66, 255));
    else VidaBarra->setFillColor(Color(255, 255, 255, 255));
    Juego::getInstance()->getWindow()->draw(*VidaBarra);
    VidaBarra = NULL;
    delete VidaBarra;
}

void Jugador::setDatos(Jugador *nuevoOtro, Mapa *nuevoMapa, vector<ObjetoMapa *> *nuevoObjetos, vector<Enemigo *> *nuevoEnemigos, Vector2f *posInicial) {
    separaObjetos(nuevoObjetos);
    mapa = nuevoMapa;
    otro = nuevoOtro;
    enemigos = nuevoEnemigos;
    sprite->setPosition(*posInicial);
    posAntX = posInicial->x;
    posAntY = posInicial->y;
    posSigX = posInicial->x;
    posSigY = posInicial->y;
}

void Jugador::cambiarArma(){
    seleccionado+=1;
    if(seleccionado > 3) seleccionado = 0;
    cout << "Selec: " << seleccionado << endl;
    if(seleccionado == 1){
        if(armaCutre == nullptr) Jugador::cambiarArma();
    } else if(seleccionado == 2){
        if(armaChachi == nullptr) Jugador::cambiarArma();
    } else if(seleccionado == 3){
        if(bomba == 0) Jugador::cambiarArma();
    }
}

void Jugador::acuchillar(vector<Enemigo *> *enem){ //Hacer una clase arma o cuchillo
    RectangleShape auxRect(Vector2f(sprite->getGlobalBounds().width, sprite->getGlobalBounds().height));
    auxRect.setPosition(sprite->getGlobalBounds().left, sprite->getGlobalBounds().top);

    auxRect.move(direccionBala->x * 16, direccionBala->y * 16);

    for(int i = 0; i < enem->size(); i++){
        if(auxRect.getGlobalBounds().intersects(enem->at(i)->getSprite()->getGlobalBounds())){
            enem->at(i)->bajarVida(20);
            cout << "He acuchillado a un enemigo" << endl;
        }
    }
}

void Jugador::tirarBomba(){
    bomba->setCogible(false);
    bomba->setPintable(true);
    bomba->getSprite()->setPosition(body->getPosition().x + 16, body->getPosition().y + 32);
    //bomba->getSprite()->move(50,50);
    bomba->explosion(enemigos, grupoCajas);
    //grupoBombas->push_back(bomba);

    bomba = nullptr;

    cambiarArma();
}
