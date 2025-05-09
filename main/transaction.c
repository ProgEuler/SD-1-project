#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "utils.h"

const char* TRANSACTION_FILE = "transaction.txt";

void log_transaction(int acc_no, const char* type, float amount) {
    FILE *file = fopen(TRANSACTION_FILE, "ab+");
    if (file == NULL) {
        printf("\n\t\t\tUnable to open transaction file!");
        return;
    }

    Transaction txn;
    txn.acc_no = acc_no;
    strncpy(txn.type, type, sizeof(txn.type) - 1);
    txn.type[sizeof(txn.type) - 1] = '\0';
    txn.amount = amount;

    get_date(txn.date);
    get_time(txn.time);

    if (fwrite(&txn, sizeof(txn), 1, file) != 1) {
        printf("\n\t\t\tError writing transaction to file!");
    } else {

        clear_screen();
        printf("\n\t\t\t======================================================\n");
        printf("\n\t\t\tTransaction : %s of Tk. %.2f is successful\n", txn.type, txn.amount);
        printf("\n\t\t\tDate: %s\t Time: %s\n", txn.date, txn.time);
        printf("\n\t\t\t======================================================\n");
    }
    fclose(file);
}

void display_transaction_history(int acc_no) {
    FILE *file = fopen(TRANSACTION_FILE, "rb");
    if (file == NULL) {
        printf("\nUnable to open transaction file!");
        return;
    }

    Transaction txn;
    int found = 0;

    show_loading("Getting transaction history");
    clear_screen();
    printf("\n\n");
    printf("\n\t\t\t\tTransaction History for Account No: %d\n\n", acc_no);
    printf("\t\t\t----------------------------------------------------------\n");
    printf("\t\t\tType       Amount       \tDate                Time\n");
    printf("\t\t\t----------------------------------------------------------\n");

    while (fread(&txn, sizeof(txn), 1, file)) {
        if (txn.acc_no == acc_no) {
            printf("\t\t\t%-10s Tk. %-10.2f %-20s %-10s\n", txn.type, txn.amount, txn.date, txn.time);
            found = 1;
        }
    }

    if (!found) {
        printf("\n\t\t\tNo transactions found for this account.\n");
    }

    fclose(file);
}
