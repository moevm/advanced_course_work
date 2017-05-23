/*!
\file
\brief Solving checker task

This file contains code for checker task on right way for compare with user solve.

\author Rybin Aleksandr 1 course 2 half
\date 22.05.2017
\version 2.0
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
	if (!(commands[argc - 2] == SAVE_RESULTS))	// Last command always 5 - "save results"
	{
		printf("Fail with last command\n");
		return 1;
	}

	Vector Data1,Data2,Data;
	ReadTable1(Table1,&Data1);
	ReadTable2(Table2,&Data2);
	CombineTables(&Data1,&Data2,&Data);
	if (Data1.len < 1 || Data2.len < 1 || Data.len < 1)
	{
		printf("Fail with data\n");
		return 1;
	}

	qsort(Data.vector_ptr,Data.len,sizeof(Table),(int (*)(const void*,const void*))CompareTable);

    /* Work with commands */
	for (int i = 0; i < argc - 1; i++)
	{
		switch (commands[i])
		{
			case CHECK_REPEATS:
				{
				CheckRepeats(&Data);
				break;
				}
			case CHECK_BY_GROUP:
				{
				CheckByGroup(&Data);
				break;
				}
			case CHECK_BAD_RESULTS:
				{
				CheckBadResults(&Data);
				break;
				}
			case CHECK_GOOD_RESULTS:
				{
				CheckGoodResults(&Data);
				break;
				}
			case SAVE_RESULTS:
				{
				SaveResults(&Data);
				break;
				}
            default:
                break;
		}
	}

	free(commands);
	fclose(Table1);
	fclose(Table2);

    return 0;
}
