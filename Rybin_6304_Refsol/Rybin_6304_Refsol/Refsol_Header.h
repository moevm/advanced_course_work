/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generate_Header.h"

#define SIZE_OF_COMMANDS 10		//!< Start min lenth of vector reading commands

/*!
\brief Read commands from file
\param[in] commands File with commands
\return info Info about readed vector
\ingroup Refsol
*/
Vector Read_Commands(FILE* commands);

/*!
\brief Read Data from file
\param[in] steam1 File with table1
\param[in] steam2 File with table2
\return info Info about readed vector
\ingroup Refsol
*/
Vector Read_Files(FILE* stream1, FILE* stream2);

