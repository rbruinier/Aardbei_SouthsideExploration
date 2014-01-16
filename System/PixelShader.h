/*
	
	Pyramid System - Pixel Shader Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __PixelShader_H__
#define __PixelShader_H__

#include <d3d9.h>

class PixelShader
{
public:
	friend class Pyramid;

	PixelShader();
	~PixelShader();

private:
	int Destroy();

	IDirect3DPixelShader9	*d3dPixelShader;
};

#endif