/********************************************************************************
** Form generated from reading UI file 'settings_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_DIALOG_H
#define UI_SETTINGS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

namespace Kites {

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *settingList;
    QStackedWidget *settingPages;
    QWidget *page;
    QWidget *page_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Kites__SettingsDialog)
    {
        if (Kites__SettingsDialog->objectName().isEmpty())
            Kites__SettingsDialog->setObjectName("Kites__SettingsDialog");
        Kites__SettingsDialog->resize(781, 367);
        gridLayout = new QGridLayout(Kites__SettingsDialog);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        settingList = new QListWidget(Kites__SettingsDialog);
        settingList->setObjectName("settingList");

        horizontalLayout->addWidget(settingList);

        settingPages = new QStackedWidget(Kites__SettingsDialog);
        settingPages->setObjectName("settingPages");
        page = new QWidget();
        page->setObjectName("page");
        settingPages->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        settingPages->addWidget(page_2);

        horizontalLayout->addWidget(settingPages);

        horizontalLayout->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Kites__SettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(Kites__SettingsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Kites__SettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Kites__SettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Kites__SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *Kites__SettingsDialog)
    {
        Kites__SettingsDialog->setWindowTitle(QCoreApplication::translate("Kites::SettingsDialog", "Dialog", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui
} // namespace Kites

#endif // UI_SETTINGS_DIALOG_H
