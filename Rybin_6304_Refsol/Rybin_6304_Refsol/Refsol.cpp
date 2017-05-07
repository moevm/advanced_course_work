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
		printf("Fail with %s\n",INPUT1);
		return 1;
	}
	else if (Table2 == NULL)
	{
		printf("Fail with %s\n",INPUT2);
		return 1;
	}

	/* Read commands */
	if (argc < 3)
	{
		printf("Too few commands\n");
		return 1;
	}
	int* commands = (int*)malloc(sizeof(int) * (argc - 1));
	for (int i = 1; i < argc; i++)
	{	
		commands[i - 1] = atoi(argv[i]);
		if ((commands[i - 1] < 1) ||	// Commands must be {1,2,3,4,5}
			(commands[i - 1] > 5))
		{
			printf("Fail with command %d\n", i);
				return 1;
		}
	}
	if (!(commands[argc - 2] == 5))	// Last command always 5 - "save results"
	{
		printf("Fail with last command\n");
		return 1;
	}
	
	Vector Data = ReadFiles(Table1,Table2);
	if (Data.lenth < 1)
	{
		printf("Fail with data\n");
		return 1;
	}

	qsort(Data.vector_ptr, Data.lenth, sizeof(Table), (int (*)(const void*,const void*))CompareTable);
	/* Work with commands */
	for (int i = 0; i < argc - 1; i++)
	{
		switch (commands[i])
		{
			case 1:
				{
				CheckRepeats(Data);
				break;
				}
			case 2:
				{
				CheckByGroup(Data);
				break;
				}
			case 3:
				{
				CheckBadResults(Data);
				break;
				}
			case 4:
				{
				CheckGoodResults(Data);
				break;
				}
			case 5:
				{
				SaveResults(Data);
				break;
				}
		}
	}

	/* Free Vector with readed data */
	for (int i = 0; i < Data.lenth; i++)
	{
		free(Data.vector_ptr[i].name);
		free(Data.vector_ptr[i].surname);
		free(Data.vector_ptr[i].patronymic);
		free(Data.vector_ptr[i].GitHub_account);
		free(Data.vector_ptr[i].Email);
	}
	free(Data.vector_ptr);
	free(commands);
	fclose(Table1);
	fclose(Table2);

    return 0;
}

