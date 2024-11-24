#ifndef HELPERFUNCTIONS_COMBINED_H
#define HELPERFUNCTIONS_COMBINED_H

#define MAX_NAME_LENGTH 100
#define MAX_CONTAINER_SIZE 100
#define MAX_NAME_SIZE 40

struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    double grade;
};

struct ContainerOfStudents {
    unsigned short int length;
    struct Student elements[MAX_CONTAINER_SIZE];
};

int getStringLength(char *string);

int scannerButBetter(const char *format, void *address);

void getStringFromUser(char *target, int sizeOfBuffer);

int getIntFromSTDIN();

int getAge();

double getGrade();

int findLargestId(int numOfStudents, struct Student *students);

void addNewStudent(int numOfStudents, struct Student students[]);

void removeStudent(int *numOfStudents, struct Student students[]);

void gradeCalculations(int numOfStudents, struct Student students[]);

void printStudents(int numOfStudents, struct Student students[]);

int openFile(int *numOfStudents, struct Student students[]);

int writeToFile(int numOfStudents, struct Student students[]);

int readFromFile(char *fileName, struct ContainerOfStudents *output);

int writeContainerToFile(struct ContainerOfStudents *source, char *fileName);

void displayAllStudents(struct ContainerOfStudents *students, int numOfStudents);

void displayStudentGradeStatistics(struct ContainerOfStudents *students, int numOfStudents);

#endif
