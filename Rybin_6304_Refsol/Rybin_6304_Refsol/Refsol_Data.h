/*!
\file

\brief Includes struct data for right solution
This file contains struct and functions for to solve task.

\author Rybin Aleksandr 1 course 2 half
\date 17.03.2017
\version 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
\struct
\brief Struct input1 for list of Table1
*/
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

/*!
\struct
\brief Struct input2 for list of Table2
*/
typedef struct input2
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	int exam_result;		//!< Mark for exam
	
	input2* next;			//!< Pointer to next member in list of fields of table
	input2* prev;			//!< //!< Pointer to previous member in list of fields of table
}input2;


/*!
\brief creates object of strcut input1
\return pointer to new object
\ingroup Refsol_Data
*/
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

	return element;
}

/*!
\brief creates object of strcut input2
\return pointer to new object
\ingroup Refsol_Data
*/
input2* create_input2_element()
{
	input2* element = (input2*)malloc(sizeof(input2));

	element->name = (char*)malloc(sizeof(char) * 100);
	element->surname = (char*)malloc(sizeof(char) * 100);

	element->next = NULL;
	element->prev = NULL;

	return element;
}

/*!
\brief free list of input1
\param[in] input1_head pointer to begin of list input1
\return void
\ingroup Refsol_Data
*/
void free_input1(input1* input1_head)
{
	while (input1_head)
	{
		if (input1_head->next == NULL)
		{
			free(input1_head->name);
			free(input1_head->surname);
			free(input1_head->Email);
			free(input1_head->GitHub_account);
			free(input1_head->patronymic);
			free(input1_head);
		}

		input1_head = input1_head->next;
		
		free(input1_head->prev->name);
		free(input1_head->prev->surname);
		free(input1_head->prev->Email);
		free(input1_head->prev->GitHub_account);
		free(input1_head->prev->patronymic);
		free(input1_head->prev);

	}
}

/*!
\brief free list of input2
\param[in] input1_head pointer to begin of list input2
\return void
\ingroup Refsol_Data
*/
void free_input2(input2* input2_head)
{
	while (input2_head)
	{
		if (input2_head->next == NULL)
		{
			free(input2_head->name);
			free(input2_head->surname);
			free(input2_head);
		}

		input2_head = input2_head->next;

		free(input2_head->prev->name);
		free(input2_head->prev->surname);
		free(input2_head->prev);
	}
}

/*!
\brief push new object to end of list input1
\param[in] input1_head pointer to begin of list input1
\param[in] push_element pointer to object to push
\return void
\ingroup Refsol_Data
*/
void push_input1(input1* head, input1* push_element)
{
	while (head->next)
	{
		head = head->next;
	}

	head->next = push_element;
	push_element->prev = head;
}

/*!
\brief push new object to end of list input2
\param[in] input1_head pointer to begin of list input2
\param[in] push_element pointer to object to push
\return void
\ingroup Refsol_Data
*/
void push_input2(input2* head, input2* push_element)
{
	while (head->next)
	{
		head = head->next;
	}

	head->next = push_element;
	push_element->prev = head;
}
