#ifndef GENIUS_WORDLISTLOADER_H
#define GENIUS_WORDLISTLOADER_H

#include <vector>
#include <string>
#include <QComboBox>

/**
 * @brief Class responsible for finding and loading wordlists
 */
class WordlistLoader {
    std::vector<std::string> wordlists;

    std::vector<std::string> listFilesInDirectory(std::string path);

    std::string getExtension(std::string path);

public:
    WordlistLoader();

    void findWordlists();

    void addWordlistsToList(QComboBox *comboBox);

    bool wordlistMissing();

    std::vector<std::string> getDictionariesList();
};


#endif //GENIUS_WORDLISTLOADER_H
