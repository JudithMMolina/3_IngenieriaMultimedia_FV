#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>

using namespace std;

class Utils
{
    public:
        Utils();
        virtual ~Utils();

        static string Int_to_String(int integer);
        static int random(int, int);
        static bool StrEquals(string texto1, string texto2) {
            return texto1.compare(texto2) == 0;
        };

        /*constexpr static int getHash(string texto, int h = 0) {
            return !texto[h] ? 5381 : (getHash(texto, h+1) * 33) ^ texto[h];
        };*/

        /*static unsigned int getHash(const char* str, int h = 0)
        {
            return !str[h] ? 5381 : (getHash(str, h+1) * 33) ^ str[h];
        }*/


        static void guardarPartida();
        static void cargarPartida();
        static void borrarPartida();

    protected:

    private:

};

#endif // UTILS_H
