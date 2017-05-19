/*
 * Функция удаления слов при условии, если гласных букв больше согласных.
 * Входные данные: имя считываемого файла типа (char *), имя выходного файла типа (char *).
 * Выходные данные: измененный файл расширения (.txt).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void WovelSymble (char *name_input_file, char *name_output_file)
{
	FILE *input_file, *output_file;
	int length_word = 0, q_wovel = 0, offset_w = 0;
	char symble;
	
	input_file = fopen (name_input_file, "r");
	output_file = fopen (name_output_file, "w");
	while ((symble = fgetc(input_file)) != EOF)
	{	
	    if (symble == ' ')
	    {
			if ((symble = fgetc(input_file)) == EOF) break;
			fputc(' ', output_file);
		}		
		fputc(symble, output_file);
		if ((symble == '	') || (symble == '.') || (symble == ',') || 
			(symble == ';') || (symble == ':') || (symble == '(') || 
			(symble == ')') || (symble == ' ') || (symble == '?') || 
			(symble == '!') || (symble == 10))
		{	
			offset_w++;		
			if ((length_word != 0) && (q_wovel > (length_word - q_wovel)))
			{
				fseek (output_file, offset_w + 1, SEEK_SET);				
				fputc(symble, output_file);
			}
			else
			{
				offset_w += length_word;
			}
			q_wovel = 0;
			length_word = 0;
		}
		else 
		{
			if ((symble == 'a') || (symble == 'e') || (symble == 'i') || 
				(symble == 'o') || (symble == 'u') || (symble == 'y') || 
				(symble == 'A') || (symble == 'E') || (symble == 'I') || 
				(symble == 'O') || (symble == 'U') || (symble == 'Y'))
			{
				q_wovel++;
			}
			if (symble != '-')
			{
				length_word++;
			}
		}
	}
	fclose (input_file);
	fclose (output_file);
}
