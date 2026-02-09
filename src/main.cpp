#include <iostream>
#include "Bank.h"

int main() {
    Bank myBank(1000.0); // Создаем банк с начальным балансом 1000

    std::cout << "Welcome to Fluffy Palm Tree Bank!\n";
    myBank.displayBalance();

    myBank.deposit(500);
    myBank.withdraw(200);
    myBank.displayBalance();

    return 0;
}

