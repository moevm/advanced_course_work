/*
    Программа generate.c генерирует в txt-файл входные данные для
    эталонного(refsol.c) и пользовательского решений поставленной задачи.

    By foksen98 17.03.2017 (Last update 25.03.2017).
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  размер диапазона чисел для функции rand()
#define AMOUNT_BMP 10
#define AMOUNT_PIXELS 500
#define AMOUNT_LENGTH 7
#define AMOUNT_ELEMENTS 3

//  количество сгенерированных тестов
#define AMOUNT_TESTS 50

//  функция генерирует индекс BMP-файла для обработки, размер и элементы последовательности функций для обработки BMP-файла
char generateAll (short amount);

//  функция генерирует координаты обрабатываемой области BMP-файла
short generateCoordinates (short amount, short lowLimit);

//  функция генерирует и записывает в txt-файл 1 полноценный тест
void generator (FILE* filePtr, const char* path, short flag);

int main ()
{
    //  здесь хранится путь к директории с BMP-файлами и txt-файлу с тестами
    const char* pathToBMP = "ImagesBMP";
    const char* pathToGenData = "generatedData.txt";

    //  инициализация функции rand()
    srand(time(NULL));

    //  открытие txt-файла для записи
    FILE* generatedData = fopen(pathToGenData, "w");

    //  генерация amountTests тестов
    for (char i = 0; i < AMOUNT_TESTS; ++i)
        generator(generatedData, pathToBMP, !(i % (AMOUNT_TESTS / 2)));

    //  закрытие txt-файла
    fclose(generatedData);

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

void generator (FILE* filePtr, const char* path, short flag)
{
    //  генерация индекса BMP-файла для обработки
    char IndexBMP = generateAll(AMOUNT_BMP);

    //  генерация координат (!квадратной!) обрабатываемой области BMP-файла
    short x0 = generateCoordinates((3 * (AMOUNT_PIXELS / 5)), 0);
    short y0 = generateCoordinates((3 * (AMOUNT_PIXELS / 5)), 0);
    short x1 = generateCoordinates((3 * (AMOUNT_PIXELS / 5)), (2 * (AMOUNT_PIXELS / 5)));
    short y1;
    if (flag)
        y1 = generateCoordinates((3 * (AMOUNT_PIXELS / 5)), (2 * (AMOUNT_PIXELS / 5)));
    else
        y1 = (y0 + (x1 - x0));

    //  генерация последовательности функций для обработки BMP-файла
    char commandsLength = generateAll(AMOUNT_LENGTH);
    char* commands = (char*)malloc((commandsLength + 1) * sizeof(char));
    for (char i = 0; i < commandsLength; ++i)
        commands[i] = generateAll(AMOUNT_ELEMENTS);
    commands[commandsLength] = ((generateAll(AMOUNT_ELEMENTS) % 2) + 3);

    //  вывод сгенерированных данных в txt-файл
    fprintf(filePtr, "%s/BMP%hhd.bmp ", path, IndexBMP);
    fprintf(filePtr, "%hd %hd ", x0, y0);
    fprintf(filePtr, "%hd %hd ", x1, y1);
    for (char i = 0; i < (commandsLength + 1); ++i)
        fprintf(filePtr, "%hhd ", commands[i]);
    fprintf(filePtr, "\n");

    //  освобождение динамической памяти
    free(commands);
}
