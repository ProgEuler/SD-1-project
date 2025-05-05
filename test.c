/* DigiPay - Simplified Digital Payment System in C (No file system) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_ID 50
#define MAX_PIN 10
#define MAX_TRANSACTIONS 100

typedef struct {
    char id[MAX_ID];
    char pin[MAX_PIN];
    float balance;
} User;

typedef struct {
    char userId[MAX_ID];
    char type[20];
    float amount;
} Transaction;

User users[MAX_USERS];
Transaction transactions[MAX_TRANSACTIONS];
int userCount = 0;
int transactionCount = 0;

/* Function declarations */
void mainMenu();
void registerUser();
bool loginUser(char userId[]);
void checkBalance(const char userId[]);
void deposit(const char userId[]);
void withdraw(const char userId[]);
void transfer(const char userId[]);
void payBill(const char userId[]);
void showTransactionHistory(const char userId[]);

/* Helper Functions */
User* findUser(const char* id);
void logTransaction(const char* userId, const char* type, float amount);

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    bool loggedIn = false;
    char userId[MAX_ID];

    while (1) {
        printf("\n=== DigiPay - Terminal Banking ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedIn = loginUser(userId);
                if (loggedIn) {
                    int userChoice;
                    while (loggedIn) {
                        printf("\nWelcome, %s\n", userId);
                        printf("1. Balance Inquiry\n");
                        printf("2. Deposit\n");
                        printf("3. Withdraw\n");
                        printf("4. Transfer\n");
                        printf("5. Pay Bill\n");
                        printf("6. Transaction History\n");
                        printf("7. Logout\n");
                        printf("Choose an option: ");
                        scanf("%d", &userChoice);

                        switch (userChoice) {
                            case 1: checkBalance(userId); break;
                            case 2: deposit(userId); break;
                            case 3: withdraw(userId); break;
                            case 4: transfer(userId); break;
                            case 5: payBill(userId); break;
                            case 6: showTransactionHistory(userId); break;
                            case 7: loggedIn = false; break;
                            default: printf("Invalid option.\n");
                        }
                    }
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid option.\n");
        }
    }
}

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return;
    }

    User user;
    printf("Enter new User ID: ");
    scanf("%s", user.id);
    printf("Enter 4-digit PIN: ");
    scanf("%s", user.pin);
    user.balance = 0.0;

    users[userCount++] = user;

    printf("User registered successfully!\n");
}

bool loginUser(char userId[]) {
    char pin[MAX_PIN];
    printf("Enter User ID: ");
    scanf("%s", userId);
    printf("Enter PIN: ");
    scanf("%s", pin);

    User* user = findUser(userId);
    if (user && strcmp(user->pin, pin) == 0) {
        printf("Login successful!\n");
        return true;
    }

    printf("Login failed.\n");
    return false;
}

void checkBalance(const char userId[]) {
    User* user = findUser(userId);
    if (user) {
        printf("Current Balance: %.2f\n", user->balance);
    }
}

void deposit(const char userId[]) {
    float amount;
    User* user = findUser(userId);
    if (!user) return;

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    user->balance += amount;
    logTransaction(userId, "Deposit", amount);
    printf("Deposit successful.\n");
}

void withdraw(const char userId[]) {
    float amount;
    User* user = findUser(userId);
    if (!user) return;

    printf("Enter withdraw amount: ");
    scanf("%f", &amount);

    if (user->balance >= amount) {
        user->balance -= amount;
        logTransaction(userId, "Withdraw", amount);
        printf("Withdrawal successful.\n");
    } else {
        printf("Insufficient balance.\n");
    }
}

void transfer(const char userId[]) {
    char receiverId[MAX_ID];
    float amount;
    User *sender = findUser(userId), *receiver;

    if (!sender) return;

    printf("Enter recipient User ID: ");
    scanf("%s", receiverId);
    printf("Enter transfer amount: ");
    scanf("%f", &amount);

    receiver = findUser(receiverId);
    if (!receiver) {
        printf("Recipient not found.\n");
        return;
    }

    if (sender->balance >= amount) {
        sender->balance -= amount;
        receiver->balance += amount;
        logTransaction(userId, "Transfer", amount);
        printf("Transfer successful.\n");
    } else {
        printf("Insufficient balance.\n");
    }
}

void payBill(const char userId[]) {
    char billType[20];
    float amount;
    User* user = findUser(userId);
    if (!user) return;

    printf("Enter bill type (e.g., electricity, water): ");
    scanf("%s", billType);
    printf("Enter bill amount: ");
    scanf("%f", &amount);

    if (user->balance >= amount) {
        user->balance -= amount;
        logTransaction(userId, billType, amount);
        printf("Bill paid successfully.\n");
    } else {
        printf("Insufficient balance.\n");
    }
}

void showTransactionHistory(const char userId[]) {
    printf("\n--- Transaction History for %s ---\n", userId);
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].userId, userId) == 0) {
            printf("%s - %s: %.2f\n", transactions[i].userId, transactions[i].type, transactions[i].amount);
        }
    }
}

User* findUser(const char* id) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].id, id) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

void logTransaction(const char* userId, const char* type, float amount) {
    if (transactionCount >= MAX_TRANSACTIONS) return;
    strcpy(transactions[transactionCount].userId, userId);
    strcpy(transactions[transactionCount].type, type);
    transactions[transactionCount].amount = amount;
    transactionCount++;
}
