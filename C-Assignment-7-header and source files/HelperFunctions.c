//
// Created by Jacob on 2024-10-23.
//

#include <stdio.h>
#include <string.h>

#include "helperFunctions.h"
#define MAX_FILE_LENGTH 300

int getStringLength(char *string) {
    // given a pointer to the beginning of a character array
    // that is guaranteed to be null terminated, return the size
    int i = 0;
    while (string[i] != '\0') {
        i++;
    }
    return i;
}


int scannerButBetter(const char *format,void *address){
    int i;
    int numOfTokensRead = scanf(format, &i);

    if (numOfTokensRead == 1) {
        // either there is only a newline left -> just pop off with getchar()
        // or there are a whole bunch of junk in addition to a newline left -> keep poppoing off until EOF or \n reached
        char x = getchar();
        while (x != EOF && x != '\n') {
            x = getchar();
        }
    } else {
        // we failed to read an integer, inform the user
        // we need to empty the buffer if necessary we failed to read
        printf("ERROR!,failed to read! clearing the buffer...\n");
        char x = getchar();
        while (x != EOF && x != '\n')
        {
            x = getchar();
        }
    }

    return numOfTokensRead;
}

void getStringFromUser(char * target, int sizeOfBuffer) {
    // keep asking the user to enter a name
    // if the user enters anything that is too long for the buffer size
    // (and there ends up being leftover characters on in the input buffer), make sure to
    // empty the buffer and ask the user to enter a name within the specified length
    // when happy with user input, then write it to the target buffer!

    // hint: if the string you read with fgets, ends with \n before the \0, that means
    // there is nothing left on the buffer (you read everything)
    while (1)
    {
        printf("enter the name of the student!");
        fgets(target, sizeOfBuffer, stdin);
        // either it ends with \n or it doesnt
        int myStringLength = getStringLength(target);
        if (target[myStringLength - 1] == '\n'){
            // everything went kosher
            // we don't need to empty the buffer
            // just take away the newline from their name!
            target[myStringLength - 1] = '.';
            break;

        } else {
            // we have to empty the buffer, tell the user to try again
            char x = getchar();
            while (x != EOF && x != '\n')
            {
                x = getchar();
            }
            printf("Error!, please try again\n");
        }

    }
    // otherwise, if there is no \n at the second last character of your input
    // (fgets ensures that the very last character will certainly be \0)
    // then that means, you have to clear the input buffer


}


int getIntFromSTDIN() {
    int intInput = 0;
     while (1) {
         intInput = 0;
         int numOfTokensRead = scanf("%d", &intInput);
         if (numOfTokensRead == 1) {
             // everything went fine however, the user could still have more junk on the input buffer
             // scanf does not fail if there is more junk than what you were looking for already on the
             // input buffer
             // in this there could be at least just a \n that we have to remove from the buffer
             // or there is more
             char c = getchar();
             while (c != '\n') {
                 c = getchar();
             }
             break; // I got the right thing now in the age Input
         } else {
             // we could not read properly. we need to empty the buffer and then
             // tell them to try again
             char c = getchar();
             while (c != '\n') {
                 c = getchar();
             }
             printf("failed to read the integer you entered!! try again...\n");
         }
     }
    return intInput;
}

int findLargestId(int numOfStudents, struct Student *student) {
    int highestId = 0;
    // iterate through every student in the array
    // if the id value of the student is larger than the highistId then replace it with the student Id
    for (int i = 0; i < numOfStudents ;i++) {
        if (student[i].id > highestId){
            highestId = student[i].id;
        }
        return highestId;
    }
}

int getAge(){
    int ageInput = 0;
    while (1) {
        ageInput = 0;
        printf("enter the age of the student!\n");
        // what is the best way to USE a function that can read an integer?
        // you can assume that your function ensures that the user enters a valid int
        // otherwise the user is going to be prompted INSIDE that helper function

        // which one is better:

        ageInput = getIntFromSTDIN();

        if (ageInput >= 0 && ageInput <= 100){break;}
        printf("Error!, please try again\n");
    }
    return ageInput;
}

double getGrade(){
    double gradeInput = 0.0;
    while (1) {
        gradeInput = 0.0;
        printf("enter the age of the student!\n");
        scanf("%l.2", &gradeInput);
        if (gradeInput >= 0 && gradeInput <= 100){break;}
        printf("Error!, please try again\n");
    }
    return gradeInput;
}

void addNewStudent(int numOfStudents, struct Student * students){

    //ID INPUT
    // loop until you find a id
    int highistId = findLargestId(numOfStudents, students);
    students[numOfStudents].id = highistId + 1;

    //NAME INPUT
    // read the name:
    char nameInput[MAX_NAME_LENGTH];
    // the next function will loop itself as many times as it needs
    // and when it is done, the input buffer is cleared!
    getStringFromUser(&nameInput[0], MAX_NAME_LENGTH);
    // at this point, we know that the nameInput array holds the name,
    // so all we need to do is to write it in the correct place of the array
    strncpy(students[numOfStudents].name, nameInput, MAX_NAME_LENGTH);

    //AGE INPUT
    int ageInput = getAge();
    students[numOfStudents].age = ageInput;

    //GRADE INPUT
    double gradeInput = getGrade();
    students[numOfStudents].grade = gradeInput;
}

void gradeCalculations(int numOfStudents, struct Student students[]) {
    // Calculate and display the average, minimum, and maximum grades of all students.
    int valueOfGrade = 0;
    // vars for grade calculation
    int highistGrade = 0;
    int lowestGrade = 100;
    int averageGrade = 0;
    int sumOfGrades = 0;

    for (int i = 0; i < numOfStudents ;i++)
    {
        valueOfGrade = students[i].grade;
        sumOfGrades += valueOfGrade;
        if (valueOfGrade > highistGrade){highistGrade = valueOfGrade;}
        if (valueOfGrade < lowestGrade){lowestGrade = valueOfGrade;}
        sumOfGrades += valueOfGrade;
    }

    averageGrade = sumOfGrades / numOfStudents;
    printf("Highest Grade: %d\n" ,highistGrade);
    printf("Lowest Grade: %d\n" ,lowestGrade);
    printf("Average Grade: %d\n" ,averageGrade);
}

void printStudents(int numOfStudents, struct Student students[]) {
    for (int i = 0; i < numOfStudents; i++) {
        {
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Grade: %.2f\n", students[i].grade); // note to self: %.2f is the amount of decimal spaces you want it to print
        }
    }
}

void removeStudent(int * numOfStudents, struct Student students[]){
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
                *numOfStudents--;
                printf("student has been removed!\n");
                break;
            }
        }
        printf("Error!, please try again\n");
    }
}

int openFile(int * numOfStudents, struct Student students[]) {
    //this function will overwrite the students array with what is in the file
    FILE *file = fopen("StudentLogs.txt", "r");

    if (file == NULL) {
        printf("File could not be opened\n");
        return 1;
    }

    char line[MAX_FILE_LENGTH];
    //reseting numOfStudents
    *numOfStudents = 0;

    while (fgets(line, MAX_FILE_LENGTH, file) != NULL) {
        // Parse the line using sscanf
        if (sscanf(line, "%d,%[^,],%d,%lf", &students[*numOfStudents].id, students[*numOfStudents].name, &students[*numOfStudents].age, &students[*numOfStudents].grade) == 4) {
            // Successfully parsed a student, increment numOfStudents
            (*numOfStudents)++;
        }
    }


    if (feof(file)) {
        printf("End of File\n");
    } else if (ferror(file)) {
        printf("Error reading from file\n");
    }

    fclose(file);

    return 0;
}

int writeToFile(int numOfStudents, struct Student students[]){
    // i had to make a copy of open file in here as doing openfile() was not working for me!
    FILE *file = fopen("StudentLogs.txt", "r");

    if (file == NULL) {
        printf("File could not be opened\n");
        return 1;
    }

    char line[MAX_FILE_LENGTH];
    //reseting numOfStudents
    numOfStudents = 0;

    while (fgets(line, MAX_FILE_LENGTH, file) != NULL) {
        // Parse the line using sscanf
        if (sscanf(line, "%d,%[^,],%d,%lf", &students[numOfStudents].id, students[numOfStudents].name, &students[numOfStudents].age, &students[numOfStudents].grade) == 4) {
            // Successfully parsed a student, increment numOfStudents
            (numOfStudents)++;
        }
    }


    if (feof(file)) {
        printf("End of File\n");
    } else if (ferror(file)) {
        printf("Error reading from file\n");
    }

    //iterate through teh array and print it into the file
    for (int i = 0; i < numOfStudents; i++) {
        fprintf(file, "%d,", students[i].id);
        fprintf(file, "%s,", students[i].name);
        fprintf(file, "%d,", students[i].age);
        fprintf(file, "%lf", students[i].grade);
    }

    fclose(file);

    return 0;
}