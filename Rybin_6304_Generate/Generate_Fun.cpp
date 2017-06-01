/*!
\file
\brief Generate Functions

\author Rybin Aleksandr 1 course 2 half
\date 21.05.2017
\version 3.0
*/

#include "Generate_Header.h"

void PutRandomCommands(FILE* commands_list)
{
	int len = rand() % MAX_LENGTH_ARRAY_COMMANDS;

	for (int i = 0; i < len; i++)
		fprintf(commands_list, "%d ", -1 + rand() % 8);

	fprintf(commands_list, "\n");
}

void  GenerateToken(char* random_token)
{
	int len = MIN_LENGTH_TOKEN + rand() % (MAX_LENGTH_TOKEN - MIN_LENGTH_TOKEN);

 	for (int i = 0; i < len ; i++)
	 	random_token[i] = (char)(97 + rand() % 25);
	random_token[len] = '\0';
}

Vector GenerateRandomVector()
{
    Vector info;
	info.len = MIN_LINES + rand() % (MAX_LINES - MIN_LINES);

	for (int i = 0; i < info.len; i++)
	{
		GenerateToken(info.vector_ptr[i].Email);
		GenerateToken(info.vector_ptr[i].GitHub_account);
		GenerateToken(info.vector_ptr[i].name);
		GenerateToken(info.vector_ptr[i].surname);
		GenerateToken(info.vector_ptr[i].patronymic);
		info.vector_ptr[i].group = 1 + rand() % MAX_GROUP;
		info.vector_ptr[i].exam_result = 1 + rand() % MAX_EXAM_RESULT;
		info.vector_ptr[i].flag = 0;
    }
	return info;
}
