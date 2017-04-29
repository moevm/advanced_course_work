/*
 * Функция сортировки слов в порядке убывания длины.
 * Входные данные: имя считываемого файла типа (char *), имя выходного файла типа (char *).
 * Выходные данные: измененный файл расширения (.txt).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void SortingWord (char *name_input_file, char *name_output_file)
{
	FILE *input_file, *output_file, *intermediate_file;
	int memory_index = 100, plas_m_i = 100, curr_word = 0, i,
		curr_offset = 0, begin_s = 0, end_s = 0, cur_s = 15;
	char symble[30], *last_word = "", last_s = 0, *string, 
		 punctuation[] = {'!', '.', '?', ',', ':', ';', '(', ')'};
	Index *massive_word = (Index*) malloc (sizeof(Index) * 100);
	
	input_file = fopen(name_input_file, "r");
	intermediate_file = fopen("intermediate_file.txt", "w");
	while(1)
	{
		fscanf(input_file, "%s", symble); //считываем слово
		if (feof(input_file)) break;
		string = strtok (symble, punctuation);
		if(string != NULL) 
		{
			if (curr_word != 0) 
			{
				fputc(' ', intermediate_file); 
			}
			fputs(string, intermediate_file);
			massive_word[curr_word].length = strlen(string);
			massive_word[curr_word].offset = curr_offset;
			curr_offset += strlen(string) + 1;
			if (strchr(string, 45) != NULL) 
			{
				massive_word[curr_word].length--;
			}
			if (++curr_word >= memory_index)  //добавление памяти
			{
				memory_index += plas_m_i;
				massive_word = (Index*) realloc (massive_word, sizeof(Index) * memory_index);        
			}
		}
	}
	fclose(input_file);
	fclose(intermediate_file);

	QuickSortForLength(massive_word, 0, curr_word);//сортировка	
	for (i = 0; i < curr_word; i++)
	{
		if (massive_word[i].length != cur_s)
		{
			QuickSortForOffset(massive_word, begin_s, (end_s - 1));//сортировка offsеt
			begin_s = end_s;
			cur_s = massive_word[i].length;
		}
		end_s++;
	}
	QuickSortForOffset(massive_word, begin_s, (end_s - 1));
	
	last_s = ' ', i = 0; 
	remove(name_output_file);
	intermediate_file = fopen("intermediate_file.txt", "r");
	output_file = fopen(name_output_file, "w");
	while (i < curr_word) // запись отсортированных слов
	{
		fseek (intermediate_file, massive_word[i].offset, SEEK_SET);
		fgets (symble, massive_word[i].length+1, intermediate_file);
		fputs (symble, output_file);
		fputc (' ', output_file);
		i++;
	}
	fclose(output_file);
	fclose(intermediate_file);
	remove("intermediate_file.txt");
}

