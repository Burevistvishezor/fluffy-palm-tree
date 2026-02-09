#include "Bank.h"
#include <iostream>

Bank::Bank(double initialBalance) {
    balance = initialBalance;
}

void Bank::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Deposited: " << amount << "\n";
    }
}

bool Bank::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        std::cout << "Withdrew: " << amount << "\n";
        return true;
    } else {
        std::cout << "Insufficient funds!\n";
        return false;
    }
}

double Bank::getBalance() const {
    return balance;
}

void Bank::displayBalance() const {
    std::cout << "Current balance: " << balance << "\n";
}
