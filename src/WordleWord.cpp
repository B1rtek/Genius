#include "WordleWord.h"

/**
 * @brief Creates the button array and places it in the specified grid layout
 */
WordleWord::WordleWord(QGridLayout *parentGridLayout) {
    for (int i = 0; i < 5; i++) {
        auto *button = new WordleButton();
        this->buttons.push_back(button);
        parentGridLayout->addWidget(button, 0, i);
    }
    this->gridLayout = parentGridLayout;
    this->reset();
}

/// Needed because GeniusWindow() constructor gets angry
WordleWord::WordleWord() = default;

/**
 * @brief Removes or adds WordleButtons to match the new word length
 * @param newLength new length of the word
 */
void WordleWord::changeLength(int newLength) {
    while (newLength < this->buttons.size()) {
        this->gridLayout->removeWidget(this->buttons.back());
        WordleButton *button = this->buttons.back();
        this->buttons.pop_back();
        button->deleteLater();
    }
    while (newLength > this->buttons.size()) {
        auto *button = new WordleButton();
        this->buttons.push_back(button);
        this->gridLayout->addWidget(button, 0, this->buttons.size());
    }
    this->reset();
}

/**
 * @brief Removes the letter from the last WordleButton
 */
void WordleWord::backspace() {
    if(wordPointer == 0) {
        return;
    }
    wordPointer = std::max(0, wordPointer - 1);
    this->buttons[this->wordPointer]->setLetter(' ');
}

/**
 * @brief Adds a letter to the last WordleButton
 * @param letterEnum Qt::Key enum of the pressed key
 */
void WordleWord::addLetter(Qt::Key letterEnum) {
    if(this->wordPointer == this->buttons.size()) {
        return;
    }
    char letter = char(letterEnum - 0x41 + 97);
    if (letter >= 'a' && letter <= 'z') {
        this->buttons[this->wordPointer]->setLetter(letter);
        wordPointer = std::min(int(this->buttons.size()), wordPointer + 1);
    }
}

/**
 * @brief Compiles the word and the result of entering it from the WordleButtons
 * @return pair containing the entered word and the result
 */
std::pair<std::string, std::string> WordleWord::getUserInput() {
    std::string input, result;
    for (auto & button : this->buttons) {
        char inputLetter = button->getLetter();
        char resultLetter = button->getResultLetter();
        if (inputLetter == ' ' || resultLetter == ' ') {
            return std::make_pair("", "");
        }
        input += inputLetter;
        result += resultLetter;
    }
    return std::make_pair(input, result);
}

/**
 * @brief Resets the WordleButtons
 */
void WordleWord::reset() {
    this->wordPointer = 0;
    for(auto & button : this->buttons) {
        button->reset();
    }
}

/**
 * @brief Enters a new word to the buttons
 * @param newWord new word to enter
 */
void WordleWord::enterWord(std::string newWord) {
    this->wordPointer = this->buttons.size();
    for(int i=0; i<this->buttons.size(); i++) {
        this->buttons[i]->reset();
        this->buttons[i]->setLetter(newWord[i]);
    }
}
