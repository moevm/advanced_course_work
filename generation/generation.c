#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#pragma pack(push)
#pragma pack(2)					// alignment for two

typedef struct bitmapfileheader //struct for bmp header
{
	unsigned char   bfType[2];
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
} bitmapfileheader;

typedef struct bitmapinfoheader //struct for bmp info
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
} bitmapinfoheader;

#pragma pack(pop)

void create_bmp(int nx, int ny);

void create_txt(int nx, int ny, int max_number_of_commands, int gen_mode);

int main(int argc, char *argv[])
{
	srand(time(NULL));

	int count_lines =      50; // generation options by default (without argue from cmd)
	int max_x_gen   =    1337;
	int max_y_gen   =    1337;

	switch (argc)
	{
		case 2:
		{
			count_lines = atoi(argv[1]);  // if we have only one argue
			break;
		}
		case 4:
		{
			count_lines = atoi(argv[1]); // if we have four argue
			max_x_gen   = atoi(argv[2]);
			max_y_gen   = atoi(argv[3]);
			break;
		}
		default:
		{
			if(argc > 1)
				printf("Wrong generation arguments, parameters choosed by default.");
			break;
		}
	}
	int nx, ny, max_number_of_commands;
	nx = (rand() % max_x_gen) + 1;								// generation random board on x and y for image
	ny = (rand() % max_y_gen) + 1;
	max_number_of_commands = (rand() % 20) + 10;
	create_bmp(nx, ny);

	create_txt(nx, ny, max_number_of_commands, count_lines);

	return 0;
}

void create_bmp(int nx, int ny)
{
	bitmapfileheader header_bmp = { 'B', 'M' };					// create and filling headers
	bitmapinfoheader info_bmp;

	int staff_for_filling = 4 - ((nx * 3) % 4);
	if (staff_for_filling == 4)
		staff_for_filling = 0;

	int size_of_image = ((nx * 3) + staff_for_filling) * ny;  // calc alignment

	header_bmp.bfSize = 54 + size_of_image;					// filling headers by standart of .bmp
	header_bmp.bfReserved1 = 0;
	header_bmp.bfReserved2 = 0;
	header_bmp.bfOffBits = 54;

	info_bmp.biSize = 40;
	info_bmp.biWidth = nx;
	info_bmp.biHeight = ny;
	info_bmp.biPlanes = 1;
	info_bmp.biBitCount = 24;
	info_bmp.biCompression = 0;
	info_bmp.biSizeImage = size_of_image;
	info_bmp.biXPelsPerMeter = 0;
	info_bmp.biYPelsPerMeter = 0;
	info_bmp.biClrUsed = 0;
	info_bmp.biClrImportant = 0;

	FILE * pFile = fopen("input_file.bmp", "wb");				// create new .bmp file

	fwrite(&header_bmp, sizeof(bitmapfileheader), 1, pFile);	// write headers into .bmp file
	fwrite(&info_bmp, sizeof(bitmapinfoheader), 1, pFile);

	int rand_colour = 0;

	for (int i = 0; i < ny; i++)
	{
		for (int j = 0; j < (nx * 3) + staff_for_filling; j++) // writing random image into .bmp file
		{
			if (j > (nx * 3))
			{
				fprintf(pFile, "%c", 0);
				continue;
			}
			rand_colour = rand() % 256;
			fwrite(&rand_colour, 1, 1, pFile);
		}
	}
	fclose(pFile);
}

void create_txt(int nx, int ny, int max_number_of_commands, int number_of_lines)
{
	FILE* pFile = fopen("commands.txt", "w");				// create file with commands for test solutions
	while(number_of_lines)
	{
	int corrupt_command = 0;								// create random corrupted commands or correct command line
	int corrupt_coord_x = 0;
	int corrupt_coord_y = 0;
	int gen_coord_x = rand() % nx;
	int gen_coord_y = rand() % ny;
	int delta_gen_coord_x = rand() % (nx - gen_coord_x);
	int delta_gen_coord_y = rand() % (ny - gen_coord_y);

	switch (rand() % 5)											// choose one of five generation set of commands
	{
		case 1:
			corrupt_command = (rand() % max_number_of_commands) + 10;
			break;
		case 2:
			corrupt_coord_x = (rand() % nx) + nx;
			corrupt_coord_y = (rand() % ny) + ny;
			break;
		case 3:
			break;
		case 4:
			corrupt_command = (rand() % max_number_of_commands) + 10;
			corrupt_coord_x = (rand() % nx) + nx;
			corrupt_coord_y = (rand() % ny) + ny;
			break;
		case 0:
			if (nx > ny)
				delta_gen_coord_x = delta_gen_coord_y;
			else
				delta_gen_coord_y = delta_gen_coord_x;
			break;
		default:
			return;
	}

	fprintf(pFile, "%d %d %d %d ",											// write generated line into commands file
		gen_coord_x + corrupt_coord_x, gen_coord_y + corrupt_coord_y,
		gen_coord_x + delta_gen_coord_x, gen_coord_y + delta_gen_coord_y);

	for (int i = 0; i < ((rand() % max_number_of_commands)+1); i++)
	{
		fprintf(pFile, "%d ", ((rand() % (3+corrupt_command))+1));
	}
	fprintf(pFile, "%d\n", 4);
	number_of_lines--;
	}
	fclose(pFile);
}
