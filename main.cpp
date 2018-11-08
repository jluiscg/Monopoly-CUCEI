#include "partida.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    partida w;
    w.show();

    return a.exec();
}
