/*
	
	Pyramid System - Material Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Material_H__
#define __Material_H__

#include <d3d9.h>

class Material
{
public:
	Material();
	~Material();

	void SetDiffuse(float fR, float fG, float fB, float fA = 1.0f);
	void SetAmbient(float fR, float fG, float fB, float fA = 1.0f);
	void SetSpecular(float fR, float fG, float fB, float fA = 0.0f);
	void SetEmissive(float fR, float fG, float fB, float fA = 0.0f);
	void SetPower(float fPower);

    D3DCOLORVALUE diffuse;
    D3DCOLORVALUE ambient;
    D3DCOLORVALUE specular;
    D3DCOLORVALUE emissive;

    float         power;
};

#endif
