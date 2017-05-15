/*
* Файл generate.c
* Создание 5 BMP изображений и текстовый документ с числовыми данными
* Автор: kovinevmv
* 15.05.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "rwBitmap.h"


/*======================================================================

  Функция addColorToBitmap заполняет переданный массив структур,
  отвечающий за пиксели изображения, произвольным образом данными
  одним из трех вариантов: белым цветом, переданным цветом фона 
  или абсолютно произвольным RGB цветом 
*/
void addColorToBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue);
//======================================================================



/*======================================================================

  Функция addRectangleToBitmap заполняет переданный массив структур,
  отвечающий за пиксели изображения, произвольными прямоугольниками.
*/
void addRectangleToBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP,
	int numberOfRectangles, int desiredColorRed, int desiredColorGreen,
	int desiredColorBlue);
//======================================================================



/*======================================================================

  Функция createBitmapFile создает BMP изображение размерами
  Width*Height, с номером fileNameIndex и цветом фона desiredColorRed,
  desiredColorGreen, desiredColorBlue, переданными данной функции
*/
void createBitmapFile(int Width, int Height, char* fileNameIndex,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue);
//======================================================================



/*======================================================================
  Функция createTxtFile создает файл input.txt с командами.
  Количество команд - 100.
*/
void createTxtFile(int Width, int Height);
//======================================================================



int main()
{
	srand(time(NULL));
	int Width = 640;        // Ширина изображения
	int Height = 360;       // Высота изображения

	unsigned int desiredColorRed, desiredColorGreen, desiredColorBlue;

	char fileNameIndex[3];  // Номер изображения

	for (int i = 1; i <= 5; i++)
	{
		// Преобразование номера изображения в строку
		sprintf(fileNameIndex, "%d", i);

		desiredColorRed = rand() % 255;     //
		desiredColorGreen = rand() % 255;   // Генерация цвета фона
		desiredColorBlue = rand() % 255;    //

		// Создание изображения
		createBitmapFile(Width, Height, fileNameIndex,
			desiredColorRed, desiredColorGreen, desiredColorBlue);
	}

	// Создание файла с командами
	createTxtFile(Width, Height);

	return 0;
}


void createBitmapFile(int Width, int Height, char* fileNameIndex,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue)
{
	char fileName[30] = "./input_";   // Создание имени изображения 
	strcat(fileName, fileNameIndex);  // с учетом его номера
	strcat(fileName, ".bmp");         //

	FILE* outfileBMP = fopen(fileName, "wb");

	BITMAPFILEHEADER headerBMP;
	BITMAPINFOHEADER infoBMP;

	// Количество байтов необходимых для выравнивания изображения
	int extraBytes = 4 - ((Width * 3) % 4);
	if (extraBytes == 4)
	{
		extraBytes = 0;
	}

	// Полный размер изображения с учетом байтов для выравнивания
	int paddedSize = ((Width * 3) + extraBytes) * Height;

	// Заполнение структур BMP изображения
	headerBMP.bfType = 0x4D42;
	headerBMP.bfSize = 54 + paddedSize;
	headerBMP.bfReserved1 = 0;
	headerBMP.bfReserved2 = 0;
	headerBMP.bfOffBits = 54;

	infoBMP.biSize = 40;
	infoBMP.biWidth = Width;
	infoBMP.biHeight = Height;
	infoBMP.biPlanes = 1;
	infoBMP.biBitCount = 24;
	infoBMP.biCompression = 0;
	infoBMP.biSizeImage = paddedSize;
	infoBMP.biXPelsPerMeter = 0;
	infoBMP.biYPelsPerMeter = 0;
	infoBMP.biClrUsed = 0;
	infoBMP.biClrImportant = 0;

	// Инициализация двумерного массива структур
	RGBPIXEL** arrayRGB = (RGBPIXEL**)malloc(sizeof(RGBPIXEL*)*Height);
	for (int i = 0; i < Height; i++)
	{
		arrayRGB[i] = (RGBPIXEL*)malloc(sizeof(RGBPIXEL)*Width);
	}
	
	// Вызов функции addColorToBitmap
	addColorToBitmap(arrayRGB, infoBMP, desiredColorRed,
		desiredColorGreen, desiredColorBlue);

	// Вызов функций addRectangleToBitmap
	addRectangleToBitmap(arrayRGB, infoBMP, 25, 255, 255, 255);
	addRectangleToBitmap(arrayRGB, infoBMP, 25, desiredColorRed,
		desiredColorGreen, desiredColorBlue);

	// Запись данных BMP изображения
	writeToBitmapHeader(outfileBMP, headerBMP);
	writeToBitmapInfo(outfileBMP, infoBMP);
	writeToBitmapRGB(outfileBMP, arrayRGB, infoBMP);

	// Освобождение памяти
	for (int i = 0; i < Height; i++)
	{
		free(arrayRGB[i]);
	}

	free(arrayRGB);

	fclose(outfileBMP);
}

void addColorToBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue)
{

	for (int i = 0; i < infoBMP.biHeight; i++)
	{
		for (int j = 0; j < infoBMP.biWidth; j++)
		{

			// Переменная, отвечающая за цвет пикселя
			// 0 - белый, 1 - рандомный, 2 - переданный
			int colorFrequency;      
			colorFrequency = rand() % 3; 

			if (colorFrequency == 0)
			{
				arrayRGB[i][j].rgbBlue = 255;   // Заполнение
				arrayRGB[i][j].rgbGreen = 255;  // пикселя белым 
				arrayRGB[i][j].rgbRed = 255;    // цветом
			}

			else if (colorFrequency == 1)
			{
				arrayRGB[i][j].rgbBlue = rand() % 256;    // Заполнение 
				arrayRGB[i][j].rgbGreen = rand() % 256;   // пикселя рандомным
				arrayRGB[i][j].rgbRed = rand() % 256;     // цветом
			}

			else
			{
				arrayRGB[i][j].rgbBlue = desiredColorBlue;    // Заполнение 
				arrayRGB[i][j].rgbGreen = desiredColorGreen;  // пикселя переданным
				arrayRGB[i][j].rgbRed = desiredColorRed;      // цветом
			}

		}
	}

}

void addRectangleToBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP,
	int numberOfRectangles, int desiredColorRed, int desiredColorGreen,
	int desiredColorBlue)
{

	for (int k = 0; k < numberOfRectangles; k++)
	{
		// Инициализация размеров добавляемых прямоуголников
		int RectangleX0Coordinates = rand() % (infoBMP.biWidth * 13 / 15 - 1);
		int RectangleY0Coordinates = rand() % (infoBMP.biHeight * 13 / 15 - 1);
		int RectangleWidth = rand() % (infoBMP.biWidth / 15) + 1;
		int RectangleHeight = rand() % (infoBMP.biHeight / 15) + 1;

		for (int i = RectangleY0Coordinates;
			i < RectangleY0Coordinates + RectangleHeight; i++)
		{
			for (int j = RectangleX0Coordinates;
				j < RectangleX0Coordinates + RectangleWidth; j++)
			{
				arrayRGB[i][j].rgbBlue = desiredColorBlue;    // Заполнение 
				arrayRGB[i][j].rgbGreen = desiredColorGreen;  // пикселя переданным
				arrayRGB[i][j].rgbRed = desiredColorRed;      // цветом
			}
		}
	}

}

void createTxtFile(int Width, int Height)
{
	FILE* outfileTXT = fopen("./input.txt", "w");

	// Запись правильных команд первого теста
	fprintf(outfileTXT, "./input_1.bmp 10 50 20 30 1 2 3 3 2 1 4\n");

	for (int i = 1; i < 50; i++)
	{
		// Переменная, отвечающая за количество команд
		int commandsSize = rand() % 12 + 1;


		// Запись пути BMP изображения
		fprintf(outfileTXT, "%s", "./input_");

		// Переменная isCorrectCommand отвечает за 
		// корректность генерируемых команд
		// 0 - некорректные, 1 - корректные
		int isCorrectCommand = rand() % 2;


		if (isCorrectCommand)
		{
			// Запись правильного индекса изображения
			fprintf(outfileTXT, "%d.bmp ", rand() % 5 + 1);
		}
		else
		{
			// Запись неправильного индекса изображения
			fprintf(outfileTXT, "%d.bmp ", rand() % 10 + 1);
		}


		isCorrectCommand = rand() % 2;
		if (!isCorrectCommand)
		{
			// Запись неправильных координат области изображения
			fprintf(outfileTXT, "%d %d ", rand() % 5000 - 1000, rand() % 5000 - 1000);
			fprintf(outfileTXT, "%d %d ", rand() % 5000 - 1000, rand() % 5000 - 1000);
		}
		else
		{
			// Генерация корректных команд

			int x0 = 1;
			int y0 = 0;
			int x1 = 0;
			int y1 = 1;

			// Генерация коррекнтых координат по Х
			// Х0 должен быть больше, чем Х1
			while (x0 >= x1)
			{
				x0 = rand() % Width;
				x1 = rand() % Height;
			}

			// Генерация коррекнтых координат по Y
			// Y1 должен быть больше, чем Y0
			while (y1 >= y0)
			{
				y0 = rand() % Width;
				y1 = rand() % Height;
			}

			// Запись правильных координат области изображения
			fprintf(outfileTXT, "%d %d ", x0, y0);
			fprintf(outfileTXT, "%d %d ", x1, y1);
		}


		isCorrectCommand = rand() % 2;
		if (!isCorrectCommand)
		{
			// Запись неправильных команд
			for (int i = 0; i < commandsSize; i++)
			{
				fprintf(outfileTXT, "%d ", rand() % 7);
			}

			fprintf(outfileTXT, "\n");
		}
		else
		{
			// Запись правильных команд
			for (int i = 0; i < commandsSize; i++)
			{
				fprintf(outfileTXT, "%d ", rand() % 3 + 1);
			}

			fprintf(outfileTXT, "%d\n", 4);
		}
	}

	fclose(outfileTXT);
}
