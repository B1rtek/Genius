#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;

int wordSize = 5;

string purify(string letters) {
    string out;
    for (auto &letter: letters) {
        if (letter <= 'z' && letter >= 'a') {
            out += letter;
        } else if (letter <= 'Z' && letter >= 'A') {
            letter += 32;
            out += letter;
        }
    }
    return out;
}

vector<string> loadWords() {
    fstream wordlist;
    wordlist.open("words.txt", ios::in);
    vector<string> words;
    string word;
    while (getline(wordlist, word)) {
        word = purify(word);
        if (word.size() == wordSize) {
            words.push_back(word);
        }
    }
    wordlist.close();
    return words;
}

bool yesOrNo() {
    string input;
    getline(cin, input);
    return (input.empty() || input[0] == 'Y' || input[0] == 'y');
}

string randomWord(vector<string> words) {
    srand(time(nullptr));
    return words[rand() % words.size()];
}

string getConfirmed(string input) {
    string output;
    for (int i = 0; i < wordSize; i++) {
        output += ' ';
    }
    for (int i = 0; i < wordSize; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            output[i] = char(int(input[i]) + 32);
        }
    }
    return output;
}

string merge(string confirmed, string newconf) {
    for (int i = 0; i < wordSize; i++) {
        if (confirmed[i] == ' ') {
            confirmed[i] = newconf[i];
        }
    }
    return confirmed;
}

vector<set<char>> addNotHere(vector<set<char>> notHere, string input) {
    for (int i = 0; i < wordSize; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            notHere[i].insert(input[i]);
        }
    }
    return notHere;
}

void addInWord(set<char> &inWord, string input) {
    for (int i = 0; i < wordSize; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            inWord.insert(input[i]);
        }
        if (input[i] >= 'A' && input[i] <= 'Z') {
            inWord.insert(char(int(input[i]) + 32));
        }
    }
}

void addWrong(set<char> &wrong, string input, string yourWord) {
    for (int i = 0; i < wordSize; i++) {
        if (input[i] == '-') {
            wrong.insert(yourWord[i]);
        }
    }
}

vector<string>
findMatching(vector<string> words, string confirmed, set<char> inWord, set<char> wrong, vector<set<char>> notHere,
             set<char> confirmedSet) {
    vector<string> matching;
    int inWordDistr[26], distr[26];
    fill(inWordDistr, inWordDistr + 26, 0);
    for (auto &letter: inWord) {
        inWordDistr[letter - 97]++;
    }
    bool good;
    for (auto &word: words) {
        good = true;
        for (int j = 0; j < wordSize; j++) {
            if (confirmed[j] != ' ' && confirmed[j] != word[j]) {
                good = false;
                break;
            }
            if (!inWord.count(word[j]) && wrong.count(word[j])) {
                good = false;
                break;
            }
            if (notHere[j].count(word[j])) {
                good = false;
                break;
            }
        }
        if (!good) {
            continue;
        }
        fill(distr, distr + 26, 0);
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
            matching.push_back(word);
        }
    }
    sort(matching.begin(), matching.end());
    return matching;
}

set<char> letters[10] = {{'a', 'e', 'i', 'o', 'u', 'l', 'n', 'r', 's', 't'},
                         {'d', 'g'},
                         {'b', 'c', 'm', 'p'},
                         {'f', 'h', 'v', 'w', 'y'},
                         {'k'},
                         {},
                         {},
                         {'j', 'x'},
                         {},
                         {'q', 'z'}};

int calculateScore(string word) {
    int score = 0;
    for (char &i: word) {
        for (int j = 0; j < 10; j++) {
            if (letters[j].count(i)) {
                score += 1 + j;
            }
        }
    }
    return score;
}

bool compare(string const &word1, string const &word2) {
    set<char> let1, let2;
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

vector<string> findDataWords(vector<string> words, string confirmed, set<char> inWord, set<char> wrong) {
    vector<string> wordSplit[wordSize * 2 + 1];
    int goodScore;
    bool bad;
    for (auto &word: words) {
        goodScore = 0;
        bad = false;
        for (auto &letter: word) {
            if (wrong.count(letter)) {
                goodScore++;
            }
            if (inWord.count(letter)) {
                bad = true;
            }
        }
        if (!bad) {
            wordSplit[goodScore].push_back(word);
        } else {
            wordSplit[goodScore + wordSize].push_back(word);
        }
    }
    for (auto &i: wordSplit) {
        if (i.size() > 1) {
            sort(i.begin(), i.end(), compare);
        }
    }
    vector<string> result;
    for (auto &i: wordSplit) {
        for (auto &word: i) {
            result.push_back(word);
        }
    }
    return result;
}

set<char> createSetFromString(string letters) {
    set<char> lettersSet;
    for (auto &letter: letters) {
        if (letter >= 'a' && letter <= 'z') {
            lettersSet.insert(letter);
        }
    }
    return lettersSet;
}

void fixWrong(set<char> &wrong, const set<char>& inWord) {
    for (auto &letter: inWord) {
        if (wrong.count(letter)) {
            wrong.erase(letter);
        }
    }
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        wordSize = stoi(argv[1]);
    }
    vector<string> words = loadWords();
    vector<string> bestStarters;
    sort(words.begin(), words.end(), compare);
    int k = 0, minScore = calculateScore(words[0]);
    while (calculateScore(words[k]) == minScore) {
        bestStarters.push_back(words[k]);
        k++;
    }
    cout << "Suggested start word: " << randomWord(bestStarters) << endl;
    string confirmed;
    for (int i = 0; i < wordSize; i++) {
        confirmed += ' ';
    }
    set<char> wrong, inWord, confirmedSet;
    vector<set<char>> notHere;
    notHere.reserve(wordSize);
    for (int i = 0; i < wordSize; i++) {
        notHere.emplace_back();
    }
    vector<string> matching, dataWords;
    string yourWord, input;
    for (int i = 0; i < 6; i++) {
        cout << "Enter your word: ";
        cin >> yourWord;
        cout << "Enter the result: ";
        cin >> input;
        string conf = getConfirmed(input);
        confirmed = merge(confirmed, conf);
        confirmedSet = createSetFromString(confirmed);
        notHere = addNotHere(notHere, input);
        addInWord(inWord, input);
        addWrong(wrong, input, yourWord);
        fixWrong(wrong, inWord);
        matching = findMatching(words, confirmed, inWord, wrong, notHere, confirmedSet);
        if (matching.size() == 1) {
            cout << "The word is " << matching[0] << endl << "GG!" << endl;
            exit(0);
        }
        cout << "Found " << matching.size() << " matching words. Display them? [Y/n]";
        getline(cin, yourWord);
        if (yesOrNo()) {
            for (auto &word: matching) {
                cout << word << endl;
            }
        }
        dataWords = findDataWords(words, confirmed, inWord, wrong);
        cout << "Display words to try? [Y/n]";
        if (yesOrNo()) {
            unsigned long long current = 0;
            do {
                for (unsigned long long j = current; j < min(current + 10, dataWords.size()); j++) {
                    cout << dataWords[j] << endl;
                }
                cout << "Display more? [Y/n]";
                current += 10;
            } while (yesOrNo());
        }
    }
    return 0;
}
