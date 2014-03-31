// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "bank.h"
Bank::Bank(unsigned int numStudents):numStudents(numStudents){
    accountConditions = new uCondition[numStudents];
    studentAccounts = new unsigned int[numStudents];
}

Bank::~Bank(){
    delete [] studentAccounts;
    delete [] accountConditions;
}

/* called by parents to deposit money
 * into student's account
 * will signal all blocked withdraw
 */
void Bank::deposit(unsigned int id, unsigned int amount){
    //add money
    studentAccounts[id] += amount;
    //signal if blocked
    while(!accountConditions[id].empty()){
        accountConditions[id].signal();
    }
}

/* called by couriers to deduct money
 * will block if there's insufficient funds
 */
void Bank::withdraw(unsigned int id, unsigned int amount){

    //wait until there's sufficient funds
    while(studentAccounts[id] < amount){
        accountConditions[id].wait();
    }
    studentAccounts[id] -= amount;

}
