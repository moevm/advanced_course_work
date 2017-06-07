/* 
 * Функция генерирования слов.
 * Входные данные: файл input_file типа (FILE *),
 * максимальная длина слова max_length_word типа (int),
 * минимальная длина слова min_length_word типа (int).
 * Выходные данные: длина слова length_word типа (int).
 * 
 * С учетом употребления знака '-' в предложениях hyphen обозначает:
 * 1-80   нет дефиса 
 * 81-100 есть дефис
 * 
 * Длина наименьшего слова с девисом равна 4.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
 
int GenerateWord (FILE * input_file, int max_length_word, int min_length_word)
{
	int length_word = rand() % max_length_word + min_length_word,
		hyphen = rand() % PERSENT + 1,
		locatoin_hyphen = max_length_word + 1, i;
	if (hyphen>80) {
		if (length_word > 3) {
			locatoin_hyphen = rand() % (length_word - 3) + 1;
		}
	}
	for (i = 0; i < length_word; i++) {
		if (i == locatoin_hyphen) {
			fputc ('-', input_file);
			length_word++;
			i++;
		}
		fputc (rand() % ALPHABET + 97, input_file);
	}	
	return length_word;
}
