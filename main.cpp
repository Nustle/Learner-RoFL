#include <iostream>
#include <ctime>
#include "include/api.h"

using namespace std;

int main() {
    time_t start, end;
    time(&start);
    cout << "Start learning..." << endl;

    TableAux table;
    json response_equivalence = {
            {"type", ""},
            {"response", ""}
    };
    while (!response_equivalence["type"].is_null() && !response_equivalence["response"].is_null()) {
        /**
         * Основную часть таблицы расширили и не получили новых строк =>
         * index_aux = index_aux_table - условие на запрос equivalence.
         **/
        while (table.index_aux < table.index_aux_table) {
            table.aux_insert();
            table.aux_pop();
        }
        cout << "Количество состояний угадано: " << table.index_aux_table << endl;
        cout << "----------------------------" << endl;
        response_equivalence = equivalence(table);
        if (!response_equivalence["response"].is_null()) {
            table.add_suffixes(response_equivalence["response"]);
            for (int i = 0; i < table.prefixes.size(); ++i) {
                table.prefixes[i].membership_row(table.suffixes, table.membership_cache);
            }
            table.aux_pop();
        }
    }

    Automata automata = table.make_automata();

    create_output_directory();
    automata.vis_automata();
    automata.generate_image();
    cout << "Итоговый автомат сохранён в output." << endl;
    cout << "Кол-во состояний: " << table.index_aux_table << endl;

    time(&end);
    cout << "Learner угадал лабиринт за: " << time(difftime(end, start)) << endl;
    return 0;
}