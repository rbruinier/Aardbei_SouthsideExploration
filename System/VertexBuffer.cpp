/*
	
	Pyramid System - Vertex Buffer Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "VertexBuffer.h"

// initiliazes common attributes
VertexBuffer::VertexBuffer()
{
	d3dVertexBuffer = NULL;

	size  = 0;
	fvf   = 0;
	usage = 0;
	pool  = D3DPOOL_DEFAULT;

	vertexSize = 0;
}

// destroys the object
VertexBuffer::~VertexBuffer()
{
}

// updates the vertex buffer with the given data
int VertexBuffer::Update(void *pData, DWORD uiOffset, DWORD uiSize)
{
	if (d3dVertexBuffer == NULL)
	{
		return E_FAIL;
	}

	int lockOffset = 0; 
	int lockSize   = size; 

	if (uiOffset != -1)
	{
		lockOffset = uiOffset;
	}

	if (uiSize != -1)
	{
		lockSize = uiSize;
	}

	void* pVertices;

	DWORD flags = D3DLOCK_NOSYSLOCK;

	if (usage & D3DUSAGE_DYNAMIC)
	{
		flags |= D3DLOCK_DISCARD;
	}

	if (FAILED(d3dVertexBuffer->Lock(lockOffset, lockSize, &pVertices, flags)))
	{
		return E_FAIL;
	}

	memcpy(pVertices, pData, lockSize);

	if (FAILED(d3dVertexBuffer->Unlock()))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// destroys the vertex buffer
int VertexBuffer::Destroy()
{
	if (d3dVertexBuffer != NULL)
	{
		if (FAILED(d3dVertexBuffer->Release()))
		{
			return E_FAIL;
		}
	}

	return D3D_OK;
}

// destroys the vertex buffer temporary
int VertexBuffer::TempDestroy()
{
	if (d3dVertexBuffer != NULL)
	{
		if (FAILED(d3dVertexBuffer->Release()))
		{
			return E_FAIL;
		}
	}

	d3dVertexBuffer = NULL;

	return D3D_OK;
}

// recreates the vertex buffer
int VertexBuffer::Restore()
{
	return D3D_OK;
}