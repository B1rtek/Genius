#include "Settings.h"
#include "Genius.h"
#include <json.hpp>
#include <fstream>

/**
 * @brief Initializes the Settings by setting the settings file path
 */
Settings::Settings() {
    this->path = "settings.json";
}

/**
 * @brief Loads the settings from the settings file, or applies defaults if no settings file is present
 */
void Settings::loadSettings(std::vector<std::string> foundDictionaries) {
    if (!fileExists(this->path)) {
        this->darkMode = true;
        this->defaultDict = "default";
        return;
    }
    std::fstream settingsFile(this->path);
    std::stringstream ss;
    ss << settingsFile.rdbuf();
    settingsFile.close();
    std::string content = ss.str();
    nlohmann::json settingsJson = nlohmann::json::parse(content);
    this->defaultDict = settingsJson.value("defaultDictionary", "default");
    this->darkMode = settingsJson.value("forTheLoveOfGodPleaseNo", true);
    /// a check is performed to see if the specified default dictionary exists, and if it doesn't, the first one is chosen
    for (auto &dict: foundDictionaries) {
        if (dict == this->defaultDict) {
            return;
        }
    }
    /// the dictionary wasn't found, the first one from the list is chosen
    this->defaultDict = foundDictionaries[0];
}

/**
 * @brief Saves the settings to the settings.json file
 */
void Settings::saveSettings() {
    nlohmann::json settingsJson = {
            {"defaultDictionary", this->defaultDict},
            {"forTheLoveOfGodPleaseNo", this->darkMode}
    };
    std::fstream settingsFile;
    settingsFile.open(this->path, std::ios::out);
    settingsFile << std::setw(4) << settingsJson;
    settingsFile.close();
}

/**
 * @brief Sets the default dictionary setting
 * @param path new default dictionary path
 */
void Settings::setDefaultDictionary(std::string path) {
    this->defaultDict = path;
}

/**
 * @return The current state of the default dictionary setting
 */
std::string Settings::getDefaultDictionary() {
    return this->defaultDict;
}

/**
 * @brief Sets the dark mode setting
 * @param yes new state of the dark mode
 */
void Settings::setDarkMode(bool yes) {
    this->darkMode = yes;
}

/**
 * @return The current state of the dark mode setting
 */
bool Settings::getDarkMode() {
    return this->darkMode;
}
