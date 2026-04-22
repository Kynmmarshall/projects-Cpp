#include <iostream>
using namespace std;



class Account
{
private:
protected:
double balance;
public:

virtual bool withdraw(double amount) = 0;
virtual bool deposit(double amount) = 0;
virtual double transfer(double amount, Account& sender, Account& receiver) = 0;
virtual void PrintBalance() = 0;

};

class SavingsAccount : public Account
{
private:
double interestRate = 0.8;

public:

SavingsAccount() {
    balance = 5000;
}

bool withdraw(double amount) {
    if (amount > balance && amount <= 0) {
        cout << "Invalid withdrawal amount!" << endl;
        return false;
    }
    balance = balance - (amount+(interestRate*amount));
    return true;
    
}

bool deposit(double amount) {
    if (amount <= 0 && amount > balance) {
        cout << "Invalid deposit amount!" << endl;
        return false;
    }
    balance = balance + (amount+(interestRate*amount));
    return true;
}

void PrintBalance() {
    cout << "Current balance SavingsAccount: " << balance << endl;

}

double transfer(double amount, Account& sender, Account& receiver) {
    if (amount <= 0) {
        cout << "Invalid transfer amount!" << endl;
        return 0;
    }
    if (!sender.withdraw(amount)) {
        return 0;
    }
    if (!receiver.deposit(amount)) {
        sender.deposit(amount);
        return 0;
    }
    return amount;
}

};

class CheckingAccount: public Account
{
private:
    double balance;
public:
    CheckingAccount() {
        balance = 5000;
    }
    bool withdraw(double amount) {
    if (amount > balance && amount <= 0) {
        cout << "Invalid withdrawal amount!" << endl;
        return false;
    }
    balance -= amount;
    return true;
    }

    bool deposit(double amount) {
    if (amount <= 0 && amount > balance) {
        cout << "Invalid deposit amount!" << endl;
        return false;
    }
    balance += amount;
    return true;
    }

    double transfer(double amount, Account& sender, Account& receiver) {
    if (amount <= 0) {
        cout << "Invalid transfer amount!" << endl;
        return 0;
    }
    if (!sender.withdraw(amount)) {
        return 0;
    }
    if (!receiver.deposit(amount)) {
        sender.deposit(amount);
        return 0;
    }
    return amount;
    }

    void PrintBalance() {
    cout << "Current balance CheckingAccount: " << balance << endl;
    }

};

class BitcoinAccount: public Account
{
private:
    double transactionFee = 0.002;
public:
    BitcoinAccount() {
        balance = 5000;
    }

    bool withdraw(double amount) {
    double fee = amount * transactionFee;
    if (amount > balance || amount <= 0) {
        cout << "Invalid withdrawal amount!" << endl;
        return false;
    }
    balance -= (amount + fee);
    return true;
    }

    bool deposit(double amount) {
    if (amount <= 0) {
        cout << "Invalid deposit amount!" << endl;
        return false;
    }
    balance += amount;
    return true;
    }

    double transfer(double amount, Account& sender, Account& receiver) {
    if (amount <= 0) {
        cout << "Invalid transfer amount!" << endl;
        return 0;
    }
    if (!sender.withdraw(amount)) {
        return 0;
    }
    if (!receiver.deposit(amount)) {
        sender.deposit(amount);
        return 0;
    }
    return amount;
    }

    void PrintBalance() {
    cout << "Current balance BitcoinAccount: " << balance << endl;
    }
};

int main() {
    SavingsAccount savings;
    CheckingAccount checking;
    BitcoinAccount bitcoin;

    savings.PrintBalance();
    checking.PrintBalance();
    bitcoin.PrintBalance();

    savings.withdraw(1000);
    checking.withdraw(1000);
    bitcoin.withdraw(1000);
    cout << "After withdrawal of 1000:" << endl;
    savings.PrintBalance();
    checking.PrintBalance();
    bitcoin.PrintBalance();

    return 0;
}




