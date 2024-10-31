#include <iostream>
#include <fstream>
#include "include/utils.h"
#include <filesystem>

using namespace std;

vector<string> Alphabet {
        "L", "R"
};

void create_output_directory() {
    filesystem::path output_dir = "../output";
    if (!filesystem::exists(output_dir)) {
        try {
            filesystem::create_directories(output_dir);
        } catch (const filesystem::filesystem_error &e) {
            cerr << "Create directory failed: " << e.what() << "\n";
            return;
        }
    }
}

void Automata::vis_automata() {
    ofstream outfile("../output/automata.txt");
    if (!outfile.is_open()) {
        cerr << "Open file error.\n";
        return;
    }

    outfile << "digraph {\n";
    outfile << "\trankdir = LR\n";
    outfile << "\tstart [shape = point]\n";
    for (const string& state : final_states) {
        outfile << "\t" << state << " [shape = doublecircle]\n";
    }
    outfile << "\tstart -> " << start << "\n";

    for (pair<string, vector<string> > transition_pair : transition) {
        string state = transition_pair.first;
        vector<string> state_transition = transition_pair.second;

        if (state_transition[0] == state_transition[1]) {
            outfile << "\t" << state << " -> " << state_transition[0]
                 << " [label = \"" << alphabet[0] << ", " << alphabet[1] << "\"]\n";
        } else {
            outfile << "\t" << state << " -> " << state_transition[0]
                 << " [label = \"" << alphabet[0] << "\"]\n";
            outfile << "\t" << state << " -> " << state_transition[1]
                 << " [label = \"" << alphabet[1] << "\"]\n";
        }
    }
    outfile << "}\n";

    outfile.close();
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

string time(double elapsed_seconds) {
    string time_learning;
    int seconds = (int)(elapsed_seconds + 0.5);
    int hours = seconds / 3600;
    int minutes = (seconds % 3600) / 60;
    seconds %= 60;

    if (hours > 0) {
        time_learning += to_string(hours) + "h";
    }
    if (minutes > 0 || (hours > 0 && seconds > 0)) {
        time_learning += to_string(minutes) + "m";
    }
    if (seconds > 0 || (hours == 0 && minutes == 0)) {
        time_learning += to_string(seconds) + "s";
    }
    return time_learning;
}