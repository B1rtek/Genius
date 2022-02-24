/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GeniusSettings
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelSettingsTitle;
    QHBoxLayout *horizontalLayout;
    QLabel *labelDictSetting;
    QComboBox *comboBoxDictSetting;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBoxDarkMode;
    QPushButton *buttonOk;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *GeniusSettings)
    {
        if (GeniusSettings->objectName().isEmpty())
            GeniusSettings->setObjectName(QString::fromUtf8("GeniusSettings"));
        GeniusSettings->resize(305, 176);
        verticalLayout = new QVBoxLayout(GeniusSettings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        labelSettingsTitle = new QLabel(GeniusSettings);
        labelSettingsTitle->setObjectName(QString::fromUtf8("labelSettingsTitle"));
        QFont font;
        font.setPointSize(14);
        labelSettingsTitle->setFont(font);
        labelSettingsTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelSettingsTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelDictSetting = new QLabel(GeniusSettings);
        labelDictSetting->setObjectName(QString::fromUtf8("labelDictSetting"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelDictSetting->sizePolicy().hasHeightForWidth());
        labelDictSetting->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(labelDictSetting);

        comboBoxDictSetting = new QComboBox(GeniusSettings);
        comboBoxDictSetting->setObjectName(QString::fromUtf8("comboBoxDictSetting"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxDictSetting->sizePolicy().hasHeightForWidth());
        comboBoxDictSetting->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(comboBoxDictSetting);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        checkBoxDarkMode = new QCheckBox(GeniusSettings);
        checkBoxDarkMode->setObjectName(QString::fromUtf8("checkBoxDarkMode"));

        horizontalLayout_2->addWidget(checkBoxDarkMode, 0, Qt::AlignHCenter);


        verticalLayout->addLayout(horizontalLayout_2);

        buttonOk = new QPushButton(GeniusSettings);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("checkbox");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        buttonOk->setIcon(icon);

        verticalLayout->addWidget(buttonOk, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(GeniusSettings);

        QMetaObject::connectSlotsByName(GeniusSettings);
    } // setupUi

    void retranslateUi(QDialog *GeniusSettings)
    {
        GeniusSettings->setWindowTitle(QCoreApplication::translate("GeniusSettings", "Settings", nullptr));
        labelSettingsTitle->setText(QCoreApplication::translate("GeniusSettings", "Settings", nullptr));
        labelDictSetting->setText(QCoreApplication::translate("GeniusSettings", "Default dictionary", nullptr));
        checkBoxDarkMode->setText(QCoreApplication::translate("GeniusSettings", "Dark mode", nullptr));
        buttonOk->setText(QCoreApplication::translate("GeniusSettings", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeniusSettings: public Ui_GeniusSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SETTINGS_H
