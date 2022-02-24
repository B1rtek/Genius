#ifndef GENIUS_GENIUSWINDOW_H
#define GENIUS_GENIUSWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_genius.h"
#include "Genius.h"
#include "WordleWord.h"

/**
 * @brief Class operating the game in the GUI version
 */
class GeniusWindow : public QMainWindow {
    Ui_Genius ui{};
    Genius genius;
    WordleWord wordDisplay;

    void linkButtons() const;

    void wordLengthChange();

    void confirmButton();

    void resetButton();

    void showMatchingWords();

    void showSuggestedWords();

    void enterWordFromList(QListWidgetItem *item);

    void showHelp();

public:
    explicit GeniusWindow(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void loadNewDictionary(QString path);
};

#endif //GENIUS_GENIUSWINDOW_H
