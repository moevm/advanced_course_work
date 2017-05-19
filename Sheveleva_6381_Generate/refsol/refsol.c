/*
 * refsol.c
 * Для каждого файла программа считывает список комманд и выполняет их.
 * 
 * Seveleva Anna group 6381
 * Refsol code
 * <annetalashi@mail.ru>
 * 
 * 01.05.2017
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"


main()
{	
	FILE *output_file;
	int var_file, var_command, i, n_offset = 0, com_2 = 0, com_3 = 0,
		nom1 = 0, nom3 = 0, nom4 = 0,
		arr_command[16], error = 0;
	char name_input_file[25],
		 name_commands[19],
		 name_output_file[31],
		 name_output_file_sort[] = "output_file_sort.txt",
		 name_output_file_wovel[] = "output_file_wovel.txt",
		 name_output_file_word[] = "output_file_word.txt",
		 name_output_file_sent[] = "output_file_sent.txt";
		 
	for (var_file = 1; var_file <= 20; var_file++)
	{
		sprintf(name_input_file,"%s_%d%s", "../test/input_file", var_file, ".txt");	
		sprintf(name_commands,"%s_%d%s", "../test/commands", var_file, ".txt");	
		for (var_command = 1; var_command <= 5; var_command++)
		{		
			n_offset = ReadCommand (name_commands, arr_command, n_offset, & error);
			if (error == 1)
			{
				error = 0;
				sprintf(name_output_file,"%s_%dx%d%s", "../result/output_file", var_file, var_command, ".txt");	
				output_file = fopen (name_output_file, "w");
				fputs("ERROR", output_file);
				fclose(output_file);
				continue;
			}
			i = 0;
		
		
			remove(name_output_file_sort);
			remove(name_output_file_wovel);
			remove(name_output_file_word);
			remove(name_output_file_sent);
			while (1)
			{
				if(arr_command[i] == 3)
				{	
						nom3 = RunCommand (name_output_file_wovel, name_input_file, name_output_file_sort, nom3, SortingWord);
						if (com_2 != 0) 
						{
							com_2 = 0;
						}
						com_3++;
				}	
				if (arr_command[i] == 2)
				{	
					WovelSymble (name_input_file, name_output_file_wovel);
					com_2++;
				}
				if (arr_command[i] == 1)
				{
					nom1 = RunCommand (name_output_file_wovel, name_input_file, name_output_file_word, nom1, QuantityWord);
				}
				if (arr_command[i] == 4)
				{
					nom4 = RunCommand (name_output_file_wovel, name_input_file, name_output_file_sent, nom4, QuantitySentence);
				}
				if (arr_command[i] == 5)
				{
					CreatingFinalFile (var_file, var_command, name_output_file_sort, name_output_file_wovel, name_output_file_word, name_output_file_sent, com_2, com_3, SortingWord);
					com_2 = 0; com_3 = 0;
					break;
				}
				i++;
			}	
			nom1 = 0; nom3 = 0; nom4 = 0;
		}	
		n_offset = 0;	
	}
}
