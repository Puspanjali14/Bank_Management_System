#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>  // File handling
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount() {}

    BankAccount(string accNo, string name, double initialBalance) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = initialBalance;
    }

    // Function to save account details to file
    void saveToFile() const {
        ofstream outFile("accountData.txt", ios::app); // Open file in append mode
        if (outFile.is_open()) {
            outFile << accountNumber << " " << accountHolderName << " " << balance << "\n";
            outFile.close();
            cout << "Account details saved to file successfully.\n";
        } else {
            cout << "Error opening file!\n";
        }
    }

    // Function to load account details from file
    static void loadFromFile() {
        ifstream inFile("accountData.txt");
        if (inFile.is_open()) {
            string accNo, name;
            double bal;
            cout << "\n===== Account Data from File =====\n";
            while (inFile >> accNo >> name >> bal) {
                cout << "Account Number: " << accNo << "\n";
                cout << "Account Holder: " << name << "\n";
                cout << "Balance: $" << fixed << setprecision(2) << bal << "\n";
                cout << "---------------------------------\n";
            }
            inFile.close();
        } else {
            cout << "Error opening file!\n";
        }
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        } else {
            cout << "Invalid or insufficient balance for withdrawal.\n";
        }
    }

    void displayBalance() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder: " << accountHolderName << "\n";
        cout << "Balance: $" << fixed << setprecision(2) << balance << "\n";
    }
};

int main() {
    string accNumber, name;
    double initialDeposit;

    // Create a new account
    cout << "Enter Account Number: ";
    cin >> accNumber;
    cout << "Enter Account Holder Name: ";
    cin.ignore(); // To handle the newline character after account number input
    getline(cin, name);
    cout << "Enter Initial Deposit: $";
    cin >> initialDeposit;

    BankAccount account(accNumber, name, initialDeposit);
    account.saveToFile(); // Save account details to file

    int choice;
    double amount;

    do {
        cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Check Balance\n";
        cout << "4. Load Account Data from File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: $";
            cin >> amount;
            account.deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            account.withdraw(amount);
            break;
        case 3:
            account.displayBalance();
            break;
        case 4:
            BankAccount::loadFromFile(); // Load account data from file
            break;
        case 5:
            cout << "Exiting system...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
