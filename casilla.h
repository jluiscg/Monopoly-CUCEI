#ifndef CASILLA_H
#define CASILLA_H
#include <QString>
#include <propiedad.h>
#include <pagoservicio.h>

#define PROPIEDAD 1
#define PARADA_LIBRE 2
#define DE_PAGO 3

class Casilla
{
private:
    int id;
    int tipo;
    Propiedad* prop;
    PagoServicio* pago;
    Casilla* sig;
public:
    Casilla(int identi, int codPropiedad, QString nom, int pre, int alq);
    Casilla(int identi,int pago, QString nombre);
    Casilla(int identi);
    ~Casilla();
    int getId();
    void setId(int identi);
    int getTipo();
    void setTipo(int tip);
    Propiedad* getPropiedad();
    void setPropiedad(Propiedad* p);
    Casilla* getSig();
    void setSig(Casilla* s);
    PagoServicio* getPago();
    void setPago(PagoServicio* p);
};

#endif // CASILLA_H
