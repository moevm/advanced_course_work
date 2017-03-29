/*
	generate.c
        Калашников Максим
	Группа 6381
	2957851alwyd@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define VALUE_INTERVAL rand()%51 - 25

char SIGN[] = { '+', '-', '*', '/' };
char *FORMAT_STRING[] = { "%s%c%s", "(%s%c%s)", "(%s)%c%s", "%s%c(%s)" };


void shuffle(char array[28], int lastElement)
{
	if (lastElement == 0) return;
	int k = rand()%lastElement;
	char ch;

	for (int i = 0; i < lastElement*3; i++)
	{
		if (k != i)
		{
			ch = array[i%lastElement];
			array[i%lastElement] = array[k%lastElement];
			array[k%lastElement] = ch;
		}
	}
}

char *func(int strLength, char varsStr[], int level, int *maxLevel, short int finalLine)
{	
	char *result = (char *)malloc(256);
	if (*maxLevel > level)
	{
		if (rand()%101 > 40 || level == 1 || *maxLevel == 1)
		{
			sprintf(result, FORMAT_STRING[0], func(strLength, varsStr, level + 1, maxLevel, finalLine),
					  	  	  SIGN[rand()%2+2],
					 	 	  func(strLength, varsStr, level + 1, maxLevel, finalLine));
		} else
			sprintf(result, FORMAT_STRING[rand()%3 + 1], func(strLength, varsStr, level + 1, maxLevel, finalLine),
								     SIGN[rand()%2],
								     func(strLength, varsStr, level + 1, maxLevel, finalLine));		
		return result;
	}
		else
		{
			if (rand()%101 > 40)
			{
				sprintf(result, "%d%c%c", VALUE_INTERVAL, SIGN[rand()%4], varsStr[(*maxLevel)%strLength]);
			}
				else
				{
					sprintf(result, "%c", varsStr[(*maxLevel)%strLength]);
				}
			
			*maxLevel = *maxLevel - 1;

			return result;
		}
}

int main()
{
	srand(time(NULL));

	FILE *f = fopen("input_file", "w");
	int varNum = rand()%25 + 2;
	char usedChars[27];
	int t = rand()%101;
	
	for (int i = 0; i < varNum; i++)
	{
		usedChars[i] = t%26 + 'a';
		t++;
	}
	
	fprintf(f,"%c:=%d;\n", usedChars[0], rand()%101 - 50);
	
	for (int i = 1; i < varNum; i++)
	{
		int b = rand()%i + 1;
		
		if ( rand()%101 > 50) 
		{
			fprintf(f,"%c:=%s;\n", usedChars[i], func(b, usedChars, 1, &b, 0));
		}
		else fprintf(f,"%c:=%d;\n", usedChars[i], VALUE_INTERVAL);
		
		shuffle(usedChars, i - 1);
	}

	fprintf(f,"%s;\n", func(varNum, usedChars, 1, &varNum, 1));

	fclose(f);
	
	return 0;
}	
