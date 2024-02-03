#pragma once
#include<string>
using namespace std;

class AutomatonError {

};

class wrongStateType : public AutomatonError{
private:
    char stateType;
public:
    wrongStateType (char stateType) : stateType(stateType) {}
    char getWrongStateType() {return stateType;}
};

class noSuchState : public AutomatonError{
private:
    string errorState;

public:
    noSuchState(string errorState) : errorState(errorState) {};
    string getErrorState() {
        return errorState;
    }
};

class noSuchTransition : public AutomatonError {};

class stateAlreadyExists : public AutomatonError{};

class noStateTypeEntered : public AutomatonError{};

class noSuchMode : public AutomatonError{};
