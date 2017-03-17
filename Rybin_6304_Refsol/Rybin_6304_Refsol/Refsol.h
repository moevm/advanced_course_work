/*!
\file

\brief Includes for right solution 
This file contains struct and functions for to solve task.

\author Rybin Aleksandr 1 course 2 half
\date 17.03.2017
\version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct input1
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	char* patronymic;		//!< Patronymic of student
	char* GitHub_account;	//!< GitHub account of student
	char* Email;			//!< Student's email
	int group;				//!< Student's group

	input1* next;			//!< Pointer to next member in list of fields of table
	input1* prev;			//!< Pointer to previous member in list of fields of table
}input1;

typedef struct input2
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	int exam_result;		//!< Mark for exam
	input2* next;			//!< Pointer to next member in list of fields of table
	input2* prev;			//!< //!< Pointer to previous member in list of fields of table
}input2;


input1* create_input1_element()
{
	input1* element = (input1*)malloc(sizeof(input1));
	
	element->Email = (char*)malloc(sizeof(char) * 100);
	element->GitHub_account = (char*)malloc(sizeof(char) * 100);
	element->name = (char*)malloc(sizeof(char) * 100);
	element->surname = (char*)malloc(sizeof(char) * 100);
	element->patronymic = (char*)malloc(sizeof(char) * 100);

	element->next = NULL;
	element->prev = NULL;
}

input2* create_input2_element()
{
	input2* element = (input2*)malloc(sizeof(input2));

	element->name = (char*)malloc(sizeof(char) * 100);
	element->surname = (char*)malloc(sizeof(char) * 100);

	element->next = NULL;
	element->prev = NULL;
}

void Read_Data(FILE* stream_1, FILE* stream_2, input1* input1_head, input2* input2_head)
{
	do
	{
		

	} while (!feof(stream_1));

}