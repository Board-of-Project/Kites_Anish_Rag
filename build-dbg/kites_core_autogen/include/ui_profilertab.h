/********************************************************************************
** Form generated from reading UI file 'profilertab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILERTAB_H
#define UI_PROFILERTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ui/profiler_tab/profiler_editor.h"

namespace Kites {

class Ui_ProfilerTab
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    ProfilerEditor *plainTextEdit;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QTableView *instructionTypeCountTableView;

    void setupUi(QWidget *Kites__ProfilerTab)
    {
        if (Kites__ProfilerTab->objectName().isEmpty())
            Kites__ProfilerTab->setObjectName("Kites__ProfilerTab");
        Kites__ProfilerTab->resize(778, 453);
        gridLayout = new QGridLayout(Kites__ProfilerTab);
        gridLayout->setObjectName("gridLayout");
        splitter = new QSplitter(Kites__ProfilerTab);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        plainTextEdit = new ProfilerEditor(splitter);
        plainTextEdit->setObjectName("plainTextEdit");
        splitter->addWidget(plainTextEdit);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        instructionTypeCountTableView = new QTableView(layoutWidget);
        instructionTypeCountTableView->setObjectName("instructionTypeCountTableView");

        verticalLayout_3->addWidget(instructionTypeCountTableView);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Kites__ProfilerTab);

        QMetaObject::connectSlotsByName(Kites__ProfilerTab);
    } // setupUi

    void retranslateUi(QWidget *Kites__ProfilerTab)
    {
        Kites__ProfilerTab->setWindowTitle(QCoreApplication::translate("Kites::ProfilerTab", "Form", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class ProfilerTab: public Ui_ProfilerTab {};
} // namespace Ui
} // namespace Kites

#endif // UI_PROFILERTAB_H
