/****************************************************************************
** Meta object code from reading C++ file 'WynikGry.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../WynikGry.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WynikGry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGameScoreENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGameScoreENDCLASS = QtMocHelpers::stringData(
    "GameScore",
    "aktualizujCzasGry",
    "",
    "std::string",
    "czas",
    "aktualizujPunkty",
    "points",
    "updateTimer"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGameScoreENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[10];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[5];
    char stringdata5[17];
    char stringdata6[7];
    char stringdata7[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGameScoreENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGameScoreENDCLASS_t qt_meta_stringdata_CLASSGameScoreENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "GameScore"
        QT_MOC_LITERAL(10, 17),  // "aktualizujCzasGry"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 11),  // "std::string"
        QT_MOC_LITERAL(41, 4),  // "czas"
        QT_MOC_LITERAL(46, 16),  // "aktualizujPunkty"
        QT_MOC_LITERAL(63, 6),  // "points"
        QT_MOC_LITERAL(70, 11)   // "updateTimer"
    },
    "GameScore",
    "aktualizujCzasGry",
    "",
    "std::string",
    "czas",
    "aktualizujPunkty",
    "points",
    "updateTimer"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGameScoreENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       5,    1,   35,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   38,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GameScore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSGameScoreENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGameScoreENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGameScoreENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GameScore, std::true_type>,
        // method 'aktualizujCzasGry'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::string, std::false_type>,
        // method 'aktualizujPunkty'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateTimer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GameScore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameScore *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->aktualizujCzasGry((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 1: _t->aktualizujPunkty((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->updateTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameScore::*)(std::string );
            if (_t _q_method = &GameScore::aktualizujCzasGry; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameScore::*)(int );
            if (_t _q_method = &GameScore::aktualizujPunkty; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *GameScore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameScore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGameScoreENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GameScore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GameScore::aktualizujCzasGry(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameScore::aktualizujPunkty(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
