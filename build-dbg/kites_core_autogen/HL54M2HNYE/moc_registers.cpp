/****************************************************************************
** Meta object code from reading C++ file 'registers.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/processor/registers.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registers.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
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
struct qt_meta_tag_ZN5Kites12RegisterFileE_t {};
} // unnamed namespace

template <> constexpr inline auto Kites::RegisterFile::qt_create_metaobjectdata<qt_meta_tag_ZN5Kites12RegisterFileE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Kites::RegisterFile",
        "updateRegister",
        "",
        "size_t",
        "regIndex",
        "uint64_t",
        "value",
        "updateFRegister",
        "registerResetSignal"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'updateRegister'
        QtMocHelpers::SignalData<void(size_t, uint64_t)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'updateFRegister'
        QtMocHelpers::SignalData<void(size_t, uint64_t)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Signal 'registerResetSignal'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RegisterFile, qt_meta_tag_ZN5Kites12RegisterFileE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Kites::RegisterFile::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites12RegisterFileE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites12RegisterFileE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5Kites12RegisterFileE_t>.metaTypes,
    nullptr
} };

void Kites::RegisterFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RegisterFile *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->updateRegister((*reinterpret_cast<std::add_pointer_t<size_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[2]))); break;
        case 1: _t->updateFRegister((*reinterpret_cast<std::add_pointer_t<size_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[2]))); break;
        case 2: _t->registerResetSignal(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RegisterFile::*)(size_t , uint64_t )>(_a, &RegisterFile::updateRegister, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RegisterFile::*)(size_t , uint64_t )>(_a, &RegisterFile::updateFRegister, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RegisterFile::*)()>(_a, &RegisterFile::registerResetSignal, 2))
            return;
    }
}

const QMetaObject *Kites::RegisterFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kites::RegisterFile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites12RegisterFileE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Kites::RegisterFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Kites::RegisterFile::updateRegister(size_t _t1, uint64_t _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void Kites::RegisterFile::updateFRegister(size_t _t1, uint64_t _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void Kites::RegisterFile::registerResetSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
