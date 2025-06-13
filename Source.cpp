#include "header.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <windows.h>

using namespace std;

ListNode::ListNode(const string& w) : word(w), next(nullptr) {}

ListChain::ListChain(const vector<string>& wordList) : words(wordList), head(nullptr) {
    if (wordList.empty()) {
        throw invalid_argument("�� ������ �� �����!");
    }
    used.resize(words.size(), false);
}

ListChain::~ListChain() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

char ListChain::getLast(const string& word) {
    if (word.empty()) {
        throw runtime_error("������ ����� � �������");
    }

    char last = word.back();
    if (last == '�') {
        if (word.length() > 1) {
            return word[word.length() - 2];
        }
    }
    return last;
}

bool ListChain::findChain(int step) {
    if (step == words.size()) {
        try {
            return (getLast(result.back()) == result.front()[0]);
        }
        catch (const runtime_error& e) {
            cerr << "������ ��� �������� �������: " << e.what() << endl;
            return false;
        }
    }

    char neededChar = step == 0 ? '\0' : getLast(result[step - 1]);

    for (size_t i = 0; i < words.size(); ++i) {
        if (!used[i]) {
            if (step == 0 || words[i][0] == neededChar) {
                used[i] = true;
                result.push_back(words[i]);

                if (findChain(step + 1)) {
                    return true;
                }

                result.pop_back();
                used[i] = false;
            }
        }
    }

    return false;
}

bool ListChain::buildChain() {
    try {
        return findChain(0);
    }
    catch (const exception& e) {
        cerr << "������ ��� ���������� �������: " << e.what() << endl;
        return false;
    }
}

void ListChain::print(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("�� ������� ������� ���� " + filename + " ��� ������");
    }

    for (size_t i = 0; i < result.size(); ++i) {
        outFile << result[i];
        if (i != result.size() - 1) {
            outFile << " ";
        }
    }
    outFile << endl;

    outFile << " ^~^  ,\n('Y') )\n/   \\/ \n(\\|||/)";

    outFile.close();
}

const vector<string>& ListChain::Result() const {
    return result;
}

vector<string> split(const string& input) {
    if (input.empty()) {
        throw invalid_argument("�� ������ �� �����!");
    }

    vector<string> words;
    string word;
    for (char ch : input) {
        if (isspace(ch)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else {
            word += ch;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

void saveToFile(const string& filename, const string& input) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("�� ������� ������� ���� " + filename + " ��� ������");
    }
    outFile << input << endl;
    outFile.close();
}