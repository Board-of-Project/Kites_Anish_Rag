/********************************************************************************
** Form generated from reading UI file 'processortab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSORTAB_H
#define UI_PROCESSORTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include "ui/processor_tab/circuit_view.h"

namespace Kites {

class Ui_ProcessorTab
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    CircuitView *graphicsView;
    QTableView *tableView;

    void setupUi(QWidget *Kites__ProcessorTab)
    {
        if (Kites__ProcessorTab->objectName().isEmpty())
            Kites__ProcessorTab->setObjectName("Kites__ProcessorTab");
        Kites__ProcessorTab->resize(792, 531);
        gridLayout = new QGridLayout(Kites__ProcessorTab);
        gridLayout->setObjectName("gridLayout");
        splitter = new QSplitter(Kites__ProcessorTab);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Vertical);
        graphicsView = new CircuitView(splitter);
        graphicsView->setObjectName("graphicsView");
        splitter->addWidget(graphicsView);
        tableView = new QTableView(splitter);
        tableView->setObjectName("tableView");
        splitter->addWidget(tableView);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Kites__ProcessorTab);

        QMetaObject::connectSlotsByName(Kites__ProcessorTab);
    } // setupUi

    void retranslateUi(QWidget *Kites__ProcessorTab)
    {
        Kites__ProcessorTab->setWindowTitle(QCoreApplication::translate("Kites::ProcessorTab", "Form", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class ProcessorTab: public Ui_ProcessorTab {};
} // namespace Ui
} // namespace Kites

#endif // UI_PROCESSORTAB_H
