#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "erst.txt"

struct Employee {
    int id;
    char name[50];
    char fatherName[50];
    int age;
    char designation[50];
    int yearsOfExperience;
    float salary;
};

int countEmployees() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1; // Return -1 to indicate an error
    }

    int count = 0;
    struct Employee employee;

    // Counting employees by reading each record from the file
    while (fscanf(file, "%d %s %s %d %s %d %f", &employee.id, employee.name, employee.fatherName,
               &employee.age, employee.designation, &employee.yearsOfExperience, &employee.salary) == 7) {
        count++;
    }

    fclose(file);
    return count;
}

int generateID() {
    static int id = 1000; // Starting ID
    return ++id;
}

float calculateSalary(const char *designation, int yearsOfExperience) {
    float baseSalary = 0;

    // Assign base salary based on designation
    if (strcmp(designation, "Secratary") == 0) {
        baseSalary = 30000;
    } else if (strcmp(designation, "Developer") == 0) {
        baseSalary = 25000;
    } else if (strcmp(designation, "Assistant") == 0) {
        baseSalary = 20000;
    } else if (strcmp(designation, "Engineer") == 0) {
        baseSalary = 23000;
    } // Add more designations and their respective base salaries as needed

    // Calculate final salary based on base and experience
    return baseSalary + (yearsOfExperience * 1000);
}

void displayMenu() {
    printf("\nEmployee Record System Menu\n");
    printf("1. Add Record\n");
    printf("2. Delete Record by ID\n");
    printf("3. Modify Record by ID\n");
    printf("4. Display Records\n");
    printf("5. Save Records to File\n");
    printf("6. Count Employees\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

void addRecord(struct Employee *employee) {
    printf("\nEnter Employee Details:\n");
    printf("Name: ");
    scanf("%s", employee->name);
    printf("Father's Name: ");
    scanf("%s", employee->fatherName);
    printf("Age: ");
    scanf("%d", &employee->age);
    printf("Designation(Secratary/Developer/Assistant/Engineer): ");
    scanf("%s", employee->designation);
    printf("Years of Experience: ");
    scanf("%d", &employee->yearsOfExperience);

    employee->id = generateID();
    employee->salary = calculateSalary(employee->designation, employee->yearsOfExperience);
}

void displayRecords() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee employee;
    printf("\nEmployee Records:\n");
    printf("\n========================="
           "==========================="
           "==========================="
           "==========================="
           "=============="); 
    printf("ID\tName\t\tFather's Name\t\tAge\tDesignation\t\tYears of Exp.\t\tSalary\n");
    printf("==========================="
           "==========================="
           "==========================="
           "==========================="
           "============\n"); 
    while (fscanf(file, "%d %s %s %d %s %d %f", &employee.id, employee.name, employee.fatherName,
               &employee.age, employee.designation, &employee.yearsOfExperience, &employee.salary) != EOF) {
        printf("%d\t%s\t\t%s\t\t\t%d\t%s\t\t%d\t\t\t%.2f\n", employee.id, employee.name, employee.fatherName,
               employee.age, employee.designation, employee.yearsOfExperience, employee.salary);
    }
    printf("==========================="
           "==========================="
           "==========================="
           "==========================="
           "============\n"); 
    fclose(file);
}

void saveToFile(struct Employee *employee) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d %s %s %d %s %d %.2f\n", employee->id, employee->name, employee->fatherName,
            employee->age, employee->designation, employee->yearsOfExperience, employee->salary);

    fclose(file);
}

void deleteRecord(int id) {
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee employee;
    while (fscanf(file, "%d %s %s %d %s %d %f", &employee.id, employee.name, employee.fatherName,
               &employee.age, employee.designation, &employee.yearsOfExperience, &employee.salary) != EOF) {
        if (employee.id != id) {
            fprintf(tempFile, "%d %s %s %d %s %d %.2f\n", employee.id, employee.name, employee.fatherName,
                    employee.age, employee.designation, employee.yearsOfExperience, employee.salary);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void modifyRecord(int id) {
    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Employee employee;
    while (fscanf(file, "%d %s %s %d %s %d %f", &employee.id, employee.name, employee.fatherName,
               &employee.age, employee.designation, &employee.yearsOfExperience, &employee.salary) != EOF) {
        if (employee.id == id) {
            printf("\nEnter modified details for Employee with ID %d:\n", id);
            printf("Name: ");
            scanf("%s", employee.name);
            printf("Father's Name: ");
            scanf("%s", employee.fatherName);
            printf("Age: ");
            scanf("%d", &employee.age);
            printf("Designation: ");
            scanf("%s", employee.designation);
            printf("Years of Experience: ");
            scanf("%d", &employee.yearsOfExperience);
            employee.salary = calculateSalary(employee.designation, employee.yearsOfExperience);
        }
        fprintf(tempFile, "%d %s %s %d %s %d %.2f\n", employee.id, employee.name, employee.fatherName,
                employee.age, employee.designation, employee.yearsOfExperience, employee.salary);
    }

    fclose(file);
    fclose(tempFile);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

int main() {
    int choice, id;
    struct Employee employee;
    
    printf("\n\n\n\n\t\t\t\t============="
           "============================="
           "============="); 
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~"); 
    printf("\n\t\t\t\t==================="
           "============================="
           "======="); 
    printf("\n\t\t\t\t[|***>***>***>***>  "
           "EMPLOYEE RECORD  <***<***<***"
           "<***|]\t"); 
    printf("\n\t\t\t\t==================="
           "============================="
           "======="); 
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~"); 
    printf("\n\t\t\t\t====================="
           "==================================\n"); 
    printf("\n\n\n\t\t\t\t\t\t\t\t"
           "Developer : Gunda Rama Praneetha and Sanskriti Tiwari"
           "\n\n\t\t\t\t"); 
  
    system("pause"); 
  
    while (1) {
        
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(&employee);
                saveToFile(&employee);
                break;
            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteRecord(id);
                break;
            case 3:
                printf("Enter ID to modify: ");
                scanf("%d", &id);
                modifyRecord(id);
                break;
            case 4:
                displayRecords();
                break;
            case 5:
                printf("Records saved to file.\n");
                break;
            case 6:
                printf("Total number of employees: %d\n", countEmployees());
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}