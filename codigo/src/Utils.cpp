#include "Utils.h"
#include "Constantes.h"
#include "Globales.h"
#include "fstream"
#include "iostream"

using namespace std;

Utils::Utils()
{
    //ctor
}

Utils::~Utils()
{
    //dtor
}

std::string Utils::Int_to_String(int integer){
    std::string result;

    result = static_cast<std::ostringstream*>( &(std::ostringstream() << integer) )->str();
    return result;
}

int Utils::random(int minimo, int maximo) {
    return rand() % (maximo - minimo + 1) + minimo;
}

/*
int Utils::getHash(string texto, int h) {
    return !texto[h] ? 5381 : (getHash(texto, h+1) * 33) ^ texto[h];
}
*/


void Utils::cargarPartida()
{
    ifstream file(Constantes::ARCHIVO_SAVE);
    if (file.is_open())
    {
        string line;

        // nivel 0
        if(getline(file, line))
        {
            if(line == "1")
            {
                Globales::NIVEL_AMERICA_SUPERADO = true;
                cout << "El nivel 0 está superado" << endl;
            }
        }

        // nivel 1
        if(getline(file, line))
        {
            if(line == "1")
            {
                Globales::NIVEL_AFRICA_SUPERADO = true;
                cout << "El nivel 1 está superado" << endl;
            }
        }


        // nivel final
        if(getline(file, line))
        {
            if(line == "1")
            {
                Globales::NIVEL_EUROPA_SUPERADO = true;
                cout << "El nivel final está superado" << endl;
            }
        }


        // nivel asia
        if(getline(file, line))
        {
            if(line == "1")
            {
                Globales::NIVEL_ASIA_SUPERADO = true;
                cout << "El nivel final está superado" << endl;
            }
        }


        // nivel antartida
        if(getline(file, line))
        {
            if(line == "1")
            {
                Globales::NIVEL_ANTARTIDA_SUPERADO = true;
                cout << "El nivel final está superado" << endl;
            }
        }

        file.close();
    }
}

void Utils::guardarPartida()
{
    ofstream myfile;
    myfile.open(Constantes::ARCHIVO_SAVE);

    if(Globales::NIVEL_AMERICA_SUPERADO)
        myfile << "1";
    else
        myfile << "0";
    myfile << endl;

    if(Globales::NIVEL_AFRICA_SUPERADO)
        myfile << "1";
    else
        myfile << "0";
    myfile << endl;

    if(Globales::NIVEL_EUROPA_SUPERADO)
        myfile << "1";
    else
        myfile << "0";
    myfile << endl;

    if(Globales::NIVEL_ASIA_SUPERADO)
        myfile << "1";
    else
        myfile << "0";
    myfile << endl;

    if(Globales::NIVEL_ANTARTIDA_SUPERADO)
        myfile << "1";
    else
        myfile << "0";
    myfile << endl;

    myfile.close();
}


void Utils::borrarPartida()
{
    ofstream myfile;
    myfile.open(Constantes::ARCHIVO_SAVE);
    myfile << "";
    myfile.close();
    Globales::NIVEL_AFRICA_SUPERADO = false;
    Globales::NIVEL_EUROPA_SUPERADO = false;
    Globales::NIVEL_AMERICA_SUPERADO = false;
    Globales::NIVEL_ASIA_SUPERADO = false;
    Globales::NIVEL_ANTARTIDA_SUPERADO = false;
}
