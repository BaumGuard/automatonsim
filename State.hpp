#include<vector>
#include<string>
#include<vector>
#include "Transition.hpp"
#ifndef ERROR
#define ERROR
#include "AutomatonError.hpp"
#endif
using namespace std;

class State {
public:
    string getStateName() const;
    char getStateType() const;
    vector<Transition> getTransitions () const;

    void setStateName(string stateName);
    void setStateType(char stateType);

    State(string stateName, char stateType);

    State() {}

    void addTransition(string sourceState, string destState, char symbol);
    void removeTransition(string sourceState, string destState, char symbol);


private:
    vector<Transition> transitions;
    string stateName;
    char stateType;
};

#include "State.cpp"
