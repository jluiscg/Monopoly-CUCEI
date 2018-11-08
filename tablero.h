#ifndef TABLERO_H
#define TABLERO_H
#include <QString>
#include <casilla.h>

class Tablero
{
private:
    Casilla* inicio;
    QString rutaImagen;
public:
    Tablero(QString rutImg);
    ~Tablero();
    void setInicio(Casilla*ini);
    QString getRutaImagen();
    Casilla* getInicio();
    Propiedad* getPropiedadById(int idPropiedad);
};

#endif // TABLERO_H
