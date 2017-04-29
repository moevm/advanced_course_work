typedef struct Index{
	int offset; // позиция в тексте
	int length;
} Index;

void Swap (Index *a, Index *b);
void QuickSortForLength (Index *arr, int first, int last);
void QuickSortForOffset (Index *arr, int first, int last);
void SortingWord (char *name_input_file, char *name_output_file);
void WovelSymble (char *name_input_file, char *name_output_file);
void QuantityWord (char *name_input_file, char *name_output_file);
void QuantitySentence (char *name_input_file, char *name_output_file);
int ReadCommand (char *name_commands, int *arr_command, int n_offset, int *error);
int RunCommand (char *name_output_file_wovel, char *name_input_file, 
				char *name_output_file, int nom, void (*funk)(char *,char *));
void CreatingFinalFile (int var_file, int var_command, char *file_sort, char *file_wovel, 
						char *file_word, char *file_sent, int com_2, int com_3,
						void (*funk)(char *,char *));
