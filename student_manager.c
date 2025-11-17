#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll;
    char name[50];
    char course[30];
    float marks;
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    do {
        printf("\n====== Student Record Manager ======\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

void addStudent() {
    FILE *fp;
    Student s;

    fp = fopen("students.dat", "ab");  // append in binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- Add Student ---\n");
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);   // read full line including spaces

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student record added successfully.\n");
}

void displayStudents() {
    FILE *fp;
    Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found. File could not be opened.\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    printf("%-10s %-20s %-15s %-10s\n", "Roll", "Name", "Course", "Marks");
    printf("-----------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("%-10d %-20s %-15s %-10.2f\n", s.roll, s.name, s.course, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found. File could not be opened.\n");
        return;
    }

    printf("\n--- Search Student ---\n");
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("\nRecord Found:\n");
            printf("Roll   : %d\n", s.roll);
            printf("Name   : %s\n", s.name);
            printf("Course : %s\n", s.course);
            printf("Marks  : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %d.\n", roll);
    }

    fclose(fp);
}

void updateStudent() {
    FILE *fp;
    Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+"); // read & write in binary
    if (fp == NULL) {
        printf("No records found. File could not be opened.\n");
        return;
    }

    printf("\n--- Update Student ---\n");
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            printf("\nExisting Record:\n");
            printf("Roll   : %d\n", s.roll);
            printf("Name   : %s\n", s.name);
            printf("Course : %s\n", s.course);
            printf("Marks  : %.2f\n\n", s.marks);

            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter new Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            // move file pointer one record back
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);

            printf("Record updated successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %d.\n", roll);
    }

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *fpTemp;
    Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found. File could not be opened.\n");
        return;
    }

    fpTemp = fopen("temp.dat", "wb");
    if (fpTemp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    printf("\n--- Delete Student ---\n");
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.roll == roll) {
            found = 1;
            // skip writing this record (deleted)
        } else {
            fwrite(&s, sizeof(Student), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    if (found) {
        remove("students.dat");
        rename("temp.dat", "students.dat");
        printf("Record deleted successfully.\n");
    } else {
        remove("temp.dat");
        printf("No student found with roll number %d.\n", roll);
    }
}
