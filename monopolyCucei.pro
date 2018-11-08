#-------------------------------------------------
#
# Project created by QtCreator 2016-10-17T08:55:40
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monopolyCucei
TEMPLATE = app


SOURCES += main.cpp\
        partida.cpp \
    casilla.cpp \
    propiedad.cpp \
    tablero.cpp \
    sleeper.cpp \
    jugador.cpp \
    pagoservicio.cpp

HEADERS  += partida.h \
    casilla.h \
    propiedad.h \
    tablero.h \
    sleeper.h \
    jugador.h \
    pagoservicio.h \
    protocol.h

FORMS    += partida.ui

RESOURCES += \
    images.qrc

QMAKE_CXXFLAGS += -std=c++0x
