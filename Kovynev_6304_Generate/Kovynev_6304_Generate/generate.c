/**
	* File generate.c
	* Generate BMP Image and Numeric Data Text Document
	* Written by kovinevmv
	* 18.03.2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fprintf_2byte(FILE* outfile, int value)
{
	fprintf(outfile, "%c", value & 0x000000FF);
	fprintf(outfile, "%c", (value & 0x0000FF00) >> 8);
}

void fprintf_4byte(FILE* outfile, int value)
{
	fprintf(outfile, "%c", value & 0x000000FF);
	fprintf(outfile, "%c", (value & 0x0000FF00) >> 8);
	fprintf(outfile, "%c", (value & 0x00FF0000) >> 16);
	fprintf(outfile, "%c", (value & (unsigned int)0xFF000000) >> 24);
}

void Create_BMP_File(int Width, int Height) {

	FILE* outfile_bmp = fopen("./input.bmp", "wb");

	int extra_bytes = 4 - ((Width * 3) % 4);
	if (extra_bytes == 4)
	{
		extra_bytes = 0;
	}

	int padded_size = ((Width * 3) + extra_bytes) * Height;

	int BMP_struct[16];
	BMP_struct[0] = 0x4D42;			// Signature ('BM')		Bytes: 2
	BMP_struct[1] = padded_size + 54;	// FileSize			Bytes: 4
	BMP_struct[2] = 0;			// Reserved field 1		Bytes: 2
	BMP_struct[3] = 0;			// Reserved field 2		Bytes: 2
	BMP_struct[4] = 54;			// OffsetBits			Bytes: 4
	BMP_struct[5] = 40;			// BITMAPINFO Size		Bytes: 4
	BMP_struct[6] = Width;			// Width			Bytes: 4
	BMP_struct[7] = Height;			// Height			Bytes: 4
	BMP_struct[8] = 1;			// Planes			Bytes: 2
	BMP_struct[9] = 24;			// BitCount			Bytes: 2
	BMP_struct[10] = 0;			// Compression			Bytes: 4
	BMP_struct[11] = padded_size;		// PaddedSize			Bytes: 4
	BMP_struct[12] = 0;			// XpelsPerMeter		Bytes: 4
	BMP_struct[13] = 0;			// YpelsPerMeter		Bytes: 4
	BMP_struct[14] = 0;			// ColorsUsed			Bytes: 4
	BMP_struct[15] = 0;			// ColorsImportant		Bytes: 4

	for (int i = 0; i <= 15; i++)
	{
		if ((i == 0) || (i == 2) || (i == 3) || (i == 8) || (i == 9))
		{
			fprintf_2byte(outfile_bmp, BMP_struct[i]);
		}
		else
		{
			fprintf_4byte(outfile_bmp, BMP_struct[i]);
		}
	}

	int red, green, blue;

	for (int i = Height - 1; i >= 0; i--)
	{
		for (int j = 0; j < Width; j++)
		{
			red = rand() % 255;
			green = rand() % 255;
			blue = rand() % 255;

			fprintf(outfile_bmp, "%c", blue);
			fprintf(outfile_bmp, "%c", green);
			fprintf(outfile_bmp, "%c", red);
		}

		if (extra_bytes)
		{
			for (int i = 0; i < extra_bytes; i++)
			{
				fprintf(outfile_bmp, "%c", 0);
			}
		}
	}
	fclose(outfile_bmp);
	return;
}

void Create_TXT_File()
{
	FILE* outfile_txt = fopen("./input.txt", "w");

	fprintf(outfile_txt, "%d\n%d\n", rand() % 2000, rand() % 2000);
	fprintf(outfile_txt, "%d\n%d\n", rand() % 2000, rand() % 2000);

	int commands_size = rand() % 10;
	for (int i = 0; i < commands_size; i++)
	{
		fprintf(outfile_txt, "%d\n", rand() % 5);
	}

	fclose(outfile_txt);
}

int main()
{
	srand(time(NULL));
	int Width = 1280;
	int Height = 720;

	Create_BMP_File(Width, Height);
	Create_TXT_File();

	return 0;
}

