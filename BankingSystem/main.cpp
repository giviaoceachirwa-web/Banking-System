#include <iostream>

using namespace std;
const int MAX_USERS = 3;

// User details stored in parallel arrays
string names[MAX_USERS]      = {"OCEAN CHIRWA", "NHLAMULO BALOYI", "LIYEMA GOLOZA"};
int accountNumbers[MAX_USERS] = {1001, 1002, 1003};
int pins[MAX_USERS]           = {1111, 2222, 3333};
double balances[MAX_USERS]    = {1500.00, 2500.50, 800.00};

// Returns the index of an account number, or -1 if not found
int findAccount(int accNo) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (accountNumbers[i] == accNo) {
            return i;
        }
    }
    return -1;
}

// Asks for account number and PIN; returns user index or -1
int login() {
    int accNo, pin;
    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter PIN: ";
    cin >> pin;

    int index = findAccount(accNo);
    if (index == -1 || pins[index] != pin) {
        cout << "Invalid account number or PIN.\n";
        return -1;
    }
    cout << "Welcome, " << names[index] << "!\n";
    return index;
}

void displayMenu() {
    cout << "\n===== GCC BANK =====\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

void deposit(int user) {
    double amount;
    cout << "Enter amount to deposit: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. It must be more than 0.\n";
    } else {
        balances[user] += amount;
        cout << "Deposit successful. New balance: R" << balances[user] << endl;
    }
}

void withdraw(int user) {
    double amount;
    cout << "Enter amount to withdraw: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. It must be more than 0.\n";
    } else if (amount > balances[user]) {
        cout << "Insufficient funds. Your balance is R" << balances[user] << endl;
    } else {
        balances[user] -= amount;
        cout << "Withdrawal successful. New balance: R" << balances[user] << endl;
    }
}

void sendCash(int user) {
    int recipientAcc;
    double amount;

    cout << "Enter recipient account number: ";
    cin >> recipientAcc;

    int recipient = findAccount(recipientAcc);
    if (recipient == -1) {
        cout << "Account does not exist.\n";
        return;
    }
    if (recipient == user) {
        cout << "You cannot send cash to your own account.\n";
        return;
    }

    cout << "Enter amount to send: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. It must be more than 0.\n";
    } else if (amount > balances[user]) {
        cout << "Insufficient funds. Your balance is R" << balances[user] << endl;
    } else {
        balances[user] -= amount;
        balances[recipient] += amount;
        cout << "R" << amount << " sent to " << names[recipient] << ".\n";
        cout << "Your new balance: R" << balances[user] << endl;
    }
}

void checkBalance(int user) {
    cout << "Current balance: R" << balances[user] << endl;
}


int main()
{
     cout << "===== WELCOME TO GCC BANK =====\n";

    // Keep asking until login succeeds
    int user = -1;
    while (user == -1) {
        user = login();
    }

    int choice = 0;
    while (choice != 5) {
        displayMenu();
        cin >> choice;

        // Handle non-numeric input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                deposit(user);
                break;
            case 2:
                withdraw(user);
                 break;
            case 3:
                sendCash(user);
                break;
            case 4:
                checkBalance(user);
                break;
            case 5:
                cout << "Thank you for banking with GCC Bank. Goodbye!\n"; \
                break;
            default:
                cout << "Invalid choice. Please enter 1-5.\n";
        }
    }
    return 0;
}
