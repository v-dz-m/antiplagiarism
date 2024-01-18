#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

double antiPlagiarism(string text, string fragment);
vector<string> getWords(string input);
bool isSeparator(char symbol);
bool isJoinSeparator(char symbol);
bool isWordOkay(string word);
void retraceTheShingles(vector<string> fragmentWords, vector<string> textWords, int step, int& matchCounter, int& totalCounter);
bool isSamplesEqual(int start, int firstIndex, int secondIndex, vector<string> fragmentWords, vector<string> textWords);

int main()
{
    string text = "Plagiarism is the representation of another person's language, thoughts, ideas, or expressions as one's own original work. Although precise definitions vary depending on the institution, in many countries and cultures plagiarism is considered a violation of academic integrity and journalistic ethics, as well as social norms around learning, teaching, research, fairness, respect, and responsibility. As such, a person or entity that is determined to have committed plagiarism is often subject to various punishments or sanctions, such as suspension, expulsion from school or work, fines, imprisonment, and other penalties. Plagiarism is typically not in itself a crime, but like counterfeiting, fraud can be punished in a court for prejudices caused by copyright infringement, violation of moral rights, or torts. In academia and in industry, it is a serious ethical offense. Plagiarism and copyright infringement overlap to a considerable extent, but they are not equivalent concepts, and although many types of plagiarism may not meet the legal requirements in copyright law as adjudicated by courts, they still constitute the passing-off of another's work as one's own, and thus plagiarism. Not all cultures and countries hold the same beliefs about personal ownership of language or ideas. In some cultures, the reiteration of another professional's work can be a sign of respect or flattery towards the person whose work is reiterated. Students who are from such countries and cultures and who move to the United States or other Western countries (where plagiarism is frowned upon) may find the transition difficult.";
    string fragment = "Plagiarism is often subject to various punishments or sanctions, such as suspension, expulsion from school or work, fines, imprisonment, and other penalties.";
    cout << antiPlagiarism(text, fragment) << "%" << endl;
    return 0;
}

double antiPlagiarism(string text, string fragment)
{
    const int STEP = 3;
    int matchCounter = 0;
    int totalCounter = 0;

    vector<string> fragmentWords = getWords(fragment);
    vector<string> textWords = getWords(text);

    retraceTheShingles(fragmentWords, textWords, STEP, matchCounter, totalCounter);

    cout << "Matches: " << matchCounter << endl;
    cout << "Total: " << totalCounter << endl;

    return ((double)matchCounter / totalCounter) * 100;
}

vector<string> getWords(string input)
{
    vector<string> words = {};
    const int N = 96;
    int i = 0;
    char word[N];
    int iw = 0;
    for (i = 0; input[i] != '\0'; i++) {
        if (isJoinSeparator(input[i])) {
            continue;
        }
        if (!isSeparator(input[i])) {
            word[iw++] = tolower(input[i]);
            if (isSeparator(input[i + 1]) || input[i + 1] == '\0') {
                word[iw] = '\0';
                if (isWordOkay(word)) {
                    words.push_back(word);
                }
                iw = 0;
            }
        }
    }

    return words;
}

bool isSeparator(char symbol)
{
    const char SEPARATORS[] = " .,;:!?\"“”‘’()[]{}+*/=«»„“—–";
    for (int i = 0; SEPARATORS[i] != '\0'; i++) {
        if (symbol == SEPARATORS[i])
            return true;
    }

    return false;
}

bool isJoinSeparator(char symbol)
{
    return symbol == '\'' || symbol == '-';
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

void retraceTheShingles(vector<string> fragmentWords, vector<string> textWords, int step, int& matchCounter, int& totalCounter)
{
    int start = step - 1;
    for (int i = start; i < fragmentWords.size(); i++) {
        for (int j = start; j < textWords.size(); j++) {
            if (isSamplesEqual) {
                matchCounter++;
                break;
            }
        }
        totalCounter++;
    }
}

bool isSamplesEqual(int start, int firstIndex, int secondIndex, vector<string> fragmentWords, vector<string> textWords)
{
    int count = start;
    while (count >= 0) {
        if (fragmentWords[firstIndex - count] != textWords[secondIndex - count--]) {
            return false;
        }
    }

    return true;
}