#include <iostream>
#include <fstream>
#include "main.h"
#include <time.h>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "file_name: " << argv[0] << std::endl;
		return 0;}
	std::ofstream fileStreamo("output.bmp", std::ofstream::binary);
	// ------------------------------------------------------------------------------открываем файл
    char * fileName = argv[1];
	std::ifstream fileStream(fileName, std::ifstream::binary); 
	if (!fileStream) {
		std::cout << "Error opening file '" << fileName << "'." << std::endl;
		return 0;}
	// ------------------------------------------------------------------------------открываем файл^
 
	// ------------------------------------------------------------------------------заголовк изображения
	BITMAPFILEHEADER fileHeader;
	read(fileStream, fileHeader.bfType, sizeof(fileHeader.bfType));
	read(fileStream, fileHeader.bfSize, sizeof(fileHeader.bfSize));
	read(fileStream, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
	read(fileStream, fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
	read(fileStream, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));
	
		write(fileStreamo, fileHeader.bfType, sizeof(fileHeader.bfType));
		write(fileStreamo, fileHeader.bfSize, sizeof(fileHeader.bfSize));
		write(fileStreamo, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
		write(fileStreamo, fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
		write(fileStreamo, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));
	
																					/*cout<<"bfType "<<fileHeader.bfType<<" \n";
																					cout<<"bfSize "<<fileHeader.bfSize<<" \n";
																					cout<<"bfReserved1 "<<fileHeader.bfReserved1<<" \n";
																					cout<<"bfReserved2 "<<fileHeader.bfReserved2<<" \n";
																					cout<<"bfOffBits "<<fileHeader.bfOffBits<<" \n";*/
	if (fileHeader.bfType != 0x4D42) {
		std::cout << "Error: '" << fileName << "' is not BMP file." << std::endl;
		return 0;}
 	// ------------------------------------------------------------------------------заголовк изображения^

	// ------------------------------------------------------------------------------информация изображения
	BITMAPINFOHEADER fileInfoHeader;
	read(fileStream, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));
	
	write(fileStreamo, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));

 																					/*cout<<"biSize "<<fileInfoHeader.biSize<<" \n";*/
	// ------------------------------------------------------------------------------информация изображения^

	// ------------------------------------------------------------------------------основа
	if (fileInfoHeader.biSize >= 12) {
		read(fileStream, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));
		read(fileStream, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
		read(fileStream, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
		read(fileStream, fileInfoHeader.biBitCount, sizeof(fileInfoHeader.biBitCount));
		write(fileStreamo, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));

		write(fileStreamo, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
		write(fileStreamo, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
		write(fileStreamo, fileInfoHeader.biBitCount, sizeof(fileInfoHeader.biBitCount));
		
																					/*cout<<"biWidth "<<fileInfoHeader.biWidth<<" \n";
 																					cout<<"biHeight "<<fileInfoHeader.biHeight<<" \n";
 																					cout<<"biPlanes "<<fileInfoHeader.biPlanes<<" \n";
 																					cout<<"biBitCount "<<fileInfoHeader.biBitCount<<" \n";*/}
	// ------------------------------------------------------------------------------основа^

	// ------------------------------------------------------------------------------получаем информацию о битности
 	int maskValue,colorsCount,bitsOnColor;
 	
	colorsCount = fileInfoHeader.biBitCount >> 3;
	if (colorsCount < 3) colorsCount = 3;
	bitsOnColor = fileInfoHeader.biBitCount / colorsCount;
	maskValue = (1 << bitsOnColor) - 1;//аналог возведения 2 в степень
																					/*cout<<"colorsCount "<<colorsCount<<" \n";
																					cout<<"bitsOnColor "<<bitsOnColor<<" \n";
																					cout<<"maskValue "<<maskValue<<" \n";*/
	
 	// ------------------------------------------------------------------------------получаем информацию о битности^

	// ------------------------------------------------------------------------------Добавляет 16 бит на пиксель и 32 форматов BPP. Добавляет сжатие RLE.
	if (fileInfoHeader.biSize >= 40) {
		read(fileStream, fileInfoHeader.biCompression, sizeof(fileInfoHeader.biCompression));
		read(fileStream, fileInfoHeader.biSizeImage, sizeof(fileInfoHeader.biSizeImage));
		read(fileStream, fileInfoHeader.biXPelsPerMeter, sizeof(fileInfoHeader.biXPelsPerMeter));
		read(fileStream, fileInfoHeader.biYPelsPerMeter, sizeof(fileInfoHeader.biYPelsPerMeter));
		read(fileStream, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
		read(fileStream, fileInfoHeader.biClrImportant, sizeof(fileInfoHeader.biClrImportant));

		write(fileStreamo, fileInfoHeader.biCompression, sizeof(fileInfoHeader.biCompression));
		write(fileStreamo, fileInfoHeader.biSizeImage, sizeof(fileInfoHeader.biSizeImage));
		write(fileStreamo, fileInfoHeader.biXPelsPerMeter, sizeof(fileInfoHeader.biXPelsPerMeter));
		write(fileStreamo, fileInfoHeader.biYPelsPerMeter, sizeof(fileInfoHeader.biYPelsPerMeter));
		write(fileStreamo, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
		write(fileStreamo, fileInfoHeader.biClrImportant, sizeof(fileInfoHeader.biClrImportant));
 		
 																					/*cout<<"biCompression "<<fileInfoHeader.biCompression<<" \n";
 																					cout<<"biSizeImage "<<fileInfoHeader.biSizeImage<<" \n";
 																					cout<<"biXPelsPerMeter "<<fileInfoHeader.biXPelsPerMeter<<" \n";
 																					cout<<"biYPelsPerMeter "<<fileInfoHeader.biYPelsPerMeter<<" \n";
 																					cout<<"biClrUsed "<<fileInfoHeader.biClrUsed<<" \n";
 																					cout<<"biClrImportant "<<fileInfoHeader.biClrImportant<<" \n";*/}
	// ------------------------------------------------------------------------------Добавляет 16 бит на пиксель и 32 форматов BPP.^

	// ------------------------------------------------------------------------------Добавляет битовых масок RGB. 
	fileInfoHeader.biRedMask = 0;
	fileInfoHeader.biGreenMask = 0;
	fileInfoHeader.biBlueMask = 0;
	if (fileInfoHeader.biSize >= 52) {
		read(fileStream, fileInfoHeader.biRedMask, sizeof(fileInfoHeader.biRedMask));
		read(fileStream, fileInfoHeader.biGreenMask, sizeof(fileInfoHeader.biGreenMask));
		read(fileStream, fileInfoHeader.biBlueMask, sizeof(fileInfoHeader.biBlueMask));

		write(fileStreamo, fileInfoHeader.biRedMask, sizeof(fileInfoHeader.biRedMask));
		write(fileStreamo, fileInfoHeader.biGreenMask, sizeof(fileInfoHeader.biGreenMask));
		write(fileStreamo, fileInfoHeader.biBlueMask, sizeof(fileInfoHeader.biBlueMask));
 		
 																					/*cout<<"1biRedMask "<<fileInfoHeader.biRedMask<<" \n";
 																					cout<<"1biGreenMask "<<fileInfoHeader.biGreenMask<<" \n";
 																					cout<<"1biBlueMask "<<fileInfoHeader.biBlueMask<<" \n";*/}
 	// ------------------------------------------------------------------------------Добавляет битовых масок RGB^

	// если маска не задана, то ставим маску по умолчанию
	if (fileInfoHeader.biRedMask == 0 || fileInfoHeader.biGreenMask == 0 || fileInfoHeader.biBlueMask == 0) {
		fileInfoHeader.biRedMask = maskValue << (bitsOnColor * 2);
		fileInfoHeader.biGreenMask = maskValue << bitsOnColor;
		fileInfoHeader.biBlueMask = maskValue;
 																					/*cout<<"0biRedMask "<<fileInfoHeader.biRedMask<<" \n";
 																					cout<<"0biGreenMask "<<fileInfoHeader.biGreenMask<<" \n";
 																					cout<<"0biBlueMask "<<fileInfoHeader.biBlueMask<<" \n";*/}
 
	// ------------------------------------------------------------------------------Добавляет канал альфа битовую маску.
	if (fileInfoHeader.biSize >= 56) {
		read(fileStream, fileInfoHeader.biAlphaMask, sizeof(fileInfoHeader.biAlphaMask));

		write(fileStreamo, fileInfoHeader.biAlphaMask, sizeof(fileInfoHeader.biAlphaMask));
	} else {
		fileInfoHeader.biAlphaMask = maskValue << (bitsOnColor * 3);
	}
 	// ------------------------------------------------------------------------------Добавляет канал альфа битовую маску^

	// ------------------------------------------------------------------------------Добавляет тип цветового пространства и гамма-коррекцию.
	if (fileInfoHeader.biSize >= 108) {
		read(fileStream, fileInfoHeader.biCSType, sizeof(fileInfoHeader.biCSType));
		read(fileStream, fileInfoHeader.biEndpoints, sizeof(fileInfoHeader.biEndpoints));
		read(fileStream, fileInfoHeader.biGammaRed, sizeof(fileInfoHeader.biGammaRed));
		read(fileStream, fileInfoHeader.biGammaGreen, sizeof(fileInfoHeader.biGammaGreen));
		read(fileStream, fileInfoHeader.biGammaBlue, sizeof(fileInfoHeader.biGammaBlue));

		write(fileStreamo, fileInfoHeader.biCSType, sizeof(fileInfoHeader.biCSType));
		write(fileStreamo, fileInfoHeader.biEndpoints, sizeof(fileInfoHeader.biEndpoints));
		write(fileStreamo, fileInfoHeader.biGammaRed, sizeof(fileInfoHeader.biGammaRed));
		write(fileStreamo, fileInfoHeader.biGammaGreen, sizeof(fileInfoHeader.biGammaGreen));
		write(fileStreamo, fileInfoHeader.biGammaBlue, sizeof(fileInfoHeader.biGammaBlue));
 		
 	/*																				cout<<"biCSType "<<fileInfoHeader.biCSType<<" \n";
 																					cout<<"biEndpoints "<<"- not string "<<" \n";
 																					cout<<"biGammaRed "<<fileInfoHeader.biGammaRed<<" \n";
  																					cout<<"biGammaGreen "<<fileInfoHeader.biGammaGreen<<" \n";
 																					cout<<"biGammaBlue "<<fileInfoHeader.biGammaBlue<<" \n";*/}
	// ------------------------------------------------------------------------------Добавляет тип пространства и гамма-коррекцию^
 
	// ------------------------------------------------------------------------------Добавляет МТП цветовые профили (International Color Consortium)
	if (fileInfoHeader.biSize >= 124) {
		read(fileStream, fileInfoHeader.biIntent, sizeof(fileInfoHeader.biIntent));
		read(fileStream, fileInfoHeader.biProfileData, sizeof(fileInfoHeader.biProfileData));
		read(fileStream, fileInfoHeader.biProfileSize, sizeof(fileInfoHeader.biProfileSize));
		read(fileStream, fileInfoHeader.biReserved, sizeof(fileInfoHeader.biReserved));

		write(fileStreamo, fileInfoHeader.biIntent, sizeof(fileInfoHeader.biIntent));
		write(fileStreamo, fileInfoHeader.biProfileData, sizeof(fileInfoHeader.biProfileData));
		write(fileStreamo, fileInfoHeader.biProfileSize, sizeof(fileInfoHeader.biProfileSize));
		write(fileStreamo, fileInfoHeader.biReserved, sizeof(fileInfoHeader.biReserved));
		
																					/*cout<<"biRedMask "<<fileInfoHeader.biIntent<<" \n";
 																					cout<<"biProfileData "<<fileInfoHeader.biProfileData<<" \n";
 																					cout<<"biProfileSize "<<fileInfoHeader.biProfileSize<<" \n";
 																					cout<<"biReserved "<<fileInfoHeader.biReserved<<" \n";*/}
	// ------------------------------------------------------------------------------Добавляет МТП цветовые профили^

	// ------------------------------------------------------------------------------временная проверка на поддерку этой версии формата
	if (fileInfoHeader.biSize != 12 && fileInfoHeader.biSize != 40 && fileInfoHeader.biSize != 52 &&
	    fileInfoHeader.biSize != 56 && fileInfoHeader.biSize != 108 && fileInfoHeader.biSize != 124) {
		std::cout << "Error: Unsupported BMP format." << std::endl;
		return 0;}
	if (fileInfoHeader.biCompression != 0 && fileInfoHeader.biCompression != 3) {
		std::cout << "Error: Unsupported BMP compression." << std::endl;
		return 0;}
	if (fileInfoHeader.biBitCount != 16 && fileInfoHeader.biBitCount != 24 && fileInfoHeader.biBitCount != 32) {
		std::cout << "Error: Unsupported BMP bit count." << std::endl;
		return 0;}
 

 	// ------------------------------------------------------------------------------временная проверка^

	// ------------------------------------------------------------------------------выделение памяти под пиксили
		static RGBQUAD **RRINF;

		RRINF = new RGBQUAD*[fileInfoHeader.biHeight]; 
		for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) 
			RRINF[i] = new RGBQUAD[fileInfoHeader.biWidth];

	// ------------------------------------------------------------------------------выделение памяти под пиксили^
 	// Размер каждой строки округляется до кратного 4 байтам
	// ------------------------------------------------------------------------------отступ в конце каждой строки = (ширина{пикс}*(глубина_цвета{бит}/8){байт})%4 & 3 
	
	int linePadding = (4 - (fileInfoHeader.biWidth * (fileInfoHeader.biBitCount / 8)) % 4) % 4;//отступ строки
 																					/*cout<<"linePadding "<<linePadding<<" \n";*/
	long int rowsize = ((int)((fileInfoHeader.biBitCount*fileInfoHeader.biWidth+31)/32))*4;//вес строки
																					/*cout<<"rowsize "<<rowsize<<" \n";*/
 	// ------------------------------------------------------------------------------отступ в конце каждой строки^
	
	// ------------------------------------------------------------------------------чтение
	int a;
    cout<<"|0 - std|1 - Negative|2 - Sepia|3 - Change color balance|4 - Random change color balance|\nChoose your filter  -  ";
    cin>>a;
    int x,y,z;
    switch (a)
    {
    	case 3:
    	{
			cout<<"Change color balance;\n";
			cout<<"Choose changing of colours.x-blue,y-green,z-red\n";
			cout<<"Choose blue\n";
			cin>>x;
			cout<<"Choose green\n";
			cin>>y;
			cout<<"Choose red\n";
			cin>>z;
			break;
		}
		case 4:
    	{
			cout<<"Randon change color balance;\n";
			int x,y,z;
			srand(time(NULL));
			x=rand()% 256;
			y=rand()% 256;
			z=rand()% 256;
			cout<<"blue= "<<x<<'\n';
			cout<<"green= "<<y<<'\n';
			cout<<"red= "<<z<<'\n';
			break;
		}
		/*case 5:
    	{
			cout<<"fil.txt\n";
			break;
		}*/
	}
	for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++){
		for (unsigned int j = 0; j < fileInfoHeader.biWidth; j++){
			read(fileStream, RRINF[i][j], fileInfoHeader.biBitCount / 8);

			switch (a){
				case 1:
				{
					RRINF[i][j].rgbRed = 255 - RRINF[i][j].rgbRed;
					RRINF[i][j].rgbGreen = 255 - RRINF[i][j].rgbGreen;
					RRINF[i][j].rgbBlue = 255 - RRINF[i][j].rgbBlue;
					break;
				}
				case 2:
				{
					RRINF[i][j].rgbRed = (RRINF[i][j].rgbRed+RRINF[i][j].rgbGreen+RRINF[i][j].rgbBlue)/3;
					RRINF[i][j].rgbGreen =(RRINF[i][j].rgbRed+RRINF[i][j].rgbGreen+RRINF[i][j].rgbBlue)/3;
					RRINF[i][j].rgbBlue =(RRINF[i][j].rgbRed+RRINF[i][j].rgbGreen+RRINF[i][j].rgbBlue)/3;
					break;
				}
				case 3:
					{
						RRINF[i][j].rgbRed = (RRINF[i][j].rgbRed+z)%256;
						RRINF[i][j].rgbGreen = (RRINF[i][j].rgbGreen+y)%256;
						RRINF[i][j].rgbBlue = (RRINF[i][j].rgbBlue+x)%256;
					break;
					}
				case 4:
					{
						RRINF[i][j].rgbRed = (RRINF[i][j].rgbRed+z)%256;
						RRINF[i][j].rgbGreen = (RRINF[i][j].rgbGreen+y)%256;
						RRINF[i][j].rgbBlue = (RRINF[i][j].rgbBlue+x)%256;
					break;
					}
				/*case 5:
					{

					break;
					}*/
				}
				
				write(fileStreamo, RRINF[i][j], fileInfoHeader.biBitCount / 8);
		}
		fileStream.seekg(linePadding, std::ios_base::cur);
		fileStreamo.seekp(linePadding, std::ios_base::cur);
	}//толкаем указатель на сдвиг с текущей позиции
 	
	write(fileStreamo, RRINF[0][0], 1);
	return 1;
}
 
unsigned char MAASK(const unsigned int byte, const unsigned int mask) {
	if (mask == 0) return 0;
	// определение количества нулевых бит справа от маски
	int maskBufer = mask, maskPadding = 0;
	// пока maskBufer != 1111 1111 сдвигай с заменой на 1
	while (!(maskBufer & 1)) {
		maskBufer >>= 1;
		maskPadding++;
	}
 
	// применение маски и смещение
	return (byte & mask) >> maskPadding;
	}