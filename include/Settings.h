#ifndef GENIUS_SETTINGS_H
#define GENIUS_SETTINGS_H

#include <string>

/**
 * @brief Class handing settings like the default dictionary or dark mode
 */
class Settings {
    std::string defaultDict;
    bool darkMode;

    void loadSettings();

    void saveSettings();

public:
    Settings();

    void setDefaultDictionary(std::string path);

    std::string getDefaultDictionary();

    void setDarkMode(bool yes);

    bool getDarkMode();
};


#endif //GENIUS_SETTINGS_H
