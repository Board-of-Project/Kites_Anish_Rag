/****************************************************************************
** Meta object code from reading C++ file 'profilertab.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ui/profiler_tab/profilertab.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profilertab.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5Kites11ProfilerTabE_t {};
} // unnamed namespace

template <> constexpr inline auto Kites::ProfilerTab::qt_create_metaobjectdata<qt_meta_tag_ZN5Kites11ProfilerTabE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Kites::ProfilerTab",
        "setSourceText",
        "",
        "sourceText",
        "updateLineExecutionCount",
        "std::map<int,int>",
        "lineExecutionCounts",
        "updateLineInstructionType",
        "std::map<int,std::string>",
        "lineInstructionTypes",
        "updateStatistics",
        "std::map<std::string,int>",
        "statistics",
        "resetProfilerView"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'setSourceText'
        QtMocHelpers::SlotData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'updateLineExecutionCount'
        QtMocHelpers::SlotData<void(const std::map<int,int> &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'updateLineInstructionType'
        QtMocHelpers::SlotData<void(const std::map<int,std::string> &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'updateStatistics'
        QtMocHelpers::SlotData<void(const std::map<std::string,int> &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 11, 12 },
        }}),
        // Slot 'resetProfilerView'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ProfilerTab, qt_meta_tag_ZN5Kites11ProfilerTabE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Kites::ProfilerTab::staticMetaObject = { {
    QMetaObject::SuperData::link<KitesTab::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites11ProfilerTabE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites11ProfilerTabE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5Kites11ProfilerTabE_t>.metaTypes,
    nullptr
} };

void Kites::ProfilerTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ProfilerTab *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->setSourceText((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->updateLineExecutionCount((*reinterpret_cast<std::add_pointer_t<std::map<int,int>>>(_a[1]))); break;
        case 2: _t->updateLineInstructionType((*reinterpret_cast<std::add_pointer_t<std::map<int,std::string>>>(_a[1]))); break;
        case 3: _t->updateStatistics((*reinterpret_cast<std::add_pointer_t<std::map<std::string,int>>>(_a[1]))); break;
        case 4: _t->resetProfilerView(); break;
        default: ;
        }
    }
}

const QMetaObject *Kites::ProfilerTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Kites::ProfilerTab::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5Kites11ProfilerTabE_t>.strings))
        return static_cast<void*>(this);
    return KitesTab::qt_metacast(_clname);
}

int Kites::ProfilerTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KitesTab::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
