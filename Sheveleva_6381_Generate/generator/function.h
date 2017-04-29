int GenerateOption (int percent_command_1, int percent_command_2, int percent_command_3,
					int percent_command_4, FILE * commands_file);
int GenerateParagraph (FILE * input_file, int max_quantity_sentence, int first);
int GeneratePunctuation (FILE * input_file);
int GeneratePunctuationMarks (FILE * input_file, int quantity_word);
int CreateWord (FILE * input_file, int nomber_word);
int GenerateSentence (FILE * input_file, int max_quantity_word);
int GenerateWord (FILE * input_file, int max_length_word, int min_length_word);
