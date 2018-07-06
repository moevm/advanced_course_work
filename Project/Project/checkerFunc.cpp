#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

struct Person{
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

typedef struct Person Student;


Student *createStudent(char *smallString){

    Student *rr=(Student*)malloc(sizeof(Student));
    char **str2=(char**)malloc(100*sizeof(char*));
    int i=0;

    smallString=strtok(smallString, ","); // èñïîëüçîâàíèå ôóíêöèè strtok, ðàçáèâàþùåé str íà ëåêñåìû

        while (smallString!=NULL){    // âûâîä ïðåäëîæåíèé
        *(str2+i)=smallString;
        i++;
        smallString=strtok(NULL, ",");
        }

    strcpy(rr->SecondName, *(str2));
    strcpy(rr->FirstName, *(str2+1));
    strcpy(rr->FatherName, *(str2+2));
    strcpy(rr->GitHub, *(str2+3));
    strcpy(rr->mail, *(str2+4));
    rr->group=atoi(*(str2+5));
    rr->next = NULL;
        rr->prev = NULL;

    free(str2);
    return rr;
}

Student *readTheFirstTable(FILE *file){

    char *string=(char*)malloc(200*sizeof(char));
    char **doubleString=(char**)malloc(200*sizeof(char*));

    Student *head;
    Student *prev;
    Student *current;
    int i=0;
    while(fgets(string, 1000, file))
        {

                if(string[strlen(string)-1] == '\n')
                {
                        string[strlen(string)-1]='\0';
                }
                
                *(doubleString+i)= string;
                if (i==0){head=createStudent(doubleString[0]); prev= head;}
        else
        {
            current = createStudent(doubleString[i]);
            current->prev = prev;
            prev->next = current;
            prev = current;
        }
                i++;
        }

   	 free(string);
	 free(doubleString);

        fclose(file);
        return head;
}

void averageGrade(Student *current, char *doubleString){

    doubleString=strtok(doubleString, ",");
    int i=1;

    while ((*(current->SecondName)!=*doubleString) || (!current))
        current=current->next;

    if(!current) return;
    while (doubleString!=NULL){
        if(i<3)
        {
        doubleString=strtok(NULL,",");        }
        else
        {
            current->examResult+=atoi(doubleString);


            doubleString=strtok(NULL,",");
        }
        i+=1;
    }
    current->averageResult=current->examResult;
}


void readTheSecondTable(FILE *file, Student *head){

    char *string=(char*)malloc(200*sizeof(char)); // ñîçäàåì äâóìåðíûé ìàññèâ, êîòîðûé áóäåò ñ÷èòûâàòü íàøè äàííûå
    char **doubleString=(char**)malloc(200*sizeof(char*));
    Student *current=head;
    int i=0;

    while(fgets(string, 1000, file))
        {

                if(string[strlen(string)-1] == '\n')//ïðîâåðÿåì ÿâëÿåòñÿ ëè ïîñëåäíèé ýëåìåíò â ñòðîêå ñèìâîëîì å¸ îêîí÷àíèÿ
                {
                        string[strlen(string)-1]='\0';
                }

                *(doubleString+i)= string;

                averageGrade(current, doubleString[i]);
                current=current->next;
                i++;
        }



        fclose(file);
        free(string);
        free(doubleString);
}

int compare(const void * x1, const void * x2) {
	return ( *(int*)x1 - *(int*)x2 );
}

int *SortOfGroup(Student *head, int countOfStudents){

int *array=(int*)malloc(sizeof(int)*countOfStudents);
int i=0;
for (i=0; i<countOfStudents;i++)
    {
    *(array+i)=head->group;
    head=head->next;
    }
qsort(array, countOfStudents, sizeof(int), compare);
return array;
}
void concatenate(Student *head, FILE *outfile){

char *examResult=(char*)malloc(sizeof(char));
snprintf(examResult, sizeof(examResult), "%d", head->examResult);

fprintf(outfile,"%s,%s,%s,%s,%s,%s\n",
	head->SecondName,
	head->FirstName,
	head->FatherName,
	head->GitHub,
	head->mail,
	examResult);
free(examResult);
}

void createNewTables(Student *head){

int countOfStudents=0;
Student *saveHead=head;
char NumberOfGroup[4];
while (head)
{
countOfStudents++;

head=head->next;
}

head=saveHead;
FILE *outfile=fopen("r.csv", "w");
int *array=SortOfGroup(head, countOfStudents);
int checkTheFirst=0;
int redax=10;
int check;
int i=0;
for (i=0; i<countOfStudents; i++){
        head=saveHead;

    if (check== *(array+i))
        continue;

    while (head){
            if (head->group== *(array+i)){
                    check=head->group;
                    if (checkTheFirst==0)
                    {
                       snprintf(NumberOfGroup, 5, "%d", head->group);
			fprintf(outfile,"%s\n", NumberOfGroup);                       
                        checkTheFirst=1;
                    }
		concatenate(head, outfile);		

            }
            head=head->next;
    }
    checkTheFirst=0;
	if (i+1!=countOfStudents)
	fprintf(outfile,"\n\n");
}
fclose(outfile);
}

void findExcellentPupils(Student *head){

int CountOfExcellentPupils=0;
while (head){
    if (head->averageResult>=22.5)
    {
        CountOfExcellentPupils++;
    }

     head=head->next;
}

printf(" %d\n", CountOfExcellentPupils);
}
