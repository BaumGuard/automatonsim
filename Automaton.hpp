#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<queue>
#include<iostream>
#include "State.hpp"
#include "Transition.hpp"
#include "Automaton_aux.hpp"
#include "AutomatonError.hpp"
using namespace std;

class Automaton {

public:
    /*
    Adding a new state to the automaton
    stateType:
     - s (Starting state)
     - n (Neutral state)
     - f (Finite state)
    */
    void addState(string stateName, char stateType);

    /*
    Adding a transition state from one state (sourceState) to another (destState)
    symbol: e is reserved for the epsilon (empty word)
    */
    void addTransition(string sourceState, string destState, char symbol); // Adding a transition to the automaton

    void removeState(string stateName); // Removing a state from the automaton
    void removeTransition(string sourceState, string destState, char symbol); // Removing a transition from the automaton

    /*
    Printing the description of the automaton including its alphabet, states and transitions
    Arguments:
    - original        Print the description of the automaton created by the user
    - epsilon-free    Print the description of the automaton that has been made epsilon-free
    - deterministic   Print the description of the DFA created from the epsilon-free NFA
    - minimal         Print the description of the minimal DFA
    */
    void printDescription(string type) const;

    // Determine the epsilon closure of a certain state
    vector<string> getEpsilonClosure (string stateName);

    void makeEpsilonFree(); // Transform the automaton created by the user into an epsilon-free NFA
    void makeDeterministic(); // Transform the epsilon-free NFA into an DFA
    void minimizeDFA();

    bool isEpsilonFree() const; // Check if the automaton created by the user is epsilon-free
    bool isDeterministic() const; // Check if the automaton created by the user is deterministic

    vector<string> printTransitions(string state, char symbol); // Get the transitions for a certain state on reading a certain symbol

    bool checkWord (string word); // Check if the automaton accepts a certain word



private:
    int numberOfStates = 0;
    map<string, State> states; // Map of the states of the automaton created by the user
    map<string, State> epsFreeStates; // Map of the states of the epsilon-free NFA
    map<string, State> deterministicStates; // Map of the states of the DFA
    map<string, State> minimalStates;

    bool madeEpsFree = false; // If the function 'makeEpsilonFree()' has been executed, the value becomes true
    bool madeDeterministic = false; // If the function 'makeDeterministic()' has been executed, the value becomes true

    string startState; // Starting state of the automaton created by the user
    string startStateDeterministic; // Starting state of the DFA
    vector<string> endStates; // Vector of finite states of the automaton created by the user
    vector<string> endStatesEpsFree; // Vector of finite states of the epsilon-free NFA

    bool isDeterministicEndState (vector<string> vec) const;

    vector<char> alphabet; // Alphabet of the automaton (with epsilon)
    vector<char> epsFreeAlphabet; // Alphabet of the automaton (without epsilon)

    bool epsilonFree = true; // If the user creates a transition on reading an epsilon, the value becomes false


    void epsilonClosureInner (vector<string>& epsilonClosure, string stateName); // Inner function for hiding the recursion

    int getTransitionIndex(map<string, State>& stateMap, string state, char symbol); // Get the vector index of a transition from a specified state map

};


#include "Automaton.cpp"
