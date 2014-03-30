// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef BANK_H
#define BANK_H
// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "bank.h"
_Monitor Bank {
    private:
        int *bankAccounts;
        unsigned int numStudents;
        uCondition *accountConditions
    public:
        Bank( unsigned int numStudents );
        ~Bank();
        void deposit( unsigned int id, unsigned int amount );
        void withdraw( unsigned int id, unsigned int amount );
};
#endif
