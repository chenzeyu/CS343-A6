// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#include "truck.h"
#include "bottlingPlant.h"
#include "mprng.h"
#include "nameServer.h"
#include "printer.h"
#include "vendingMachine.h"

Truck::Truck(Printer &printer, NameServer &nameServer, BottlingPlant &plant,
            unsigned int numVendingMachines, unsigned int maxStockPerFlavour) :
            printer(printer),
            nameServer(nameServer),
            plant(plant),
            numVendingMachines(numVendingMachines),
            maxStockPerFlavour(maxStockPerFlavour) {}

/*
 * main function for thread. Will collect soda from plant and deliver to each
 * vending machine. Will terminate upon recieving signal from plant while trying
 * to collect soda.
 */
void Truck::main() {
    printer.print(Printer::Truck, (char)Start);

    unsigned int numFlavours = VendingMachine::NUM_FLAVOURS;
    unsigned int* cargo = new unsigned int[numFlavours];
    VendingMachine** vendingMachines = nameServer.getMachineList();
    
    while (true) {
        // Get some Tim's
        yield(mprng(1, 10));

        // Get soda
        if (plant.getShipment(cargo)) break;

        // Sum total number of sodas recieved
        unsigned int total = 0;
        for (unsigned int f=0; f<numFlavours; f++) {
            total += cargo[f];
        }

        printer.print(Printer::Truck, (char)DeliveryPickedUp, total);

        // Restock vending machines
        for (unsigned int m=0; m<numVendingMachines && total > 0; m++) {
            printer.print(Printer::Truck, (char)DeliveryStart, m, total);

            // Begin restock for mth vending machine
            unsigned int* inventory = vendingMachines[m]->inventory();

            // Top up each flavour
            unsigned int notReplenished = 0;
            for (unsigned int f=0; f<numFlavours; f++) {
                unsigned int amount = std::min(maxStockPerFlavour - inventory[f], cargo[f]);
                inventory[f] += amount;
                cargo[f] -= amount;
                total -= amount;
                notReplenished += maxStockPerFlavour - inventory[f];
            }

            if (notReplenished > 0) printer.print(Printer::Truck, (char)DeliveryFail, m, notReplenished);
            printer.print(Printer::Truck, (char)DeliveryFinished, m, total);

            // Indicate restock has completed
            vendingMachines[m]->restocked();
        }
    }

    delete [] cargo;

    printer.print(Printer::Truck, (char)Finished);
}