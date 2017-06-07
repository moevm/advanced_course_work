#define BUFFER_WORD 25
#define BUFFER_NUMBER 10
#define MAX_QUANT_FILE 20
#define MAX_QUANT_COMMAND 5
#define BUFFER_NAME 31
#define BUFFER_MEMORY 100
#define BUFFER_ARR_COMMAND 16

typedef struct Index{
	int offset; // позиция в тексте
	int length;
} Index;

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
