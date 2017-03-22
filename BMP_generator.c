#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#pragma pack(push)
#pragma pack(2) // выравнивание структур по два байта

typedef struct BITMAPFILEHEADER // описание структур для заполнения информационных полей BMP файла
{
	unsigned char   bfType[2];
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER
{
	unsigned int    biSize;
	int             biWidth;
	int             biHeight;
	unsigned short  biPlanes;
	unsigned short  biBitCount;
	unsigned int    biCompression;
	unsigned int    biSizeImage;
	int             biXPelsPerMeter;
	int             biYPelsPerMeter;
	unsigned int    biClrUsed;
	unsigned int    biClrImportant;
} BITMAPINFOHEADER;

#pragma pack(pop)

void create_BMP(int nx, int ny);

void create_TXT(int nx, int ny, int number_of_commands);

int main()
{
	srand(time(NULL));								// получение зерна генерации

	int nx, ny, number_of_commands;
	scanf("%d%d%d", &nx, &ny, &number_of_commands); // считывание (опционально, можно заменить конкретными значениями или случайными)

	create_BMP(nx, ny);								// создание случайного BMP файла с заданными размерами
	create_TXT(nx, ny, number_of_commands);			// создание случайного txt файла содержащего команды для редакции bmp файла

	return 0;
}

void create_BMP(int nx, int ny)
{
	BITMAPFILEHEADER header_BMP;					// объявление структур для заполнения информационных полей
	BITMAPINFOHEADER info_BMP;

	int staff_for_filling = 4 - ((nx * 3) % 4);		// вычисление необходимого количества бит для выравнивания
	if (staff_for_filling == 4)
	{
		staff_for_filling = 0;
	}

	int size_of_image = ((nx * 3) + staff_for_filling) * ny; // вычисление размера изображения (без инф. полей)

	header_BMP.bfType[0] = 'B';						// заполнение информационных полей BMP файла в соответствии с документацией
	header_BMP.bfType[1] = 'M';
	header_BMP.bfSize = 54 + size_of_image;			// размер информационных структур равен 54 битам
	header_BMP.bfReserved1 = 0;
	header_BMP.bfReserved2 = 0;
	header_BMP.bfOffBits = 54;						// количество бит лежащих перед началом массива изображения

	info_BMP.biSize = 40;							// размер структуры info_BMP в битах
	info_BMP.biWidth = nx;							// количество пикселей по горизонтали
	info_BMP.biHeight = ny;							// количество пикселей по вертикали
	info_BMP.biPlanes = 1;							// должно быть установлено на 1
	info_BMP.biBitCount = 24;						// количество бит в одном пикселе (в данном случае 3 байта на пиксель)
	info_BMP.biCompression = 0;						// без сжатия
	info_BMP.biSizeImage = size_of_image;			// размер изображения в битах
	info_BMP.biXPelsPerMeter = 0;					// в данном случае остальные поля не используются и равны по умолчанию нулю
	info_BMP.biYPelsPerMeter = 0;
	info_BMP.biClrUsed = 0;
	info_BMP.biClrImportant = 0;

	FILE * pFile = fopen("input_file_test.bmp", "wb");		// открытие файла в поток

	fwrite(&header_BMP, sizeof(BITMAPFILEHEADER), 1, pFile); // запись заголовочных структур в начало файла
	fwrite(&info_BMP, sizeof(BITMAPINFOHEADER), 1, pFile);

	int rand_colour = 0;

	for (int i = 0; i < ny; i++)		// цикл заполняющий массив с числовыми значениями цветов изображения случайными числами (случайными цветами)
	{
		for (int j = 0; j < (nx * 3) + staff_for_filling; j++)
		{
			if (j > (nx * 3))					// если все пиксели строки записаны и требуется дописать биты для выравнивания они дописываются
			{
				fprintf(pFile, "%c", 0);
				continue;
			}
			rand_colour = rand() % 256;			// генерация случайного числа соответствующего одной из составляющей пикселя (RGB)
			fwrite(&rand_colour, 1, 1, pFile);	// запись случайного числа в массив изображения
		}
	}
	fclose(pFile);								// закрытие файлового потока
}

void create_TXT(int nx, int ny, int number_of_commands)
{
	FILE* pFile = fopen("input.txt", "w");					// открытие текстового файла для записи

	fprintf(pFile, "%d\n%d\n%d\n%d\n",						// запись в файл набора координат и команд
		(rand() % ((nx + (nx / 4))) - rand() % (nx / 2)),	// для последующего взаимодействия эталонной программы
		(rand() % ((ny + (ny / 4))) - rand() % (ny / 2)),	// с изображением
		rand() % (nx + (nx / 8)),							// наборы сгенерированы случайно с небольшой поправкой на необходимость
		rand() % (ny + (ny / 8)));							// особой генерации координат (левая и правая точки)

	for (int i = 0; i < number_of_commands; i++)
	{
		fprintf(pFile, "%d\n", ((rand() % 3)+1));			// запись в файл команд для изменения файла в дальнейшем
	}
	fprintf(pFile, "%d", 4);								// запись в файла команды сохранения файла изображения

	fclose(pFile);											// закрытие файлового потока
}
