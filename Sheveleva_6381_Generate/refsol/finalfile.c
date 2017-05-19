#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"


/*
 * записываем кол-во слов, кол-во предложений и сам файл
 */
 
 void PrintFirstString (char *file_open, FILE *output_file)
 {
	 FILE *file;
	 char str_input[10];
	 file = fopen (file_open, "r");
	 if (file != NULL) 
	{
		fscanf (file, "%s", str_input);
		fputs (str_input, output_file);
		fputc ('\n', output_file);
		fclose (file);
	}
 }
 
  void PrintText (char *file_open, FILE *output_file)
 {
	 FILE *file;
	 char str_input[10];
	 file = fopen (file_open, "r");
	 while (!feof(file))
		{
			fscanf (file, "%s", str_input);
			fputs (str_input, output_file);
			fputc (' ', output_file);
		}
	fclose (file);
 }
 
void CreatingFinalFile (int var_file, int var_command, char *file_sort, char *file_wovel, 
						char *file_word, char *file_sent, int com_2, int com_3,
						void (*funk)(char *,char *))
{
	FILE *output_file, *file;
	char name_output_file[31], str[10];
	
	sprintf(name_output_file,"%s_%dx%d%s", "../result/output_file", var_file, var_command, ".txt");	
	remove(name_output_file);
	output_file = fopen (name_output_file, "w");	
	PrintFirstString (file_word, output_file);
	PrintFirstString (file_sent, output_file);
	if (com_2 != 0)
	{
		file = fopen (file_wovel, "r");
		if (file != NULL) 
		{
			if (com_3 == 0)
			{
				fclose (file);
				PrintText (file_wovel, output_file);
			}
			else
			{
				fclose(file);
				remove(file_sort);
				(*funk)(file_wovel, file_sort);
				PrintText (file_sort, output_file);
			}
		}
	}
	else
	{
		file = fopen (file_sort, "r");
		if (file != NULL) 
		{
			fclose (file);
			PrintText (file_sort, output_file);
		}
	}
	fclose (output_file);
	remove (file_sort);
	remove (file_wovel);
	remove (file_word);
	remove (file_sent);
}
