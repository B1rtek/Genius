#ifndef GENIUS_WORDLEBUTTON_H
#define GENIUS_WORDLEBUTTON_H

#include <set>
#include <QtWidgets/QPushButton>
#include <QMouseEvent>

enum ButtonColor {
    GRAY, YELLOW, GREEN
};

class WordleButton : public QPushButton {
    char letter;
    ButtonColor color;
    std::string baseStyleSheet;

    void setButtonColor();

public:
    explicit WordleButton(QWidget *parent = nullptr);

    [[nodiscard]] int heightForWidth(int width) const override;

    void resizeEvent(QResizeEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void setLetter(char newLetter);

    char getLetter() const;

    char getResultLetter();

    void reset();
};

#endif //GENIUS_WORDLEBUTTON_H
