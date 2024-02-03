#include "Automaton.hpp"
#include<sstream>

vector<string> splitString(string input) {
    vector<string> result;
    istringstream iss(input);
    string token;

    while (iss >> token) {
        result.push_back(token);
    }

    return result;
}


int main () {

    Automaton a;

    string command = "start";

    do {
        cout << "> ";
        getline(cin, command);

        vector<string> parsed_input = splitString(command);

        if (parsed_input.size() == 0)
            continue;

        if (parsed_input[0].compare("state") == 0) {
            for (uint i=1; i<parsed_input.size(); i+=2) {
                try {
                a.addState(parsed_input[i], parsed_input[i+1][0]);
                cout << parsed_input[i] << " : Added state(s) successfully\n";
                }
                catch (wrongStateType wst) {cout << wst.getWrongStateType() << " : Wrong state type\n";}
            }
            cout << '\n';
        }
        else if (parsed_input[0].compare("transition") == 0) {
            if (parsed_input.size() < 4)
                cout << "No transition symbol entered\n\n";
            else {
                try {
                a.addTransition(parsed_input[1], parsed_input[2], parsed_input[3][0]);
                cout << "Added transition successfully\n\n";
                }
                catch (noSuchState nss) {cout << nss.getErrorState() << " : No such state\n";}
            }
        }
        else if (parsed_input[0].compare("description") == 0) {
            cout << '\n';
            a.printDescription("original");
            cout << '\n';
        }
        else if (command.compare("make epsilon free") == 0) {
            a.makeEpsilonFree();
            cout << "Made epsilon-free successfully\n\n";
        }
        else if (command.compare("epsilon free description") == 0) {
            cout << '\n';
            a.printDescription("epsilon-free");
            cout << '\n';
        }
        else if (parsed_input[0].compare("epsilon") == 0 && parsed_input[1].compare("closure") == 0) {
            cout << '\n';
            vector<string> epsClos = a.getEpsilonClosure(parsed_input[2]);
            for (uint i=0; i<epsClos.size(); i++)
                cout << epsClos[i] << ' ';
            cout << '\n';
        }
        else if (parsed_input[0].compare("check") == 0) {
            (a.checkWord(parsed_input[1]))? (cout << "Accepted\n") : (cout << "Not accepted\n");
        }
        else if (parsed_input[0].compare("minimize") == 0) {
            a.minimizeDFA();
        }
        else if (parsed_input[0].compare("deterministic") == 0 && parsed_input[1].compare("description")==0) {
            a.printDescription("deterministic");
        }
        else if (parsed_input[0].compare("minimal") == 0 && parsed_input[1].compare("description")==0) {
            a.printDescription("minimal");
        }
        else if (command.compare("exit") == 0) {
            break;
        }
        else {
            cout << command << " : Invalid command\n";
        }

    }

    while (command.compare("exit"));


}
