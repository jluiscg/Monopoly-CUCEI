/****************************************************************************
** Meta object code from reading C++ file 'partida.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../monopolyCucei/partida.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'partida.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_partida_t {
    QByteArrayData data[13];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_partida_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_partida_t qt_meta_stringdata_partida = {
    {
QT_MOC_LITERAL(0, 0, 7), // "partida"
QT_MOC_LITERAL(1, 8, 19), // "on_btnDados_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 22), // "on_btnConectar_clicked"
QT_MOC_LITERAL(4, 52, 20), // "on_btnVender_clicked"
QT_MOC_LITERAL(5, 73, 29), // "on_btnEsperarConexion_clicked"
QT_MOC_LITERAL(6, 103, 21), // "on_btnComprar_clicked"
QT_MOC_LITERAL(7, 125, 23), // "on_btnNoComprar_clicked"
QT_MOC_LITERAL(8, 149, 13), // "newConnection"
QT_MOC_LITERAL(9, 163, 9), // "connected"
QT_MOC_LITERAL(10, 173, 9), // "dataRecvd"
QT_MOC_LITERAL(11, 183, 11), // "desconexion"
QT_MOC_LITERAL(12, 195, 27) // "on_btnPagarArticulo_clicked"

    },
    "partida\0on_btnDados_clicked\0\0"
    "on_btnConectar_clicked\0on_btnVender_clicked\0"
    "on_btnEsperarConexion_clicked\0"
    "on_btnComprar_clicked\0on_btnNoComprar_clicked\0"
    "newConnection\0connected\0dataRecvd\0"
    "desconexion\0on_btnPagarArticulo_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_partida[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void partida::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        partida *_t = static_cast<partida *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnDados_clicked(); break;
        case 1: _t->on_btnConectar_clicked(); break;
        case 2: _t->on_btnVender_clicked(); break;
        case 3: _t->on_btnEsperarConexion_clicked(); break;
        case 4: _t->on_btnComprar_clicked(); break;
        case 5: _t->on_btnNoComprar_clicked(); break;
        case 6: _t->newConnection(); break;
        case 7: _t->connected(); break;
        case 8: _t->dataRecvd(); break;
        case 9: _t->desconexion(); break;
        case 10: _t->on_btnPagarArticulo_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject partida::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_partida.data,
      qt_meta_data_partida,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *partida::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *partida::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_partida.stringdata0))
        return static_cast<void*>(const_cast< partida*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int partida::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
