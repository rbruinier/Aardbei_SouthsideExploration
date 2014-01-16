/*
	
	Pyramid System - Vertex Shader Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "VertexShader.h"

VertexShader::VertexShader()
{
	d3dVertexShader	  = NULL;
	d3dVertexDeclaration = NULL;
}

VertexShader::~VertexShader()
{
}

int VertexShader::Destroy()
{
	if (d3dVertexDeclaration != NULL)
	{
		if (FAILED(d3dVertexDeclaration->Release()))
		{
			return E_FAIL;
		}
	}

	if (d3dVertexShader != NULL)
	{
		if (FAILED(d3dVertexShader->Release()))
		{
			return E_FAIL;
		}
	}

	return D3D_OK;
}
