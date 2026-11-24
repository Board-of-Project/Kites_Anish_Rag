/********************************************************************************
** Form generated from reading UI file 'addpseudo_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPSEUDO_DIALOG_H
#define UI_ADDPSEUDO_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Kites {

class Ui_AddPseudoDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPlainTextEdit *pseudoInstructionTextEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QPlainTextEdit *expansionTextEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveButton;

    void setupUi(QDialog *Kites__AddPseudoDialog)
    {
        if (Kites__AddPseudoDialog->objectName().isEmpty())
            Kites__AddPseudoDialog->setObjectName("Kites__AddPseudoDialog");
        Kites__AddPseudoDialog->resize(715, 331);
        verticalLayout_3 = new QVBoxLayout(Kites__AddPseudoDialog);
        verticalLayout_3->setObjectName("verticalLayout_3");
        splitter = new QSplitter(Kites__AddPseudoDialog);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        pseudoInstructionTextEdit = new QPlainTextEdit(layoutWidget);
        pseudoInstructionTextEdit->setObjectName("pseudoInstructionTextEdit");

        verticalLayout_2->addWidget(pseudoInstructionTextEdit);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        expansionTextEdit = new QPlainTextEdit(layoutWidget1);
        expansionTextEdit->setObjectName("expansionTextEdit");

        verticalLayout->addWidget(expansionTextEdit);

        splitter->addWidget(layoutWidget1);

        verticalLayout_3->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        saveButton = new QPushButton(Kites__AddPseudoDialog);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(Kites__AddPseudoDialog);

        QMetaObject::connectSlotsByName(Kites__AddPseudoDialog);
    } // setupUi

    void retranslateUi(QDialog *Kites__AddPseudoDialog)
    {
        Kites__AddPseudoDialog->setWindowTitle(QCoreApplication::translate("Kites::AddPseudoDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Kites::AddPseudoDialog", "Pseudo Instruction", nullptr));
        label_2->setText(QCoreApplication::translate("Kites::AddPseudoDialog", "Expansion", nullptr));
        saveButton->setText(QCoreApplication::translate("Kites::AddPseudoDialog", "Save", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class AddPseudoDialog: public Ui_AddPseudoDialog {};
} // namespace Ui
} // namespace Kites

#endif // UI_ADDPSEUDO_DIALOG_H
