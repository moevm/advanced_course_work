/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#define INPUT1 "input_file_1.csv" //!< First table
#define INPUT2 "input_file_2.csv" //!< Second table

#include "Generate_Header.h"

/*!
\brief Creates new object of struct Table
\param[in] new_element Pointer to object to initialize
\return void
\ingroup Refsol
*/
void TableCreate(Table* new_element);

/*!
\brief Read Data from file
\param[in] steam1 File with table1
\param[in] steam2 File with table2
\return info Info about readed vector
\ingroup Refsol
*/
Vector ReadFiles(FILE* stream1, FILE* stream2);

