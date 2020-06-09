#include "NivelFactory.h"
#include "Utils.h"
#include "EnemigoFactory.h"
#include "Pocion.h"
#include "Roca.h"
#include "Arma.h"
#include "Bomba.h"
#include "Llave.h"
#include "Caja.h"
#include "Puerta.h"
#include "fstream"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
using namespace sf;

const string NivelFactory::nombreTileSet = "./mapas/TodoSprites.png";

void NivelFactory::crearNivel(string nombreArchivo, Nivel *nivel) {

    ifstream i(nombreArchivo);
    json j = json::parse(i);

    int heightMapa = j["height"];
    int widthMapa  = j["width"];
    int tileWidth  = j["tilewidth"];
    int tileHeight = j["tileheight"];
    cout << "la altura del mapa es " << heightMapa << endl;
    cout << "la anchura del mapa es " << heightMapa << endl;
    cout << "la anchura del tile es " << tileWidth << endl;
    cout << "la altura del tile es " << tileHeight << endl;

    nivel->getMapa()->setMapTileWidth(widthMapa);
    nivel->getMapa()->setMapTileHeight(heightMapa);
    nivel->getMapa()->setTileSizeX(tileWidth);
    nivel->getMapa()->setTileSizeY(tileHeight);

    sf::Vector2u tileSize(tileWidth, tileHeight);

    int numCapas = j["layers"].size();
    cout << "hay " << numCapas << " capas" << endl;

    for(int numCapaActual = 0; numCapaActual < numCapas; numCapaActual++){
        auto capaActual = j["layers"][numCapaActual];
        string nombreCapa = capaActual["name"].get<std::string>();

        // ENEMIGOS
        if (capaActual["objects"] != nullptr && nombreCapa.compare("enemigos") == 0)
        {
            int numobjetos = capaActual["objects"].size();
            for(int objetoActual = 0; objetoActual < numobjetos; objetoActual++){
                auto objetoSimple = capaActual["objects"][objetoActual];

                int x = objetoSimple["x"];
                int y = objetoSimple["y"];
                int tipoEnemigo = 1;
                if(objetoSimple["properties"]["TipoEnemigo"] != nullptr && objetoSimple["properties"]["TipoEnemigo"] != NULL)
                    tipoEnemigo = objetoSimple["properties"]["TipoEnemigo"];
                Enemigo *enemigo = EnemigoFactory::crearEnemigo(x, y, tipoEnemigo);
                nivel->getEnemigos()->push_back(enemigo);
            }
        }

        else if(capaActual["objects"] != nullptr && nombreCapa.compare("spawn") == 0){
            int numobjetos = capaActual["objects"].size();
            for(int objetoActual = 0; objetoActual < numobjetos; objetoActual++){
                auto objetoSimple = capaActual["objects"][objetoActual];

                int x = objetoSimple["x"];
                int y = objetoSimple["y"];

                Vector2f *pos = new Vector2f(x,y);

                nivel->getSpawns()->push_back(pos);
            }
        }

        // OBJETOS
        else if (capaActual["objects"] != nullptr &&
            (nombreCapa.compare("pociones") == 0
            || nombreCapa.compare("rocas") == 0
            || nombreCapa.compare("armas") == 0
            || nombreCapa.compare("bombas") == 0
            || nombreCapa.compare("llaves") == 0
            || nombreCapa.compare("puertas") == 0
            || nombreCapa.compare("cajas") == 0
            || nombreCapa.compare("meta") == 0))
        {
            int numobjetos = capaActual["objects"].size();
            for(int objetoActual = 0; objetoActual < numobjetos; objetoActual++){
                auto objetoSimple = capaActual["objects"][objetoActual];

                int x = objetoSimple["x"];
                int y = objetoSimple["y"];

                int tipo = 1;
                if(objetoSimple["properties"]["Tipo"] != nullptr && objetoSimple["properties"]["Tipo"] != NULL)
                    tipo = objetoSimple["properties"]["Tipo"];

                ObjetoMapa *objeto;
                if(Utils::StrEquals(nombreCapa, "pociones")) {
                    objeto = new Pocion(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "rocas")) {
                    objeto = new Roca(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "bombas")) {
                    objeto = new Bomba(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "llaves")) {
                    objeto = new Llave(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "armas")) {
                    objeto = new Arma(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "puertas")) {
                    objeto = new Puerta(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "cajas")){
                    objeto = new Caja(x, y, tipo);
                } else if(Utils::StrEquals(nombreCapa, "meta")){
                    objeto = new ObjetoMetaNivel(x, y, tipo);
                }

                nivel->getObjetos()->push_back(objeto);
            }
        }


        // COLISIONES
        else if (capaActual["objects"] != nullptr &&
            (nombreCapa.compare("electricidad") == 0
            || nombreCapa.compare("agua") == 0
            || nombreCapa.compare("colisiones") == 0
            || nombreCapa.compare("escaleras") == 0))
        {
            int numobjetos = capaActual["objects"].size();

            for(int objetoActual = 0; objetoActual < numobjetos; objetoActual++){
                //Objeto actual;
                auto objetoSimple = capaActual["objects"][objetoActual];
                RectangleShape *r = new RectangleShape();
                r->setSize(Vector2f(objetoSimple["width"], objetoSimple["height"]));
                r->setPosition(objetoSimple["x"], objetoSimple["y"]);

                if(Utils::StrEquals(nombreCapa, "electricidad")) {
                    r->setFillColor(Color(0, 128, 128, 50));
                    nivel->getMapa()->getRectangulosElectricidad()->push_back(r);
                } else if(Utils::StrEquals(nombreCapa, "agua")) {
                    r->setFillColor(Color(0, 0, 128, 50));
                    nivel->getMapa()->getRectangulosAgua()->push_back(r);
                } else if(Utils::StrEquals(nombreCapa, "colisiones")) {
                    r->setFillColor(Color(255, 0, 0, 50));
                    nivel->getMapa()->getRectangulosParedes()->push_back(r);
                } else if(Utils::StrEquals(nombreCapa, "escaleras")) {
                    r->setFillColor(Color(255, 128, 0, 50));
                    nivel->getMapa()->getRectangulosEscaleras()->push_back(r);
                }


            }
        }



        // MAPA DE CALOR
        else if(capaActual["data"] != nullptr && nombreCapa.compare("mapa_calor") == 0)
        {
            vector<int> datas = capaActual["data"];
            int *data = datas.data();

           /* int **mapaCalor = new int*[widthMapa];
            for(int i = 0; i < widthMapa; i++)
                mapaCalor[i] = new int[heightMapa];

            int totalTiles = widthMapa * heightMapa;
            int tileActual = 0;
            for(int y = 0; y < heightMapa; y++) {
                for(int x = 0; x < widthMapa; x++) {
                    mapaCalor[x][y] = data[tileActual];
                    tileActual++;
                }
            }*/

            int **mapaCalor = new int*[heightMapa];
            for(int i = 0; i < heightMapa; i++)
                mapaCalor[i] = new int[widthMapa];

            int totalTiles = heightMapa * widthMapa;
            int tileActual = 0;
            for(int y = 0; y < heightMapa; y++) {
                for(int x = 0; x < widthMapa; x++) {
                    mapaCalor[y][x] = data[tileActual];
                    tileActual++;
                }
            }

            nivel->getMapa()->setMapaCalorParedes(mapaCalor);

/*
            cout << "Empieza el test de mapa de calor" << endl;
            cout << "En la pos 6,3 hay calor" << (mapaCalor[6, 3] != 0) << endl;
            cout << "En la pos 7,3 hay calor" << (mapaCalor[7, 3] != 0) << endl;
            cout << "En la pos 13,9 hay calor" << (mapaCalor[13, 9] != 0) << endl;
            cout << "En la pos 14,9 hay calor" << (mapaCalor[14, 9] != 0) << endl;
            cout << "En la pos 15,9 hay calor" << (mapaCalor[15, 9] != 0) << endl;

            cout << "Termina el test de mapa de calor" << endl;

            for(int y = 0; y < heightMapa; y++) {
                for(int x = 0; x < widthMapa; x++) {
                    if (mapaCalor[x][y] == 0)
                        cout << "_";
                    else
                        cout << "X";
                }
                cout << "" << endl;
            }
*/
        }



        // TILES
        else if(capaActual["data"] != nullptr)
        {
            vector<int> datas = capaActual["data"];
            int *data = datas.data();
            bool tapaJugador = capaActual["properties"]["TapaJugador"];

            cout << "Esta capa tapa al jugador " << tapaJugador << endl;

            TileMap *tileMap = new TileMap(NivelFactory::nombreTileSet, tileSize, data, widthMapa, heightMapa);
            if(tapaJugador)
                nivel->getMapa()->getTileMapsDelante()->push_back(tileMap);
            else
                nivel->getMapa()->getTileMapsDetras()->push_back(tileMap);
        }
    }
}
