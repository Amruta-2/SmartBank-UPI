#ifndef SMARTBANK_UPI_H
#define SMARTBANK_UPI_H

// ===========================================================
// SmartBank+UPI Header File
// -----------------------------------------------------------
// Contains global constants, data structures, and function
// declarations shared across all SmartBank source files.
// ===========================================================


// -----------------------------
// Configuration Macros
// -----------------------------
#define MAX_USERS 100               // Max number of users
#define MAX_TRANSACTIONS 100       // Max number of transactions per user


// -----------------------------
// User Data Structure
// -----------------------------
typedef struct {
    char name[50];                                 // Full name
    char phone[15];                                // Phone number (digits only)
    char upi_id[30];                               // Unique UPI ID (e.g., user@ybl)
    int upi_pin;                                   // 4-digit UPI PIN
    int atm_pin;                                   // 4-digit ATM PIN
    long long int atm_balance;                     // ATM balance
    long long int wallet_balance;                  // Wallet balance (deprecated/optional)
    long long int account_number;                  // Account number
    char atm_history[MAX_TRANSACTIONS][100];       // ATM transaction logs
    int atm_txn_count;                             // Number of ATM transactions
    char upi_history[MAX_TRANSACTIONS][100];       // UPI transaction logs
    int upi_txn_count;                             // Number of UPI transactions
    int login_attempts;                            // Count of login attempts
    long long upi_balance;                         // UPI wallet balance
} User;


// -----------------------------
// Global Variables
// -----------------------------
extern User users[MAX_USERS];        // Global user array
extern int user_count;               // Number of registered users


// -----------------------------
// Core Function Declarations
// -----------------------------
void registerUser();                 // New user registration
int login();                         // Login with UPI ID & PIN


// -----------------------------
// ATM Services
// -----------------------------
void showATMMenu(int userIndex);                  // ATM main menu
void checkATMBalance(int userIndex);              // View ATM balance
void depositATM(int userIndex);                   // Deposit money
void withdrawATM(int userIndex);                  // Withdraw money
void transferATM(int userIndex);                  // Transfer to another account
void showATMTransactionHistory(int userIndex);    // ATM transaction history

// -----------------------------
// UPI Wallet Services
// -----------------------------
void showUPIMenu(int userIndex);                  // UPI wallet menu
void checkBalance(int userIndex);                 // View UPI balance
void addMoney(int userIndex);                     // Add money to wallet
void sendMoney(int userIndex);                    // Send UPI to another
void showTransactionHistory(int userIndex);       // Show UPI transaction history

// -----------------------------
// Utility Functions
// -----------------------------
void clear();                                      // Clear screen or formatting
void printTime(char *buffer);                      // Get current timestamp
void addTransaction(char history[MAX_TRANSACTIONS][100], int *count, const char *entry); // Add transaction
void logToFile(const char *upi_id, const char *type, const char *entry);                // Log transaction to file

// -----------------------------
// Validation & Lookup
// -----------------------------
int isValidPhone(const char *phone);               // Validate mobile number
int isValidUPI(const char *upi);                   // Validate UPI format
int isUPIExists(const char *upi);                  // Check if UPI already exists
int isPhoneExists(const char *phone);              // Check if phone already exists
int findUserByUPI(const char *upi_id);             // Get user index by UPI ID

// -----------------------------
// Persistence
// -----------------------------
void loadUsersFromFile();                          // Load users at startup
void saveUsersToFile();                            // Save users before exit

#endif // SMARTBANK_UPI_H
