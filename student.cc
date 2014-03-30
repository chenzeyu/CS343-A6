// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "student.h"

const unsigned int MIN_PURCHASES = 1;
Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
                unsigned int maxPurchases ):
    printer(prt),
    nameserver(nameserver),
    office(cardOffice),
    id(id),
    maxPurchases(maxPurchases){
        purchase = mprng(MIN_PURCHASES, maxPurchases);
        flavour = mprng(VendingMachine::NUM_FLAVOURS - 1);
        printer.print(Printer::Student, 'S');
    }

Student::main(){

}
