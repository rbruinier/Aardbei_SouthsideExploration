/*
	
	Pyramid Engine - Camera Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Camera_H__
#define __Camera_H__

#include "../System/Vector.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetLocation(float fX, float fY, float fZ);
	void SetTarget(float fX, float fY, float fZ);

	void SetLocation(Vector &pLocation);
	void SetTarget(Vector &pTarget);

	void SetRoll(float fRoll);
	void SetFov(float fFov);
	void SetAspect(float fAspect);

	void SetNearPlane(float fDistance);
	void SetFarPlane(float fDistance);

	void Update();

	Vector location;
	Vector target;

protected:

private:
	float  roll;
	float  fov;
	float  aspect;
	float  nearPlane;
	float  farPlane;
};

#endif

