/*
 * Функция сортировки слов в порядке убывания длины.
 * Входные данные: имя считываемого файла типа (char *), имя выходного файла типа (char *).
 * Выходные данные: измененный файл расширения (.txt).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

 int cmp(const void *a, const void *b) {
     return ((Index*)b)->length - ((Index*)a)->length;
 }

void SortingWord (char *name_input_file, char *name_output_file)
{
	FILE *input_file, *output_file, *intermediate_file;
	int memory_index = BUFFER_MEMORY, curr_word = 0, i,
		curr_offset = 0;
	char symble[BUFFER_WORD], *last_word = "", last_s = 0, *string, 
		 punctuation[] = {'!', '.', '?', ',', ':', ';', '(', ')'};
	Index *massive_word = (Index*) malloc (sizeof(Index) * BUFFER_MEMORY);
	
	input_file = fopen (name_input_file, "r");
	intermediate_file = fopen ("intermediate_file.txt", "w");
	while (1)
	{
		fscanf (input_file, "%s", symble);
		if (feof(input_file)) break;
		
		string = strtok (symble, punctuation);
		if((string != NULL)&&(string[0]!='-')) 
		{
			if (curr_word != 0) 
			{
				fputc (' ', intermediate_file); 
			}
			fputs (string, intermediate_file);
			if (strchr (string, 45) != NULL) 
			{
				massive_word[curr_word].length = strlen(string)-1;
			}
			else
			{
				massive_word[curr_word].length = strlen(string);
			}
			massive_word[curr_word].offset = curr_offset;
			curr_offset += strlen(string) + 1;
			if (++curr_word >= memory_index) 
			{
				memory_index += BUFFER_MEMORY;
				massive_word = (Index*) realloc (massive_word, sizeof(Index) * memory_index);        
			}
		}
	}
	fclose (input_file);
	fclose (intermediate_file);
	qsort(massive_word, curr_word, sizeof(Index), cmp);
	
	last_s = ' ', i = 0; 
	remove (name_output_file);
	intermediate_file = fopen ("intermediate_file.txt", "r");
	output_file = fopen (name_output_file, "w");
	while (i < curr_word) // запись отсортированных слов
	{
		if (i != 0) fputc (' ', output_file);
		fseek (intermediate_file, massive_word[i].offset, SEEK_SET);
		fgets (symble, massive_word[i].length + 1, intermediate_file);
		if (strchr (symble, 45) != NULL) 
		{
			fputs (symble, output_file);
			symble[0] = fgetc (intermediate_file);
			fputc (symble[0], output_file);
		}
		else
		{
			fputs (symble, output_file);
	}		
		i++;
	}
	free(massive_word);
	fclose (output_file);
	fclose (intermediate_file);
	remove ("intermediate_file.txt");
}
