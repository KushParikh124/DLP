#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int no_inp_symbols;
    cout << "Enter the number of input symbols: ";
    cin >> no_inp_symbols;

    vector<char> inp_symbols(no_inp_symbols);
    for (int i = 0; i < no_inp_symbols; i++) {
        cout << "Enter the " << i + 1 << "th input symbol: ";
        cin >> inp_symbols[i];
    }

    int states;
    cout << "Enter the number of states: ";
    cin >> states;

    int initial_state;  
    cout << "Enter the initial state: ";
    cin >> initial_state;

    int accepting_states;
    cout << "Enter the number of accepting states: ";
    cin >> accepting_states;

    vector<int> accepting_state(accepting_states);
    for (int i = 0; i < accepting_states; i++) {
        cout << "Enter the " << i + 1 << "th accepting state: ";
        cin >> accepting_state[i];
    }

    vector<vector<int>> transition_function(states, vector<int>(no_inp_symbols));
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < no_inp_symbols; j++) {
            cout << "Enter the transition from state " << i + 1 
                 << " on input symbol '" << inp_symbols[j] << "': ";
            cin >> transition_function[i][j];
        }
    }

    string input_string;
    cout << "Enter the string to validate: ";
    cin >> input_string;

    // String Validation
    int current_state = initial_state;

    for (char ch : input_string) {
        auto it = find(inp_symbols.begin(), inp_symbols.end(), ch);
        if (it == inp_symbols.end()) {
            cout << "Invalid String (contains unknown symbol '" << ch << "')!" << endl;
            return 0;
        }

        int symbol_index = distance(inp_symbols.begin(), it);
        current_state = transition_function[current_state - 1][symbol_index];
    }

    // Check if final state is an accepting state
    if (find(accepting_state.begin(), accepting_state.end(), current_state) != accepting_state.end()) {
        cout << "Valid String" << endl;
    } else {
        cout << "Invalid String" << endl;
    }

    return 0;
}