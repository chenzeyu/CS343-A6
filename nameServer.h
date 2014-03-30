// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6

#ifndef NAMESERVER_H
#define NAMESERVER_H

_Monitor Printer;
_Task VendingMachine;

_Task NameServer {
    Printer &printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    VendingMachine **vendingMachines;
    unsigned int *nextVendingMachine;
    enum States {Start = 'S',
            Registering = 'R',
            NewMachine = 'N',
            Finished = 'F'};

    void main();
  public:
    NameServer( Printer &printer, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine(unsigned int id);
    VendingMachine **getMachineList();
};

#endif