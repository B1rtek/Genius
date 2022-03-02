#include <QKeyEvent>
#include <QMessageBox>
#include <QStyleFactory>
#include "GeniusWindow.h"
#include "WordlistLoader.h"
#include "ui_help.h"
#include "ui_settings.h"

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
    this->wordlistLoader = WordlistLoader();
    this->wordlistLoader.findWordlists();
    this->wordlistLoader.addWordlistsToList(this->ui.comboBoxWordlist);
    if (this->wordlistLoader.wordlistMissing()) {
        QMessageBox::critical(this, "Genius",
                              "No dictionaries found. Make sure that you put a words.txt file in the app directory, or place a dictionary in the dictionaries folder.",
                              QMessageBox::Ok);
        exit(0);
    }
    this->settings = Settings();
    this->settings.loadSettings(this->wordlistLoader.getDictionariesList());
    this->setDarkMode(this->settings.getDarkMode());
    this->ui.comboBoxWordlist->setCurrentIndex(
            this->ui.comboBoxWordlist->findText(QString(this->settings.getDefaultDictionary().c_str())));
    this->genius.changeDictionary(this->settings.getDefaultDictionary());
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
    connect(this->ui.comboBoxWordlist, &QComboBox::currentTextChanged, this, &GeniusWindow::loadNewDictionary);
    connect(this->ui.actionSettings, &QAction::triggered, this, &GeniusWindow::showSettings);
    connect(this->ui.actionHelp, &QAction::triggered, this, &GeniusWindow::showHelp);
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
    this->analyze(true);
}

/**
 * @brief Starts word analysis
 */
void GeniusWindow::analyze(bool newWordEntered) {
    if(newWordEntered) {
        std::pair<std::string, std::string> userInput = this->wordDisplay.getUserInput();
        if (userInput.first.empty() || userInput.second.empty()) {
            return;
        }
        this->genius.enterWord(userInput.first, userInput.second);
    }
    this->genius.analyze();
    this->ui.listMatching->clear();
    this->ui.listSuggested->clear();
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
 * @brief Shows the help dialog
 */
void GeniusWindow::showHelp() {
    Ui_GeniusHelp helpUI{};
    auto *helpDialog = new QDialog();
    helpUI.setupUi(helpDialog);
    connect(helpUI.buttonOk, &QPushButton::clicked, helpDialog, &QDialog::close);
    helpDialog->show();
}

/**
 * @brief Shows the settings dialog
 */
void GeniusWindow::showSettings() {
    Ui_GeniusSettings settingsUI{};
    auto *settingsDialog = new QDialog();
    settingsUI.setupUi(settingsDialog);
    settingsUI.checkBoxDarkMode->setChecked(this->settings.getDarkMode());
    for (auto &dict: wordlistLoader.getDictionariesList()) {
        settingsUI.comboBoxDictSetting->addItem(QString(dict.c_str()));
    }
    settingsUI.comboBoxDictSetting->setCurrentIndex(
            settingsUI.comboBoxDictSetting->findText(QString(this->settings.getDefaultDictionary().c_str())));
    connect(settingsUI.buttonOk, &QPushButton::clicked, settingsDialog, &QDialog::close);
    connect(settingsUI.checkBoxDarkMode, &QCheckBox::stateChanged, this, &GeniusWindow::setDarkMode);
    connect(settingsUI.comboBoxDictSetting, &QComboBox::currentTextChanged, this, &GeniusWindow::setDefaultDictionary);
    settingsDialog->setModal(true);
    settingsDialog->show();
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
    this->settings.saveSettings();
}

/**
 * @brief Loads the specified dictionary
 */
void GeniusWindow::loadNewDictionary(const QString& path) {
    if (path.toStdString() == this->genius.getCurrentDictionary()) {
        return;
    }
    this->genius.changeDictionary(path.toStdString());
    if(this->genius.getHistorySize() == 0) {
        this->resetButton();
    } else {
        this->analyze(false);
    }
}

/**
 * @brief Sets the dark mode and saves it in the settings
 */
void GeniusWindow::setDarkMode(bool darkMode) {
    this->settings.setDarkMode(darkMode);
    // Thank you Jorgen (https://stackoverflow.com/users/6847516/jorgen) for sharing your dark mode palette ^^
    // https://stackoverflow.com/questions/15035767/is-the-qt-5-dark-fusion-theme-available-for-windows
    if (darkMode) {
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
        darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
        darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
        darkPalette.setColor(QPalette::Dark, QColor(35, 35, 35));
        darkPalette.setColor(QPalette::Shadow, QColor(20, 20, 20));
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
        darkPalette.setColor(QPalette::HighlightedText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));
        QApplication::setPalette(darkPalette);
    } else {
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(255, 255, 255));
        darkPalette.setColor(QPalette::WindowText, QColor(46, 51, 56));
        darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(116, 127, 141));
        darkPalette.setColor(QPalette::Base, QColor(242, 243, 245));
        darkPalette.setColor(QPalette::AlternateBase, QColor(235, 237, 239));
        darkPalette.setColor(QPalette::ToolTipBase, QColor(242, 243, 245));
        darkPalette.setColor(QPalette::ToolTipText, QColor(46, 51, 56));
        darkPalette.setColor(QPalette::Text, QColor(46, 51, 56));
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(116, 127, 141));
        darkPalette.setColor(QPalette::Dark, QColor(46, 51, 56));
        darkPalette.setColor(QPalette::Shadow, QColor(235, 235, 235));
        darkPalette.setColor(QPalette::Button, QColor(222, 222, 222));
        darkPalette.setColor(QPalette::ButtonText, QColor(46, 51, 56));
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(128, 128, 128));
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(175, 175, 175));
        darkPalette.setColor(QPalette::HighlightedText, QColor(46, 51, 56));
        darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(128, 128, 128));
        QApplication::setPalette(darkPalette);
    }
}

/**
 * @brief Sets the new default dictionary
 */
void GeniusWindow::setDefaultDictionary(const QString& defaultDict) {
    this->settings.setDefaultDictionary(defaultDict.toStdString());
}
