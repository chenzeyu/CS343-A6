// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "watcardOffice.h"
WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ){}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){}

WATCardOffice::Job *WATCardOffice::requestWork() {}
