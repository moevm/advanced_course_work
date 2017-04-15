/*!
\file
\brief Generate Header
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH_ARRAY_COMMANDS 10		//!< Max length of generating array of commands
#define MAX_LENGTH_TOKEN 15				//!< Max length of generating random token
#define MIN_LENGTH_TOKEN 5				//!< Min length of generating random token
#define MAX_GROUP 1000					//!< Max generating group number
#define MAX_EXAM_RESULT 5				//!< Max generating exam result
#define MAX_LINES 20					//!< Max lines in generating tables
#define MIN_LINES 15						//!< Min lines in generating tables
#define HEADER1 "Name,Surname,Patronymic,GitHub,Email,Group\n" //!< Header for first table
#define HEADER2 "Name,Surname,Exam_mark\n"					   //!< Header for second table

/*!
\struct
\brief Struct Table for generating data, or read data from tables
*/
typedef struct Table
{
	char* name;				//!< Name of student
	char* surname;			//!< Surame of student
	char* patronymic;		//!< Patronymic of student
	char* GitHub_account;	//!< GitHub account of student
	char* Email;			//!< Student's email
	int group;				//!< Student's group
	int exam_result;		//!< Mark for exam
	bool check;				//!< Check repeats in vector

} Table;

/*!
\struct
\brief Struct Array for return information about vector
*/
typedef struct Vector
{
	int lenth;				//!< Lenth of vector 
	Table* vector_ptr;		//!< Pointer to vector
}Vector;

/*!
\brief Generates vector of integers
\param[in] commands_list Pointer to file to write commands
\return void
\ingroup Generate
*/
void PutRandomCommands(FILE* commands_list);

/*!
\brief Generates random token
\param[in] a Type of random, 0 if just token, 1 if @Email token, 2 if @GitHub token
\return random_token Pointer to random token
\ingroup Generate
*/
char* GenerateToken(int a);

/*!
\brief Generates random vector of fields
\return info Sturct Vector whith information about generated vector
\ingroup Generate
*/
Vector GenerateRandomVector();
