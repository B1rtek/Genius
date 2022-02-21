#ifndef BATTLESHIP_CPP_BATTLESHIPGUI_H
#define BATTLESHIP_CPP_BATTLESHIPGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_genius.h"
#include "Genius.h"
#include "WordleWord.h"

/**
 * @brief Class operating the game in the GUI version
 */
class GeniusWindow : public QMainWindow {
    Ui_Genius ui;
    Genius genius;
    WordleWord wordDisplay;

    void linkButtons();

    void wordLengthChange();

    void confirmButton();

    void resetButton();

    void showMatchingWords();

    void showSuggestedWords();

    void enterWordFromList(QListWidgetItem *item);

public:
    explicit GeniusWindow(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;
};

#endif //BATTLESHIP_CPP_BATTLESHIPGUI_H
