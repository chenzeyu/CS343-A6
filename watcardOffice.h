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

        //args definition
        struct Args {
            unsigned int sid;
            Bank &bank;
            WATCard *card;
            unsigned int amount;
            Args(Bank &bank, unsigned int sid, WATCard *watcard, unsigned int amount) :
                sid(sid), bank(bank), card(watcard), amount(amount) {}
        };

        struct Job {                           // marshalled arguments and return future
            Args args;                         // call arguments (YOU DEFINE "Args")
            WATCard::FWATCard result;                   // return future
            Job( Args args ) : args( args ) {}
        };

        _Task Courier {
            private:
                void main();
                unsigned int id;
                WATCardOffice *office;
                Printer &printer;
                Bank &bank;
            public:
                Courier(unsigned int id, WATCardOffice *office, Printer &printer, Bank &bank);
        };                 // communicates with bank

        Courier **couriers;
        Job *pendingJob;
        Printer &printer;
        Bank &bank;
        unsigned int numCouriers;
        bool jobDone;

        void main();

    public:
        _Event Lost {};                        // uC++ exception type, like "struct"
        WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
        WATCard::FWATCard create( unsigned int sid, unsigned int amount );
        WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
        ~WATCardOffice();
        Job *requestWork();
};

#endif
