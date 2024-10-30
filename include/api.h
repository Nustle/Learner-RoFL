#ifndef API_H
#define API_H

#include <nlohmann/json.hpp>
#include "table_aux.h"

using namespace std;
using json = nlohmann::json;

int membership(const string& word);
json equivalence(TableAux table);

#endif