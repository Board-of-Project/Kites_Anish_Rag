/********************************************************************************
** Form generated from reading UI file 'registercontainer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERCONTAINER_H
#define UI_REGISTERCONTAINER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

namespace Kites {

class Ui_RegisterContainer
{
public:
    QGridLayout *gridLayout;
    QComboBox *displayType;
    QLabel *label;
    QWidget *sectionsContainer;

    void setupUi(QWidget *Kites__RegisterContainer)
    {
        if (Kites__RegisterContainer->objectName().isEmpty())
            Kites__RegisterContainer->setObjectName("Kites__RegisterContainer");
        Kites__RegisterContainer->resize(553, 612);
        gridLayout = new QGridLayout(Kites__RegisterContainer);
        gridLayout->setObjectName("gridLayout");
        displayType = new QComboBox(Kites__RegisterContainer);
        displayType->addItem(QString());
        displayType->addItem(QString());
        displayType->addItem(QString());
        displayType->setObjectName("displayType");

        gridLayout->addWidget(displayType, 1, 1, 1, 1);

        label = new QLabel(Kites__RegisterContainer);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        sectionsContainer = new QWidget(Kites__RegisterContainer);
        sectionsContainer->setObjectName("sectionsContainer");

        gridLayout->addWidget(sectionsContainer, 0, 0, 1, 2);


        retranslateUi(Kites__RegisterContainer);

        QMetaObject::connectSlotsByName(Kites__RegisterContainer);
    } // setupUi

    void retranslateUi(QWidget *Kites__RegisterContainer)
    {
        Kites__RegisterContainer->setWindowTitle(QCoreApplication::translate("Kites::RegisterContainer", "Form", nullptr));
        displayType->setItemText(0, QCoreApplication::translate("Kites::RegisterContainer", "Binary", nullptr));
        displayType->setItemText(1, QCoreApplication::translate("Kites::RegisterContainer", "Hexadecimal", nullptr));
        displayType->setItemText(2, QCoreApplication::translate("Kites::RegisterContainer", "Decimal/Float", nullptr));

        label->setText(QCoreApplication::translate("Kites::RegisterContainer", "Display Type:", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class RegisterContainer: public Ui_RegisterContainer {};
} // namespace Ui
} // namespace Kites

#endif // UI_REGISTERCONTAINER_H
