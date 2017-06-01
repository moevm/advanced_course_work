#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
// количество случайных тестов
// максимальное количество матриц в файле
#define TEST_NUMBER 50            
#define MAX_MATRIX 20			
#define MAX_MATRIX_SIZE 10
#define MIN_MATRIX_SIZE 2
#define MAX_ELEMENT 100
#define MIN_ELEMENT -20

int RandCount(int count,int min);		// функции для получения случайного значения


int main()
{	
	srand(time(NULL));
	int number_of_files;
	char* filename;
	int k;
	FILE* file;
	for(number_of_files = 0; number_of_files< TEST_NUMBER; ++number_of_files)
	{
		char filename[BUFSIZ];
		sprintf(filename,"test%d.txt",number_of_files+1);
		file = fopen(filename,"wt");
		printf("%s\n",filename);
		int number_of_matrix = RandCount(MAX_MATRIX, 1);
		for(k=0; k<number_of_matrix; ++k)
		{
			int n = RandCount(MAX_MATRIX_SIZE,MIN_MATRIX_SIZE);
			int m;
			 if (RandCount(10,0) == 0)
			 {
	 			m = RandCount(MAX_MATRIX_SIZE,MIN_MATRIX_SIZE);   // создаём случайную матрицу
			 }
			 else
			 {
				m = n;							// создаём квадратную матрицу
			 }
			 int arr[MAX_MATRIX_SIZE];
			for(int i = 0; i < m; ++i)
			{
				int k = RandCount(10,2);
				for(int j = 0; j < n; ++j)
				{
					if ((number_of_files % 11 != 0) || (i==0))
					{
						arr[j] = RandCount(MAX_ELEMENT,MIN_ELEMENT);
						fprintf(file, "%d.%d ",arr[j],RandCount(MAX_ELEMENT,0)); // заполним матрицу случайными числами
					}
				else
					{
						fprintf(file, "%d.%d ",k*arr[j],RandCount(MAX_ELEMENT,0));
					}
				}
				fprintf(file, "\n");
			}
			fprintf(file, "\n");
			fprintf(file, "\n");
		}
		fclose(file);
	}

	file = fopen("input","wt");         			
	int n = RandCount(2,0);		
	for(k=0;k<n;++k)								
	{
		fprintf(file, "%d ",RandCount(2,1));
	}
	fprintf(file, "1 2 3 4\n");    // добавление завершающей команды

	return 0;
}


int RandCount(int count,int min)
{

	int result = min + rand() % count;
	return result;
}