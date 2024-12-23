#include <iostream>
#include <fstream>
#include <string>


using namespace std;


void createAccount();
void deposit();
void withdraw();
void checkDetails();

int main() {
    int choice;
//display menu
    while (true) {
        
        cout << "\nWelcome to Simple Bank System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Account Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkDetails(); break;
            case 5: cout << "Thank you for using the system. Goodbye!\n"; return 0;
            default: cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to create a new account
void createAccount() {
    string name, accountNumber;
    double initialDeposit;

    cout << "Enter your name: ";
    cin.ignore();// Ignore leftover newline
    getline(cin, name);
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter initial deposit: ";
    cin >>initialDeposit;

    if (initialDeposit < 0) {
        cout << "Initial deposit cannot be negative.\n";
        return;
    }

   // Save account details to a file
    fstream my_file("accounts.txt", ios::app);
    my_file << accountNumber << " " << name << " " << initialDeposit << endl;
    my_file.close();

    cout << "Account created successfully!"<<endl;
}

//function to deposit money
void deposit() {
    string accountNumber;
    double depositAmount;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter deposit amount: ";
    cin >> depositAmount;

    if (depositAmount <= 0) {
        cout << "Deposit amount must be positive."<<endl;
        return;
    }

    fstream my_file("accounts.txt", ios::in);
    fstream tempFile("temp.txt",ios::out);
    string accNum, name;
    double balance;
    bool found = false;

    while (my_file >> accNum >> ws && getline(my_file, name, ' ') && my_file >> balance) {
        if (accNum == accountNumber) {
            balance += depositAmount;
            found = true;
        }
        tempFile << accNum << " " << name << " " << balance << endl;
    }

    my_file.close();
    tempFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found) {
        cout << "Deposit successful!\n";
    } else {
        cout << "Account not found.\n";
    }
}

// function to withdraw money
void withdraw() {
    string accountNumber;
    double withdrawAmount;

    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter withdraw amount: ";
    cin >> withdrawAmount;

    if (withdrawAmount <= 0) {
        cout << "Withdrawal amount must be positive."<<endl;
        return;
    }

    fstream my_file("accounts.txt", ios::in);
    ofstream tempFile("temp.txt");
    string accNum, name;
    double balance;
    bool found = false;

    while (my_file >> accNum >> ws && getline(my_file, name, ' ') && my_file >> balance) {
        if (accNum == accountNumber) {
            if (balance >= withdrawAmount) {
                balance -= withdrawAmount;
                found = true;
            } else {
                cout << "Insufficient balance."<<endl;
                tempFile.close();
                my_file.close();
                remove("temp.txt");
                return;
            }
        }
        tempFile << accNum << " " << name << " " << balance << endl;
    }

    my_file.close();
    tempFile.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found) {
        cout << "Withdrawal successful!\n";
    } else {
        cout << "Account not found.\n";
    }
}

//function to check account details
void checkDetails() {
    string accountNumber;

    cout << "Enter account number: ";
    cin >> accountNumber;

    fstream my_file("accounts.txt", ios::in);
    string accNum, name;
    double balance;

    while (my_file >> accNum >> ws && getline(my_file, name, ' ') && my_file >> balance) {
        if (accNum == accountNumber) {
            cout << "Name: " << name << endl;
            cout << "Account Number: " << accNum << endl;
            cout << "Balance: "<<balance << endl;
            my_file.close();
            return;
        }
    }

    my_file.close();
    cout << "Account not found."<<endl;
}
