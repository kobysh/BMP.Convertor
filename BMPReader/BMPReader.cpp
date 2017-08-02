// BMPReader.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int main()
{
	printf(">>BMP Readear<<\n\n");

	char *fname = (char *)malloc(256);
	printf("Enter input filename: ");
	scanf("%s", fname);
	getchar();

	char n;
	printf("\nConvert to negative? (y/n) - ");
	n = getchar();
	getchar();

	char m;
	printf("\nConvert to monochrome? (y/n) - ");
	m = getchar();

	if ((n != 'y') && (m != 'y'))
	{
		printf("\nNo action selected for processing.\nComplete.\n ");
		system("pause");
		return NULL;
	}
	

	printf("\nStarting...\n");
	FILE *pFile = fopen(fname, "rb");

	//проверка на наличие(открытие) файла
	if (!pFile) { printf("\nError. Can not open %s.\n", fname); system("pause"); return NULL; }

	// считываем заголовок файла
	BITMAPFILEHEADER header;

	header.bfType = read_u16(pFile);
	header.bfSize = read_u32(pFile);
	header.bfReserved1 = read_u16(pFile);
	header.bfReserved2 = read_u16(pFile);
	header.bfOffBits = read_u32(pFile);

	//проверка, что загружен именно BMP (проверка сигнатуры файла)
	if (header.bfType != 0x4d42 && header.bfType != 0x4349 && header.bfType != 0x5450) { fclose(pFile); printf("Error. Invalid signature of BMP file.\n"); system("pause");  return NULL; }

	// считываем заголовок изображения
	BITMAPINFOHEADER bmiHeader;

	bmiHeader.biSize = read_u32(pFile);
	bmiHeader.biWidth = read_s32(pFile);
	bmiHeader.biHeight = read_s32(pFile);
	bmiHeader.biPlanes = read_u16(pFile);
	bmiHeader.biBitCount = read_u16(pFile);
	bmiHeader.biCompression = read_u32(pFile);
	bmiHeader.biSizeImage = read_u32(pFile);
	bmiHeader.biXPelsPerMeter = read_s32(pFile);
	bmiHeader.biYPelsPerMeter = read_s32(pFile);
	bmiHeader.biClrUsed = read_u32(pFile);
	bmiHeader.biClrImportant = read_u32(pFile);

	//проверки на битность BMP-файла (только 24-bit изображения)
	if (bmiHeader.biBitCount != 24) { fclose(pFile); printf("Error. Invalid BMP file (24-bit BMP files only). \n"); system("pause");  return NULL; }

	// инициализация массива пикселей
	RGBQUAD *pixels = new RGBQUAD[bmiHeader.biHeight * bmiHeader.biWidth];

	// читаем байты цветов
	for (int i = 0; i < bmiHeader.biHeight * bmiHeader.biWidth; i++) {
		pixels[i].rgbBlue = getc(pFile);
		pixels[i].rgbGreen = getc(pFile);
		pixels[i].rgbRed = getc(pFile);
	}
	fclose(pFile);

/*=====НЕГАТИВ=====*/
	if (n == 'y')
	{	
		printf("\nConvert to negative... ");

		char negative[256];
		strcpy(negative, "negative_");
		strcat(negative, fname);

		FILE *oFile = fopen(negative, "wb");

		// записываем заголовок файла
		write_u16(header.bfType, oFile);
		write_u32(header.bfSize, oFile);
		write_u16(header.bfReserved1, oFile);
		write_u16(header.bfReserved2, oFile);
		write_u32(header.bfOffBits, oFile);

		// записываем заголовок изображения
		write_u32(bmiHeader.biSize, oFile);
		write_s32(bmiHeader.biWidth, oFile);
		write_s32(bmiHeader.biHeight, oFile);
		write_u16(bmiHeader.biPlanes, oFile);
		write_u16(bmiHeader.biBitCount, oFile);
		write_u32(bmiHeader.biCompression, oFile);
		write_u32(bmiHeader.biSizeImage, oFile);
		write_s32(bmiHeader.biXPelsPerMeter, oFile);
		write_s32(bmiHeader.biYPelsPerMeter, oFile);
		write_u32(bmiHeader.biClrUsed, oFile);
		write_u32(bmiHeader.biClrImportant, oFile);

		// записываем байты цветов
		for (int i = 0; i < bmiHeader.biHeight * bmiHeader.biWidth; i++) {
			putc(~pixels[i].rgbBlue & 0xFF, oFile);
			putc(~pixels[i].rgbGreen & 0xFF, oFile);
			putc(~pixels[i].rgbRed & 0xFF, oFile);
		}

		fclose(oFile);
		
		printf("OK - %s", negative);
	}
	else printf("\nNegative is not selected.");

/*====МОНОХРОМНОЕ====*/
	if (m == 'y')
	{
		printf("\nConvert to monochrome... ");

		char monoch[256];
		strcpy(monoch, "monochrome_");
		strcat(monoch, fname);

		FILE *oFile = fopen(monoch, "wb");

		// записываем заголовок файла
		write_u16(header.bfType, oFile);
		write_u32(header.bfSize, oFile);
		write_u16(header.bfReserved1, oFile);
		write_u16(header.bfReserved2, oFile);
		write_u32(header.bfOffBits, oFile);

		// записываем заголовок изображения
		write_u32(bmiHeader.biSize, oFile);
		write_s32(bmiHeader.biWidth, oFile);
		write_s32(bmiHeader.biHeight, oFile);
		write_u16(bmiHeader.biPlanes, oFile);
		write_u16(bmiHeader.biBitCount, oFile);
		write_u32(bmiHeader.biCompression, oFile);
		write_u32(bmiHeader.biSizeImage, oFile);
		write_s32(bmiHeader.biXPelsPerMeter, oFile);
		write_s32(bmiHeader.biYPelsPerMeter, oFile);
		write_u32(bmiHeader.biClrUsed, oFile);
		write_u32(bmiHeader.biClrImportant, oFile);

		// записываем байты цветов
		int mcol;
		for (int i = 0; i < bmiHeader.biHeight * bmiHeader.biWidth; i++) {
			//для перевода изображения в монохромное используем формулу Y=R*0.21+G*0.72+B*0.07
			mcol = pixels[i].rgbBlue*0.07 + pixels[i].rgbGreen*0.72 + pixels[i].rgbRed*0.21;

			putc(mcol, oFile);
			putc(mcol, oFile);
			putc(mcol, oFile);
		}

		fclose(oFile);

		printf("OK - %s", monoch);
	}
	else printf("\nMonochrome is not selected.\n");

	printf("\nComplete.\n");
	system("pause");
	return 0;
}


static unsigned short read_u16(FILE *fp)
{
	unsigned char b0, b1;

	b0 = getc(fp);
	b1 = getc(fp);

	return ((b1 << 8) | b0);
}


static unsigned int read_u32(FILE *fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


static int read_s32(FILE *fp)
{
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

static void write_u16(unsigned short input, FILE *fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
}

static void write_u32(unsigned int input, FILE *fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
	putc(input >> 16, fp);
	putc(input >> 24, fp);
}

static void write_s32(int input, FILE *fp)
{
	putc(input, fp);
	putc(input >> 8, fp);
	putc(input >> 16, fp);
	putc(input >> 24, fp);
}
