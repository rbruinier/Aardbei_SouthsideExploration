/*
	
	Pyramid System - Light Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Light_H__
#define __Light_H__

#include <d3d9.h>

enum PYRAMID_LIGHT_TYPE
{
	LIGHT_POINT       = 1,
	LIGHT_SPOT        = 2,
	LIGHT_DIRECTIONAL = 3
};

class Light
{
public:
	Light();
	~Light();

	void SetType(PYRAMID_LIGHT_TYPE iType);

	void SetDiffuse(float fR, float fG, float fB, float fA = 1.0f);
	void SetAmbient(float fR, float fG, float fB, float fA = 1.0f);
	void SetSpecular(float fR, float fG, float fB, float fA = 0.0f);

	void SetRange(float fRange);

	void SetLocation(float fX, float fY, float fZ);
	void SetDirection(float fX, float fY, float fZ);

	void SetFalloff(float fFalloff);

	void SetAttenuation(float fAtt0, float fAtt1, float fAtt2);

	void SetThetaPhi(float fTheta, float fPhi);

private:
    D3DLIGHTTYPE  type;

    D3DCOLORVALUE diffuse;
    D3DCOLORVALUE specular;
    D3DCOLORVALUE ambient;

    D3DVECTOR     location;
    D3DVECTOR     direction;

    float         range;
    float         falloff;

    float         attenuation0;
    float         attenuation1;
    float         attenuation2;

    float         theta;
    float         phi;
};

#endif
