/*!
\file
\brief Generate Header
\author Rybin Aleksandr 1 course 2 half
\date 21.05.2017
\version 3.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LENGTH_ARRAY_COMMANDS 10	                           	//!< Max length of generating array of commands
#define MAX_LENGTH_TOKEN 15				                           	//!< Max length of generating random token
#define MIN_LENGTH_TOKEN 5				                  			//!< Min length of generating random token
#define MAX_GROUP 1000					              				//!< Max generating group number
#define MAX_EXAM_RESULT 5	                          				//!< Max generating exam result
#define MAX_LINES 15			                            		//!< Max lines in generating tables
#define MIN_LINES 5					                       			//!< Min lines in generating tables
#define HEADER1 "Name,Surname,Patronymic,GitHub,Email,Group\n"      //!< Header for first table
#define HEADER2 "Name,Surname,Exam_mark\n"					        //!< Header for second table
#define INPUT1 "input_file_1.csv"		                            //!< First table
#define INPUT2 "input_file_2.csv"		                            //!< Second table
#define COMMANDS "commands.txt"			                            //!< File with commands

/*!
\struct
\brief Struct Table for generating data, or read data from tables
*/
typedef struct Table
{
	char name[MAX_LENGTH_TOKEN];				                    //!< Name of student
	char surname[MAX_LENGTH_TOKEN];			                        //!< Surame of student
	char patronymic[MAX_LENGTH_TOKEN];		                        //!< Patronymic of student
	char GitHub_account[MAX_LENGTH_TOKEN];	                        //!< GitHub account of student
	char Email[MAX_LENGTH_TOKEN];	                                //!< Student's email
	int group;				                                        //!< Student's group
	int exam_result;		                                        //!< Mark for exam
	int flag;				                                        //!< If repeats 1, if last in group (-1), default 0
}Table;

/*!
\struct
\brief Struct Array for return information about vector
*/
typedef struct Vector
{
	int len;				                                        //!< Length of vector
	Table vector_ptr[MAX_LINES];		                            //!< Pointer to struct Table arrayr
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
\param[in] random_token Pointer to string to write random token
\return void
\ingroup Generate
*/
void GenerateToken(char* random_token);

/*!
\brief Generates random vector of fields
\return info Sturct Vector whith information about generated vector
\ingroup Generate
*/
Vector GenerateRandomVector();
