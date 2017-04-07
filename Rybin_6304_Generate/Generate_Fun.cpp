/*!
\file
\brief Generate Functions

\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"

void PutRandomCommands(FILE* commands_list)
{
	int lenth = rand() % MAX_LENTH_ARRAY_COMMANDS;

	for (int i = 0; i < lenth; i++)
		fprintf(commands_list, "%d ", -1 + rand() % 7);

	fprintf(commands_list, "\n");
}

char* GenerateToken(int a)
{
	int lenth = MIN_LENTH_TOKEN + rand() % (MAX_LENTH_TOKEN - MIN_LENTH_TOKEN);
	char* random_token = (char*)malloc(sizeof(char) * (lenth + 9));

	for (int i = 0; i < lenth - 1; i++)
	{
		random_token[i] = (char)(97 + rand() % 25);
	}
	random_token[lenth - 1] = '\0';

	switch (a)
	{
	case 1:
		strncat(random_token, "@Email", 6);
		random_token[lenth + 8] = '\0';
		break;
	case 2:
		strncat(random_token, "@GitHub", 7);
		random_token[lenth + 8] = '\0';
		break;
	default: break;
	}
	return random_token;
}

Vector GenerateRandomVector(int max, int min)
{
	int lenth = min + rand() % (max - min);
	Table* vector = (Table*)malloc(sizeof(Table) * lenth);

	for (int i = 0; i < lenth; i++)
	{
		vector[i].Email = GenerateToken(1);
		vector[i].GitHub_account = GenerateToken(2);
		vector[i].name = GenerateToken(0);
		vector[i].surname = GenerateToken(0);
		vector[i].patronymic = GenerateToken(0);
		vector[i].group = 1 + rand() % MAX_GROUP;
		vector[i].exam_result = 1 + rand() % MAX_EXAM_RESULT;
		vector[i].check = true;
	}

	Vector info;
	info.lenth = lenth;
	info.vector_ptr = vector;

	return info;
}
