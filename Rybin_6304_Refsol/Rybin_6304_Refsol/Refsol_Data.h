/*!
\file

\brief Includes struct data for right solution
This file contains struct and functions to work with data.

\author Rybin Aleksandr 1 course 2 half
\date 17.03.2017
\version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
\struct
\brief Struct input for list of Tables
*/
typedef struct input
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	char* patronymic;		//!< Patronymic of student
	char* GitHub_account;	//!< GitHub account of student
	char* Email;			//!< Student's email
	int group;				//!< Student's group
	int exam_result;		//!< Mark for exam
	int line;				//!< Number of line in table

	input* next;			//!< Pointer to next member in list of fields of table
	input* prev;			//!< Pointer to previous member in list of fields of table
}input;

/*!
\brief creates object of strcut input
\return pointer to new object
\ingroup Refsol_Data
*/
input* create_input_element()
{
	input* element = (input*)malloc(sizeof(input));

	element->Email = (char*)malloc(sizeof(char) *30);
	element->GitHub_account = (char*)malloc(sizeof(char) *30);
	element->name = (char*)malloc(sizeof(char) *30);
	element->surname = (char*)malloc(sizeof(char) *30);
	element->patronymic = (char*)malloc(sizeof(char) *30);

	element->group = 0;
	element->exam_result = 0;
	element->line = 0;

	element->next = NULL;
	element->prev = NULL;

	return element;
}

/*!
\brief free list of input
\param[in] input_head pointer to begin of list input
\return void
\ingroup Refsol_Data
*/
void free_input(input* input_head)
{
	while (true)
	{
		if (input_head->next == NULL)
		{
			free(input_head->name);
			free(input_head->surname);
			free(input_head->Email);
			free(input_head->GitHub_account);
			free(input_head->patronymic);
			free(input_head);
			return;
		}

		input_head = input_head->next;
		
		free(input_head->prev->name);
		free(input_head->prev->surname);
		free(input_head->prev->Email);
		free(input_head->prev->GitHub_account);
		free(input_head->prev->patronymic);
		free(input_head->prev);

	}
}

/*!
\brief push new object to end of list input
\param[in] input_head pointer to begin of list input
\param[in] push_element pointer to object to push
\return void
\ingroup Refsol_Data
*/
void push_input(input* input_head, input* push_element)
{
	while (input_head->next)
	{
		input_head = input_head->next;
	}

	input_head->next = push_element;
	push_element->prev = input_head;

}


