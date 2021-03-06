// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include <uC++.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watcardOffice.h"
#include "nameServer.h"
#include "vendingMachine.h"
#include "bottlingPlant.h"
#include "student.h"
#include "mprng.h"

using namespace std;

bool convert(int &val, char *buffer ) { // convert C string to integer
    std::stringstream ss( buffer ); // connect stream and buffer
    ss >> dec >> val; // convert integer from buffer
    return ! ss.fail() && // conversion successful ?
        // characters after conversion all blank ?
        string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

/**
 * print usage of the program
 */
static void usage(char **argv) {
    cerr << "Usage: " << argv[0] << " [ config-file [ random-seed (> 0) ] ]"
        << endl;
    exit(EXIT_FAILURE);
}

void uMain::main() {

    if (argc > 3) {
        usage(argv);
    }

    // config file
    string configFile = "soda.config";
    if (argc >= 2) {
        configFile = string(argv[1]);
    }

    // seed
    int seed = getpid();
    if (argc >= 3 && (!convert(seed, argv[2]) || seed <= 0)) {
        usage(argv);
    }
    mprng.seed(seed);

    // parse the config file
    ConfigParms params;
    processConfigFile(configFile.c_str(), params);

    // setup printer
    Printer printer(params.numStudents, params.numVendingMachines, params.numCouriers);

    // setup bank
    Bank bank(params.numStudents);

    {
        // setup parent
        Parent parent(printer, bank, params.numStudents, params.parentalDelay);

        // setup office
        WATCardOffice office(printer, bank, params.numCouriers);

        // setup nameserver
        NameServer nameserver(printer, params.numVendingMachines, params.numStudents);

        VendingMachine *vendingMachines[params.numVendingMachines];
        {
            // setup vendingMachine
            for (unsigned int m = 0; m < params.numVendingMachines; m++) {
                vendingMachines[m] = new VendingMachine(printer, nameserver, m, params.sodaCost, params.maxStockPerFlavour);
            }

            //setup bottling plant
            BottlingPlant plant(printer, nameserver, params.numVendingMachines, params.maxShippedPerFlavour, params.maxStockPerFlavour, params.timeBetweenShipments);

            //set up students
            Student *students[params.numStudents];
            for (unsigned int s = 0; s < params.numStudents; s++) {
                students[s] = new Student(printer, nameserver, office, s, params.maxPurchases);
            }

            // cleaning up
            for (unsigned int s = 0; s < params.numStudents; s++) {
                delete students[s];
            }
        }

        for (unsigned int m = 0; m < params.numVendingMachines; m++) {
            delete vendingMachines[m];
        }

    }
}
