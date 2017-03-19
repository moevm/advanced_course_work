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
	/* Arguments should be: input_file_1 input_file_2 comand[0-4] 5 ... */
	if (argc < 4)
	{
		printf("Failed with arguments");
		return 1;
	}

	/* Open files */
	FILE* Table1 = fopen(argv[1], "r");
	FILE* Table2 = fopen(argv[2], "r");
	if (Table1 == NULL)
	{
		printf("Failed with input_file_1");
		return 1;
	}
	if (Table2 == NULL)
	{
		printf("Failed with input_file_2");
		return 1;
	}

	/* Create lists */
	input1* input1_head = create_input1_element();
	input2* input2_head = create_input2_element();

	Read_Data(Table1, Table2, input1_head, input2_head);
	
	
	
	
	free_input1(input1_head);
	free_input2(input2_head);

	fclose(Table1);
	fclose(Table2);
    return 0;
}

