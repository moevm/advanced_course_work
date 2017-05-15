/*
* Файл refsol.c
* Обработка изображения в соответствии с переданными командами
* Автор: kovinevmv
* 16.05.2017
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "stack.h"
#include "rwBitmap.h"


/*======================================================================
  Функция mirrorReflectionBitmap отражает по горизонтали двумерный 
  массив цветов arrayRGB с учетом размеров изображения BMP из
  структуры infoBitmap
*/
void mirrorReflectionBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBitmap);
//======================================================================


/*======================================================================
  Функция drawBlackTriangle рисует прямоугольный треугольник в массиве
  arrayRGB в заданной области (x0, y0, x1, y1) черным цветом. Прямой 
  угол лежит в левом нижнем углу области, длина катетов определяется 
  длиной стороны области, к которой они прилегают, и равна половине 
  этой стороны.
*/
void drawBlackTriangle(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBitmap,
	int x0, int y0, int x1, int y1);
//======================================================================


/*======================================================================
  Функция searchWhiteRectangle находит в массиве arrayRGB самый 
  большой белый прямоугольник и выводит координаты левого верхнего
  угла и правого нижнего.
*/
void searchWhiteRectangle(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBitmap);
//======================================================================


/*======================================================================
  Функция writeError печатает "Fail with ... " в зависимости от 
  переданного аргумента errorCode (1 - input_file, 2 - x0, 3 - y0,
  4 - x1, 5 - y1, 6 - commands)
*/
void writeError(int errorCode);
//======================================================================


/*======================================================================
  Функция isCorrectCommands проверяет корректность введенных данных
  массива слов (команд) data длиной lenght. В случае ошибки вызывает 
  функцию writeError и возвращает 1, в противном случае - 0
*/
int isCorrectCommands(char** data, int lenght, BITMAPINFOHEADER infoBitmap);
//======================================================================


int main()
{

	// Считывание строки команд
	char* string = (char*)malloc(sizeof(char) * 500);
	fgets(string, 500, stdin);
	(*strstr(string, "\n")) = 0;


	// Выделение памяти под массив лексем - команд
	char** data = (char**)malloc(sizeof(char*) * 25);
	for (int i = 0; i < 25; i++)
	{
		data[i] = NULL;
	}

	// Разделение строки на лексемы
	int length = 0;
	for (char* word = strtok(string, " "); word; word = strtok(NULL, " "))
	{
		data[length++] = word;
	}


	// Открытие изображения BMP
	FILE* inputFile = fopen(data[0], "rb");

	// В случае отсутствия файла или ошибки открытия, вызов функции
	// writeError и вывод ненулевого кода возврата
	if (!inputFile)
	{
		writeError(1);
		return 1;
	}

	// Инициализация структур BMP изображения и считывание их из файла
	BITMAPFILEHEADER headerBitmap = readFromBitmapHeader(inputFile);
	BITMAPINFOHEADER infoBitmap = readFromBitmapInfo(inputFile);

	// Инициализация двумерного массива структур
	RGBPIXEL** arrayRGB = (RGBPIXEL**)malloc(sizeof(RGBPIXEL*)*infoBitmap.biHeight);
	for (int i = 0; i < infoBitmap.biHeight; i++)
	{
		arrayRGB[i] = (RGBPIXEL*)malloc(sizeof(RGBPIXEL)*infoBitmap.biWidth);
	}
	arrayRGB = readFromBitmapRGB(inputFile, infoBitmap);

	fclose(inputFile);

	// Проверка переданных команд на корректность
	if (!isCorrectCommands(data, length, infoBitmap))
	{
		return 1;
	}


	// В соответствии с номером команды выполняется определенная функция
	// 1 - поиск максимальной прямоугольной области
	// 2 - нарисовать черный треугольник 
	// 3 - отображение изображения
	// 4 - сохранение результатов обработки

	for (int i = 5; i < length; i++)
	{
		switch (atoi(data[i]))
		{
			case 1:
			{
				searchWhiteRectangle(arrayRGB, infoBitmap);
				break;
			}
			case 2:
			{
				drawBlackTriangle(arrayRGB, infoBitmap,
				atoi(data[1]), atoi(data[2]),
				atoi(data[3]), atoi(data[4]));
				break;
			}
			case 3:
			{
				mirrorReflectionBitmap(arrayRGB, infoBitmap);
				break;
			}
			case 4:
			{
				FILE* outFile = fopen("./refsol.bmp", "wb");

				// Запись данных BMP изображения
				writeToBitmapHeader(outFile, headerBitmap);
				writeToBitmapInfo(outFile, infoBitmap);
				writeToBitmapRGB(outFile, arrayRGB, infoBitmap);
				fclose(outFile);
			}
		}
	}

	// Освобождение памяти
	for (int i = 0; i < infoBitmap.biHeight; i++)
	{
		free(arrayRGB[i]);
	}

	free(arrayRGB);
	free(data);
	free(string);

	return 0;
}


void mirrorReflectionBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBitmap)
{

	RGBPIXEL temp;  // Переменная для обмена пикселями

	for (int i = 0; i < infoBitmap.biHeight; i++)
	{
		int k = infoBitmap.biWidth - 1;
		for (int j = 0; j < k; j++)
		{
			// Обмениваем [i][j] и [i][k] элементы местами
			temp = arrayRGB[i][j];
			arrayRGB[i][j] = arrayRGB[i][k];
			arrayRGB[i][k] = temp;
			k--;
		}
	}

}

void drawBlackTriangle(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBitmap,
	int x0, int y0, int x1, int y1)
{

	// Массив steps содержит длины отрезков i - строки треугольника
	// От 0 до половины стороны катета, прилежащего к оси X
	float* steps = (float*)malloc(sizeof(float)*(y0 - y1));
	steps[0] = 0.0;

	// Расчет длин отрезков
	for (int i = 1; i < y0 - y1; i++)
	{
		steps[i] = (float)(x1 - x0) / (float)(y0 - y1) + steps[i - 1];
	}

	int k = 0;
	for (int i = (y1 + y0) / 2; i < y0; i++)
	{
		for (int j = x0; j < x0 + (int)steps[k]; j++)
		{
			arrayRGB[i][j].rgbBlue = 0;      // Заполнение
			arrayRGB[i][j].rgbRed = 0;       // пикселя черным 
			arrayRGB[i][j].rgbGreen = 0;     // цветом
		}
		k++;
	}

}

void searchWhiteRectangle(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBitmap)
{

	Stack* stack = NULL;

	int maximumArea = 0;
	int y1 = 0;
	int x1 = 0;
	int y0 = 0;
	int x0 = 0;
	

	int* dl = (int*)malloc(sizeof(int)*infoBitmap.biWidth);
	int* dr = (int*)malloc(sizeof(int)*infoBitmap.biWidth);
	int* d  = (int*)malloc(sizeof(int)*infoBitmap.biWidth);
	for (int i = 0; i < infoBitmap.biWidth; i++)
	{
		d[i]  = -1;
		dr[i] = -1;
		dl[i] = -1;
	}


	for (int i = 0; i < infoBitmap.biHeight; i++)
	{


		for (int j = 0; j < infoBitmap.biWidth; j++)
		{
			if (!((arrayRGB[i][j].rgbBlue  == 255) &&
				  (arrayRGB[i][j].rgbRed   == 255) &&
				  (arrayRGB[i][j].rgbGreen == 255)))
			{
				d[j] = i;
			}
		}

		while (!empty(stack))
		{
			pop(&stack);
		}


		for (int j = 0; j < infoBitmap.biWidth; j++)
		{
			while (!empty(stack) && d[top(stack)] <= d[j])
			{
				pop(&stack);
			}

			dl[j] = empty(stack) ? -1 : top(stack);
			push(&stack, j);
		}

		while (!empty(stack))
		{
			pop(&stack);
		}

		for (int j = infoBitmap.biWidth - 1; j >= 0; --j)
		{
			while (!empty(stack) && d[top(stack)] <= d[j])
			{
				pop(&stack);
			}

			dr[j] = empty(stack) ? infoBitmap.biHeight : top(stack);
			push(&stack, j);

		}
		for (int j = 0; j < infoBitmap.biWidth; ++j)
		{
			if ((i - d[j]) * (dr[j] - dl[j] - 1) >= maximumArea)
			{
				maximumArea = (i - d[j]) * (dr[j] - dl[j] - 1);
				y1 = i;
				y0 = d[j];
				x1 = dr[j];
				x0 = dl[j];
			}
		}
	}

	printf("%d\n%d\n%d\n%d\n", x0 + 1, y0 + 1, x1 - 1, y1);

}

void writeError(int errorCode)
{
	printf("Fail with ");
	switch (errorCode)
	{
	case 1: printf("input_file"); break;
	case 2: printf("x0"); break;
	case 3: printf("y0"); break;
	case 4: printf("x1"); break;
	case 5: printf("y1"); break;
	case 6: printf("commands"); break;
	}
	printf("\n");
}

int isCorrectCommands(char** data, int lenght, BITMAPINFOHEADER infoBitmap)
{

	// Имя файла - один из 5 вариантов
	if (!((data[0] = "./input_1.bmp") ||
              (data[0] = "./input_2.bmp") ||
  	      (data[0] = "./input_3.bmp") ||
	      (data[0] = "./input_4.bmp") ||
	      (data[0] = "./input_5.bmp")))
	{
		writeError(1);
		return 0;
	}

	int x0 = atoi(data[1]);
	int y0 = atoi(data[2]);
	int x1 = atoi(data[3]);
	int y1 = atoi(data[4]);

	// Если координаты области по X находятся вне изображения 
	// или x0 < x1 - ошибка
	if (!(x0 < x1) || (x0 > infoBitmap.biWidth) || (x0 < 0))
	{
		writeError(2);
		return 0;
	}

	// Если координаты области по Y находятся вне изображения 
	// или y0 > y1 - ошибка
	if (!(y0 > y1) || (y0 > infoBitmap.biHeight) || (y0 < 0))
	{
		writeError(3);
		return 0;
	}

	if ((x1 > infoBitmap.biWidth) || (x1 < 0))
	{
		writeError(4);
		return 0;
	}

	if ((y1 > infoBitmap.biHeight) || (y1 < 0))
	{
		writeError(5);
		return 0;
	}

	// Команда - число от 1 до 4 включительно
	// В противном случае - ошибка
	for (int i = 5; i < lenght; i++)
	{
		if ((atoi(data[i]) > 4) || (atoi(data[i]) < 1))
		{
			writeError(6);
			return 0;
		}
	}

	// 4 - последняя команда, в случае отсутствия - ошибка
	if (atoi(data[lenght - 1]) != 4)
	{
		writeError(6);
		return 0;
	}

}
