#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
 
typedef int FXPT2DOT30;
 
typedef struct {
	unsigned short bfType;
	unsigned int   bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int   bfOffBits;
} BITMAPFILEHEADER;
typedef struct {
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
} CIEXYZ;
typedef struct {
	CIEXYZ  ciexyzRed; 
	CIEXYZ  ciexyzGreen; 
	CIEXYZ  ciexyzBlue; 
} CIEXYZTRIPLE;

 

 //Давайте спиздим структуры из windows.h wingdi.h WinGDI.h
typedef struct {
unsigned int   biSize;
//Размер структуры.
unsigned int   biWidth;
//Ширина изображения в пикселах соответственно.
unsigned int   biHeight;
//Высота изображения в пикселах соответственно.
unsigned short biPlanes;
//Количество плоскостей. Использовалось ранее при небольшой глубине фвета. Сейчас, при числе цветов 256 и больше, оно всегда равно 1. Сохранено для совместимости.
unsigned short biBitCount;
//Глубина цвета в битах на пиксель.
unsigned int   biCompression;
//Тип сжатия. Если компрессия не используется, то флаг имеет значенине BI_RGB. Возможны варианты BI_RLE8, BI_RLE4, BI_BITFIELDS и BI_JPEG.
unsigned int   biSizeImage;
//Размер изображения в байтах. Если изображение не сжато (то есть поле biCompression установлено в BI_RGB), то здесь может быть записан 0.
unsigned int   biXPelsPerMeter;
//Горизонтальное и вертикальное разрешение (в пикселях на метр) соответственно. Важно в первую очередь для устройства, на которое будет выводиться битовый массив.
unsigned int   biYPelsPerMeter;
//Горизонтальное и вертикальное разрешение (в пикселях на метр) соответственно. Важно в первую очередь для устройства, на которое будет выводиться битовый массив.
unsigned int   biClrUsed;
//Количество используемых цветов кодовой таблицы. Если значение поля равно 0, то используется максимально возможное количество цветов, которые разрешены значением поля biBitCount.
unsigned int   biClrImportant;
//Количество основных цветов. Определяет число цветов, необходимых для отображения изображения. Если значение поля равно 0, то используются все цвета.
unsigned int   biRedMask;
unsigned int   biGreenMask;
unsigned int   biBlueMask;
unsigned int   biAlphaMask;
unsigned int   biCSType;
CIEXYZTRIPLE   biEndpoints;
unsigned int   biGammaRed;
unsigned int   biGammaGreen;
unsigned int   biGammaBlue;
unsigned int   biIntent;
unsigned int   biProfileData;
unsigned int   biProfileSize;
unsigned int   biReserved;
} BITMAPINFOHEADER;
 
typedef struct {
	unsigned char  rgbBlue;
	unsigned char  rgbGreen;
	unsigned char  rgbRed;
	unsigned char  rgbReserved;
} RGBQUAD;
unsigned char MAASK(const unsigned int byte, const unsigned int mask);
template <typename Type>
void read(std::ifstream &fp, Type &result, std::size_t size) {
	fp.read(reinterpret_cast<char*>(&result), size);
}
template <typename Type>
void write(std::ofstream &fp, Type &result, std::size_t size) {
	fp.write(reinterpret_cast<char*>(&result), size);
}


 
#endif // MAIN_H_INCLUDEDs