// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#include "vendingMachine.h"
#include "nameServer.h"
#include "printer.h"
#include "watcard.h"

VendingMachine::VendingMachine( Printer &printer, NameServer &nameServer, unsigned int id,
                unsigned int sodaCost, unsigned int maxStockPerFlavour ) :
        printer(printer),
        nameServer(nameServer),
        id(id), sodaCost(sodaCost),
        maxStockPerFlavour(maxStockPerFlavour),
        stocking(false) {

    printer.print(Printer::Vending, id, (char)Start, sodaCost);
    sodaCounts = new unsigned int[NUM_FLAVOURS];
    std::fill(sodaCounts, sodaCounts + NUM_FLAVOURS, 0);
    nameServer.VMregister(this);
}

VendingMachine::~VendingMachine() {
    delete [] sodaCounts;
}

/*
 * Attempt to purchase a particular flavour of soda. If a student attempts
 * to call this method during restocking that student will wait on a bench
 * until restocking is complete.
 * Will return:
 * VendingMachine::STOCK if the vending machine is out of that flavour,
 * VendingMachine::FUNDS if the student has insufficient funds or
 * VendingMachine::BUY if the purchase was successful.
 */
VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard &card) {
    Status status;

    if (sodaCounts[flavour] == 0) {
        // Out of student's favourite flavour
        status = STOCK;
    } else if (card.getBalance() < sodaCost) {
        // Student has insufficient funds
        status = FUNDS;
    } else {
        // Purchase successful, decrease soda count and remove funds
        card.withdraw(sodaCost);
        sodaCounts[flavour] -= 1;
        status = BUY;
        printer.print(Printer::Vending, id, (char)Bought, flavour, sodaCounts[flavour]);
    }

    return status;
}

/*
 * Return a pointer to the vending machines inventory.
 * This is called by the truck during restocking.
 */
unsigned int* VendingMachine::inventory() {
    printer.print(Printer::Vending, id, (char)RestockStart);
    stocking = true;
    return sodaCounts;
}

/*
 * Called by the truck to indicate restocking is complete.
 */
void VendingMachine::restocked() {
    printer.print(Printer::Vending, id, (char)RestockFinished);
    stocking = false;
}

/*
 * Returns cost per soda.
 */
_Nomutex unsigned int VendingMachine::cost() {
    return sodaCost;
}

/*
 * Returns the ID of the vending machine.
 */
_Nomutex unsigned int VendingMachine::getId() {
    return id;
}

/*
 * main function for thread. Will wait until the destructor is called.
 */
void VendingMachine::main() {
    while (true) {
        _Accept(~VendingMachine) {break;}
        or _Accept(inventory, restocked) {}
        or _When(stocking == false) _Accept(buy) {}
    }
    
    printer.print(Printer::Vending, id, (char)Finished);
}
