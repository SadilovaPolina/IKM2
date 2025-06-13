#pragma once

#include <string>
#include <vector>

using namespace std;

class ListNode {
public:
    string word;
    ListNode* next;

    ListNode(const string& w);
};

class ListChain {
private:
    ListNode* head;
    vector<string> words;
    vector<bool> used;
    vector<string> result;

    char getLast(const string& word);
    bool findChain(int step);

public:
    ListChain(const vector<string>& wordList);
    ~ListChain();
    bool buildChain();
    void print(const string& filename);
    const vector<string>& Result() const;
};

vector<string> split(const string& input);
void saveToFile(const string& filename, const string& input);

