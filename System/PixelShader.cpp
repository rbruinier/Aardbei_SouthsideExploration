/*
	
	Pyramid System - Pixel Shader Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "PixelShader.h"

PixelShader::PixelShader()
{
	d3dPixelShader = NULL;
}
	

PixelShader::~PixelShader()
{
}

int PixelShader::Destroy()
{
	if (d3dPixelShader != NULL)
	{
		if (FAILED(d3dPixelShader->Release()))
		{
			return E_FAIL;
		}
	}

	return D3D_OK;
}
