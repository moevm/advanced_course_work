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

#define Max_Lenth_array_commands 10		//!< Max lenth of generating array of commands
#define Max_Lenth_token 15				//!< Max lenth of generating random token
#define Min_Lenth_token 5				//!< Min lenth of generating random token
#define Max_Group 1000					//!< Max generating group number
#define Max_Exam_result 5				//!< Max generating exam result
#define Max_lines 20					//!< Max lines in generating tables
#define Min_lines 5						//!< Min lines in generating tables
#define Max_Lenth_field 30				//!< Max lenth of created fields in struct Table 

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
	bool check;			//!< Check repeats in vector

} Table;

/*!
\struct
\brief Struct Array for return information about vector
*/
typedef struct Vector
{
	int lenth;				//!< Lenth of created random vector of fields
	Table* random_vector;		//!< Pointer to created random vector of fields
}Vector;

/*!
\brief Generates vector of integers
\param[in] commands_list Pointer to file to write commands
\return void
\ingroup Generate
*/
void put_random_commands(FILE* commands_list);

/*!
\brief Generates random token
\param[in] a Type of random, 0 if just token, 1 if @Email token, 2 if @GitHub token
\return random_token Pointer to random token
\ingroup Generate
*/
char* generate_token(int a);

/*!
\brief Initialize's object of strcut Table
\param[in] element Object to initialize
\return void
\ingroup Data
*/
void constructor_element(Table element);

/*!
\brief Generates random vector of fields
\param[in] max Max lines in generating tables
\param[in] min Min lines in generating tables
\return info Sturct Vector this information about generated vector
\ingroup Data
*/
Vector generate_random_vector(int max,int min);