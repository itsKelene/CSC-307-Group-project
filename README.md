# **Secure Password Manager**

**Author:** Chakiya McKenzie
**Course:** CSC 307 H001
**Semester:** Summer 2026

---

## 1\. Prerequisites & Environment
Before running this project, make sure your system meets the following requirements:

* **Operating System:** Windows 10/11, macOS, or Linux  
* **Compiler:** GCC 11.0+ (or any C++ compiler with C++11 support)  

### Required Libraries
This project only uses the C++ Standard Library. No extra libraries are needed.
* `<iostream>` – Console input/output  
* `<vector>` – Hash table buckets  
* `<string>` – String handling  
* `<fstream>` – Reading and writing CSV files  
* `<sstream>` – Parsing command input and password hashing

---

## 2\. Installation & Setup
1. Download/Install the project files.  
2. Make sure all of the following files are in the same directory:  
   * `main.cpp`  
   * `PasswordHashTable.cpp`  
   * `PasswordHashTable.h`  
   * `Entry.h`  
   * `passwords.csv` (optional sample data)  
3. Open the folder in your preferred IDE or terminal.

---

## 3\. Build Instructions
### **Using Command Line (G++)**
g++ \-std=c++11 main.cpp PasswordHashTable.cpp \-o PasswordManager

### **Run the Program**
./PasswordManager
(On Windows)
PasswordManager.exe

### **Using an IDE**
* Open the project in Visual Studio Code or another C++ IDE.  
* Add all project source files (`main.cpp` and `PasswordHashTable.cpp`) and header files (`PasswordHashTable.h` and `Entry.h`).  
* Build the project.  
* Run the executable.

---

## 4\. Execution Guide
After starting the program, a command prompt will appear.

### **Available Commands**
Insert \<username\> \<password\>
Adds a new username and password.

Search \<username\>
Searches for an existing username.

Edit \<username\> \<newPassword\>
Updates the password for an existing user.

Delete \<username\>
Removes a user from the hash table.

Login \<username\> \<password\>
Verifies that the username and password match.

Save \<filename\>
Saves all stored usernames and hashed passwords to a CSV file.

Load \<filename\>
Loads usernames and hashed passwords from a CSV file.

Help
Displays the list of available commands.
Exit
Closes the program.

### **Executable**
* Executable Name: `PasswordManager` (or `PasswordManager.exe` on Windows)  
* Entry Point: `main.cpp`  
* Command-Line Arguments: None required.

---

## 5\. Troubleshooting / Known Issues
* Ensure all project files are included during compilation.  
* The program stores hashed passwords, not plain-text passwords.  
* If a CSV file cannot be opened, verify that the filename and directory are correct.  
* Existing usernames are not checked for duplicates before insertion.  
* The project is a console application and does not include a graphical user interface.

