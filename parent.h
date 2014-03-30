// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef PARENT_H
#define PARENT_H
#include "printer.h"
#include "bank.h"
#include "mprng.h"

class Printer;
class Bank;

_Task Parent {
    private:
        void main();
        unsigned int numStudents;
        Printer &printer;
        Bank &bank;
    public:
        Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
#endif
