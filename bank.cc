Bank::Bank(unsigned int numStudents):numStudents(numStudents){
    accountConditions = new uCondition[numStudents];
    studentAccounts = new int[numStudents];
}

Bank::~Bank(){
    delete [] bankAccounts;
    delete [] accountConditions;
}

/* called by parents to deposit money
 * into student's account
 * will signal all blocked withdraw
 */
Bank::deposit(unsigned int id, unsigned int amount){
    //add money
    studentAccounts[id] += amount;
    //signal if blocked
    while(!accountConditions[id].empty){
        accountConditions.signal();
    }
}

/* called by couriers to deduct money
 * will block if there's insufficient funds
 */
Bank::withdraw(unsigned int id, unsigned int amount){

    //wait until there's sufficient funds
    while(studentAccounts[id] < amount){
        accountConditions[id].wait();
    }
    studentAccounts[id] -= amount;

}
