#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

string getTextFromFile(string fileName);
string getFragmentFromInput();
double antiPlagiarism(string text, string fragment);
vector<string> getWords(string input);
bool isJoinSeparator(char symbol);
bool isSeparator(char symbol);
bool isWordOkay(string word);
bool isWordsAreEqual(string first, string second);
bool isEnoughWords(int fragmentCount, int textCount);
void retraceTheShingles(vector<string> fragmentWords, vector<string> textWords, int step, int& matchCounter, int& totalCounter);
bool isSamplesAreEqual(int start, int firstIndex, int secondIndex, vector<string> fragmentWords, vector<string> textWords);
void printResult(int value);

int main()
{
    string text = getTextFromFile("source.txt");
    string fragment = getFragmentFromInput();
    cout << endl << "Original text:" << endl << text << endl << endl;

    int percent = antiPlagiarism(text, fragment);
    printResult(percent);

    return 0;
}

string getTextFromFile(string fileName)
{
    string fileContent;
    ifstream fileStream;
    fileStream.open(fileName);
    getline(fileStream, fileContent);

    return fileContent;
}

string getFragmentFromInput()
{
    string content;
    cout << endl << "Please, enter your fragment for checking: ";
    getline(cin >> ws, content);

    return content;
}

double antiPlagiarism(string text, string fragment)
{
    const int STEP = 3;
    int matchCounter = 0;
    int totalCounter = 0;

    vector<string> fragmentWords = getWords(fragment);
    vector<string> textWords = getWords(text);

    if (!isEnoughWords(fragmentWords.size(), textWords.size()))
        return 0;

    retraceTheShingles(fragmentWords, textWords, STEP, matchCounter, totalCounter);

    return ((double)matchCounter / totalCounter) * 100;
}

vector<string> getWords(string input)
{
    const int LETTERS_WORD_MAX = 64;
    int i = 0;
    int iw = 0;
    char word[LETTERS_WORD_MAX];
    string lastWord;
    vector<string> words = {};

    for (i = 0; input[i] != 0; i++) {
        if (isJoinSeparator(input[i])) {
            continue;
        }
        if (!isSeparator(input[i])) {
            word[iw++] = tolower(input[i]);
            if (isSeparator(input[i + 1]) || input[i + 1] == 0) {
                word[iw] = 0;
                string newWord = word;
                if (isWordOkay(word) && !isWordsAreEqual(newWord, lastWord)) {
                    words.push_back(word);
                    lastWord = word;
                }
                iw = 0;
            }
        }
    }

    return words;
}

bool isJoinSeparator(char symbol)
{
    return symbol == '\'' || symbol == '-';
}

bool isSeparator(char symbol)
{
    const char SEPARATORS[] = " .,;:!?\"“”‘’()[]{}+*/=«»„“—–";
    for (int i = 0; SEPARATORS[i] != 0; i++) {
        if (symbol == SEPARATORS[i])
            return true;
    }

    return false;
}

bool isWordOkay(string word)
{
    string stopWords[] = { "a", "an", "of", "it", "in", "and", "the", "as", "like", "but", "so", "what", "when", "where", "while", "due", "to", "for", "this", "that", "these", "those", "nevertheless", "around", "on", "at", "above", "down", "inside", "outside", "out", "such", "from", "between", "or", "who", "which", "unless", "until", "up", "down", "by", "not", "although", "thus" };
    string pronouns[] = { "i", "you", "he", "she", "it", "we", "they", "my", "your", "his", "her", "its", "ours", "yours", "theirs", "me", "him", "us", "them", "myself", "yourself", "himself", "herself", "itself", "ourselves", "yourselves", "themselves", "own" };

    for (int i = 0; i < 45; i++) {
        if (word == stopWords[i])
            return false;
    }
    for (int i = 0; i < 28; i++) {
        if (word == pronouns[i])
            return false;
    }

    return true;
}

bool isWordsAreEqual(string first, string second)
{
    if (first.size() != second.size()) {
        return false;
    }
    for (int i = 0; i < first.size(); i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }

    return true;
}

bool isEnoughWords(int fragmentCount, int textCount)
{
    const int FRAGMENT_MIN = 3;
    const int TEXT_MIN = 10;
    if (fragmentCount < FRAGMENT_MIN || textCount < TEXT_MIN) {
        cout << endl << "ERROR! Word counts in text and fragment are insufficient for checking!" << endl;
        cout << TEXT_MIN << " words for text and " << FRAGMENT_MIN << " words for fragment required (excluding special characters, conjunctions, particles, pronouns)." << endl << endl;
        return false;
    }

    return true;
}

void retraceTheShingles(vector<string> fragmentWords, vector<string> textWords, int step, int& matchCounter, int& totalCounter)
{
    int start = step - 1;
    for (int i = start; i < fragmentWords.size(); i++) {
        for (int j = start; j < textWords.size(); j++) {
            if (isSamplesAreEqual(start, i, j, fragmentWords, textWords)) {
                matchCounter++;
                break;
            }
        }
        totalCounter++;
    }
}

bool isSamplesAreEqual(int start, int firstIndex, int secondIndex, vector<string> fragmentWords, vector<string> textWords)
{
    int count = start;
    while (count >= 0) {
        if (!isWordsAreEqual(fragmentWords[firstIndex - count], textWords[secondIndex - count])) {
            return false;
        }
        count--;
    }

    return true;
}

void printResult(int value)
{
    const int BAR_STEP = 10;
    cout << "The identified borrowing percentage of text is " << value << "%: ";
    for (int i = 0; i < 100; i += BAR_STEP) {
        cout << (i < value ? "█ " : "▓ ");
    }
    cout << endl;
}