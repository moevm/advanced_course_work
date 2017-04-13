/*
    Заголовочный файл с объявлением структур и функций для программы refsol.c.

    By foksen 26.03.2017 (Last update 11.04.17).
*/
//  длина строки сгенерированных данных
#define GEN_DATA_LENGTH 53
//  длина пути к сгененерированному BMP-файлу
#define PATH_TO_BMP_LENGTH 19
//  максимальный размер последовательности функций
#define COMMANDS_LENGTH 8

//  I структура заголовка BMP-файла (14 байт)
#pragma pack(push, 2)
typedef struct
{
    unsigned short bfType;              //  сигнатура формата(4D42/424D)
    unsigned int bfSize;                //  размер файла в байтах
    unsigned short bfReserved1;         //  зарезервировано(0)
    unsigned short bfReserved2;         //  зарезервировано(0)
    unsigned int bfOffBits;             //  положение пикселей относительно начала файла в байтах
} BITMAPFILEHEADER;

//  II структура заголовка BMP-файла (124 байта)
typedef struct
{
    unsigned int biSize;                //  размер 2-ой структуры в байтах
    int biWidth;                        //  ширина растра в пикселях
    int biHeight;                       //  высота растра в пикселях
    unsigned short biPlanes;            //  поле для Windows(1)
    unsigned short biBitCount;          //  количество бит на пиксель
    unsigned int biCompression;         //  способ хранения пикселей
    unsigned int biSizeImage;           //  размер пиксельных данных в байтах
    int biXPelsPerMeter;                //  количество пикселей на метр по горизонтали
    int biYPelsPerMeter;                //  количество пикселей на метр по вертикали
    unsigned int biClrUsed;             //  размер таблицы цветов в ячейках
    unsigned int biClrImportant;        //  количество ячеек таблицы цветов
    unsigned int biRedMask;             //  битовая маска для красного цвета
    unsigned int biGreenMask;           //  битовая маска для зеленого цвета
    unsigned int biBlueMask;            //  битовая маска для синего цвета
    unsigned int biAlphaMask;           //  битовая маска для значения альфа-канала
    unsigned int biCSType;              //  вид цветового пространства
    unsigned int biEndpoints[9];        //  значение этих 4-х полей
    unsigned int biGammaRed;            //  берется во внимание,
    unsigned int biGammaGreen;          //  елси поле CSType
    unsigned int biGammaBlue;           //  содержит 0;
    unsigned int biIntent;              //  предпочтение при рендиренге растра
    unsigned int biProfileData;         //  смещение пикселей от начала Info в байтах
    unsigned int biProfileSize;         //  размер цветового профиля в байтах
    unsigned int biReserved;            //  зарезервировано(0)
} BITMAPINFO;

//  структура пикселя
typedef struct
{
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
} PIXEL;

//  структура одного сгенерированного теста
typedef struct
{
    char pathToBMP[PATH_TO_BMP_LENGTH];
    int x0;
    int y0;
    int x1;
    int y1;
    char commands[COMMANDS_LENGTH];
    char commandsAmount;
} GENDATA;

//  структура указателей на заголовки и массив пикселей
typedef struct
{
    BITMAPFILEHEADER* BF;
    BITMAPINFO* BI;
    PIXEL* RGB;
    char Addition;
} BMPDATA;
#pragma pack(pop)

//  функция читает сгенерирванные данные из txt-файла
GENDATA* readGeneratedData ();

//  функция проверяет корректность данных, считанных функцией readGeneratedData
int checkGenData (GENDATA* genDataInfo, BMPDATA* DataBMP);

//  функция читает содержимое BMP-файла
BMPDATA* readBMP (GENDATA* genDataInfo);

//  функция поворачивает заданную область по часовой стрелке на 90 градусов
void rotation (GENDATA* genDataInfo, BMPDATA* DataBMP);

//  функция инвертирует цвета в заданной области
void inversion (GENDATA* genDataInfo, BMPDATA* DataBMP);

//  функция рисует две диагонали толщиной 1 пиксель для заданной области черным цветом
void diagonal (GENDATA* genDataInfo, BMPDATA* DataBMP);

//  функция создает BMP-файл и записывет в него обработанное изображение
void writeBMP (BMPDATA* DataBMP);
