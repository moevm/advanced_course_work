/*
    Программа refsol.c (эталонное решение поставленной задачи) выполняет
    обработку BMP-файла и записывает результат в новый BMP-файл.

    By foksen98 25.03.2017 (Last update 17.04.17).
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "refsol.h"

int main ()
{
    //  чтение сгенерированных данных
    GENDATA* genDataInfo = readGeneratedData();
    //  чтение содержимого BMP-файла
    BMPDATA* DataBMP = readBMP(genDataInfo);
    if (!DataBMP)
        return 0;
    //  обработка изображения
    for (char i = 0; i < (genDataInfo->commandsAmount - 1); ++i)
        switch (genDataInfo->commands[i])
        {
            case 1 :
            {
                rotation(genDataInfo, DataBMP);
                break;
            }
            case 2 :
            {
                inversion(genDataInfo, DataBMP);
                break;
            }
            case 3 :
            {
                diagonal(genDataInfo, DataBMP);
                break;
            }
        }
    //  создание и запись обработанного BMP-файла
    writeBMP(DataBMP);
    printf("Look OUT.bmp.");

    //  очищение памяти
    free(genDataInfo);
    free(DataBMP->BF);
    free(DataBMP->BI);
    free(DataBMP->RGB);
    free(DataBMP);

    return 0;
}

GENDATA* readGeneratedData ()
{
    char genDataStr[GEN_DATA_LENGTH];
    GENDATA* genDataInfo = (GENDATA*)malloc(sizeof(GENDATA));

    fgets(genDataStr, GEN_DATA_LENGTH, stdin);
    strncpy(genDataInfo->pathToBMP, strtok(genDataStr, " "), PATH_TO_BMP_LENGTH);
    genDataInfo->x0 = atoi(strtok(NULL, " "));
    genDataInfo->y0 = atoi(strtok(NULL, " "));
    genDataInfo->x1 = atoi(strtok(NULL, " "));
    genDataInfo->y1 = atoi(strtok(NULL, " "));
    char i = 0;
    char* ptr = strtok(NULL, " \n");
    while (ptr)
    {
        genDataInfo->commands[i++] = atoi(ptr);
        ptr = strtok(NULL, " \n");
    }
    genDataInfo->commandsAmount = i;

    return genDataInfo;
}

int checkGenData (GENDATA* genDataInfo, BMPDATA* DataBMP)
{
    if (
        ((genDataInfo->x1 - genDataInfo->x0) != (genDataInfo->y1 - genDataInfo->y0)) ||
        (genDataInfo->x0 > DataBMP->BI->biWidth) ||
        (genDataInfo->y0 > DataBMP->BI->biHeight) ||
        (genDataInfo->x1 > DataBMP->BI->biWidth) ||
        (genDataInfo->y1 > DataBMP->BI->biHeight) ||
        (genDataInfo->x0 > genDataInfo->x1)
       )
    {
        printf("Fail with coordinates.");
        return 1;
    }
    if (genDataInfo->commands[genDataInfo->commandsAmount - 1] != 4)
    {
        printf("Fail with commands.");
        return 2;
    }

    return 0;
}

BMPDATA* readBMP (GENDATA* genDataInfo)
{
    FILE* BMP = fopen(genDataInfo->pathToBMP, "r");
    //  проверяем корректность пути к BMP-файлу
    if (!BMP)
    {
        printf("Fail with input_file.");
        return NULL;
    }
    BMPDATA* DataBMP = (BMPDATA*)malloc(sizeof(BMPDATA));
    DataBMP->BF = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    DataBMP->BI = (BITMAPINFO*)malloc(sizeof(BITMAPINFO));

    fread(DataBMP->BF, 1, sizeof(BITMAPFILEHEADER), BMP);
    fread(DataBMP->BI, 1, sizeof(BITMAPINFO), BMP);

    //  проверка корректности сгенерированных данных
    if (checkGenData(genDataInfo, DataBMP) != 0)
        return NULL;

    DataBMP->Addition = ((4 - ((DataBMP->BI->biWidth * 3) & 3)) & 3);
    char Zero;
    DataBMP->RGB = (PIXEL*)malloc(sizeof(PIXEL*) * DataBMP->BI->biHeight * DataBMP->BI->biWidth);

    for (int i = 0; i < DataBMP->BI->biHeight; ++i)
    {
        for (int j = 0; j < DataBMP->BI->biWidth; ++j)
            fread(&DataBMP->RGB[i * (DataBMP->BI->biWidth) + j], 1, sizeof(PIXEL), BMP);
        for (char k = 0; k < DataBMP->Addition; ++k)
            fscanf(BMP, "%c", &Zero);
    }

    fclose(BMP);

    return  DataBMP;
}

void rotation (GENDATA* genDataInfo, BMPDATA* DataBMP)
{
    int x0 = genDataInfo->x0;
    int y0 = genDataInfo->y0;
    int x1 = genDataInfo->x1;
    int y1 = genDataInfo->y1;
    int Width = DataBMP->BI->biWidth;
    int Height = DataBMP->BI->biHeight;
    for (int i = 0; i < ((y1 - y0) / 2); ++i)
        for (int j = 0; j < (y1  - y0 - 2 * i); ++j)
        {
            PIXEL temp = DataBMP->RGB[(Height - y1 + j + i) * Width + x0 + i];
            DataBMP->RGB[(Height - y1 + j + i) * Width + x0 + i] = DataBMP->RGB[(Height - y1 + i) * Width + x1 - j - i];
            DataBMP->RGB[(Height - y1 + i) * Width + x1 - j - i] = DataBMP->RGB[(Height - y0 - j - i) * Width + x1 - i];
            DataBMP->RGB[(Height - y0 - j - i) * Width + x1 - i] = DataBMP->RGB[(Height - y0 - i) * Width + x0 + j + i];
            DataBMP->RGB[(Height - y0 - i) * Width + x0 + j + i] = temp;
        }
}

void inversion (GENDATA* genDataInfo, BMPDATA* DataBMP)
{
    int x0 = genDataInfo->x0;
    int y0 = genDataInfo->y0;
    int x1 = genDataInfo->x1;
    int y1 = genDataInfo->y1;
    int Width = DataBMP->BI->biWidth;
    int Height = DataBMP->BI->biHeight;
    for (int i = (Height - y1); i <= (Height - y0); ++i)
        for (int j = x0; j <= x1; ++j)
        {
            DataBMP->RGB[i * Width + j].Blue = ~DataBMP->RGB[i * Width + j].Blue;
            DataBMP->RGB[i * Width + j].Green = ~DataBMP->RGB[i * Width + j].Green;
            DataBMP->RGB[i * Width + j].Red = ~DataBMP->RGB[i * Width + j].Red;
        }
}

void diagonal (GENDATA* genDataInfo, BMPDATA* DataBMP)
{
    int x0 = genDataInfo->x0;
    int y0 = genDataInfo->y0;
    int x1 = genDataInfo->x1;
    int y1 = genDataInfo->y1;
    int Width = DataBMP->BI->biWidth;
    int Height = DataBMP->BI->biHeight;
    for (int i = (Height - y1); i <= (Height - y0); ++i)
        {
            DataBMP->RGB[i * Width + x0].Blue = 0;
            DataBMP->RGB[i * Width + x0].Green = 0;
            DataBMP->RGB[i * Width + x0++].Red = 0;
            DataBMP->RGB[i * Width + x1].Blue = 0;
            DataBMP->RGB[i * Width + x1].Green = 0;
            DataBMP->RGB[i * Width + x1--].Red = 0;
        }
}

void writeBMP (BMPDATA* DataBMP)
{
    const char* nameOUT = "REFOUT.bmp";
    FILE* OUT = fopen(nameOUT, "w");

    fwrite(DataBMP->BF, 1, sizeof(BITMAPFILEHEADER), OUT);
    fwrite(DataBMP->BI, 1, sizeof(BITMAPINFO), OUT);

    for (int i = 0; i < DataBMP->BI->biHeight; ++i)
    {
        for (int j = 0; j < DataBMP->BI->biWidth; ++j)
            fwrite(&DataBMP->RGB[i * (DataBMP->BI->biWidth) + j], 1, sizeof(PIXEL), OUT);
        for (char k = 0; k < DataBMP->Addition; ++k)
            fprintf(OUT, "%c", 0);
    }

    fclose(OUT);
}
