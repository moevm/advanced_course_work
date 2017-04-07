/*!
\file
\brief Refsol Functions
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Refsol_Header.h"

Vector Read_Commands(FILE* commands)
{
	Vector info;
	int size_commands = SIZE_OF_COMMANDS;
	int buf = 0;
	int counter_commands = 0;

	info.vector_ptr = (int*)malloc(sizeof(int) * size_commands);

	while (fscanf(commands, "%d", &buf) != EOF)
	{
		/* If commands exists yet */
		if ((buf < 1) || (buf > 5))
		{
			printf("Fail with command %d", counter_commands + 1);
			info.lenth = -1;
			return info;
		}
		else if (counter_commands > size_commands - 1)
		{
			size_commands *= 2;
			info.vector_ptr = (int*)realloc(info.vector_ptr, size_commands);
		}
		else
		{
			((int*)info.vector_ptr)[counter_commands++] = buf;
		}
	}
	/* Check when file ends */
	if (counter_commands < 1)
	{
		printf("Too few commands");
		info.lenth = -1;
		return info;
	}
	else if (((int*)info.vector_ptr)[counter_commands - 1] != 5)
	{
		printf("Fail with last command");
		info.lenth = -1;
		return info;
	}
	else
	{
		info.lenth = counter_commands;
		return info;
	}
}

Vector Read_Files(FILE* stream1, FILE* stream2)
{
	Vector info;
	int counter = 0;
	int buf = 0;

	/* Skip headers and checks files */
	while ((buf = fgetc(stream1)) != EOF)
	{
		if (buf == '\n')
			counter++;
	}
	if (counter < 2)
	{
		printf("Error readinf input_file_1");
		info.lenth = -1;
		return info;
	}
	counter = 0;
	while ((buf = fgetc(stream2)) != EOF)
	{
		if (buf == '\n')
			counter++;
	}
	if (counter < 2)
	{
		printf("Error reading input_file_2");
		info.lenth = -1;
		return info;
	}

	/* Return to begin of files*/
	rewind(stream1);
	rewind(stream2);

	info.lenth = counter;
	info.vector_ptr = (Table*)malloc(sizeof(Table) * info.lenth);

	return info;
}