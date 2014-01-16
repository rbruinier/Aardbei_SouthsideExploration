/*
	
	Pyramid System - Index Buffer Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "IndexBuffer.h"


// initiliazes common attributes
IndexBuffer::IndexBuffer()
{
	d3dIndexBuffer = NULL;

	size   = 0;
	format = D3DFMT_INDEX16;
	usage  = 0;
	pool   = D3DPOOL_DEFAULT;
}

// destroys the object
IndexBuffer::~IndexBuffer()
{
}

// updates the index buffer with the given data
int IndexBuffer::Update(void *pData, DWORD uiOffset, DWORD uiSize)
{
	if (d3dIndexBuffer == NULL)
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

	if (FAILED(d3dIndexBuffer->Lock(lockOffset, lockSize, &pVertices, flags)))
	{
		return E_FAIL;
	}

	memcpy(pVertices, pData, lockSize);

	if (FAILED(d3dIndexBuffer->Unlock()))
	{
		return E_FAIL;
	}

	return D3D_OK;
}


// destroys the index buffer
int IndexBuffer::Destroy()
{
	if (d3dIndexBuffer != NULL)
	{
		if (FAILED(d3dIndexBuffer->Release()))
		{
			return E_FAIL;
		}
	}

	return D3D_OK;
}

// destroys the index buffer temporary
int IndexBuffer::TempDestroy()
{
	if (d3dIndexBuffer != NULL)
	{
		if (FAILED(d3dIndexBuffer->Release()))
		{
			return E_FAIL;
		}
	}

	d3dIndexBuffer = NULL;

	return D3D_OK;
}

// recreates the index buffer
int IndexBuffer::Restore()
{
	return D3D_OK;
}

