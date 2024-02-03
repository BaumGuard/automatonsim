void Automaton::addState(string stateName, char stateType) {

    if (!(stateType == 's' || stateType == 'n' || stateType == 'f'))
        throw wrongStateType(stateType);

    states[stateName] = State(stateName, stateType);
    epsFreeStates[stateName] = State(stateName, stateType);

    switch (stateType) {
        case 's':
            startState = stateName;
            break;
        case 'f':
            endStates.push_back(stateName);
            endStatesEpsFree.push_back(stateName);
            break;
        }
}

void Automaton::removeState(string stateName) {

    if (states.count(stateName) == 0)
        throw noSuchState(stateName);

    states.erase(stateName);

    for (auto& stateIt : states) {
        for (uint a=0; a<stateIt.second.getTransitions().size(); a++) {
            if (stateIt.second.getTransitions()[a].getDestState() == stateName) {
                removeTransition(stateIt.second.getTransitions()[a].getSourceState(), stateIt.second.getTransitions()[a].getDestState(), stateIt.second.getTransitions()[a].getSymbol());
            }
        }
    }
}


void Automaton::addTransition(string sourceState, string destState, char symbol) {

    if (states.count(sourceState) == 0)
        throw noSuchState(sourceState);
    if (states.count(destState) == 0)
        throw noSuchState(destState);
    cout << symbol << '\n';

    states.find(sourceState)->second.addTransition(sourceState, destState, symbol);

    if (!containsSymbol(alphabet, symbol)) {
        alphabet.push_back(symbol);
    }

    if (symbol != 'e' && !containsSymbol(epsFreeAlphabet, symbol)) {
        epsFreeAlphabet.push_back(symbol);
    }

    if (symbol == 'e')
        epsilonFree = false;

    sort(alphabet.begin(), alphabet.end());
    sort(epsFreeAlphabet.begin(), epsFreeAlphabet.end());
}

void Automaton::removeTransition(string sourceState, string destState, char symbol) {
    states[sourceState].removeTransition(sourceState, destState, symbol);
}


vector<string> Automaton::getEpsilonClosure (string stateName) {
    vector<string> epsilonClosure;

    epsilonClosureInner(epsilonClosure, stateName);

    return epsilonClosure;
}


void Automaton::makeEpsilonFree() {
    for (auto& stateIt : states) {
        for (uint a=0; a<epsFreeAlphabet.size(); a++) {
            vector<string> epsClos = getEpsilonClosure(stateIt.second.getStateName());

            vector<string> transStates;



            for (uint b=0; b<epsClos.size(); b++) {
                for (uint c=0; c<states[epsClos[b]].getTransitions().size(); c++) {
                    if (states[epsClos[b]].getTransitions()[c].getSymbol() == epsFreeAlphabet[a])
                        transStates.push_back(states[epsClos[b]].getTransitions()[c].getDestState());
                }
            }

            vector<string> newStates;

            for (uint i=0; i<transStates.size(); i++) {
                vector<string> tempStates = getEpsilonClosure(transStates[i]);
                newStates.reserve( newStates.size() + tempStates.size() );
                newStates.insert( newStates.end(), tempStates.begin(), tempStates.end() );
            }

            for (uint i=0; i<newStates.size(); i++) {
                epsFreeStates[stateIt.second.getStateName()].addTransition(stateIt.second.getStateName(), newStates[i], epsFreeAlphabet[a]);
            }
        }

        for (uint i=0; i<stateIt.second.getTransitions().size(); i++) {
            if (stateIt.second.getTransitions()[i].getSymbol() == 'e') {
                if (states[stateIt.second.getTransitions()[i].getDestState()].getStateType() == 'f') {
                    epsFreeStates[stateIt.second.getStateName()].setStateType('f');
                    endStatesEpsFree.push_back(stateIt.second.getStateName());
                }
            }
        }
    }

    madeEpsFree = true;

}

bool Automaton::isEpsilonFree() const {
    return epsilonFree;
}


vector<string> Automaton::printTransitions(string state, char symbol) {
    vector<string> trans;

    for (uint i=0; i<epsFreeStates[state].getTransitions().size(); i++) {
        if (epsFreeStates[state].getTransitions()[i].getSymbol() == symbol && !contains(trans, epsFreeStates[state].getTransitions()[i].getDestState()))
            trans.push_back(epsFreeStates[state].getTransitions()[i].getDestState());
    }

    return trans;
}


bool Automaton::isDeterministicEndState (vector<string> vec) const {
    bool found = false;

    for (uint i=0; i<vec.size(); i++) {
        for (uint j=0; j<endStatesEpsFree.size(); j++) {
            if (vec[i] == endStatesEpsFree[j]) {
                found = true;
                break;
            }
        }
    }

    return found;
}


void Automaton::makeDeterministic() {

    if (!isEpsilonFree())
        makeEpsilonFree();

    queue<vector<string>> comboQueue;
    vector<vector<string>> comboHistory;

    vector<string> startCombo;
    startCombo.push_back(startState);
    comboQueue.push(startCombo);

    int stateCount = 0;

    vector<vector<string>*> dfaStates;

    while (!comboQueue.empty()) {
        vector<string>* stateLine = new vector<string>[epsFreeAlphabet.size()+1];
        stateLine[0] = comboQueue.front();

        for (uint b=0; b<epsFreeAlphabet.size(); b++) {

            vector<string> curCombo;

            for (uint a=0; a<comboQueue.front().size(); a++) {

                vector<string> tempStates = printTransitions(comboQueue.front()[a], epsFreeAlphabet[b]);

                if (!tempStates.empty())
                    curCombo.insert(curCombo.end(), tempStates.begin(), tempStates.end());



            }
            curCombo = uniqueVector(curCombo);
            sort(curCombo.begin(), curCombo.end());
            stateLine[b+1] = curCombo;

                if (!containsCombo(comboHistory, curCombo) && !curCombo.empty()) {
                    comboQueue.push(curCombo);
                    comboHistory.push_back(curCombo);
                }

        }
        comboQueue.pop();
        dfaStates.push_back(stateLine);
        stateCount++;
    }

    string newStateTable[stateCount][epsFreeAlphabet.size()+1];

    vector<char> dfaEndStates;

    for (int a=0; a<stateCount; a++) {

        vector<string> stateToken = dfaStates[a][0];
        newStateTable[a][0] = "q"+to_string(a);

        for (int b=0; b<stateCount; b++) {
            for (uint c=1; c<= epsFreeAlphabet.size(); c++) {
                if (dfaStates[b][c] == stateToken) {
                    newStateTable[b][c] = "q"+to_string(a);
                }
            }
        }

        if (isDeterministicEndState(stateToken))
            dfaEndStates.push_back('f');
        else
            dfaEndStates.push_back('n');
    }


    dfaEndStates[0] = 's';

    for (int a=0; a<stateCount; a++) {
        deterministicStates[newStateTable[a][0]].setStateName(newStateTable[a][0]);
        deterministicStates[newStateTable[a][0]].setStateType(dfaEndStates[a]);
        for (uint b=0; b<epsFreeAlphabet.size(); b++) {
            if (newStateTable[a][b+1].length() > 0)
                deterministicStates[newStateTable[a][0]].addTransition(newStateTable[a][0], newStateTable[a][b+1], epsFreeAlphabet[b]);
        }
    }

    startStateDeterministic = "q0";
    madeDeterministic = true;

}

bool Automaton::isDeterministic() const {

    bool det = true;

    for (auto& stateIt : states) {
        for (uint a=0; a<alphabet.size(); a++) {

            int count = 0;
            for (uint b=0; b<stateIt.second.getTransitions().size(); b++) {
                if (stateIt.second.getTransitions()[b].getSymbol() == alphabet[a])
                    count++;
            }

            if (count > 1) {
                det = false;
                break;
            }
        }

    }

    return det;
}


void Automaton::minimizeDFA() {

    if (!isEpsilonFree())
        makeEpsilonFree();
    if (!isDeterministic())
        makeDeterministic();

    vector<vector<string>> equiGroups;
    vector<string> testvec;
    equiGroups.push_back(testvec);
    equiGroups.push_back(testvec);

    for (auto& stateIt : deterministicStates) {
        if (stateIt.second.getStateType() == 's' || stateIt.second.getStateType() == 'n')
            equiGroups[0].push_back(stateIt.second.getStateName());
        else
            equiGroups[1].push_back(stateIt.second.getStateName());
    }

    vector<vector<string>> recentGroups;

    while (recentGroups != equiGroups) {

        recentGroups = equiGroups;
        vector<vector<string>> tempGroups;

        int it = 0;
        for (uint a = 0; a<equiGroups.size(); a++) {

            vector<string> group1, group2;

            for (uint b = 0; b<equiGroups[a].size(); b++) {

                if (deterministicStates[equiGroups[a][b]].getTransitions().size() == 0)
                    group1.push_back(equiGroups[a][b]);

                else {

                    for (uint c = 0; c<deterministicStates[equiGroups[a][b]].getTransitions().size(); c++) {

                        if (!contains(equiGroups[a], deterministicStates[equiGroups[a][b]].getTransitions()[c].getDestState())) {
                            group2.push_back(equiGroups[a][b]);
                        }
                        else {
                            group1.push_back(equiGroups[a][b]);
                        }
                    }
                }
            }

            group1 = uniqueVector(group1);
            group2 = uniqueVector(group2);

            tempGroups.push_back(group1);
            tempGroups.push_back(group2);

        }

        equiGroups.clear();

        for (int i=0; i<tempGroups.size(); i++) {
            if (tempGroups[i].size() > 0)
                equiGroups.push_back(tempGroups[i]);
        }

    }


    for (int a=0; a<equiGroups.size(); a++) {

        minimalStates["q"+to_string(a)] = State("q"+to_string(a), deterministicStates[equiGroups[a][0]].getStateType());

        for (int b=0; b<deterministicStates[equiGroups[a][0]].getTransitions().size(); b++) {

            int index = 0;

            for (int c=0; c<equiGroups.size(); c++) {
                bool found = false;
                for (int d=0; d<equiGroups[c].size(); d++) {

                    if (equiGroups[c][d] == deterministicStates[equiGroups[a][0]].getTransitions()[b].getDestState()) {
                        found = true;
                        break;
                    }
                }

                if (found == true) {
                    index = c;
                    break;
                }
            }

            minimalStates["q"+to_string(a)].addTransition("q"+to_string(a), "q"+to_string(index), deterministicStates[equiGroups[a][0]].getTransitions()[b].getSymbol());
        }
    }

}


void Automaton::printDescription(string type) const {

    map<string, State> mapReference;

    if (type.compare("original")==0)
        mapReference = states;
    else if (type.compare("epsilon-free")==0)
        mapReference = epsFreeStates;
    else if (type.compare("deterministic")==0)
        mapReference = deterministicStates;
    else if (type.compare("minimal")==0)
        mapReference = minimalStates;
    else
        throw noSuchMode();

    cout << "Alphabet:\n";

    for (uint i=0; i<epsFreeAlphabet.size(); i++) {
        cout << epsFreeAlphabet[i] << ' ';
    }
    cout << '\n';

    cout << "\nStates:\n";

    for (auto& stateIt : mapReference) {
        cout << stateIt.second.getStateName() << ' ' << stateIt.second.getStateType() << '\n';
    }

    cout << "\nTransitions:\n";

    for (auto stateIt : mapReference) {
        for (uint i=0; i < stateIt.second.getTransitions().size(); i++) {
            cout << stateIt.second.getTransitions()[i].getSourceState() << ' ' << stateIt.second.getTransitions()[i].getDestState() << ' ' << stateIt.second.getTransitions()[i].getSymbol() << '\n';
        }
    }
}


bool Automaton::checkWord (string word) {

    string currentState;

    uint it = 0;

    if (isDeterministic() && isEpsilonFree())
        currentState = startState;
    else {
        makeEpsilonFree();
        makeDeterministic();
        currentState = startStateDeterministic;
    }

    for (uint i=0; i<word.length(); i++) {

        int transitionIndex;

        if (isDeterministic() && isEpsilonFree())
            transitionIndex = getTransitionIndex(states, currentState, word[i]);
        else
            transitionIndex = getTransitionIndex(deterministicStates, currentState, word[i]);

        if (transitionIndex != -1) {
            if (isDeterministic() && isEpsilonFree()) {
                if (containsTransition(states[currentState].getTransitions(), word[i]))
                    currentState = states[currentState].getTransitions()[transitionIndex].getDestState();
                else
                    break;
            }
            else {
                if (containsTransition(deterministicStates[currentState].getTransitions(), word[i]))
                    currentState = deterministicStates[currentState].getTransitions()[transitionIndex].getDestState();
                else
                    break;
            }
        }

        it++;

    }

    if (isDeterministic() && isEpsilonFree()) {
        if (states[currentState].getStateType() == 'f' && it == word.length())
            return true;
        else
            return false;
    }
    else {
        if (deterministicStates[currentState].getStateType() == 'f' && it == word.length())
            return true;
        else
            return false;
    }

}



void Automaton::epsilonClosureInner (vector<string>& epsilonClosure, string stateName) {
    if (!contains(epsilonClosure, stateName)) {
        epsilonClosure.push_back(stateName);

        for (uint i=0; i<states[stateName].getTransitions().size(); i++) {
            if (states[stateName].getTransitions()[i].getSymbol() == 'e') {
                epsilonClosureInner(epsilonClosure, states[stateName].getTransitions()[i].getDestState());
            }
        }
    }
}


int Automaton::getTransitionIndex(map<string, State>& stateMap, string state, char symbol) {
    bool exists = -1;

    for (uint i=0; i<stateMap[state].getTransitions().size(); i++) {
        if (stateMap[state].getTransitions()[i].getSymbol() == symbol) {
            exists = i;
            break;
        }
    }

    return exists;
}
