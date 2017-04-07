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
	/* Arguments should be: input_file_1 input_file_2 commands_file */
	if (argc < 4)
	{
		printf("Too few arguments");
		return -1;
	}

	/* Open files */
	FILE* Table1 = fopen(argv[1], "r"); 
	FILE* Table2 = fopen(argv[2], "r");
	FILE* Commands_File = fopen(argv[3], "r");

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
	else if (Commands_File == NULL)
	{
		printf("Fail with Commands");
		return -1;
	}

	Vector Data = Read_Files(Table1,Table2);
	if (Data.lenth < 0)
		return -1;

	Vector commands = Read_Commands(Commands_File);
	if (commands.lenth < 0)
		return -1;

	free(commands.vector_ptr);
	fclose(Table1);
	fclose(Table2);

    return 0;
}

