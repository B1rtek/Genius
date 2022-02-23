/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GeniusHelp
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *buttonOk;

    void setupUi(QDialog *GeniusHelp)
    {
        if (GeniusHelp->objectName().isEmpty())
            GeniusHelp->setObjectName(QString::fromUtf8("GeniusHelp"));
        GeniusHelp->resize(400, 300);
        verticalLayout = new QVBoxLayout(GeniusHelp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(GeniusHelp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        buttonOk = new QPushButton(GeniusHelp);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
        buttonOk->setSizePolicy(sizePolicy);
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("checkbox")));
        buttonOk->setIcon(icon);

        verticalLayout->addWidget(buttonOk, 0, Qt::AlignHCenter);


        retranslateUi(GeniusHelp);

        QMetaObject::connectSlotsByName(GeniusHelp);
    } // setupUi

    void retranslateUi(QDialog *GeniusHelp)
    {
        GeniusHelp->setWindowTitle(QCoreApplication::translate("GeniusHelp", "Help", nullptr));
        label->setText(QCoreApplication::translate("GeniusHelp", "To enter a word, simply type on your keyboard or select a word from one of the lists. Mark a letter as yellow with a left mouse button click, or as green with a right click. To enter your word, press \"Confirm\", or if you made a mistake, click \"Reset\".", nullptr));
        buttonOk->setText(QCoreApplication::translate("GeniusHelp", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeniusHelp: public Ui_GeniusHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
