/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"

#define Sizeof_Commands 10		//!< Start min lenth of vector reading commands
#define Max_Lenth_field 50		//!< Lenth of readed field
#define Max_Lenth_Line	1000	//!< Max lenth of line in reading tables
/*!
\brief Initialize's object of struct Table
\param[in] element Object to initialize
\return void
\ingroup Refsol
*/
void Table_Constructor(Table element);

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

