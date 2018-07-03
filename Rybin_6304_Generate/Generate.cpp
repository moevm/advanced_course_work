/*!
\file
\brief Generating data for checker

This file contains code for generate 2 random tables(csv format)  and commands_file.txt .

\author Rybin Aleksandr 1 course 2 half
\date 21.05.2017
\version 3.0
*/

#include "Generate_Header.h"

int main()
{

	// /* Initialize a seed for rand() */
	srand(time(NULL));

	/* Create new files */
	FILE* Table1 = fopen(INPUT1, "w");
	FILE* Table2 = fopen(INPUT2, "w");
	FILE* Commands = fopen(COMMANDS, "w");

	/* Create table header */
	fprintf(Table1, HEADER1);
	fprintf(Table2, HEADER2);

	Vector random = GenerateRandomVector();

	/* Write commands file as much as lines in generated table */
	for (int i = 0; i < random.len; i++)
		PutRandomCommands(Commands);

	/* Write files */
	for (int i = 0; i < random.len; i++)
	{
		/* Take random element from vector */
		int index = rand() % random.len;
		fprintf(Table1, "%s,%s,%s,%s,%s",
	        			random.vector_ptr[index].name,
	        			random.vector_ptr[index].surname,
	        			random.vector_ptr[index].patronymic,
	        			random.vector_ptr[index].GitHub_account,
	        			random.vector_ptr[index].Email);

		fprintf(Table2, "%s,%s,%d\n",
	        			random.vector_ptr[index].name,
	        			random.vector_ptr[index].surname,
	        			random.vector_ptr[index].exam_result);
		index = rand() % random.len;
		fprintf(Table1, ",%d\n", random.vector_ptr[index].group);
	}

	fclose(Table1);
	fclose(Table2);
	fclose(Commands);

  return 0;
}
