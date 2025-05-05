#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    int acc_no;
    char type[10];       // Transaction type: "Deposit" or "Withdraw"
    float amount;
    char date[50];       // Date of transaction
    char time[50];       // Time of transaction
} Transaction;

void log_transaction(int acc_no, const char* type, float amount);
void display_transaction_history(int acc_no);

#endif
