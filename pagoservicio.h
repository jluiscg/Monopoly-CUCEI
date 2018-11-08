#ifndef PAGOSERVICIO_H
#define PAGOSERVICIO_H

#endif // PAGOSERVICIO_H
#include <QString>
class PagoServicio{
private:
    QString nombre;
    int pago;
public:
    PagoServicio(QString nombre, int pago);
    ~PagoServicio();
    QString getNombre();
    int getPago();
    void setNombre(QString nombre);
    void setPago(int pago);
};
