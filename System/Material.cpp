/*
	
	Pyramid System - Material Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Material.h"     

Material::Material()
{
	SetDiffuse(1, 1, 1, 1);
	SetAmbient(1, 1, 1, 1);
	SetSpecular(0, 0, 0, 0);
	SetEmissive(0, 0, 0, 0);
	SetPower(0);
}

Material::~Material()
{
}

void Material::SetDiffuse(float fR, float fG, float fB, float fA)
{
	diffuse.a = fA;
	diffuse.r = fR;
	diffuse.g = fG;
	diffuse.b = fB;
}

void Material::SetAmbient(float fR, float fG, float fB, float fA)
{
	ambient.a = fA;
	ambient.r = fR;
	ambient.g = fG;
	ambient.b = fB;
}

void Material::SetSpecular(float fR, float fG, float fB, float fA)
{
	specular.a = fA;
	specular.r = fR;
	specular.g = fG;
	specular.b = fB;
}

void Material::SetEmissive(float fR, float fG, float fB, float fA)
{
	emissive.a = fA;
	emissive.r = fR;
	emissive.g = fG;
	emissive.b = fB;
}

void Material::SetPower(float fPower)
{
	power = fPower;
}
