/*
	
	Pyramid System - Vertex Buffer Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __VertexBuffer_H__
#define __VertexBuffer_H__

#include <d3d9.h>

class VertexBuffer
{
public:
	friend class Pyramid;

	VertexBuffer();
	~VertexBuffer();

	int Update(void *pData, DWORD uiOffset = -1, DWORD uiSize = -1);

	IDirect3DVertexBuffer9 *d3dVertexBuffer;

private:
	int Destroy();
	int TempDestroy();
	int Restore();


	DWORD   size;
	DWORD   vertexSize;
	DWORD   usage;
	DWORD   fvf;
	D3DPOOL	pool;
};

#endif