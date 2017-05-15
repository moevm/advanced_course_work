/*
* File generate.c
* Generate 5 Bitmap Images and Numeric Data Text Document
* Written by kovinevmv
* 07.05.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "rwBitmap.h"

void addColorToBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue);

void addRectangleToBitmap(RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP,
	int numberOfRectangles, int desiredColorRed, int desiredColorGreen,
	int desiredColorBlue);

void createBitmapFile(int Width, int Height, char* fileNameIndex,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue);

void createTxtFile(int Width, int Height);


int main()
{
	srand(time(NULL));
	int Width = 640;
	int Height = 360;

	unsigned int desiredColorRed, desiredColorGreen, desiredColorBlue;

	char fileNameIndex[3];

	for (int i = 1; i <= 5; i++)
	{
		sprintf(fileNameIndex, "%d", i);

		desiredColorRed = rand() % 255;
		desiredColorGreen = rand() % 255;
		desiredColorBlue = rand() % 255;

		createBitmapFile(Width, Height, fileNameIndex,
			desiredColorRed, desiredColorGreen, desiredColorBlue);
	}

	createTxtFile(Width, Height);
	return 0;
}


void createBitmapFile(int Width, int Height, char* fileNameIndex,
	int desiredColorRed, int desiredColorGreen, int desiredColorBlue)
{
	char fileName[30] = "./input_";
	strcat(fileName, fileNameIndex);
	strcat(fileName, ".bmp");

	FILE* outfileBMP = fopen(fileName, "wb");

	BITMAPFILEHEADER headerBMP;
	BITMAPINFOHEADER infoBMP;

	int extraBytes = 4 - ((Width * 3) % 4);
	if (extraBytes == 4)
	{
		extraBytes = 0;
	}

	int paddedSize = ((Width * 3) + extraBytes) * Height;

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

	RGBPIXEL** arrayRGB = (RGBPIXEL**)malloc(sizeof(RGBPIXEL*)*Height);
	for (int i = 0; i < Height; i++)
	{
		arrayRGB[i] = (RGBPIXEL*)malloc(sizeof(RGBPIXEL)*Width);
	}
	
	addColorToBitmap(arrayRGB, infoBMP, desiredColorRed,
		desiredColorGreen, desiredColorBlue);

	addRectangleToBitmap(arrayRGB, infoBMP, 25, 255, 255, 255);
	addRectangleToBitmap(arrayRGB, infoBMP, 25, desiredColorRed,
		desiredColorGreen, desiredColorBlue);

	writeToBitmapHeader(outfileBMP, headerBMP);
	writeToBitmapInfo(outfileBMP, infoBMP);
	writeToBitmapRGB(outfileBMP, arrayRGB, infoBMP);

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

			int colorFrequency;
			colorFrequency = rand() % 3;

			if (colorFrequency == 0)
			{
				arrayRGB[i][j].rgbBlue = 255;
				arrayRGB[i][j].rgbGreen = 255;
				arrayRGB[i][j].rgbRed = 255;
			}

			else if (colorFrequency == 1)
			{
				arrayRGB[i][j].rgbBlue = rand() % 256;
				arrayRGB[i][j].rgbGreen = rand() % 256;
				arrayRGB[i][j].rgbRed = rand() % 256;
			}

			else
			{
				arrayRGB[i][j].rgbBlue = desiredColorBlue;
				arrayRGB[i][j].rgbGreen = desiredColorGreen;
				arrayRGB[i][j].rgbRed = desiredColorRed;
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
				arrayRGB[i][j].rgbBlue = desiredColorBlue;
				arrayRGB[i][j].rgbGreen = desiredColorGreen;
				arrayRGB[i][j].rgbRed = desiredColorRed;
			}
		}
	}

}

void createTxtFile(int Width, int Height)
{
	FILE* outfileTXT = fopen("./input.txt", "w");

	fprintf(outfileTXT, "./input_1.bmp 10 50 20 30 1 2 3 3 2 1 4\n");

	for (int i = 1; i < 50; i++)
	{
		int commandsSize = rand() % 12 + 1;
		fprintf(outfileTXT, "%s", "./input_");

		int isCorrectCommand = rand() % 2;
		if (isCorrectCommand)
		{
			fprintf(outfileTXT, "%d.bmp ", rand() % 5 + 1);
		}
		else
		{
			fprintf(outfileTXT, "%d.bmp ", rand() % 10 + 1);
		}


		isCorrectCommand = rand() % 2;
		if (!isCorrectCommand)
		{
			fprintf(outfileTXT, "%d %d ", rand() % 5000 - 1000, rand() % 5000 - 1000);
			fprintf(outfileTXT, "%d %d ", rand() % 5000 - 1000, rand() % 5000 - 1000);
		}
		else
		{
			int x0 = 1;
			int y0 = 0;
			int x1 = 0;
			int y1 = 1;

			while (x0 >= x1)
			{
				x0 = rand() % Width;
				x1 = rand() % Height;
			}

			while (y1 >= y0)
			{
				y0 = rand() % Width;
				y1 = rand() % Height;
			}

			fprintf(outfileTXT, "%d %d ", x0, y0);
			fprintf(outfileTXT, "%d %d ", x1, y1);
		}

		isCorrectCommand = rand() % 2;
		if (!isCorrectCommand)
		{
			for (int i = 0; i < commandsSize; i++)
			{
				fprintf(outfileTXT, "%d ", rand() % 7);
			}

			fprintf(outfileTXT, "\n");
		}
		else
		{
			for (int i = 0; i < commandsSize; i++)
			{
				fprintf(outfileTXT, "%d ", rand() % 3 + 1);
			}

			fprintf(outfileTXT, "%d\n", 4);
		}
	}

	fclose(outfileTXT);
}
