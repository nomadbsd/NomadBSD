/****************************************************************************
** Meta object code from reading C++ file 'wizard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "src/wizard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wizard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SetupWizard_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetupWizard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetupWizard_t qt_meta_stringdata_SetupWizard = {
    {
QT_MOC_LITERAL(0, 0, 11) // "SetupWizard"

    },
    "SetupWizard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetupWizard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SetupWizard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SetupWizard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizard::staticMetaObject>(),
    qt_meta_stringdata_SetupWizard.data,
    qt_meta_data_SetupWizard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SetupWizard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetupWizard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SetupWizard.stringdata0))
        return static_cast<void*>(this);
    return QWizard::qt_metacast(_clname);
}

int SetupWizard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizard::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_WelcomePage_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WelcomePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WelcomePage_t qt_meta_stringdata_WelcomePage = {
    {
QT_MOC_LITERAL(0, 0, 11) // "WelcomePage"

    },
    "WelcomePage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WelcomePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void WelcomePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject WelcomePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_WelcomePage.data,
    qt_meta_data_WelcomePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WelcomePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WelcomePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WelcomePage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int WelcomePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_LocalePage_t {
    QByteArrayData data[4];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LocalePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LocalePage_t qt_meta_stringdata_LocalePage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LocalePage"
QT_MOC_LITERAL(1, 11, 14), // "localeSelected"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3) // "row"

    },
    "LocalePage\0localeSelected\0\0row"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LocalePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void LocalePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LocalePage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->localeSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LocalePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_LocalePage.data,
    qt_meta_data_LocalePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LocalePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LocalePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LocalePage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int LocalePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_KbdLayoutPage_t {
    QByteArrayData data[5];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KbdLayoutPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KbdLayoutPage_t qt_meta_stringdata_KbdLayoutPage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "KbdLayoutPage"
QT_MOC_LITERAL(1, 14, 17), // "kbdLayoutSelected"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "row"
QT_MOC_LITERAL(4, 37, 18) // "kbdVariantSelected"

    },
    "KbdLayoutPage\0kbdLayoutSelected\0\0row\0"
    "kbdVariantSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KbdLayoutPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void KbdLayoutPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KbdLayoutPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->kbdLayoutSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->kbdVariantSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KbdLayoutPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_KbdLayoutPage.data,
    qt_meta_data_KbdLayoutPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KbdLayoutPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KbdLayoutPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KbdLayoutPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int KbdLayoutPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_ExtraKbdLayoutPage_t {
    QByteArrayData data[7];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtraKbdLayoutPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtraKbdLayoutPage_t qt_meta_stringdata_ExtraKbdLayoutPage = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ExtraKbdLayoutPage"
QT_MOC_LITERAL(1, 19, 17), // "kbdLayoutSelected"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 3), // "row"
QT_MOC_LITERAL(4, 42, 18), // "kbdVariantSelected"
QT_MOC_LITERAL(5, 61, 9), // "addLayout"
QT_MOC_LITERAL(6, 71, 12) // "removeLayout"

    },
    "ExtraKbdLayoutPage\0kbdLayoutSelected\0"
    "\0row\0kbdVariantSelected\0addLayout\0"
    "removeLayout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtraKbdLayoutPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       5,    0,   40,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExtraKbdLayoutPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExtraKbdLayoutPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->kbdLayoutSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->kbdVariantSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addLayout(); break;
        case 3: _t->removeLayout(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExtraKbdLayoutPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_ExtraKbdLayoutPage.data,
    qt_meta_data_ExtraKbdLayoutPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ExtraKbdLayoutPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtraKbdLayoutPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtraKbdLayoutPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int ExtraKbdLayoutPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_TimezonePage_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TimezonePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TimezonePage_t qt_meta_stringdata_TimezonePage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TimezonePage"
QT_MOC_LITERAL(1, 13, 16), // "timezoneSelected"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3) // "row"

    },
    "TimezonePage\0timezoneSelected\0\0row"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TimezonePage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void TimezonePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimezonePage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->timezoneSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TimezonePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_TimezonePage.data,
    qt_meta_data_TimezonePage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TimezonePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimezonePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TimezonePage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int TimezonePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_PasswordPage_t {
    QByteArrayData data[3];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PasswordPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PasswordPage_t qt_meta_stringdata_PasswordPage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PasswordPage"
QT_MOC_LITERAL(1, 13, 15), // "passwordChanged"
QT_MOC_LITERAL(2, 29, 0) // ""

    },
    "PasswordPage\0passwordChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PasswordPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PasswordPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PasswordPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->passwordChanged(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject PasswordPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_PasswordPage.data,
    qt_meta_data_PasswordPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PasswordPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PasswordPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PasswordPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int PasswordPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_GeliPage_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GeliPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GeliPage_t qt_meta_stringdata_GeliPage = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GeliPage"
QT_MOC_LITERAL(1, 9, 7), // "setGeli"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 5), // "state"
QT_MOC_LITERAL(4, 24, 15) // "passwordChanged"

    },
    "GeliPage\0setGeli\0\0state\0passwordChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeliPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

       0        // eod
};

void GeliPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GeliPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setGeli((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->passwordChanged(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GeliPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_GeliPage.data,
    qt_meta_data_GeliPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GeliPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeliPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GeliPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int GeliPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_ProgramsPage_t {
    QByteArrayData data[3];
    char stringdata0[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProgramsPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProgramsPage_t qt_meta_stringdata_ProgramsPage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ProgramsPage"
QT_MOC_LITERAL(1, 13, 16), // "selectionChanged"
QT_MOC_LITERAL(2, 30, 0) // ""

    },
    "ProgramsPage\0selectionChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProgramsPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ProgramsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProgramsPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProgramsPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_ProgramsPage.data,
    qt_meta_data_ProgramsPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProgramsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProgramsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProgramsPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int ProgramsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_SummaryPage_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SummaryPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SummaryPage_t qt_meta_stringdata_SummaryPage = {
    {
QT_MOC_LITERAL(0, 0, 11) // "SummaryPage"

    },
    "SummaryPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SummaryPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SummaryPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SummaryPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_SummaryPage.data,
    qt_meta_data_SummaryPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SummaryPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SummaryPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SummaryPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int SummaryPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_CommitPage_t {
    QByteArrayData data[8];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CommitPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CommitPage_t qt_meta_stringdata_CommitPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CommitPage"
QT_MOC_LITERAL(1, 11, 13), // "readCmdOutput"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "readError"
QT_MOC_LITERAL(4, 36, 10), // "catchError"
QT_MOC_LITERAL(5, 47, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(6, 70, 7), // "cleanup"
QT_MOC_LITERAL(7, 78, 20) // "QProcess::ExitStatus"

    },
    "CommitPage\0readCmdOutput\0\0readError\0"
    "catchError\0QProcess::ProcessError\0"
    "cleanup\0QProcess::ExitStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CommitPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       6,    2,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,

       0        // eod
};

void CommitPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CommitPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readCmdOutput(); break;
        case 1: _t->readError(); break;
        case 2: _t->catchError((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 3: _t->cleanup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CommitPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWizardPage::staticMetaObject>(),
    qt_meta_stringdata_CommitPage.data,
    qt_meta_data_CommitPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CommitPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CommitPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CommitPage.stringdata0))
        return static_cast<void*>(this);
    return QWizardPage::qt_metacast(_clname);
}

int CommitPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWizardPage::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
