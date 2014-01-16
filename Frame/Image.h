/*
	
	Pyramid Tools - Image Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Image_H__
#define __Image_H__


#include <windows.h>

class Image
{
public:
	Image(char *pFilename);
	Image(void *pData, int nrBytes);
	~Image();

	int width;
	int height;

	DWORD *data;

	bool valid;

private:
	void LoadImage(char *pFilename);
	void LoadImage(void *pData, int nrBytes);

	void LoadNormalMap(char *pFilename);
};


#endif