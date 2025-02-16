"# StudentManagementSystemC" 

Student Record Management System

Description
This is a simple Student Record Management System written in C. It allows users to add, display, search, modify, and delete student records using a text file (`students.txt`) for data storage. The program provides a menu-driven interface for easy interaction.

Features
- Add a new student record
- Display all student records
- Search for a student by ID
- Modify an existing student record
- Delete a student record
- Handles invalid inputs gracefully

File Structure
- `students.txt`: The text file used for storing student records.
- `student_management.c`: The main source code file containing all functionalities.

Compilation and Execution
To compile the program, use the following command:
```sh
gcc student_management.c -o student_management
```

To run the program, use:
```sh
./student_management
```

How to Use
1. Run the program and choose an option from the menu.
2. Enter the required student details.
3. Perform actions such as adding, searching, modifying, or deleting records.
4. Exit the program when done.

Data Storage Format
The student records are stored in `students.txt` using a pipe (`|`) delimiter:
```
ID|Name|Age|Course|Email|Phone
```
Example:
```
101|John Doe|20|Computer Science|johndoe@example.com|9876543210
102|Jane Smith|22|Information Technology|janesmith@example.com|9123456789
```

Error Handling
- The program validates input types (e.g., ID and age should be integers).
- It handles file opening errors and prevents data corruption.

Future Enhancements
- Implementing a GUI-based interface.
- Adding database support (MySQL, SQLite) for better data management.
- Implementing authentication for security.

Author
Developed by Dhrumil

