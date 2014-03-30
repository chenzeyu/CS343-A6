#ifndef PRINTER_H
#define PRINTER_H
_Monitor Printer {
    private:
        unsigned int numStudents;
        unsigned int numVendingMachines;
        unsigned int numCouriers;
        unsigned int numColumns;
        struct printingItem{
            unsigned int value1;
            unsigned int value2;
            unsigned int id;
            char state;
            bool hasValues;
        }
        printingItem *items;
        _Mutex void Printer::printMaster( unsigned int id, char state, int value1, int value2);
        void flush();
        unsigned int calculateID(Kind k);

    public:
        enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
        Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
        void print( Kind kind, char state );
        void print( Kind kind, char state, int value1 );
        void print( Kind kind, char state, int value1, int value2 );
        void print( Kind kind, unsigned int lid, char state );
        void print( Kind kind, unsigned int lid, char state, int value1 );
        void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
        ~Printer();
};
#endif
