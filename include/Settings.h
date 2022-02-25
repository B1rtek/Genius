#ifndef GENIUS_SETTINGS_H
#define GENIUS_SETTINGS_H

#include <string>
#include <vector>

/**
 * @brief Class handing settings like the default dictionary or dark mode
 */
class Settings {
    std::string path;
    std::string defaultDict;
    bool darkMode;

public:
    Settings();

    void loadSettings(std::vector<std::string> foundDictionaries);

    void saveSettings();

    void setDefaultDictionary(std::string path);

    std::string getDefaultDictionary();

    void setDarkMode(bool yes);

    bool getDarkMode();
};


#endif //GENIUS_SETTINGS_H
