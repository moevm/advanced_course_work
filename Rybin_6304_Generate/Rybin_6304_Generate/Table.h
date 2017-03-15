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
	srand(clock());

	if (a == 0)
	{
		random = 1 + rand() %1000;
		return &random;
	}
	else if (a == 1)
	{
		random = 1 + rand() %5;
		return &random;
	}
	else
	{

		int lenth = rand() % 10 + 1;
		int* random_array = (int*)malloc(sizeof(int) * lenth);
		
		for (int i = 0; i < lenth - 1; i++)
		{
			srand(clock());

			random_array[i] = 1 + rand() %5;
		}
		random_array[lenth] = 5;

		return random_array;
	}
}

/*!
\brief Generates random integer[1-10000]
\return random_token Random integer value of group or mark
\ingroup Random
*/
char* generate_token()
{
	srand(clock());
	int lenth = 1 + rand() %20;
	char* random_token = (char*)malloc(sizeof(char) * lenth);

	for (int i = 0; i < lenth; i++)
	{
		srand(clock());

		random_token[i] = (char)(65 + rand() %58);
	}
	return random_token;

}