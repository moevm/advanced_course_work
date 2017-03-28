#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TestNumber 50            // количество случайных тестов
#define MaxMatrix 20			// максимальное количество матриц в файле
#define MaxMatrixSize 10
#define MinMatrixSize 2
#define MaxElement 100
#define MinElement -20

int RandCount(int max,int min);		// функция для получения случайного значения

char* MakeName(int index); 	// генератор имён файлов

int main()
{	
	srand(time(NULL));
	int number_of_files;
	char* filename = (char*)malloc(sizeof(char)*10);
	int k;
	FILE* file;
	for(number_of_files = 0; number_of_files< TestNumber; ++number_of_files)
	{
		filename = MakeName(number_of_files+1);
		printf("%s\n",filename);
		file = fopen(filename,"wt");
		int number_of_matrix = RandCount(MaxMatrix, 1);
		for(k=0; k<number_of_matrix; ++k)
		{
			int n = RandCount(MaxMatrixSize,MinMatrixSize);
			int m;
			 if (RandCount(10,0) == 0)
			 {
	 			m = RandCount(MaxMatrixSize,MinMatrixSize);   // создаём случайную матрицу
			 }
			 else
			 {
				m = n;							// создаём квадратную матрицу
			 }
			for(int i = 0; i < m; ++i)
			{
				for(int j = 0; j < n; ++j)
				{
					fprintf(file, "%d ",RandCount(MaxElement,MinElement));   // заполним матрицу случайными числами в пределах [-100,100]
				}
				fprintf(file, "\n");
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}

	file = fopen("input","wt");         			//   создадим файл с командами
	int n = RandCount(MaxMatrix,MaxMatrixSize);		// и заполним его так, чтобы было
	for(k=0;k<n;++k)								// от 11 до 21 команды
	{
		fprintf(file, "%d ",RandCount(3,1));
	}
	fprintf(file, "4 ");    // добавление завершающей команды
	fclose(file);

	return 0;
}


int RandCount(int max,int min)
{

	int result = min + rand() % max;
	return result;
}

char* MakeName(int index)
{
	char str[5];
	sprintf(str,"%d",index);
	char name[10] = "test";
	char add[]=".txt";
	strcat(name,str);
	strcat(name,add);
	return name;
}

