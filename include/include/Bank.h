#ifndef BANK_H
#define BANK_H

#include <string>

class Bank {
private:
    double balance;

public:
    Bank(double initialBalance = 0.0);

    void deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
    void displayBalance() const;
};

#endif // BANK_H
