#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
    char email[50];
    char phone[15];
};

void addStudent();
void displayStudents();
void searchStudent();
void modifyStudent();
void deleteStudent();

int main() {
    int choice;
    while (1) {
        printf("\nStudent Record Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Modify Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n'); // flush input
            continue;
        }
        while(getchar() != '\n'); // remove leftover newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: modifyStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        perror("Error opening file for appending");
        return;
    }
    
    struct Student s;
    
    printf("Enter Student ID: ");
    if (scanf("%d", &s.id) != 1) {
        printf("Invalid input for ID!\n");
        while(getchar() != '\n');
        fclose(file);
        return;
    }
    while(getchar() != '\n'); // flush newline

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  // remove trailing newline

    printf("Enter Age: ");
    if (scanf("%d", &s.age) != 1) {
        printf("Invalid input for Age!\n");
        while(getchar() != '\n');
        fclose(file);
        return;
    }
    while(getchar() != '\n');

    printf("Enter Course: ");
    fgets(s.course, sizeof(s.course), stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = '\0';

    // Write record using a pipe delimiter
    fprintf(file, "%d|%s|%d|%s|%s|%s\n", s.id, s.name, s.age, s.course, s.email, s.phone);
    fclose(file);
    printf("Student record added successfully!\n");
}

void displayStudents() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }
    
    struct Student s;
    printf("\nStudent Records:\n");
    printf("ID\tName\t\tAge\tCourse\t\tEmail\t\t\tPhone\n");
    printf("-----------------------------------------------------------------------\n");
    // Using %49[^|] and %14[^\n] ensures we don't exceed the field widths.
    while (fscanf(file, "%d|%49[^|]|%d|%49[^|]|%49[^|]|%14[^\n]\n", 
                  &s.id, s.name, &s.age, s.course, s.email, s.phone) == 6) {
        printf("%d\t%-15s\t%d\t%-15s\t%-20s\t%s\n", 
               s.id, s.name, s.age, s.course, s.email, s.phone);
    }
    fclose(file);
}

void searchStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No records found!\n");
        return;
    }
    
    int id, found = 0;
    struct Student s;
    printf("Enter Student ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        fclose(file);
        return;
    }
    while(getchar() != '\n');
    
    while (fscanf(file, "%d|%49[^|]|%d|%49[^|]|%49[^|]|%14[^\n]\n", 
                  &s.id, s.name, &s.age, s.course, s.email, s.phone) == 6) {
        if (s.id == id) {
            printf("Student Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\nEmail: %s\nPhone: %s\n",
                   s.id, s.name, s.age, s.course, s.email, s.phone);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found)
        printf("Student not found!\n");
}

void modifyStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }
    
    int id, found = 0;
    struct Student s;
    printf("Enter Student ID to modify: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        fclose(file);
        fclose(temp);
        return;
    }
    while(getchar() != '\n');
    
    while (fscanf(file, "%d|%49[^|]|%d|%49[^|]|%49[^|]|%14[^\n]\n", 
                  &s.id, s.name, &s.age, s.course, s.email, s.phone) == 6) {
        if (s.id == id) {
            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Enter New Age: ");
            if (scanf("%d", &s.age) != 1) {
                printf("Invalid input for Age!\n");
                while(getchar() != '\n');
                continue;
            }
            while(getchar() != '\n');

            printf("Enter New Course: ");
            fgets(s.course, sizeof(s.course), stdin);
            s.course[strcspn(s.course, "\n")] = '\0';

            printf("Enter New Email: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = '\0';

            printf("Enter New Phone Number: ");
            fgets(s.phone, sizeof(s.phone), stdin);
            s.phone[strcspn(s.phone, "\n")] = '\0';

            found = 1;
        }
        fprintf(temp, "%d|%s|%d|%s|%s|%s\n", s.id, s.name, s.age, s.course, s.email, s.phone);
    }
    
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    
    if (found)
        printf("Student record modified successfully!\n");
    else
        printf("Student not found!\n");
}

void deleteStudent() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("Error opening file!\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }
    
    int id, found = 0;
    struct Student s;
    printf("Enter Student ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        fclose(file);
        fclose(temp);
        return;
    }
    while(getchar() != '\n');
    
    while (fscanf(file, "%d|%49[^|]|%d|%49[^|]|%49[^|]|%14[^\n]\n", 
                  &s.id, s.name, &s.age, s.course, s.email, s.phone) == 6) {
        if (s.id == id) {
            found = 1;
            continue;  // Skip this record (i.e. delete)
        }
        fprintf(temp, "%d|%s|%d|%s|%s|%s\n", s.id, s.name, s.age, s.course, s.email, s.phone);
    }
    
    fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    
    if (found)
        printf("Student record deleted successfully!\n");
    else
        printf("Student not found!\n");
}
