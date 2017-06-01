#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void writeToBitmapHeader(FILE* outfile, BITMAPFILEHEADER headerBMP)
{
	fwrite(&headerBMP.bfType, 2, 1, outfile);
	fwrite(&headerBMP.bfSize, 4, 1, outfile);
	fwrite(&headerBMP.bfReserved1, 2, 1, outfile);
	fwrite(&headerBMP.bfReserved2, 2, 1, outfile);
	fwrite(&headerBMP.bfOffBits, 4, 1, outfile);
}


void writeToBitmapInfo(FILE* outfile, BITMAPINFOHEADER infoBMP)
{
	fwrite(&infoBMP.biSize, 4, 1, outfile);
	fwrite(&infoBMP.biWidth, 4, 1, outfile);
	fwrite(&infoBMP.biHeight, 4, 1, outfile);
	fwrite(&infoBMP.biPlanes, 2, 1, outfile);
	fwrite(&infoBMP.biBitCount, 2, 1, outfile);
	fwrite(&infoBMP.biCompression, 4, 1, outfile);
	fwrite(&infoBMP.biSizeImage, 4, 1, outfile);
	fwrite(&infoBMP.biXPelsPerMeter, 4,1, outfile);
	fwrite(&infoBMP.biYPelsPerMeter, 4, 1, outfile);
	fwrite(&infoBMP.biClrUsed, 4, 1, outfile);
	fwrite(&infoBMP.biClrImportant, 4, 1, outfile);
}

void WriteToBitmapRGB(FILE* outfile, RGBQUAD** arrayRGB, BITMAPINFOHEADER infoBMP)
{
	int extraBytes = 4 - ((infoBMP.biWidth * 3) % 4);
	if (extraBytes == 4)
	{
		extraBytes = 0;
	}

	for (int i = infoBMP.biHeight - 1; i >= 0; i--)
	{
		for (int j = 0; j < infoBMP.biWidth; j++)
		{
			fprintf(outfile, "%c", arrayRGB[i][j].rgbBlue);
			fprintf(outfile, "%c", arrayRGB[i][j].rgbGreen);
			fprintf(outfile, "%c", arrayRGB[i][j].rgbRed);
		}

		if (extraBytes)
		{
			for (int j = 0; j < extraBytes; j++)
			{
				fprintf(outfile, "%c", 0);
			}
		}
	}

}

void createBitmapFile(int Width, int Height)
{

	FILE* outfileBMP = fopen("./input.bmp", "wb");

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

	writeToBitmapHeader(outfileBMP, headerBMP);
	writeToBitmapInfo(outfileBMP, infoBMP);


	RGBQUAD** arrayRGB = (RGBQUAD**)malloc(sizeof(RGBQUAD*)*Height);
	for (int i = 0; i < Height; i++)
	{
		arrayRGB[i] = (RGBQUAD*)malloc(sizeof(RGBQUAD)*Width);
	}


	for (int i = 0; i <Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			arrayRGB[i][j].rgbBlue = rand() % 256;
			arrayRGB[i][j].rgbGreen = rand() % 256;
			arrayRGB[i][j].rgbRed = rand() % 256;
		}

	}

	WriteToBitmapRGB(outfileBMP, arrayRGB, infoBMP);

	fclose(outfileBMP);
}
