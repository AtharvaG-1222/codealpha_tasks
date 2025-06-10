#include <iostream>
#include <vector>
using namespace std;

class transaction {
public:
    string type;
    double amount;
    string details;

    transaction(string t, double a, string d) {
        type = t;
        amount = a;
        details = d;
    }

    void display() {
        cout << type << " of Rs" << amount << " | " << details << endl;
    }
};

class account {
    string acc_no;
    double balance;
    vector<transaction> history;

public:
    void put_data(string a_no, double bal = 0) {
        acc_no = a_no;
        balance = bal;
        history.push_back(transaction("Account Created", bal, "Initial Balance"));
    }

    string get_acc_no() {
        return acc_no;
    }

    double get_balance() {
        return balance;
    }

    void deposit(double amt) {
        balance += amt;
        history.push_back(transaction("Deposit", amt, "Amount Deposited"));
    }

    bool withdraw(double amt) {
        if (amt > balance) {
            cout << "Insufficient balance. Withdrawal failed.\n";
            return false;
        }
        balance -= amt;
        history.push_back(transaction("Withdrawal", amt, "Amount Withdrawn"));
        cout << "Withdrawal successful.\n";
        return true;
    }

    bool transfer(account &receiver, double amt) {
        if (withdraw(amt)) {
            receiver.deposit(amt);
            history.push_back(transaction("Transfer Sent", amt, "To: " + receiver.get_acc_no()));
            receiver.history.push_back(transaction("Transfer Received", amt, "From: " + acc_no));
            cout << "Transfer successful.\n";
            return true;
        }
        return false;
    }

    void show_transactions() {
        cout << "\nTransaction History for Account: " << acc_no << endl;
        if (history.empty()) {
            cout << "No transactions found.\n";
        } else {
            for (auto &t : history)
                t.display();
        }
    }

    void show_info() {
        cout << "\nAccount Number: " << acc_no << "\nBalance: Rs" << balance << endl;
    }
};

class customer {
    string name;
    string cust_id;
    account acc;

public:
    void put_data(string n, string id, string acc_no) {
        name = n;
        cust_id = id;
        acc.put_data(acc_no);
    }

    string get_id() {
        return cust_id;
    }

    account &get_account() {
        return acc;
    }

    void show_customer() {
        cout << "\nCustomer Name: " << name << "\nCustomer ID: " << cust_id << endl;
        acc.show_info();
    }
};

int main() {
    vector<customer> bank;
    int ch;
    string name, id, acc_no, id2;
    double amt;

    do {
        cout << "\n===== BANKING SYSTEM MENU =====\n";
        cout << "1. Create Customer & Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Info\n";
        cout << "6. View Transaction History\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cin.ignore();
            cout << "\nEnter Customer Name: ";
            getline(cin, name);
            cout << "Enter Customer ID: ";
            getline(cin, id);
            cout << "Enter Account Number: ";
            getline(cin, acc_no);
            {
                customer c;
                c.put_data(name, id, acc_no);
                bank.push_back(c);
                cout << "Customer and Account created successfully!\n";
            }
            break;

        case 2:
            cout << "\nEnter Customer ID for deposit: ";
            cin >> id;
            cout << "Enter amount to deposit: Rs";
            cin >> amt;
            for (auto &c : bank) {
                if (c.get_id() == id) {
                    c.get_account().deposit(amt);
                    cout << "Deposit successful.\n";
                    break;
                }
            }
            break;

        case 3:
            cout << "\nEnter Customer ID for withdrawal: ";
            cin >> id;
            cout << "Enter amount to withdraw: Rs";
            cin >> amt;
            for (auto &c : bank) {
                if (c.get_id() == id) {
                    c.get_account().withdraw(amt);
                    break;
                }
            }
            break;

        case 4:
            cout << "\nEnter Sender Customer ID: ";
            cin >> id;
            cout << "Enter Receiver Customer ID: ";
            cin >> id2;
            cout << "Enter amount to transfer: Rs";
            cin >> amt;
            {
                account *sender = nullptr, *receiver = nullptr;
                for (auto &c : bank) {
                    if (c.get_id() == id) sender = &c.get_account();
                    if (c.get_id() == id2) receiver = &c.get_account();
                }
                if (sender && receiver && sender != receiver) {
                    sender->transfer(*receiver, amt);
                } else {
                    cout << "Invalid sender or receiver ID.\n";
                }
            }
            break;

        case 5:
            cout << "\nEnter Customer ID to view account info: ";
            cin >> id;
            for (auto &c : bank) {
                if (c.get_id() == id) {
                    c.show_customer();
                    break;
                }
            }
            break;

        case 6:
            cout << "\nEnter Customer ID to view transactions: ";
            cin >> id;
            for (auto &c : bank) {
                if (c.get_id() == id) {
                    c.get_account().show_transactions();
                    break;
                }
            }
            break;

        case 0:
            cout << "\nExiting Banking System. Thank you for using our service!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (ch != 0);

    return 0;
}
