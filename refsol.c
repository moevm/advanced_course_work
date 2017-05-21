#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

typedef struct matrix{
    int Cols;
    int Lines;
    int** ptr;
    int isError;
    struct matrix *next;
} MATRIX;

typedef struct List{
    MATRIX* head;
    MATRIX* cur;
} List;

void openFile(FILE **f, char*);
void checkFile(FILE *f);
int checkCommands(char* argv, int* toTrans, int* toMulti, int* toRang);

void createMatrixList(FILE* f, List *List);
void newMatrix(List*, int**);
void checkColsMatrix(List* List, int lastCurCol, int CurCol);
int ListCorrect(List* List);

void transpose(List* List);

void rankOfAllMatrices(List* List);
void rankOfOneMatrix(MATRIX* curPtr);
int findNumber(float **m, int w, int h, int cur_coord);
void swapLines(float** m, int n1, int n2, int);
void swapCols(float** m, int n1, int n2, int);
int min(int, int);

int checkMulti(List* List);
void multiAllMatrices(List* List);
int** multiTwoMatrices(int** totalMatrix, int* totalMatrix_w, int totalMatrix_h, MATRIX*);
void printMatrixInFile(FILE *f, int**, int w, int h);

int main(int argc, char** argv){
    // Для каждоай матрицы должен создаваться двумерный массив, 
    // указатель на который лежит в списке матриц в поле ptr. printf
    List List;
    FILE* f;

    openFile(&f, argv[1]);
    checkFile(f);
    createMatrixList(f, &List);
    if (ListCorrect(&List) == 0)
        exit(1);

    int toTrans, toMulti, toRang;
    toTrans = toMulti = toRang = 0;

    if (argc == 3)
        checkCommands(argv[2], &toTrans, &toMulti, &toRang);
    else { 
        printf("Arguments not found!\n");
        return -1;
    }
    
    if (toRang != 0)
        rankOfAllMatrices(&List);

    if (toTrans != 0)
        transpose(&List);
    if (toMulti != 0)
        if (checkMulti(&List) != 0)
            multiAllMatrices(&List);
        else
            printf("Matrices not multiplied.\n");

    return 0;
}

void createMatrixList(FILE *f, List *List){
    char symb;
    fpos_t pos;
    int CurCol = -1;
    int lastCurCol = 0;
    int CurLine = 0;
    int indentNumber = 0;

    int **m = (int**)malloc(sizeof(int*));
        m[0] = (int*)malloc(sizeof(int));
    newMatrix(List, m);

    fgetpos(f, &pos);
    symb = fgetc(f);
    printf("Open create mtrix\n");

    while (1){
    	if (symb >= '0' && symb <= '9'){
            fsetpos(f, &pos);
            switch (indentNumber){
                case 0: 
        	        CurCol++;
                    //List->cur->Cols = CurCol + 1;
                    m[CurLine] = (int*)realloc(m[CurLine], (CurCol + 1) * sizeof(int));
                    List->cur->ptr = m;
                    fscanf(f, "%d", &m[CurLine][CurCol]);
                    break;
                case 1:
                    CurLine++;
                    lastCurCol = CurCol + 1;
                    CurCol = 0;
                    List->cur->Lines = CurLine + 1;
                    m = (int**)realloc(m, (CurLine+1) * sizeof(int*));
                    m[CurLine] = (int*)malloc(sizeof(int));
                    List->cur->ptr = m;
                    fscanf(f, "%d", &m[CurLine][CurCol]);
                    break;
                default: 
                    CurCol = CurLine = lastCurCol =  0;
                    m = (int**)malloc(sizeof(int*));
                    m[CurLine] = (int*)malloc(sizeof(int));
                    newMatrix(List, m);
                    fscanf(f, "%d", &m[CurLine][CurCol]);
                    break;
            }
            indentNumber = 0;
            symb = fgetc(f);
    	}	
        else 
    	if (symb == '\n'){
            indentNumber++;
            checkColsMatrix(List, lastCurCol, CurCol+1);
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
            checkColsMatrix(List, lastCurCol, CurCol+1);
            break;
        }
    }
}

void newMatrix(List* List, int** m){
    static int numberOfMatrices = 0;
    numberOfMatrices++;
    MATRIX* tmp = (MATRIX*)malloc(sizeof(MATRIX));
    if (numberOfMatrices == 1)
        List->head = tmp;
    else 
        List->cur->next = tmp;
    List->cur = tmp;
    List->cur->next = NULL;
    List->cur->ptr = m;
    List->cur->Lines = 1;
}

void checkColsMatrix(List* List, int lastCurCol, int CurCol){
    if (lastCurCol == 0){
        List->cur->isError = 0;
        List->cur->Cols = CurCol;
    }
    else 
        if (lastCurCol != CurCol){
            List->cur->isError = 1;
            List->cur->Cols = -1;
        }
}

void openFile(FILE **f, char* file_name){
    (*f) = fopen(file_name, "r");
    if ((*f) == NULL){
        printf("No file.\n");
        exit(-1);
    }
}

void checkFile(FILE *file){
    fseek(file, 0, SEEK_END);
    long pos = ftell(file);
    if (pos > 0)
        rewind(file);
    else {
        printf("File is empty.\n");
        exit(0);
    }
}

int ListCorrect(List* List){
    MATRIX* ptr = List->head;
    int matrixNumber = 0;
    int allMatricesCorrect = 1;
    while (ptr){
        matrixNumber++;
        if (ptr->isError == 1){
            printf("Fail with %d\n", matrixNumber);
            allMatricesCorrect = 0;
        }
        ptr = ptr->next;
    }
    return allMatricesCorrect;
}

void transpose(List* List){
    FILE *f = fopen("out_trans", "w");
    MATRIX* curPtr = List->head;
    while(curPtr){
        int **new = (int**)malloc(curPtr->Cols * sizeof(int*));
        for (int i = 0; i < curPtr->Cols; i++)
            new[i] = (int*)malloc(curPtr->Lines * sizeof(int));
            
        for (int i = 0; i < curPtr->Cols; i++){
            for (int j = 0; j < curPtr->Lines; j++){
                new[i][j] = curPtr->ptr[j][i];
            }
        }
        printMatrixInFile(f, new, curPtr->Lines, curPtr->Cols);
        // for (int i = 0; i < curPtr->Lines; i++)
            // free(curPtr->ptr[i]);
        free(new);
        curPtr = curPtr->next;
    }
    fclose(f);
}

void rankOfAllMatrices(List* List){
    MATRIX* curPtr = List->head;
    while (curPtr){
        rankOfOneMatrix(curPtr);
        curPtr = curPtr->next;  
    }
}

void rankOfOneMatrix(MATRIX* curPtr){
    int h = curPtr->Lines;
    int w = curPtr->Cols;
    float **new = (float**)malloc(h * sizeof(float*));
    for (int i = 0; i < h; i++)
        new[i] = (float*)malloc(w * sizeof(float));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            new[i][j] = curPtr->ptr[i][j];

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
    free(new);
    printf("Rang = %d\n", rank);
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
    float tmp;
    for (int i = 0; i < w; i++){
        tmp = m[n1][i];
        m[n1][i] = m[n2][i];
        m[n2][i] = tmp;
    }
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
    MATRIX* ptr = List->head;
    while (ptr->next){
        if(ptr->Cols != ptr->next->Lines)
            return 0;
        ptr = ptr->next;
    }
    return 1;
}

void multiAllMatrices(List* List){
    FILE *f = fopen("out_multi", "w");
    MATRIX* curPtr = List->head;
    int **totalMatrix = List->head->ptr;
    int totalMatrix_h = List->head->Lines;
    int totalMatrix_w = List->head->Cols;
    while (curPtr->next){
        totalMatrix = multiTwoMatrices(totalMatrix, &totalMatrix_w, totalMatrix_h, curPtr->next);
        curPtr = curPtr->next;
    }
    printMatrixInFile(f, totalMatrix, totalMatrix_w, totalMatrix_h);
    fclose(f);
}

int** multiTwoMatrices(int** totalMatrix, int* totalMatrix_w, int totalMatrix_h, MATRIX* m){
    int h_1 = totalMatrix_h;
    int w_1 = *totalMatrix_w;
    int w_2 = m->Cols;

    int **tmp = (int**)calloc(h_1, sizeof(int*));
    for (int i = 0; i < h_1; i++)
        tmp[i] = (int*)calloc(w_2, sizeof(int));
    
    for (int i = 0; i < h_1; i++)
        for (int j = 0; j < w_2; j++)
            for (int k = 0; k < w_1; k++)
                tmp[i][j] += totalMatrix[i][k] * m->ptr[k][j];

    *totalMatrix_w = m->Cols;
    free(totalMatrix);
    return tmp;
}

void printMatrixInFile(FILE *f, int** matrix, int w, int h){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            fprintf(f, "%d ", matrix[i][j]);
            if (j == w-1)
                fprintf(f, "\n");
        }
    }
    fprintf(f,"\n");
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