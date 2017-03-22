/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and integer array .

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include "Data.h"

#define Max_lines 15		//!< Max lines in generating table
#define Min_lines 5			//!< Min lines in generating table

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
	int lenth = Min_lines + rand() %Max_lines;

	/* Create a first element of data list */
	Table* head = generate_field(0);
	create_random_list(head, lenth);

	/* Put a fields in table */
	for (int i = 0; i < lenth; i++)
	{
		print_field(head, rand() % lenth, Random_Table1, Random_Table2);
	}
	
	free_list(head);
	fclose(Random_Table1);
	fclose(Random_Table2);

    return 0;
}

