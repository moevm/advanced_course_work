#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"


/*
 * записываем кол-во слов, кол-во предложений и сам файл
 */
void CreatingFinalFile (int var_file, int var_command, char *file_sort, char *file_wovel, 
						char *file_word, char *file_sent, int com_2, int com_3,
						void (*funk)(char *,char *))
{
	FILE *output_file, *file;
	char name_output_file[21], str[10];
	
	sprintf(name_output_file,"%s_%dx%d%s", "output_file", var_file, var_command, ".txt");	
	remove(name_output_file);
	output_file = fopen (name_output_file, "w");	
	file = fopen (file_word, "r");
	if (file != NULL) 
	{
		fscanf(file, "%s", str);
		fputs(str, output_file);
		fputc('\n', output_file);
		fclose(file);
	}
	file = fopen (file_sent, "r");
	if (file != NULL) 
	{
		fscanf(file, "%s", str);
		fputs(str, output_file);
		fputc('\n', output_file);
		fclose(file);
	}
	if (com_2 != 0)
	{
		file = fopen (file_wovel, "r");
		if (file != NULL) 
		{
			if (com_3 == 0)
			{
				while (!feof(file))
				{
					fscanf(file, "%s", str);
					fputs(str, output_file);
					fputc(' ', output_file);
				}
				fclose(file);
			}
			else
			{
				fclose(file);
				remove(file_sort);
				(*funk)(file_wovel, file_sort);	
				file = fopen (file_sort, "r");
				while (!feof(file))
				{
					fscanf(file, "%s", str);
					fputs(str, output_file);
					fputc(' ', output_file);
				}
				fclose(file);
			}
		}
	}
	else
	{
		file = fopen (file_sort, "r");
		if (file != NULL) 
		{
			while (!feof(file))
			{
				fscanf(file, "%s", str);
				fputs(str, output_file);
				fputc(' ', output_file);
			}
			fclose(file);
		}
	}
	fclose(output_file);
	remove(file_sort);
	remove(file_wovel);
	remove(file_word);
	remove(file_sent);
}
