// CS343 - Concurrent and Parallel Programming
// Winter, 2014
// Assignment 6
#ifndef PARENT_H
#define PARENT_H
_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};
#endif
