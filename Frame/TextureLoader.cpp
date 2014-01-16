/*
	
	Pyramid Tools - Texture Loader Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "TextureLoader.h"

#include "../System/Pyramid.h"
#include "../System/Texture.h"

extern DWORD* loadATSFromMem(byte* atsMem, int &width, int &height);

#include "Image.h"

extern Pyramid* pyramid;

TextureLoader::TextureLoader()
{
	nrTextures = 0;
}

TextureLoader::~TextureLoader()
{
	int i;

	for (i = 0; i < nrTextures; i++)
	{
		delete image[i];
	}
}

void TextureLoader::Load(unsigned char* atsData, char* pName, bool bMipMap, int options)
{
	int width, height;

	DWORD* data = loadATSFromMem(atsData, width, height);

	if (data != NULL)
	{
		if (options == 0)
		{
			for (int i = 0; i < width * height; i++)
			{
				if (data[i] != 0)
				{
					data[i] |= (DWORD) ((data[i] & 0xff0000) >> 16) << 24;
				}
			}
		}
		else if (options == 1)
		{
			for (int i = 0; i < width * height; i++)
			{
				if (data[i] != 0)
				{
					int r = (data[i] & 0xff0000) >> 16;
					int g = (data[i] & 0xff00) >> 8;
					int b = (data[i] & 0xff);

					int fade = (r + g + b) / 3;

					if (fade < 20)
					{
						data[i] |= (DWORD)fade << 24;
					}
					else
					{
						data[i] |= 0xff000000;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < width * height; i++)
			{
				if ((data[i] & 0xffffff) == options)
				{
					data[i] = 0xff000000 | (data[i] & 0xffffff);
				}
				else
				{
					data[i] = 0x00000000 | (data[i] & 0xffffff);
				}
			}
		}

		pyramid->CreateTexture(width, height, 32, bMipMap, false, false, &texture[nrTextures]);

		texture[nrTextures]->Update(data);

		name[nrTextures] = pName;

		nrTextures++;
	}
}

void TextureLoader::Load(char *pFilename, char *pName, bool bMipmap)
{
	image[nrTextures] = new Image(pFilename);

 	if (image[nrTextures]->valid)
	{
		pyramid->CreateTexture(image[nrTextures]->width, image[nrTextures]->height, 32, 
							   bMipmap, false, false, &texture[nrTextures]);

		texture[nrTextures]->Update(image[nrTextures]->data);

		name[nrTextures] = pName;

		nrTextures++;
	}
}


void TextureLoader::Load(void *pData, int nrBytes, char *pName, bool bMipmap)
{
	image[nrTextures] = new Image(pData, nrBytes);

 	if (image[nrTextures]->valid)
	{
		pyramid->CreateTexture(image[nrTextures]->width, image[nrTextures]->height, 32, 
							   bMipmap, false, false, &texture[nrTextures]);

		texture[nrTextures]->Update(image[nrTextures]->data);

		name[nrTextures] = pName;

		nrTextures++;
	}
}

void TextureLoader::Load(DWORD *pData, DWORD uiWidth, DWORD uiHeight, char *pName, bool bMipmap)
{
	pyramid->CreateTexture(uiWidth, uiHeight, 32,bMipmap, false, false, &texture[nrTextures]);

	texture[nrTextures]->Update(pData);

	name[nrTextures] = pName;

	nrTextures++;
}

void TextureLoader::Destroy()
{
}

Texture *TextureLoader::GetTexture(char *pName)
{
	for (int i = 0; i < nrTextures; i++)
	{
		if (strcmp(name[i], pName) == 0)
		{
			return texture[i];
		}
	}

	return NULL;
}

Texture * TextureLoader:: operator [](char *pName)
{
	return GetTexture(pName);
}