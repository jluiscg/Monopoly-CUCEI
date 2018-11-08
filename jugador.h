#ifndef JUGADOR_H
#define JUGADOR_H
#include <QString>
#include "casilla.h"

class Jugador
{
public:
    Jugador(int cod, QString nom, int din, QString ruta);
    ~Jugador();
    void setCodigo(int cod);
    int getCodigo();
    void setNombre(QString nom);
    QString getNombre();
    void setDinero(int din);
    int getDinero();
    void setPosicion(Casilla *pos);
    Casilla* getPosicion();
    void setX(int posX);
    int getX();
    void setY(int posY);
    int getY();
    void setRutaImagen(QString ruta);
    QString getRutaImagen();
    void setCarcel(int jail);
    int getCarcel();
    void setTirosDobles(int dobles);
    int getTirosDobles();
private:
    int codigo;
    QString nombre;
    int dinero;
    Casilla* posicion;
    int x;
    int y;
    QString rutaImagen;
    int carcel;
    int tirosDobles;
};

#endif // JUGADOR_H
