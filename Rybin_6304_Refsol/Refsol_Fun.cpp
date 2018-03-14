/*!
\file
\brief Refsol Functions
\author Rybin Aleksandr 1 course 2 half
\date 22.05.2017
\version 3.0
*/

#include "Refsol_Header.h"

int CompareTable(const Table* a, const Table* b)
{
	return (a->group - b->group);
}

void ReadTable1(FILE* stream,Vector* data)
{
	int count = 0;
	char buf[MAX_LENGTH_TOKEN * 5 + 10]; // Five fields and integer(INT_MAX have 10 signs)

    memset(data->vector_ptr, 0, sizeof(data->vector_ptr));

	/* Skip Header*/
	fscanf(stream,"%*s");
	if(feof(stream))
	{
		printf("Error reading first table");
		data->len = -1;
		return ;
	}

	while (count < MAX_LINES)
	{
		fscanf(stream,"%s",buf);
		if(feof(stream))
		{
			data->len = count;
			return ;
		}

		if(!ParseString(&(data->vector_ptr[count]), buf , 0))
		{
			printf("Eror reading first table");
			data->len = -1;
			return ;
		}
		count++;
	}
}

void ReadTable2(FILE* stream,Vector* data)
{
	int count = 0;
	char buf[MAX_LENGTH_TOKEN * 2 + 10]; // Two fields and integer(INT_MAX have 10 signs)

    memset(data->vector_ptr, 0 , sizeof(data->vector_ptr));

	/* Skip Header,*/
	fscanf(stream,"%*s");
	if(feof(stream))
	{
		printf("Eror reading second table");
		data->len = -1;
		return ;
	}

	while (count < MAX_LINES)
	{
		fscanf(stream,"%s",buf);
		if(feof(stream))
		{
			data->len = count;
			return ;
		}

		if(!ParseString(&(data->vector_ptr[count]), buf , 1))
		{
			printf("Eror reading second table");
			data->len = -1;
			return ;
		}
		count++;
	}
}

void CombineTables(Vector* data1,Vector* data2,Vector* data)
{
	if(data1->len < 0 || data2->len < 0 || data1->len != data2->len)
	{
		data->len = -1;
		return ;
	}

	memset(data->vector_ptr, 0 ,sizeof(data->vector_ptr));
	data->len = data1->len;

	for(int i = 0; i < data->len; i++)
	{
		if(strcmp(data1->vector_ptr[i].name,data2->vector_ptr[i].name) != 0
			|| strcmp(data1->vector_ptr[i].surname,data2->vector_ptr[i].surname) != 0)
		{
			data->len = -1;
			return ;
		}

		strcpy(data->vector_ptr[i].name,data1->vector_ptr[i].name);
		strcpy(data->vector_ptr[i].surname,data1->vector_ptr[i].surname);
		strcpy(data->vector_ptr[i].patronymic,data1->vector_ptr[i].patronymic);
		strcpy(data->vector_ptr[i].GitHub_account,data1->vector_ptr[i].GitHub_account);
		strcpy(data->vector_ptr[i].Email,data1->vector_ptr[i].Email);
		data->vector_ptr[i].group = data1->vector_ptr[i].group;
		data->vector_ptr[i].exam_result = data2->vector_ptr[i].exam_result;
	}
}

void CheckBadResults(Vector* data)
{
	int count = 0;
	for (int i = 0; i < data->len; i++)
	{
		if ((data->vector_ptr[i].exam_result <= (int)(0.6 * MAX_EXAM_RESULT))
			&& (data->vector_ptr[i].flag != 1))
			count++;
	}
	printf("Students with mark less then 60 percents: %d\n", count);
}

void CheckGoodResults(Vector* data)
{
	int count = 0;
	for (int i = 0; i < data->len; i++)
	{
		if ((data->vector_ptr[i].exam_result == MAX_EXAM_RESULT)
			&& (data->vector_ptr[i].flag != 1))
			count++;
	}
	printf("Students with max mark: %d\n", count);
}

void CheckRepeats(Vector* data)
{
	for (int i = 0; i < data->len - 1; i++)
        if(memcmp(&(data->vector_ptr[i]),
				  &(data->vector_ptr[i + 1]),sizeof(Table)) == 0)
            data->vector_ptr[i].flag = 1;
}

void CheckByGroup(Vector* data)
{
	for (int i = 0; i < data->len; i++)
	{
		if (data->vector_ptr[i].group != data->vector_ptr[i + 1].group)
		{
			if (data->vector_ptr[i].flag == 1)	// If repeats then flag saves
				continue;
			data->vector_ptr[i].flag = -1;
		}
		else if (data->vector_ptr[i + 1].flag == 1)
		//If next is repeat then current student is last
			data->vector_ptr[i].flag = -1;
	}
}

void SaveResults(Vector* data)
{
	FILE* result = fopen(RESULT, "w");
	fprintf(result, RESULT_HEADER);

	for (int i = 0; i < data->len; i++)
	{
		if (data->vector_ptr[i].flag == 1)
			continue;

		fprintf(result, "%d,%s,%s,%s,%s,%s,%d\n",
            			data->vector_ptr[i].group,
	            		data->vector_ptr[i].name,
        		    	data->vector_ptr[i].surname,
        			    data->vector_ptr[i].patronymic,
        			    data->vector_ptr[i].GitHub_account,
        			    data->vector_ptr[i].Email,
			            data->vector_ptr[i].exam_result);

		if (data->vector_ptr[i].flag == -1)
            			fprintf(result, "\n\n");
	}

	fclose(result);
}

int ParseString(Table* obj,char* buf,int param)
{
		char* buf_ptr = strtok(buf,",");
		if(!buf_ptr) return -1;
		strcpy(obj->name,buf_ptr);

		buf_ptr = strtok(NULL,",");
		if(!buf_ptr) return -1;
		strcpy(obj->surname,buf_ptr);

		if(param == 0);
		else
		{
			buf_ptr = strtok(NULL,",");
			if(!buf_ptr) return -1;
			obj->exam_result = atoi(buf_ptr);

			buf_ptr = strtok(NULL,",");
			if(buf_ptr) return -1; // if something extra in buf

			return 1;
		}

		buf_ptr = strtok(NULL,",");
		if(!buf_ptr) return -1;
		strcpy(obj->patronymic,buf_ptr);

		buf_ptr = strtok(NULL,",");
		if(!buf_ptr) return -1;
		strcpy(obj->GitHub_account,buf_ptr);

		buf_ptr = strtok(NULL,",");
		if(!buf_ptr) return -1;
		strcpy(obj->Email,buf_ptr);

		buf_ptr = strtok(NULL,",");
		if(!buf_ptr) return -1;
		obj->group = atoi(buf_ptr);

		buf_ptr = strtok(NULL,",");
		if(buf_ptr) return -1; // if something extra in buf

	return 1;
}
