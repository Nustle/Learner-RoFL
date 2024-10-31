#ifndef TABLE_AUX_H
#define TABLE_AUX_H

#include "utils.h"

using namespace std;

class Prefix {
public:
    string prefix;
    vector<int> row;

    Prefix(const string& prefix);

    /**
     * Заполняет строку текущего префикса значениями 0 и 1 в таблице Майхилла-Неурода.
     **/
    void membership_row(vector<string> suffixes, unordered_map<string, int>& membership_cache);
private:
    /**
     * При добавлении нового суффикса в таблицу, дополняем строку таблицы текущего префикса
     * с столбца, имеющего индекс suffix_size.
     **/
    int suffix_size = 0;
};

class TableAux {
public:
    vector<Prefix> prefixes;
    vector<string> suffixes;
    unordered_map<string, int> membership_cache;

    /**
     * Индекс последнего префикса в таблице, который был расширен символами алфавита L и R.
     * **/
    int index_aux = 0;

    /**
     * Индекс строки, с которой начинается расширенная таблица.
     * **/
    int index_aux_table = 0;

    TableAux();

    /**
     * Добавляет новые префиксы в расширенную часть таблицы: к префиксам из основной части таблицы добавляются L и R.
     * Добавленные строки заполняются значениями 0 и 1 в таблице Майхилла-Нероуда.
     * **/
    void aux_insert();

    /**
     * Функция проверки на противоречивость.
     * Переносит строки из расширенной части таблицы в основную, если их нет в основной.
     * **/
    void aux_pop();

    /**
     * Добавляем в таблицу всевозможные суффиксы слова, не входящего в мой язык, который вернул МАТ.
     * **/
    void add_suffixes(string response);
    Automata make_automata();
private:
    unordered_map<string, bool> prefixes_unique, suffixes_unique;
};

#endif