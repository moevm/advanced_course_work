/*!
\file
\brief Refsol Functions
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Refsol_Header.h"

void TableCreate(Table* new_element)
{
	new_element->name = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->surname = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->patronymic = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->GitHub_account = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->Email = (char*)malloc(sizeof(char) * MAX_LENGTH_TOKEN);
	new_element->check = false;
	new_element->group = 0;
	new_element->exam_result = 0;
}

Vector ReadFiles(FILE* stream1, FILE* stream2)
{
	Vector info;
	info.vector_ptr = (Table*)malloc(sizeof(Table) * MAX_LINES);
	int counter = 0;
	int buf = 0 ;

	/* Skip headers in tables */
	while ((buf = fgetc(stream1) != '\n'))
	{
		if (feof(stream1))
		{
			printf("Fail with %s",INPUT1);
			exit(0);
		}
	}
	while ((buf = fgetc(stream2) != '\n'))
	{
		if (feof(stream2))
		{
			printf("Fail with %s",INPUT2);
			exit(0);
		}
	}

	while (true)
	{
		int i = 0;
		TableCreate(&info.vector_ptr[counter]);

		while ((buf = fgetc(stream1) != ','))
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
		
		while ((buf = fgetc(stream1) != ','))
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

		while ((buf = fgetc(stream1) != ','))
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

		while ((buf = fgetc(stream1) != ','))
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

		while ((buf = fgetc(stream1) != ','))
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
		while ((buf = fgetc(stream2) != ','))
		{
			if (feof(stream2))
			{
				info.lenth = counter;
				return info;
			}
		}
		while ((buf = fgetc(stream2) != ','))
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

		while ((buf = fgetc(stream1) != '\n'))
		{
			if (feof(stream1))
			{
				info.lenth = counter;
				return info;
			}
		}
		while ((buf = fgetc(stream2) != '\n'))
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