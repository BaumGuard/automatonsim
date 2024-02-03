string State::getStateName() const {
    return stateName;
}

char State::getStateType() const {
    return stateType;
}

vector<Transition> State::getTransitions() const {
    return transitions;
}

void State::setStateType(char stateType) {
    this->stateType = stateType;
}

void State::setStateName(string stateName) {
    this->stateName = stateName;
}

State::State(string stateName, char stateType) :
    stateName(stateName),
    stateType(stateType)
    {}


void State::addTransition(string sourceState, string destState, char symbol) {
    transitions.push_back(Transition(sourceState, destState, symbol));
}

void State::removeTransition(string sourceState, string destState, char symbol) {
    bool removeSuccessful = false;

    for (uint a=0; a<transitions.size(); a++) {
        if (transitions[a].getDestState() == destState && transitions[a].getSymbol() == symbol) {
            transitions.erase(transitions.begin() + a);
            removeSuccessful = true;
            break;
        }
    }

    if (removeSuccessful == false)
        throw noSuchTransition();
}
