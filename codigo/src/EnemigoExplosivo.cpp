#include "EnemigoExplosivo.h"


const int EnemigoExplosivo::RANGO_DETECCION=450;
const int EnemigoExplosivo::RANGO_PARPADEO=75;


EnemigoExplosivo::EnemigoExplosivo(int posX, int posY)
{
    vida=100;
    item=0;
    enemigoVivo=true;

    distancia=0.0;
    dentroDelRadio=false;

    animacionAndarClock.restart();
    animacionExplosion.restart();
    rangeClock.restart();

    sf::Texture *tex2 = new Texture();
    if (!tex2->loadFromFile("resources/enemigo1.png"))
    {
        std::cerr << "Error cargando la imagen enemigo1.png";
        exit(0);
    }
    sprite= new sf::Sprite(*tex2);
    sprite->setScale(2, 2);
    sprite->setOrigin(16/2,17/2);
    sprite->setTextureRect(sf::IntRect(1*16, 2*17, 16, 17));
    sprite->setPosition(posX, posY);

    sf::Texture *texExplosion = new Texture();
    if (!texExplosion->loadFromFile("resources/Explosion_enemigo1.png"))
    {
        std::cerr << "Error cargando la imagen Explosion_enemigo1.png";
        exit(0);
    }
    spriteExplosion= new sf::Sprite(*texExplosion);
    spriteExplosion->setScale(0.6, 0.6);
    spriteExplosion->setOrigin(240/2,224/2);

    mostrar=false;
    animacionExplotarMuerte=false;

    siguientePosX = sprite->getPosition().x;
    siguientePosY = sprite->getPosition().y;

    /*animacionStop = new Animacion(sprite, seconds(2.0), false);
    animacionUp = new Animacion(sprite, seconds(0.3), false);
    animacionLeft = new Animacion(sprite, seconds(0.3), false);
    animacionDown = new Animacion(sprite, seconds(0.3), false);
    animacionRight = new Animacion(sprite, seconds(0.3), false);
    animacionUpAtaque = new Animacion(sprite, seconds(0.15), false);
    animacionLeftAtaque = new Animacion(sprite, seconds(0.15), false);
    animacionDownAtaque = new Animacion(sprite, seconds(0.15), false);
    animacionRightAtaque = new Animacion(sprite, seconds(0.15), false);*/
}


EnemigoExplosivo::~EnemigoExplosivo()
{
    //delete spriteExplosion;
    //dtor
}


void EnemigoExplosivo::render(sf::RenderWindow *window)
{
    if(enemigoVivo==true){
        if(mostrar==false)
            window->draw(*sprite);
        else
            window->draw(*spriteExplosion);
    }
}


void EnemigoExplosivo::update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa)
{
    float distancia1=0.0;
    float distancia2=0.0;
    float posXJug1 = jugador1->getBody()->getPosition().x+32;
    float posYJug1 = jugador1->getBody()->getPosition().y+32;
    float posXJug2 = jugador2->getBody()->getPosition().x+32;
    float posYJug2 = jugador2->getBody()->getPosition().y+32;


    mapa2 = mapa->getMapaCalorParedes(); // esto se puede optimizar poniendolo al crear

    int cols = mapa->getMapTileWidth();
    int rows = mapa->getMapTileHeight();

    if(vida>0)
    {
        distancia1=pow((pow((posXJug1-sprite->getPosition().x),2)+pow(posYJug1-sprite->getPosition().y,2)),0.5);
        distancia2=pow((pow((posXJug2-sprite->getPosition().x),2)+pow(posYJug2-sprite->getPosition().y,2)),0.5);

        if(distancia1<=distancia2)
            distancia=distancia1;
        else
            distancia=distancia2;

        // calcula el tiempo que pasa el jugador dentro del radio de explosion
        if(distancia<RANGO_DETECCION)
        {
            animacionMovimiento(); // Metodo animacion: andar y parpadera

            // Comprobar explosion y bajarle vida a los jugadores en caso de estar en el rango
            //cout << distanciaNodosJugador << endl;
            if(distancia<RANGO_PARPADEO && (distanciaNodosJugador<5 || distanciaNodosJugador==100))
            {
                if(dentroDelRadio==false)
                {
                    dentroDelRadio=true;
                    rangeClock.restart();
                }
                else
                {
                    if(rangeClock.getElapsedTime().asSeconds()>2.0)
                    {
                        vida=0;
                        animacionExplotarMuerte=true;
                        animacionExplosion.restart();
                        if(distancia1<RANGO_PARPADEO)
                        {
                            //std::cout << "Vida del jugador 1 reducida" << std::endl;
                            bajarVidaJugador1(jugador1);
                        }
                        if(distancia2<RANGO_PARPADEO)
                        {
                            //std::cout << "Vida del jugador 2 reducida" << std::endl;
                            bajarVidaJugador2(jugador2);
                        }
                    }
                }
            }
            else
            {
                dentroDelRadio=false;
            }

            if(distancia1<=distancia2)
                movimientoEnemigo(sprite->getPosition().x, sprite->getPosition().y, posXJug1, posYJug1, VELOCIDAD_ENEMIGO_1 , rows, cols);
            else
                movimientoEnemigo(sprite->getPosition().x, sprite->getPosition().y, posXJug2, posYJug2, VELOCIDAD_ENEMIGO_1 , rows, cols);
        }else{
            animacionReposo();
        }
    }


    if(recibirDanyo==true && tiempoEnRojo.getElapsedTime().asMilliseconds()>300.0)
        recibirDanyo=false;

    if(vida<=0 && enemigoVivo==true && animacionExplotarMuerte==true){
        animacionExplotar();
    }else if(vida<=0 && enemigoVivo==true && animacionExplotarMuerte==false){
        enemigoVivo=false;
        spriteExplosion=nullptr;
        delete spriteExplosion;
        delete sprite;
    }
}


// genera la animación de explotar del enemigo
void EnemigoExplosivo::animacionExplotar()
{
    if(mostrar==false)
        animacionExplosion.restart();
    mostrar = true;
    spriteExplosion->setPosition(sprite->getPosition());

    if(animacionExplosion.getElapsedTime().asSeconds()<0.05)
        spriteExplosion->setTextureRect(sf::IntRect(2*240, 1*224, 240, 224));
    else if(animacionExplosion.getElapsedTime().asSeconds()<0.1)
        spriteExplosion->setTextureRect(sf::IntRect(1*240, 1*224, 240, 224));
    else if(animacionExplosion.getElapsedTime().asSeconds()<0.15)
        spriteExplosion->setTextureRect(sf::IntRect(0*240, 1*224, 240, 224));
    else if(animacionExplosion.getElapsedTime().asSeconds()<0.2)
        spriteExplosion->setTextureRect(sf::IntRect(2*240, 0*224, 240, 224));
    else if(animacionExplosion.getElapsedTime().asSeconds()<0.25)
        spriteExplosion->setTextureRect(sf::IntRect(1*240, 0*224, 240, 224));
    else if(animacionExplosion.getElapsedTime().asSeconds()<0.3)
        spriteExplosion->setTextureRect(sf::IntRect(0*240, 0*224, 240, 224));
    else if(animacionExplosion.getElapsedTime().asSeconds()<0.4){
        animacionExplotarMuerte=false;
        enemigoVivo=false;
        delete spriteExplosion;
        spriteExplosion=nullptr;
    }
}

void EnemigoExplosivo::animacionReposo(){
    if(recibirDanyo==false){
        if(animacionReposoReloj.getElapsedTime().asSeconds()<2.0)
            sprite->setTextureRect(sf::IntRect(4*16, 3*17, 16, 17));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<2.5)
            sprite->setTextureRect(sf::IntRect(4*16, 1*17, 16, 17));
        else
            animacionReposoReloj.restart();
    }else{
        if(animacionReposoReloj.getElapsedTime().asSeconds()<2.0)
            sprite->setTextureRect(sf::IntRect(9*16, 3*17, 16, 17));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<2.5)
            sprite->setTextureRect(sf::IntRect(9*16, 1*17, 16, 17));
        else
            animacionReposoReloj.restart();
    }
}


void EnemigoExplosivo::bajarVidaJugador1(Jugador *jugador1)
{
        //std::cout << "Vida del jugador 1 reducida POR EL AEREO" << std::endl;
        jugador1->modificarVida(-DANYO_ENEMIGO_1);
}


void EnemigoExplosivo::bajarVidaJugador2(Jugador *jugador2)
{
        //std::cout << "Vida del jugador 2 reducida POR EL AEREO" << std::endl;
        jugador2->modificarVida(-DANYO_ENEMIGO_1);
}


// genera la animación de parpadeo de explosion y movimiento del enemigo
void EnemigoExplosivo::animacionMovimiento()
{
    switch(enemigoPos)
    {
        case 5:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(1*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(1*16, 3*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(2*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(2*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(6*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(6*16, 3*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(7*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(7*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 4:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(3*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(3*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(3*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(3*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(8*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(8*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(8*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(8*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 3:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(3*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(3*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(3*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(3*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(8*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(8*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(8*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(8*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 2:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(3*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(3*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(3*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(3*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(8*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(8*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(8*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(8*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 1:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(1*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(1*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(2*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(2*16, 2*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(6*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(6*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(7*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(7*16, 2*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 8:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(0*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(0*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(0*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(0*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(5*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(5*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(5*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(5*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 7:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(0*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(0*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(0*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(0*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                 if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(5*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(5*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(5*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(5*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;

        case 6:
            if(recibirDanyo==false){
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(0*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(0*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(0*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(0*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }else{
                if (distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.15)
                    sprite->setTextureRect(sf::IntRect(5*16, 4*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.3)
                    sprite->setTextureRect(sf::IntRect(5*16, 2*17, 16, 17));
                else if(distancia<RANGO_PARPADEO && animacionAndarClock.getElapsedTime().asSeconds()<0.45)
                    sprite->setTextureRect(sf::IntRect(5*16, 5*17, 16, 17));
                else if(animacionAndarClock.getElapsedTime().asSeconds()<0.6)
                    sprite->setTextureRect(sf::IntRect(5*16, 3*17, 16, 17));
                else
                    animacionAndarClock.restart();
            }
            break;
        default:
            break;
    }
}

