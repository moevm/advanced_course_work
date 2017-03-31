/*
 * File generate.c
 * Generate Bitmap Image and Numeric Data Text Document
 * Written by kovinevmv
 * 31.03.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
#include "wBitmap.h"

void createTXTFile()
{
	FILE* outfileTXT = fopen("./input.txt", "w");

	fprintf(outfileTXT, "%d\n%d\n", rand() % 2000, rand() % 2000);
	fprintf(outfileTXT, "%d\n%d\n", rand() % 2000, rand() % 2000);

	int commandsSize = rand() % 10;
	for (int i = 0; i < commandsSize; i++)
	{
		fprintf(outfileTXT, "%d\n", rand() % 5);
	}

	fclose(outfileTXT);
}

int main()
{
	srand(time(NULL));
	int Width = 1280;
	int Height = 720;

	createBitmapFile(Width, Height);
	createTXTFile();

	return 0;
}
