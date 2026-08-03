#include <iostream>
#include <sstream>
#include <string>
#include "PasswordHashTable.h"

using namespace std;

void printHelp() {
    cout << "\nAvailable Commands:\n";
    cout << "  Insert <username> <password>   Add a new username/password entry\n";
    cout << "  Search <username>               Check if a username exists\n";
    cout << "  Edit <username> <newPassword>   Update a stored password\n";
    cout << "  Delete <username>               Remove a username/password entry\n";
    cout << "  Login <username> <password>     Verify a username/password combination\n";
    cout << "  Save <filename>                 Save all entries to a CSV file\n";
    cout << "  Load <filename>                 Load entries from a CSV file\n";
    cout << "  Help                            Show this command list\n";
    cout << "  Exit                            Exit the application\n\n";
}

int main() {
    PasswordHashTable passwordTable;

    cout << "===================================\n";
    cout << " Secure Password Manager\n";
    cout << " CSC 307 - Group 3\n";
    cout << "===================================\n";
    printHelp();

    string line;
    bool running = true;

    while (running) {
        cout << "> ";

        if (!getline(cin, line)) {
            cout << "\n";
            break;
        }

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "Insert") {
            string username, password;
            if (ss >> username >> password) {
                passwordTable.insert(username, password);
                cout << "Inserted \"" << username << "\".\n";
            } else {
                cout << "Usage: Insert <username> <password>\n";
            }
        }
        else if (command == "Search") {
            string username;
            if (ss >> username) {
                if (passwordTable.search(username)) {
                    cout << "\"" << username << "\" was found in the table.\n";
                } else {
                    cout << "\"" << username << "\" was not found.\n";
                }
            } else {
                cout << "Usage: Search <username>\n";
            }
        }
        else if (command == "Edit") {
            string username, newPassword;
            if (ss >> username >> newPassword) {
                if (passwordTable.update(username, newPassword)) {
                    cout << "Password updated for \"" << username << "\".\n";
                } else {
                    cout << "\"" << username << "\" was not found.\n";
                }
            } else {
                cout << "Usage: Edit <username> <newPassword>\n";
            }
        }
        else if (command == "Delete") {
            string username;
            if (ss >> username) {
                if (passwordTable.remove(username)) {
                    cout << "\"" << username << "\" was deleted.\n";
                } else {
                    cout << "\"" << username << "\" was not found.\n";
                }
            } else {
                cout << "Usage: Delete <username>\n";
            }
        }
        else if (command == "Login") {
            string username, password;
            if (ss >> username >> password) {
                if (passwordTable.verifyPassword(username, password)) {
                    cout << "Login successful. Welcome, " << username << "!\n";
                } else {
                    cout << "Login failed: incorrect username or password.\n";
                }
            } else {
                cout << "Usage: Login <username> <password>\n";
            }
        }
        else if (command == "Save") {
            string filename;
            if (ss >> filename) {
                passwordTable.saveToCSV(filename);
            } else {
                cout << "Usage: Save <filename>\n";
            }
        }
        else if (command == "Load") {
            string filename;
            if (ss >> filename) {
                passwordTable.loadFromCSV(filename);
            } else {
                cout << "Usage: Load <filename>\n";
            }
        }
        else if (command == "Help") {
            printHelp();
        }
        else if (command == "Exit") {
            cout << "Goodbye!\n";
            running = false;
        }
        else {
            cout << "Unknown command \"" << command << "\". Type \"Help\" for a list of commands.\n";
        }
    }

    return 0;
}
