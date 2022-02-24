#include <fstream>
#include "WordlistLoader.h"
#include "Genius.h"

/**
 * @brief Creates the WordlistLoader
 */
WordlistLoader::WordlistLoader() = default;

/**
 * @return List of paths to all files in the dictionaries directory
 */
std::vector<std::string> WordlistLoader::listFilesInDirectory(std::string path) {
#ifdef _WIN32
    std::string command = "dir " + path + "/A-D /B > temp.txt";
#elif linux
    // https://askubuntu.com/questions/289321/listing-files-in-a-directory-without-listing-subdirectories-and-their-contents-i
    std::string command = "find " + path + " -maxdepth 1 -type f -printf '%f\n' > temp.txt";
#endif
    system(command.c_str());
    std::fstream list;
    list.open("temp.txt", std::ios::in);
    std::vector<std::string> filelist;
    std::string temp;
    while(getline(list, temp)) {
        filelist.push_back(temp);
    }
    list.close();
    remove("temp.txt");
    return filelist;
}

/**
 * @brief Finds the extension of the file
 * @param path path to the file
 * @return extension
 */
std::string WordlistLoader::getExtension(std::string path) {
    std::string extension;
    int i = path.size() - 1;
    while (i >= 0 && path[i] != '.') {
        extension += path[i];
        i--;
    }
    if (i == 0) {
        return "";
    }
    std::reverse(extension.begin(), extension.end());
    return extension;
}

/**
 * @brief Finds all wordlists
 */
void WordlistLoader::findWordlists() {
    if (fileExists("words.txt")) {
        this->wordlists.emplace_back("default");
    }
    std::vector<std::string> filelist = this->listFilesInDirectory("dictionaries");
    for (auto &file: filelist) {
        if (getExtension(file) == "txt") {
            this->wordlists.push_back(file);
        }
    }
}

/**
 * @brief Adds all wordlists to the dictionary combo box
 * @param comboBox target QComboBox
 */
void WordlistLoader::addWordlistsToList(QComboBox *comboBox) {
    for (auto &file: this->wordlists) {
        comboBox->addItem(QString(file.c_str()));
    }
}

/**
 * @return true if no wordlists were found, false otherwise
 */
bool WordlistLoader::wordlistMissing() {
    return this->wordlists.empty();
}
