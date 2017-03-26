/*
 * Функция генерирования абзаца.
 * Входные данные: файл input_file типа (FILE *),
 * максимальное количество предложений в абзаце max_quantity_sentence типа (int).
 * Выходные данные: длина абзаца length_paragraph типа (int).
 */
int GenerateParagraph (FILE * input_file,
					   int max_quantity_sentence)
{
	int length_paragraph = 0,
		quantity_sentence = rand() % max_quantity_sentence + 1,
		i;
	for (i=0; i<quantity_sentence; i++) {
		if (i == 0) {
		fputc(9,input_file); 									// Отступ для первого предложения.	
		}
		length_paragraph += GenerateSentence(input_file, 15);	// Генерация предложений, максимальное количество слов - 15
	}
	fputc('\n', input_file);
	return length_paragraph;
}
