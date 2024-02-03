#pragma once
#include<string>

using namespace std;

class Transition {
public:

    Transition(string sourceState, string destState, char symbol);

    string getSourceState() const;
    string getDestState() const;
    char getSymbol() const;

private:
    string sourceState, destState;
    char symbol;
};

#include "Transition.cpp"
