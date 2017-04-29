/*
 * Функция подсчета предложений в тексте.
 * Входные данные: имя считываемого файла типа (char *), имя выходного файла типа (char *).
 * Выходные данные: измененный файл расширения (.txt).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void QuantitySentence (char *name_input_file, char *name_output_file)
{
	FILE *input_file, *output_file;
	int quantity_s = 0, last_w = 0;
	char string[20], q_s[10];
	input_file = fopen (name_input_file, "r");
	output_file = fopen (name_output_file, "w");
	while (1)
	{
		fscanf(input_file, "%s", string);
		if (feof(input_file)) break;
		if ((((string[strlen(string) - 1] == '.') || (string[strlen(string) - 1] == '!') || (string[strlen(string) - 1] == '?')) && (strlen(string) > 1)) || 
			((strlen(string) > 2) && (string[strlen(string) - 2] == '?')) ||
			((strlen(string) > 3) && (string[strlen(string) - 3] == '.')))
		{	
			quantity_s++;
			last_w = 0;
		}
		if (((string[strlen(string) - 1] == '.') || (string[strlen(string) - 1] == '!') || (string[strlen(string) - 1] == '?')) && (last_w != 0))
		{
			quantity_s++;
			last_w = 0;
		}
		last_w++;
	}
	sprintf (q_s, "%d ", quantity_s);
	fputs (q_s, output_file);
	fclose (input_file);
	fclose (output_file);
}
