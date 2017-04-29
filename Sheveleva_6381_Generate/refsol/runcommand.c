/*
 * Функция выполнения команд 1, 3, 4.
 * Входные данные: названия входных, выходных файлов и файла для результата выполнения 2 команды типа (char *), 
 * 				   количество выполнений команды типа (int), указатель на функцию выполнения команды.
 * Выходные данные: количество выполнений команды типа (int).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int RunCommand (char *name_output_file_wovel, char *name_input_file, 
				char *name_output_file, int nom, void (*funk)(char *,char *))
{
	FILE *output;
	output = fopen (name_output_file_wovel, "r");
	if (output == NULL)
	{
		output = fopen (name_output_file, "r");
		if (output == NULL)
		{
			remove(name_output_file);
			(*funk)(name_input_file, name_output_file);	
			return (nom + 1);
		}
		else
		{
			fclose (output);
			return nom;
		}		
	}
	else
	{
		fclose (output);
		if (nom == 0)
		{
			remove(name_output_file);
			(*funk)(name_output_file_wovel, name_output_file);
			return (nom + 1);
		}
		if (nom == 1)
		{
			remove(name_output_file);
			(*funk)(name_output_file_wovel, name_output_file);
			return (nom + 1);
		}
		else
		{
			return (nom + 1);
		}
	}	
}
