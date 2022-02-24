/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef HELP_H
#define HELP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GeniusHelp
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *labelTitle;
    QLabel *label;
    QLabel *labelGithubLink;
    QPushButton *buttonOk;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *GeniusHelp)
    {
        if (GeniusHelp->objectName().isEmpty())
            GeniusHelp->setObjectName(QString::fromUtf8("GeniusHelp"));
        GeniusHelp->resize(400, 300);
        verticalLayout = new QVBoxLayout(GeniusHelp);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        labelTitle = new QLabel(GeniusHelp);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QFont font;
        font.setPointSize(14);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        label = new QLabel(GeniusHelp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignJustify|Qt::AlignTop);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        labelGithubLink = new QLabel(GeniusHelp);
        labelGithubLink->setObjectName(QString::fromUtf8("labelGithubLink"));
        labelGithubLink->setTextFormat(Qt::MarkdownText);
        labelGithubLink->setWordWrap(true);
        labelGithubLink->setOpenExternalLinks(true);

        verticalLayout->addWidget(labelGithubLink);

        buttonOk = new QPushButton(GeniusHelp);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonOk->sizePolicy().hasHeightForWidth());
        buttonOk->setSizePolicy(sizePolicy);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("checkbox");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        buttonOk->setIcon(icon);

        verticalLayout->addWidget(buttonOk, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(GeniusHelp);

        QMetaObject::connectSlotsByName(GeniusHelp);
    } // setupUi

    void retranslateUi(QDialog *GeniusHelp)
    {
        GeniusHelp->setWindowTitle(QCoreApplication::translate("GeniusHelp", "Help", nullptr));
        labelTitle->setText(QCoreApplication::translate("GeniusHelp", "Help", nullptr));
        label->setText(QCoreApplication::translate("GeniusHelp", "To enter a word, simply type on your keyboard or select a word from one of the lists. Mark a letter as yellow with a left mouse button click, or as green with a right click. To enter your word, press \"Confirm\", or if you made a mistake, click \"Reset\".", nullptr));
        labelGithubLink->setText(QCoreApplication::translate("GeniusHelp", "For a more detailed description, go to the [project's github page](https://github.com/B1rtek/Genius)", nullptr));
        buttonOk->setText(QCoreApplication::translate("GeniusHelp", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GeniusHelp: public Ui_GeniusHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // HELP_H
