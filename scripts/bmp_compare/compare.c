#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	FILE * pFile = fopen("output_file.bmp", "rb");		// open original .bmp file from true solution
	if (!pFile)
	{
		printf("Orginal .bmp file does not exist.\n");	// return 1 and message if file doesn't exists
		return 1;										
	}

	fseek(pFile, 0L, SEEK_END);	
	unsigned int size_on_bite = ftell(pFile);			// calc size of image with help ftell in the end of file
	fseek(pFile, 0L, SEEK_SET);

	char* original_bmp_bites = (char*)malloc(size_on_bite);
	fread(original_bmp_bites, size_on_bite, 1, pFile);	// get all bytes from file in array

	fclose(pFile);

	pFile = fopen("my_solution.bmp", "rb");				// open comparing .bmp file from custom solution
	if (!pFile)
	{
		printf("Comparing .bmp file does not exist.\n"); // if file doesn't exists return 1 and message
		return 1;
	}

	fseek(pFile, 0L, SEEK_END);
	if (ftell(pFile) != size_on_bite)
	{			
		free(original_bmp_bites);						// calc size on bytes custom .bmp and compare with original .bmp size
		fclose(pFile);									// if not equal - return 2 and message
		printf("Size of comparing .bmp files not equal.\n");
		return 2;
	}
	fseek(pFile, 0L, SEEK_SET);

	char* tests_bmp_bites = (char*)malloc(size_on_bite); // get all bytes custom .bmp into array
	fread(tests_bmp_bites, size_on_bite, 1, pFile);

	if (memcmp(tests_bmp_bites, original_bmp_bites, size_on_bite)) // compare data of arrays original and custom .bmp files
	{
		fclose(pFile);											// if not equal - return 3 and message
		free(original_bmp_bites);
		free(tests_bmp_bites);
		printf("Data of comparing .bmp files not equal.\n");
		return 3;
	}
														// if all tests done - files are equal, good job
	fclose(pFile);
	free(original_bmp_bites);
	free(tests_bmp_bites);
	printf(".bmp files are equal.\n");
	return 0;
}
