/*
 * Функция генерирования абзаца.
 * Входные данные: файл input_file типа (FILE *),
 * максимальное количество предложений в абзаце max_quantity_sentence типа (int),
 * номер вхождения типа (int) для перехода на новую строку.
 * Выходные данные: длина абзаца length_paragraph типа (int).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
 
int GenerateParagraph (FILE * input_file, int max_quantity_sentence, int first)
{
	int length_paragraph = 0, i,
		quantity_sentence = rand() % max_quantity_sentence + 1;
	if (first != 0) 
	{
		fputc('\n', input_file);
	}
	for (i=0; i<quantity_sentence; i++) {
		if (i == 0) {
		fputc(9,input_file); 									// Отступ для первого предложения.	
		}
		length_paragraph += GenerateSentence(input_file, 15);	// Генерация предложений, максимальное количество слов - 15
	}	
	return length_paragraph;
}
