#ifndef GENIUS_GENIUS_H
#define GENIUS_GENIUS_H

#include <vector>
#include <string>
#include <set>

int calculateScore(const std::string &word);

bool compare(std::string const &word1, std::string const &word2);

bool fileExists(const std::string &path);

bool isNumeric(std::string &possiblyNumber);

class Genius {
    std::vector<std::string> dictionary[8];
    std::vector<std::string> bestStarters[8];
    int wordSize;
    std::set<char> wrong, inWord;
    std::vector<std::set<char>> notHere;
    std::string userWord, userResult, confirmed;
    std::vector<std::string> matching, dataWords;
    int currentDataWordIndex;

    void loadWords(std::string path);

    static std::string purify(std::string word);

    void findStarters();

    [[nodiscard]] std::string getConfirmed(std::string input) const;

    [[nodiscard]] std::string mergeConfirmed(std::string currentConfirmed, std::string newConfirmed) const;

    void addNotHere(std::vector<std::set<char>> &currentNotHere, std::string input) const;

    void addInWord(std::set<char> &inWord, std::string input) const;

    void addWrong(std::set<char> &wrong, std::string input, std::string yourWord) const;

    static void fixWrong(std::set<char> &wrong, const std::set<char>& inWord);

    [[nodiscard]] std::vector<std::string>
    findMatching(std::vector<std::string> allWords, std::string currentConfirmed, const std::set<char>& currentInWord,
                 const std::set<char>& currentWrong,
                 std::vector<std::set<char>> currentNotHere) const;

    [[nodiscard]] std::vector<std::string>
    findDataWords(const std::vector<std::string>& allWords, const std::set<char>& currentInWord, const std::set<char>& currentWrong) const;

public:
    Genius();

    std::vector<std::string> getStarters();

    void enterWord(std::string enteredWord, std::string result);

    void analyze();

    int getMatchingAmount();

    std::vector<std::string> getMatching();

    std::vector<std::string> getDataWords();

    void setWordSize(int newWordSize);

    void reset();

    void saveWordCache();

    bool checkIfWordsFileExists();

    void start(std::string path);
};

#endif //GENIUS_GENIUS_H
