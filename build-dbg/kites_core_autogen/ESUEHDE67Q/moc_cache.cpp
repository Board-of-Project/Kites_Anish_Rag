/****************************************************************************
** Meta object code from reading C++ file 'cache.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/processor/cache/cache.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cache.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5Kites5CacheE_t {};
} // unnamed namespace

template <> constexpr inline auto Kites::Cache::qt_create_metaobjectdata<qt_meta_tag_ZN5Kites5CacheE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Kites::Cache",
        "cacheMissSignal",
        "",
        "uint64_t",
        "address",
        "cacheHitSignal",
        "cacheLineUpdatedSignal",
        "cacheReconfiguredSignal",
        "CacheConfig",
        "newConfig",
        "cacheStatsUpdatedSignal",
        "CacheStats",
        "newStats",
        "customPolicyScriptLoadedSignal",
        "success",
        "std::string",
        "errorMessage",
        "loadCustomPolicyScript",
        "path"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'cacheMissSignal'
        QtMocHelpers::SignalData<void(uint64_t)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'cacheHitSignal'
        QtMocHelpers::SignalData<void(uint64_t)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'cacheLineUpdatedSignal'
        QtMocHelpers::SignalData<void(uint64_t)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'cacheReconfiguredSignal'
        QtMocHelpers::SignalData<void(CacheConfig)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Signal 'cacheStatsUpdatedSignal'
        QtMocHelpers::SignalData<void(CacheStats)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Signal 'customPolicyScriptLoadedSignal'
        QtMocHelpers::SignalData<void(bool, const std::string &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 14 }, { 0x80000000 | 15, 16 },
        }}),
        // Signal 'customPolicyScriptLoadedSignal'
        QtMocHelpers::SignalData<void(bool)>(13, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::Bool, 14 },
        }}),
        // Slot 'loadCustomPolicyScript'
        QtMocHelpers::SlotData<void(const std::string &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 15, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Cache, qt_meta_tag_ZN5Kites5CacheE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Kites::Cache::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites5CacheE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites5CacheE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5Kites5CacheE_t>.metaTypes,
    nullptr
} };

void Kites::Cache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Cache *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->cacheMissSignal((*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[1]))); break;
        case 1: _t->cacheHitSignal((*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[1]))); break;
        case 2: _t->cacheLineUpdatedSignal((*reinterpret_cast<std::add_pointer_t<uint64_t>>(_a[1]))); break;
        case 3: _t->cacheReconfiguredSignal((*reinterpret_cast<std::add_pointer_t<CacheConfig>>(_a[1]))); break;
        case 4: _t->cacheStatsUpdatedSignal((*reinterpret_cast<std::add_pointer_t<CacheStats>>(_a[1]))); break;
        case 5: _t->customPolicyScriptLoadedSignal((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<std::string>>(_a[2]))); break;
        case 6: _t->customPolicyScriptLoadedSignal((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->loadCustomPolicyScript((*reinterpret_cast<std::add_pointer_t<std::string>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Cache::*)(uint64_t )>(_a, &Cache::cacheMissSignal, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cache::*)(uint64_t )>(_a, &Cache::cacheHitSignal, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cache::*)(uint64_t )>(_a, &Cache::cacheLineUpdatedSignal, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cache::*)(CacheConfig )>(_a, &Cache::cacheReconfiguredSignal, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cache::*)(CacheStats )>(_a, &Cache::cacheStatsUpdatedSignal, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cache::*)(bool , const std::string & )>(_a, &Cache::customPolicyScriptLoadedSignal, 5))
            return;
    }
}

const QMetaObject *Kites::Cache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kites::Cache::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites5CacheE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "MemoryDevice"))
        return static_cast< MemoryDevice*>(this);
    return QObject::qt_metacast(_clname);
}

int Kites::Cache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Kites::Cache::cacheMissSignal(uint64_t _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Kites::Cache::cacheHitSignal(uint64_t _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Kites::Cache::cacheLineUpdatedSignal(uint64_t _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Kites::Cache::cacheReconfiguredSignal(CacheConfig _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void Kites::Cache::cacheStatsUpdatedSignal(CacheStats _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Kites::Cache::customPolicyScriptLoadedSignal(bool _t1, const std::string & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1, _t2);
}
QT_WARNING_POP
