# 🏦 SmartBank + UPI System in C

> A console-based simulation of ATM and UPI transactions built using C language with file handling and secure login.  
> Developed during the Embedded Systems course at Emertxe Institute of Technology.

---

## 📄 Project Description (300 characters)

SmartBank + UPI System is a C-based console app simulating ATM and UPI banking features. It includes user login, secure PINs, fund transfers, and file-based data storage. Built during the Embedded Systems course at Emertxe Institute using modular and validated C code.

---

## 👩‍💻 Developed By

- **Name:** Amruta Patil  
- **Institute:** Emertxe Institute of Technology, Bangalore  
- **Email:** amruta1444@gmail.com  
- **Academic Year:** 2024–25  

---

## 🎯 Objective

Build a secure, modular, and file-based banking simulation system using the C language that allows user registration, ATM functions, UPI wallet transfers, and transaction history tracking.

---

## 🛠️ Technologies Used

- **Programming Language:** C  
- **Concepts:** File Handling, Structures, Modular Programming, Input Validation  
- **Interface:** Command-Line Interface (CLI)

---

## 📂 File Structure

```

├── main.c
├── user.c / user.h         // Registration and Login
├── atm.c / atm.h           // ATM Operations
├── upi.c / upi.h           // UPI Wallet Functions
├── utils.c / utils.h       // Validations & Helpers
├── users.txt               // User Data
├── transactions.txt        // Transaction Logs




## ✨ Features

* 🔐 Secure Login using ATM or UPI PIN
* 🏧 ATM Operations: Withdraw, Transfer to Wallet, Balance Inquiry
* 📲 UPI Wallet: Send Money, View Wallet Balance, Transaction Logs
* 📁 Persistent data storage using `users.txt` and `transactions.txt`
* 🧾 User and transaction validation (Phone, UPI ID, Account No, PINs)
* 🧩 Modular Design using multiple `.c` and `.h` files

---

## 📸 Sample Output

```
🏦 Welcome to SmartBank + UPI System
=====================================
1. Register
2. Login
3. Exit

-- UPI Login --
Enter UPI ID: amruta@ybl
Enter PIN: ****

-- Dashboard --
1. ATM Operations
2. UPI Wallet
3. Transaction History
4. Logout
```

---

## 🔍 Future Scope

* 🔒 Encrypt PINs instead of plain text
* 🖼️ Build a GUI version using C/C++ or Python
* 📈 Add mini statements and spending analytics
* 🧠 Implement multi-threading for concurrent users

---

## ✅ Conclusion

This project demonstrates strong fundamentals in C programming, modular design, file I/O, and user input validation. It provides a practical simulation of real-world banking systems through a lightweight, secure, and intuitive CLI interface.

---

