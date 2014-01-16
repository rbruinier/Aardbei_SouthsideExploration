/*
	
	Pyramid System - Texture Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Texture.h"

// initiliazes common attributes
Texture::Texture()
{
	d3dTexture      = NULL;
	d3dDepthStencil = NULL;

	width  = 0;
	height = 0;
	size   = 0;
	levels = 1;
	usage  = 0;
	bpp    = 32;
	format = D3DFMT_UNKNOWN;
	pool   = D3DPOOL_DEFAULT;

	localData = NULL;
}

// destroys the object
Texture::~Texture()
{
}

// updates the texture surface with given data (will automaticly generate mipmaps when desired)
int Texture::Update(DWORD *pData)
{
	memcpy(localData, pData, size * 4);

	int nrLevels = 1;

	if (levels == 0)
	{
		nrLevels = d3dTexture->GetLevelCount();
	}

	int tempWidth  = width;
	int tempHeight = height;

	for (int i = 0; i < nrLevels; i++)
	{
		D3DLOCKED_RECT d3dLR;

		if (FAILED(d3dTexture->LockRect(i, &d3dLR, NULL, D3DLOCK_NOSYSLOCK)))
		{
			return E_FAIL;
		}

		UploadRawData(d3dLR.pBits, localData, tempWidth * tempHeight);

		if (FAILED(d3dTexture->UnlockRect(i)))
		{
			return E_FAIL;
		}

		if (levels == 0)
		{
			tempWidth  >>= 1;
			tempHeight >>= 1;

			if ((tempWidth != 0) && (tempHeight != 0))
			{
				ScaleRawData(localData, tempWidth, tempHeight, localData, tempWidth << 1, tempHeight << 1);
			}
		}
	}

	return D3D_OK;
}

// destroys the Direct3D texture
int Texture::Destroy()
{
	if (d3dTexture != NULL)
	{
		if (FAILED(d3dTexture->Release()))
		{
			return E_FAIL;
		}
	}

	if (d3dDepthStencil != NULL)
	{
		if (FAILED(d3dDepthStencil->Release()))
		{
			return E_FAIL;
		}
	}

	if (localData != NULL)	
	{
		delete [] localData;
	}

	return D3D_OK;
}

int Texture::TempDestroy()
{
	if (d3dTexture != NULL)
	{
		if (FAILED(d3dTexture->Release()))
		{
			return E_FAIL;
		}
	}

	if (d3dDepthStencil != NULL)
	{
		if (FAILED(d3dDepthStencil->Release()))
		{
			return E_FAIL;
		}
	}

	d3dTexture = NULL;
	d3dDepthStencil = NULL;

	return D3D_OK;
}

int Texture::Restore()
{
	return D3D_OK;
}

// rescales 32 bit pixel data to smaller sizes
int Texture::ScaleRawData(DWORD *pTarget, DWORD uiTargetWidth, DWORD uiTargetHeight, 
                          DWORD *pSource, DWORD uiSourceWidth, DWORD uiSourceHeight)
{
	int factorX = uiSourceWidth  / uiTargetWidth;
	int factorY = uiSourceHeight / uiTargetHeight;

	for (DWORD y = 0; y < uiTargetHeight; y++)
	{
		for (DWORD x = 0; x < uiTargetWidth; x++)
		{
			DWORD a1 = (*pSource >> 24) & 255;
			DWORD r1 = (*pSource >> 16) & 255;
			DWORD g1 = (*pSource >>  8) & 255;
			DWORD b1 = (*pSource >>  0) & 255;

			DWORD a2 = (*(pSource + 1) >> 24) & 255;
			DWORD r2 = (*(pSource + 1) >> 16) & 255;
			DWORD g2 = (*(pSource + 1) >>  8) & 255;
			DWORD b2 = (*(pSource + 1) >>  0) & 255;

			DWORD a3 = (*(pSource + uiSourceWidth) >> 24) & 255;
			DWORD r3 = (*(pSource + uiSourceWidth) >> 16) & 255;
			DWORD g3 = (*(pSource + uiSourceWidth) >>  8) & 255;
			DWORD b3 = (*(pSource + uiSourceWidth) >>  0) & 255;

			DWORD a4 = (*(pSource + uiSourceWidth + 1) >> 24) & 255;
			DWORD r4 = (*(pSource + uiSourceWidth + 1) >> 16) & 255;
			DWORD g4 = (*(pSource + uiSourceWidth + 1) >>  8) & 255;
			DWORD b4 = (*(pSource + uiSourceWidth + 1) >>  0) & 255;

			DWORD a = (a1 + a2 + a3 + a4) >> 2;
			DWORD r = (r1 + r2 + r3 + r4) >> 2;
			DWORD g = (g1 + g2 + g3 + g4) >> 2;
			DWORD b = (b1 + b2 + b3 + b4) >> 2;
	
			*pTarget = (a << 24) | (r << 16) | (g << 8) | b;

			pTarget++;

			pSource += factorX;
		}

		pSource += uiSourceWidth * (factorY - 1);
	}

	return D3D_OK;
}

// uploads and converts the raw 32 bit texture data to a locked Direct3D texture surface
int Texture::UploadRawData(void *pTarget, DWORD *pSource, DWORD nrPixels)
{
	if ((format == D3DFMT_A8R8G8B8) || (format == D3DFMT_X8R8G8B8)) 
	{
		DWORD *pDst = (DWORD*) pTarget;
		__asm {
			mov		ecx, [nrPixels]

			mov		esi, [pSource]
			mov		edi, [pDst]

			align 4

			rep		movsd
		}
		return D3D_OK;
	}

	return E_FAIL;
}

