/*
	
	Pyramid System - Texture Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Texture_H__
#define __Texture_H__

#include <d3d9.h>

class Texture
{
public:
	friend class Pyramid;

	Texture();
	~Texture();

	int Update(DWORD *pData);

private:
	int Destroy();
	int TempDestroy();
	int Restore();

	int UploadRawData(void *pTarget, DWORD *pSource, DWORD nrPixels);
	int ScaleRawData(DWORD *pTarget, DWORD uiTargetWidth, DWORD uiTargetHeight, 
	                 DWORD *pSource, DWORD uiSourceWidth, DWORD uiSourceHeight);


	IDirect3DTexture9 *d3dTexture;
	IDirect3DSurface9 *d3dDepthStencil;
	IDirect3DSurface9 *d3dSurface;

	DWORD     width;
	DWORD     height;
	DWORD     size;
	DWORD     levels;
	DWORD     usage;
	DWORD     bpp;
	D3DFORMAT format;
	D3DPOOL	  pool;

	bool      multisample;

	DWORD     *localData;
};

#endif