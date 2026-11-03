/********************************************************************************
** Form generated from reading UI file 'editortab.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITORTAB_H
#define UI_EDITORTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ui/editor_tab/main_editor.h>
#include "ui/editor_tab/disassembly_editor.h"

namespace Kites {

class Ui_EditorTab
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QRadioButton *editorViewButton;
    QRadioButton *expandedViewButton;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    Editor *assemblyTextEdit;
    QWidget *page_2;
    QVBoxLayout *verticalLayout;
    Editor *expandedTextEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    DisassemblyEditor *disassemblyTextEdit;

    void setupUi(QWidget *Kites__EditorTab)
    {
        if (Kites__EditorTab->objectName().isEmpty())
            Kites__EditorTab->setObjectName("Kites__EditorTab");
        Kites__EditorTab->resize(865, 496);
        gridLayout = new QGridLayout(Kites__EditorTab);
        gridLayout->setObjectName("gridLayout");
        splitter = new QSplitter(Kites__EditorTab);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        editorViewButton = new QRadioButton(layoutWidget);
        editorViewButton->setObjectName("editorViewButton");

        horizontalLayout->addWidget(editorViewButton);

        expandedViewButton = new QRadioButton(layoutWidget);
        expandedViewButton->setObjectName("expandedViewButton");

        horizontalLayout->addWidget(expandedViewButton);


        verticalLayout_4->addLayout(horizontalLayout);

        stackedWidget = new QStackedWidget(layoutWidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        assemblyTextEdit = new Editor(page);
        assemblyTextEdit->setObjectName("assemblyTextEdit");

        verticalLayout_3->addWidget(assemblyTextEdit);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout = new QVBoxLayout(page_2);
        verticalLayout->setObjectName("verticalLayout");
        expandedTextEdit = new Editor(page_2);
        expandedTextEdit->setObjectName("expandedTextEdit");

        verticalLayout->addWidget(expandedTextEdit);

        stackedWidget->addWidget(page_2);

        verticalLayout_4->addWidget(stackedWidget);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        disassemblyTextEdit = new DisassemblyEditor(layoutWidget1);
        disassemblyTextEdit->setObjectName("disassemblyTextEdit");

        verticalLayout_2->addWidget(disassemblyTextEdit);

        splitter->addWidget(layoutWidget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Kites__EditorTab);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Kites__EditorTab);
    } // setupUi

    void retranslateUi(QWidget *Kites__EditorTab)
    {
        Kites__EditorTab->setWindowTitle(QCoreApplication::translate("Kites::EditorTab", "Form", nullptr));
        label->setText(QCoreApplication::translate("Kites::EditorTab", "Input", nullptr));
        editorViewButton->setText(QCoreApplication::translate("Kites::EditorTab", "Editor", nullptr));
        expandedViewButton->setText(QCoreApplication::translate("Kites::EditorTab", "Expanded", nullptr));
        label_2->setText(QCoreApplication::translate("Kites::EditorTab", "Output", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class EditorTab: public Ui_EditorTab {};
} // namespace Ui
} // namespace Kites

#endif // UI_EDITORTAB_H
