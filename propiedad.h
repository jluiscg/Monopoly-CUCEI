#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <string>
using namespace std;

class Propiedad{
private:
    int codigo;
    string nombre;
    int precio;
    int alquiler;
    int duenio;
public:
    Propiedad(int, string,int,int,int);
    ~Propiedad();
    void setCodigo(int);
    int getCodigo();
    void setNombre(string);
    string getNombre();
    void setPrecio(int);
    int getPrecio();
    void setAlquiler(int);
    int getAlquiler();
    void setDuenio(int);
    int getDuenio();
};

#endif // PROPIEDAD_H
