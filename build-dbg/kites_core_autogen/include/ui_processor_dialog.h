/********************************************************************************
** Form generated from reading UI file 'processor_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESSOR_DIALOG_H
#define UI_PROCESSOR_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

namespace Kites {

class Ui_ProcessorDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QTreeWidget *treeWidget;

    void setupUi(QDialog *Kites__ProcessorDialog)
    {
        if (Kites__ProcessorDialog->objectName().isEmpty())
            Kites__ProcessorDialog->setObjectName("Kites__ProcessorDialog");
        Kites__ProcessorDialog->resize(400, 300);
        gridLayout = new QGridLayout(Kites__ProcessorDialog);
        gridLayout->setObjectName("gridLayout");
        buttonBox = new QDialogButtonBox(Kites__ProcessorDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        treeWidget = new QTreeWidget(Kites__ProcessorDialog);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        treeWidget->setObjectName("treeWidget");

        gridLayout->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(Kites__ProcessorDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Kites__ProcessorDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Kites__ProcessorDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Kites__ProcessorDialog);
    } // setupUi

    void retranslateUi(QDialog *Kites__ProcessorDialog)
    {
        Kites__ProcessorDialog->setWindowTitle(QCoreApplication::translate("Kites::ProcessorDialog", "Dialog", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Kites::ProcessorDialog", "Processor Type", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("Kites::ProcessorDialog", "Single cycle processor", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("Kites::ProcessorDialog", "5 statge Processor w/o hazard detection w/o forwarding", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("Kites::ProcessorDialog", "5 statge Processor w/ hazard detection w/o forwarding", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem4->setText(0, QCoreApplication::translate("Kites::ProcessorDialog", "5 statge Processor w/o hazard detection w/ forwarding", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem5->setText(0, QCoreApplication::translate("Kites::ProcessorDialog", "5 statge Processor w/ hazard detection w/ forwarding", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class ProcessorDialog: public Ui_ProcessorDialog {};
} // namespace Ui
} // namespace Kites

#endif // UI_PROCESSOR_DIALOG_H
