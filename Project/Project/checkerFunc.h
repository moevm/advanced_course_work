#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

/*struct Person{
char SecondName[50];
char FirstName[50];
char FatherName[50];
char GitHub[50];
char mail[50];
int group;
int examResult;
float averageResult;
bool ExcellentTasting;
struct Person *next;
struct Person *prev;
};
*/
typedef struct Person Student;
Student *createStudent(char *smallString);
Student *readTheFirstTable(FILE *file);
void averageGrade(Student *current, char *doubleString);
void readTheSecondTable(FILE *file, Student *head);
int compare(const void * x1, const void * x2);
int *SortOfGroup(Student *head, int countOfStudents);
void concatenate(Student *head, FILE *outfile);
void createNewTables(Student *head);
void findExcellentPupils(Student *head);
