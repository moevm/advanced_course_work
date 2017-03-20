/*!
\file
\brief Random functions

\author Rybin Aleksandr 1 course 2 half
\date 15.03.2017
\version 1.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*!
\brief Generates array of integers
\param[in] commands_list Pointer to file to write commands
\return void 
\ingroup Generate_Random_Data
*/
void put_random_array(FILE* commands_list)
{
	int lenth = rand() % 10;
	
	for (int i = 0; i < lenth; i++)
		fprintf(commands_list, "%d ", -1 + rand() % 7);
}

/*!
\brief Generates random token(char*)
\param[in] a Type of random, 0 if just token, 1 if Email token, 2 if GitHub token
\return random_token Pointer to random token
\ingroup Generate_Random_Data
*/
char* generate_token(int a)
{
	int lenth = 5 + rand() % 10;
	char* random_token = (char*)malloc(sizeof(char) * (lenth + 9));

	for (int i = 0; i < lenth - 1; i++)
	{
		random_token[i] = (char)(97 + rand() % 25);
	}
	random_token[lenth - 1] = '\0';

	switch (a)
	{
	case 1:
	{
		strncat(random_token, "@Email", 6);
		random_token[lenth + 8] = '\0';
		break;
	}
	case 2:
	{
		strncat(random_token, "@GitHub", 7);
		random_token[lenth + 8] = '\0';
		break;
	}
	default: break;
	}

	return random_token;
}