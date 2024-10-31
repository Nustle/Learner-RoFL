#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

extern vector<string> Alphabet;

class Automata {
public:
    vector<string> alphabet = Alphabet;
    string start = "ε";

    unordered_map<string, vector<string> > transition;
    vector<string> final_states;

    void vis_automata();
    void generate_image();
};

string concat(string prefix, string suffix);

bool compare_rows(vector<int> row_aux, vector<int> row_main);

template <typename T>
string array_to_string(vector<T> a) {
    ostringstream ans;
    for (T elem : a) {
        ans << elem << " ";
    }
    return ans.str();
}

void create_output_directory();

string time(double elapsed_seconds);
#endif