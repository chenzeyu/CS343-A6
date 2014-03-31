// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H
#include <uC++.h>
#include "watcard.h"
#include "bank.h"
#include "printer.h"

class Printer;
class Bank;

_Task WATCardOffice {
    private:
        Printer &printer;
        Bank &bank;
        unsigned int numCouriers;
        struct Args {
            unsigned int id;
            Bank &bank;
            WATCard *watcard;
            unsigned int amount;
            Args(Bank &bank, unsigned int id, WATCard *watcard, unsigned int amount) :
                id(id), bank(bank), watcard(watcard), amount(amount) {}
        };

        struct Job {                           // marshalled arguments and return future
            Args args;                         // call arguments (YOU DEFINE "Args")
            WATCard::FWATCard result;                   // return future
            Job( Args args ) : args( args ) {}
        };
        _Task Courier {};                 // communicates with bank
        void main();

    public:
        _Event Lost {};                        // uC++ exception type, like "struct"
        WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
        WATCard::FWATCard create( unsigned int sid, unsigned int amount );
        WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
        Job *requestWork();
};

#endif
