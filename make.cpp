#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream> 
#include <string>
#include <regex>
#include <unordered_map>

// Define the Automaton structure
struct Automaton {
    int id;
    std::vector<int> states;
    std::vector<std::pair<int, char>> transitions;
    int start_state;
    int final_state;
};

// Function to add a new Automaton to the array
void addAutomaton(std::vector<Automaton> &automatons, int id, const std::vector<int> &states,
    const std::vector<std::pair<int, char>> &transitions, int start_state, int final_state) {
    Automaton automaton;
    automaton.id = id;
    automaton.states = states;
    automaton.transitions = transitions;
    automaton.start_state = start_state;
    automaton.final_state = final_state;
    automatons.push_back(automaton);
}

// Function to access an Automaton by its ID
Automaton* getAutomatonByID(std::vector<Automaton> &automatons, int id) {
    for (auto &automaton : automatons) {
        if (automaton.id == id) {
            return &automaton;
        }
    }
    return nullptr;
}

// Function to delete an Automaton by its ID
void deleteAutomaton(std::vector<Automaton> &automatons, int id) {
    automatons.erase(std::remove_if(automatons.begin(), automatons.end(),
        [id](const Automaton &automaton) { return automaton.id == id; }), automatons.end());
}

// Function to print all Automatons
void printAllAutomatons(const std::vector<Automaton> &automatons) {
    std::cout << "All Automatons:\n";
    for (const auto &automaton : automatons) {
        std::cout << "Automaton ID: " << automaton.id << std::endl;
        std::cout << "States: ";
        for (const auto &state : automaton.states) {
            std::cout << state << " ";
        }
        std::cout << std::endl;
        std::cout << "Transitions: ";
        for (const auto &transition : automaton.transitions) {
            std::cout << "(" << transition.first << "," << transition.second << ") ";
        }
        std::cout << std::endl;
        std::cout << "Start state: " << automaton.start_state << std::endl;
        std::cout << "Final state: " << automaton.final_state << std::endl;
        std::cout << "-------------------------------------\n";
    }
}

// Function to input details for a new Automaton from the user
void inputAutomatonDetails(std::vector<Automaton> &automatons) {
    int id, start_state, final_state;
    std::vector<int> states;
    std::vector<std::pair<int, char>> transitions;

    std::cout << "Enter Automaton ID: ";
    std::cin >> id;

    std::cout << "Enter number of states: ";
    int num_states;
    std::cin >> num_states;
    std::cout << "Enter state IDs: ";
    for (int i = 0; i < num_states; ++i) {
        int state;
        std::cin >> state;
        states.push_back(state);
    }

    std::cout << "Enter number of transitions: ";
    int num_transitions;
    std::cin >> num_transitions;
    std::cout << "Enter transitions in the format (source_state symbol destination_state): ";
    for (int i = 0; i < num_transitions; ++i) {
        int source_state, destination_state;
        char symbol;
        std::cin >> source_state >> symbol >> destination_state;
        transitions.push_back(std::make_pair(source_state, symbol));
    }

    std::cout << "Enter start state: ";
    std::cin >> start_state;
    std::cout << "Enter final state: ";
    std::cin >> final_state;

    addAutomaton(automatons, id, states, transitions, start_state, final_state);
}

// Function to perform semantic analysis and convert languages
std::string convertLanguage(const std::string &program, const std::unordered_map<std::string, std::string> &translationMap) {
    std::string translatedProgram;
    std::string word;
    bool isWord = false;

    for (char c : program) {
        if (std::isalpha(c)) {
            word += c;
            isWord = true;
        } else {
            if (isWord) {
                if (translationMap.find(word) != translationMap.end()) {
                    translatedProgram += translationMap.at(word);
                } else {
                    translatedProgram += word;
                }
                word.clear();
                isWord = false;
            }
            translatedProgram += c;
        }
    }

    if (!word.empty()) {
        if (translationMap.find(word) != translationMap.end()) {
            translatedProgram += translationMap.at(word);
        } else {
            translatedProgram += word;
        }
    }

    return translatedProgram;
}

// Function to tokenize a program
std::vector<std::string> tokenizeProgram(const std::string &program) {
    std::vector<std::string> tokens;
    std::istringstream iss(program);
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to check if a program follows a specified grammar
bool checkProgramGrammar(const std::string &program) {
    std::regex ifElseRegex("if.*else");
    return std::regex_search(program, ifElseRegex);
}

int main() {
    std::vector<Automaton> automatons;
    std::unordered_map<std::string, std::string> translationMap = {
        {"if", "si"},
        {"else", "otro"},
        {"roy","abbas"},
        {"abbas","roy"}
        // Add more translation mappings as needed
    };

    int choice;
    do {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. Add Automaton\n";
        std::cout << "2. Delete Automaton\n";
        std::cout << "3. Print All Automatons\n";
        std::cout << "4. Tokenize Program\n";
        std::cout << "5. Check Program Grammar\n";
        std::cout << "6. Convert Language\n";
        std::cout << "7. search for automaton\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inputAutomatonDetails(automatons);
                break;
            case 2:
                int deleteID;
                std::cout << "Enter Automaton ID to delete: ";
                std::cin >> deleteID;
                deleteAutomaton(automatons, deleteID);
                break;
            case 3:
                printAllAutomatons(automatons);
                break;
            case 4: {
                std::string program;
                std::cout << "Enter the program as a string: ";
                std::cin.ignore(); // Ignore newline character in input buffer
                std::getline(std::cin, program);

                std::vector<std::string> tokens = tokenizeProgram(program);
                std::cout << "Tokens:\n";
                for (const auto &token : tokens) {
                    std::cout << token << std::endl;
                }
                break;
            }
            case 5: {
                std::string program;
                std::cout << "Enter the program as a string: ";
                std::cin.ignore(); // Ignore newline character in input buffer
                std::getline(std::cin, program);

                bool followsGrammar = checkProgramGrammar(program);
                std::cout << (followsGrammar ? "Follows" : "Does not follow") << " specified grammar.\n";
                break;
            }
            case 6: {
                std::string program;
                std::cout << "Enter the program as a string: ";
                std::cin.ignore(); // Ignore newline character in input buffer
                std::getline(std::cin, program);

                std::string convertedProgram = convertLanguage(program, translationMap);
                std::cout << "Translated Program: " << convertedProgram << std::endl;
                break;
            }
            case 7: {
    int searchID;
    std::cout << "Enter Automaton ID to search: ";
    std::cin >> searchID;

    Automaton* foundAutomaton = getAutomatonByID(automatons, searchID);
    if (foundAutomaton != nullptr) {
        std::cout << "Automaton found:\n";
        std::cout << "Automaton ID: " << foundAutomaton->id << std::endl;
        std::cout << "States: ";
        for (const auto &state : foundAutomaton->states) {
            std::cout << state << " ";
        }
        std::cout << std::endl;
        std::cout << "Transitions: ";
        for (const auto &transition : foundAutomaton->transitions) {
            std::cout << "(" << transition.first << "," << transition.second << ") ";
        }
        std::cout << std::endl;
        std::cout << "Start state: " << foundAutomaton->start_state << std::endl;
        std::cout << "Final state: " << foundAutomaton->final_state << std::endl;
        std::cout << "-------------------------------------\n";
    } else {
        std::cout << "No Automaton found with ID: " << searchID << std::endl;
    }
    break;
}

            case 8:
                std::cout << "Exiting...\n";
                return 0;
              
            default:
                std::cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 8);

    return 0;
}
