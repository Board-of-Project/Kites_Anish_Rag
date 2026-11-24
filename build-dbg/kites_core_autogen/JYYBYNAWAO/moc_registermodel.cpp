/****************************************************************************
** Meta object code from reading C++ file 'registermodel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/register_table/registermodel.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registermodel.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5Kites13RegisterModelE_t {};
} // unnamed namespace

template <> constexpr inline auto Kites::RegisterModel::qt_create_metaobjectdata<qt_meta_tag_ZN5Kites13RegisterModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Kites::RegisterModel",
        "updateRegisterValue",
        "",
        "size_t",
        "regIndex",
        "uint64_t",
        "value",
        "registerResetSlot",
        "updateFRegisterValue"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'updateRegisterValue'
        QtMocHelpers::SlotData<void(size_t, uint64_t)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
        // Slot 'registerResetSlot'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateFRegisterValue'
        QtMocHelpers::SlotData<void(size_t, uint64_t)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { 0x80000000 | 5, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RegisterModel, qt_meta_tag_ZN5Kites13RegisterModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Kites::RegisterModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractTableModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites13RegisterModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites13RegisterModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5Kites13RegisterModelE_t>.metaTypes,
    nullptr
} };

void Kites::RegisterModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RegisterModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->updateRegisterValue((*reinterpret_cast<std::add_pointer_t<size_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[2]))); break;
        case 1: _t->registerResetSlot(); break;
        case 2: _t->updateFRegisterValue((*reinterpret_cast<std::add_pointer_t<size_t>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *Kites::RegisterModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kites::RegisterModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites13RegisterModelE_t>.strings))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int Kites::RegisterModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
