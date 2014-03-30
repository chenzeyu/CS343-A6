// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

_Monitor Printer;
_Task NameServer;
class WATCard;

_Task VendingMachine {
    unsigned int id;  // id of the vending machine
    unsigned int sodaCost;  // cost per soda
    unsigned int* sodaCounts;  // number of soda left for each flavour
    unsigned int maxStockPerFlavour;  // max number of a flavour that can be in the machine
    Printer &printer;
    NameServer &nameServer;
    bool stocking;  // Indicates the vending machine is being restocked
    uCondition bench;  // Students wait on the bench if the vending machine is being restocked
    enum States {Start = 'S',
            RestockStart = 'r',
            RestockFinished = 'R',
            Bought = 'B',
            Finished = 'F'};

    void main();
  public:
    enum Flavours {F1, F2, F3, NUM_FLAVOURS};
    enum Status { BUY, STOCK, FUNDS };  // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif