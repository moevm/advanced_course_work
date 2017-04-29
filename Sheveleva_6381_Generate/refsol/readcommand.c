#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int ReadCommand (char *name_commands, int *arr_command, int n_offset, int *error)
{
	FILE *commands;
	int i = 0, com_2 = 0;
	char number;
	commands = fopen (name_commands, "r");	
	fseek (commands, n_offset, SEEK_SET);	
	while(1)
	{	
		number = fgetc(commands);
		if ((number - '0') == 2)
		{
			com_2++;
		}
		printf("%c ",number);
		arr_command[i] = number - '0';
		number = fgetc(commands);
		n_offset += 2;
		if ((feof(commands))||(number == '\n')) break;
		i++;
	}
	printf("\n");
	if (com_2 > 1)
	{
		printf ("ERROR\n");
		*error = 1;
	}
	fclose(commands);
	return n_offset;
}
