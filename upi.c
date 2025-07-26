#include <stdio.h>
#include <string.h>
#include "smartbank_upi.h"

// ===========================================================
// 🏦  UPI Service Functions
// ===========================================================

// Function: checkBalance
void checkBalance(int userIndex) {
    printf("\n💰 Current Wallet Balance: ₹%lld\n", users[userIndex].wallet_balance);
}

// Function: addMoney
void addMoney(int userIndex) {
    long long int amount;
    printf("Enter amount to add: ");
    scanf("%lld", &amount);

    users[userIndex].wallet_balance += amount;

    char timeStr[50], entry[200];
    printTime(timeStr);
    sprintf(entry, "[%s] Added ₹%lld to wallet", timeStr, amount);

    addTransaction(users[userIndex].upi_history, &users[userIndex].upi_txn_count, entry);
    logToFile(users[userIndex].upi_id, "upi", entry);

    saveUsersToFile();  // ✅ persist data

    printf("✅ ₹%lld added successfully!\n", amount);
    printf("💰 Current Wallet Balance: ₹%lld\n", users[userIndex].wallet_balance);
}

// Function: sendMoney
void sendMoney(int senderIndex) {
    char receiverUPI[50];
    long long amount;

    printf("Enter receiver UPI ID: ");
    scanf("%s", receiverUPI);

    int receiverIndex = findUserByUPI(receiverUPI);
    if (receiverIndex == -1) {
        printf("❌ Receiver UPI not found.\n");
        return;
    }

    printf("Enter amount to send: ₹");
    scanf("%lld", &amount);

    if (amount <= 0 || amount > users[senderIndex].wallet_balance) {
        printf("❌ Insufficient balance or invalid amount.\n");
        return;
    }

    users[senderIndex].wallet_balance -= amount;
    users[receiverIndex].wallet_balance += amount;

    char entry[200], timeStr[50];
    printTime(timeStr);
    sprintf(entry, "%s - Sent ₹%lld to %s", timeStr, amount, users[receiverIndex].upi_id);
    addTransaction(users[senderIndex].upi_history, &users[senderIndex].upi_txn_count, entry);
    logToFile(users[senderIndex].upi_id, "UPI", entry);

    sprintf(entry, "%s - Received ₹%lld from %s", timeStr, amount, users[senderIndex].upi_id);
    addTransaction(users[receiverIndex].upi_history, &users[receiverIndex].upi_txn_count, entry);
    logToFile(users[receiverIndex].upi_id, "UPI", entry);

    saveUsersToFile();  // ✅ persist data

    printf("✅ ₹%lld sent to %s successfully.\n", amount, users[receiverIndex].name);
}

// Function: showTransactionHistory
void showTransactionHistory(int userIndex) {
    printf("\n--- 🧾 Transaction History ---\n");
    if (users[userIndex].upi_txn_count == 0) {
        printf("No transactions found.\n");
        return;
    }
    for (int i = users[userIndex].upi_txn_count - 1; i >= 0; i--) {
        printf("%s\n", users[userIndex].upi_history[i]);
    }
}

// Function: showUPIMenu
void showUPIMenu(int userIndex) {
    int choice;
    do {
        printf("\n-----------------------------------------\n");
        printf("1. Check Balance\n");
        printf("2. Add Money\n");
        printf("3. Send Money\n");
        printf("4. Transaction History\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: checkBalance(userIndex); break;
            case 2: addMoney(userIndex); break;
            case 3: sendMoney(userIndex); break;
            case 4: showTransactionHistory(userIndex); break;
            case 5: printf("🔒 Logged out successfully.\n"); break;
            default: printf("❌ Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}
