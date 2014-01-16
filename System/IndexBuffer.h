/*
	
	Pyramid System - Index Buffer Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __IndexBuffer_H__
#define __IndexBuffer_H__

#include <d3d9.h>

class IndexBuffer
{
public:
	friend class Pyramid;

	IndexBuffer();
	~IndexBuffer();

	int Update(void *pData, DWORD uiOffset = -1, DWORD uiSize = -1);

private:
	int Destroy();
	int TempDestroy();
	int Restore();

	IDirect3DIndexBuffer9 *d3dIndexBuffer;

	DWORD     size;
	DWORD     usage;
	D3DFORMAT format;
	D3DPOOL	  pool;
};

#endif