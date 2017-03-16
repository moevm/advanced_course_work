/*!
\file
\brief Includes for generate data

This file contains structs and functions for generate data.

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*!
\struct
\brief Struct Table for generating data for first table
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
} Table;

/*!
\brief Generates random integer[1-1000]
\param[in] a Type of random, 0 if group number, 1 if mark for exam, 2 if array of random integer[0-5]
\return pointer Random integer(pointer) value of group or mark or array
\ingroup Random
*/
int* generate_number(int a)
{
	int random;

	switch (a)
	{

	case 0:
	{
		random = 1 + rand() % 1000;
		return &random;
		break;
	}
	case 1:
	{
		random = 1 + rand() % 5;
		return &random;
		break;
	}
	case 2:
	{

		int lenth = rand() % 10 + 1;
		int* random_array = (int*)malloc(sizeof(int) * lenth);

		for (int i = 0; i < lenth - 1; i++)
		{
			random_array[i] = 1 + rand() % 5;
		}
		random_array[lenth] = 5;

		return random_array;
	}
	}
}

/*!
\brief Generates random integer[1-10000]
\param[in] a Type of random, 0 if just token, 1 if Email token, 2 if GitHub token
\return random_token Random token(char*)
\ingroup Random
*/
char* generate_token(int a)
{
	int lenth = 5 + rand() % 10;
	char* random_token = (char*)malloc(sizeof(char) * (lenth + 9));

	for (int i = 0; i < lenth - 1; i++)
	{
		random_token[i] = (char)(97 + rand() % 25);
	}
	random_token[lenth - 1] = '\0';

	switch (a)
	{
	case 1:
		{
			strncat(random_token, "@Email", 6);
			random_token[lenth + 8] = '\0';
			break;
		}
	case 2:
		{
			strncat(random_token, "@GitHub", 7);
			random_token[lenth + 8] = '\0';
			break;
		}
	default: break;
	}

	return random_token;
}


/*!
\brief Generates table field 
\param[in] Table_obj struct to write data
\return nothing
\ingroup Random
*/
void generate_field(Table* Table_obj)
{
	Table_obj->Email = generate_token(1);
	Table_obj->GitHub_account = generate_token(2);
	Table_obj->name = generate_token(0);
	Table_obj->surname = generate_token(0);
	Table_obj->patronymic = generate_token(0);
	Table_obj->group = *generate_number(0);
	Table_obj->exam_result = *generate_number(1);
}