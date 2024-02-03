Transition::Transition(string sourceState, string destState, char symbol) :
    sourceState(sourceState),
    destState(destState),
    symbol(symbol)
{}

string Transition::getSourceState() const {
    return sourceState;
}

string Transition::getDestState() const {
    return destState;
}

char Transition::getSymbol() const {
    return symbol;
}
