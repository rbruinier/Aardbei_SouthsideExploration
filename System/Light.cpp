/*
	
	Pyramid System - Light Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Light.h"	

#include <math.h>

Light::Light()
{
/*
	setType(D3DLIGHT_POINT);
	setDiffuse(r, g, b, a); 
	setAmbient(0, 0, 0, 0);
	setRange((float)sqrt(FLT_MAX));
	setSpecular(r, g, b, a);
    setAttenuation(1, 0, 0);
*/
	
	SetType(LIGHT_POINT);

	SetDiffuse(1, 1, 1, 1);
	SetSpecular(1, 1, 1, 1);
	SetAmbient(0, 0, 0, 0);

	SetRange((float)sqrt(FLT_MAX));

    SetAttenuation(1, 0, 0);
	SetThetaPhi(1.f, 2.f);
	SetFalloff(1.f);

	SetLocation(0, 0, 0);
	SetDirection(0, 1, 0);
}

Light::~Light()
{
}

void Light::SetType(PYRAMID_LIGHT_TYPE iType)
{
	type = (D3DLIGHTTYPE) iType;
}

void Light::SetDiffuse(float fR, float fG, float fB, float fA)
{
	diffuse.r = fR;
	diffuse.g = fG;
	diffuse.b = fB;
	diffuse.a = fA;
}

void Light::SetAmbient(float fR, float fG, float fB, float fA)
{
	ambient.r = fR;
	ambient.g = fG;
	ambient.b = fB;
	ambient.a = fA;
}

void Light::SetSpecular(float fR, float fG, float fB, float fA)
{
	specular.r = fR;
	specular.g = fG;
	specular.b = fB;
	specular.a = fA;
}

void Light::SetRange(float fRange)
{
	range = fRange;
}

void Light::SetLocation(float fX, float fY, float fZ)
{
	location.x = fX;
	location.y = fY;
	location.z = fZ;
}

void Light::SetDirection(float fX, float fY, float fZ)
{
	direction.x = fX;
	direction.y = fY;
	direction.z = fZ;
}

void Light::SetFalloff(float fFalloff)
{
	falloff = fFalloff;
}

void Light::SetAttenuation(float fAtt0, float fAtt1, float fAtt2)
{
	attenuation0 = fAtt0;
	attenuation1 = fAtt1;
	attenuation2 = fAtt2;
}

void Light::SetThetaPhi(float fTheta, float fPhi)
{
	theta = fTheta;
	phi   = fPhi;
}