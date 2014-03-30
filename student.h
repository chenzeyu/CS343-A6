// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef STUDENT_H
#define STUDENT_H
#include "printer.h"
#include "nameServer.h"
#include "watcardOffice.h"
#include "vendingMachine.h"
#include "watcardOffice.h"
#include "watcard.h"

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
        enum State {STARTING = 'S', SELECT_MACHINE = 'V', BUY = 'B', WATCARD_LOST = 'L', FINISHED = 'F'};
    public:
        Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
                unsigned int maxPurchases );
};

#endif //student.h
