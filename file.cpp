#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

// Function to split input into tokens
vector<string> parseInput(string input) {
    vector<string> tokens;
    stringstream ss(input);
    string word;

    while (ss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

// Convert vector<string> to char* array (for execvp)
char** convertToCharArray(vector<string> &tokens) {
    char **args = new char*[tokens.size() + 1];

    for (size_t i = 0; i < tokens.size(); i++) {
        args[i] = new char[tokens[i].size() + 1];
        strcpy(args[i], tokens[i].c_str());
    }
    args[tokens.size()] = NULL;

    return args;
}

int main() {
    string input;

    while (true) {
        cout << "MiniShell> ";
        getline(cin, input);

        // Exit condition
        if (input == "exit") {
            break;
        }

        // Parse input
        vector<string> tokens = parseInput(input);
        if (tokens.empty()) continue;

        // Convert to char array
        char **args = convertToCharArray(tokens);

        // Create child process
        pid_t pid = fork();

        if (pid < 0) {
            cerr << "Fork failed!" << endl;
            return 1;
        }
        else if (pid == 0) {
            // Child process executes command
            if (execvp(args[0], args) == -1) {
                perror("Command execution failed");
            }
            exit(0);
        }
        else {
            // Parent waits for child
            wait(NULL);
        }

        // Free memory
        for (size_t i = 0; i < tokens.size(); i++) {
            delete[] args[i];
        }
        delete[] args;
    }

    return 0;
}  