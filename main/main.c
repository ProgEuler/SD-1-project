#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#include "transaction.h"
#include "utils.h"
#include <ctype.h>

void user_menu();
void login_user();
void logout_user();
void user_form();
void welcome();
void create_acc();
void deposit();
void withdraw();
void check_balance();
void get_time(char*);
void get_date(char*);
void display_time_date();
void show_loading(const char* message);
void clear_screen();
void to_uppercase(char* str);
int get_password();
void transfer();
void transaction_history();

const char* ACCOUNT_FILE = "account.txt";
int logged_in = 0;

typedef struct {
    char name[50];
    int acc_no;
    float balance;
    int pass;
} Account;

int main(){
    welcome();
    return 0;
}

void welcome() {
    clear_screen();
    system("cls");

    printf("\n\n");
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t||                                                 ||\n");
    printf("\t\t\t||               WELCOME TO NUBPay                 ||\n");
    printf("\t\t\t||                                                 ||\n");
    printf("\t\t\t=====================================================\n");
    printf("\t\t\t||                                                 ||\n");
    printf("\t\t\t||   A Secure and Organized Payment System         ||\n");
    printf("\t\t\t||   Exclusively for NUB Students                  ||\n");
    printf("\t\t\t||                                                 ||\n");
    printf("\t\t\t=====================================================\n");

    printf("\n\n");
    display_time_date();

    printf("\n\t\t--------------------------------------------------------------------------\n");
    printf("\t\t\t\t\tDeveloped By: Saruf, Jakaria, Shihab, Nur\n");
    printf("\t\t--------------------------------------------------------------------------\n");
    printf("\n\t\t\tSome test account: \n");
    printf("\t\t\t acc_no : 123   pass: 4455\n");
    printf("\t\t\t acc_no : 1857  pass: 321\n");
    printf("\n\n\t\t\tPress any key to continue...");
    getch();
    user_form();
}
void user_form(){
    int option;
    while (1)
    {
        printf("\n\t1. Login");
        printf("\n\t\t\tDont have an account?");
        printf("\n\t2. Register");
        printf("\n\t3. Exit");
        printf("\n\tSelect an option: ");
        scanf("%d", &option);
        switch (option)
        {
        case 1: login_user();
            break;
        case 2: create_acc();
            break;
        case 3:
            printf("\t\t\tThank you for using NUBPay.\n\n");
            show_loading("Exiting");
            return;
            break;
        default: printf("\nInvalid option");
            break;
        }
    }
}
void create_acc() {
    Account acc;

    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL) {
        printf("\n\t\t\tUnable to open account file!");
        return;
    }

    clear_screen();
    printf("\n\n\t\t\t===================================================\n");
    printf("\n\t\t\t\t           REGISTRATION PAGE            \n");
    printf("\n\t\t\t====================================================\n");

    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

    printf("\n\t\t\tEnter your full name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0'; // Remove newline character

    // Validate account number
    while (1) {
        printf("\t\t\tEnter your account number: ");
        if (scanf("%d", &acc.acc_no) == 1) break;
        else {
            printf("\t\t\tInvalid input! Please enter numbers only.\n");
            while ((c = getchar()) != '\n' && c != EOF); // Clear input buffer
        }
    }
    while ((c = getchar()) != '\n' && c != EOF);

    // Validate password
    while (1) {
        printf("\t\t\tCreate a unique password (at least 4 digits): ");
        char password[50];
        scanf("%s", password);

        int is_valid = 1;
        int length = strlen(password);

        // Check if the password contains only digits and is at least 4 characters long
        if (length < 4) {
            is_valid = 0;
        } else {
            for (int i = 0; i < length; i++) {
                if (!isdigit(password[i])) {
                    is_valid = 0;
                    break;
                }
            }
        }

        if (is_valid) {
            acc.pass = atoi(password); // Convert the valid password to an integer
            break;
        } else {
            printf("\n\t\t\tInvalid password! Please enter at least 4 digits.\n");
        }
    }

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file); // Save the account details
    show_loading("Creating your account");

    clear_screen();
    to_uppercase(acc.name);

    printf("\n\n\t\t\t========================================\n");
    printf("\n\t\t\t  Account created successfully!");
    printf("\n\t\t\t  WELCOME, %s!\n", acc.name);
    printf("\n\t\t\t========================================\n");


    fclose(file);
}

void login_user() {
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("\n\t\t\tUnable to open account file!");
        return;
    }

    int acc_no;
    int pass;
    Account acc_r;
    char c;

    clear_screen();
    printf("\n\n\t\t\t===================================================\n");
    printf("\n\t\t\t\t           LOGIN PAGE            \n");
    printf("\n\t\t\t====================================================\n");

    printf("\n\t\t\tEnter your account number: ");
    scanf("%d", &acc_no);
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\t\t\tEnter your password: ");
    pass = get_password(); // Read password as an integer

    while (fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == acc_no && acc_r.pass == pass) { // Compare account number and password

            fclose(file);

            show_loading("\n\n\t\t\tLogging in");
            clear_screen();
            to_uppercase(acc_r.name);

            printf("\n\n\t\t\t====================================================\n");
            printf("\n\t\t\t  Welcome, %s!\t\t Account No. %d\n", acc_r.name, acc_r.acc_no);

            printf("\n\t\t\t====================================================\n");
            user_menu();
            logged_in = acc_no;
            return; // Successful login
        }
    }

    fclose(file);
    printf("\n\n\t\t\tInvalid credentials. Please try again.\n");
}

void logout_user(){
    welcome();
}
void user_menu(){
    while (1)
    {
        int choice;

        printf("\n\n\t1. deposit money\n");
        printf("\t2. withdraw money\n");
        printf("\t3. check balance\n");
        printf("\t4. transactions\n");
        printf("\t5. Logout\n");
        printf("\t6. Transfer money\n");
        printf("\t7. exit\n\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: deposit();
            break;
        case 2: withdraw();
            break;
        case 3: check_balance();
            break;
        case 4:
            transaction_history();
            break;
        case 5: logout_user();
            break;
        case 6: transfer();
            break;
        case 7:
            printf("\n\t\t\tThank your for being with us");
            exit(0);
            break;

        default:
            printf("Invalid choice");
            break;
        }
    }
}
void deposit(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("Unable to open account file!!");
        return;
    }

    int acc_no;
    int acc_pass;
    float money;
    Account acc_r;

    printf("\n\t\tEnter account no: ");
    scanf("%d", &acc_no);
    printf("\n\t\tEnter password: ");
    acc_pass = get_password();
    printf("\n\t\tEnter amount to deposit: ");
    scanf("%f", &money);

    int flag = 0;

    while(fread(&acc_r, sizeof(acc_r), 1, file)){
        if(acc_r.acc_no == acc_no){
            if(acc_r.pass == acc_pass){
                if(money <= 0){
                    fclose(file);
                    show_loading("\n\t\t\tProcessing deposit");
                    clear_screen();
                    printf("\n\t\t\tInvalid amount!");
                    return;
                }
                acc_r.balance += money;
                fseek(file, -(long)sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                show_loading("\n\t\t\tProcessing deposit");
                printf("\n\t\t\tSuccessfully deposited Tk. %.2f \n\n\t\t\tNew balance is Tk. %.2f", money, acc_r.balance);

                // Log the transaction
                log_transaction(acc_no, "Deposit", money);

                flag = 1;
                break;
            }else {
                fclose(file);
                show_loading("\n\t\t\tProcessing deposit");
                clear_screen();
                printf("\n\t\t\tInvalid password!");
                return;
            }
        }
    }
    if(!flag) printf("\nAccount no. %d was not found in records.", acc_no);
    fclose(file);
}
void withdraw(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("Unable to open account file!!");
        return;
    }

    int acc_no;
    int acc_pass;
    float money;
    Account acc_r;

    printf("\n\t\tEnter account no: ");
    scanf("%d", &acc_no);
    printf("\n\t\tEnter password: ");
    acc_pass = get_password();
    printf("\n\t\tEnter amount to withdraw: ");
    scanf("%f", &money);

    while(fread(&acc_r, sizeof(acc_r), 1, file)){
        if(acc_r.acc_no == acc_no){
            if(acc_r.pass == acc_pass){
                if(money <= 0){
                    fclose(file);
                    show_loading("\n\t\t\tProcessing withdrawal");
                    clear_screen();
                    printf("\n\t\t\tInvalid amount!");
                    return;
                }
                else if(acc_r.balance >= money){
                    acc_r.balance -= money;
                    fseek(file, -(long)sizeof(acc_r), SEEK_CUR);
                    fwrite(&acc_r, sizeof(acc_r), 1, file);
                    fclose(file);

                    show_loading("\n\t\t\tProcessing withdrawal");
                    // Log the transaction
                    log_transaction(acc_no, "Withdraw", money);

                    return;
                }else {
                    fclose(file);
                    show_loading("\n\t\t\tProcessing withdrawal");
                    clear_screen();
                    printf("\n\t\t\tInsufficient balance!");
                    return;
                }
            }else {
                fclose(file);
                show_loading("\n\t\t\tProcessing withdrawal");
                clear_screen();
                printf("\n\t\t\tInvalid password!");
                return;
            }
        }

        fclose(file);
        printf("\n\t\t\tAccount no. %d was not found in records.", acc_no);
    }
}
void check_balance(){
    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if(file == NULL){
        printf("\n\tUnable to open file!!");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("\n\tEnter your account number: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.acc_no == acc_no){
            show_loading("\n\t\t\tFetching balance");
            clear_screen();
            printf("\n\n\t\t\t====================================================\n");
            printf("\n\t\t\t\tYour current balance is Tk. %.2f\n", acc_read.balance);
            printf("\n\t\t\t====================================================\n");
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\n\t\t\t Account No: %d is not found", acc_no);
}
void get_time(char* buffer){
    time_t rawtime;
    struct tm *current_time;

    time(&rawtime);
    current_time = localtime(&rawtime);

    strftime(buffer, 50, "%I:%M:%S %p",
    current_time);
}
void get_date(char* buffer){
    time_t rawtime;
    struct tm *current_time;

    time(&rawtime);
    current_time = localtime(&rawtime);

    strftime(buffer, 50, "%d %B %Y | %A",
        current_time);
}
void display_time_date(){
    char time[50];
    get_time(time);
    char date[50];
    get_date(date);

    printf("\t\t\tTime: %s\t Datte: %s\n", time, date);
    return;
}
void clear_screen() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void show_loading(const char* message) {
    printf("\n\n\t\t\t%s", message);
    fflush(stdout);
    for (int i = 0; i < 3; i++) {
        usleep(100000);
        printf(".");
        fflush(stdout);
    }
    sleep(1);
}
void to_uppercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}
int get_password(){
    int pass = 0;
    char ch;
    while ((ch = getch()) != '\r') { // Read password without echoing
        if (ch == '\b') { // Handle backspace
            if (pass > 0) {
                printf("\b \b");
                pass /= 10;
            }
        } else if (ch >= '0' && ch <= '9') {
            printf("*");
            pass = pass * 10 + (ch - '0');
        }
    }
    return pass;
}
void transfer() {
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if (file == NULL) {
        printf("Unable to open account file!!");
        return;
    }

    int sender_acc_no = logged_in;
    int recipient_acc_no, sender_pass;
    float amount;

    Account acc_r, sender, recipient;
    int recipient_found = 0;

    printf("\n\t\tEnter your password: ");
    sender_pass = get_password();

    while(fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == sender_acc_no) {
            if (acc_r.pass == sender_pass) {
                sender = acc_r;
                break;
            } else {
                printf("\n\t\t\tWrong password!");
                fclose(file);
                return;
            }
        }
    }

    printf("\n\t\tEnter recipient's account number: ");
    scanf("%d", &recipient_acc_no);

    while(fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == recipient_acc_no) {
            recipient_found = 1;
            recipient = acc_r;
            break;
        }
    }
    if (!recipient_found) {
        printf("\n\t\t\tAccount no. %d was not found in records.", recipient_acc_no);
        fclose(file);
        return;
    }

    printf("\n\t\tEnter amount to transfer: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\n\t\t\tInvalid amount!");
        fclose(file);
        return;
    }

    if (sender.balance < amount) {
        printf("\n\t\t\tInsufficient balance!");
        fclose(file);
        return;
    }

    // Update balances
    sender.balance -= amount;
    recipient.balance += amount;

    // Update the file
    rewind(file);
    while (fread(&acc_r, sizeof(acc_r), 1, file)) {
        if (acc_r.acc_no == sender_acc_no) {
            fseek(file, -(long)sizeof(acc_r), SEEK_CUR);
            fwrite(&sender, sizeof(sender), 1, file);
        }
        if (acc_r.acc_no == recipient_acc_no) {
            fseek(file, -(long)sizeof(acc_r), SEEK_CUR);
            fwrite(&recipient, sizeof(recipient), 1, file);
        }
    }

    fclose(file);

    // Log the transactions
    log_transaction(sender_acc_no, "Transfer Out", amount);
    log_transaction(recipient_acc_no, "Transfer In", amount);

    show_loading("\n\t\t\tProcessing transfer");
    printf("\n\t\t\tSuccessfully transferred Tk. %.2f to Account No. %d", amount, recipient_acc_no);
}
void transaction_history(){
    int acc_no, acc_pass;

    printf("\n\tEnter your account number: ");
    scanf("%d", &acc_no);
    // printf("\n\tEnter your password: ");
    // acc_pass = get_password();
    display_transaction_history(acc_no);
}
