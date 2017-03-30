#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include "checkerFunc.h"



int main()
{
    setlocale(0, ""); // подключаем кириллицу

    FILE *file;
    char *f1name="f1.csv";
    char *f2name="f2.csv";

    file=fopen(f1name,"r");
    Student *head=readTheFirstTable(file);
    Student *saveHead=head;

    file=fopen(f2name,"r");
    readTheSecondTable(file, head);

    int tmp;
    int choice;
    int *commands=(int*)malloc(sizeof(int)*10);
    file=fopen("commands", "r");
    fread(commands, sizeof(commands), 1, file);
    for (int i=0; i<5; i++)
	{
    	if (*(commands+i)==4)
		{
		break;
		}
        if (*(commands+i)==3)
            {
            findExcellentPupils(head);
            }      
        }
        
    FILE *outFile=fopen("r.csv", "w");
    fputs(createNewTables(head), outFile);
    fclose(outFile);
    fclose(file);
    return 0;
}
