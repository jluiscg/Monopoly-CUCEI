#include <casilla.h>

Casilla::Casilla(int cod,string nom,int pre, int alq){
    prop= new Propiedad(cod,nom,pre,alq,0);
    sig=nullptr;
}
Casilla::~Casilla(){
    delete prop;
    delete sig;
}
Propiedad* Casilla::getPropiedad(){
    return prop;
}
Casilla* Casilla::getSig(){
    return sig;
}
void Casilla::setSig(Casilla* s){
    this->sig=s;
}
