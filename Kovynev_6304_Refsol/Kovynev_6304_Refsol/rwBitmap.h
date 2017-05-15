void writeToBitmapHeader(FILE* outfile, BITMAPFILEHEADER headerBMP);

void writeToBitmapInfo(FILE* outfile, BITMAPINFOHEADER infoBMP);

void writeToBitmapRGB(FILE* outfile, RGBPIXEL** arrayRGB, BITMAPINFOHEADER infoBMP);

BITMAPFILEHEADER readFromBitmapHeader(FILE* bitmap);

BITMAPINFOHEADER readFromBitmapInfo(FILE* bitmap);

RGBPIXEL** readFromBitmapRGB(FILE* bitmap, BITMAPINFOHEADER info);
