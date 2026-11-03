/********************************************************************************
** Form generated from reading UI file 'cachetab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CACHETAB_H
#define UI_CACHETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ui/cache_tab/cacheconfigwidget.h>

namespace Kites {

class Ui_CacheTab
{
public:
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QSplitter *splitter_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    CacheConfigWidget *InstructionConfig;
    QSpacerItem *verticalSpacer_3;
    QTableView *InstructiontableView;
    QWidget *L1Tab;
    QGridLayout *gridLayout_2;
    QSplitter *splitter_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    CacheConfigWidget *L1Config;
    QSpacerItem *verticalSpacer;
    QTableView *L1tableView;
    QWidget *L2Tab;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    CacheConfigWidget *L2Config;
    QSpacerItem *verticalSpacer_2;
    QTableView *L2tableView;

    void setupUi(QWidget *Kites__CacheTab)
    {
        if (Kites__CacheTab->objectName().isEmpty())
            Kites__CacheTab->setObjectName("Kites__CacheTab");
        Kites__CacheTab->resize(824, 549);
        gridLayout_4 = new QGridLayout(Kites__CacheTab);
        gridLayout_4->setObjectName("gridLayout_4");
        tabWidget = new QTabWidget(Kites__CacheTab);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        splitter_4 = new QSplitter(tab);
        splitter_4->setObjectName("splitter_4");
        splitter_4->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter_4);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        InstructionConfig = new CacheConfigWidget(layoutWidget);
        InstructionConfig->setObjectName("InstructionConfig");

        verticalLayout_4->addWidget(InstructionConfig);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        splitter_4->addWidget(layoutWidget);
        InstructiontableView = new QTableView(splitter_4);
        InstructiontableView->setObjectName("InstructiontableView");
        splitter_4->addWidget(InstructiontableView);

        gridLayout_3->addWidget(splitter_4, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        L1Tab = new QWidget();
        L1Tab->setObjectName("L1Tab");
        gridLayout_2 = new QGridLayout(L1Tab);
        gridLayout_2->setObjectName("gridLayout_2");
        splitter_2 = new QSplitter(L1Tab);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        L1Config = new CacheConfigWidget(layoutWidget1);
        L1Config->setObjectName("L1Config");

        verticalLayout_2->addWidget(L1Config);

        verticalSpacer = new QSpacerItem(20, 464, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        splitter_2->addWidget(layoutWidget1);
        L1tableView = new QTableView(splitter_2);
        L1tableView->setObjectName("L1tableView");
        splitter_2->addWidget(L1tableView);

        gridLayout_2->addWidget(splitter_2, 0, 0, 1, 1);

        tabWidget->addTab(L1Tab, QString());
        L2Tab = new QWidget();
        L2Tab->setObjectName("L2Tab");
        gridLayout = new QGridLayout(L2Tab);
        gridLayout->setObjectName("gridLayout");
        splitter_3 = new QSplitter(L2Tab);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget2 = new QWidget(splitter_3);
        layoutWidget2->setObjectName("layoutWidget2");
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        L2Config = new CacheConfigWidget(layoutWidget2);
        L2Config->setObjectName("L2Config");

        verticalLayout_3->addWidget(L2Config);

        verticalSpacer_2 = new QSpacerItem(20, 464, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        splitter_3->addWidget(layoutWidget2);
        L2tableView = new QTableView(splitter_3);
        L2tableView->setObjectName("L2tableView");
        splitter_3->addWidget(L2tableView);

        gridLayout->addWidget(splitter_3, 0, 0, 1, 1);

        tabWidget->addTab(L2Tab, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(Kites__CacheTab);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Kites__CacheTab);
    } // setupUi

    void retranslateUi(QWidget *Kites__CacheTab)
    {
        Kites__CacheTab->setWindowTitle(QCoreApplication::translate("Kites::CacheTab", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Kites::CacheTab", "Page", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(L1Tab), QCoreApplication::translate("Kites::CacheTab", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(L2Tab), QCoreApplication::translate("Kites::CacheTab", "Tab 2", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class CacheTab: public Ui_CacheTab {};
} // namespace Ui
} // namespace Kites

#endif // UI_CACHETAB_H
