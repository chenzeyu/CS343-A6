// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "watcardOffice.h"
#include "mprng.h"

const unsigned int CHANCE_LOST = 6;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
    printer(prt), bank(bank), numCouriers(numCouriers), pendingJob(NULL)
{
    jobDone = false;
    couriers = new Courier *[numCouriers];
    for(unsigned int i = 0; i < numCouriers; i++){
        couriers[i] = new Courier(i, this, printer, bank);
    }
}

WATCardOffice::~WATCardOffice(){
    for(unsigned int i = 0; i < numCouriers; i++){
        delete couriers[i];
    }
    delete [] couriers;
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ){
    pendingJob = new Job(Args(bank, sid, new WATCard(), amount));

    //courier prints complete transfer
    printer.print(Printer::WATCardOffice, 'T', sid, amount);

    return pendingJob->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ){
    pendingJob = new Job(Args(bank, sid, card, amount));

    //courier prints complete transfer
    printer.print(Printer::WATCardOffice, 'T', sid, amount);

    return pendingJob->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
    if(jobDone) return NULL;
    Job *tempJob = pendingJob;
    pendingJob = NULL;
    return tempJob;
}

void WATCardOffice::main(){
    //office starts
    printer.print(Printer::WATCardOffice, 'S');

    for(;;){
        _Accept(~WATCardOffice){
            jobDone = true;
            for(unsigned int i = 0; i < numCouriers; i++){
                _Accept(requestWork);
            }
            break;
        }
        or _When(pendingJob == NULL) _Accept(create, transfer);
        or _When(pendingJob != NULL) _Accept(requestWork);
    }

    //office finished
    printer.print(Printer::WATCardOffice, 'F');
}

/*------------------------------------------------------------
 *                  Courier Implementation
 * -----------------------------------------------------------
 */
WATCardOffice::Courier::Courier(unsigned int id, WATCardOffice *office, Printer &printer, Bank &bank):
    id(id), office(office), printer(printer), bank(bank){
    }

void WATCardOffice::Courier::main(){

    //courier starts
    printer.print(Printer::Courier, id, 'S');

    for(;;){
        Job *job = office->requestWork();
        if(job == NULL) break;

        //possible to drop card
        if(mprng(CHANCE_LOST - 1) == 0){

            job->result.exception(new Lost);

            //delete card if lost
            if(job->args.card != NULL) delete job->args.card;
        }
        else {
            //starts transfer
            printer.print(Printer::Courier, id, 't', job->args.sid, job->args.amount);
            //withdraw from bank
            bank.withdraw(job->args.sid, job->args.amount);

            if(job->args.card == NULL) job->args.card = new WATCard();

            job->args.card->deposit(job->args.amount);

            //conplete tranfer
            printer.print(Printer::Courier, id, 'T', job->args.sid, job->args.amount);
            //future available
            job->result.delivery(job->args.card);
        }
        delete job;
    }
    //conplete tranfer
    printer.print(Printer::Courier, id, 'F');
}
