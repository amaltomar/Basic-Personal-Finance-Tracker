#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Transaction class
class Transaction {
public:
    string type; // "Income" or "Expense"
    double amount;
    string description;

    Transaction(string t, double a, string d) {
        type = t;
        amount = a;
        description = d;
    }

    // Display transaction
    void display() {
        cout << type << " | " << amount << " | " << description << endl;
    }
};

// Function to save transactions to file
void saveToFile(const vector<Transaction>& transactions) {
    ofstream file("transactions.txt");
    for (const auto& t : transactions) {
        file << t.type << "," << t.amount << "," << t.description << endl;
    }
    file.close();
}

// Function to load transactions from file
void loadFromFile(vector<Transaction>& transactions) {
    ifstream file("transactions.txt");
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');
        string type = line.substr(0, pos1);
        double amount = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        string desc = line.substr(pos2 + 1);
        transactions.push_back(Transaction(type, amount, desc));
    }
    file.close();
}

// Main program
int main() {
    vector<Transaction> transactions;
    loadFromFile(transactions);

    int choice;
    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Income\n2. Add Expense\n3. Show Transactions\n4. Show Balance\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            double amount;
            string desc;
            cout << "Enter amount: ";
            cin >> amount;
            cin.ignore();
            cout << "Enter description: ";
            getline(cin, desc);

            string type = (choice == 1) ? "Income" : "Expense";
            transactions.push_back(Transaction(type, amount, desc));
            saveToFile(transactions);

            cout << type << " added successfully!\n";
        }
        else if (choice == 3) {
            cout << "\n--- Transactions ---\n";
            for (auto& t : transactions) {
                t.display();
            }
        }
        else if (choice == 4) {
            double balance = 0;
            for (auto& t : transactions) {
                if (t.type == "Income") balance += t.amount;
                else balance -= t.amount;
            }
            cout << "\nCurrent Balance: " << balance << endl;
        }
    } while (choice != 5);

    cout << "Exiting tracker. Goodbye!\n";
    return 0;
}