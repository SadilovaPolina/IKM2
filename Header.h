#pragma once

#include <string>
#include <vector>

using namespace std;

// Класс узла связного списка
class ListNode {
public:
    string word; // Слово, хранящееся в узле
    ListNode* next;

    ListNode(const string& w);
};

// Класс для работы с цепочкой слов
class ListChain {
private:
    ListNode* head;
    vector<string> words; // Вектор всех слов для построения цепочки
    vector<bool> used;
    vector<string> result;

// Получить последнюю букву слова
    char getLast(const string& word);
// Рекурсивная функция для поиска цепочки
    bool findChain(int step);

public:
// Конструктор, принимающий список слов
    ListChain(const vector<string>& wordList);
    ~ListChain();
// Построить цепочку слов
    bool buildChain();
// Вывести результат в файл
    void print(const string& filename);
    const vector<string>& Result() const;
};

// Функция для разделения строки на слова
vector<string> split(const string& input);
// Функция для сохранения строки в файл
void saveToFile(const string& filename, const string& input);

