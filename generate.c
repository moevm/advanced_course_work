/*
	generate.c
    Фиалковский Максим
	Группа 6381
	makometr@yandex.ru
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0

void generateCorrectMatrix(FILE *f, int isCorrectMultiplication, int i); 
// Генерирует и записывает в файл правильную матрицу.
// Каждая строчка начинается с числа и заканчивается числом.
void generateIncorrectMatrix(FILE *f); // генерирует и записывает в файл неправильную матрицу.
void generateIndent(FILE *f, int numberOfMatrix, int currentMatrix); // Вставляют отступ.
int randIntTuning(); // Настраиваемый генератор чисел от -20 до 20.

int main(int argc, char* argv[]){
    srand(time(NULL));
    int isCorrectMatrix = 0;
    switch (argv[1][0]){
        case '0':
            printf("Incorrect will be generated\n");
            isCorrectMatrix = 0;
            break;
        case '1':
            printf("Correct will be generated!\n");
            isCorrectMatrix = 1;
            break;
        default:
            printf("Wrong generation arguments!\n");
            break; 
            exit(1);
    }
    FILE *f = fopen("testcase", "w");

    int numberOfMatrix = 2 + rand() % 6; // Количество генерируемых матриц. 2 - 7
     // isCorrectMatrix Параметр генерации, отвечающий за генерирование матриц с ошибками или без.
    int isCorrectMultiplication; // Парметр генерации, отвечающий за генерацию умножаемых матриц. 0 - 1
    if (isCorrectMatrix != FALSE)
        isCorrectMultiplication = rand() % 3;

    switch (isCorrectMatrix){
        case 1:
            for (int i = 0; i < numberOfMatrix; i++){
                generateCorrectMatrix(f, isCorrectMultiplication, i);
                generateIndent(f, numberOfMatrix, i);
            }
            break;
        case FALSE:
                for (int i = 0; i < numberOfMatrix; i++){
                generateIncorrectMatrix(f);
                generateIndent(f, numberOfMatrix, i);
            }

    }
    fclose(f);
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

void generateIndent(FILE *f, int numberOfMatrix, int currentMatrix){
    if (currentMatrix != numberOfMatrix - 1)
        for (int i = 0; i < (1 + rand() % 4); i++)
            fprintf(f,"\n");
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