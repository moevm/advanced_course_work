#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

struct Person{
char SecondName[50];
char FirstName[50];
char FatherName[50];
char GitHub[50];
char mail[50];
char group[4];
int examResult1;
int examResult2;
int examResult3;
int examResult4;
int examResult5;
struct Person *next;
struct Person *prev;
};

typedef struct Person Student;

char *createGroup();
char *createWord();
Student *createStudent();
Student* createStudentList(int n);
void createFirstTable(Student *head);
char *createMarks(void);
void createSecondTable(Student *head);
void createCommands(void);
