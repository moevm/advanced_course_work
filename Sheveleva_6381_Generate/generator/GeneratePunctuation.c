/*
 * Функция генерирования окончания предложения.
 * Входные данные: файл input_file типа (FILE *).
 * Выходные данные: количество напечатанных элементов типа (int).
 * 
 * C учетом частоты употребления, generate_punctuation обозначает:
 * 1-62   -- '.'
 * 63-79  -- '!'
 * 80-96  -- '?'
 * 97-98  -- '?!'
 * 99-100 -- '...' 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
 
int GeneratePunctuation (FILE * input_file)
{
	int generate_punctuation = rand() % PERSENT + 1;

	if (generate_punctuation < 63) {
			fputs (". ", input_file);
			return 2;
		}
	if ((generate_punctuation > 62) && (generate_punctuation < 80)) {
			fputs ("! ", input_file);
			return 2;
		}		
	if ((generate_punctuation >79) && (generate_punctuation < 97)) {
			fputs ("? ", input_file);
			return 2;
		}		
	if ((generate_punctuation > 96) && (generate_punctuation < 99)) {
			fputs ("?! ", input_file);
			return 3;
		}
	if (generate_punctuation > 98) {
			fputs ("... ", input_file);
			return 4;
		}				
}
