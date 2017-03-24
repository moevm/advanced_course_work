/*!
\file
\brief Funsctions to work with Readed or Generated Data

This file contains struct and functions for save and work with generated data or readed data.

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include "Generate.h"

#define Max_Lenth_field 30	//!< Max lenth of created fields in struct Table
#define Max_Group 1000		//!< Max generating group number
#define Max_Exam_result 5	//!< Max generating exam result

/*!
\struct
\brief Struct Table for generating temporary data, or read data from tables
*/
typedef struct Table
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	char* patronymic;		//!< Patronymic of student
	char* GitHub_account;	//!< GitHub account of student
	char* Email;			//!< Student's email
	int group;				//!< Student's group
	int exam_result;		//!< Mark for exam
	int number;				//!< Number of element in list, or number of line in table

	Table* next;			//!< Pointer to next element
	Table* prev;			//!< Pointer to previous element
} Table;

/*!
\brief Generates random table field
\param[in] number Number of creating element
\return Table_obj Pointer to new object
\ingroup Generate
*/
Table* generate_field(int number)
{
	Table* Table_obj = (Table*)malloc(sizeof(Table));

	Table_obj->Email = generate_token(1);
	Table_obj->GitHub_account = generate_token(2);
	Table_obj->name = generate_token(0);
	Table_obj->surname = generate_token(0);
	Table_obj->patronymic = generate_token(0);
	Table_obj->group = 1 + rand() % Max_Group;
	Table_obj->exam_result = 1 + rand() % Max_Exam_result;
	Table_obj->number = number;

	Table_obj->next = NULL;
	Table_obj->prev = NULL;

	return Table_obj;
}

/*!
\brief Push new object to end of list
\param[in] head Pointer to begin of list
\param[in] new_element Pointer to object to push
\return void
\ingroup Data
*/
void push(Table* head, Table* new_element)
{
	while (head->next)
	{
		head = head->next;
	}

	head->next = new_element;
	new_element->prev = head;
}

/*!
\brief Crate list of random fields
\param[in] head Pointer to begin of list
\param[in] count number of elements that wiil be generate
\return void
\ingroup Generate
*/
void create_random_list(Table* head,int count)
{
	for (int i = 0; i < count; i++)
	{
		push(head, generate_field(i));
	}
}

/*!
\brief Printf field by number
\param[in] head Pointer to begin of list
\param[in] number number of element that need to print
\param[in] table1 Pointer to first file
\param[in] table 2 Pointer to second file
\return void
\ingroup Data
*/
void print_field(Table* head, int number,FILE* table1,FILE*table2)
{
	while (head->next)
	{
		if (head->number == number)
		{
			fprintf(table1, "%s,%s,%s,%s,%s,%d\n",
				head->name,
				head->surname,
				head->patronymic,
				head->GitHub_account,
				head->Email,
				head->group);
			fprintf(table2, "%s,%s,%d\n",
				head->name,
				head->surname,
				head->exam_result);

			return;
		}
		else
			head = head->next;
	}
}

/*!
\brief Free list
\param[in] head Pointer to begin of list
\return void
\ingroup Data
*/
void free_list(Table* head)
{
	while (head)
	{
		if (head->next == NULL)
		{
			free(head->Email);
			free(head->surname);
			free(head->name);
			free(head->patronymic);
			free(head->GitHub_account);
			free(head);
			return;
		}

		head = head->next;
		free(head->prev->Email);
		free(head->prev->surname);
		free(head->prev->name);
		free(head->prev->patronymic);
		free(head->prev->GitHub_account);
		free(head->prev);


	}
}

/*!
\brief creates object of strcut Table
\return pointer to new object
\ingroup Data
*/
Table* create_input_element()
{
	Table* element = (Table*)malloc(sizeof(Table));

	element->Email = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element->GitHub_account = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element->name = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element->surname = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element->patronymic = (char*)malloc(sizeof(char) * Max_Lenth_field);

	element->group = 0;
	element->exam_result = 0;
	element->number = 0;

	element->next = NULL;
	element->prev = NULL;

	return element;
}

/*!
\brief Remove element
\param[in] input_head Pointer to begin of list
\return void
\ingroup Data
*/
void Remove_element(Table* head)
{
		if (head->next == NULL)
		{
			head->prev->next = NULL;
			free(head->Email);
			free(head->surname);
			free(head->name);
			free(head->patronymic);
			free(head->GitHub_account);
			free(head);
		}

		head->prev->next = head->next;
		head->next->prev = head->prev;

		free(head->Email);
		free(head->surname);
		free(head->name);
		free(head->patronymic);
		free(head->GitHub_account);
		free(head);
}