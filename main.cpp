// ============================================================
// GCC BANK - Command Line Banking System
// Gauteng City College | Introduction to Programming NQF 4
// Features: login, deposit, withdraw, send cash, check balance
// ============================================================

#include <iostream>   // for cout and cin (input and output)
#include <string>     // for using the string type
using namespace std;

// The number of users the bank has
const int MAX_USERS = 3;

// ---------- USER DETAILS (stored in arrays) ----------
// Each position (index) belongs to one user.
// Example: index 0 = Thabo, so names[0], accountNumbers[0],
// pins[0] and balances[0] are all Thabo's details.
string names[MAX_USERS]       = {"OCEAN CHIRWA", "NHLAMULO BALOYI", "LIYEMA GOLOZA"};
int accountNumbers[MAX_USERS] = {1001, 1002, 1003};
int pins[MAX_USERS]           = {1111, 2222, 3333};
double balances[MAX_USERS]    = {1500.00, 2500.50, 800.00};

// ---------- FUNCTION: findAccount ----------
// Looks for an account number in the array.
// Returns the index (position) if found, or -1 if not found.
int findAccount(int accNo) {
    // Loop through every user
    for (int i = 0; i < MAX_USERS; i++) {
        // If the account number matches, return this position
        if (accountNumbers[i] == accNo) {
            return i;
        }
    }
    // We went through all users and found nothing
    return -1;
}

// ---------- FUNCTION: login ----------
// Asks for the account number and PIN.
// Returns the user's index if correct, or -1 if wrong.
int login() {
    int accNo, pin;

    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter PIN: ";
    cin >> pin;

    // If the user typed letters instead of numbers, clear the error
    // and remove the bad input, otherwise the program will loop forever
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter numbers only.\n";
        return -1;
    }

    // Find the account, then check if the PIN matches
    int index = findAccount(accNo);
    if (index == -1 || pins[index] != pin) {
        cout << "Invalid account number or PIN.\n";
        return -1;
    }

    // Login worked
    cout << "Welcome, " << names[index] << "!\n";
    return index;
}

// ---------- FUNCTION: displayMenu ----------
// Prints the bank menu on the screen.
void displayMenu() {
    cout << "\n===== GCC BANK =====\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

// ---------- FUNCTION: deposit ----------
// Adds money to the logged-in user's balance.
// "user" is the index of the person who logged in.
void deposit(int user) {
    double amount;
    cout << "Enter amount to deposit: R";
    cin >> amount;

    // The amount must be more than 0
    if (amount <= 0) {
        cout << "Invalid amount. It must be more than 0.\n";
    } else {
        balances[user] += amount;   // add the money
        cout << "Deposit successful. New balance: R" << balances[user] << endl;
    }
}

// ---------- FUNCTION: withdraw ----------
// Removes money from the logged-in user's balance.
void withdraw(int user) {
    double amount;
    cout << "Enter amount to withdraw: R";
    cin >> amount;

    if (amount <= 0) {
        // Amount must be more than 0
        cout << "Invalid amount. It must be more than 0.\n";
    } else if (amount > balances[user]) {
        // Cannot take out more than the balance
        cout << "Insufficient funds. Your balance is R" << balances[user] << endl;
    } else {
        balances[user] -= amount;   // remove the money
        cout << "Withdrawal successful. New balance: R" << balances[user] << endl;
    }
}

// ---------- FUNCTION: sendCash ----------
// Sends money from the logged-in user to another account.
void sendCash(int user) {
    int recipientAcc;
    double amount;

    cout << "Enter recipient account number: ";
    cin >> recipientAcc;

    // Check that the recipient account exists
    int recipient = findAccount(recipientAcc);
    if (recipient == -1) {
        cout << "Account does not exist.\n";
        return;   // stop the function here
    }

    // A user must not send money to themselves
    if (recipient == user) {
        cout << "You cannot send cash to your own account.\n";
        return;
    }

    cout << "Enter amount to send: R";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount. It must be more than 0.\n";
    } else if (amount > balances[user]) {
        // The sender does not have enough money
        cout << "Insufficient funds. Your balance is R" << balances[user] << endl;
    } else {
        balances[user] -= amount;        // take money from the sender
        balances[recipient] += amount;   // give money to the recipient
        cout << "R" << amount << " sent to " << names[recipient] << ".\n";
        cout << "Your new balance: R" << balances[user] << endl;
    }
}

// ---------- FUNCTION: checkBalance ----------
// Shows the current balance of the logged-in user.
void checkBalance(int user) {
    cout << "Current balance: R" << balances[user] << endl;
}

// ---------- MAIN FUNCTION ----------
// The program starts here.
int main()
{
    cout << "===== WELCOME TO GCC BANK =====\n";

    // Keep asking for login details until they are correct
    int user = -1;   // -1 means "nobody is logged in yet"
    while (user == -1) {
        user = login();
    }

    // The menu repeats until the user chooses 5 (Exit)
    int choice = 0;
    while (choice != 5) {
        displayMenu();
        cin >> choice;

        // If the user typed letters instead of a number,
        // clear the error and remove the bad input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            choice = 0;   // 0 will show "Invalid choice" below
        }

        // Run the function that matches the user's choice
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
                cout << "Thank you for banking with GCC Bank. Goodbye!\n";
                break;
            default:
                // Any other number is not on the menu
                cout << "Invalid choice. Please enter 1-5.\n";
        }
    }

    return 0;   // program ended successfully
}
