/*
 * generate.c
 * 
 * Seveleva Anna group 6381
 * Generate code
 * <annetalashi@mail.ru>
 * 
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
	FILE * input_file;
	int quantity_symbol = rand() % 10000 + 10000,
		actual_quantity_symbol = 0,
		quantity_options = rand() % 12 + 1,
		actual_quantity_options = quantity_options,
		* options = (int *) malloc (sizeof (int) * quantity_options),
		use_second_command_2 = 0,
		length_paragraph;
	input_file = fopen ("input_file.txt", "w");
	while (actual_quantity_symbol < quantity_symbol)
	{
		length_paragraph = GenerateParagraph (input_file, 20);
		actual_quantity_symbol += length_paragraph;
	}
	while (actual_quantity_options > 0) {
		if (actual_quantity_options  == 1) {
			options[quantity_options - 1] = 5;
		}
		else {
			if (use_second_command_2 == 0) {
				options[quantity_options - actual_quantity_options] = GenerateOption(25, 25, 25, 25);
				if (options[quantity_options - actual_quantity_options] == 2) {
					use_second_command_2 = 1;
				}
			}
			else {
				options[quantity_options - actual_quantity_options] = GenerateOption(32, 4, 32, 32);
			}
		}
		//printf ("%d ", options[quantity_options - actual_quantity_options]);
		actual_quantity_options--;
	}
	return 0;
}
