#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class user {
    string user, pass;

public:
    void register_user() {
        cout << "\n--- Register The User ---\n";
        cout << "Enter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        if (user.empty() || pass.empty()) {
            cout << "!! Username and password cannot be empty. !!\n";
            return;
        }

        ifstream infile("users.txt");
        string u, p;
        while (infile >> u >> p) {
            if (u == user) {
                cout << "User already exists!\n";
                infile.close();
                return;
            }
        }
        infile.close();

        ofstream outfile("users.txt", ios::app);
        outfile << user << " " << pass << endl;
        outfile.close();
        cout << "✅ Registration successful!\n";
    }

    void login_user() {
        cout << "\n--- User Login ---\n";
        cout << "Enter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        ifstream infile("users.txt");
        string u, p;
        bool found = false;
        while (infile >> u >> p) {
            if (u == user && p == pass) {
                found = true;
                break;
            }
        }
        infile.close();

        if (found)
            cout << "Login successful. Welcome, " << user << "!\n";
        else
            cout << "Login failed. Invalid username or password.\n";
    }
};

int main() {
    int choice;
    user u;

    do {
        cout << "\n----- USER LOGIN SYSTEM -----\n";
        cout << "1. Register\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                u.register_user();
                break;
            case 2:
                u.login_user();
                break;
            case 3:
                cout << "---Thank You For Using Our Software!! Thank You !!---\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
