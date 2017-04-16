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
	FILE* Table1 = fopen(INPUT1, "r"); 
	FILE* Table2 = fopen(INPUT2, "r");

	if (Table1 == NULL)
	{
		printf("Fail with %s",INPUT1);
		return 0;
	}
	else if (Table2 == NULL)
	{
		printf("Fail with %s",INPUT2);
		return 0;
	}

	/* Read commands */
	if (argc < 3)
	{
		printf("Too few commands");
		return 0;
	}
	int* commands = (int*)malloc(sizeof(int) * (argc - 1));
	for (int i = 1; i < argc; i++)
	{	
		commands[i - 1] = atoi(argv[i]);
		if ((commands[i - 1] < 0) ||
			(commands[i - 1] > 5))
		{
			printf("Fail with command %d", i);
				return 0;
		}
	}
	if (!(commands[argc - 2] == 5))
	{
		printf("Fail with last command");
		return 0;
	}
	
	Vector Data = ReadFiles(Table1,Table2);
	if (Data.lenth < 1)
	{
		printf("Fail with data");
		return 0;
	}

	qsort(Data.vector_ptr, Data.lenth, sizeof(Table), (int (*)(const void*,const void*))CompareTable);

	free(commands);
	fclose(Table1);
	fclose(Table2);

    return 0;
}

