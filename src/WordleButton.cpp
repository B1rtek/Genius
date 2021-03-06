#include "WordleButton.h"

/**
 * @brief Creates the WordleButton
 * @param parent Qt5 stuff idk
 */
WordleButton::WordleButton(QWidget *parent) : QPushButton(parent) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    QSizePolicy policy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    policy.setHeightForWidth(true);
    this->setSizePolicy(policy);
    this->setMaximumSize(40, 40);
    this->baseStyleSheet = "color: white; font-size: 20px; font-style: bold;";
    this->reset();
}

/**
 * @brief Sets the actual color of the button to the current one
 */
void WordleButton::setButtonColor() {
    std::map<ButtonColor, std::string> colorMap = {
            {ButtonColor::GRAY,   "#787c7e"},
            {ButtonColor::GREEN,  "#6aaa64"},
            {ButtonColor::YELLOW, "#c9b458"}
    };
    std::string newColorString = this->baseStyleSheet + "background-color: " + colorMap[this->color];
    this->setStyleSheet(newColorString.c_str());
}

/**
 * @brief Ensures that the button is (almost) always square
 * @param width Qt5 stuff idk
 * @return Qt5 stuff idk, this function is overridden
 */
int WordleButton::heightForWidth(int width) const {
    return width;
}

/**
 * @brief Ensures that the button doesn't become too small when resizing the window
 * @param event Qt5 stuff idk
 */
void WordleButton::resizeEvent(QResizeEvent *event) {
    this->setMinimumWidth(this->height());
}

/**
 * @brief Captures the mouse presses and triggers according actions
 * @param event
 */
void WordleButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (this->color == ButtonColor::YELLOW) {
            this->color = ButtonColor::GRAY;
        } else {
            this->color = ButtonColor::YELLOW;
        }
    } else if (event->button() == Qt::RightButton) {
        if (this->color == ButtonColor::GREEN) {
            this->color = ButtonColor::GRAY;
        } else {
            this->color = ButtonColor::GREEN;
        }
    }
    this->setButtonColor();
}

/**
 * @brief Sets the letter to display on the button
 * @param newLetter
 */
void WordleButton::setLetter(char newLetter) {
    this->letter = newLetter;
    if (this->letter == ' ') {
        this->setText(" ");
    } else {
        this->setText(QString(char(int(this->letter) - 32)));
    }
}

/**
 * @return The letter on the button
 */
char WordleButton::getLetter() const {
    return this->letter;
}

/**
 * @return The letter if the color of the button is yellow, capitalized if it's green, or - if it's gray
 */
char WordleButton::getResultLetter() {
    if (this->letter == ' ') {
        return ' ';
    }
    if (this->color == ButtonColor::GRAY) {
        return '-';
    } else if (this->color == ButtonColor::GREEN) {
        return char(int(this->letter) - 32);
    } else {
        return this->letter;
    }
}

/**
 * @brief Resets the state of this button
 */
void WordleButton::reset() {
    this->letter = ' ';
    this->setText("");
    this->color = ButtonColor::GRAY;
    this->setButtonColor();
}

/**
* @brief Sets the new button color
*/
void WordleButton::setColor(ButtonColor newColor) {
    this->color = newColor;
    this->setButtonColor();
}