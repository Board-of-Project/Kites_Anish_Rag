/********************************************************************************
** Form generated from reading UI file 'cacheconfigwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CACHECONFIGWIDGET_H
#define UI_CACHECONFIGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

namespace Kites {

class Ui_CacheConfigWidget
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QComboBox *writeMissComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *writeHitComboBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QComboBox *repPolComboBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *linesSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *waysSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *wordsSpinBox;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *customPolicyScriptlineEdit;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QLineEdit *sizeLineEdit;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QLineEdit *hitsLineEdit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QLineEdit *missesLineEdit;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_7;
    QLineEdit *hitrateLineEdit;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QLineEdit *writeBackLineEdit;

    void setupUi(QWidget *Kites__CacheConfigWidget)
    {
        if (Kites__CacheConfigWidget->objectName().isEmpty())
            Kites__CacheConfigWidget->setObjectName("Kites__CacheConfigWidget");
        Kites__CacheConfigWidget->resize(404, 413);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Kites__CacheConfigWidget->sizePolicy().hasHeightForWidth());
        Kites__CacheConfigWidget->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(Kites__CacheConfigWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        groupBox = new QGroupBox(Kites__CacheConfigWidget);
        groupBox->setObjectName("groupBox");
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        horizontalLayout_4->addWidget(label_6);

        writeMissComboBox = new QComboBox(groupBox);
        writeMissComboBox->addItem(QString());
        writeMissComboBox->addItem(QString());
        writeMissComboBox->setObjectName("writeMissComboBox");

        horizontalLayout_4->addWidget(writeMissComboBox);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        horizontalLayout_5->addWidget(label_5);

        writeHitComboBox = new QComboBox(groupBox);
        writeHitComboBox->addItem(QString());
        writeHitComboBox->addItem(QString());
        writeHitComboBox->setObjectName("writeHitComboBox");

        horizontalLayout_5->addWidget(writeHitComboBox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        repPolComboBox = new QComboBox(groupBox);
        repPolComboBox->addItem(QString());
        repPolComboBox->addItem(QString());
        repPolComboBox->addItem(QString());
        repPolComboBox->setObjectName("repPolComboBox");

        horizontalLayout_6->addWidget(repPolComboBox);


        verticalLayout_3->addLayout(horizontalLayout_6);


        gridLayout->addLayout(verticalLayout_3, 1, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        linesSpinBox = new QSpinBox(groupBox);
        linesSpinBox->setObjectName("linesSpinBox");

        horizontalLayout->addWidget(linesSpinBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        waysSpinBox = new QSpinBox(groupBox);
        waysSpinBox->setObjectName("waysSpinBox");

        horizontalLayout_2->addWidget(waysSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        wordsSpinBox = new QSpinBox(groupBox);
        wordsSpinBox->setObjectName("wordsSpinBox");

        horizontalLayout_3->addWidget(wordsSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(Kites__CacheConfigWidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        customPolicyScriptlineEdit = new QLineEdit(groupBox_2);
        customPolicyScriptlineEdit->setObjectName("customPolicyScriptlineEdit");

        horizontalLayout_7->addWidget(customPolicyScriptlineEdit);


        gridLayout_2->addLayout(horizontalLayout_7, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(Kites__CacheConfigWidget);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName("label_9");

        horizontalLayout_8->addWidget(label_9);

        sizeLineEdit = new QLineEdit(groupBox_3);
        sizeLineEdit->setObjectName("sizeLineEdit");

        horizontalLayout_8->addWidget(sizeLineEdit);


        gridLayout_4->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName("label_8");

        horizontalLayout_11->addWidget(label_8);

        hitsLineEdit = new QLineEdit(groupBox_3);
        hitsLineEdit->setObjectName("hitsLineEdit");

        horizontalLayout_11->addWidget(hitsLineEdit);


        gridLayout_4->addLayout(horizontalLayout_11, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName("label_10");

        horizontalLayout_10->addWidget(label_10);

        missesLineEdit = new QLineEdit(groupBox_3);
        missesLineEdit->setObjectName("missesLineEdit");

        horizontalLayout_10->addWidget(missesLineEdit);


        gridLayout_4->addLayout(horizontalLayout_10, 1, 1, 2, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName("label_7");

        horizontalLayout_12->addWidget(label_7);

        hitrateLineEdit = new QLineEdit(groupBox_3);
        hitrateLineEdit->setObjectName("hitrateLineEdit");

        horizontalLayout_12->addWidget(hitrateLineEdit);


        gridLayout_4->addLayout(horizontalLayout_12, 2, 0, 2, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName("label_11");

        horizontalLayout_9->addWidget(label_11);

        writeBackLineEdit = new QLineEdit(groupBox_3);
        writeBackLineEdit->setObjectName("writeBackLineEdit");

        horizontalLayout_9->addWidget(writeBackLineEdit);


        gridLayout_4->addLayout(horizontalLayout_9, 3, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 2, 0, 1, 1);


        retranslateUi(Kites__CacheConfigWidget);

        QMetaObject::connectSlotsByName(Kites__CacheConfigWidget);
    } // setupUi

    void retranslateUi(QWidget *Kites__CacheConfigWidget)
    {
        Kites__CacheConfigWidget->setWindowTitle(QCoreApplication::translate("Kites::CacheConfigWidget", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Kites::CacheConfigWidget", "Cache Configurations", nullptr));
        label_6->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Write miss", nullptr));
        writeMissComboBox->setItemText(0, QCoreApplication::translate("Kites::CacheConfigWidget", "Write Allocate", nullptr));
        writeMissComboBox->setItemText(1, QCoreApplication::translate("Kites::CacheConfigWidget", "Write No Allocate", nullptr));

        label_5->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Write hit", nullptr));
        writeHitComboBox->setItemText(0, QCoreApplication::translate("Kites::CacheConfigWidget", "Write Back", nullptr));
        writeHitComboBox->setItemText(1, QCoreApplication::translate("Kites::CacheConfigWidget", "Write Through", nullptr));

        label_4->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Replacement Policy", nullptr));
        repPolComboBox->setItemText(0, QCoreApplication::translate("Kites::CacheConfigWidget", "LRU", nullptr));
        repPolComboBox->setItemText(1, QCoreApplication::translate("Kites::CacheConfigWidget", "FIFO", nullptr));
        repPolComboBox->setItemText(2, QCoreApplication::translate("Kites::CacheConfigWidget", "Custom", nullptr));

        label->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "2^n Lines", nullptr));
        label_2->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "2^n Ways", nullptr));
        label_3->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "2^n words/line", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Kites::CacheConfigWidget", "Custom Policy", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Kites::CacheConfigWidget", "Statistics", nullptr));
        label_9->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Size in Bits:", nullptr));
        label_8->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Hits:", nullptr));
        label_10->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Misses:", nullptr));
        label_7->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Hit rate:", nullptr));
        label_11->setText(QCoreApplication::translate("Kites::CacheConfigWidget", "Write backs:", nullptr));
    } // retranslateUi

};

} // namespace Kites

namespace Kites {
namespace Ui {
    class CacheConfigWidget: public Ui_CacheConfigWidget {};
} // namespace Ui
} // namespace Kites

#endif // UI_CACHECONFIGWIDGET_H
