#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

unordered_set<string> keywords = {"int", "float", "char", "return", "if", "else", "while", "for", "void"};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '%'};
unordered_set<char> punctuations = {';', ',', '(', ')', '{', '}'};
unordered_map<string, string> symbolTable;
vector<string> symbolOrder; // To store unique identifiers in order
vector<string> lexicalErrors;

bool isKeyword(const string& str) {
    return keywords.find(str) != keywords.end();
}

bool isOperator(char ch) {
    return operators.find(ch) != operators.end();
}

bool isPunctuation(char ch) {
    return punctuations.find(ch) != punctuations.end();
}

bool isValidIdentifier(const string& identifier) {
    if (identifier.empty() || !(isalpha(identifier[0]) || identifier[0] == '_')) {
        return false;
    }
    for (char ch : identifier) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}

void tokenize(const string& code) {
    int i = 0, n = code.length();
    while (i < n) {
        if (isspace(code[i])) {
            i++;
            continue;
        }

        // Handle single-line comments
        if (code[i] == '/' && i + 1 < n && code[i + 1] == '/') {
            while (i < n && code[i] != '\n') i++;  
            continue;
        }

        // Handle multi-line comments
        if (code[i] == '/' && i + 1 < n && code[i + 1] == '*') {
            i += 2;
            while (i + 1 < n && !(code[i] == '*' && code[i + 1] == '/')) i++;
            i += 2;  
            continue;
        }

        // Handle identifiers and keywords
        if (isalpha(code[i]) || code[i] == '_') {
            string identifier;
            while (i < n && (isalnum(code[i]) || code[i] == '_')) {
                identifier += code[i++];
            }

            if (isKeyword(identifier)) {
                cout << "Keyword: " << identifier << endl;
            } else if (identifier == "main") {
                cout << "Function: " << identifier << endl;  
            } else if (isValidIdentifier(identifier)) {
                cout << "Identifier: " << identifier << endl;  // ✅ Print every occurrence
                
                // Store only unique identifiers in symbol table
                if (symbolTable.find(identifier) == symbolTable.end()) { 
                    symbolTable[identifier] = "Identifier";  
                    symbolOrder.push_back(identifier);  
                }
            } else {
                lexicalErrors.push_back("Invalid identifier: " + identifier);
            }
            continue;
        }

        // Handle constants
        if (isdigit(code[i])) {
            string constant;
            while (i < n && isdigit(code[i])) {
                constant += code[i++];
            }

            if (i < n && isalpha(code[i])) { 
                constant += code[i++];
                while (i < n && isalnum(code[i])) {
                    constant += code[i++];
                }
                lexicalErrors.push_back(constant + " invalid lexeme");
            } else {
                cout << "Constant: " << constant << endl;
            }
            continue;
        }

        // Handle string literals
        if (code[i] == '"') {
            string strConst;
            i++; 
            while (i < n && code[i] != '"') {
                strConst += code[i++];
            }
            if (i < n) { 
                i++;  
                cout << "String: \"" << strConst << "\"" << endl;
            } else {
                lexicalErrors.push_back("Missing closing quote for string literal");
            }
            continue;
        }

        // Handle character literals
        if (code[i] == '\'') {
            i++; 
            if (i < n && code[i] != '\'') {  
                cout << "Character: '" << code[i++] << "'" << endl; 
                if (i < n && code[i] == '\'') { 
                    i++;
                } else {
                    lexicalErrors.push_back("Invalid character literal");
                }
            } else {
                lexicalErrors.push_back("Empty character literal");
                i++; 
            }
            continue;
        }

        // Handle operators
        if (isOperator(code[i])) {
            cout << "Operator: " << code[i] << endl;
            i++;
            continue;
        }

        // Handle punctuation
        if (isPunctuation(code[i])) {
            cout << "Punctuation: " << code[i] << endl;
            i++;
            continue;
        }

        lexicalErrors.push_back(string(1, code[i]) + " invalid lexeme");
        i++;
    }
}

int main() {
    string filename;

    cout << "Enter the filename: ";
    getline(cin, filename); 

    ifstream file(filename); 
    if (!file) { 
        cerr << "Error! Could not open file." << endl;
        return 1; 
    }

    ostringstream ss; 
    ss << file.rdbuf(); 
    string content = ss.str(); 

    tokenize(content); 

    if (!lexicalErrors.empty()) {
        cout << "\nLEXICAL ERRORS\n";
        for (const auto& error : lexicalErrors) {
            cout << error << endl;
        }
    } else {
        cout << "\nNo Lexical Errors Found.\n";
    }

    cout << "\nSYMBOL TABLE ENTRIES\n";
    int count = 1;
    for (const auto& identifier : symbolOrder) { 
        cout << count++ << ") " << identifier << endl; 
    }

    return 0; 
}