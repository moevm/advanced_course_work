#include "Data.h"

/*!
\brief Read data from tables
\param[in] stream_1 pointer to first table
\param[in] stream_2 pointer to second table
\param[in] input_head pointer to begin of list Table
\return void
\ingroup Refsol
*/
void Read_Data(FILE* stream_1, FILE* stream_2, Table* input_head)
{	
	int buf;

	/* Skip headers of tables */
	while ((buf = fgetc(stream_1)) != '\n');
	while ((buf = fgetc(stream_2)) != '\n');

	/* Number of line in table */
	int number = 1;

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

		/* Skip to fields in second table */
		while ((buf = fgetc(stream_2)) != ',');
		while ((buf = fgetc(stream_2)) != ',');

		fscanf(stream_2, "%d", &input_head->exam_result);

		input_head->number = ++number;

		/* Create in end new object */
		push(input_head, create_input_element());
		input_head = input_head->next;

		/* Go to new line */
		while ((buf = fgetc(stream_1)) != '\n');
		while ((buf = fgetc(stream_2)) != '\n');
	} while (true);
}

/*!
\brief Check mark

Check marks in second table with defined Max_Exam_result
\param[in] input_head pointer to begin of list Table
\return void
\ingroup Refsol
*/
void Check_max_mark(Table* input_head)
{
	int count = 0;
	while (input_head->next)
	{
		if (input_head->exam_result == Max_Exam_result)
			count++;
	}
	printf("%d", count);
}

/*!
\brief Check bad_result

Check exam_results in second table with defined Max_Exam_result*0,6
\param[in] input_head pointer to begin of list Table
\return void
\ingroup Refsol
*/
void Check_bad_results(Table* input_head)
{
	int count = 0;
	while (input_head->next)
	{
		if (input_head->exam_result < (int)(0,6 * Max_Exam_result))
			count++;
	}
	printf("%d", count);
}