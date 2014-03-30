// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef STUDENT_H
#define STUDENT_H
_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif //student.h
