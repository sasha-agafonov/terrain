/****************************************************************************
** Meta object code from reading C++ file 'interface_hydro_parameters_menu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "interface_hydro_parameters_menu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface_hydro_parameters_menu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_hydro_parameters_menu_t {
    QByteArrayData data[6];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_hydro_parameters_menu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_hydro_parameters_menu_t qt_meta_stringdata_hydro_parameters_menu = {
    {
QT_MOC_LITERAL(0, 0, 21), // "hydro_parameters_menu"
QT_MOC_LITERAL(1, 22, 29), // "eroded_heightmap_valid_signal"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 26), // "erosion_parameters_changed"
QT_MOC_LITERAL(4, 80, 15), // "erode_heightmap"
QT_MOC_LITERAL(5, 96, 22) // "eroded_heightmap_valid"

    },
    "hydro_parameters_menu\0"
    "eroded_heightmap_valid_signal\0\0"
    "erosion_parameters_changed\0erode_heightmap\0"
    "eroded_heightmap_valid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_hydro_parameters_menu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void hydro_parameters_menu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<hydro_parameters_menu *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->eroded_heightmap_valid_signal(); break;
        case 1: _t->erosion_parameters_changed(); break;
        case 2: _t->erode_heightmap(); break;
        case 3: _t->eroded_heightmap_valid(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (hydro_parameters_menu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&hydro_parameters_menu::eroded_heightmap_valid_signal)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject hydro_parameters_menu::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_hydro_parameters_menu.data,
    qt_meta_data_hydro_parameters_menu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *hydro_parameters_menu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *hydro_parameters_menu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_hydro_parameters_menu.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int hydro_parameters_menu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void hydro_parameters_menu::eroded_heightmap_valid_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
