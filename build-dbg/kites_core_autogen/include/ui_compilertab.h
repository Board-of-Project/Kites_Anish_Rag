/********************************************************************************
** Form generated from reading UI file 'compilertab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPILERTAB_H
#define UI_COMPILERTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ui/compiler_tab/compiler_editor.h>
#include <ui/editor_tab/main_editor.h>

namespace Kites {

class Ui_CompilerTab
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *convertToAssemblyButton;
    QLabel *label_3;
    QLineEdit *compilerOptionslineEdit;
    CompilerEditor *inputTextEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QPushButton *copyToMainEditorButton;
    Editor *outputTextEdit;
    QPlainTextEdit *console;

    void setupUi(QWidget *Kites__CompilerTab)
    {
        if (Kites__CompilerTab->objectName().isEmpty())
            Kites__CompilerTab->setObjectName("Kites__CompilerTab");
        Kites__CompilerTab->resize(880, 473);
        gridLayout = new QGridLayout(Kites__CompilerTab);
        gridLayout->setObjectName("gridLayout");
        splitter_2 = new QSplitter(Kites__CompilerTab);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Orientation::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        convertToAssemblyButton = new QPushButton(layoutWidget);
        convertToAssemblyButton->setObjectName("convertToAssemblyButton");

        horizontalLayout->addWidget(convertToAssemblyButton);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        compilerOptionslineEdit = new QLineEdit(layoutWidget);
        compilerOptionslineEdit->setObjectName("compilerOptionslineEdit");

        horizontalLayout->addWidget(compilerOptionslineEdit);


        verticalLayout->addLayout(horizontalLayout);

        inputTextEdit = new CompilerEditor(layoutWidget);
        inputTextEdit->setObjectName("inputTextEdit");

        verticalLayout->addWidget(inputTextEdit);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        copyToMainEditorButton = new QPushButton(layoutWidget1);
        copyToMainEditorButton->setObjectName("copyToMainEditorButton");

        horizontalLayout_2->addWidget(copyToMainEditorButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        outputTextEdit = new Editor(layoutWidget1);
        outputTextEdit->setObjectName("outputTextEdit");

        verticalLayout_2->addWidget(outputTextEdit);

        splitter->addWidget(layoutWidget1);
        splitter_2->addWidget(splitter);
        console = new QPlainTextEdit(splitter_2);
        console->setObjectName("console");
        splitter_2->addWidget(console);

        gridLayout->addWidget(splitter_2, 0, 0, 1, 1);


        retranslateUi(Kites__CompilerTab);

        QMetaObject::connectSlotsByName(Kites__CompilerTab);
    } // setupUi

    void retranslateUi(QWidget *Kites__CompilerTab)
    {
        Kites__CompilerTab->setWindowTitle(QCoreApplication::translate("Kites::CompilerTab", "Form", nullptr));
        label->setText(QCoreApplication::translate("Kites::CompilerTab", "TextLabel", nullptr));
        convertToAssemblyButton->setText(QCoreApplication::translate("Kites::CompilerTab", "Compile", nullptr));
        label_3->setText(QCoreApplication::translate("Kites::CompilerTab", "Compiler options", nullptr));
        label_2->setText(QCoreApplication::translate("Kites::CompilerTab", "TextLabel", nullptr));
        copyToMainEditorButton->setText(QCoreApplication::translate("Kites::CompilerTab", "Copy to Clipboard", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class CompilerTab: public Ui_CompilerTab {};
} // namespace Ui
} // namespace Kites

#endif // UI_COMPILERTAB_H
