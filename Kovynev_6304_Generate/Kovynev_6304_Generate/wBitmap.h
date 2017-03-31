void writeToBitmapHeader(FILE* outfile, BITMAPFILEHEADER headerBMP);

void writeToBitmapInfo(FILE* outfile, BITMAPINFOHEADER infoBMP);

void WriteToBitmapRGB(FILE* outfile, RGBQUAD** arrayRGB, BITMAPINFOHEADER infoBMP);

void createBitmapFile(int Width, int Height);
