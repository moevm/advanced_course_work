/*
 * generate.c
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
#include "GeneratePunctuation.h"
#include "GeneratePunctuationMarks.h"
#include "GenerateWord.h"
#include "GenerateSentence.h"
#include "GenerateParagraph.h"
#include "GenerateOption.h"

int main (int argc, char **argv)
{
	srand (time (NULL));
	FILE * input_file,
		 * commands;
	int quantity_symbol = rand() % 10000 + 10000,
		actual_quantity_symbol = 0,
		quantity_options = rand() % 12 + 1,
		actual_quantity_options = quantity_options,
		options = 0,
		use_second_command_2 = 0,
		length_paragraph;
	input_file = fopen ("input_file.txt", "w");
	commands = fopen ("commands.txt", "w");
	while (actual_quantity_symbol < quantity_symbol)
	{
		length_paragraph = GenerateParagraph (input_file, 20);
		actual_quantity_symbol += length_paragraph;
	}
	while (actual_quantity_options > 0) {
		if (actual_quantity_options  == 1) {
			fputs("5", commands);
		}
		else {
			if ((use_second_command_2 == 0) && (GenerateOption(25, 25, 25, 25, commands) == 2)) {
					use_second_command_2 = 1;
			}
			else {
				options = GenerateOption(32, 4, 32, 32, commands);
			}
		}
		actual_quantity_options--;
	}
	return 0;
}
