#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
//./ej1 | od -a (ASCII) -x (hexadecimal)

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):x(_x),y(_y)
    {
        strncpy(name, _n, 80);
    };

    virtual ~Jugador(){};

    void to_bin()
    {
        //80 del nombre + 2 ints
        int32_t total = 80 * sizeof(char) + 2 * sizeof(int16_t);
        //Hace el malloc
        alloc_data(total);
        
        //Nos interesa saber donde empiezan las variables dentro del buffer
        char * tmp = _data + sizeof(int32_t); //Tmp apunta al nombre
        
        //NOMBRE
        memcpy(tmp, (void *)name,80 * sizeof(char));
        tmp += 80 * sizeof(char);
        //X
        memcpy(tmp, &_x, sizeof(int16_t));
        tmp += sizeof(int16_t);
        
        //Y
        memcpy(tmp, &_y, sizeof(int16_t));
    }

    int from_bin(char * data)
    {
        char * tmp = data + sizeof(int32_t);
        //Nombre
        memcpy(name, tmp, 80);
        tmp += 80 * sizeof(char);
        //X
        memcpy(&_x,tmp, sizeof(int16_t));
        tmp += sizeof(int16_t);
        
        //Y
        memcpy( &_y,tmp,sizeof(int16_t));
        
    }

public:
    char name[80];

    int16_t x;
    int16_t y;
};

int main(int argc, char **argv)
{
    Jugador one("player one", 134, 23);
    Jugador one_("-", 0 ,0);
    
    one.to_bin();
    std::cout << "---------\n" << one.data() << << "---------\n";
    one_.from_bin(one.data());
    std::cout << "N:" << one_.name << "\n X: "<<one_._x<< " Y: "<< one_._y << "\n";

    
}
