#include "tablero.h"

Tablero::Tablero(QString rutImg)
{
    this->rutaImagen=rutImg;
    this->inicio=nullptr;
    ///creacion del tablero JARCODIADO :v
    Casilla* aux;
    inicio=new Casilla(0);//salida
    aux=inicio;
    aux->setSig(new Casilla(1,1,"El Brother",60,2));//1 y 2 conjunto azul feo
    aux=aux->getSig();
    aux->setSig(new Casilla(2));//sorpresa 1
    aux=aux->getSig();
    aux->setSig(new Casilla(3,2,"Donia Tifo",60,4));//1 y 2 conjunto azul feo
    aux=aux->getSig();
    aux->setSig(new Casilla(4,200,"Orden de pago"));
    aux=aux->getSig();
    aux->setSig(new Casilla(5,23,"Ruta 622",200,25));//23 a 26 codigos de las rutas
    aux=aux->getSig();
    aux->setSig(new Casilla(6,3,"Modulo U",100,6));//3,4 y 5 conjunto azul claro
    aux=aux->getSig();
    aux->setSig(new Casilla(7));//sorpresa 2
    aux=aux->getSig();
    aux->setSig(new Casilla(8,4,"Modulo T",100,6));//3,4 y 5 conjunto azul claro
    aux=aux->getSig();
    aux->setSig(new Casilla(9,5,"Modulo X",120,8));//3,4 y 5 conjunto azul claro
    aux=aux->getSig();
    aux->setSig(new Casilla(10));//carcel :'V articulo 35 :'c
    aux=aux->getSig();
    aux->setSig(new Casilla(11,6,"Modulo W",140,10));//6,7 y 8 conjunto morado
    aux=aux->getSig();
    aux->setSig(new Casilla(12,27,"Coliseo",150,4));//coliseo, reemplaza a electricidad
    aux=aux->getSig();
    aux->setSig(new Casilla(13,7,"Modulo V1",140,10));//6,7 y 8 conjunto morado
    aux=aux->getSig();
    aux->setSig(new Casilla(14,8,"Modulo V2",160,12));//6,7 y 8 conjunto morado
    aux=aux->getSig();
    aux->setSig(new Casilla(15,24,"Ruta 615",200,25));//23 a 26 codigos de las rutas
    aux=aux->getSig();
    aux->setSig(new Casilla(16,9,"Modulo P",180,14));//9,10 y 11 conjunto naranja
    aux=aux->getSig();
    aux->setSig(new Casilla(17));//sorpresa 1
    aux=aux->getSig();
    aux->setSig(new Casilla(18,10,"Modulo Q",180,14));//9,10 y 11 conjunto naranja
    aux=aux->getSig();
    aux->setSig(new Casilla(19,11,"Lab. Ing. Civil",200,16));//9,10 y 11 conjunto naranja
    aux=aux->getSig();
    aux->setSig(new Casilla(20));//parada libre
    aux=aux->getSig();
    aux->setSig(new Casilla(21,12,"Antonio Rodriguez",220,18));//12,13 y 14 conjunto rojo
    aux=aux->getSig();
    aux->setSig(new Casilla(22));//sorpresa 2
    aux=aux->getSig();
    aux->setSig(new Casilla(23,13,"Matute Remus",220,18));//12,13 y 14 conjunto rojo
    aux=aux->getSig();
    aux->setSig(new Casilla(24,14,"Enrique Diaz de Leon",240,20));//12,13 y 14 conjunto rojo
    aux=aux->getSig();
    aux->setSig(new Casilla(25,25,"Ruta 644-B",200,25));//23 a 26 codigos de las rutas
    aux=aux->getSig();
    aux->setSig(new Casilla(26,15,"Modulo Alfa",260,22));//15,16 y 17 conjunto amarillo
    aux=aux->getSig();
    aux->setSig(new Casilla(27,16,"Modulo Beta",260,22));//15,16 y 17 conjunto amarillo
    aux=aux->getSig();
    aux->setSig(new Casilla(28,28,"Gimnasio de usos Multiples",150,4));//gimnasio reemplaza a agua
    aux=aux->getSig();
    aux->setSig(new Casilla(29,17,"El Globo",280,22));//15,16 y 17 conjunto amarillo
    aux=aux->getSig();
    aux->setSig(new Casilla(30));//go to jail/ articulo 35 :'C
    aux=aux->getSig();
    aux->setSig(new Casilla(31,18,"Modulo O",300,26));//18,19 y 20 conjunto verde
    aux=aux->getSig();
    aux->setSig(new Casilla(32,19,"Modulo N",300,26));//18,19 y 20 conjunto verde
    aux=aux->getSig();
    aux->setSig(new Casilla(33));//sorpresa 1
    aux=aux->getSig();
    aux->setSig(new Casilla(34,20,"Modulo M",320,28));//18,19 y 20 conjunto verde
    aux=aux->getSig();
    aux->setSig(new Casilla(35,26,"Ruta 647",200,25));//23 a 26 codigos de las rutas
    aux=aux->getSig();
    aux->setSig(new Casilla(36));//sorpresa 2
    aux=aux->getSig();
    aux->setSig(new Casilla(37,21,"El Chedraui",350,35));//21 y 22 conjunto azul oscuro
    aux=aux->getSig();
    aux->setSig(new Casilla(38,75,"Extraordinarios"));
    aux=aux->getSig();
    aux->setSig(new Casilla(39,22,"Rectoria",400,50));//21 y 22 conjunto azul oscuro
    aux=aux->getSig();
    aux->setSig(inicio);
}
Tablero::~Tablero()
{
    delete inicio;
}
void Tablero::setInicio(Casilla *ini)
{
    this->inicio=ini;
}
QString Tablero::getRutaImagen()
{
    return rutaImagen;
}
Casilla* Tablero::getInicio()
{
    return inicio;
}

Propiedad* Tablero::getPropiedadById(int idPropiedad)
{
    Casilla*aux=this->inicio->getSig();
    while(aux->getId()!=0)
    {
        if(aux->getTipo()==PROPIEDAD)
            if(aux->getPropiedad()->getCodigo()==idPropiedad)
                break;
        aux=aux->getSig();
    }
    return aux->getPropiedad();
}
