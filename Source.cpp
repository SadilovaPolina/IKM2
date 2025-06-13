#include "header.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <windows.h>

using namespace std;

// Конструктор инициализирует слово
ListNode::ListNode(const string& w) : word(w), next(nullptr) {}

// Конструктор инициализирует список слов и выделяет память
ListChain::ListChain(const vector<string>& wordList) : words(wordList), head(nullptr) {
    if (wordList.empty()) {
        throw invalid_argument("Вы ничего не ввели!");
    }
    used.resize(words.size(), false);
}

 //Ообождение памяти от узлов списка
ListChain::~ListChain() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

// Метод получения последней буквы слова (игнорируя мягкий знак)
char ListChain::getLast(const string& word) {
    if (word.empty()) {
        throw runtime_error("Пустое слово в цепочке");
    }

    char last = word.back(); // Получаем последний символ
    if (last == 'ü') {
        if (word.length() > 1) {
            return word[word.length() - 2]; // Возвращаем предпоследний символ если последний 'ь'
        }
    }
    return last;
}

// Рекурсивный метод поиска цепочки слов
bool ListChain::findChain(int step) {
    if (step == words.size()) { //Если цепочка построена полностью
        try { // Проверяем замкнутость цепочки
            return (getLast(result.back()) == result.front()[0]);
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка при проверке цепочки: " << e.what() << endl;
            return false;
        }
    }

    // Определяем нужную букву для продолжения цепочки
    char neededChar = step == 0 ? '\0' : getLast(result[step - 1]);

    // Перебираем все слова
    for (size_t i = 0; i < words.size(); ++i) {
        if (!used[i]) { // Если слово еще не использовано
            // Если это первое слово или слово начинается с нужной буквы
            if (step == 0 || words[i][0] == neededChar) {
                used[i] = true;
                result.push_back(words[i]); // Добавляем слово в цепочку

                if (findChain(step + 1)) {
                    return true;
                }

                // Откат
                result.pop_back();
                used[i] = false;
            }
        }
    }

    return false;
}

// Метод для построения цепочки
bool ListChain::buildChain() {
    try {
        return findChain(0);
    }
    catch (const exception& e) {
        cerr << "Ошибка при построении цепочки: " << e.what() << endl;
        return false;
    }
}

// Вывод результата в файл
void ListChain::print(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Не удалось открыть файл " + filename + " для записи");
    }

    // Записываем цепочку в файл
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

// Результат
const vector<string>& ListChain::Result() const {
    return result;
}

// Функция разделения строки на слова
vector<string> split(const string& input) {
    if (input.empty()) {
        throw invalid_argument("Вы ничего не ввели!");
    }

    vector<string> words;
    string word;
    for (char ch : input) {
        if (isspace(ch)) {
            if (!word.empty()) {
                words.push_back(word); // Добавляем собранное слово
                word.clear();
            }
        }
        else {
            word += ch; // Собираем слово посимвольно
        }
    }
    if (!word.empty()) {
        words.push_back(word); // Добавляем последнее слово
    }
    return words;
}

// Сохранение строки в файл
void saveToFile(const string& filename, const string& input) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Не удалось открыть файл " + filename + " для записи");
    }
    outFile << input << endl;
    outFile.close();
}
