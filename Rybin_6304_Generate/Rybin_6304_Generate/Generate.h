/*!
\file
\brief Includes for generate data

This file contains struct and functions for generate data.

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
\brief Struct Table for generating temporary data for tables
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
\param[in] a Type of random, 0 if need [1,1000], 1 if need [0,5]
\return random Random integer value of group or mark 
\ingroup Generate_Random_Data
*/
int generate_number(int a)
{
	int random;

	if (a == 0)
			random = 1 + rand() % 1000;
	else
			random = 1 + rand() % 5;

	 return random;
}

/*!
\brief Generates random token(char*) 
\param[in] a Type of random, 0 if just token, 1 if Email token, 2 if GitHub token
\return random_token Pointer to random token
\ingroup Generate_Random_Data
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
\return void 
\ingroup Generate_Random_Data
*/
void generate_field(Table* Table_obj)
{
	Table_obj->Email = generate_token(1);
	Table_obj->GitHub_account = generate_token(2);
	Table_obj->name = generate_token(0);
	Table_obj->surname = generate_token(0);
	Table_obj->patronymic = generate_token(0);
	Table_obj->group = generate_number(0);
	Table_obj->exam_result = generate_number(1);
}

/*!
\brief Generates array of integers [0,4] end is always 5
\return void 
\ingroup Generate_Random_Data
*/
void put_random_array()
{
	int lenth = 2 + rand() % 8;
	
	for (int i = 0; i < lenth; i++)
		printf("%d ", rand() %5);
	printf("5\n");
}