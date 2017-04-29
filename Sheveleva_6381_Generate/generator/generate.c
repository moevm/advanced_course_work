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
		* commands,	i = 0, j, k, actual_quantity_options,
		use_second_command_2 = 0, length_paragraph, error;
	char  *name_input_file = (char*)malloc(sizeof(char)*16),
		  *name_commands;

	for (k = 1; k <= 20; k++) {	
		sprintf(name_input_file,"%s_%d%s", "input_file", k, ".txt");
		error = remove(name_input_file);	                                    		// Удаляем файл input_file, если он был уже создан		
		input_file = fopen (name_input_file, "w");
		quantity_symbol = rand() % 10000 + 10000;										// Генерация количества символов в пределах 10000-20000
		actual_quantity_symbol = 0;
		
		while (actual_quantity_symbol < quantity_symbol)								// Генерация input файла
		{
			if (actual_quantity_symbol == 0)
			{
				length_paragraph = GenerateParagraph (input_file, 20, 0);	
			}
			else
			{
				length_paragraph = GenerateParagraph (input_file, 20, 1);
			}					// Генерация параграфа, максимальное количество предложений - 20
			actual_quantity_symbol += length_paragraph;
		}
		fclose (input_file);
		
		sprintf(name_input_file,"%s_%d%s", "input_file", k, ".txt");		
		for (j = 0; j < 5; j++) {	
			quantity_options = rand() % 12 + 1;											//Количество команд
			commands = (int *) malloc (sizeof (int) * quantity_options);
			actual_quantity_options = quantity_options;	
			name_commands = (char*)malloc(sizeof(char) * quantity_options);
			sprintf(name_commands,"%s_%d%s", "commands", k, ".txt");							
			if (j==0) {
				error = remove(name_commands);											// Удаляем файл commands, если он был уже создан	
			}						
			commands_file = fopen (name_commands, "a");	            
								
			while (actual_quantity_options > 0) {
				if (actual_quantity_options  == 1) {
					fputs("5\n", commands_file);
					commands[i] = 5;
				}
				else {
					if (use_second_command_2 == 0) {
						commands[i] = GenerateOption(25, 25, 25, 25, commands_file);
						if (commands[i] == 2) {
							use_second_command_2 = 1;
						}
					}
					else {
						if (j == 0) {
							commands[i] = GenerateOption(20, 40, 20, 20, commands_file); // Генерация ошибочной 2 команды
						}
						else {
							commands[i] = GenerateOption(33, 0, 33, 34, commands_file); // Генерация без 2 команды
						}
					}
				}
				actual_quantity_options--;
				i++;
			}
			i = 0;
			use_second_command_2 = 0;
			free (commands);
			free (name_commands);
			fclose (commands_file);
		}
	}
	return 0;
}
