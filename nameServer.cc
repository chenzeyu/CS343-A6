// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#include "nameServer.h"
#include "printer.h"
#include "vendingMachine.h"

NameServer::NameServer(Printer &printer, unsigned int numVendingMachines, unsigned int numStudents) :
        printer(printer),
        numVendingMachines(numVendingMachines),
        numStudents(numStudents),
        numRegistered(0) {

    printer.print(Printer::NameServer, (char)Start);

    // Create empty array for vending machines to be registered into
    vendingMachines = new VendingMachine*[numVendingMachines];

    // Allocate vending machines to students in a round-robin fashion
    nextVendingMachine = new unsigned int[numStudents];
    for (unsigned int i=0; i<numStudents; i++) {
        nextVendingMachine[i] = i % numVendingMachines;
    }
}

NameServer::~NameServer() {
    delete [] vendingMachines;
    delete [] nextVendingMachine;
}

/*
 * Register a vending machine to the name server.
 */
void NameServer::VMregister(VendingMachine *vendingMachine) {
    printer.print(Printer::NameServer, (char)Registering, vendingMachine->getId());
    vendingMachines[vendingMachine->getId()] = vendingMachine;
    numRegistered += 1;
}

/*
 * Called by a student to get a vending machine.
 */
VendingMachine *NameServer::getMachine(unsigned int id) {
    printer.print(Printer::NameServer, (char)NewMachine, id, nextVendingMachine[id]);
    VendingMachine *vm = vendingMachines[nextVendingMachine[id]];
    nextVendingMachine[id] = (nextVendingMachine[id]+1) % numVendingMachines;
    return vm;
}

/*
 * Return an array of all the vending machines in order.
 * Called by the truck when delivering soda.
 */
VendingMachine **NameServer::getMachineList() {
    return vendingMachines;
}

/*
 * main function of thread. Will wait for destructor to be called.
 */
void NameServer::main() {
    while (numRegistered < numVendingMachines) {
        _Accept(VMregister);
    }

    while (true) {
        _Accept(~NameServer) {break;}
        or _Accept(getMachine, getMachineList) {}
    }
    printer.print(Printer::NameServer, (char)Finished);
}