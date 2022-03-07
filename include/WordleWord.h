#ifndef GENIUS_WORDLEWORD_H
#define GENIUS_WORDLEWORD_H

#include <vector>
#include <QGridLayout>
#include "WordleButton.h"

class WordleWord {
    std::vector<WordleButton*> buttons;
    int wordPointer;
    QGridLayout *gridLayout;

public:
    WordleWord();

    explicit WordleWord(QGridLayout *parentGridLayout);

    void changeLength(int newLength);

    void backspace();

    void addLetter(Qt::Key letterEnum);

    std::pair<std::string, std::string> getUserInput();

    void reset();

    void enterWord(std::string newWord);

    void setInput(std::pair<std::string, std::string> input);
};


#endif //GENIUS_WORDLEWORD_H
