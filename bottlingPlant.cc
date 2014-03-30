// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#include "bottlingPlant.h"
#include "mprng.h"
#include "printer.h"
#include "truck.h"
#include "vendingMachine.h"

BottlingPlant::BottlingPlant(Printer &printer, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments) :
        printer(printer),
        nameServer(nameServer),
        numVendingMachines(numVendingMachines),
        maxShippedPerFlavour(maxShippedPerFlavour),
        maxStockPerFlavour(maxStockPerFlavour),
        timeBetweenShipments(timeBetweenShipments),
        shuttingDown(false) {}

/*
 * Called by the truck to pick up a shipment. cargo is
 * filled up with different flavours of soda.
 * Returns true if the plant is shutting down and false
 * if the shipment was completed.
 */
bool BottlingPlant::getShipment(unsigned int cargo[]) {
    // Return true to indicate the plant is shutting down
    if (shuttingDown) return true;

    // Transfer stock to truck
    for (unsigned int f=0; f<VendingMachine::NUM_FLAVOURS; f++) {
        unsigned int amount = std::min(stock[f], maxShippedPerFlavour);
        cargo[f] = amount;
        stock[f] -= amount;
    }

    printer.print(Printer::BottlingPlant, (char)Shipping);
    return false;
}

void BottlingPlant::main() {
    printer.print(Printer::BottlingPlant, (char)Start);
    stock = new unsigned int[VendingMachine::NUM_FLAVOURS];
    std::fill(stock, stock+VendingMachine::NUM_FLAVOURS, 0);
    {
        Truck truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour);
        while (true) {
            // Simulate time to produce soda
            yield(timeBetweenShipments);

            // Produce soda
            unsigned int totalProduced = 0;
            for (unsigned int f=0; f<VendingMachine::NUM_FLAVOURS; f++) {
                unsigned int amount = mprng(0, maxShippedPerFlavour);
                stock[f] = amount;
                totalProduced += amount;
            }
            printer.print(Printer::BottlingPlant, (char)Generating, totalProduced);

            // Wait for truck to pick up soda or for plant to shutdown
            _Accept(~BottlingPlant) {
                // Begin shutdown
                shuttingDown = true;
                break;
            } or _Accept(getShipment) {
            }
        }

        // Wait for truck to finish
        _Accept(getShipment);
    }

    delete [] stock;
    printer.print(Printer::BottlingPlant, (char)Finished);
}