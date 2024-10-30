#include <iostream>
#include <time.h>
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
         * Основную частЬ таблицы расширили и не получили новых строк =>
         * index_aux = index_aux_table - условие на запрос equivalence.
         **/
        while (table.index_aux < table.index_aux_table) {
            table.aux_insert();
            table.aux_pop();
        }
        response_equivalence = equivalence(table);
        if (!response_equivalence["response"].is_null()) {
            table.add_suffixes(response_equivalence["response"]);
            for (int i = 0; i < table.prefixes.size(); ++i) {
                table.prefixes[i].membership_row(table.suffixes);
            }
            table.aux_pop();
        }
    }

    Automata automata = table.make_automata();
    cout << "---- Итоговый автомат ----" << endl;
    automata.vis_automata();
    cout << "Кол-во состояний: " << table.index_aux_table << endl;

    time(&end);
    printf("Learner угадал автомат за: %f секунд\n", difftime(end, start));
    return 0;
}
