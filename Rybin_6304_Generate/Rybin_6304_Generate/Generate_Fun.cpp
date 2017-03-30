/*!
\file
\brief Generate Functions
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0

*/

#include "Generator.h"

void put_random_commands(FILE* commands_list)
{
	int lenth = rand() % Max_Lenth_array_commands;

	for (int i = 0; i < lenth; i++)
		fprintf(commands_list, "%d ", -1 + rand() % 7);
}

char* generate_token(int a)
{
	int lenth = Min_Lenth_token + rand() % Max_Lenth_token;
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

void constructor_element(Table element)
{
	element.Email = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element.GitHub_account = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element.name = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element.surname = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element.patronymic = (char*)malloc(sizeof(char) * Max_Lenth_field);
	element.group = 0;
	element.exam_result = 0;
	element.check = false;

}

Vector generate_random_vector(int max, int min)
{
	int lenth = min + rand() % (max - min);
	Table* vector = (Table*)malloc(sizeof(Table) * lenth);

	for (int i = 0; i < lenth; i++)
	{
		vector[i].Email = generate_token(1);
		vector[i].GitHub_account = generate_token(2);
		vector[i].name = generate_token(0);
		vector[i].surname = generate_token(0);
		vector[i].patronymic = generate_token(0);
		vector[i].group = 1 + rand() % Max_Group;
		vector[i].exam_result = 1 + rand() % Max_Exam_result;
		vector[i].check = false;
	}

	Vector info;
	info.lenth = lenth;
	info.random_vector = vector;

	return info;
}