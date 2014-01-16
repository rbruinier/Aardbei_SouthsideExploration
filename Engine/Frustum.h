/*
	
	Pyramid Engine - Frustum Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Frustum_H__
#define __Frustum_H__

class Frustum
{
public:
	enum PLANE_SIDE
	{
		PLANE_RIGHT	 = 0,
		PLANE_LEFT	 = 1,
		PLANE_BOTTOM = 2,
		PLANE_TOP    = 3,
		PLANE_BACK	 = 4,
		PLANE_FRONT	 = 5
	}; 

	Frustum();
	~Frustum();

	void Update();

	bool PointInFrustum(float fX, float fY, float fZ);
	bool SphereInFrustum(float fX, float fY, float fZ, float fRadius);
	bool BoxInFrustum(float fX, float fY, float fZ, float fX2, float fY2, float fZ2);

private:
	void NormalizePlane(int uiSide);

	float sides[6][4];
};

#endif
