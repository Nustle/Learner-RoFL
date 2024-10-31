#include "include/table_aux.h"
#include "include/utils.h"
#include "include/api.h"
#include <algorithm>

using namespace std;

Prefix::Prefix(const string& prefix) {
    this->prefix = prefix;
}

void Prefix::membership_row(vector<string> suffixes, unordered_map<string, int>& membership_cache) {
    int suffix_end = (int)suffixes.size();
    for (int j = suffix_size; j < suffix_end; ++j) {
        int word_membership;
        const string& suffix = suffixes[j];
        string word = concat(prefix, suffix);
        auto word_cache = membership_cache.find(word);
        if (word_cache != membership_cache.end()) {
            word_membership = word_cache->second;
        }  else {
            word_membership = membership(word);
            membership_cache[word] = word_membership;
        }
        row.push_back(word_membership);
    }
    suffix_size = suffix_end;
}

TableAux::TableAux() {
    prefixes.push_back(Prefix("ε"));
    prefixes_unique["ε"] = true;
    index_aux_table++;
    suffixes.push_back("ε");
    suffixes_unique["ε"] = true;
    prefixes[0].membership_row(suffixes, membership_cache);
}

void TableAux::aux_insert() {
    /** Расширяем префикс с номера, равному 1-ому префиску, который не расширялся - index_aux. **/
    for (int i = index_aux; i < index_aux_table; ++i) {
        string prefix = prefixes[i].prefix;
        for (const string& letter : Alphabet) {
            Prefix prefix_aux = Prefix(concat(prefix, letter));

            /** Проверка на уникальность префикса в таблице. **/
            if (prefixes_unique.find(prefix_aux.prefix) == prefixes_unique.end()) {
                prefixes_unique[prefix_aux.prefix] = true;
                prefix_aux.membership_row(suffixes, membership_cache);
                prefixes.push_back(prefix_aux);
            }
        }
    }
    /** Все префиксы из текущей основной части таблицы были расширены. **/
    index_aux = index_aux_table;
}

void TableAux::aux_pop() {
    /** Фиксируем начало расширенной таблицы. **/
    int start_aux = index_aux_table;

    /**
     * Начинаем с индекса, равного фиксированному началу расширенной части таблицы.
     * **/
    for (int i = start_aux; i < prefixes.size(); ++i) {
        Prefix prefix_aux = prefixes[i];
        bool in_table = false;

        /** Начало расширенной таблицы могло сдвинуться, поэтому index_aux_table, а не start_aux. **/
        for (int j = 0; j < index_aux_table; ++j) {
            Prefix prefix_main = prefixes[j];
            if (compare_rows(prefix_aux.row, prefix_main.row)) {
                in_table = true;
                break;
            }
        }

        /** Строка из расширенной таблицы - уникальная, а значит должна попасть в основную часть. **/
        if (!in_table) {
            swap(prefixes[i], prefixes[index_aux_table]);

            /** Сдвигаем границу расширенной таблицы. **/
            index_aux_table++;
        }
    }
}

void TableAux::add_suffixes(string response) {
    string suffix;
    for (int j = (int)response.size() - 1; j >= 0; --j) {
        suffix = response[j] + suffix;

        /** Проверка на уникальность суффикса в таблице. **/
        if (suffixes_unique.find(suffix) == suffixes_unique.end()) {
            suffixes.push_back(suffix);
            suffixes_unique[suffix] = true;
        }
    }
}

Automata TableAux::make_automata() {
    unordered_map<string, vector<int> > main_prefixes;

    /**
     * Каждому префиксу из расширенной части таблицы ставим в соответствие эквивалентный
     * ему префикс из основной части таблицы по отношению Майхилла-Нероуда.
     * **/
    unordered_map<string, string> aux_prefixes;

    for (int i = 0; i < index_aux_table; ++i) {
        main_prefixes[prefixes[i].prefix] = prefixes[i].row;
    }
    for (int i = index_aux_table; i < prefixes.size(); ++i) {
        vector<int> aux_row = prefixes[i].row;
        for (pair<string, vector<int> > main_prefix : main_prefixes) {
            if (compare_rows(aux_row, main_prefix.second)) {
                aux_prefixes[prefixes[i].prefix] = main_prefix.first;
                break;
            }
        }
    }

    Automata automata;
    for (pair<string, vector<int> > main_prefix : main_prefixes) {
        automata.transition[main_prefix.first];
        if (main_prefixes[main_prefix.first][0] == 1) {
            automata.final_states.push_back(main_prefix.first);
        }
        for (const string& letter : Alphabet) {
            string state = concat(main_prefix.first, letter);

            /** Проверка на принадлежность префикса основной части таблицы. **/
            if (main_prefixes.find(state) != main_prefixes.end()) {
                automata.transition[main_prefix.first].push_back(state);
            } else {

                /** Заменяем на эквивалентное слово. **/
                automata.transition[main_prefix.first].push_back(aux_prefixes[state]);
            }
        }
    }

    return automata;
}
