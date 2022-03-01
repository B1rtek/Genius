#include <fstream>
#include <ctime>
#include <algorithm>
#include <random>
#include <utility>
#include "Genius.h"

/**
 * @brief Calculates the score of the word
 * @param word word to calculate score of
 * @return score
 *
 * Score is calculated according to letter values in Scrabble
 */
int calculateScore(const std::string &word) {

    std::set<char> letters[10] = {{'a', 'e', 'i', 'o', 'u', 'l', 'n', 'r', 's', 't'},
                                  {'d', 'g'},
                                  {'b', 'c', 'm', 'p'},
                                  {'f', 'h', 'v', 'w', 'y'},
                                  {'k'},
                                  {},
                                  {},
                                  {'j', 'x'},
                                  {},
                                  {'q', 'z'}};

    int score = 0;
    for (char i: word) {
        for (int j = 0; j < 10; j++) {
            if (letters[j].count(i)) {
                score += 1 + j;
            }
        }
    }
    return score;
}

/**
 * @brief Custom compare function for sorting words from best to worst from the data gathering standpoint
 *
 * sort() using this compare function sorts words according to their scores in Scrabble, the lowest ranked words
 * come first on the list
 */
bool compare(const std::string &word1, const std::string &word2) {
    std::set<char> let1, let2;
    for (char i: word1) {
        let1.insert(i);
    }
    for (char i: word2) {
        let2.insert(i);
    }
    if (let1.size() > let2.size()) {
        return true;
    } else if (let1.size() < let2.size()) {
        return false;
    }
    int score1 = calculateScore(word1), score2 = calculateScore(word2);
    if (score1 < score2) {
        return true;
    } else {
        return false;
    }
}

/**
 * Checks if the specified file exists
 * @param path path to the file to check
 * @return true if it exists, false if it doesn't
 *
 * Replacement for std::filesystem::exists because programs compiled with it don't run
 */
bool fileExists(const std::string &path) {
    std::ifstream f(path.c_str());
    return f.good();
}

/**
 * @brief Checks if the string contains a number
 * @param possiblyNumber string to check
 * @return true if it contains a number, false otherwise
 *
 * Created so I don't have to handle exceptions while converting strings to numbers
 */
bool isNumeric(std::string &possiblyNumber) {
    return std::all_of(possiblyNumber.begin(), possiblyNumber.end(),
                       [](char character) { return character >= '0' && character <= '9'; });
}

/**
 * @brief Initializes the Genius class
 */
Genius::Genius() {
    this->wordSize = 5;
    this->currentDataWordIndex = 0;
    this->dictionaryPath = "";
    this->historyPointer = 0;
}

/**
 * @brief Loads words from the dictionary
 */
void Genius::loadWords(const std::string &path) {
    for (int i = 0; i < 8; i++) {
        this->dictionary[i].clear();
        this->bestStarters[i].clear();
    }
    std::string pathToDict, pathToCache;
    if (path == "default") {
        pathToDict = "words.txt";
        pathToCache = "wordCache.gen";
    } else {
        pathToDict = "dictionaries/" + path;
        pathToCache = "dictionaries/" + path + ".cache";
    }
    std::fstream wordlist;
    wordlist.open(pathToDict.c_str(), std::ios::in);
    std::string word;
    while (getline(wordlist, word)) {
        word = Genius::purify(word);
        if (word.size() < 4 || word.size() > 11) {
            continue;
        }
        this->dictionary[word.size() - 4].push_back(word);
    }
    wordlist.close();
    if (fileExists(pathToCache)) {
        std::fstream wordCache;
        int currentLength = 0;
        wordCache.open(pathToCache.c_str(), std::ios::in);
        while (getline(wordCache, word)) {
            if (word.size() < 4) {
                if (isNumeric(word)) {
                    currentLength = stoi(word);
                } else {
                    currentLength = 0;
                }
            } else {
                this->bestStarters[currentLength - 4].push_back(word);
            }
        }
        wordCache.close();
    }
    this->findStarters();
}

/**
 * @brief Removes all characters that are not letters from the word and converts it to lowercase
 * @param word word to be purified
 * @return purified word
 */
std::string Genius::purify(std::string word) {
    std::string out;
    for (auto &letter: word) {
        if (letter <= 'z' && letter >= 'a') {
            out += letter;
        } else if (letter <= 'Z' && letter >= 'A') {
            letter += 32;
            out += letter;
        }
    }
    return out;
}

/**
 * @brief Chooses the best starting words
 */
void Genius::findStarters() {
    if (this->bestStarters[wordSize - 4].empty()) {
        sort(this->dictionary[wordSize - 4].begin(), this->dictionary[wordSize - 4].end(), compare);
        int k = 0;
        if (this->dictionary[wordSize - 4].empty()) {
            return;
        }
        int minScore = calculateScore(dictionary[wordSize - 4][0]);
        while (calculateScore(dictionary[wordSize - 4][k]) == minScore) {
            bestStarters[wordSize - 4].push_back(dictionary[wordSize - 4][k]);
            k++;
        }
    }
}

/**
 * @brief Extracts the confirmed word from the input
 * @param input result of entering the word into Wordle
 * @return string containing just the confirmed letters
 */
std::string Genius::getConfirmed(std::string input) const {
    std::string output;
    for (int i = 0; i < this->wordSize; i++) {
        output += ' ';
    }
    for (int i = 0; i < this->wordSize; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            output[i] = char(int(input[i]) + 32);
        }
    }
    return output;
}

/**
 * @brief Merges the new and old currentConfirmed letters strings
 * @param currentConfirmed current currentConfirmed letters string
 * @param newConfirmed new currentConfirmed letters string, created with getConfirmed()
 * @return currentConfirmed letters string merged from these two
 */
std::string Genius::mergeConfirmed(std::string currentConfirmed, std::string newConfirmed) const {
    for (int i = 0; i < this->wordSize; i++) {
        if (currentConfirmed[i] == ' ') {
            currentConfirmed[i] = newConfirmed[i];
        }
    }
    return currentConfirmed;
}

/**
 * @brief Adds letters to the notHere sets
 * @param currentNotHere current vector of notHere sets
 * @param input result of entering the word into Wordle
 * @return updated notHere vector
 *
 * There exists a notHere set for all letters in the word, knowing that a certain letter can't be at the certain
 * position helps filtering out matching words
 */
void Genius::addNotHere(std::vector<std::set<char>> &currentNotHere, std::string input) const {
    for (int i = 0; i < this->wordSize; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            currentNotHere[i].insert(input[i]);
        }
    }
}

/**
 * @brief Adds letters to the inWord set
 * @param inWord set to add new letters to
 * @param input result of entering the word into Wordle
 */
void Genius::addInWord(std::set<char> &inWordSet, std::string input) const {
    for (int i = 0; i < this->wordSize; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            inWordSet.insert(input[i]);
        }
        if (input[i] >= 'A' && input[i] <= 'Z') {
            inWordSet.insert(char(int(input[i]) + 32));
        }
    }
}

/**
 * @brief Adds letters to the wrong letters set
 * @param wrong set of wrong letters
 * @param input result of entering the word into Wordle
 * @param yourWord the word entered into Wordle
 */
void Genius::addWrong(std::set<char> &wrongSet, std::string input, std::string yourWord) const {
    for (int i = 0; i < this->wordSize; i++) {
        if (input[i] == '-') {
            wrongSet.insert(yourWord[i]);
        }
    }
}

/**
 * @brief Fixes the wrong letters set by removing letters that got into it and inWord set at the same time
 * @param wrong set of wrong letters
 * @param inWord set of letters in the word
 */
void Genius::fixWrong(std::set<char> &wrongSet, const std::set<char> &inWordSet) {
    for (auto &letter: inWordSet) {
        if (wrongSet.count(letter)) {
            wrongSet.erase(letter);
        }
    }
}

/**
 * @brief Creates a vector of all matching words
 * @param allWords list of all words of the currently analyzed length
 * @param currentConfirmed current confirmed letters string
 * @param currentInWord set of letters in the word
 * @param currentWrong set of wrong letters
 * @param currentNotHere vector of notHere sets
 * @return vector containing all matching words
 *
 * The algorithm is not that complicated, you can figure it out by reading the code
 */
std::vector<std::string>
Genius::findMatching(std::vector<std::string> allWords, std::string currentConfirmed,
                     const std::set<char> &currentInWord,
                     const std::set<char> &currentWrong, std::vector<std::set<char>> currentNotHere) const {
    std::vector<std::string> currentMatching;
    int inWordDistr[26], distr[26];
    std::fill(inWordDistr, inWordDistr + 26, 0);
    for (auto &letter: currentInWord) {
        inWordDistr[letter - 97]++;
    }
    bool good;
    for (auto &word: allWords) {
        good = true;
        for (int j = 0; j < this->wordSize; j++) {
            if (currentConfirmed[j] != ' ' && currentConfirmed[j] != word[j]) {
                good = false;
                break;
            }
            if (!currentInWord.count(word[j]) && currentWrong.count(word[j])) {
                good = false;
                break;
            }
            if (currentNotHere[j].count(word[j])) {
                good = false;
                break;
            }
        }
        if (!good) {
            continue;
        }
        std::fill(distr, distr + 26, 0);
        for (auto &letter: word) {
            distr[letter - 97]++;
        }
        for (int j = 0; j < 26; j++) {
            if (distr[j] < inWordDistr[j]) {
                good = false;
                break;
            }
        }
        if (good) {
            currentMatching.push_back(word);
        }
    }
    sort(currentMatching.begin(), currentMatching.end());
    return currentMatching;
}

/**
 * @brief Creates a vector of the best words to gather data about the mystery word
 * @param allWords
 * @param currentConfirmed
 * @param currentInWord
 * @param currentWrong
 * @return
 */
std::vector<std::string>
Genius::findDataWords(const std::vector<std::string> &allWords, const std::set<char> &currentInWord,
                      const std::set<char> &currentWrong) const {
    std::vector<std::string> wordSplit[this->wordSize * 2 + 1];
    int goodScore;
    bool bad;
    for (auto &word: allWords) {
        goodScore = 0;
        bad = false;
        for (auto &letter: word) {
            if (currentWrong.count(letter)) {
                goodScore++;
            }
            if (currentInWord.count(letter)) {
                bad = true;
            }
        }
        if (!bad) {
            wordSplit[goodScore].push_back(word);
        } else {
            wordSplit[goodScore + this->wordSize].push_back(word);
        }
    }
    for (auto &i: wordSplit) {
        if (i.size() > 1) {
            sort(i.begin(), i.end(), compare);
        }
    }
    std::vector<std::string> result;
    for (auto &i: wordSplit) {
        for (auto &word: i) {
            result.push_back(word);
        }
    }
    return result;
}

/**
 * @brief Creates a list of 10 good starting words
 * @return a list containing 10 good starting words
 */
std::vector<std::string> Genius::getStarters() {
    std::mt19937 gen(time(nullptr)); // NOLINT(cert-msc51-cpp) it really doesn't matter
    std::shuffle(this->bestStarters[this->wordSize - 4].begin(), this->bestStarters[this->wordSize - 4].end(), gen);
    std::vector<std::string> starters;
    int amount = this->bestStarters[this->wordSize -
                                    4].size(); // NOLINT(cppcoreguidelines-narrowing-conversions) doesn't matter
    amount = std::min(amount, 10);
    for (int i = 0; i < amount; i++) {
        starters.push_back(bestStarters[this->wordSize - 4][i]);
    }
    return starters;
}

/**
 * @brief Primary data input method
 * @param enteredWord word entered into Wordle
 * @param result result of entering that word into Wordle
 */
void Genius::enterWord(std::string enteredWord, std::string result) {
    if(this->historyPointer >= this->history.size()) {
        this->history.emplace_back(enteredWord, result);
    } else {
        this->history.back() = std::make_pair(enteredWord, result);
    }
    this->userWord = std::move(enteredWord);
    this->userResult = std::move(result);
}

/**
 * @brief Analyzes the entered word
 */
void Genius::analyze() {
    while (historyPointer < this->history.size()) {
        this->currentDataWordIndex = 0;
        this->userWord = this->history[historyPointer].first;
        this->userResult = this->history[historyPointer].second;
        std::string conf = getConfirmed(this->userResult);
        this->confirmed = this->mergeConfirmed(this->confirmed, conf);
        addNotHere(this->notHere, this->userResult);
        this->addInWord(this->inWord, this->userResult);
        this->addWrong(this->wrong, this->userResult, this->userWord);
        this->fixWrong(this->wrong, this->inWord);
        this->matching = this->findMatching(this->dictionary[this->wordSize - 4], this->confirmed, this->inWord,
                                            this->wrong, this->notHere);
        this->dataWords = this->findDataWords(this->dictionary[this->wordSize - 4], this->inWord, this->wrong);
        this->historyPointer++;
    }
}

/**
 * @return Amount of matching words
 */
int Genius::getMatchingAmount() {
    return this->matching.size(); // NOLINT(cppcoreguidelines-narrowing-conversions) doesn't matter
}

/**
 * @brief Gets all matching words list
 * @return vector with all matching words
 */
std::vector<std::string> Genius::getMatching() {
    return this->matching;
}

/**
 * @brief Gets 10 next data words
 * @return vector with 10 data words
 */
std::vector<std::string> Genius::getDataWords() {
    std::vector<std::string> dataWordsBatch;
    int batchPointer = this->dataWords.size(); // NOLINT(cppcoreguidelines-narrowing-conversions) doesn't matter
    batchPointer = std::min(batchPointer, currentDataWordIndex + 10);
    for (int i = currentDataWordIndex; i < batchPointer; i++) {
        dataWordsBatch.push_back(this->dataWords[i]);
    }
    currentDataWordIndex = batchPointer;
    return dataWordsBatch;
}

/**
 * @brief Sets the word size
 */
void Genius::setWordSize(int newWordSize) {
    this->wordSize = newWordSize;
    this->reset();
    this->findStarters();
}

/**
 * @brief Resets the Genius
 */
void Genius::reset() {
    this->wrong.clear();
    this->inWord.clear();
    this->notHere.clear();
    this->confirmed.clear();
    this->dataWords.clear();
    notHere.reserve(wordSize);
    for (int i = 0; i < this->wordSize; i++) {
        notHere.emplace_back();
        confirmed += ' ';
    }
    this->currentDataWordIndex = 0;
    this->historyPointer = 0;
    this->history.clear();
}

/**
 * @brief Saves the bestStarters lists to wordCache.gen
 */
void Genius::saveWordCache() {
    std::string cachePath;
    if (dictionaryPath.empty()) {
        return;
    }
    if (this->dictionaryPath == "default") {
        cachePath = "wordCache.gen";
    } else {
        cachePath = "dictionaries/" + this->dictionaryPath + ".cache";
    }
    std::fstream wordCache;
    wordCache.open(cachePath.c_str(), std::ios::out);
    for (int i = 0; i < 8; i++) {
        if (!this->bestStarters[i].empty()) {
            wordCache << i + 4 << std::endl;
            for (const auto &word: bestStarters[i]) {
                wordCache << word << std::endl;
            }
        }
    }
    wordCache.close();
}

/**
 * @brief Starts Genius
 *
 * Contains a part of constructor that segfaults if no words.txt is present
 */
void Genius::start(const std::string &path) {
    this->saveWordCache();
    this->dictionaryPath = path;
    //this->reset();
    loadWords(path);
    this->historyPointer = 0;
    this->analyze();
}

/**
 * @return Current dictionary path
 */
std::string Genius::getCurrentDictionary() {
    return this->dictionaryPath;
}
