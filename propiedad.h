#ifndef PROPIEDAD_H
#define PROPIEDAD_H
#include <QString>

class Propiedad
{
private:
    int codigo;
    QString nombre;
    int precio;
    int alquiler;
    int duenio;
public:
    Propiedad(int, QString,int,int,int);
    ~Propiedad();
    void setCodigo(int);
    int getCodigo();
    void setNombre(QString);
    QString getNombre();
    void setPrecio(int);
    int getPrecio();
    void setAlquiler(int);
    int getAlquiler();
    void setDuenio(int);
    int getDuenio();
};

#endif // PROPIEDAD_H
