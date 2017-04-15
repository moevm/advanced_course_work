/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and commands_file.txt .

\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generate_Header.h"

int main()
{
	/* Initialize a seed for rand() */
	srand(time(NULL));

	/* Create new files */
	FILE* Random_Table1 = fopen("input_file_1.csv", "w");
	FILE* Random_Table2 = fopen("input_file_2.csv", "w");
	FILE* Commands_file = fopen("commands.txt", "w");

	/* Create table header */
	fprintf(Random_Table1, HEADER1);
	fprintf(Random_Table2, HEADER2);

	Vector info = GenerateRandomVector();

	/* Write commands file */
	for (int i = 0; i < info.lenth; i++)
		PutRandomCommands(Commands_file);

	/* Write files */
	for (int i = 0; i < info.lenth; i++)
	{
		/* Take random element from vector */
		int index = rand() % info.lenth;
		fprintf(Random_Table1, "%s,%s,%s,%s,%s",

			info.vector_ptr[index].name,
			info.vector_ptr[index].surname,
			info.vector_ptr[index].patronymic,
			info.vector_ptr[index].GitHub_account,
			info.vector_ptr[index].Email);

		fprintf(Random_Table2, "%s,%s,%d\n",
			info.vector_ptr[index].name,
			info.vector_ptr[index].surname,
			info.vector_ptr[index].exam_result);
		index = rand() % info.lenth;
		fprintf(Random_Table1, ",%d\n", info.vector_ptr[index].group);
	}

	/* Free vector and close files */
	for (int i = 0; i < info.lenth; i++)
		{
			free(info.vector_ptr[i].name);
			free(info.vector_ptr[i].surname);
			free(info.vector_ptr[i].patronymic);
			free(info.vector_ptr[i].Email);
			free(info.vector_ptr[i].GitHub_account);
		}
	free(info.vector_ptr);
	fclose(Random_Table1);
	fclose(Random_Table2);
	fclose(Commands_file);

    return 0;
}

