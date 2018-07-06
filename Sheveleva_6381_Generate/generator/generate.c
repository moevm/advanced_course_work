/*
 * generate.c
 * Программа генерирует текст (>10000 символов) 20 раз. 
 * Для каждого текста генерируется 5 разных наборов комманд. 
 * Последний текст записывается в файл input.txt.
 * Последний набор комманд записывается в файл commands.txt
 * 
 * Seveleva Anna group 6381
 * Generate code
 * <annetalashi@mail.ru>
 * 
 * 23.03.2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "function.h"

int main (int argc, char **argv)
{
	srand (time (NULL));
	FILE * input_file,
		 * commands_file;
	int quantity_symbol, actual_quantity_symbol, quantity_options,
		i = 0, j, k, actual_quantity_options,
		use_second_command_2 = 0, length_paragraph, error;
	char  name_input_file[25],
		  name_commands[16];

	for (k = 1; k <= Q_TEST_FILE; k++) {	
		sprintf(name_input_file,"../test/%s_%d%s", "input_file", k, ".txt");
		error = remove(name_input_file);	                                    				
		input_file = fopen (name_input_file, "w");
		quantity_symbol = rand() % QUANTITY_SYMBOL + QUANTITY_SYMBOL;					
		actual_quantity_symbol = 0;
		
		while (actual_quantity_symbol < quantity_symbol)					
		{
			if (actual_quantity_symbol == 0)
			{
				length_paragraph = GenerateParagraph (input_file, MAX_QUANTITY_SENTENCE, 0);	
			}
			 
			{
				length_paragraph = GenerateParagraph (input_file, MAX_QUANTITY_SENTENCE, 1);
			}			
			actual_quantity_symbol += length_paragraph;
		}	
		fputs ("End.", input_file);
		fclose (input_file);
			
		for (j = 0; j < Q_SET_COMMANDS; j++) {	
			quantity_options = rand() % Q_TEST_COMMANDS + 1;					
			actual_quantity_options = quantity_options;	
			sprintf(name_commands,"../test/%s_%d%s", "commands", k, ".txt");							
			if (j==0) {
				error = remove(name_commands);						
			}						
			commands_file = fopen (name_commands, "a");	            
								
			while (actual_quantity_options > 0) {
				if (actual_quantity_options  == 1) {
					fputs("5\n", commands_file);
				}
				else {
					if (use_second_command_2 == 0) {
						if (GenerateOption(25, 25, 25, 25, commands_file) == 2) {
							use_second_command_2 = 1;
						}
					}
					else {
						if (j == 0) {
							GenerateOption(20, 40, 20, 20, commands_file); // Генерация ошибочной 2 команды
						}
						else {
							GenerateOption(33, 0, 33, 34, commands_file); // Генерация без 2 команды
						}
					}
				}
				actual_quantity_options--;
				i++;
			}
			i = 0;
			use_second_command_2 = 0;
			fclose (commands_file);
		}
	}
	return 0;
}
