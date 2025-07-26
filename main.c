#include <stdio.h>
#include <stdlib.h>
#include "smartbank_upi.h"  // Header file with function declarations & user structure

// 🌟 Main function: Entry point of the SmartBank & UPI program
int main() {
    int choice; // User's main menu choice

    // 🚀 Step 1: Load all previously registered users from file
    // This ensures user data like balances and history are available after restart
    loadUsersFromFile();

    // 🌀 Infinite loop to keep showing the main menu until user exits
    while (1) {
        clear(); // Utility function to clear the screen for better UI (can use system("clear") or system("cls"))

        // 🌐 Step 2: Display main menu
        printf("========================================================\n");
        printf("         🏦 Welcome to SmartBank & UPI System        \n");
        printf("========================================================\n");

        printf("1. Register New User\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        // ✅ Step 3: Get user input for main menu choice with validation
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer on invalid entry
            printf("❌ Invalid input! Please enter a number.\n");
            continue;
        }

        // 🔁 Step 4: Handle user's choice
        switch (choice) {

            case 1:
                // 📝 Register a new user
                registerUser();
                printf("\n🔁 Please login to continue...\n");
                break;

            case 2: {
                // 🔐 Login existing user and get their index
                int userIndex = login();  // Checks UPI ID and UPI PIN

                if (userIndex != -1) {
                    int subChoice;

                    // 🧭 Submenu loop for logged-in user
                    do {
                        printf("\n🔐 Please choose a mode:\n");
                        printf("1. ATM Services\n");
                        printf("2. UPI Wallet\n");
                        printf("3. Logout\n");
                        printf("Enter your choice: ");

                        // Validate submenu input
                        if (scanf("%d", &subChoice) != 1) {
                            while (getchar() != '\n'); // clear invalid input
                            printf("❌ Invalid input! Please enter a number.\n");
                            continue;
                        }

                        // 💼 Handle submenu choice
                        switch (subChoice) {
                            case 1:
                                showATMMenu(userIndex);   // 🚪 Open ATM services menu
                                break;

                            case 2:
                                showUPIMenu(userIndex);   // 💳 Open UPI wallet menu
                                break;

                            case 3:
                                printf("🔒 Logged out successfully.\n");
                                break;

                            default:
                                printf("❌ Invalid choice. Try again.\n");
                        }

                    } while (subChoice != 3); // Exit submenu on logout
                }
                break;
            }

            case 3:
                // 🛑 Exit the application
                printf("✅ Exiting... Thank you for using SmartBank!\n");
                exit(0);

            default:
                // ❌ Handle invalid main menu input
                printf("❌ Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
