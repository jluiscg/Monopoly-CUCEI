#ifndef CASILLA_H
#define CASILLA_H

#include <propiedad.h>

class Casilla{
private:
    Propiedad* prop;
    Casilla* sig;
public:
    Casilla(int cod, string nom, int pre, int alq);
    ~Casilla();
    Propiedad* getPropiedad();
    Casilla* getSig();
    void setSig(Casilla* s);
};

#endif // CASILLA_H
