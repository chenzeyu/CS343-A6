// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "watcard.h"

WATCard::WATCard(){
    balance = 0;
}

void WATCard::deposit(unsigned int amount){
    balance += amount;
}

void WATCard::withdraw(unsigned int amount){
    balance -= amount;
}

unsigned int WATCard::getBalance(){
    return balance;
}
