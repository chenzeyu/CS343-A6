// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "watcardOffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
    printer(prt), bank(bank), numCouriers(numCouriers)
{
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
    return 0;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
    return 0;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
    return 0;
}
