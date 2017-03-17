/*
    Программа generate.c генерирует входные данные для программы refsol.c,
    которая является эталонным решением поставленной задачи.

    By foksen98 17.03.2017.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  размер диапазона чисел для функции rand()
#define amountBMP 10
#define amountPixels 500
#define amountLength 7
#define amountElements 3

//  функция генерирует индекс BMP-файла для обработки, размер и элементы последовательности функций для обработки BMP-файла
char generateAll (short);

//  функция генерирует координаты обрабатываемой области BMP-файла
short generateCoordinates (short, short);

int main ()
{
//  здесь хранится путь к директории с BMP-файлами
    const char* pathToBMP = "/ImagesBMP/BMP";

//  инициализация функции rand()
    srand(time(NULL));

//  генерация индекса BMP-файла для обработки
    char IndexBMP = generateAll(amountBMP);

//  генерация координат обрабатываемой области BMP-файла
    short x0 = generateCoordinates((3 * (amountPixels / 5)), 0);
    short y0 = generateCoordinates((3 * (amountPixels / 5)), 0);
    short x1 = generateCoordinates((3 * (amountPixels / 5)), (2 * (amountPixels / 5)));
    short y1 = generateCoordinates((3 * (amountPixels / 5)), (2 * (amountPixels / 5)));

//  генерация последовательности функций для обработки BMP-файла
    char commandsLength = generateAll(amountLength);
    char* commands = (char*)malloc(commandsLength * sizeof(char));
    for (char i = 0; i < commandsLength; ++i)
        commands[i] = generateAll(amountElements);

//  вывод сгенерированных данных на консоль

//  вывод сгенерированных данных в txt-файл
    FILE* generatedData = fopen("generatedData.txt", "w");
    fprintf(generatedData, "%s%hhd.bmp\n", pathToBMP, IndexBMP);
    fprintf(generatedData, "%hd %hd\n", x0, y0);
    fprintf(generatedData, "%hd %hd\n", x1, y1);
    for (char i = 0; i < commandsLength; ++i)
        fprintf(generatedData, "%hhd ", commands[i]);
    fprintf(generatedData, "4\n");
    fclose(generatedData);

//  освобождение динамической памяти
    free(commands);

    return 0;
}

char generateAll (short amount)
{
    return (rand() % amount + 1);
}

short generateCoordinates (short amount, short lowLimit)
{
    return (rand() % amount + lowLimit);
}
