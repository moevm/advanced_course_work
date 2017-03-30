/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"

#define Sizeof_Commands 10


/*!
\brief Read commands from file
\param[in] commands Pointer to file with commands
\return info Info about vector
\ingroup Refsol
*/
Vector Read_Commands(FILE* commands);

