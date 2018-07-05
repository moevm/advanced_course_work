#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#define size_of_new_mem_block 8

typedef struct Matrix{
    int Cols;
    int Lines;
    int** ptr;
    int isError;
} MATRIX;

typedef struct Node{
    MATRIX data;
    struct Node *next;
} NODE;

typedef struct List{
    NODE *head;
    NODE *cur;
} List;

int openFile(FILE **f, char*);
int checkFile(FILE *f);
int checkCommands(char* argv, int* toTrans, int* toMulti, int* toRang);

void createMatrixList(FILE* f, List *List);
void newNode(List*);
void initMatrixData(MATRIX* m_data, int** m);
void changeMatrixDataPtr(MATRIX* m_data, int** m);
void checkColsMatrix(MATRIX* m_data, int lastCurCol, int CurCol);
int ListCorrect(List* List);
int isMatrixCorrect(MATRIX m_data);

void transposeAllMatrices(List* List, FILE* f);
MATRIX* transposeOneMatrix(MATRIX m_data);

void rankOfAllMatrices(List* List);
int rankOfOneMatrix(MATRIX curPtr);
int findNumber(float **m, int w, int h, int cur_coord);
void swapLines(float** m, int n1, int n2, int);
void swapCols(float** m, int n1, int n2, int);
int min(int, int);

int checkMulti(List* List);
void multiAllMatrices(List* List, FILE* f);
MATRIX* multiTwoMatrices(MATRIX* totalMatrix, MATRIX m);
void printMatrixInFile(FILE *f, int**, int w, int h);

int main(int argc, char** argv){
    // Для каждоай матрицы должен создаваться двумерный массив, 
    // указатель на который лежит в списке матриц в поле ptr. printf
    char file_names[2][12] = {
        "ref_trans",
        "ref_multi",
    };
    List List;
    List.head = NULL;
    List.cur = NULL;
    FILE* f;

    if (openFile(&f, argv[1]))
    {
        printf("No file.\n");
        return 1;
    }
    if (checkFile(f))
    {
        printf("File is empty.\n");
        return 1;
    }
    createMatrixList(f, &List);
    if (ListCorrect(&List) == 0)
        return 1;

    int toTrans, toMulti, toRang;
    toTrans = toMulti = toRang = 0;

    if (argc == 3)
        checkCommands(argv[2], &toTrans, &toMulti, &toRang);
    else { 
        printf("Arguments not found!\n");
        return 1;
    }
    
    if (toRang)
        rankOfAllMatrices(&List);

    if (toTrans)
    {
        FILE *tr = fopen(file_names[0], "w");
        transposeAllMatrices(&List, tr);
        fclose(tr);
    }
    if (toMulti != 0)
    {
        if (checkMulti(&List)){
            FILE *file_mul = fopen(file_names[1], "w");
            multiAllMatrices(&List, file_mul);
            fclose(file_mul);
        }
        else
            printf("Matrices are not multiplied.\n");
    }
    return 0;
}

int checkCommands(char* commands, int* toTrans, int* toMulti, int* toRang){
    int length = strlen(commands);
    int pos_1, pos_2, pos_3, pos_4;
    pos_1 = pos_2 = pos_3 = pos_4 = -1;

    for (int i = 0; i < length; i++){
        switch (commands[i]){
            case '1':
                if (pos_1 == -1)
                    pos_1 = i;
                break;
            case '2':
                if (pos_2 == -1)
                    pos_2 = i;
                break;
            case '3':
                if (pos_3 == -1)
                    *toRang = 1;
                break;
            case '4':
                pos_4 = i;
                if (pos_1 < pos_4 && pos_1 != -1)  
                    *toMulti = 1;
                if (pos_2 < pos_4 && pos_2 != -1)
                    *toTrans = 1;
                break;
            default:
                printf("Invalid arguments.\n");
                return -1;
        }
    }
    return 0;
}

void createMatrixList(FILE *f, List *List){
    char symb;
    int** m;
    fpos_t pos;
    int CurCol, lastCurCol, CurLine;
    CurCol = lastCurCol = CurLine = 0;
    int indentNumber = 2;
    fgetpos(f, &pos);
    symb = fgetc(f);

    while (1){
    	if (symb >= '0' && symb <= '9'){
            fsetpos(f, &pos);
            switch (indentNumber){
                case 0: 
        	        CurCol++;
                    if (CurCol % size_of_new_mem_block == 0)
                        m[CurLine] = (int*)realloc(m[CurLine], (CurCol + size_of_new_mem_block) * sizeof(int));
                    changeMatrixDataPtr(&(List->cur->data), m);
                    fscanf(f, "%d", &m[CurLine][CurCol]);
                    break;
                case 1:
                    CurLine++;
                    lastCurCol = CurCol + 1;
                    CurCol = 0;
                    List->cur->data.Lines = CurLine + 1;
                    m = (int**)realloc(m, (CurLine + 1) * sizeof(int*));
                    m[CurLine] = (int*)malloc(size_of_new_mem_block * sizeof(int));
                    changeMatrixDataPtr(&(List->cur->data), m);
                    fscanf(f, "%d", &m[CurLine][CurCol]);
                    break;
                default: 
                    CurCol = CurLine = lastCurCol =  0;
                    m = (int**)malloc(sizeof(int*));
                    m[CurLine] = (int*)malloc(size_of_new_mem_block * sizeof(int));
                    newNode(List);
                    initMatrixData(&(List->cur->data), m);
                    fscanf(f, "%d", &m[CurLine][CurCol]);
                    break;
            }
            indentNumber = 0;
            symb = fgetc(f);
    	}	
        else 
    	if (symb == '\n'){
            indentNumber++;
            checkColsMatrix(&(List->cur->data), lastCurCol, CurCol+1);
            fgetpos(f, &pos);
            symb = fgetc(f);
    	}
        else 
        if (symb == ' '){
            fgetpos(f, &pos);
            symb = fgetc(f);
        }
        else
        if (symb == '-'){
            symb = fgetc(f);
        }
        else 
        if (symb == EOF){
            checkColsMatrix(&(List->cur->data), lastCurCol, CurCol+1);
            break;
        }
    }
}

void changeMatrixDataPtr(MATRIX* m_data, int** m){
    m_data->ptr = m;
}

void newNode(List* List){
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->next = NULL;
    if (List->head == NULL)
        List->head = new_node;
    else 
        List->cur->next = new_node;
    List->cur = new_node;
}

void initMatrixData(MATRIX* m_data, int** m){
    m_data->ptr = m;
    m_data->Lines = 1;
    m_data->Cols = 0;
    m_data->isError = 0;
}

void checkColsMatrix(MATRIX* cur_m_data, int lastCurCol, int CurCol){
    if (lastCurCol == 0){
        cur_m_data->isError = 0;
        cur_m_data->Cols = CurCol;
    }
    else 
        if (lastCurCol != CurCol){
            cur_m_data->isError = 1;
            cur_m_data->Cols = -1;
        }
}

int openFile(FILE **f, char* file_name){
    (*f) = fopen(file_name, "r");
    if ((*f) == NULL)
        return 1;
    else
        return 0;
}

int checkFile(FILE *file){
    fseek(file, 0, SEEK_END);
    long pos = ftell(file);
    if (pos > 0){
        rewind(file);
        return 0;
    }
    else 
        return 1;
}

int ListCorrect(List* List){
    NODE* ptr = List->head;
    int matrixNumber = 0;
    int allMatricesCorrect = 1;
    while (ptr){
        matrixNumber++;
        if (!isMatrixCorrect(ptr->data)){
            printf("Fail with %d\n", matrixNumber);
            allMatricesCorrect = 0;
        }
        ptr = ptr->next;
    }
    return allMatricesCorrect;
}

int isMatrixCorrect(MATRIX m_data){
    if (m_data.isError == 1)
        return 0;
    else 
        return 1;
}

void transposeAllMatrices(List* List, FILE* f){
    NODE *curPtr = List->head;
    while(curPtr){
    MATRIX* trans_matrix = transposeOneMatrix(curPtr->data);
        printMatrixInFile(f, trans_matrix->ptr, trans_matrix->Cols, trans_matrix->Lines);
        if (curPtr->next != NULL)
            fprintf(f, "\n\n");
        for (int i = 0; i < trans_matrix->Lines; i++)
            free(trans_matrix->ptr[i]);
        free(trans_matrix);
        curPtr = curPtr->next;
    }
}

MATRIX* transposeOneMatrix(MATRIX m_data){
    MATRIX *tmp = (MATRIX*)malloc(sizeof(m_data));
    tmp->Cols = m_data.Lines;
    tmp->Lines = m_data.Cols;
    tmp->isError = m_data.isError;
    tmp->ptr = (int**)malloc(tmp->Lines * sizeof(int*));
    for (int i = 0; i < tmp->Lines; i++)
        tmp->ptr[i] = (int*)malloc(tmp->Cols * sizeof(int));
        
    for (int i = 0; i < tmp->Lines; i++){
        for (int j = 0; j < tmp->Cols; j++){
            tmp->ptr[i][j] = m_data.ptr[j][i];
        }
    }
    return tmp;
}

void rankOfAllMatrices(List* List){
    int rank = 0;
    NODE* curPtr = List->head;
    while (curPtr){
        rank = rankOfOneMatrix(curPtr->data);
        printf("Rang = %d\n", rank);
        curPtr = curPtr->next;  
    }
}

int rankOfOneMatrix(MATRIX m_data){
    int h = m_data.Lines;
    int w = m_data.Cols;
    float **new = (float**)malloc(h * sizeof(float*));
    for (int i = 0; i < h; i++)
        new[i] = (float*)malloc(w * sizeof(float));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            new[i][j] = m_data.ptr[i][j];

    for (int i = 0; i < min(w, h); i++){
        if (findNumber(new, w, h, i) == -1)
            break;
        float divider = new[i][i];
        for (int k = 0; k < w; k++){
            new[i][k] /= divider;
        }

        for (int j = i+1; j < w; j++){ // домножение столбцов
            float factor  = -new[i][j];
            for (int k = i; k < h; k++){
                new[k][j] += new[k][i] * factor;    
            }
        }
        for (int j = i+1; j < h; j++){ //домножение строк можно убрать или просто заменить нулями
            float factor = -new[j][i];
            for (int k = i; k < w; k++){
                new[j][k] += new[i][k] * factor;
            }
        }
    }
    int rank = 0;
    for(int i = 0; i < min(w, h); i++){
        if (fabs(new[i][i]) > FLT_EPSILON)
            rank++;
    }
    for (int i = 0; i < h; i++)
        free(new[i]);
    free(new);
    return rank;
}

int min(int a, int b){
    if (a > b)
        return b;
    else 
        return a;
}

int findNumber(float **m, int w, int h, int cur_coord){
    for (int i = cur_coord; i < w; i++){
        for (int j = cur_coord; j < h; j++){
            if (fabs(m[j][i]) > FLT_EPSILON){
                if (i == cur_coord && j == cur_coord)
                    return 0;
                else
                if (i == cur_coord && j != cur_coord){
                    swapLines(m, cur_coord, j, w);
                    return 0; 
                }
                else
                if(i != cur_coord && j == cur_coord){
                    swapCols(m, cur_coord, i, h);
                    return 0;
                }
                if (i != cur_coord && j != cur_coord){
                    swapLines(m, cur_coord, j, w);
                    swapCols(m, cur_coord, i, h);
                    return 0;
                }
            }
        }
    }
    return -1;
}

void swapLines(float** m, int n1, int n2, int w){
    float *tmp;
    tmp = m[n1];
    m[n1] = m[n2];
    m[n2] = tmp;
}

void swapCols(float** m, int n1, int n2, int h){
    float tmp;
    for (int i = 0; i < h; i++){
        tmp = m[i][n1];
        m[i][n1] = m[i][n2];
        m[i][n2] = tmp;
    }
}

int checkMulti(List* List){
    NODE* ptr = List->head;
    while (ptr->next){
        if(ptr->data.Cols != ptr->next->data.Lines)
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

void multiAllMatrices(List* List, FILE* f){
    NODE* curPtr = List->head;
    MATRIX* totalMatrix = (MATRIX*)malloc(sizeof(MATRIX));
    totalMatrix->Lines = List->head->data.Lines;
    totalMatrix->Cols = List->head->data.Cols;
    totalMatrix->isError = List->head->data.isError;
    totalMatrix->ptr = (int**)malloc(totalMatrix->Lines * sizeof(int*));
    for (int i = 0; i < totalMatrix->Lines; i++)
        totalMatrix->ptr[i] = (int*)malloc(totalMatrix->Cols * sizeof(int));
    
    for (int i = 0; i < totalMatrix->Lines; i++)
        for (int j = 0; j < totalMatrix->Cols; j++)
            totalMatrix->ptr[i][j] = List->head->data.ptr[i][j];

    while (curPtr->next){
        multiTwoMatrices(totalMatrix, curPtr->next->data);
        curPtr = curPtr->next;
    }
    printMatrixInFile(f, totalMatrix->ptr, totalMatrix->Cols, totalMatrix->Lines);
    for (int i = 0; i < totalMatrix->Lines; i++)
        free(totalMatrix->ptr[i]);
    free(totalMatrix);
}

MATRIX* multiTwoMatrices(MATRIX* totalMatrix, MATRIX m){
    int h_1 = totalMatrix->Lines;
    int w_1 = totalMatrix->Cols;
    int w_2 = m.Cols;

    int **tmp = (int**)calloc(h_1, sizeof(int*));
    for (int i = 0; i < h_1; i++)
        tmp[i] = (int*)calloc(w_2, sizeof(int));
    
    for (int i = 0; i < h_1; i++)
        for (int j = 0; j < w_2; j++)
            for (int k = 0; k < w_1; k++)
                tmp[i][j] += totalMatrix->ptr[i][k] * m.ptr[k][j];

    totalMatrix->Cols = m.Cols;
    for (int i = 0; i < h_1; i++)
        free(totalMatrix->ptr[i]);
    free(totalMatrix->ptr);
    totalMatrix->ptr = tmp;
    return totalMatrix;
}

void printMatrixInFile(FILE *f, int** matrix, int w, int h){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            fprintf(f, "%d ", matrix[i][j]);
            if (j == w-1 && i != h-1)
                fprintf(f, "\n");
        }
    }
}