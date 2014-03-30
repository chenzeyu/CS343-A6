// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#ifndef TRUCK_H
#define TRUCK_H

_Monitor Printer;
_Task NameServer;
_Task BottlingPlant;

_Task Truck {
    Printer &printer;
    NameServer &nameServer;
    BottlingPlant &plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    enum States {Start = 'S',
            DeliveryPickedUp = 'P',
            DeliveryStart = 'd',
            DeliveryFail = 'U',
            DeliveryFinished = 'D',
            Finished = 'F'};

    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif