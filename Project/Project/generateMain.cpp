#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "generateFunc.h"

int main()
{
    char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    srand( (unsigned)time( NULL ) );

    int countOfStud=0;
    countOfStud=rand() %60;

    Student *head=createStudentList(countOfStud);
    //printStudents(head);
    createFirstTable(head);
    createSecondTable(head);
    createCommands();
}
