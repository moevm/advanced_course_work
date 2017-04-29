/*
 * Функция генерирования предложения.
 * Входные данные: файл input_file типа (FILE *),
 * максимальное количество слов max_quantity_word типа (int).
 * Выходные данные: длина предложения length_sentence типа (int).
 * 
 * Вспомогательная функция создания слова.
 * Входные данные: файл input_file типа (FILE *),
 * номер слова в предложении nomber_word типа (int).
 * Выходные данные: длина слова length_word типа (int).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
 
int CreateWord (FILE * input_file, int nomber_word)
{
	int length_word;
			
	if (nomber_word == 0) {
		fputc (rand() % 25 + 65, input_file); 						//Генерация заглавной буквы.
		length_word = GenerateWord (input_file, 15, 0); 			// Генерация слова, максимальная длина - 15
		return length_word + 1;
	}
	else {
		length_word = GenerateWord (input_file, 15, 1);				// Генерация слова, максимальная длина - 15
		return length_word;
	}
}

int GenerateSentence (FILE * input_file, int max_quantity_word)
{
	int quantity_word = rand() % max_quantity_word + 1, length_sentence = 0,
		length_punctuation, length_punctuation_marks, 								
		place_second_bracket = max_quantity_word + 1,			  
		quantity_second_bracket = 0, actual_quantity_word, j;	

	for (actual_quantity_word = 0; actual_quantity_word < quantity_word; actual_quantity_word++) {
		length_sentence += CreateWord (input_file, actual_quantity_word);
		if (actual_quantity_word == (quantity_word - 1)) {
			if (actual_quantity_word == place_second_bracket) {  
				for (j = 0; j < quantity_second_bracket; j++) { 
					fputc (')', input_file);
				}
			}
			length_punctuation = GeneratePunctuation (input_file);
			length_sentence += length_punctuation;
		}
		else {
			if (actual_quantity_word == place_second_bracket) { 
				fputs (")", input_file);  	
				quantity_second_bracket--;  
				if (quantity_second_bracket != 0) {  
					place_second_bracket = rand() % (quantity_word - actual_quantity_word - 1) + (actual_quantity_word + 1);  
				}	  
			}
			length_punctuation_marks = GeneratePunctuationMarks (input_file, actual_quantity_word);
			if (length_punctuation_marks == 4) {
				if (quantity_second_bracket == 0) {
					place_second_bracket = rand() % (quantity_word - actual_quantity_word - 1) + (actual_quantity_word + 1);
				}
				quantity_second_bracket++;
			}
			length_sentence += length_punctuation_marks;
		}
	}	
	return length_sentence;
}
