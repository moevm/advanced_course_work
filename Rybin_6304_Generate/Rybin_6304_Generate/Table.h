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
\brief Struct Table1 for generating data for first table
*/
typedef struct Table1
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	char* patronymic;		//!< Patronymic of student
	char* GitHub_account;	//!< GitHub account of student
	char* Email;			//!< Student's email
	int group;				//!< Student's group
} Table1;

/*!
\struct
\brief Struct Table2 for generating data for second table
*/
typedef struct Table2
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	int exam_result;		//!< Mark for exam
} Table2;

/*!
\brief Generates random integer[1-10000]
\param[in] a Type of random, 0 if group number, 1 if mark for exam, 2 if array of random integer[0-5]
\return pointer Random integer(pointer) value of group or mark or array
\ingroup Random
*/
int* generate_number(int a)
{
	int random;

	if (a == 0)
	{
		random = 1 + rand() % 1000;
		return &random;
	}
	else if (a == 1)
	{
		random = 1 + rand() % 5;
		return &random;
	}
	else
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

/*!
\brief Generates random integer[1-10000]
\param[in] a Type of random, 0 if just token, 1 if Email token, 2 if GitHub token
\return random_token Random integer value of group or mark
\ingroup Random
*/
char* generate_token(int a)
{
	int lenth = 5 + rand() %10;
	char* random_token = (char*)malloc(sizeof(char) * (lenth + 9));

	for (int i = 0; i < lenth - 1; i++)
	{
		random_token[i] = (char)(97 + rand() %25);
	}
	random_token[lenth - 1] = '\0';

	if (a == 1)
	{
		strncat(random_token, "@Email", 6);
		random_token[lenth + 8] = '\0';
	}
	if (a == 2)
	{
		strncat(random_token, "@GitHub", 7);
		random_token[lenth + 8] = '\0';
	}
	return random_token;

}

/*!
\brief Generates table field 1 and 2
\param[in] Table1_obj struct to write data
\param[in] Table2_obj struct to write data
\return nothing
\ingroup Random
*/
void generate_field(Table1* Table1_obj, Table2* Table2_obj)
{
	char* name = generate_token(0);
	char * surname = generate_token(0);

	Table1_obj->Email = generate_token(1);
	Table1_obj->GitHub_account = generate_token(2);
	Table1_obj->name = name;
	Table1_obj->surname = surname;
	Table1_obj->patronymic = generate_token(0);
	Table1_obj->group = *generate_number(0);

	Table2_obj->name = name;
	Table2_obj->surname = surname;
	Table2_obj->exam_result = *generate_number(1);
}