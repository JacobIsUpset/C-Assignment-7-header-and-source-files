//
// Created by Jacob on 2024-10-23.
//

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#define MAX_NAME_LENGTH 100

struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    double grade;
};

int getIntFromSTDIN();

void gradeCalculations(int numOfStudents, struct Student students[]);

void printStudents(int numOfStudents, struct Student students[]);

//start

int getStringLength(char *string);

int scannerButBetter(const char *format,void *address);

void getStringFromUser(char * target, int sizeOfBuffer);

int getIntFromSTDIN();

int findLargestId(int numOfStudents, struct Student *student);

//inputs

int getAge();

double getGrade();

void addNewStudent(int numOfStudents, struct Student students[]);

void gradeCalculations(int numOfStudents, struct Student students[]);

//menu 3
// In helperFunctions.h
void removeStudent(int *numOfStudents, struct Student students[]);

int openFile(int *numOfStudents, struct Student students[]);

int writeToFile(int numOfStudents, struct Student students[]);

#endif //HELPERFUNCTIONS_H