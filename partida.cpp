#include "partida.h"
#include "ui_partida.h"

partida::partida(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::partida)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    tablero=new Tablero("../monopolyCucei/images/tablero-f-c.png");
    ui->graphicsView->setScene(scene);
    ui->btnDados->setVisible(false);
    ui->btnComprar->setVisible(false);
    ui->btnNoComprar->setVisible(false);
    ui->btnVender->setVisible(false);
    ui->btnPagarArticulo->setVisible(false);
    turno=1;
    //solo para pruebas :v
    //jugadores[1]= new Jugador(1,"uno",1000,"../monopolyCucei/images/memputa.png");
    //jugadores[2]= new Jugador(2,"dos",1000,"../monopolyCucei/images/n-pac.png");
    //jugadores[3]= new Jugador(3,"tres",1000,"../monopolyCucei/images/franco2.png");
    //jugadores[4]= new Jugador(4,"cuatro",1000,"../monopolyCucei/images/hassem2.png");
    //for(int i=1;i<=NUMJUGADORES;i++)
        //jugadores[i]->setPosicion(tablero->getInicio());
    //solo para pruebas :v
    socket=new QTcpSocket(this);
    server=new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &partida::newConnection);
    connect(socket,&QTcpSocket::connected,this,&partida::connected);
    connect(socket,&QTcpSocket::readyRead,this,&partida::dataRecvd);
    connect(socket,&QTcpSocket::disconnected,this,&partida::desconexion);
}

partida::~partida()
{
    delete ui;
    delete tablero;
    for(int i=NUMJUGADORES;i>=0;i--)
    {
        delete jugadores[i];
    }

}

void partida::on_btnDados_clicked()
{
    //limpiar mensajes
    ui->lblMensajes->setText("");
    //generar random para dados
    srand(time(0));
    int dad1,dad2;
    dad1=1+rand()%(7-1);
    dad2=1+rand()%(7-1);
    //dad1=4;
    //dad2=6;
    //desactivar el boton para evitar volver a tirar
    ui->btnDados->setVisible(false);
    ui->btnPagarArticulo->setVisible(false);
    //enviar mensaje con los datos de la movida
    char bytes[2]={0};
    bytes[0]=DADOS;
    bytes[1]=dad1;
    bytes[1]=bytes[1]<<3;
    bytes[1]=bytes[1]+dad2;
    socket->write(bytes,2);
    //todo lo que sigue a continuación se hará cuando se reciba el paquete
    //asignar dados
    setDados(dad1,dad2);
    //mostrar etiquetas de dados
    mostrarEtiquetasDados();
    //sumar tiro doble o reiniciar
    if(dado1==dado2)
        jugadores[turno]->setTirosDobles(jugadores[turno]->getTirosDobles()+1);
    else
        jugadores[turno]->setTirosDobles(0);
    //comprobar articulo 35 y triple tiro doble
    if(jugadores[turno]->getCarcel() == NO_ART_35)
    {
        if(jugadores[turno]->getTirosDobles()==3)
        {
            ui->lblMensajes->setText("Triple tiro doble, "+jugadores[turno]->getNombre()+" cae en articulo 35 :'c");
            jugadores[turno]->setTirosDobles(0);
            moverJugadorAArt35(turno);
        }
        else//mover ficha
        {
            moverFicha(dado1+dado2,turno);
        }
    }
    else
    {
        if(dado1 == dado2)
        {
            ui->lblMensajes->setText("Tiro doble, articulo 35 perdonado c':");
            jugadores[turno]->setCarcel(NO_ART_35);
            //mover ficha
            moverFicha(dado1+dado2,turno);
        }
        else
        {
            jugadores[turno]->setCarcel(jugadores[turno]->getCarcel()+1);
            if(jugadores[turno]->getCarcel() > LIMIT_ART_35)
            {
                ui->lblMensajes->setText("Tiempo de artículo 35 terminado, se cobrarán $50.00");
                jugadores[turno]->setCarcel(NO_ART_35);
                jugadores[turno]->setDinero(jugadores[turno]->getDinero() - PRECIO_ART_35);
                actualizarEtiquetasDinero();
            }
            else
            {
                ui->lblMensajes->setText("No hay tiro doble, " +jugadores[turno]->getNombre()+ " continua en articulo");
            }
        }
    }
    paqueteEsperado=DADOS;
    //mostrar informacion de la casilla y realizar accion
    //actualiza turno en caso de ser posible
    accionCasillaActual(jugadores[turno]->getPosicion(),turno);
    //independientemente de cualquier cosa, se debe activar
    //pero como nos vale madre lo quitamos :v
    //ui->btnVender->setVisible(true);
}

void partida::on_btnConectar_clicked()
{
    QString ip=ui->tbxIp->text();
    if(ip.length()<=0)
    {
        ui->lblMensajes->setText("Host invalido, se utilizará 192.168.0.4");
        ip="192.168.0.4";
        s.delay();
        s.delay();
    }
    QString puertoString=ui->tbxPuerto->text();
    bool puertoValido=false;
    quint16 puerto=puertoString.toShort(&puertoValido,10);
    if(puertoValido)
    {
        //si se pudo convertir y es puerto valido
        ui->lblMensajes->setText("Puerto valido :v");
    }
    else
    {
        ui->lblMensajes->setText("Puerto invalido, se utilizara el 33120");
        puertoValido=true;
        puerto=33120;
    }
    //todo es para pruebas ahorita :v
    QString nom=ui->tbxNombre->text();
    if(nom.length()<=0 || nom.length()>15)
    {
        ui->lblMensajes->setText("Nombre invalido, se utilizará Juanjo");
        nom="Juanjo";
        ui->lblTitulo->setText("MONOPOLY CUCEI :V - "+nom);
        s.delay();
        s.delay();
    }
    jugadores[2]=new Jugador(2,nom,1000,"../monopolyCucei/images/n-pac.png");
    numeroJugador=2;
    ui->lblMensajes->setText("Conectando a "+ip+" en el puerto "+QString::number(puerto));
    socket->connectToHost(ip,puerto, QIODevice::ReadWrite);
}

void partida::mostrarTablero(int x,int y)
{
    QPixmap pixmap(tablero->getRutaImagen());
    tableroImagen.setPixmap(pixmap);
    tableroImagen.setPixmap(pixmap);
    tableroImagen.setX(x);
    tableroImagen.setY(y);
    scene->addItem(&tableroImagen);
}

void partida::on_btnVender_clicked()
{
    //aún no sé como hacerle para que el usuario pueda vender sus propiedades :'v
    //no se venden :v
}

void partida::mostrarFicha(int jugador)
{
    QPixmap pixmap(jugadores[jugador]->getRutaImagen());
    fichas[jugador].setPixmap(pixmap);
    fichas[jugador].setPixmap(pixmap);
    fichas[jugador].setX(jugadores[jugador]->getX());
    fichas[jugador].setY(jugadores[jugador]->getY());
    scene->addItem(&fichas[jugador]);
}

void partida::mover1Casilla(int jugador)
{
    if(jugadores[jugador]->getPosicion()->getId()<10)
        jugadores[jugador]->setX(jugadores[jugador]->getX()-40);
    else if(jugadores[jugador]->getPosicion()->getId()<20)
        jugadores[jugador]->setY(jugadores[jugador]->getY()-40);
    else if(jugadores[jugador]->getPosicion()->getId()<30)
        jugadores[jugador]->setX(jugadores[jugador]->getX()+40);
    else if(jugadores[jugador]->getPosicion()->getId()<40)
        jugadores[jugador]->setY(jugadores[jugador]->getY()+40);
    scene->removeItem(&fichas[jugador]);
    mostrarFicha(jugador);
    jugadores[jugador]->setPosicion(jugadores[jugador]->getPosicion()->getSig());
    //si llega al inicio
    if(jugadores[jugador]->getPosicion()->getId() == 0 && jugadores[jugador]->getCarcel() == NO_ART_35)
    {
        jugadores[jugador]->setDinero(jugadores[jugador]->getDinero() + 200);
        actualizarEtiquetasDinero();
    }
}

int partida::calcularAlquiler(Propiedad*propiedad)
{
    //primero vamos a revisar los casos especiales de propiedades
    //que son solo 2 en su conjunto, luego las 4 estaciones y finalmente
    //mediante el modulo del id de la propiedad revisaremos si se trata
    //de la primera propiedad del trio, de la segunda o de la tercera
    //para así evaluar solamente 3 casos y no caso a caso por propiedad
    int alquiler=propiedad->getAlquiler();
    int idPropiedad=propiedad->getCodigo();
    int duenio=propiedad->getDuenio();
    //revisa el brother
    if(idPropiedad==1)
    {
        if(tablero->getPropiedadById(2)->getDuenio()==duenio)
        {
            alquiler=alquiler*2;
        }
    }
    //revisa doña tifo
    else if(idPropiedad==2)
    {
        if(tablero->getPropiedadById(1)->getDuenio()==duenio)
        {
            alquiler=alquiler*2;
        }
    }
    //revisa el chedraui
    else if(idPropiedad==21)
    {
        if(tablero->getPropiedadById(22)->getDuenio()==duenio)
        {
            alquiler=alquiler*2;
        }
    }
    //revisa rectoria
    else if(idPropiedad==22)
    {
        if(tablero->getPropiedadById(21)->getDuenio()==duenio)
        {
            alquiler=alquiler*2;
        }
    }
    //revisa el coliseo
    else if(idPropiedad==27)
    {
        if(tablero->getPropiedadById(28)->getDuenio()==duenio)
        {
            alquiler=(dado1+dado2)*10;
        }
        else alquiler=(dado1+dado2)*4;
    }
    //revisa el gum
    else if(idPropiedad==28)
    {
        if(tablero->getPropiedadById(27)->getDuenio()==duenio)
        {
            alquiler=(dado1+dado2)*10;
        }
        alquiler=(dado1+dado2)*4;
    }
    //revisar rutas camiones
    else if(idPropiedad==23 || idPropiedad==24 || idPropiedad==25 || idPropiedad==26)
    {
        int contador=0;
        if(tablero->getPropiedadById(23)->getDuenio()==duenio)
            contador++;
        if(tablero->getPropiedadById(24)->getDuenio()==duenio)
            contador++;
        if(tablero->getPropiedadById(25)->getDuenio()==duenio)
            contador++;
        if(tablero->getPropiedadById(26)->getDuenio()==duenio)
            contador++;
        switch(contador)
        {
        case 1:
            alquiler=25;
            break;
        case 2:
            alquiler=50;
            break;
        case 3:
            alquiler=100;
            break;
        case 4:
            alquiler=200;
            break;
        default:
            alquiler=0;
        }
    }
    //la primer propiedad del trio
    else if( (propiedad->getCodigo()%3) == 0 )
    {
        if( tablero->getPropiedadById(idPropiedad+1)->getDuenio() == duenio &&
            tablero->getPropiedadById(idPropiedad+2)->getDuenio() == duenio)
            alquiler=alquiler*2;
    }
    else if( (propiedad->getCodigo()%3) == 1 )
    {
        if( tablero->getPropiedadById(idPropiedad-1)->getDuenio() == duenio &&
            tablero->getPropiedadById(idPropiedad+1)->getDuenio() == duenio)
            alquiler=alquiler*2;
    }
    else if( (propiedad->getCodigo()%3) == 2 )
    {
        if( tablero->getPropiedadById(idPropiedad-1)->getDuenio() == duenio &&
            tablero->getPropiedadById(idPropiedad-2)->getDuenio() == duenio)
            alquiler=alquiler*2;
    }
    return alquiler;
}

void partida::cobrarAlquiler(int pagador, Propiedad *propiedad)
{
    int alquiler=calcularAlquiler(propiedad);
    jugadores[pagador]->setDinero(jugadores[pagador]->getDinero() - alquiler);
    jugadores[propiedad->getDuenio()]->setDinero(jugadores[propiedad->getDuenio()]->getDinero() + alquiler);
    ui->lblMensajes->setText("Alquiler cobrado de jugador "
                             + jugadores[pagador]->getNombre() + " a "
                             + jugadores[propiedad->getDuenio()]->getNombre() + ":$"
                             + QString::number(alquiler) + ".00");
    actualizarEtiquetasDinero();
}

void partida::setDados(int dad1,int dad2)
{
    this->dado1=dad1;
    this->dado2=dad2;
}

void partida::mostrarEtiquetasDados()
{
    //pasar los datos a qstring's
    QString dado1aux=QString::number(dado1);
    QString dado2aux=QString::number(dado2);
    //mostrar el resultado de los dados
    ui->lblDado1->setText(dado1aux);
    ui->lblDado2->setText(dado2aux);
}

void partida::moverFicha(int cantidadMovimientos, int jugador)
{
    //mover la ficha
    for(int i=0;i<cantidadMovimientos;i++)
    {
        s.delay();
        mover1Casilla(jugador);
    }
    //revisar si cayó en la carcel
    if(jugadores[jugador]->getPosicion()->getId() == 30)
    {
        ui->lblMensajes->setText(jugadores[jugador]->getNombre()+" a caido en Articulo 35 :'c");
        moverJugadorAArt35(jugador);
    }
}

void partida::accionCasillaActual(Casilla *casilla,int jugador)
{
    bool actualizarTurno=true;
    if(casilla->getTipo()==PROPIEDAD)
    {
        ui->lblNombreCasilla->setText(casilla->getPropiedad()->getNombre());
        //revisar si la casilla tiene dueño
        if(casilla->getPropiedad()->getDuenio() > 0)
        {
            QString alquiler=QString::number(casilla->getPropiedad()->getAlquiler());
            ui->lblPrecioCasilla->setText("Alquiler:$"+alquiler+".00");
            //la casilla no es tuya :'c
            if(casilla->getPropiedad()->getDuenio() != jugadores[jugador]->getCodigo())
            {
                cobrarAlquiler(turno,casilla->getPropiedad());
            }
            //la casilla es tuya
            else
            {
                //no pasa nada
                ui->lblMensajes->setText("Casilla propiedad del jugador");
            }
        }
        //si no tiene dueño
        else
        {
            QString precio=QString::number(casilla->getPropiedad()->getPrecio());
            ui->lblPrecioCasilla->setText("Precio:$"+precio+".00");
            //revisa si el jugador tiene dinero para comprarla
            if(jugadores[jugador]->getDinero() > casilla->getPropiedad()->getPrecio())
            {
                if(turno==numeroJugador){
                    paqueteEsperado=NO_PCKG;
                    ui->btnComprar->setVisible(true);
                    ui->btnNoComprar->setVisible(true);
                }
                else paqueteEsperado=COMPRA;
                actualizarTurno=false;
            }
            //si no tiene dinero
            else
            {
                ui->lblMensajes->setText("El jugador no tiene dinero para comprar esta propiedad");
            }
        }
    }
    else if(casilla->getTipo()==PARADA_LIBRE)
    {
        if(casilla->getId() == 10 && jugadores[jugador]->getCarcel() != NO_ART_35)
        {
            ui->lblNombreCasilla->setText("Articulo 35");
            ui->lblPrecioCasilla->setText("");
            //actualizarTurno=false;
        }
        else
        {
            ui->lblNombreCasilla->setText("Parada libre");
            ui->lblPrecioCasilla->setText("");
        }
    }
    else if(casilla->getTipo()==DE_PAGO)
    {
        ui->lblPrecioCasilla->setText("Cobro: $"+QString::number(casilla->getPago()->getPago()));
        ui->lblNombreCasilla->setText(casilla->getPago()->getNombre());
        jugadores[jugador]->setDinero(jugadores[jugador]->getDinero() - casilla->getPago()->getPago());
        ui->lblMensajes->setText("Pago cobrado a "
                                 + jugadores[jugador]->getNombre() +" :$"
                                 + QString::number(casilla->getPago()->getPago()) + ".00");
        actualizarEtiquetasDinero();
    }
    if(actualizarTurno)
        asignarTurno();
}

void partida::asignarTurno()
{
    //revisar de quien es el siguiente turno y asignar
    if(dado1!=dado2)
    {
        if(turno==NUMJUGADORES)
            turno=1;
        else
            turno++;
        QString auxTurno=QString::number(turno);
        ui->lblTurno->setText("Turno Jugador "+auxTurno+": "+jugadores[turno]->getNombre());
    }
    else
    {
        if(jugadores[turno]->getCarcel() == NO_ART_35)
        {
            QString auxTurno=QString::number(turno);
            ui->lblTurno->setText("Nuevamente Jugador "+auxTurno+": "+jugadores[turno]->getNombre());
        }
        else
        {
            if(turno==NUMJUGADORES)
                turno=1;
            else
                turno++;
            QString auxTurno=QString::number(turno);
            ui->lblTurno->setText("Turno Jugador "+auxTurno+": "+jugadores[turno]->getNombre());
        }
    }
    //provisional en lo que se hace el juego en línea
    if(turno==numeroJugador)
    {
        ui->btnDados->setVisible(true);
        if(jugadores[turno]->getCarcel() != NO_ART_35)
            ui->btnPagarArticulo->setVisible(true);
    }
    if(jugadores[1]->getDinero()<=0||jugadores[2]->getDinero()<=0){
        QString ganador;
        if(jugadores[1]->getDinero()<=0) ganador=jugadores[2]->getNombre();
        else ganador=jugadores[1]->getNombre();
        QMessageBox messageBox;
        messageBox.information(0,"FIN DE PARTIDA",ganador+" gano!");
        messageBox.setFixedSize(500,200);
        socket->close();
        this->close();
    }
}

void partida::comprar(int jugador,Propiedad*propiedad)
{
    //revisa que tenga suficiente dinero
    propiedad->setDuenio(jugador);
    jugadores[jugador]->setDinero(jugadores[jugador]->getDinero() - propiedad->getPrecio());
    ui->lblMensajes->setText(propiedad->getNombre()+" comprado por "+jugadores[jugador]->getNombre());
    actualizarEtiquetasDinero();
}

void partida::on_btnEsperarConexion_clicked()
{
    paqueteEsperado=NO_PCKG;
    QString ip=ui->tbxIp->text();
    QString puertoString=ui->tbxPuerto->text();
    bool puertoValido=false;
    quint16 puerto=puertoString.toShort(&puertoValido,10);
    if(puertoValido)
    {
        //si se pudo convertir y es puerto valido
        ui->lblMensajes->setText("Puerto valido :v");
        s.delay();
        s.delay();
        s.delay();
    }
    else
    {
        ui->lblMensajes->setText("Puerto invalido, se utilizara el 33120");
        puertoValido=true;
        puerto=33120;
        s.delay();
        s.delay();
        s.delay();
    }
    ui->lblIp->setVisible(false);
    ui->tbxIp->setVisible(false);
    ui->lblPuerto->setVisible(false);
    ui->tbxPuerto->setVisible(false);
    ui->btnConectar->setVisible(false);
    ui->btnEsperarConexion->setVisible(false);
    ui->lblNombre->setVisible(false);
    ui->tbxNombre->setVisible(false);
    QString nom = ui->tbxNombre->text();
    if(nom.length()<=0 || nom.length()>15)
    {
        ui->lblMensajes->setText("Nombre invalido, se utilizará Felix");
        nom="Felix";
        ui->lblTitulo->setText("MONOPOLY CUCEI :V - "+nom);
        s.delay();
        s.delay();
    }
    if(!server->listen(QHostAddress::Any, puerto))
    {
        ui->lblMensajes->setText("No se pudo iniciar el servidor");
    }
    else
    {
        ui->lblMensajes->setText("Esperando conexion en "+QString::number(puerto));
    }
    jugadores[1]= new Jugador(1,nom,1000,"../monopolyCucei/images/memputa.png");
    numeroJugador=1;
}

void partida::on_btnComprar_clicked()
{
    comprar(turno,jugadores[turno]->getPosicion()->getPropiedad());
    ui->btnComprar->setVisible(false);
    ui->btnNoComprar->setVisible(false);
    char bytes[2];
    bytes[0]=COMPRA;
    bytes[1]=1;
    socket->write(bytes,2);
    asignarTurno();
    paqueteEsperado=DADOS;
}

void partida::on_btnNoComprar_clicked()
{
    ui->btnComprar->setVisible(false);
    ui->btnNoComprar->setVisible(false);
    char bytes[2];
    bytes[0]=COMPRA;
    bytes[1]=0;
    socket->write(bytes,2);
    asignarTurno();
    paqueteEsperado=DADOS;
}

void partida::actualizarEtiquetasDinero()
{
    ui->lblDineroJugador1->setText("$"+QString::number(jugadores[1]->getDinero())+".00");
    ui->lblDineroJugador2->setText("$"+QString::number(jugadores[2]->getDinero())+".00");
}

void partida::moverJugadorAArt35(int jugador)
{
    jugadores[jugador]->setCarcel(INICIO_ART_35);
    while (jugadores[jugador]->getPosicion()->getId() != 10)
    {
        //s.delay();
        mover1Casilla(jugador);
    }
    ui->lblNombreCasilla->setText("Articulo 35");
    ui->lblPrecioCasilla->setText("");
}

void partida::liberarDeArticulo(int jugador)
{
    ui->lblMensajes->setText("Articulo 35 pagado por "+jugadores[jugador]->getNombre());
    jugadores[jugador]->setCarcel(NO_ART_35);
    jugadores[jugador]->setDinero(jugadores[jugador]->getDinero() - PRECIO_ART_35);
    actualizarEtiquetasDinero();
}

void partida::newConnection(){
    socket=server->nextPendingConnection();
    server->close();
    connect(socket,&QTcpSocket::connected,this,&partida::connected);
    connect(socket,&QTcpSocket::readyRead,this,&partida::dataRecvd);
    connect(socket,&QTcpSocket::disconnected,this,&partida::desconexion);
    ui->lblMensajes->setText("Conectado");
    ui->lblIp->setVisible(false);
    ui->tbxIp->setVisible(false);
    ui->lblPuerto->setVisible(false);
    ui->tbxPuerto->setVisible(false);
    ui->lblNombre->setVisible(false);
    ui->tbxNombre->setVisible(false);
    char pckg[16]={0};
    pckg[0]=NOM_J;
    strcpy(&(pckg[1]),jugadores[1]->getNombre().toStdString().c_str());
    socket->write(pckg,16);
    paqueteEsperado=NOM_J;
}

void partida::connected(){
    ui->lblMensajes->setText("Conectado, esperando nombre");

    if(socket->state()==QTcpSocket::ConnectedState){
        ui->btnConectar->setVisible(false);
        ui->btnEsperarConexion->setVisible(false);
        ui->lblIp->setVisible(false);
        ui->tbxIp->setVisible(false);
        ui->lblPuerto->setVisible(false);
        ui->tbxPuerto->setVisible(false);
        ui->lblNombre->setVisible(false);
        ui->tbxNombre->setVisible(false);
        paqueteEsperado=NOM_J;
        //ui->btnDados->setVisible(true);
    }
}

void partida::dataRecvd(){
    char t;
    int n=socket->read(&t,1);
    if(n>0){
        if(paqueteEsperado==DADOS && jugadores[turno]->getCarcel() != NO_ART_35 && t==PAGAR_ART)
        {
            liberarDeArticulo(turno);
        }
        else if(t!=paqueteEsperado){
            QMessageBox messageBox;
            messageBox.critical(0,"ERROR","paquete recibido diferente del esperado\nPOSIBLE desincronozacion\nel juego se cerrara");
            messageBox.setFixedSize(500,200);
            socket->close();
            this->close();
        }
        else{
            if(t==NOM_J){
                recibirNombre();
            }
            else if(t==DADOS)
                recibirDados();
            else if(t==COMPRA)
                recibirCompra();
        }
    }
}

void partida::recibirNombre(){
    char pckg[16]={0};
    int n=socket->read(pckg,15);
    if(n>0){
        ui->lblMensajes->setText("Nombre recibido, listo para jugar");
        QString nom=pckg;
        if(numeroJugador==1){
            jugadores[2]=new Jugador(2,nom,1000,"../monopolyCucei/images/n-pac.png");
            ui->btnDados->setVisible(true);
            paqueteEsperado=NO_PCKG;
            ui->lblTurno->setText("Turno Jugador 1: "+jugadores[1]->getNombre());
        }
        else{
            jugadores[1]=new Jugador(1,nom,1000,"../monopolyCucei/images/memputa.png");
            char tosnd[16]={0};
            tosnd[0]=NOM_J;
            strcpy(&(tosnd[1]),jugadores[2]->getNombre().toStdString().c_str());
            socket->write(tosnd,16);
            paqueteEsperado=DADOS;
            ui->lblTurno->setText("Turno Jugador 1: "+jugadores[1]->getNombre());
        }
        ui->lblNombreJugador1->setText(jugadores[1]->getNombre());
        ui->lblNombreJugador2->setText(jugadores[2]->getNombre());
        mostrarTablero(0,0);
        actualizarEtiquetasDinero();
        for(int i=1;i<=NUMJUGADORES;i++)
            mostrarFicha(i);
        for(int i=1;i<=NUMJUGADORES;i++)
                jugadores[i]->setPosicion(tablero->getInicio());
    }
    else if(n<0){
        mostrarErrorYCerrar();
    }

}

void partida::recibirDados(){
    //limpiar mensajes
    ui->lblMensajes->setText("");
    unsigned char bytes;
    int dad1=0,dad2=0;
    int n=socket->read((char*)&bytes,1);
    if(n>0){
        bytes=bytes<<2;
        bytes=bytes>>2;
        char aux=bytes;
        aux=aux>>3;
        dad1=aux;
        aux=aux<<3;
        dad2=bytes^aux;
        //setDados(dad1,dad2);
        //mostrarEtiquetasDados();
        if((dad1>6||dad1<1)||(dad2>6||dad2<1)){
            //el contrincante hizo trampa
            QMessageBox messageBox;
            messageBox.critical(0,"Error","el contrincante hizo trampa!\ncerrando conexion y juego");
            messageBox.setFixedSize(500,200);
            socket->close();
            this->close();
        }
    }
    else if(n<0){
        mostrarErrorYCerrar();
    }
    //todo lo que sigue a continuación se hará cuando se reciba el paquete
    //asignar dados
    setDados(dad1,dad2);
    //mostrar etiquetas de dados
    mostrarEtiquetasDados();
    //sumar tiro doble o reiniciar
    if(dado1==dado2)
        jugadores[turno]->setTirosDobles(jugadores[turno]->getTirosDobles()+1);
    else
        jugadores[turno]->setTirosDobles(0);
    //comprobar articulo 35 y triple tiro doble
    if(jugadores[turno]->getCarcel() == NO_ART_35)
    {
        if(jugadores[turno]->getTirosDobles()==3)
        {
            ui->lblMensajes->setText("Triple tiro doble, "+jugadores[turno]->getNombre()+" cae en articulo 35 :'c");
            jugadores[turno]->setTirosDobles(0);
            moverJugadorAArt35(turno);
        }
        else//mover ficha
        {
            moverFicha(dado1+dado2,turno);
        }
    }
    else
    {
        if(dado1 == dado2)
        {
            ui->lblMensajes->setText("Tiro doble, articulo 35 perdonado c':");
            jugadores[turno]->setCarcel(NO_ART_35);
            //mover ficha
            moverFicha(dado1+dado2,turno);
        }
        else
        {
            jugadores[turno]->setCarcel(jugadores[turno]->getCarcel()+1);
            if(jugadores[turno]->getCarcel() > LIMIT_ART_35)
            {
                ui->lblMensajes->setText("Tiempo de artículo 35 terminado, se cobrarán $50.00");
                jugadores[turno]->setCarcel(NO_ART_35);
                jugadores[turno]->setDinero(jugadores[turno]->getDinero() - PRECIO_ART_35);
                actualizarEtiquetasDinero();
            }
            else
            {
                ui->lblMensajes->setText("No hay tiro doble, " +jugadores[turno]->getNombre()+ " continua en articulo");
            }
        }
    }
    paqueteEsperado=DADOS;
    //mostrar informacion de la casilla y realizar accion
    //actualiza turno en caso de ser posible
    accionCasillaActual(jugadores[turno]->getPosicion(),turno);
}

void partida::recibirCompra(){
    ui->lblMensajes->setText("");
    char byte;
    int n=socket->read(&byte,1);
    if(n>0){
        if(byte!=0){
            comprar(turno,jugadores[turno]->getPosicion()->getPropiedad());
        }
        paqueteEsperado=DADOS;
        asignarTurno();
    }
    else if(n<0){
        mostrarErrorYCerrar();
    }
}

void partida::desconexion(){
    if(!(jugadores[1]->getDinero()<=0)&&!(jugadores[2]->getDinero()<=0)){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Conexion perdida!");
        messageBox.setFixedSize(500,200);
        this->close();
    }
}

void partida::mostrarErrorYCerrar(){
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Un error fatal ha ocurrido D=!\nEl juego se cerrara");
    messageBox.setFixedSize(500,200);
    this->close();
}

void partida::on_btnPagarArticulo_clicked()
{
    ui->btnPagarArticulo->setVisible(false);
    liberarDeArticulo(turno);
    char byte[1];
    byte[0]=PAGAR_ART;
    socket->write(byte,1);
}

void partida::keyPressEvent(QKeyEvent *event)
{
}
