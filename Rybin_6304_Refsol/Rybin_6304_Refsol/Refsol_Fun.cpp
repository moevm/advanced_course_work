/*!
\file
\brief Refsol Functions
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Refsol_Header.h"

int CompareTable(const Table* a, const Table* b)
{
	return (a->group - b->group);
}

void TableCreate(Table* new_element)
{
	new_element->name = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->surname = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->patronymic = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->GitHub_account = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->Email = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->group = 0;
	new_element->exam_result = 0;
	new_element->flag = 0;
}

Vector ReadFiles(FILE* stream1, FILE* stream2)
{
	Vector info;
	info.vector_ptr = (Table*)malloc(sizeof(Table) * MAX_LINES);
	int counter = 0;
	char buf = 0 ;

	/* Skip headers in tables */
	while (fscanf(stream1,"%c",&buf) && (buf != '\n'))
	{
		if (feof(stream1))
		{
			printf("Fail with %s",INPUT1);
			exit(1);
		}
	}
	while (fscanf(stream2, "%c", &buf) && (buf != '\n'))
	{
		if (feof(stream2))
		{
			printf("Fail with %s",INPUT2);
			exit(1);
		}
	}

	while (true)
	{
		int i = 0;
		TableCreate(&info.vector_ptr[counter]);

		while (fscanf(stream1, "%c", &buf) && (buf != ','))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
			info.vector_ptr[counter].name[i++] = buf;
		}
		info.vector_ptr[counter].name[i] = '\0';
		i = 0;
		
		while (fscanf(stream1, "%c", &buf) && (buf != ','))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
			info.vector_ptr[counter].surname[i++] = buf;
		}
		info.vector_ptr[counter].surname[i] = '\0';
		i = 0;

		while (fscanf(stream1, "%c", &buf) && (buf != ','))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
			info.vector_ptr[counter].patronymic[i++] = buf;
		}
		info.vector_ptr[counter].patronymic[i] = '\0';
		i = 0;

		while (fscanf(stream1, "%c", &buf) && (buf != ','))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
			info.vector_ptr[counter].GitHub_account[i++] = buf;
		}
		info.vector_ptr[counter].GitHub_account[i] = '\0';
		i = 0;

		while (fscanf(stream1, "%c", &buf) && (buf != ','))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
			info.vector_ptr[counter].Email[i++] = buf;
		}
		info.vector_ptr[counter].Email[i] = '\0';
		i = 0;

		fscanf(stream1, "%d", &info.vector_ptr[counter].group);
		if (feof(stream1))
		{
			info.lenth = counter;
			return info;
		}
		/* Skip same fields "Name,Surname" in second table */
		while (fscanf(stream2, "%c", &buf) && (buf != ','))
		{
			if (feof(stream2))
			{
				info.lenth = counter;
				return info;
			}
		}
		while (fscanf(stream2, "%c", &buf) && (buf != ','))
		{
			if (feof(stream2))
			{
				info.lenth = counter;
				return info;
			}
		}
		
		fscanf(stream2, "%d", &info.vector_ptr[counter].exam_result);
		if (feof(stream1))
		{
			info.lenth = counter;
			return info;
		}

		while (fscanf(stream1, "%c", &buf) && (buf != '\n'))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
		}
		while (fscanf(stream2, "%c", &buf) && (buf != '\n'))
		{
			if (feof(stream2))
			{
				info.lenth = counter;
				return info;
			}
		}
		counter++;
	}
}

void CheckBadResults(Vector data)
{
	int count = 0;
	for (int i = 0; i < data.lenth; i++)
	{
		if ((data.vector_ptr[i].exam_result <= (int)(0.6 * MAX_EXAM_RESULT))&&(data.vector_ptr[i].flag != 1))
			count++;
	}
	printf("Students with mark less then 60 percents: %d\n", count);
}

void CheckGoodResults(Vector data)
{
	int count = 0;
	for (int i = 0; i < data.lenth; i++)
	{
		if ((data.vector_ptr[i].exam_result == MAX_EXAM_RESULT)&&(data.vector_ptr[i].flag != 1))
			count++;
	}
	printf("Students with max mark: %d\n", count);
}

void CheckRepeats(Vector data)
{
	for (int i = 0; i < data.lenth - 1; i++)
	{
		if ((strcmp(data.vector_ptr[i].name, data.vector_ptr[i + 1].name) == 0) &&
			(strcmp(data.vector_ptr[i].surname, data.vector_ptr[i + 1].surname) == 0) &&
			(strcmp(data.vector_ptr[i].patronymic, data.vector_ptr[i + 1].patronymic) == 0) &&
			(strcmp(data.vector_ptr[i].Email, data.vector_ptr[i + 1].Email) == 0) &&
			(strcmp(data.vector_ptr[i].GitHub_account, data.vector_ptr[i + 1].GitHub_account) == 0) &&
			(data.vector_ptr[i].group == data.vector_ptr[i + 1].group) &&
			(data.vector_ptr[i].exam_result == data.vector_ptr[i + 1].exam_result))
			data.vector_ptr[i + 1].flag = 1;
	}
}

void CheckByGroup(Vector data)
{
	for (int i = 0; i < data.lenth; i++)
	{
		if (data.vector_ptr[i].group != data.vector_ptr[i + 1].group)
		{
			if (data.vector_ptr[i].flag == 1) // If repeats flag saves
				continue;
			data.vector_ptr[i].flag = -1;
		}
		else if (data.vector_ptr[i + 1].flag == 1)	//If next is repeat then current student is last
			data.vector_ptr[i].flag = -1;
	}
}

void SaveResults(Vector data)
{
	FILE* result = fopen(RESULT, "w");
	fprintf(result, RESULT_HEADER);

	for (int i = 0; i < data.lenth; i++)
	{
		if (data.vector_ptr[i].flag == 1)
			continue;

		fprintf(result, "%d,%s,%s,%s,%s,%s,%d\n",
			data.vector_ptr[i].group,
			data.vector_ptr[i].name,
			data.vector_ptr[i].surname,
			data.vector_ptr[i].patronymic,
			data.vector_ptr[i].GitHub_account,
			data.vector_ptr[i].Email,
			data.vector_ptr[i].exam_result);

		if (data.vector_ptr[i].flag == -1)
			fprintf(result, "\n\n");
	}

	fclose(result);
}