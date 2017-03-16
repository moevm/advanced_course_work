/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and integer array of elements [0-5].

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include "Generate.h"

int main()
{
	/* Create new files */
	FILE* Random_Table1 = fopen("input_file_1.csv", "w");
	FILE* Random_Table2 = fopen("input_file_2.csv", "w");

	/* Create table header */
	fprintf(Random_Table1, "Name,Surname,Patronymic,GitHub,Email,Group\n");
	fprintf(Random_Table2, "Name,Surname,Exam_mark\n");

	/* Put a name of created tables and array of commands to stdout*/
	printf("input_file_1.csv input_file_2.csv ");
	put_random_array();

	srand(clock());
	int lenth = 10 + rand() %5;

	/* Create a temporary data struct */
	Table* Table_obj = (Table*)malloc(sizeof(Table));

	/* Put a fields in table */
	for (int i = 0; i < lenth; i++)
	{

		generate_field(Table_obj);

		fprintf(Random_Table1, "%s,%s,%s,%s,%s,%d\n",
			Table_obj->name,
			Table_obj->surname,
			Table_obj->patronymic,
			Table_obj->GitHub_account,
			Table_obj->Email,
			Table_obj->group);

		fprintf(Random_Table2, "%s,%s,%d\n",
			Table_obj->name,
			Table_obj->surname,
			Table_obj->exam_result);

		/* Delete temporary data */
		free(Table_obj->Email);
		free(Table_obj->GitHub_account);
		free(Table_obj->name);
		free(Table_obj->surname);
		free(Table_obj->patronymic);
		
	}
	
	free(Table_obj);

	fclose(Random_Table1);
	fclose(Random_Table2);

    return 0;
}

