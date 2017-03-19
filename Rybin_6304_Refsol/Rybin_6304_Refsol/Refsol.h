#include "Refsol_Data.h"

/*!
\brief Read data from tables
\param[in] stream_1 pointer to first table
\param[in] stream_2 pointer to second table
\param[in] input_head pointer to begin of list input
\return void
\ingroup Refsol_Data
*/
void Read_Data(FILE* stream_1, FILE* stream_2, input* input_head)
{	
	int buf;

	/* Skip headers of tables */
	while ((buf = fgetc(stream_1)) != '\n');
	while ((buf = fgetc(stream_2)) != '\n');

	int number = 1;
	/* First table */
	do
	{
		int i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return;
			input_head->name[i++] = buf;
		}
		input_head->name[i] = '\0';
		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return;
			input_head->surname[i++] = buf;
		}
		input_head->surname[i] = '\0';
		i = 0;
		
		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return;
			input_head->patronymic[i++] = buf;
		}
		input_head->patronymic[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return;
			input_head->GitHub_account[i++] = buf;
		}
		input_head->GitHub_account[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return;
			input_head->Email[i++] = buf;
		}
		input_head->Email[i] = '\0';

		i = 0;

		fscanf(stream_1, "%d", &input_head->group);

		while ((buf = fgetc(stream_2)) != ',');
		while ((buf = fgetc(stream_2)) != ',');

		fscanf(stream_2, "%d", &input_head->exam_result);

		input_head->line = ++number;

		push_input(input_head, create_input_element());
		input_head = input_head->next;

		while ((buf = fgetc(stream_1)) != '\n');
		while ((buf = fgetc(stream_2)) != '\n');
	} while (true);
}

void Check_max_mark(input* input_head)
{
	int count = 0;
	while (input_head->next)
	{
		if (input_head->exam_result == 5)
			count++;
	}
	printf("%d", count);
}

void Check_bad_results(input* input_head)
{
	int count = 0;
	while (input_head->next)
	{
		if (input_head->exam_result < 3)
			count++;
	}
	printf("%d", count);
}