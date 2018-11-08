#ifndef PARTIDA_H
#define PARTIDA_H
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include "sleeper.h"
#include "tablero.h"
#include "jugador.h"
#include <time.h>
#define NUMJUGADORES 2
#define NO_PCKG 0
#define NOM_J 1
#define DADOS 2
#define COMPRA 3
#define PAGAR_ART 4
#define NO_ART_35 0
#define INICIO_ART_35 1
#define LIMIT_ART_35 3
#define PRECIO_ART_35 50
namespace Ui {
class partida;
}

class partida : public QMainWindow
{
    Q_OBJECT

public:
    explicit partida(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    ~partida();

private slots:
    void on_btnDados_clicked();

    void on_btnConectar_clicked();

    void on_btnVender_clicked();

    void on_btnEsperarConexion_clicked();

    void on_btnComprar_clicked();

    void on_btnNoComprar_clicked();

    void newConnection();

    void connected();

    void dataRecvd();

    void desconexion();

    void on_btnPagarArticulo_clicked();

private:
    Ui::partida *ui;
    QGraphicsScene *scene;
    Sleeper s;
    QGraphicsPixmapItem tableroImagen;
    QGraphicsPixmapItem fichas[NUMJUGADORES+1];
    Tablero *tablero;
    Jugador *jugadores[NUMJUGADORES+1];
    QTcpSocket* socket;
    QTcpServer* server;
    int turno;
    int dado1;
    int dado2;
    int dobles;
    int numeroJugador;
    int paqueteEsperado;
    void mostrarTablero(int x,int y);
    void mostrarFicha(int jugador);
    void mover1Casilla(int jugador);
    int calcularAlquiler(Propiedad*propiedad);
    void cobrarAlquiler(int pagador,Propiedad*propiedad);
    void setDados(int dad1,int dad2);
    void mostrarEtiquetasDados();
    void moverFicha(int cantidadMovimientos,int jugador);
    void accionCasillaActual(Casilla*casilla,int jugador);
    void asignarTurno();
    void comprar(int jugador,Propiedad*propiedad);
    void actualizarEtiquetasDinero();
    void moverJugadorAArt35(int jugador);
    void liberarDeArticulo(int jugador);
    void recibirNombre();
    void recibirDados();
    void recibirCompra();
    void mostrarErrorYCerrar();
};

#endif // PARTIDA_H
