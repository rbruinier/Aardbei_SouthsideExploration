/*
	
	Pyramid Tools - Texture Loader Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __TextureLoader_H__
#define __TextureLoader_H__

#include <windows.h>

class Texture;
class Image;

class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	void Destroy();
	void Load(unsigned char* atsData, char* pName, bool bMipMap, int options);
	void Load(char *pFilename, char *pName, bool bMipmap);
	void Load(void *pData, int nrBytes, char *pName, bool bMipmap);
	void Load(DWORD *pData, DWORD uiWidth, DWORD uiHeight, char *pName, bool bMipmap);

	Texture *GetTexture(char *pName);

	Texture * operator[](char *pName);

private:
	char* name[1024];
	Texture* texture[1024];
	Image* image[1024];

	int nrTextures;
};


#endif