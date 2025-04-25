#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>

void user_menu();
void login_user();
void user_form();
void welcome();
void create_acc();
void deposit();
void withdraw();
void check_balance();
void get_time(char*);
void get_date(char*);
void display_time_date();
void clear_screen();

const char* ACCOUNT_FILE = "account.dat";

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

void welcome(){
    clear_screen();
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t==== WELCOME TO NUBPay ==== \n");
    printf("\t\t A Organized Payment system for NUB Students " );
    printf("\n\n\n");
    display_time_date();
    printf("\n---------------------------------------------------------------------------------" );
    printf("\n\t\t\t\t\t DEVELOPED BY Saruf, Jakaria, Shihab, Nur\n\n\n" );
    user_form();
    return;
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
            printf("\nExiting Program.\n");
            return;
            break;

        default: printf("\nInvalid option");
            break;
        }
    }
}
void create_acc(){
    Account acc;

    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if(file == NULL) {
        printf("\n\\t\t\tUnable to open file");
        return;
    }

    char c;
    do{
        c = getchar();
    }while (c != '\n' && c != EOF);

    printf("\n\tEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';

    printf("\tEnter your account number: ");
    scanf("%d", &acc.acc_no);

    printf("\tcreat a unique password: ");
    scanf("%d", &acc.pass);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\n\t\t\tAccount created successfully!\n");
}
void login_user(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("Unable to open a");
        return;
    }

    int acc_no;
    int pass;
    Account acc_r;

    printf("\nEnter your account No: ");
    scanf("%d", &acc_no);
    printf("\nEnter your password: ");
    char ch;
    while((ch = getch()) != '\r') {
        if(ch == '\b') {
            if(pass > 0) {
                printf("\b \b");
                pass /= 10;
            }
        } else if(ch >= '0' && ch <= '9') {
            printf("*");
            pass = pass * 10 + (ch - '0');
        }
    }


    while(fread(&acc_r, sizeof(acc_r), 1, file)){
        if(acc_r.acc_no == acc_no && acc_r.pass == pass){
            fclose(file);
            printf("\n\n\t\t\tYou are logged in your account successfully!!");
            user_menu();
            return;
        }
    }
    fclose(file);
    printf("\n\t\t\tInvalid credantials, Try again.");
}
void user_menu(){
    while (1)
    {
        int choice;
        printf("\n\n\t1. deposit money\n");
        printf("\t2. withdraw money\n");
        printf("\t3. check balance\n");
        printf("\t4. exit\n");
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
    float money;
    Account acc_r;

    printf("\nEnter acc no: ");
    scanf("%d", &acc_no);
    printf("Enter amount to deposit: ");
    scanf("%f", &money);

    while(fread(&acc_r, sizeof(acc_r), 1, file)){
        if(acc_r.acc_no == acc_no){
            acc_r.balance += money;
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);
            fclose(file);
            printf("\n\t\t\tSuccessfully deposited Tk. %.2f \n\n\t\t\tNew balance is Tk. %.2f", money, acc_r.balance);
            return;
        }

        fclose(file);
        printf("\nAccount no. %d was not found in records.", acc_no);
    }
}
void withdraw(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("Unable to open account file!!");
        return;
    }

    int acc_no;
    float money;
    Account acc_r;

    printf("\nEnter acc no: ");
    scanf("%d", &acc_no);
    printf("\nEnter amount to withdraw: ");
    scanf("%f", &money);

    while(fread(&acc_r, sizeof(acc_r), 1, file)){
        if(acc_r.acc_no == acc_no){
            if(acc_r.balance >= money){
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                fclose(file);
                printf("\n\t\t\tSuccessfully withdrawn Tk. %.2f \n\n\t\t\tNew balance is Tk. %.2f", money, acc_r.balance);
                return;
            }else {
                printf("Insufficient balance!");
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
        printf("\nUnable to open file!!");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.acc_no == acc_no){
            printf("\n\t\t\tYour current balance is Tk. %.2f", acc_read.balance);
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

    printf("\tTime: %s\n", time);
    printf("\tDate: %s\n", date);
    return;
}
void clear_screen() {
    #ifdef _Win32
      system("cls");
    #else
      system("clear");
    #endif
}
