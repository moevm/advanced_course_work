/*
 * Функция генерирования знаков препинания внутри предложения.
 * Входные данные: файл input_file типа (FILE *) и 
 * количество слов в предложении quantity_word типа (int).
 * Выходные данные: количество напечатанных элементов типа (int).
 * 
 * C учетом частоты употребления, generate_punctuation_marks обозначает:
 * 1-59  -- ' '
 * 60-84 -- ','
 * 85-92 -- '-'
 * 93-96 -- ';'
 * 97-99 -- ':' 
 * 100   -- '('
 */
int GeneratePunctuationMarks (FILE * input_file, 
							  int quantity_word)
{
	int generate_punctuation_marks;
	
	if (quantity_word > 1) {
		generate_punctuation_marks = rand() % 100 + 1;
		if (generate_punctuation_marks < 60) {
			fputc (' ', input_file);
			return 1;
		}
		if ((generate_punctuation_marks > 59) && (generate_punctuation_marks < 85)) {
			fputs (", ", input_file);
			return 2;
		}
		if ((generate_punctuation_marks > 84) && (generate_punctuation_marks < 93)) {
			fputs (" - ", input_file);
			return 3;
		}
		if ((generate_punctuation_marks > 92) && (generate_punctuation_marks < 97)) {
			fputs ("; ", input_file);
			return 2;
		}
		if ((generate_punctuation_marks > 96) && (generate_punctuation_marks < 100)) {
			fputs (": ", input_file);
			return 2;
		}
		if (generate_punctuation_marks == 100) {
			fputs (" (", input_file);
			return 4;
		}	
	}
	else {
		fputc (' ', input_file);
		return 1;
	}
}
