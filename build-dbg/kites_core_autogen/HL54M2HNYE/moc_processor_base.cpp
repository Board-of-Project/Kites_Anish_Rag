/****************************************************************************
** Meta object code from reading C++ file 'processor_base.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/processor/processor_base.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processor_base.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5Kites13ProcessorBaseE_t {};
} // unnamed namespace

template <> constexpr inline auto Kites::ProcessorBase::qt_create_metaobjectdata<qt_meta_tag_ZN5Kites13ProcessorBaseE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Kites::ProcessorBase",
        "processorClockedSignal",
        "",
        "ProcessorState",
        "processorState",
        "updateCircuitStateSignal",
        "wireList",
        "processorPausedAtBreakpointSignal"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'processorClockedSignal'
        QtMocHelpers::SignalData<void(const ProcessorState &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'updateCircuitStateSignal'
        QtMocHelpers::SignalData<void(const QList<QString> &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QStringList, 6 },
        }}),
        // Signal 'processorPausedAtBreakpointSignal'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ProcessorBase, qt_meta_tag_ZN5Kites13ProcessorBaseE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Kites::ProcessorBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites13ProcessorBaseE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites13ProcessorBaseE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5Kites13ProcessorBaseE_t>.metaTypes,
    nullptr
} };

void Kites::ProcessorBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ProcessorBase *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->processorClockedSignal((*reinterpret_cast<std::add_pointer_t<ProcessorState>>(_a[1]))); break;
        case 1: _t->updateCircuitStateSignal((*reinterpret_cast<std::add_pointer_t<QList<QString>>>(_a[1]))); break;
        case 2: _t->processorPausedAtBreakpointSignal(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ProcessorBase::*)(const ProcessorState & )>(_a, &ProcessorBase::processorClockedSignal, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorBase::*)(const QList<QString> & )>(_a, &ProcessorBase::updateCircuitStateSignal, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorBase::*)()>(_a, &ProcessorBase::processorPausedAtBreakpointSignal, 2))
            return;
    }
}

const QMetaObject *Kites::ProcessorBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kites::ProcessorBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites13ProcessorBaseE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Kites::ProcessorBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Kites::ProcessorBase::processorClockedSignal(const ProcessorState & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Kites::ProcessorBase::updateCircuitStateSignal(const QList<QString> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void Kites::ProcessorBase::processorPausedAtBreakpointSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
