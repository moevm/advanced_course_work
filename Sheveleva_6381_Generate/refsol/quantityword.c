/*
 * Функция подсчета слов в тексте.
 * Входные данные: имя считываемого файла типа (char *), имя выходного файла типа (char *).
 * Выходные данные: измененный файл расширения (.txt).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void QuantityWord (char *name_input_file, char *name_output_file)
{
FILE *input_file, *output_file;
	int quantity_w = 0;
	char string[20], q_w[10];
	input_file = fopen (name_input_file, "r");
	output_file = fopen (name_output_file, "w");
	while (!feof(input_file))
	{
		fscanf(input_file, "%s", string);
		if ((string[0] != '-') && (string[0] != '.') && (string[0] != ',') &&
			(string[0] != '?') && (string[0] != '!') && (string[0] != ':') && 
			(string[0] != ';') && (string[0] != ')'))
		{
			quantity_w++;
		}
		
	}
	sprintf (q_w, "%d ", quantity_w);
	fputs (q_w, output_file);
	fclose (input_file);
	fclose (output_file);
}
