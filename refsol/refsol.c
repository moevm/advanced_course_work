#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(push)
#pragma pack(2)									// alignment for two

typedef struct BITMAPFILEHEADER					// struct describing header .bmp file
{
	unsigned char   bfType[2];
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
} BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER					// struct containing info .bmp file
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

typedef struct RGBTRIPPLE						// struct describing one pixel of image
{
	unsigned char   rgbBlue;
	unsigned char   rgbGreen;
	unsigned char   rgbRed;
} RGBTRIPPLE;

typedef struct IMAGE							// struct describing and containing each element of .bmp file
{
	BITMAPFILEHEADER	header_of_image;
	BITMAPINFOHEADER	info_of_image;
	RGBTRIPPLE **		pixels_of_image;
} IMAGE;

void draw_Pixel(int x_coord, int y_coord, RGBTRIPPLE ** pixel);

void draw_Circle(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixel);

void fill_direct_Black(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixels);

void swap_direct_for_vertical(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixels);

void quad_swap(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixels);

void memory_free(int ny, RGBTRIPPLE ** pixel, IMAGE * current_bmp);

int main()
{
	FILE * pFile = fopen("input_file.bmp", "rb");			// open .bmp file for reading
	if (pFile == NULL)
		return 0;

	IMAGE * current_bmp = (IMAGE*)malloc(sizeof(IMAGE));	// reading headers into prepared struct
	fread(&current_bmp->header_of_image, sizeof(BITMAPFILEHEADER), 1, pFile);
	fread(&current_bmp->info_of_image, sizeof(BITMAPINFOHEADER), 1, pFile);

	int nx = current_bmp->info_of_image.biWidth;			// get size of image
	int ny = current_bmp->info_of_image.biHeight;

	int x0, y0, x1, y1;										// get coord of direct to change image
	scanf("%d%d%d%d", &x0, &y0, &x1, &y1);					// also check for wrong coords

	if (((x0 < 0) || (y0 < 0) || (x1 >(nx - 1)) || (y1 >(ny - 1)) || (x1 < x0) || (y1 < y0))
		|| ((x0 == x1) && (y0 == y1)))
	{
		printf("Fail with coords\n");
		fclose(pFile);

		free(current_bmp);
		return 0;
	}

	RGBTRIPPLE ** pixel = (RGBTRIPPLE**)malloc(sizeof(RGBTRIPPLE*) * ny);	// allocated pixel struct for image
	for (int i = 0; i < ny; i++)
		pixel[i] = (RGBTRIPPLE*)malloc(sizeof(RGBTRIPPLE) * nx);

	int staff_for_filling = 4 - ((nx * 3) % 4);								// calc alignment bytes
	if (staff_for_filling == 4)
		staff_for_filling = 0;

	for (int i = 0; i < ny; i++)											// writing each pixel (RGB) into allocated struct
	{
		for (int j = 0; j < nx; j++)
		{
			pixel[i][j].rgbBlue = getc(pFile);
			pixel[i][j].rgbGreen = getc(pFile);
			pixel[i][j].rgbRed = getc(pFile);
		}
		for (int k = 0; k < staff_for_filling; k++)							// skip alignment bytes
			getc(pFile);
	}
	current_bmp->pixels_of_image = pixel;

	fclose(pFile);

	int active = 1;
	int command = 0;

	while (active)
	{
		scanf("%d", &command);												// get command and choose operation
		switch (command)
		{
			case 1:
				swap_direct_for_vertical(x0, y0, x1, y1, ny, pixel);
				break;
			case 2:
				quad_swap(x0, y0, x1, y1, ny, pixel);
				break;
			case 3:
				draw_Circle(x0, y0, x1, y1, ny, pixel);
				break;
			case 4:
				active = 0;
				break;
			default:
				printf("Fail with commands\n");							// check for wrong commands
				memory_free(ny, pixel, current_bmp);
				return 0;
		}
	}

	pFile = fopen("output_file.bmp", "wb");										// create new file with actually changes

	fwrite(&current_bmp->header_of_image, sizeof(BITMAPFILEHEADER), 1, pFile);  // write headers into new .bmp
	fwrite(&current_bmp->info_of_image, sizeof(BITMAPINFOHEADER), 1, pFile);
	for (int i = 0; i < ny; i++)												// write changed image into new .bmp
	{
		for (int j = 0; j < nx; j++)
			fwrite(&current_bmp->pixels_of_image[i][j], 1, 3, pFile);
		for (int k = 0; k < staff_for_filling; k++)
			fprintf(pFile, "%c", 0);
	}

	fclose(pFile);

	memory_free(ny, pixel, current_bmp);					// free
  	return 0;
}

void draw_Pixel(int x_coord, int y_coord, RGBTRIPPLE ** pixel) // this draw white pixel of the coords
{
	pixel[y_coord][x_coord].rgbRed = 255;
	pixel[y_coord][x_coord].rgbGreen = 255;
	pixel[y_coord][x_coord].rgbBlue = 255;
}

void draw_Circle(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixel) // draw circle by algorithm of bresenham's
{
	int x_coord_centre;
	int y_coord_centre;
	int x, y, delta;
	int r_circle;
	int around_quad = 1;
	int delta_quad = x1 - x0 - 1;

	if ((x1 - x0) != (y1 - y0))									// if direct not quad - fill direct black
	{
		fill_direct_Black(x0, y0, x1, y1, ny, pixel);
		return;
	}

	if ((delta_quad) % 2)										// draw circle around point or 2x2 quad
		around_quad = 0;

	x_coord_centre = x0 + delta_quad / 2 + 1;					// calc coord centre of circle
	y_coord_centre = ny - (y0 + delta_quad /2) - 2;
	r_circle = delta_quad / 2 + !around_quad;					// calc radius and delta to rastr view circle
	x = 0;
	y = r_circle;
	delta = 3 - 2 * r_circle;

	while (x<y)
	{	// draw circle
		draw_Pixel(x_coord_centre + x, y_coord_centre + y + around_quad, pixel);
		draw_Pixel(x_coord_centre + x, y_coord_centre - y, pixel);
		draw_Pixel(x_coord_centre - x - around_quad, y_coord_centre + y + around_quad, pixel);
		draw_Pixel(x_coord_centre - x - around_quad, y_coord_centre - y, pixel);
		draw_Pixel(x_coord_centre + y, y_coord_centre + x + around_quad, pixel);
		draw_Pixel(x_coord_centre + y, y_coord_centre - x, pixel);
		draw_Pixel(x_coord_centre - y - around_quad, y_coord_centre + x + around_quad, pixel);
		draw_Pixel(x_coord_centre - y - around_quad, y_coord_centre - x, pixel);

		if (delta<0)						// change delta if we need to shift draw to left
			delta += 4 * x + 6;
		else {
			delta += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}

	if (x == y)								// if x = y we draw yet four pixels
	{
		draw_Pixel(x_coord_centre + x, y_coord_centre + y + around_quad, pixel);
		draw_Pixel(x_coord_centre + x, y_coord_centre - y, pixel);
		draw_Pixel(x_coord_centre - x - around_quad, y_coord_centre + y + around_quad, pixel);
		draw_Pixel(x_coord_centre - x - around_quad, y_coord_centre - y, pixel);
	}
}

void fill_direct_Black(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixels) // just... fill direct black
{
	x1 += 1;
	y0 = ny - y0 - 1;
	y1 = ny - y1 - 1;
	for (int i = 0; i <= (y0 - y1); i++)
		memset(&pixels[y1 + i][x0], 0, (x1 - x0) * 3);
}

void swap_direct_for_vertical(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixels) // swap direct for vertical
{
	x1 += 1;
	y0 = ny - y0;
	y1 = ny - y1;
	RGBTRIPPLE * buffer = (RGBTRIPPLE*)malloc(sizeof(RGBTRIPPLE) * (x1-x0));
	for(int i = 0; i<=((y0-y1)/2); i++)
	{
		memcpy(buffer, &pixels[y1+i-1][x0], (x1 - x0) * 3);						// copy plot of string to buffer
		memcpy(&pixels[y1+i-1][x0], &pixels[y0 - i - 1][x0], (x1 - x0) * 3);	// then copy [i] plot of string to inverse of [i]
		memcpy(&pixels[y0 - i - 1][x0], buffer, (x1 - x0) * 3);					// restore plot of string from buf
	}
	free(buffer);
}

void quad_swap(int x0, int y0, int x1, int y1, int ny, RGBTRIPPLE ** pixels)   // divide direct on four part and swap it diagonally
{
	x1 += 1;
	y0 = ny - y0;
	y1 = ny - y1 - 1;
	int delta_y = (y0 - y1);
	int delta_x = (x1 - x0);
	RGBTRIPPLE * buffer = (RGBTRIPPLE*)malloc(sizeof(RGBTRIPPLE) * (delta_x/2));
	for (int i = 0; i < delta_y / 2; i++)
	{	// divide on four part, copy upper left plot string to lower right plot direct, and the same thing is the other way around
		memcpy(buffer, &pixels[y0 - (delta_y / 2) + i][x1 - (delta_x / 2)], delta_x / 2 * 3);
		memcpy(&pixels[y0 - (delta_y / 2) + i][x1 - (delta_x / 2)], &pixels[y1 + i][x0], delta_x / 2 * 3);
		memcpy(&pixels[y1 + i][x0], buffer, delta_x / 2 * 3);
		memcpy(buffer, &pixels[y0 - (delta_y / 2) + i][x0], delta_x / 2 * 3);
		memcpy(&pixels[y0 - (delta_y / 2) + i][x0], &pixels[y1+i][x1-(delta_x/2)], delta_x / 2 * 3);
		memcpy(&pixels[y1 + i][x1-(delta_x/2)], buffer, delta_x / 2 * 3);
	}
	free(buffer);
}

void memory_free(int ny, RGBTRIPPLE ** pixel, IMAGE * current_bmp) // free all allocated for .bmp file memory
{
	for (int i = 0; i < ny; i++)
		free(pixel[i]);
	free(pixel);
	free(current_bmp);
}
