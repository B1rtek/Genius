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
    // Thanks gregpaton08 https://stackoverflow.com/users/854871/gregpaton08
    // https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
    std::array<char, 128> buffer{};
    std::string result;
#ifdef _WIN32
    std::string command = "dir " + path + "/A-D /B";
#elif linux
    // https://askubuntu.com/questions/289321/listing-files-in-a-directory-without-listing-subdirectories-and-their-contents-i
    std::string command = "find " + path + " -maxdepth 1 -type f -printf '%f\n'";
#endif
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return {};
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    result += '\n';
    std::vector<std::string> filelist;
    std::string temp;
    for (char i: result) {
        if (i != '\n') {
            temp += i;
        } else {
            filelist.push_back(temp);
            temp.clear();
        }
    }
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
        this->wordlists.emplace_back("words.txt");
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
