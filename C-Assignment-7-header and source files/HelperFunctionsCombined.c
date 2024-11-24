#include "HelperFunctionsCombined.h"
#include <stdio.h>
#include <string.h>

int getStringLength(char *string) {
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}

int scannerButBetter(const char *format, void *address) {
    int i;
    int numOfTokensRead = scanf(format, &i);
    if (numOfTokensRead == 1) {
        char x = getchar();
        while (x != EOF && x != '\n') {
            x = getchar();
        }
    } else {
        printf("ERROR!,failed to read! clearing the buffer...\n");
        char x = getchar();
        while (x != EOF && x != '\n') {
            x = getchar();
        }
    }
    return numOfTokensRead;
}

void getStringFromUser(char *target, int sizeOfBuffer) {
    while (1) {
        printf("enter the name of the student!");
        fgets(target, sizeOfBuffer, stdin);
        int myStringLength = getStringLength(target);
        if (target[myStringLength - 1] == '\n') {
            target[myStringLength - 1] = '.';
            break;
        } else {
            char x = getchar();
            while (x != EOF && x != '\n') {
                x = getchar();
            }
            printf("Error!, please try again\n");
        }
    }
}

int getIntFromSTDIN() {
    int intInput = 0;
    while (1) {
        intInput = 0;
        int numOfTokensRead = scanf("%d", &intInput);
        if (numOfTokensRead == 1) {
            char c = getchar();
            while (c != '\n') {
                c = getchar();
            }
            break;
        } else {
            char c = getchar();
            while (c != '\n') {
                c = getchar();
            }
            printf("failed to read the integer you entered!! try again...\n");
        }
    }
    return intInput;
}

int getAge() {
    int ageInput = 0;
    while (1) {
        ageInput = 0;
        printf("enter the age of the student!\n");
        ageInput = getIntFromSTDIN();
        if (ageInput >= 0 && ageInput <= 100) {
            break;
        }
        printf("Error!, please try again\n");
    }
    return ageInput;
}

double getGrade() {
    double gradeInput = 0.0;
    while (1) {
        gradeInput = 0.0;
        printf("enter the age of the student!\n");
        scanf("%lf", &gradeInput);
        if (gradeInput >= 0 && gradeInput <= 100) {
            break;
        }
        printf("Error!, please try again\n");
    }
    return gradeInput;
}

int findLargestId(int numOfStudents, struct Student *students) {
    int highestId = 0;
    for (int i = 0; i < numOfStudents; i++) {
        if (students[i].id > highestId) {
            highestId = students[i].id;
        }
    }
    return highestId;
}

void addNewStudent(int numOfStudents, struct Student *students) {
    //ID INPUT
    int highistId = findLargestId(numOfStudents, students);
    students[numOfStudents].id = highistId + 1;
    //NAME INPUT
    char nameInput[MAX_NAME_LENGTH];
    getStringFromUser(&nameInput[0], MAX_NAME_LENGTH);
    strncpy(students[numOfStudents].name, nameInput, MAX_NAME_LENGTH);
    //AGE INPUT
    int ageInput = getAge();
    students[numOfStudents].age = ageInput;
    //GRADE INPUT
    double gradeInput = getGrade();
    students[numOfStudents].grade = gradeInput;
}

void removeStudent(int *numOfStudents, struct Student students[]) {
    int idInput = 0;
    while (1) {
        idInput = 0;
        printf("please enter the id of the student you would like to remove!");
        getIntFromSTDIN();
        for (int i = 0; i < *numOfStudents; i++) {
            if (students[i].id == idInput) {
                if (i != (*numOfStudents - 1)) {
                    students[i] = students[*numOfStudents - 1];
                }
                (*numOfStudents)--;
                printf("student has been removed!\n");
                return;
            }
        }
        printf("Error!, please try again\n");
    }
}

void gradeCalculations(int numOfStudents, struct Student students[]) {
    int valueOfGrade = 0;
    int highestGrade = 0;
    int lowestGrade = 100;
    int sumOfGrades = 0;
    for (int i = 0; i < numOfStudents; i++) {
        valueOfGrade = students[i].grade;
        sumOfGrades += valueOfGrade;
        if (valueOfGrade > highestGrade) {
            highestGrade = valueOfGrade;
        }
        if (valueOfGrade < lowestGrade) {
            lowestGrade = valueOfGrade;
        }
    }
    double averageGrade = (double)sumOfGrades / numOfStudents;
    printf("Highest Grade: %d\n", highestGrade);
    printf("Lowest Grade: %d\n", lowestGrade);
    printf("Average Grade: %.2f\n", averageGrade);
}

int readFromFile(char *filename, struct ContainerOfStudents *container) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    container->length = 0;
    while (fscanf(file, "%d,%[^,],%d,%lf",
        &container->elements[container->length].id,
        container->elements[container->length].name,
        &container->elements[container->length].age,
        &container->elements[container->length].grade) == 4) {
        container->length++;
        if (container->length >= MAX_CONTAINER_SIZE) {
            printf("Container size limit reached.\n");
            break;
        }
    }

    if (ferror(file)) {
        printf("Error reading file: %s\n", filename);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

int writeContainerToFile(struct ContainerOfStudents *source, char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (!file) {
        printf("Error opening file: %s\n", fileName);
        return 1;
    }

    for (int i = 0; i < source->length; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n",
            source->elements[i].id,
            source->elements[i].name,
            source->elements[i].age,
            source->elements[i].grade);
    }

    if (ferror(file)) {
        printf("Error writing to file: %s\n", fileName);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

void displayAllStudents(struct ContainerOfStudents *students, int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        printf("Student Name: %s, Grade: %d\n", students->students[i].name, students->students[i].grade);
    }
}

void displayStudentGradeStatistics(struct ContainerOfStudents *students, int numOfStudents) {
    // Calculate and display the average, minimum, and maximum grades of all students.
    int valueOfGrade = 0;
    // vars for grade calculation
    int highistGrade = 0;
    int lowestGrade = 100;
    int averageGrade = 0;
    int sumOfGrades = 0;

    gradeCalculations(numOfStudents, students);

    averageGrade = sumOfGrades / numOfStudents;
    printf("Highest Grade: %d\n" ,highistGrade);
    printf("Lowest Grade: %d\n" ,lowestGrade);
    printf("Average Grade: %d\n" ,averageGrade);
}
