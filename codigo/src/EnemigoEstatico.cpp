#include "EnemigoEstatico.h"

EnemigoEstatico::EnemigoEstatico(float posX, float posY)
{
    vida = 40;
    item=0;
    vectorX = 0.0;
    vectorY = 0.0;
    vMagnitud = 0.0;
    divisorUnitario = 0.0;
    distancia=0.f;
    dentroDelRadio=false;
    enemigoVivo=true;
    rangeClock.restart();
    animacionClock.restart();
    tocadoClock.restart();

    direccion_enemigo2 = 3;
    bala_eliminada = false; //paa saber si la bala se ha eliminado ya
    colision_personaje = false;
    angleRads = 0.0;
    angleDegs = 0.0;
    PI = 3.14159265359;

    sf::Texture *tex2 = new Texture();
    if (!tex2->loadFromFile("resources/voltorb.png"))
    {
        std::cerr << "Error cargando la imagen voltorb.png";
        exit(0);
    }
    /*CARGAMOS TEXTURA DE LA BALA*/
    if (!texBala.loadFromFile("resources/bala_fuego.png"))
    {
        std::cerr << "Error cargando la imagen bala_aerea_coche.png";
        exit(0);
    }
    sprite= new sf::Sprite(*tex2);
    sprite->setOrigin(25/2,25/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite->setTextureRect(sf::IntRect(4, 2, 25, 25));
    sprite->scale(1.5,1.5);
    // Lo dispongo en el centro de la pantalla
    sprite->setPosition(posX, posY);

    posXAnterior.clear();
    posYAnterior.clear();
    posXSiguiente.clear();
    posYSiguiente.clear();
    rotAnterior.clear();
    rotSiguiente.clear();
    unitarioX.clear();
    unitarioY.clear();

    bool tocado = false;
}

EnemigoEstatico::~EnemigoEstatico()
{
    /*for(int i = 0; i < todasBalas0.size(); i++)
    {
        //animacionExplosion(todasBalas0[i]->getPosition().x, todasBalas0[i]->getPosition().y);
        delete(todasBalas0[i]);
        todasBalas0[i]=nullptr;
    }
    todasBalas0.clear();

    delete bala0;
    bala0=nullptr;*/
}


void EnemigoEstatico::render(sf::RenderWindow *window, double percentTick)
{
    double posFinX=0;
    double posFinY=0;
    int rotacion=0;
    for(int i=0; i<todasBalas0.size(); i++)
    {
        posFinX = (posXSiguiente[i]-posXAnterior[i])*percentTick+posXAnterior[i];
        posFinY = (posYSiguiente[i]-posYAnterior[i])*percentTick+posYAnterior[i];
        rotacion = (rotSiguiente[i]-rotAnterior[i])*percentTick+rotAnterior[i];
        todasBalas0[i]->setPosition(posFinX,posFinY);
        todasBalas0[i]->setRotation(rotacion);

        window->draw(*todasBalas0[i]);
    }
    if(enemigoVivo == true)
        window->draw(*sprite);
}


void EnemigoEstatico::update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa, sf::Time timeElapsed)
{
    float distancia1;
    float distancia2;
    vector<RectangleShape *> *rectangulos = mapa->getRectangulosParedes();
    if(vida <= 0)
        enemigoVivo=false;

    if(enemigoVivo==true)
    {
        distancia1=pow((pow((jugador1->getSprite()->getPosition().x+32-sprite->getPosition().x),2)+pow(jugador1->getSprite()->getPosition().y+32-sprite->getPosition().y,2)),0.5);
        distancia2=pow((pow((jugador2->getSprite()->getPosition().x+32-sprite->getPosition().x),2)+pow(jugador2->getSprite()->getPosition().y-sprite->getPosition().y+32,2)),0.5);

        if(distancia1<=distancia2)
            distancia=distancia1;
        else
            distancia=distancia2;

        if(distancia<400)
        {
            if(dentroDelRadio==false)
            {
                dentroDelRadio=true;
               // rangeClock.restart();
                animacionClock.restart();
            }
            else
            {
                calcularDireccion(distancia1,distancia2, jugador1, jugador2);
                animacionDisparo();
            }
        }
        else
        {
            dentroDelRadio=false;
            animacionReposo();
        }

    }

    chocarBalas(timeElapsed, jugador1, jugador2, rectangulos);

    if(tocadoClock.getElapsedTime().asSeconds()>0.2)
        tocadoClock.restart();

    if(recibirDanyo==true && tiempoEnRojo.getElapsedTime().asMilliseconds()>300.0)
        recibirDanyo=false;
}



void EnemigoEstatico::bajarVidaJugador1(Jugador *jugador1)
{
    //std::cout << "Vida del jugador 1 reducida POR EL AEREO" << std::endl;
    jugador1->modificarVida(-DANYO_BALA_ENEMIGO_2);
}


void EnemigoEstatico::bajarVidaJugador2(Jugador *jugador2)
{
    //std::cout << "Vida del jugador 2 reducida POR EL AEREO" << std::endl;
    jugador2->modificarVida(-DANYO_BALA_ENEMIGO_2);
}


void EnemigoEstatico::calcularDireccion(float distancia1, float distancia2, Jugador *jugador1, Jugador *jugador2){
    if(distancia1<=distancia2)
    {
        vectorX=jugador1->getBody()->getPosition().x+32-sprite->getPosition().x;
        vectorY=jugador1->getBody()->getPosition().y+32-sprite->getPosition().y;
    }
    else
    {
        vectorX=jugador2->getBody()->getPosition().x+32-sprite->getPosition().x;
        vectorY=jugador2->getBody()->getPosition().y+32-sprite->getPosition().y;
    }

    vMagnitud= (vectorX*vectorX)+(vectorY*vectorY);
    divisorUnitario=sqrt(vMagnitud);
    angleRads = atan2(-vectorY, vectorX);
    angleDegs = angleRads * 180 / PI;

    if(angleDegs >=0 && angleDegs <= 180){ //entre 0 y 180 grados
        if(angleDegs >=0 && angleDegs <= 90){ // entre 0 y 90 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(4, 216, 25, 25));
            else
                sprite->setTextureRect(sf::IntRect(4, 216+243, 25, 25));
            direccion_enemigo2 = 1;
        }else{ //entre 90 y 180 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(4, 145, 25, 25));
            else
                sprite->setTextureRect(sf::IntRect(4, 145+243, 25, 25));
            direccion_enemigo2 = 2;
        }
    }else{
         if(angleDegs > -180 && angleDegs < -90){ // entre 0 y 90 grados
             if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(4, 2, 25, 25));
            else
                sprite->setTextureRect(sf::IntRect(4, 2+243, 25, 25));
            direccion_enemigo2 = 3;
        }else{ //entre 90 y 180 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(3, 73, 25, 25));
            else
                sprite->setTextureRect(sf::IntRect(3, 73+243, 25, 25));
            direccion_enemigo2 = 4;
        }
    }
}


void EnemigoEstatico::chocarBalas(sf::Time timeElapsed, Jugador *jugador1, Jugador *jugador2, vector<RectangleShape *> *rectangulos ){
    for(int i=0; i<todasBalas0.size() && tocado==false; i++)
    {
        //poner el movimiento
        posXAnterior[i]=posXSiguiente[i];
        posYAnterior[i]=posYSiguiente[i];
        rotAnterior[i]=rotSiguiente[i];

        posXSiguiente[i]=posXAnterior[i] + unitarioX[i] * timeElapsed.asMilliseconds()*0.06;
        posYSiguiente[i]=posYAnterior[i] + unitarioY[i] * timeElapsed.asMilliseconds()*0.06;
        rotSiguiente[i]=rotAnterior[i] + 20 * timeElapsed.asMilliseconds()*0.04;
        /*todasBalas0[i]->setPosition(todasBalas0[i]->getPosition().x + unitarioX[i] * VELOCIDAD_BALA_ENEMIGO_2,todasBalas0[i]->getPosition().y + unitarioY[i] * VELOCIDAD_BALA_ENEMIGO_2);*/
        //todasBalas0[i]->setRotation(todasBalas0[0]->getRotation()+20);
        for(int j = 0; j < rectangulos->size() && tocado==false; j++)
        {

            if(todasBalas0[i]->getGlobalBounds().intersects(jugador1->getBody()->getGlobalBounds()) || todasBalas0[i]->getGlobalBounds().intersects(jugador2->getBody()->getGlobalBounds()))
            {
                if(todasBalas0[i]->getGlobalBounds().intersects(jugador1->getBody()->getGlobalBounds()))
                    bajarVidaJugador1(jugador1);
                else
                    bajarVidaJugador2(jugador2);

                delete(todasBalas0[i]);
                todasBalas0.erase(todasBalas0.begin()+i);
                posXAnterior.erase(posXAnterior.begin()+i);
                posYAnterior.erase(posYAnterior.begin()+i);
                posXSiguiente.erase(posXSiguiente.begin()+i);
                posYSiguiente.erase(posYSiguiente.begin()+i);
                rotAnterior.erase(rotAnterior.begin()+i);
                rotSiguiente.erase(rotSiguiente.begin()+i);

                unitarioX.erase(unitarioX.begin()+i);
                unitarioY.erase(unitarioY.begin()+i);
                //   std::cerr << todasBalas0.size();
                bala_eliminada = true;
                // llamar a dañar el enemigo
                std::cout << "jugador dañado" << std::endl;
                tocadoClock.restart();

                tocado = true;
            }
            else if(todasBalas0[i]->getGlobalBounds().intersects((*rectangulos)[j]->getGlobalBounds()))
            {
                //animacionExplosion(todasBalas0[i]->getPosition().x, todasBalas0[i]->getPosition().y);
                delete(todasBalas0[i]);
                todasBalas0.erase(todasBalas0.begin()+i);

                posXAnterior.erase(posXAnterior.begin()+i);
                posYAnterior.erase(posYAnterior.begin()+i);
                posXSiguiente.erase(posXSiguiente.begin()+i);
                posYSiguiente.erase(posYSiguiente.begin()+i);
                rotAnterior.erase(rotAnterior.begin()+i);
                rotSiguiente.erase(rotSiguiente.begin()+i);

                unitarioX.erase(unitarioX.begin()+i);
                unitarioY.erase(unitarioY.begin()+i);
                bala_eliminada = true;
                std::cout << "bala choca contra muro" << std::endl;
                tocadoClock.restart();

                tocado = true;
            }
        }

        bala_eliminada = false;
    }
        tocado = false;
}


void EnemigoEstatico::anyadirBala(){
    if(enemigoVivo == true)
    {
        bala0 = new sf::Sprite;
        bala0->setTexture(texBala);
        bala0->setScale(1.5,1.5);
        bala0->setTextureRect(sf::IntRect(0, 0, 11, 11));
       // bala0->setOrigin(11/2,11/2);
        bala0->setPosition(sprite->getPosition().x,sprite->getPosition().y);
        todasBalas0.push_back(bala0);

        posXAnterior.push_back(sprite->getPosition().x);
        posYAnterior.push_back(sprite->getPosition().y);
        posXSiguiente.push_back(sprite->getPosition().x);
        posYSiguiente.push_back(sprite->getPosition().y);

        rotAnterior.push_back(0);
        rotSiguiente.push_back(20);

       // isFiring = false;
        animacionClock.restart();


        unitarioX.push_back(vectorX/divisorUnitario);
        unitarioY.push_back(vectorY/divisorUnitario);

        //sprite.setRotation(angleDegs);

        std::cerr << angleDegs << std::endl;
    }
}


void EnemigoEstatico::animacionReposo(){
    if(recibirDanyo==false){
        if(animacionReposoReloj.getElapsedTime().asSeconds()<2.0)
            sprite->setTextureRect(sf::IntRect(4, 2, 25, 25));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<2.5)
            sprite->setTextureRect(sf::IntRect(45, 2, 25, 25));
        else
            animacionReposoReloj.restart();
    }else{
        if(animacionReposoReloj.getElapsedTime().asSeconds()<2.0)
            sprite->setTextureRect(sf::IntRect(4, 2+243, 25, 25));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<2.5)
            sprite->setTextureRect(sf::IntRect(45, 2+243, 25, 25));
        else
            animacionReposoReloj.restart();
    }
}


void EnemigoEstatico::animacionDisparo(){
    if(animacionClock.getElapsedTime().asSeconds()>4.0 && animacionClock.getElapsedTime().asSeconds()<4.5)
    {
        //sprite direccion del enemigo
        if(recibirDanyo==false){
            if(direccion_enemigo2 == 1){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(44, 216, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(44, 216, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(126, 215, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(248, 214, 27, 27));
            }
            if(direccion_enemigo2 == 2){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(45, 145, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(45, 145, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(127, 144, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(249, 143, 27, 27));
            }
            if(direccion_enemigo2 == 3){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(45, 2, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(86, 2, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(127, 2, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(208, 1, 27, 27));
            }
            if(direccion_enemigo2 == 4){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(44, 73, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(85, 73, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(126, 73, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(207, 72, 27, 27));
            }
        }else{
            if(direccion_enemigo2 == 1){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(44, 216+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(44, 216+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(126, 215+243, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(248, 214+243, 27, 27));
            }
            if(direccion_enemigo2 == 2){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(45, 145+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(45, 145+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(127, 144+243, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(249, 143+243, 27, 27));
            }
            if(direccion_enemigo2 == 3){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(45, 2+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(86, 2+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(127, 2+243, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(208, 1+243, 27, 27));
            }
            if(direccion_enemigo2 == 4){
                if(animacionClock.getElapsedTime().asSeconds()<4.15)
                    sprite->setTextureRect(sf::IntRect(44, 73+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.30)
                    sprite->setTextureRect(sf::IntRect(85, 73+243, 25, 25));
                else if(animacionClock.getElapsedTime().asSeconds()<4.5)
                    sprite->setTextureRect(sf::IntRect(126, 73+243, 25, 25));
                else
                    sprite->setTextureRect(sf::IntRect(207, 72+243, 27, 27));
            }
        }
    }

    if(animacionClock.getElapsedTime().asSeconds()>4.5)
    {
        anyadirBala();
    }
}



