#include <stdio.h>

main()
{
	FILE *file;
	file = fopen("userout.txt","w");
	fputs("ERROR",file);
	fclose(file);
    return 0;
}
