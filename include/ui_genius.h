/********************************************************************************
** Form generated from reading UI file 'genius.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENIUS_H
#define UI_GENIUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Genius
{
public:
    QAction *actionHelp;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelGenius;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelWordLength;
    QSlider *sliderWordLength;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLetters;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *buttonConfirm;
    QPushButton *buttonReset;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelMatchingWords;
    QPushButton *buttonMatching;
    QListWidget *listMatching;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelSuggestedWords;
    QPushButton *buttonSuggested;
    QListWidget *listSuggested;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Genius)
    {
        if (Genius->objectName().isEmpty())
            Genius->setObjectName(QString::fromUtf8("Genius"));
        Genius->resize(800, 543);
        actionHelp = new QAction(Genius);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("help")));
        actionHelp->setIcon(icon);
        centralwidget = new QWidget(Genius);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labelGenius = new QLabel(centralwidget);
        labelGenius->setObjectName(QString::fromUtf8("labelGenius"));
        QFont font;
        font.setPointSize(16);
        labelGenius->setFont(font);
        labelGenius->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(labelGenius);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        labelWordLength = new QLabel(centralwidget);
        labelWordLength->setObjectName(QString::fromUtf8("labelWordLength"));
        labelWordLength->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(labelWordLength);

        sliderWordLength = new QSlider(centralwidget);
        sliderWordLength->setObjectName(QString::fromUtf8("sliderWordLength"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sliderWordLength->sizePolicy().hasHeightForWidth());
        sliderWordLength->setSizePolicy(sizePolicy);
        sliderWordLength->setMinimum(4);
        sliderWordLength->setMaximum(11);
        sliderWordLength->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(sliderWordLength);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        gridLetters = new QGridLayout();
        gridLetters->setObjectName(QString::fromUtf8("gridLetters"));

        horizontalLayout_4->addLayout(gridLetters);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        buttonConfirm = new QPushButton(centralwidget);
        buttonConfirm->setObjectName(QString::fromUtf8("buttonConfirm"));

        horizontalLayout_3->addWidget(buttonConfirm);

        buttonReset = new QPushButton(centralwidget);
        buttonReset->setObjectName(QString::fromUtf8("buttonReset"));

        horizontalLayout_3->addWidget(buttonReset);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelMatchingWords = new QLabel(centralwidget);
        labelMatchingWords->setObjectName(QString::fromUtf8("labelMatchingWords"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelMatchingWords->sizePolicy().hasHeightForWidth());
        labelMatchingWords->setSizePolicy(sizePolicy1);
        labelMatchingWords->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelMatchingWords, 0, Qt::AlignRight);

        buttonMatching = new QPushButton(centralwidget);
        buttonMatching->setObjectName(QString::fromUtf8("buttonMatching"));

        horizontalLayout->addWidget(buttonMatching, 0, Qt::AlignLeft);


        verticalLayout->addLayout(horizontalLayout);

        listMatching = new QListWidget(centralwidget);
        listMatching->setObjectName(QString::fromUtf8("listMatching"));

        verticalLayout->addWidget(listMatching);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelSuggestedWords = new QLabel(centralwidget);
        labelSuggestedWords->setObjectName(QString::fromUtf8("labelSuggestedWords"));
        labelSuggestedWords->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(labelSuggestedWords, 0, Qt::AlignRight);

        buttonSuggested = new QPushButton(centralwidget);
        buttonSuggested->setObjectName(QString::fromUtf8("buttonSuggested"));

        horizontalLayout_2->addWidget(buttonSuggested, 0, Qt::AlignLeft);


        verticalLayout_2->addLayout(horizontalLayout_2);

        listSuggested = new QListWidget(centralwidget);
        listSuggested->setObjectName(QString::fromUtf8("listSuggested"));

        verticalLayout_2->addWidget(listSuggested);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_5);

        Genius->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Genius);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 27));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        Genius->setMenuBar(menubar);
        statusbar = new QStatusBar(Genius);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Genius->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionHelp);

        retranslateUi(Genius);

        QMetaObject::connectSlotsByName(Genius);
    } // setupUi

    void retranslateUi(QMainWindow *Genius)
    {
        Genius->setWindowTitle(QCoreApplication::translate("Genius", "Genius", nullptr));
        actionHelp->setText(QCoreApplication::translate("Genius", "Help", nullptr));
        labelGenius->setText(QCoreApplication::translate("Genius", "Genius", nullptr));
        labelWordLength->setText(QCoreApplication::translate("Genius", "Word length", nullptr));
        buttonConfirm->setText(QCoreApplication::translate("Genius", "Confirm", nullptr));
        buttonReset->setText(QCoreApplication::translate("Genius", "Reset", nullptr));
        labelMatchingWords->setText(QCoreApplication::translate("Genius", "Matching words", nullptr));
        buttonMatching->setText(QCoreApplication::translate("Genius", "Show", nullptr));
        labelSuggestedWords->setText(QCoreApplication::translate("Genius", "Suggested words", nullptr));
        buttonSuggested->setText(QCoreApplication::translate("Genius", "More", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("Genius", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Genius: public Ui_Genius {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENIUS_H
