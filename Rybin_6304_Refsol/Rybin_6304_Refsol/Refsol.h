/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"

#define Sizeof_Commands 10

/*!
\brief Read data from tables
\param[in] stream_1 pointer to first table
\param[in] stream_2 pointer to second table
\return first_element Pointer to begin of readed list
\ingroup Refsol
*/
Table* Read_Data(FILE* stream_1, FILE* stream_2)
{	
	int buf;

	/* Skip headers of tables */
	while ((buf = fgetc(stream_1)) != '\n')
		if (feof(stream_1))
		{
			printf("Fail with input_file_1");
			return NULL;
		}
	while ((buf = fgetc(stream_2)) != '\n')
		if (feof(stream_2))
		{
			printf("Fail with input_file_2");
			return NULL;
		}

	/* Number of line in table */
	int number = 1;
	/* Create first element that will be return */
	Table* first_element = create_input_element();
	Table* input_head = first_element;

	/* Reading fields */
	do
	{
		int i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->name[i++] = buf;
		}
		input_head->name[i] = '\0';
		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->surname[i++] = buf;
		}
		input_head->surname[i] = '\0';
		i = 0;
		
		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->patronymic[i++] = buf;
		}
		input_head->patronymic[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->GitHub_account[i++] = buf;
		}
		input_head->GitHub_account[i] = '\0';

		i = 0;

		while ((buf = fgetc(stream_1)) != ',')
		{
			if (feof(stream_1))
				return first_element;
			input_head->Email[i++] = buf;
		}
		input_head->Email[i] = '\0';

		i = 0;

		fscanf(stream_1, "%d", &input_head->group);
		if (feof(stream_1))
			return first_element;

		/* Skip to fields in second table */
		while ((buf = fgetc(stream_2)) != ',')
			if (feof(stream_2))
				return first_element;;
		while ((buf = fgetc(stream_2)) != ',')
			if (feof(stream_2))
				return first_element;;

		fscanf(stream_2, "%d", &input_head->exam_result);
		if (feof(stream_2))
			return first_element;

		input_head->number = ++number;

		/* Create in end new object */
		push(input_head, create_input_element());
		input_head = input_head->next;

		/* Go to new line */
		while ((buf = fgetc(stream_1)) != '\n');
		if (feof(stream_1))
			return first_element;
		while ((buf = fgetc(stream_2)) != '\n')
			if (feof(stream_2))
				return first_element;
	} while (true);
}

/*!
\brief Read commands from file
\param[in] commands Pointer to file with commands
\return lenth of vector, or -1 if any error
\ingroup Refsol
*/
Vector Read_Commands(FILE* commands);

