/*
	
	Pyramid Engine - Camera Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#include "Camera.h"

#include <math.h>

#include "../System/Pyramid.h"
#include "../System/Matrix.h"

extern Pyramid* pyramid;

Camera::Camera()
{
	SetLocation(0, 0, -10);
	SetTarget(0, 0, 0);
	SetRoll(0);
	SetFov(0.80f);
	SetAspect(0.75f);
	SetNearPlane(0.01f);
	SetFarPlane(1000.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	float  fLength;
	Vector vAt      = target;
	Vector vFrom    = location;
	Vector vWorldUp = Vector(0, 1, 0);

    Vector vView    = vAt - vFrom;

	vView = vView.Normalize();

    float fDotProduct = vWorldUp.DotProduct(vView);

    Vector vUp = vWorldUp - (vView * fDotProduct);

    if (1e-6f > (fLength = vUp.Magnitude())) 
	{
        vUp = Vector(0.0f, 1.0f, 0.0f) - (vView * vView.y);
        if (1e-6f > (fLength = vUp.Magnitude())) 
		{
            vUp = Vector(0.0f, 0.0f, 1.0f) - (vView * vView.z);
            fLength = vUp.Magnitude();
        }
    }

    vUp = vUp.Scale(1.0f / fLength);

    Vector vRight = vUp.CrossProduct(vView);
  
	Matrix matView, matRoll, matProjection;

    matView._11 = vRight.x; matView._12 = vUp.x; matView._13 = vView.x;
    matView._21 = vRight.y; matView._22 = vUp.y; matView._23 = vView.y;
    matView._31 = vRight.z; matView._32 = vUp.z; matView._33 = vView.z;

    matView._41 = -vFrom.DotProduct(vRight);
    matView._42 = -vFrom.DotProduct(vUp);
    matView._43 = -vFrom.DotProduct(vView);

	matRoll = Matrix::RotateZ(roll * (_PI / 180.f));

	matView = matView * matRoll;

	pyramid->SetViewMatrix(matView);

	float w = aspect * (float) (cos(fov / 2.0f) / sin(fov / 2.0f));
	float h =   1.0f * (float) (cos(fov / 2.0f) / sin(fov / 2.0f));
    float Q = farPlane / (farPlane - nearPlane);

    matProjection._11 = w;
    matProjection._22 = h;
    matProjection._33 = Q;
    matProjection._34 = 1.0f;
    matProjection._43 = -Q * nearPlane;
	matProjection._44 = 0.0f;

    pyramid->SetProjectionMatrix(matProjection);
}

void Camera::SetLocation(float fX, float fY, float fZ)
{
	location.x = fX;
	location.y = fY;
	location.z = fZ;
}

void Camera::SetTarget(float fX, float fY, float fZ)
{
	target.x = fX;
	target.y = fY;
	target.z = fZ;
}

void Camera::SetLocation(Vector &pLocation)
{
	location = pLocation;
}

void Camera::SetTarget(Vector &pTarget)
{
	target = pTarget;
}

void Camera::SetRoll(float fRoll)
{
	roll = fRoll;
}

void Camera::SetFov(float fFov)
{
	fov = fFov;
}

void Camera::SetAspect(float fAspect)
{
	aspect = fAspect;
}

void Camera::SetNearPlane(float fDistance)
{
	nearPlane = fDistance;
}

void Camera::SetFarPlane(float fDistance)
{
	farPlane = fDistance;
}