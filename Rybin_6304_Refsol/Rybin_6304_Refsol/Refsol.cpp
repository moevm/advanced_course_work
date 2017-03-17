/*!
\file
\brief Solving checker task 

This file contains code for checker task on right way for compare with user solve.

\author Rybin Aleksandr 1 course 2 half
\date 17.03.2017
\version 1.0
*/

#include "Refsol.h"

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		printf("Failed with arguments");
		return 1;
	}

	FILE* Table1 = fopen(argv[1], "r");
	FILE* Table2 = fopen(argv[2], "r");
	if (Table1 == NULL)
	{
		printf("Failed with input_file_1");
		return 1;
	}
	if (Table2 == NULL)
	{
		printf("Failed with input_file_2");
		return 1;
	}

	do
	{

	} while (!feof(Table1));





    return 0;
}

