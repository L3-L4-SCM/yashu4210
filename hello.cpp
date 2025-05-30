#include <iostream>i
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Transaction {
public:
    string type;
    double amount;
    double balanceAfter;

    Transaction(string t, double a, double b) : type(t), amount(a), balanceAfter(b) {}
};

class Account {
private:// Account Number and accountHolderName and balance take from users 
    string accountNumber;
    string accountHolderName;
    double balance;
    vector<Transaction> transactionHistory;

public:
    Account(string accNumber, string accHolderName, double initialBalance)
        : accountNumber(accNumber), accountHolderName(accHolderName), balance(initialBalance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back(Transaction("Deposit", amount, balance));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactionHistory.push_back(Transaction("Withdrawal", amount, balance));
        } else {
            cout << "Insufficient funds!" << endl;
        }
    }

    void printTransactionHistory() const {
        cout << "\nTransaction History for Account: " << accountNumber << endl;
        cout << "---------------------------------------------------" << endl;
        for (const auto& transaction : transactionHistory) {
            cout << setw(12) << left << transaction.type
                 << setw(10) << right << fixed << setprecision(2) << transaction.amount
                 << setw(20) << right << fixed << setprecision(2) << transaction.balanceAfter
                 << endl;
        }
        cout << "---------------------------------------------------" << endl;
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount() {
        string accNumber, accHolderName;
        double initialBalance;

        cout << "Enter Account Number: ";
        cin >> accNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        getline(cin, accHolderName);
        cout << "Enter Initial Deposit Amount: ";
        cin >> initialBalance;

        accounts.push_back(Account(accNumber, accHolderName, initialBalance));
        cout << "Account created successfully!" << endl;
    }

    Account* findAccount(const string& accNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void displayAllAccounts() const {
        cout << "\nAll Accounts:" << endl;
        cout << "---------------------------------------------------" << endl;
        for (const auto& account : accounts) {
            cout << "Account Number: " << account.getAccountNumber()
                 << "Account Holder: " << account.getAccountHolderName()
                 << "Account Balance: " << fixed << setprecision(2) << account.getBalance()
                 << endl;
        }
        cout << "---------------------------------------------------" << endl;
    }
};

int main() {
    Bank bank;
    int choice;
    string accNumber;

    do {
        cout << "\nBanking System Menu:" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. View Transaction History" << endl;
        cout << "6. View All Accounts" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                {
                    Account* account = bank.findAccount(accNumber);
                    if (account) {
                        double amount;
                        cout << "Enter Deposit Amount: ";
                        cin >> amount;
                        account->deposit(amount);
                    } else {
                        cout << "Account not found!" << endl;
                    }
                }
                break;

            case 3:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                {
                    Account* account = bank.findAccount(accNumber);
                    if (account) {
                        double amount;
                        cout << "Enter Withdrawal Amount: ";
                        cin >> amount;
                        account->withdraw(amount);
                    } else {
                        cout << "Account not found!" << endl;
                    }
                }
                break;

            case 4:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                {
                    Account* account = bank.findAccount(accNumber);
                    if (account) {
                        cout << "Account Balance: " << fixed << setprecision(2) << account->getBalance() << endl;
                    } else {
                        cout << "Account not found! try again..." << endl;
                    }
                }
                break;

            case 5:
                cout << "Enter Account Number: ";
                cin >> accNumber;
                {
                    Account* account = bank.findAccount(accNumber);
                    if (account) {
                        account->printTransactionHistory();
                    } else {
                        cout << "Account not found!try again.." << endl;
                    }
                }
                break;

            case 6:
                bank.displayAllAccounts();
                break;

            case 7:
                cout << "Exiting the banking system. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

