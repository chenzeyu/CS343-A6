// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#include "parent.h"

const unsigned int LOW = 1;
const unsigned int HIGH = 3;
Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay):
    printer(prt),
    bank(bank),
    numStudents(numStudents),
    delay(parentalDelay){
    }

void Parent::main(){
    printer.print(Printer::Parent, 'S');
    for(;;){
        _Accept(~Parent){
            break;
        }
        _Else{
            //yield before perform
            yield(delay);

            //generate student and amount of money
            unsigned int student = mprng(numStudents - 1);
            unsigned int money = mprng(LOW,HIGH);

            //depoist
            bank.deposit(student, money);

            //print deposit message
            printer.print(Printer::Parent, 'D', student, money);
        }
    }
    //finished
    printer.print(Printer::Parent, 'F');
}
