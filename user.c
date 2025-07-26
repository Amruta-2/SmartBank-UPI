#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "smartbank_upi.h"

User users[MAX_USERS];   // Array to store user records
int user_count = 0;      // Track number of registered users

// ===========================================================
// Function Prototypes
// ===========================================================
void saveUsersToFile();
void loadUsersFromFile();

// ===========================================================
// Function: generateUniqueAccountNumber
// Purpose : Generate a unique 6-digit account number
// ===========================================================
int generateUniqueAccountNumber() {
    int acc, isUnique;
    srand(time(NULL));  // Seed the random number generator once

    do {
        acc = 100000 + rand() % 900000;  // 6-digit number
        isUnique = 1;

        for (int i = 0; i < user_count; i++) {
            if (users[i].account_number == acc) {
                isUnique = 0;  // Collision found, regenerate
                break;
            }
        }
    } while (!isUnique);

    return acc;
}

// ===========================================================
// Function: registerUser
// Purpose : Register a new user with validation and storage
// ===========================================================
void registerUser() {
    if (user_count >= MAX_USERS) {
        printf("❌ User limit reached. Cannot register more users.\n");
        return;
    }

    User newUser;

    printf("Enter your full name        : ");
    scanf(" %[^\n]", newUser.name);

    // Validate unique phone number
    while (1) {
        int duplicate = 0;
        printf("Enter phone number (10 digits): ");
        scanf("%s", newUser.phone);

        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].phone, newUser.phone) == 0) {
                printf("❌ Phone number already registered! Please try another.\n");
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) break;
    }

    // Validate unique UPI ID
    while (1) {
        int duplicate = 0;
        printf("Create your UPI ID (e.g. yourname@ybl): ");
        scanf("%s", newUser.upi_id);

        for (int i = 0; i < user_count; i++) {
            if (strcmp(users[i].upi_id, newUser.upi_id) == 0) {
                printf("❌ UPI ID already exists! Please choose a different one.\n");
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) break;
    }

    // Set UPI and ATM PINs
    printf("Set 4-digit UPI PIN         : ");
    scanf("%d", &newUser.upi_pin);

    printf("Set 4-digit ATM PIN         : ");
    scanf("%d", &newUser.atm_pin);

    // Initialize account details
    newUser.account_number = generateUniqueAccountNumber();
    newUser.upi_balance = 0;
    newUser.atm_balance = 0;

    // Add to user list
    users[user_count++] = newUser;

    // Save to file
    saveUsersToFile();

    printf("\n✅ Registration successful!\n");
    printf("🎉 Your Account Number is: %lld\n", newUser.account_number);
    printf("🔐 You can now log in and use SmartBank+UPI services.\n\n");
}

// ===========================================================
// Function: login
// Purpose : Authenticate user by UPI ID and PIN
// Returns : Index of logged-in user or -1 on failure
// ===========================================================
int login() {
    char inputUPI[50];
    int inputPIN;

    clear();  // Optional: Clears screen if defined

    printf("=========================================\n");
    printf("---- 🔐 Login ----\n");
    printf("Enter your UPI ID    : ");
    scanf("%s", inputUPI);

    printf("Enter your UPI PIN   : ");
    scanf("%d", &inputPIN);

    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].upi_id, inputUPI) == 0 && users[i].upi_pin == inputPIN) {
            printf("✅ Login successful! Welcome, %s\n", users[i].name);
            return i;
        }
    }

    printf("❌ Login failed! Invalid UPI ID or PIN.\n");
    return -1;
}

// ===========================================================
// Function: saveUsersToFile
// Purpose : Persist user records to "users.txt"
// ===========================================================
void saveUsersToFile() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        perror("Error saving users");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(fp, "%s\n", users[i].name);
        fprintf(fp, "%s %s %d %d %lld %lld %d\n",
            users[i].phone,
            users[i].upi_id,
            users[i].upi_pin,
            users[i].atm_pin,
            users[i].wallet_balance,
            users[i].account_number,
            users[i].atm_balance
        );
    }

    fclose(fp);
}

// ===========================================================
// Function: loadUsersFromFile
// Purpose : Load existing users from "users.txt" at startup
// ===========================================================
void loadUsersFromFile() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        return; // No users yet
    }

    while (fscanf(fp, " %[^\n]", users[user_count].name) == 1) {
        fscanf(fp, "%s %s %d %d %lld %lld %d",
            users[user_count].phone,
            users[user_count].upi_id,
            &users[user_count].upi_pin,
            &users[user_count].atm_pin,
            &users[user_count].wallet_balance,
            &users[user_count].account_number,
            &users[user_count].atm_balance
        );
        user_count++;
    }

    fclose(fp);
}

