# NUBPay

NUBPay is a secure and organized payment system exclusively designed for NUB students. It allows users to create accounts, log in, deposit money, withdraw money, transfer funds, and view transaction history.

## Features

- **Account Management**:
  - Create a new account with a unique account number and password.
  - Login with account credentials.
  - Logout functionality.

- **Transactions**:
  - Deposit money (with a maximum limit of Tk. 50,000 per transaction).
  - Withdraw money (ensures sufficient balance).
  - Transfer money to other accounts.
  - View transaction history.

- **Security**:
  - Passwords are masked during input.
  - Password validation ensures at least 4 digits.
  - Prevents transferring money to the same account.

- **User-Friendly Interface**:
  - Clear and organized menus.
  - Loading animations for better user experience.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC).
- A terminal or command prompt to run the program.

### Installation

1. Clone the repository or download the source code.
2. Ensure all required files (e.g., `transaction.h`, `utils.h`) are in the same directory as `main.c`.
3. Create account.txt and transaction.txt
4. Compile the program using a C compiler:
   ```bash
   gcc main.c transaction.c -o NUBPay

### Limitations

 - The program currently supports only text-based input and output.
 - Passwords are stored as plain integers in the file, which may not be secure.
 - Future Enhancements Encrypt passwords before storing them in the file.
 - Implement multi-threading for better performance.

### Contributors

Saruf, Jakaria, Nur, Shihab


### License

This project is for educational purposes only and is not licensed for commercial use.
