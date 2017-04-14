/*!
\file
\brief Solving checker task 

This file contains code for checker task on right way for compare with user solve.

\author Rybin Aleksandr 1 course 2 half
\date 17.03.2017
\version 1.0
*/

#include "Refsol_Header.h"

int main(int argc, char* argv[])
{	
	/* Open files */
	FILE* Table1 = fopen("input_file_1", "r"); 
	FILE* Table2 = fopen("input_file_2", "r");

	if (Table1 == NULL)
	{
		printf("Fail with input_file_1");
		return -1;
	}
	else if (Table2 == NULL)
	{
		printf("Fail with input_file_2");
		return -1;
	}

	/* Read commands */
	if (argc < 3)
	{
		printf("Too few commands");
		return 0;
	}
	int* commands = (int*)malloc(sizeof(int) * argc);
	for (int i = 1; i < argc; i++)
	{	
		commands[i] = atoi(argv[i]);
		if ((commands[i] < 0) ||
			(commands[i] > 5))
		{
			printf("Fail with command %d", i);
				return 0;
		}
	}
	if (!(commands[argc - 1] == 5))
	{
		printf("Fail with last command");
		return 0;
	}
	
	Vector Data = Read_Files(Table1,Table2);
	if (Data.lenth < 0)
		return -1;

	free(commands);
	fclose(Table1);
	fclose(Table2);

    return 0;
}

