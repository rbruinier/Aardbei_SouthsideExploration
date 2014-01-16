/*
	
	Pyramid Engine - Frustum Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#include "Frustum.h"

#include "../System/Pyramid.h"
#include "../System/Matrix.h"

#include <math.h>

extern Pyramid *pyramid;

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

void Frustum::NormalizePlane(int uiSide)
{
	float magnitude = (float) sqrt((sides[uiSide][0] * sides[uiSide][0]) + 
	                               (sides[uiSide][1] * sides[uiSide][1]) + 
	                               (sides[uiSide][2] * sides[uiSide][2]));

	sides[uiSide][0] /= magnitude;
	sides[uiSide][1] /= magnitude;
	sides[uiSide][2] /= magnitude;
	sides[uiSide][3] /= magnitude; 
}

void Frustum::Update()
{
	float clip[16];

	Matrix matProjection, matView, matClip;

	pyramid->GetProjectionMatrix(matProjection);
	pyramid->GetViewMatrix(matView);

	matClip = matView * matProjection;

	memcpy(clip, &matClip, sizeof(Matrix));

	sides[PLANE_RIGHT][0] = clip[ 3] - clip[ 0];
	sides[PLANE_RIGHT][1] = clip[ 7] - clip[ 4];
	sides[PLANE_RIGHT][2] = clip[11] - clip[ 8];
	sides[PLANE_RIGHT][3] = clip[15] - clip[12];

	NormalizePlane(PLANE_RIGHT);

	sides[PLANE_LEFT][0] = clip[ 3] + clip[ 0];
	sides[PLANE_LEFT][1] = clip[ 7] + clip[ 4];
	sides[PLANE_LEFT][2] = clip[11] + clip[ 8];
	sides[PLANE_LEFT][3] = clip[15] + clip[12];

	NormalizePlane(PLANE_LEFT);

	sides[PLANE_BOTTOM][0] = clip[ 3] + clip[ 1];
	sides[PLANE_BOTTOM][1] = clip[ 7] + clip[ 5];
	sides[PLANE_BOTTOM][2] = clip[11] + clip[ 9];
	sides[PLANE_BOTTOM][3] = clip[15] + clip[13];

	NormalizePlane(PLANE_BOTTOM);

	sides[PLANE_TOP][0] = clip[ 3] - clip[ 1];
	sides[PLANE_TOP][1] = clip[ 7] - clip[ 5];
	sides[PLANE_TOP][2] = clip[11] - clip[ 9];
	sides[PLANE_TOP][3] = clip[15] - clip[13];

	NormalizePlane(PLANE_TOP);

	sides[PLANE_BACK][0] = clip[ 3] - clip[ 2];
	sides[PLANE_BACK][1] = clip[ 7] - clip[ 6];
	sides[PLANE_BACK][2] = clip[11] - clip[10];
	sides[PLANE_BACK][3] = clip[15] - clip[14];

	NormalizePlane(PLANE_BACK);

	sides[PLANE_FRONT][0] = clip[ 3] + clip[ 2];
	sides[PLANE_FRONT][1] = clip[ 7] + clip[ 6];
	sides[PLANE_FRONT][2] = clip[11] + clip[10];
	sides[PLANE_FRONT][3] = clip[15] + clip[14];

	NormalizePlane(PLANE_FRONT);
}

bool Frustum::PointInFrustum(float fX, float fY, float fZ)
{
	for (int i = 0; i < 6; i++)
	{
		if (((sides[i][0] * fX) + (sides[i][1] * fY) + (sides[i][2] * fZ) + sides[i][3]) <= 0)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::SphereInFrustum(float fX, float fY, float fZ, float fRadius)
{
	for (int i = 0; i < 6; i++)
	{
		if (((sides[i][0] * fX) + (sides[i][1] * fY) + (sides[i][2] * fZ) + sides[i][3]) <= -fRadius)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::BoxInFrustum(float fX, float fY, float fZ, float fX2, float fY2, float fZ2)
{
	for (int i = 0; i < 6; i++)
	{
		if (sides[i][0] * fX  + sides[i][1] * fY  + sides[i][2] * fZ  + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX2 + sides[i][1] * fY  + sides[i][2] * fZ  + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX  + sides[i][1] * fY2 + sides[i][2] * fZ  + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX2 + sides[i][1] * fY2 + sides[i][2] * fZ  + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX  + sides[i][1] * fY  + sides[i][2] * fZ2 + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX2 + sides[i][1] * fY  + sides[i][2] * fZ2 + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX  + sides[i][1] * fY2 + sides[i][2] * fZ2 + sides[i][3] > 0)  continue;
		if (sides[i][0] * fX2 + sides[i][1] * fY2 + sides[i][2] * fZ2 + sides[i][3] > 0)  continue;

		return false;
	}

	return true;
}