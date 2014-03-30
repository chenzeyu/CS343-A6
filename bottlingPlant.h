// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

_Monitor Printer;
_Task NameServer;

_Task BottlingPlant {
    Printer &printer;
    NameServer &nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int* stock;
    bool shuttingDown;
    enum States {Start = 'S',
            Generating = 'G',
            Shipping = 'P',
            Finished = 'F'};

   void main();
  public:
    BottlingPlant( Printer &printer, NameServer &nameServer, unsigned int numVendingMachines,
        unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
        unsigned int timeBetweenShipments );
    bool getShipment(unsigned int cargo[]);
};

#endif