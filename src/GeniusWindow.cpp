#include <QKeyEvent>
#include <QMessageBox>
#include "GeniusWindow.h"
#include "WordlistLoader.h"
#include "ui_help.h"

/**
 * @brief Initializes all elements of the game and all additional widgets created
 * in code rather than in the designer like UIBoards and UIFleets
 * @param parent Qt5 stuff, unused
 */
GeniusWindow::GeniusWindow(QWidget *parent) {
    this->ui = Ui_Genius();
    this->ui.setupUi(this);
    this->wordDisplay = WordleWord(this->ui.gridLetters);
    this->genius = Genius();
    WordlistLoader wordlistLoader = WordlistLoader();
    wordlistLoader.findWordlists();
    wordlistLoader.addWordlistsToList(this->ui.comboBoxWordlist);
    if (wordlistLoader.wordlistMissing()) {
        QMessageBox::critical(this, "Genius",
                              "No dictionaries found. Make sure that you put a words.txt file in the app directory, or place a dictionary in the dictionaries folder.",
                              QMessageBox::Ok);
        exit(0);
    }
    this->genius.start(this->ui.comboBoxWordlist->currentText().toStdString());
    this->resetButton();
    this->linkButtons();
}

/**
 * @brief Links the buttons and other UI elements to their callback functions
 */
void GeniusWindow::linkButtons() const {
    this->ui.sliderWordLength->setValue(5);
    connect(this->ui.sliderWordLength, &QSlider::valueChanged, this, &GeniusWindow::wordLengthChange);
    connect(this->ui.buttonConfirm, &QPushButton::clicked, this, &GeniusWindow::confirmButton);
    connect(this->ui.buttonReset, &QPushButton::clicked, this, &GeniusWindow::resetButton);
    connect(this->ui.buttonMatching, &QPushButton::clicked, this, &GeniusWindow::showMatchingWords);
    connect(this->ui.buttonSuggested, &QPushButton::clicked, this, &GeniusWindow::showSuggestedWords);
    connect(this->ui.listMatching, &QListWidget::itemClicked, this, &GeniusWindow::enterWordFromList);
    connect(this->ui.listSuggested, &QListWidget::itemClicked, this, &GeniusWindow::enterWordFromList);
    connect(this->ui.actionHelp, &QAction::triggered, this, &GeniusWindow::showHelp);
    connect(this->ui.comboBoxWordlist, &QComboBox::currentTextChanged, this, &GeniusWindow::loadNewDictionary);
}

/**
 * @brief Informs the WordleWord about the change
 */
void GeniusWindow::wordLengthChange() {
    genius.setWordSize(this->ui.sliderWordLength->value());
    this->wordDisplay.changeLength(this->ui.sliderWordLength->value());
    this->resetButton();
}

/**
 * @brief Starts the analysis of the word
 */
void GeniusWindow::confirmButton() {
    std::pair<std::string, std::string> userInput = this->wordDisplay.getUserInput();
    if (userInput.first.empty() || userInput.second.empty()) {
        return;
    }
    this->ui.listMatching->clear();
    this->ui.listSuggested->clear();
    this->genius.enterWord(userInput.first, userInput.second);
    this->genius.analyze();
    int matchingAmount = this->genius.getMatchingAmount();
    std::string newMatchingText = "Matching words: " + std::to_string(matchingAmount);
    this->ui.labelMatchingWords->setText(newMatchingText.c_str());
    if (matchingAmount <= 10) {
        this->showMatchingWords();
    }
    this->showSuggestedWords();
}

/**
 * @brief Resets everything
 */
void GeniusWindow::resetButton() {
    this->genius.reset();
    this->wordDisplay.reset();
    this->ui.listMatching->clear();
    this->ui.listSuggested->clear();
    std::vector<std::string> starters = this->genius.getStarters();
    for (auto &item: starters) {
        this->ui.listSuggested->addItem(item.c_str());
    }
    this->ui.labelMatchingWords->setText("Matching words");
}

/**
 * @brief Populates the matching words list widget with matching words
 */
void GeniusWindow::showMatchingWords() {
    this->ui.listMatching->clear();
    std::vector<std::string> matching = this->genius.getMatching();
    for (auto &item: matching) {
        this->ui.listMatching->addItem(item.c_str());
    }
}

/**
 * @brief Shows the help window
 */
void GeniusWindow::showHelp() {
    Ui_GeniusHelp helpUI;
    QDialog *helpDialog = new QDialog();
    helpUI.setupUi(helpDialog);
    connect(helpUI.buttonOk, &QPushButton::clicked, helpDialog, &QDialog::close);
    helpDialog->setModal(true);
    helpDialog->show();
}

/**
 * @brief Populates the suggested words list widget with suggested words
 */
void GeniusWindow::showSuggestedWords() {
    std::vector<std::string> suggested = this->genius.getDataWords();
    for (auto &item: suggested) {
        this->ui.listSuggested->addItem(item.c_str());
    }
}

/**
 * @brief Override to capture key presses
 * @param event Qt5 QKeyEvent
 */
void GeniusWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Backspace) {
        this->wordDisplay.backspace();
    } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        this->confirmButton();
    } else {
        this->wordDisplay.addLetter(static_cast<Qt::Key>(event->key()));
    }
}

/**
 * @brief Enters the word from the selected list item into the wordDisplay
 * @param item
 */
void GeniusWindow::enterWordFromList(QListWidgetItem *item) {
    std::string itemContent = item->text().toStdString();
    this->wordDisplay.enterWord(itemContent);
}

/**
 * @brief Detects the action of closing the app and triggers cache saving
 * @param event Qt5 QCloseEvent
 */
void GeniusWindow::closeEvent(QCloseEvent *event) {
    this->genius.saveWordCache();
}

/**
 * @brief Loads the specified dicionary
 */
void GeniusWindow::loadNewDictionary(QString path) {
    this->genius.start(path.toStdString());
    this->resetButton();
}


