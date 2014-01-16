/*
	
	Pyramid System - Vertex Shader Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __VertexShader_H__
#define __VertexShader_H__

#include <d3d9.h>

class VertexShader
{
public:
	friend class Pyramid;

	VertexShader();
	~VertexShader();

private:
	int Destroy();

	IDirect3DVertexShader9      *d3dVertexShader;
	IDirect3DVertexDeclaration9 *d3dVertexDeclaration;
};

#endif