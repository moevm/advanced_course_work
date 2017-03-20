/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and integer array .

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include "Generate.h"
#include "Generate_Data.h"

int main()
{
	/* Initialize a seed for rand() */
	srand(time(NULL));

	/* Create new files */
	FILE* Random_Table1 = fopen("input_file_1.csv", "w");
	FILE* Random_Table2 = fopen("input_file_2.csv", "w");
	FILE* Commands_file = fopen("commands.txt", "w");

	put_random_array(Commands_file);

	/* Create table header */
	fprintf(Random_Table1, "Name,Surname,Patronymic,GitHub,Email,Group\n");
	fprintf(Random_Table2, "Name,Surname,Exam_mark\n");

	/* Lines in table */
	int lenth = 5 + rand() %15;

	/* Create a temporary data list  */
	Table* head = generate_field();

	/* Put a fields in table */
	for (int i = 0; i < lenth; i++)
	{
	
	}
	
	free_list(head);
	fclose(Random_Table1);
	fclose(Random_Table2);

    return 0;
}

