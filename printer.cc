// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "printer.h"
#include <iostream>
using namespace std;

const unsigned int NUM_KINDS = 5;
const int DUMMY_VALUE = -1;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
    numStudents(numStudents), numMachines(numVendingMachines), numCouriers(numCouriers) {

        //set up helpers
        numColumns = NUM_KINDS + students + machines + couriers;
        items = new printingItem[numColumns];
        for (unsigned int i = 0; i < numColumns; i++) {
            items[i].hasValues = false;
        }

        // Print header
        cout << "Parent\tWATOff\tNames\tTruck\tPlant\t";
        for (unsigned int i = 0; i < numStudents; i++) {
            cout << "Stud" << i << '\t';
        }
        for (unsigned int i = 0; i < numMachines; i++) {
            cout << "Mach" << i << '\t';
        }
        for (unsigned int i = 0; i < numCouriers; i++) {
            cout << "Cour" << i << '\t';
        }

        cout << endl;

        for (unsigned int i = 0; i < numColumns; i++) {
            cout << "=======" << '\t';
        }

        cout << endl;

    }

Printer::~Printer () {
    cout << "***********************" << endl;
    delete [] items;
}

void Printer::flush () {
    for (unsigned int i = 0; i < numColumns; i++) {
        if (items[i].hasValues) {
            cout << items[i].state;
            if (items[i].value1 != DUMMY_VALUE) {
                cout << items[i].value1;
                if (items[i].value2 != DUMMY_VALUE) {
                    cout << ',' << items[i].value2;
                }
            }
            items[i].hasValues = false;
        }
        cout << "\t";
    }
    cout << endl;
}

_Mutex void Printer::printMaster( unsigned int id, char state, int value1, int value2) {
    if (state == 'F') {

        unsigned int i;
        for (i = 0; i < numColumns; i++) {
            if (items[id].hasValues) {
                flush();
                break;
            }
        }

        //print finished
        for (i = 0; i < numColumns; i++) {
            if (id != i)
                cout << "...";
            else
                cout << state;
            cout << "\t";
        }

        cout << endl;
    }

    else if (items[id].hasValues) {
        flush();
    }

    if (state != 'F') {
        items[id].value1 = value1;
        items[id].value2 = value2;
        items[id].hasValues = true;
        items[id].state = state;
    }
}

unsigned int Printer::calculateID(Kind k){
    unsigned int id = 0;
    switch (k) {
        case Student:
            id = NUM_KINDS;
            break;
        case Vending:
            id = NUM_KINDS + numStudents;
            break;
        case Courier:
            id = NUM_KINDS + numStudents + numMachines;
            break;
        default:
            id = (unsigned int) k;
            break;
    }
    return id;
}

//implement public print functions using printMaster
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {
    unsigned int id = calculateID(kind);
    printMaster(id + lid, state, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {

    printMaster(id + lid, state, value1, value2);
}
void Printer::print( Kind kind, char state, int value1 ) {
    printMaster(kind, state, value1, DUMMY_VALUE);
}

void Printer::print( Kind kind, char state ) {
    printMaster(kind, state, DUMMY_VALUE, DUMMY_VALUE);
}

void Printer::print( Kind kind, char state, int value1, int value2 ) {
    print(kind, 0, state, value1, value2);
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
    print(kind, lid, state, DUMMY_VALUE, DUMMY_VALUE);
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {
    print(kind, lid, state, value1, DUMMY_VALUE);
}
