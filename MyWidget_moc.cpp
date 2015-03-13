/****************************************************************************
** Meta object code from reading C++ file 'MyWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      31,    9,    9,    9, 0x08,
      54,    9,    9,    9, 0x08,
      77,    9,    9,    9, 0x08,
     102,    9,    9,    9, 0x08,
     112,    9,    9,    9, 0x08,
     120,    9,    9,    9, 0x08,
     133,    9,    9,    9, 0x08,
     145,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MyWidget[] = {
    "MyWidget\0\0sliderValueChanged()\0"
    "spinBValueChanged(int)\0exsliderValueChanged()\0"
    "exsTrliderValueChanged()\0animate()\0"
    "about()\0parameters()\0translate()\0"
    "setColor()\0"
};

void MyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MyWidget *_t = static_cast<MyWidget *>(_o);
        switch (_id) {
        case 0: _t->sliderValueChanged(); break;
        case 1: _t->spinBValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->exsliderValueChanged(); break;
        case 3: _t->exsTrliderValueChanged(); break;
        case 4: _t->animate(); break;
        case 5: _t->about(); break;
        case 6: _t->parameters(); break;
        case 7: _t->translate(); break;
        case 8: _t->setColor(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MyWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyWidget::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyWidget,
      qt_meta_data_MyWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyWidget))
        return static_cast<void*>(const_cast< MyWidget*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
