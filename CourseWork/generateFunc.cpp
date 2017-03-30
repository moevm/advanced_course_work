#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define CONST_GROUP 3000

char *createGroup(){

int value=0;
char *group=(char*)malloc(sizeof(char)*4);

value=CONST_GROUP+rand() % 10;

snprintf(group,5,"%d", value);

return group;

}

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

char *createWord(){

    char alphabet[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int randomLengthOfWord=0;
    randomLengthOfWord=1+ rand() %14;
    char *words=(char*)malloc(sizeof(char)*randomLengthOfWord);
    int i=0;
         for (i=0; i<8; i++){
                int randomAlphabet= rand() % 26;
                *(words+i)=alphabet[randomAlphabet];
        }

return words;
}

Student *createStudent(){

    Student *rr=(Student*)malloc(sizeof(Student));

        strcpy(rr->SecondName,createWord());
        strcpy(rr->FirstName,createWord());
        strcpy(rr->FatherName,createWord());
        strcpy(rr->GitHub,createWord());
        strcpy(rr->mail,createWord());
        strcpy(rr->group,createGroup());

    return rr;
}

Student* createStudentList(int n)
{

        Student *head = createStudent();

        Student *prev = head;
        Student *current;
        int i=0;
        for (i = 1; i < n; ++i)
        {
                current = createStudent();
                current->prev = prev;
                prev->next = current;
                prev = current;
        }
        return head;
}

void createFirstTable(Student *head){

FILE *outFile=fopen("f1.csv", "w");
while (head)
{
    fprintf(outFile, "%s,%s,%s,%s,%s,%s",
		head->SecondName,
		head->FirstName,
		head->FatherName,
		head->GitHub,
		head->mail,
		head->group);
   if (head->next) fprintf(outFile, "\n");
    head=head->next;
}

fclose(outFile);
}

char *createMarks(){

    char *str=(char*)malloc(sizeof(char)*5);
    *str=NULL;
    char *Mark=(char*)malloc(sizeof(char));
    *Mark=NULL;
        int i=0;
    for (i=0;i<5;i++){

        int randomMark=1+rand() % 5 ;
       snprintf(Mark, sizeof(Mark), "%d", randomMark);
        strcat(str, Mark);

        if(i!=4) 
 	 strcat(str, ",");
            }
    return str;
    }

void createSecondTable(Student *head){

FILE *outFile=fopen("f2.csv", "w");

    while (head)
        {
	    fprintf(outFile, "%s,%s,%s,%s",
		    head->SecondName,
		    head->FirstName,
		    head->FatherName,
		    createMarks());
            if (head->next) fprintf(outFile, "\n");
            head=head->next;
        }

    fclose(outFile);
}

void createCommands(void){

int countOfCommands= 1+rand() % 5;
int *commands=(int*)malloc(sizeof(int)*countOfCommands);

for (int i=0; i<countOfCommands-1; i++)
	{
	*(commands+i)=1+ rand() % 4;
	}
*(commands+countOfCommands)=4;

FILE *file=fopen("commands", "w");
fwrite(commands,sizeof(commands),1, file);
fclose(file);
free(commands);
}
