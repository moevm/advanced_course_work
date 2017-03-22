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
	/* Arguments should be: input_file_1 input_file_2 commands_file */
	if (argc < 4)
	{
		printf("Fail with arguments");
		return 1;
	}

	/* Open files */
	FILE* Table1 = fopen(argv[1], "r+t");
	FILE* Table2 = fopen(argv[2], "r+t");
	FILE* Commands = fopen(argv[3], "r");

	if (Table1 == NULL)
	{
		printf("Fail with input_file_1");
		return 1;
	}
	else if (Table2 == NULL)
	{
		printf("Fail with input_file_2");
		return 1;
	}
	else if (Commands == NULL)
	{
		printf("Fail with Commands");
		return 1;
	}

	/* Create lists */
	Table* input_head = create_input_element();

	Read_Data(Table1, Table2, input_head);
	

	free_list(input_head);

	fclose(Table1);
	fclose(Table2);

    return 0;
}

