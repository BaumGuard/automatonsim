#include<vector>
#include<string>
#include "Transition.hpp"
using namespace std;

bool contains(vector<string>& vec, string token) {
    bool found = false;

    for (uint i=0; i<vec.size(); i++) {
        if (vec[i].compare(token) == 0) {
            found = true;
            break;
        }
    }

    return found;
}


bool containsTransition(vector<Transition> vec, char symbol) {
    bool found = false;

    for (uint i=0; i<vec.size(); i++) {
        if (vec[i].getSymbol() == symbol) {
            found = true;
            break;
        }
    }

    return found;
}

bool containsSymbol(vector<char>& vec, char symbol) {
    bool found = false;

    for (uint i=0; i<vec.size(); i++) {
        if (vec[i] == symbol) {
            found = true;
            break;
        }
    }

    return found;
}



bool containsCombo(vector<vector<string>>& q, vector<string>& vec) {
    bool found = false;

    for (uint i=0; i<q.size(); i++) {
        if (q[i] == vec) {
            found = true;
            break;
        }
    }

    return found;
}

vector<string> uniqueVector (vector<string> vec) {
    vector<string> unique;

    for (uint i=0; i<vec.size(); i++) {
        if (!contains(unique, vec[i]))
            unique.push_back(vec[i]);
    }
    return unique;
}

