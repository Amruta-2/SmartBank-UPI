#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smartbank_upi.h"

// 1. Check ATM Balance
void checkATMBalance(int userIndex) {
    printf("\n🏦 Current ATM Balance: ₹%lld\n", users[userIndex].atm_balance);
}

//  2. Deposit Money to ATM Balance
void depositATM(int userIndex) {
    long long amount;
    printf("Enter amount to deposit: ₹");
    scanf("%lld", &amount);

    if (amount <= 0) {
        printf("❌ Invalid amount.\n");
        return;
    }

    users[userIndex].atm_balance += amount;

    char entry[100];
    sprintf(entry, "Deposited ₹%lld", amount);
    
    // Add to transaction history
    addTransaction(users[userIndex].atm_history, &users[userIndex].atm_txn_count, entry);

    // ✅ Log to file
    logToFile(users[userIndex].upi_id, "ATM", entry);

    printf("✅ ₹%lld deposited successfully.\n", amount);
}


// 3. Withdraw Money from ATM
void withdrawATM(int userIndex) {
    long long amount;
    printf("Enter amount to withdraw: ₹");
    scanf("%lld", &amount);

    if (amount <= 0 || amount > users[userIndex].atm_balance) {
        printf("❌ Invalid or insufficient balance.\n");
        return;
    }

    users[userIndex].atm_balance -= amount;

    char entry[100];
    sprintf(entry, "Withdrew ₹%lld", amount);
    addTransaction(users[userIndex].atm_history, &users[userIndex].atm_txn_count, entry);

    // ✅ Save to transaction file
    logToFile(users[userIndex].upi_id, "ATM", entry);

    printf("✅ ₹%lld withdrawn successfully.\n", amount);
}


//  4. Transfer Money to Another Account via ATM
void transferATM(int userIndex) {
    int recipientAccount;
    long long int amount;

    printf("Enter recipient Account Number: ");
    if (scanf("%d", &recipientAccount) != 1) {
        printf("❌ Invalid account number. Transaction cancelled.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');  // clear buffer

    int recipientIndex = -1;
    for (int i = 0; i < user_count; i++) {
        if (users[i].account_number == recipientAccount) {
            recipientIndex = i;
            break;
        }
    }

    if (recipientIndex == -1) {
        printf("❌ Account number not found. Transaction cancelled.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    if (scanf("%lld", &amount) != 1) {
        printf("❌ Invalid amount. Transaction cancelled.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');  // clear buffer

    if (amount <= 0) {
        printf("❌ Invalid amount. Must be positive.\n");
        return;
    }

    if (amount > users[userIndex].atm_balance) {
        printf("❌ Insufficient balance.\n");
        return;
    }

    // Update both users' balances
    users[userIndex].atm_balance -= amount;
    users[recipientIndex].atm_balance += amount;

    //  Save updated balances
    saveUsersToFile();

    char timeStr[50], entry[200];
    printTime(timeStr);
    sprintf(entry, "[%s] Transferred ₹%lld to Account %d", timeStr, amount, recipientAccount);
    addTransaction(users[userIndex].atm_history, &users[userIndex].atm_txn_count, entry);
    logToFile(users[userIndex].upi_id, "atm", entry);

    printf("✅ ₹%lld transferred to Account No: %d\n", amount, recipientAccount);
    printf("(UTR: TXN%04dAC)\n", rand() % 9999);
}

// 5. View ATM Transaction History
void showATMTransactionHistory(int userIndex) {
    printf("\n--- 🧾 ATM Transaction History ---\n");

    if (users[userIndex].atm_txn_count == 0) {
        printf("No transactions found.\n");
        return;
    }

    for (int i = 0; i < users[userIndex].atm_txn_count; i++) {
        printf("%s\n", users[userIndex].atm_history[i]);
    }
}

//  6. Display ATM Menu
void showATMMenu(int userIndex) {
    int choice;
    while (getchar() != '\n');  // Clear input buffer

    do {
        printf("\n========= 🏧 ATM Menu =========\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer to Another Account\n");
        printf("5. View ATM Transaction History\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: checkATMBalance(userIndex); break;
            case 2: depositATM(userIndex); break;
            case 3: withdrawATM(userIndex); break;
            case 4: transferATM(userIndex); break;
            case 5: showATMTransactionHistory(userIndex); break;
            case 6: printf("🔁 Returning to main menu...\n"); break;
            default: printf("❌ Invalid choice. Try again.\n");
        }

    } while (choice != 6);
}
