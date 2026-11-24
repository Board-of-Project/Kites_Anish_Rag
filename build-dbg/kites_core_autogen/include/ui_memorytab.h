/********************************************************************************
** Form generated from reading UI file 'memorytab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEMORYTAB_H
#define UI_MEMORYTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "ui/memory_tab/memory_table_view.h"

namespace Kites {

class Ui_MemoryTab
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QLabel *label;
    QLineEdit *searchBar;
    QPushButton *searchButton;
    MemoryTableView *memoryTableView;

    void setupUi(QWidget *Kites__MemoryTab)
    {
        if (Kites__MemoryTab->objectName().isEmpty())
            Kites__MemoryTab->setObjectName("Kites__MemoryTab");
        Kites__MemoryTab->resize(756, 466);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Kites__MemoryTab->sizePolicy().hasHeightForWidth());
        Kites__MemoryTab->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(Kites__MemoryTab);
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(Kites__MemoryTab);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 2, 1, 1);

        comboBox = new QComboBox(Kites__MemoryTab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        label = new QLabel(Kites__MemoryTab);
        label->setObjectName("label");

        gridLayout->addWidget(label, 2, 0, 1, 1);

        searchBar = new QLineEdit(Kites__MemoryTab);
        searchBar->setObjectName("searchBar");

        gridLayout->addWidget(searchBar, 2, 3, 1, 1);

        searchButton = new QPushButton(Kites__MemoryTab);
        searchButton->setObjectName("searchButton");

        gridLayout->addWidget(searchButton, 2, 4, 1, 1);

        memoryTableView = new MemoryTableView(Kites__MemoryTab);
        memoryTableView->setObjectName("memoryTableView");

        gridLayout->addWidget(memoryTableView, 0, 0, 1, 5);


        retranslateUi(Kites__MemoryTab);

        QMetaObject::connectSlotsByName(Kites__MemoryTab);
    } // setupUi

    void retranslateUi(QWidget *Kites__MemoryTab)
    {
        Kites__MemoryTab->setWindowTitle(QCoreApplication::translate("Kites::MemoryTab", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("Kites::MemoryTab", " Search Memory", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Kites::MemoryTab", "Hex", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Kites::MemoryTab", "Binary", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Kites::MemoryTab", "Decimal", nullptr));

        label->setText(QCoreApplication::translate("Kites::MemoryTab", "Display Type:", nullptr));
        searchButton->setText(QCoreApplication::translate("Kites::MemoryTab", "Search", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class MemoryTab: public Ui_MemoryTab {};
} // namespace Ui
} // namespace Kites

#endif // UI_MEMORYTAB_H
