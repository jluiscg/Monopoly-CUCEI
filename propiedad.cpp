#include <propiedad.h>

Propiedad::Propiedad(int codigo,string nombre,int precio, int alquiler, int duenio){
    this->codigo=codigo;
    this->nombre=nombre;
    this->precio=precio;
    this->alquiler=alquiler;
    this->duenio=duenio;
}
Propiedad::~Propiedad(){
 //:v
}
void Propiedad::setCodigo(int codigo){
    this->codigo=codigo;
}
int Propiedad::getCodigo(){
    return codigo;
}
void Propiedad::setNombre(string nombre){
    this->nombre=nombre;
}
string Propiedad::getNombre(){
    return nombre;
}
void Propiedad::setPrecio(int precio){
    this->precio=precio;
}
int Propiedad::getPrecio(){
    return precio;
}
void Propiedad::setAlquiler(int alquiler){
    this->alquiler=alquiler;
}
int Propiedad::getAlquiler(){
    return alquiler;
}
void Propiedad::setDuenio(int duenio){
    this->duenio=duenio;
}
int Propiedad::getDuenio(){
    return duenio;
}
