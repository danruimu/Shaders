/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created: Mon Dec 3 13:44:39 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/glwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      32,   31,   31,    9, 0x0a,
      39,   31,   31,    9, 0x0a,
      60,   51,   31,    9, 0x0a,
      87,   31,   31,    9, 0x0a,
     101,   31,   31,    9, 0x0a,
     116,   31,  112,    9, 0x0a,
     143,   31,   31,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLWidget[] = {
    "GLWidget\0PLUGINGLWIDGET_EXPORT\0\0help()\0"
    "addObject()\0filename\0addObjectFromFile(QString)\0"
    "resetCamera()\0drawAxes()\0Box\0"
    "boundingBoxIncludingAxes()\0loadPlugin()\0"
};

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLWidget *_t = static_cast<GLWidget *>(_o);
        switch (_id) {
        case 0: _t->help(); break;
        case 1: _t->addObject(); break;
        case 2: _t->addObjectFromFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->resetCamera(); break;
        case 4: _t->drawAxes(); break;
        case 5: { Box _r = _t->boundingBoxIncludingAxes();
            if (_a[0]) *reinterpret_cast< Box*>(_a[0]) = _r; }  break;
        case 6: _t->loadPlugin(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLWidget,
      qt_meta_data_GLWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLWidget))
        return static_cast<void*>(const_cast< GLWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
