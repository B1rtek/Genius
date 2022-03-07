#include <iostream>

#include "Genius.h"

using namespace std;

void printVectorContents(const vector<string>& content, const string& title = "", const string& footer = "") {
    if (!title.empty()) cout << title << endl;
    for (auto &line: content) {
        cout << line << endl;
    }
    if (!footer.empty()) cout << footer;
}

bool yesOrNo() {
    string input;
    getline(cin, input);
    return (input.empty() || input[0] == 'Y' || input[0] == 'y');
}

int main(int argc, char **argv) {
    int wordSize = 5;
    if (argc >= 2) {
        wordSize = stoi(argv[1]);
    }
    Genius genius = Genius();
    genius.changeDictionary("default");
    genius.reset();
    genius.setWordSize(wordSize);
    vector<string> suggestedStartWords = genius.getStarters();
    printVectorContents(suggestedStartWords, "Suggested start words: ");
    string userWord, result;
    while (true) {
        cout << "Enter your word: ";
        cin >> userWord;
        cout << "Enter the result: ";
        cin >> result;
        genius.enterWord(userWord, result);
        genius.analyze();
        vector<string> matchingWords = genius.getMatching();
        int matchingAmount = genius.getMatchingAmount();
        if (matchingAmount == 1) {
            cout << "The word is " << matchingWords[0] << endl;
            break;
        } else {
            cout << "Found " << matchingAmount << " matching words. Display them? [Y/n]";
        }
        getline(cin, result); /// garbage
        if (yesOrNo()) {
            printVectorContents(matchingWords, "Matching words:");
        }
        vector<string> dataWords = genius.getDataWords();
        printVectorContents(dataWords, "Suggested words:", "Display more? [Y/n]");
        while (yesOrNo()) {
            dataWords = genius.getDataWords();
            printVectorContents(dataWords, "", "Display more? [Y/n]");
        }
    }
    return 0;
}