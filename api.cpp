#include <iostream>
#include <cpr/cpr.h>
#include "include/api.h"
#include "include/utils.h"
#include <thread>
#include <chrono>

using namespace std;
using json = nlohmann::json;

string url = "http://127.0.0.1:8095";

int membership(const string& word) {
    try {
        cpr::Response response = cpr::Post(
            cpr::Url{url + "/checkWord"},
            cpr::Header{{"Content-Type", "application/json"}},
            cpr::Body{json{{"word", word}}.dump()}
        );
        if (response.status_code == 200) {
            json json_response = json::parse(response.text);

            /** Таймаут для избежания сетевых ошибок, связанных с исчерпанием системных ресурсов. **/
            this_thread::sleep_for(std::chrono::milliseconds(3));
            return json_response["response"] ? 1 : 0;
        } else {
            cerr << "Check word error " << response.status_code << ": " << response.text << endl;
            return -1;
        }
    } catch (const exception& e) {
        cerr << "Check word failed: " << e.what() << endl;
        return -1;
    }
}

json equivalence(TableAux table) {
    try {
        json eq;
        eq["main_prefixes"] = "";
        eq["non_main_prefixes"] = "";
        eq["suffixes"] = array_to_string(table.suffixes);
        eq["table"] = "";

        string main_prefixes, non_main_prefixes, json_table;

        for (int i = 0; i < table.index_aux_table; ++i) {
            Prefix p = table.prefixes[i];
            main_prefixes += (p.prefix + " ");
            json_table += array_to_string(p.row);
        }
        main_prefixes.pop_back();

        for (int i = table.index_aux_table; i < table.prefixes.size(); ++i) {
            Prefix p_aux = table.prefixes[i];
            non_main_prefixes += (p_aux.prefix + " ");
            json_table += array_to_string(p_aux.row);
        }
        non_main_prefixes.pop_back();
        json_table.pop_back();

        eq["main_prefixes"] = main_prefixes;
        eq["non_main_prefixes"] = non_main_prefixes;
        eq["table"] = json_table;

        cpr::Response response = cpr::Post(
                cpr::Url{url + "/checkTable"},
                cpr::Header{{"Content-Type", "application/json"}},
                cpr::Body{eq.dump()}
        );

        if (response.status_code == 200) {
            json json_response = json::parse(response.text);
            return json_response;
        } else {
            cerr << "Check table error " << response.status_code << ": " << response.text << endl;
            return -1;
        }
    } catch (const exception& e) {
        cerr << "Check table failed: " << e.what() << endl;
        return json{{"error", string("Check table failed: ") + e.what()}};
    }
}

