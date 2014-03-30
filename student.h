// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef STUDENT_H
#define STUDENT_H
#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "vendingMachine.h"
class printer;
class nameserver;
class watcardOffice;

_Task Student {
    private:
        void main();
        Printer &printer;
        NameServer &nameserver;
        WATCardOffice &office;
        unsigned int id;
        unsigned int maxPurchases;
        unsigned int purchase;
        unsigned int flavour;
    public:
        Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
                unsigned int maxPurchases );
};

#endif //student.h
