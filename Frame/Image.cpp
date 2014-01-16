/*
	
	Pyramid Tools - Image Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Image.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <ocidl.h>
#include <olectl.h>

#ifndef R
	#define R(x) ((x >> 16) & 255)
#endif

#ifndef G
	#define G(x) ((x >> 8) & 255)
#endif

#ifndef B
	#define B(x) ((x >> 0) & 255)
#endif

Image::Image(char* pFilename)
{
	data = NULL;

	width  = 0;
	height = 0;

	valid = false;

	if (strstr(pFilename, ".jpg") || strstr(pFilename, ".bmp"))
	{
		LoadImage(pFilename);
	}

	if (valid)
	{
		for (int i = 0; i < width * height; i++)
		{
			//data[i] |= (DWORD) 255 << 24;
			if (data[i] != 0)
			{
				data[i] |= (DWORD) ((data[i] & 0xff0000) >> 16) << 24;
			}
		}

		return;
	}

	if (strstr(pFilename, ".map"))
	{
		LoadNormalMap(pFilename);
	}
}

Image::Image(void* pData, int nrBytes)
{
	data = NULL;

	width  = 0;
	height = 0;

	valid = false;

	if ((pData != NULL) && (nrBytes != 0))
	{
		LoadImage(pData, nrBytes);
	}

	if (valid)
	{
		for (int i = 0; i < width * height; i++)
		{
			data[i] |= (DWORD) 255 << 24;
		}
	}
}

Image::~Image()
{
	if (data != NULL)
	{
		delete [] data;
	}
}

void Image::LoadNormalMap(char* pFilename)
{
	HANDLE hFile = CreateFile(pFilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

	DWORD dwBytesRead = 0;
	ReadFile(hFile, &width, 4, &dwBytesRead, NULL);
	ReadFile(hFile, &height, 4, &dwBytesRead, NULL);

	data = new DWORD[width * height];

	ReadFile(hFile, data,  width * height * 4, &dwBytesRead, NULL);

	for (int b = 0; b < 1; b++)
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int col1 = data[(((y - 1) & (height - 1)) * width) + ((x - 0) & (width - 1))];
				int col2 = data[(((y + 1) & (height - 1)) * width) + ((x + 0) & (width - 1))];
				int col3 = data[(((y - 0) & (height - 1)) * width) + ((x - 1) & (width - 1))];
				int col4 = data[(((y + 0) & (height - 1)) * width) + ((x + 1) & (width - 1))];

				int col = (((R(col1) + R(col2) + R(col3) + R(col4)) >> 2) << 16) |
						  (((G(col1) + G(col2) + G(col3) + G(col4)) >> 2) <<  8) |
						  (((B(col1) + B(col2) + B(col3) + B(col4)) >> 2) <<  0);

				data[(y * width) + x] = col;
			}
		}
	}

	for (int i = 0; i < width * height; i++)
	{
		int a, r, g, b;

		a = (data[i] >> 24) & 255;
		r = (data[i] >> 16) & 255;
		g = (data[i] >>  8) & 255;
		b = (data[i] >>  0) & 255;

		data[i] = (a << 24) | (r << 16) | (b << 8) | g;
	}

	valid = true;
}

void Image::LoadImage(char* pFilename)
{
	static HDC hdcnull = GetDC(NULL);
	static LPPICTURE gpPicture;
	
	HANDLE hFile = CreateFile(pFilename, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);

	LPVOID pvData = NULL;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);

	pvData = GlobalLock(hGlobal);

	DWORD dwBytesRead = 0;
	BOOL bRead = ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
	GlobalUnlock(hGlobal);
	CloseHandle(hFile);

	LPSTREAM pstm = NULL;
	HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);

	if (gpPicture) gpPicture->Release();

	hr = ::OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID *)&gpPicture);
	pstm->Release();

	long hmWidth;
	long hmHeight;
	gpPicture->get_Width(&hmWidth);
	gpPicture->get_Height(&hmHeight);

	HDC hdc = CreateCompatibleDC(hdcnull);

	#define HIMETRIC_INCH 2540

	width	= MulDiv(hmWidth, GetDeviceCaps(hdc, LOGPIXELSX), HIMETRIC_INCH);
	height	= MulDiv(hmHeight, GetDeviceCaps(hdc, LOGPIXELSY), HIMETRIC_INCH);

	HBITMAP bmp = CreateCompatibleBitmap(hdcnull, width, height);
	SelectObject(hdc, bmp);

	gpPicture->Render(hdc, 0, 0, width, height, 0, hmHeight, hmWidth, -hmHeight, NULL);

	BITMAPINFOHEADER lpbi;
	ZeroMemory(&lpbi,sizeof(BITMAPINFOHEADER));
	lpbi.biSize        = sizeof(BITMAPINFOHEADER);
	lpbi.biWidth       = width;
	lpbi.biHeight      = height;
	lpbi.biPlanes      = 1;
	lpbi.biBitCount    = 32;
	lpbi.biCompression = BI_RGB;

	data = new DWORD[width * height];

	for (int i = 0; i < height; i++)
	{
		GetDIBits(hdc, bmp, height - i - 1, 1, &data[i * width], (LPBITMAPINFO)&lpbi, DIB_RGB_COLORS);
	}

	valid = true;
}

void Image::LoadImage(void* pData, int nrBytes)
{
	static HDC hdcnull = GetDC(NULL);
	static LPPICTURE gpPicture;

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nrBytes);

	LPVOID pvData = GlobalLock(hGlobal);

	if (pvData != NULL)
	{
		memcpy(pvData, pData, nrBytes);
	}

	GlobalUnlock(hGlobal);

	LPSTREAM pstm = NULL;
	HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);

	if (gpPicture) gpPicture->Release();

	hr = ::OleLoadPicture(pstm, nrBytes, FALSE, IID_IPicture, (LPVOID *)&gpPicture);
	pstm->Release();

	long hmWidth;
	long hmHeight;
	gpPicture->get_Width(&hmWidth);
	gpPicture->get_Height(&hmHeight);

	HDC hdc = CreateCompatibleDC(hdcnull);

	#define HIMETRIC_INCH 2540

	width	= MulDiv(hmWidth, GetDeviceCaps(hdc, LOGPIXELSX), HIMETRIC_INCH);
	height	= MulDiv(hmHeight, GetDeviceCaps(hdc, LOGPIXELSY), HIMETRIC_INCH);

	HBITMAP bmp = CreateCompatibleBitmap(hdcnull, width, height);
	SelectObject(hdc, bmp);

	gpPicture->Render(hdc, 0, 0, width, height, 0, hmHeight, hmWidth, -hmHeight, NULL);

	BITMAPINFOHEADER lpbi;
	ZeroMemory(&lpbi,sizeof(BITMAPINFOHEADER));
	lpbi.biSize        = sizeof(BITMAPINFOHEADER);
	lpbi.biWidth       = width;
	lpbi.biHeight      = height;
	lpbi.biPlanes      = 1;
	lpbi.biBitCount    = 32;
	lpbi.biCompression = BI_RGB;

	data = new DWORD[width * height];

	for (int i = 0; i < height; i++)
	{
		GetDIBits(hdc, bmp, height - i - 1, 1, &data[i * width], (LPBITMAPINFO)&lpbi, DIB_RGB_COLORS);
	}

	valid = true;
}