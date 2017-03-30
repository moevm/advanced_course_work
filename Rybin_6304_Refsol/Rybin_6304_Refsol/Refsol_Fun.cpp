/*!
\file
\brief Refsol Functions
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"
#include "Refsol.h"

Vector Read_Commands(FILE* commands)
{
	int size_commands = Sizeof_Commands;
	int buf = 0;
	int counter_commands = 0;

	Table* vector = (Table*)malloc(sizeof(Table) * size_commands);

	while (fscanf(commands, "%d", &buf) != EOF)
	{
		/* If commands exists yet */
		if ((buf < 1) || (buf > 5))
		{
			printf("Fail with command %d", counter_commands + 1);
			return -1;
		}
		else if (counter_commands > size_commands - 1)
		{
			size_commands *= 2;
			*commands_vector = (int*)realloc(commands_vector, size_commands);
		}
		else
		{
			*(*commands_vector + counter_commands++) = buf;
		}
	}
	/* Check when file ends */
	if (counter_commands < 1)
	{
		printf("Too few commands");
		return -1;
	}
	else if (*(*commands_vector + counter_commands - 1) != 5)
	{
		printf("Fail with last command");
		return -1;
	}
	else
		return counter_commands;
}