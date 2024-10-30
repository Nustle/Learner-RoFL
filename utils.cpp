#include <iostream>
#include "include/utils.h"

using namespace std;

vector<string> Alphabet {
        "L", "R"
};

void Automata::vis_automata() {
    cout << "digraph {\n";
    cout << "\trankdir = LR\n";
    cout << "\tstart [shape = point]\n";
    for (const string& state : final_states) {
        cout << "\t" << state << " [shape = doublecircle]\n";
    }
    cout << "\tstart -> " << start << "\n";

    for (pair<string, vector<string> > transition_pair : transition) {
        string state = transition_pair.first;
        vector<string> state_transition = transition_pair.second;

        if (state_transition[0] == state_transition[1]) {
            cout << "\t" << state << " -> " << state_transition[0]
                 << " [label = \"" << alphabet[0] << ", " << alphabet[1] << "\"]\n";
        } else {
            cout << "\t" << state << " -> " << state_transition[0]
                 << " [label = \"" << alphabet[0] << "\"]\n";
            cout << "\t" << state << " -> " << state_transition[1]
                 << " [label = \"" << alphabet[1] << "\"]\n";
        }
    }
    cout << "}\n";
}

string concat(string prefix, string suffix) {
    if (prefix == "ε") {
        return suffix;
    } else if (suffix == "ε") {
        return prefix;
    } else {
        return prefix + suffix;
    }
}

bool compare_rows(vector<int> row_aux, vector<int> row_main) {
    for (int i = 0; i < row_aux.size(); ++i) {
        if (row_aux[i] != row_main[i]) {
            return false;
        }
    }
    return true;
}