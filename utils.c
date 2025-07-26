#include <stdio.h>
#include <string.h>
#include <time.h>
#include "smartbank_upi.h"

// -----------------------------------------------------
// 🧹 clear
// Purpose : Displays a clean UI separator (visual only)
// -----------------------------------------------------
void clear() {
    printf("\n=========================================\n");
}

// -----------------------------------------------------
// 🕒 printTime
// Purpose : Formats current time into string: "YYYY-MM-DD HH:MM:SS"
// Output  : Stored in 'buffer'
// -----------------------------------------------------
void printTime(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", t);
}

// -----------------------------------------------------
// 💾 addTransaction
// Purpose : Stores a transaction log entry in memory
// Input   : history array, pointer to count, entry string
// -----------------------------------------------------
void addTransaction(char history[MAX_TRANSACTIONS][100], int *count, const char *entry) {
    if (*count >= MAX_TRANSACTIONS) return; // Max reached
    strncpy(history[*count], entry, 99);
    history[*count][99] = '\0'; // Ensure null-termination
    (*count)++;
}

// -----------------------------------------------------
// 📁 logToFile
// Purpose : Appends a transaction entry to a shared file
// File    : all_upi_transactions.txt
// -----------------------------------------------------
void logToFile(const char *upi_id, const char *type, const char *entry) {
    FILE *fp = fopen("all_transaction.txt", "a");  // ✅ Unified file
    if (fp == NULL) {
        printf("❌ Error: Could not open all_transaction.txt.\n");
        return;
    }

    char timeStr[50];
    printTime(timeStr);

    // Format: [Timestamp] [UPI_ID] [TYPE] Message
    fprintf(fp, "[%s] [%s] [%s] %s\n", timeStr, upi_id, type, entry);

    fclose(fp);
}


// -----------------------------------------------------
// 📞 isValidPhone
// Purpose : Checks if the phone number has exactly 10 digits
// -----------------------------------------------------
int isValidPhone(const char *phone) {
    if (strlen(phone) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9') return 0;
    }
    return 1;
}

// -----------------------------------------------------
// 🏦 isValidUPI
// Purpose : Validates UPI ID format (e.g., name@bank)
// -----------------------------------------------------
int isValidUPI(const char *upi) {
    char *atPos = strchr(upi, '@');
    if (atPos == NULL || atPos == upi || *(atPos + 1) == '\0') return 0;
    return 1;
}

// -----------------------------------------------------
// 🔁 isUPIExists
// Purpose : Checks if the provided UPI ID already exists
// -----------------------------------------------------
int isUPIExists(const char *upi) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].upi_id, upi) == 0)
            return 1;
    }
    return 0;
}

// -----------------------------------------------------
// 📱 isPhoneExists
// Purpose : Checks if the provided phone number is already used
// -----------------------------------------------------
int isPhoneExists(const char *phone) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}

// -----------------------------------------------------
// 🔍 findRecipientIndex
// Purpose : Returns user index using account number
// Returns : Index if found, -1 otherwise
// -----------------------------------------------------
int findRecipientIndex(long long recipientAccount) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].account_number == recipientAccount)
            return i;
    }
    return -1;
}

// -----------------------------------------------------
// 🔍 findUserByUPI
// Purpose : Returns user index using UPI ID
// Returns : Index if found, -1 otherwise
// -----------------------------------------------------
int findUserByUPI(const char *upi_id) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].upi_id, upi_id) == 0)
            return i;
    }
    return -1;
}
