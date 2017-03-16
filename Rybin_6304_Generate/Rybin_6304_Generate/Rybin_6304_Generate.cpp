/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and integer array of elements [0-5].

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include "Table.h"

int main()
{
	FILE* Random_Table1 = fopen("input_file_1.csv", "w");
	FILE* Random_Table2 = fopen("input_file_2.csv", "w");

	srand(clock());
	int lenth = 1 + rand() %20;

	Table1* Table1_obj = (Table1*)malloc(sizeof(Table1));
	Table2* Table2_obj = (Table2*)malloc(sizeof(Table2));

	for (int i = 0; i < lenth; i++)
	{

		generate_field(Table1_obj, Table2_obj);

		fprintf(Random_Table1, "%s,%s,%s,%s,%s,%d\n",
			Table1_obj->Email,
			Table1_obj->GitHub_account,
			Table1_obj->name,
			Table1_obj->surname,
			Table1_obj->patronymic,
			Table1_obj->group);

		fprintf(Random_Table2, "%s,%s,%d\n",
			Table2_obj->name,
			Table2_obj->surname,
			Table2_obj->exam_result);

		free(Table1_obj->Email);
		free(Table1_obj->GitHub_account);
		free(Table1_obj->name);
		free(Table1_obj->surname);
		free(Table1_obj->patronymic);
		
		free(Table2_obj->name);
		free(Table2_obj->surname);
	}

	free(Table1_obj);
	free(Table2_obj);

	fclose(Random_Table1);
	fclose(Random_Table2);

    return 0;
}

