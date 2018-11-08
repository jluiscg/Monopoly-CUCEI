#include <casilla.h>

Casilla::Casilla(int identi, int cod, QString nom, int pre, int alq){
    this->id=identi;
    this->tipo=PROPIEDAD;
    prop = new Propiedad(cod,nom,pre,alq,0);
    sig=nullptr;
    pago=nullptr;
}
Casilla::Casilla(int identi, int pago,QString nombre){
    this->id=identi;
    this->tipo=DE_PAGO;
    this->pago=new PagoServicio(nombre,pago);
    sig=nullptr;
    prop=nullptr;
}
Casilla::Casilla(int identi){
    this->id=identi;
    this->tipo=PARADA_LIBRE;
    sig=nullptr;
    prop=nullptr;
    pago=nullptr;
}
Casilla::~Casilla(){
    delete prop;
    delete pago;
    delete sig;
}
int Casilla::getId()
{
    return id;
}

void Casilla::setId(int identi)
{
    this->id=identi;
}

int Casilla::getTipo()
{
    return tipo;
}

void Casilla::setTipo(int tip)
{
    this->tipo=tip;
}

Propiedad* Casilla::getPropiedad(){
    return prop;
}
void Casilla::setPropiedad(Propiedad *p){
    this->prop=p;
}
Casilla* Casilla::getSig(){
    return sig;
}
void Casilla::setSig(Casilla* s){
    this->sig=s;
}
PagoServicio* Casilla::getPago(){
    return pago;
}
void Casilla::setPago(PagoServicio* p){
    this->pago=p;
}
