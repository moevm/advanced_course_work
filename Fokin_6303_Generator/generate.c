/*
    Программа generate.c генерирует в txt-файл входные данные для
    эталонного(refsol.c) и пользовательского решений поставленной задачи.

    By foksen98 17.03.2017 (Last update 18.03.2017).
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  размер диапазона чисел для функции rand()
#define amountBMP 10
#define amountPixels 500
#define amountLength 7
#define amountElements 3

// количество сгенерированных тестов
#define amountTests 50

//  функция генерирует индекс BMP-файла для обработки, размер и элементы последовательности функций для обработки BMP-файла
char generateAll (short);

//  функция генерирует координаты обрабатываемой области BMP-файла
short generateCoordinates (short, short);

//  функция генерирует и записывает в txt-файл 1 полноценный тест
void generator (FILE*, const char*);

int main ()
{
//  здесь хранится путь к директории с BMP-файлами
    const char* pathToBMP = "/ImagesBMP";

//  инициализация функции rand()
    srand(time(NULL));

//  открытие txt-файла для записи
    FILE* generatedData = fopen("generatedData.txt", "w");

//  генерация amountTests тестов
    for (char i = 0; i < amountTests; ++i)
        generator(generatedData, pathToBMP);

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

void generator (FILE* filePtr, const char* path)
{
//  генерация индекса BMP-файла для обработки
    char IndexBMP = generateAll(amountBMP);

//  генерация координат (!квадратной!) обрабатываемой области BMP-файла
    short x0 = generateCoordinates((3 * (amountPixels / 5)), 0);
    short y0 = generateCoordinates((3 * (amountPixels / 5)), 0);
    short x1 = generateCoordinates((3 * (amountPixels / 5)), (2 * (amountPixels / 5)));
    short y1 = (y0 + (x1 - x0));

//  генерация последовательности функций для обработки BMP-файла
    char commandsLength = generateAll(amountLength);
    char* commands = (char*)malloc(commandsLength * sizeof(char));
    for (char i = 0; i < commandsLength; ++i)
        commands[i] = generateAll(amountElements);

//  вывод сгенерированных данных в txt-файл
    fprintf(filePtr, "%s/BMP%hhd.bmp ", path, IndexBMP);
    fprintf(filePtr, "%hd %hd ", x0, y0);
    fprintf(filePtr, "%hd %hd ", x1, y1);
    for (char i = 0; i < commandsLength; ++i)
        fprintf(filePtr, "%hhd ", commands[i]);
    fprintf(filePtr, "4\n");

//  освобождение динамической памяти
    free(commands);
}
