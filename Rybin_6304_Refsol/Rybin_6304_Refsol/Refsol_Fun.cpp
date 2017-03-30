/*!
\file
\brief Refsol Functions
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Refsol.h"

Vector Read_Commands(FILE* commands)
{
	Vector info;
	int size_commands = Sizeof_Commands;
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

}