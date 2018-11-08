#include "jugador.h"

Jugador::Jugador(int cod, QString nom, int din, QString ruta)
{
    this->codigo=cod;
    this->nombre=nom;
    this->dinero=din;
    posicion=nullptr;
    this->rutaImagen=ruta;
    this->x=430;
    this->y=430;
    this->carcel=0;
    this->tirosDobles=0;
}
Jugador::~Jugador()
{
    delete posicion;
}
void Jugador::setCodigo(int cod)
{
    this->codigo=cod;
}
int Jugador::getCodigo()
{
    return codigo;
}
void Jugador::setNombre(QString nom)
{
    this->nombre=nom;
}
QString Jugador::getNombre()
{
    return nombre;
}
void Jugador::setDinero(int din)
{
    this->dinero=din;
}
int Jugador::getDinero()
{
    return dinero;
}
void Jugador::setPosicion(Casilla *pos)
{
    this->posicion=pos;
}
Casilla* Jugador::getPosicion()
{
    return posicion;
}
void Jugador::setX(int posX)
{
    this->x=posX;
}
int Jugador::getX()
{
    return x;
}
void Jugador::setY(int posY)
{
    this->y=posY;
}
int Jugador::getY()
{
    return y;
}

void Jugador::setRutaImagen(QString ruta)
{
    this->rutaImagen=ruta;
}

QString Jugador::getRutaImagen()
{
    return rutaImagen;
}

void Jugador::setCarcel(int jail)
{
    this->carcel=jail;
}

int Jugador::getCarcel()
{
    return carcel;
}

void Jugador::setTirosDobles(int dobles)
{
    this->tirosDobles=dobles;
}

int Jugador::getTirosDobles()
{
    return tirosDobles;
}

