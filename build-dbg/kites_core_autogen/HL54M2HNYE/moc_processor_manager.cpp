/****************************************************************************
** Meta object code from reading C++ file 'processor_manager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/processor/processor_manager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processor_manager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5Kites16ProcessorManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto Kites::ProcessorManager::qt_create_metaobjectdata<qt_meta_tag_ZN5Kites16ProcessorManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Kites::ProcessorManager",
        "processorClockedSignal",
        "",
        "ProcessorState",
        "processorState",
        "runFinishedSignal",
        "processorStateChangedSignal",
        "processorPausedAtBreakpointSignal",
        "runErrorSignal",
        "errorMessage",
        "sourceLine",
        "updateDisassemblySignal",
        "disassemblyText",
        "updateEditorHighlightSignal",
        "std::vector<std::pair<int,std::string>>",
        "editorLines",
        "disassemblyLines",
        "runSlot",
        "processorClockedSlot"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'processorClockedSignal'
        QtMocHelpers::SignalData<void(const ProcessorState &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'runFinishedSignal'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'processorStateChangedSignal'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'processorPausedAtBreakpointSignal'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'runErrorSignal'
        QtMocHelpers::SignalData<void(const QString &, int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 9 }, { QMetaType::Int, 10 },
        }}),
        // Signal 'updateDisassemblySignal'
        QtMocHelpers::SignalData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 12 },
        }}),
        // Signal 'updateEditorHighlightSignal'
        QtMocHelpers::SignalData<void(const std::vector<std::pair<int,std::string>> &, const std::vector<std::pair<int,std::string>> &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 14, 15 }, { 0x80000000 | 14, 16 },
        }}),
        // Slot 'runSlot'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'processorClockedSlot'
        QtMocHelpers::SlotData<void(const ProcessorState &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ProcessorManager, qt_meta_tag_ZN5Kites16ProcessorManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Kites::ProcessorManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites16ProcessorManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites16ProcessorManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5Kites16ProcessorManagerE_t>.metaTypes,
    nullptr
} };

void Kites::ProcessorManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ProcessorManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->processorClockedSignal((*reinterpret_cast<std::add_pointer_t<ProcessorState>>(_a[1]))); break;
        case 1: _t->runFinishedSignal(); break;
        case 2: _t->processorStateChangedSignal(); break;
        case 3: _t->processorPausedAtBreakpointSignal(); break;
        case 4: _t->runErrorSignal((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->updateDisassemblySignal((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->updateEditorHighlightSignal((*reinterpret_cast<std::add_pointer_t<std::vector<std::pair<int,std::string>>>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<std::vector<std::pair<int,std::string>>>>(_a[2]))); break;
        case 7: _t->runSlot(); break;
        case 8: _t->processorClockedSlot((*reinterpret_cast<std::add_pointer_t<ProcessorState>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)(const ProcessorState & )>(_a, &ProcessorManager::processorClockedSignal, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)()>(_a, &ProcessorManager::runFinishedSignal, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)()>(_a, &ProcessorManager::processorStateChangedSignal, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)()>(_a, &ProcessorManager::processorPausedAtBreakpointSignal, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)(const QString & , int )>(_a, &ProcessorManager::runErrorSignal, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)(const QString & )>(_a, &ProcessorManager::updateDisassemblySignal, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcessorManager::*)(const std::vector<std::pair<int,std::string>> & , const std::vector<std::pair<int,std::string>> & )>(_a, &ProcessorManager::updateEditorHighlightSignal, 6))
            return;
    }
}

const QMetaObject *Kites::ProcessorManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kites::ProcessorManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites16ProcessorManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Kites::ProcessorManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Kites::ProcessorManager::processorClockedSignal(const ProcessorState & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Kites::ProcessorManager::runFinishedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Kites::ProcessorManager::processorStateChangedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Kites::ProcessorManager::processorPausedAtBreakpointSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Kites::ProcessorManager::runErrorSignal(const QString & _t1, int _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void Kites::ProcessorManager::updateDisassemblySignal(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void Kites::ProcessorManager::updateEditorHighlightSignal(const std::vector<std::pair<int,std::string>> & _t1, const std::vector<std::pair<int,std::string>> & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1, _t2);
}
QT_WARNING_POP
