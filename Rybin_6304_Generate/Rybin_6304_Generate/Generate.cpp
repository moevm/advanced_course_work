/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and commands_file.txt .

\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0

*/

#include "Generator.h"

int main()
{
	/* Initialize a seed for rand() */
	srand(time(NULL));

	/* Create new files */
	FILE* Random_Table1 = fopen("input_file_1.csv", "w");
	FILE* Random_Table2 = fopen("input_file_2.csv", "w");
	FILE* Commands_file = fopen("commands.txt", "w");

	put_random_commands(Commands_file);

	/* Create table header */
	fprintf(Random_Table1, "Name,Surname,Patronymic,GitHub,Email,Group\n");
	fprintf(Random_Table2, "Name,Surname,Exam_mark\n");


	
	
	fclose(Random_Table1);
	fclose(Random_Table2);

    return 0;
}

