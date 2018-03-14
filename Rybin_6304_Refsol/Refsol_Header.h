/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 22.05.2017
\version 3.0
*/

#include "Generate_Header.h"

#define RESULT "results.csv"	                                                //!< New file with results of programm
#define RESULT_HEADER "Group,Name,Surname,Patronymic,GitHub,Email,ExamResult\n" //!< Header for file with results
#define CHECK_REPEATS 1                                                         //!< Command 1
#define CHECK_BY_GROUP 2                                                        //!< Command 2
#define CHECK_BAD_RESULTS 3                                                     //!< Command 3
#define CHECK_GOOD_RESULTS 4                                                    //!< Command 4
#define SAVE_RESULTS 5                                                          //!< Command 5

/*!
\brief Compare two objects of struct Table
\param[in] a first ptr
\param[in] a second ptr
\return a->group - b->group
\ingroup Refsol
*/
int CompareTable(const Table* a, const Table* b);

/*!
\brief Parse string
\param[in] obj pointer to object to write result
\param[in] buf string to parse
\param[in] param <0> if parse sting to first table or <1> to second table
\return result of parsing
\ingroup Refsol
*/
int ParseString(Table* obj,char* buf,int param);

/*!
\brief Read input_file_1
\param[in] stream file with table1
\param[in] data pointer to object to read data
\return void
\ingroup Refsol
*/
void ReadTable1(FILE* stream,Vector* data);

/*!
\brief Read input_file_2
\param[in] stream file with table2
\param[in] data pointer to object to read data
\return void
\ingroup Refsol
*/
void ReadTable2(FILE* stream,Vector* data);

/*!
\brief Combine data from first & second files
\param[in] Data1 pointer to object with first table
\param[in] Data2 pointer to object with second table
\param[in] data pointer to object to combine data
\return void
\ingroup Refsol
*/
void CombineTables(Vector* data1,Vector* data2,Vector* data);

/*!
\brief Count students with mark less then 60% of max
\param[in] data struct Vector with info
\return void
\ingroup Refsol
*/
void CheckBadResults(Vector* data);

/*!
\brief Count students with max mark
\param[in] data struct Vector with info
\return void
\ingroup Refsol
*/
void CheckGoodResults(Vector* data);

/*!
\brief Check repeats in sorted readed data
\param[in] data struct Vector with data
\return void
\ingroup Refsol
*/
void CheckRepeats(Vector* data);

/*!
\brief Check data by group and marks last stident in group
\param[in] data struct Vector with data
\return void
\ingroup Refsol
*/
void CheckByGroup(Vector* data);

/*!
\brief Save results in new file results.txt
\param[in] data struct Vector with data
\return void
\ingroup Refsol
*/
void SaveResults(Vector* data);
