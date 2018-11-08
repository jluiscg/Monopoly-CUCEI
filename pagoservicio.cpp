#include <pagoservicio.h>

PagoServicio::PagoServicio(QString nombre, int pago){
    this->nombre=nombre;
    this->pago=pago;
}
PagoServicio::~PagoServicio(){

}
void PagoServicio::setNombre(QString nombre){
    this->nombre=nombre;
}
void PagoServicio::setPago(int pago){
    this->pago=pago;
}
QString PagoServicio::getNombre(){
    return nombre;
}
int PagoServicio::getPago(){
    return pago;
}
