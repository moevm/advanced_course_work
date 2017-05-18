#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
//#include "MakeName.h"
#include <time.h>

#define TEST_NUMBER 50            // количество случайных тестов
#define MAX_MATRIX 20			// максимальное количество матриц в файле
#define MAX_MATRIX_SIZE 10
#define MIN_MATRIX_SIZE 2
#define MAX_ELEMENT 100
#define MIN_ELEMENT -20

int RandCount(int max,int min);		// функция для получения случайного значения

char* MakeName(int index,char* name, char* add); 	// генератор имён файлов

int main()
{	
	srand(time(NULL));
	int number_of_files;
	char* filename;
	int k;
	FILE* file;
	for(number_of_files = 0; number_of_files< TEST_NUMBER; ++number_of_files)
	{
		filename = MakeName(number_of_files+1,"test",".txt");
		file = fopen(filename,"wt");
		printf("%s\n",filename);
		int number_of_matrix = RandCount(MAX_MATRIX, 1);
		for(k=0; k<number_of_matrix; ++k)
		{
			int n = RandCount(MAX_MATRIX_SIZE,MIN_MATRIX_SIZE);
			int* arr = (int*)malloc(sizeof(int)*n);
			int m;
			 if (RandCount(10,0) == 0)
			 {
	 			m = RandCount(MAX_MATRIX_SIZE,MIN_MATRIX_SIZE);   // создаём случайную матрицу
			 }
			 else
			 {
				m = n;							// создаём квадратную матрицу
			 }
			for(int i = 0; i < m; ++i)
			{
				for(int j = 0; j < n; ++j)
				{
					if ((number_of_files % 11 != 0) || (i==0))
					{
						arr[j] = RandCount(MAX_ELEMENT,MIN_ELEMENT);
						fprintf(file, "%d ",arr[j]); // заполним матрицу случайными числами
					}
				else
					{
						fprintf(file, "%d ",2*arr[j]);
					}
				}
				fprintf(file, "\n");
			}
			fprintf(file, "\n");
			fprintf(file, "\n");
		}
		fclose(file);
		free(filename);
	}

	file = fopen("input","wt");         			
	int n = RandCount(2,3);		
	for(k=0;k<n;++k)								
	{
		fprintf(file, "%d ",RandCount(3,1));
	}
	fprintf(file, "4 ");    // добавление завершающей команды

	return 0;
}


int RandCount(int max,int min)
{

	int result = min + rand() % max;
	return result;
}

char* MakeName(int index,char* name, char* add)
{	
	char* result = (char*)malloc(sizeof(char)*20);			// создание имени файла
	char str[5];
	sprintf(str,"%d",index);
	strcat(result,name);
	strcat(result,str);
	strcat(result,add);
	return result;
}
