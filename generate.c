/*
	gen.c
    Фиалковский Максим
	Группа 6381
	makometr@yandex.ru
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define FILES_NUMBER 1

void generateCorrectMatrix(FILE *f, int isCorrectMultiplication, int i); // Генерирует и записывает в файл правильную матрицу.
// Каждая строчка начинается с числа и заканчивается числом.
void generateIncorrectMatrix(FILE *f); // генерирует и записывает в файл неправильную матрицу.
void generateIndent(FILE *f, int isCorrectIndent, int numberOfMatrix, int currentMatrix); // Вставляют отступ.
int randIntTuning(); // Настраиваемый генератор чисел от -20 до 20.

char* genFileName(int, char*);

int main(){
    srand(time(NULL));
    char name[12] = "testcase_";

    for (int i = 0; i < FILES_NUMBER; i++){
        genFileName(i+1, name);
        // printf("%s\n", name);

        FILE *f = fopen(name, "w");
        int isCorrectMatrix = rand() % 3; // Параметр генерации, отвечающий за генерирование матриц с ошибками или без.
        int numberOfMatrix = 2 + rand() % 6; // Количество генерируемых матриц. 2 - 7
        int isCorrectIndent = rand() % 2; // Параметр, отвечающий за отступ между матрицами. 0 - 1
        int isCorrectMultiplication; // Парметр генерации, отвечающий за генерацию умножаемых матриц. 0 - 1
        if (isCorrectMatrix == TRUE)
            isCorrectMultiplication = rand() % 3;

        switch (isCorrectMatrix){
            case 1:
            case 2:
                for (int i = 0; i < numberOfMatrix; i++){
                    generateCorrectMatrix(f, isCorrectMultiplication, i);
                    generateIndent(f, isCorrectIndent, numberOfMatrix, i);
                }
                break;
            case FALSE:
                    for (int i = 0; i < numberOfMatrix; i++){
                    generateIncorrectMatrix(f);
                    generateIndent(f, isCorrectIndent, numberOfMatrix, i);
                }

        }
        fclose(f);
    }
    return 0;
}

void generateCorrectMatrix(FILE *f, int isCorrectMultiplication, int currentNumberOfMatrix){
    static int lines;
    static int cols;
    fpos_t pos;
    fgetpos(f, &pos);

    if (isCorrectMultiplication == FALSE || currentNumberOfMatrix == 0)
        lines = 2 + ((rand() % 100) * (rand() % 100)) % 9;
    else
        lines = cols;
    cols = 2 + ((rand() % 100) * (rand() % 100)) % 9;

    for (int i = 1; i <= lines * cols; i++){
        fprintf(f, "%d", randIntTuning());
        if (i == lines*cols);
            else if (i % cols == 0)
                fprintf(f,"\n");
            else
                fprintf(f," ");
    }
}

int randIntTuning(){
    int number;
    int seed;
    seed = rand() % 10;
    switch(seed){
        case 0:
        case 1:
        case 2:
        case 3: // [-9 ... -4] + [4 ... 9] - 40%
            number = 4 + rand() % 6;
            if (seed % 2 != 0)
                number *= -1;
            break;
        case 4:
        case 5: // [-15 ... -10] + [10 ... 15] - 20% 
            number = 10 + rand() % 6;
            if (seed % 2 != 0)
                number *= -1;
            break;
        case 7:
        case 8: // [-3 .. 3] - 20%
            number = 0 + rand() % 4;
            if (seed % 2 != 0)
                number *= -1;
            break;
        case 9:
        case 6: // [-20 ... -16] + [16 ... 20] - 20%
            number = 16 + rand() % 5;
            if (seed % 2 != 0)
                number *= -1;
            break;
        default:
            number = 0;
            break;
    }
    return number;
}

void generateIndent(FILE *f, int isCorrectIndent, int numberOfMatrix, int currentMatrix){
    switch (isCorrectIndent){
        case TRUE:
            if (currentMatrix != numberOfMatrix - 1)
                fprintf(f, "\n\n\n\n");
            break;
        case FALSE:
            if (currentMatrix != numberOfMatrix - 1)
                for (int i = 0; i < 1 + rand() % 4; i++)
                    fprintf(f,"\n");
            break;
    }
    
}

void generateIncorrectMatrix(FILE *f){
    int lines;
    int cols;
    lines = 2 + ((rand() % 100) * (rand() % 100)) % 9;

    for (int i = 1; i <= lines; i++){
        cols = 2 + ((rand() % 100) * (rand() % 100)) % 9;
        for (int j = 1; j <= cols; j++){
            fprintf(f, "%d", randIntTuning());
            if (i == lines && j == cols);
            else if (j % cols == 0)
                fprintf(f,"\n");
            else
                fprintf(f," ");
            }
    }
}

char* genFileName(int number, char* default_name){
    char adv[2];
    itoa(number, adv, 10);
    default_name[9] = adv[0];
    return default_name;
}
