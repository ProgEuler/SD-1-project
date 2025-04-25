#include <stdio.h>
#include <string.h>
#include <unistd.h>

void user_menu();
int login_user();
void user_form();
void embeded_pass();
void welcome();
void create_acc();
void deposit();
void withdraw();
void check_balance();

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
    // while (1)
    {
        int choice;

        printf("1. create acount\n");
        printf("2. deposit money\n");
        printf("3. withdraw money\n");
        printf("4. check balance\n");
        printf("5. exit\n");
        printf("2. Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: create_acc();
            break;
        case 2: deposit();
            break;
        case 3: withdraw();
            break;
        case 4: check_balance();
            break;
        case 5:
            printf("Thank your for visiting");
            return 0;
            break;

        default:
            printf("Invalid choice");
            break;
        }
    }

}

void welcome(){
    printf("\n\n\n");
    printf("\t\t\t==== WELCOME TO NUBPay ==== \n");
    printf("\t\t\t A Organized Payment system for NUB Students " );
    printf("\n\n\n");
    printf("---------------------------------------------------------------------------------------------------------" );
    printf("\t\t\t\t\t DEVELOPED BY Saruf, Jakaria, Shihab, Nur" );
    user_form();
    return;
}
void user_form(){
    int option;
    while (1)
    {
        printf("\n1. Login");
        printf("\nDont have an account?");
        printf("\n2. create");
        printf("\n3. Exit");
        printf("\nSelect an option: ");
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
        printf("\nUnable to open file");
        return;
    }

    char c;
    do{
        c = getchar();
    }while (c != '\n' && c != EOF);

    printf("\nEnter your name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    int ind = strcspn(acc.name, "\n");
    acc.name[ind] = '\0';

    printf("Enter your account number: ");
    scanf("%d", &acc.acc_no);

    printf("creat a unique password: ");
    scanf("%d", &acc.pass);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("\n Account created successfully!");
}
int login_user(){
    FILE *file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL){
        printf("Unable to open a")
    }
}
void user_menu(){
    while (1)
    {
        int choice;
        printf("1. deposit money\n");
        printf("2. withdraw money\n");
        printf("3. check balance\n");
        printf("4. exit\n");
        printf("Enter your choice: ");
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
            printf("Thank your for visiting");
            return 0;
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
            printf("\nSuccessfully deposited Tk. %.2f \nNew balance is Tk. %.2f", money, acc_r.balance);
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
    printf("Enter amount to withdraw: ");
    scanf("%f", &money);

    while(fread(&acc_r, sizeof(acc_r), 1, file)){
        if(acc_r.acc_no == acc_no){
            if(acc_r.balance >= money){
                acc_r.balance -= money;
                fseek(file, -sizeof(acc_r), SEEK_CUR);
                fwrite(&acc_r, sizeof(acc_r), 1, file);
                fclose(file);
                printf("\nSuccessfully withdrawn Tk. %.2f \nNew balance is Tk. %.2f", money, acc_r.balance);
                return;
            }else {
                printf("Insufficient balance!");
                return;
            }
        }

        fclose(file);
        printf("\nAccount no. %d was not found in records.", acc_no);
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
    printf("Enter your account number: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1, file)){
        if(acc_read.acc_no == acc_no){
            printf("Your current balance is Tk. %.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("\n Account No: %d is not found", acc_no);
}
