/*
	
	Pyramid System - Vector Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Vector.h"
#include "Matrix.h"

#include <math.h>

Vector::Vector()
{
	x = y = z = 0;
}

Vector::Vector(float fX, float fY, float fZ)
{
	x = fX;
	y = fY;
	z = fZ;
}

Vector::~Vector()
{
}

Vector &Vector::operator = (const Vector &pV)
{
	x = pV.x;
	y = pV.y;
	z = pV.z;

	return *this;	
}

Vector Vector::operator - (const Vector &pV) const
{
	return Subtract(pV);
}

Vector Vector::operator + (const Vector &pV) const
{
	return Add(pV);
}

Vector Vector::operator * (const Vector &pV) const
{
	return Multiply(pV);
}

Vector Vector::operator * (const float fScale) const
{
	return Scale(fScale);
}

Vector Vector::operator / (const Vector &pV) const
{
	return Divide(pV);
}

Vector Vector::operator / (const float fScale) const
{
	return Scale(1.f / fScale);
}

Vector &Vector::operator -= (const Vector &pV)
{
	*this = Subtract(pV);

	return *this;
}

Vector &Vector::operator += (const Vector &pV)
{
	*this = Add(pV);

	return *this;
}

Vector &Vector::operator *= (const Vector &pV)
{
	*this = Multiply(pV);

	return *this;
}

Vector &Vector::operator *= (const float fScale)
{
	*this = Scale(fScale);

	return *this;
}

Vector &Vector::operator /= (const Vector &pV)
{
	*this = Divide(pV);

	return *this;
}

float Vector::Magnitude() const
{
	return (float) sqrt((x * x) + (y * y) + (z * z));
}

Vector Vector::Flip() const
{
	return Vector(-x, -y, -z);
}

Vector Vector::Normalize() const
{
	float lengthInv = 1.0f / (float) sqrt((x * x) + (y * y) + (z * z));
	
	return Vector(x * lengthInv, y * lengthInv, z * lengthInv);
}

Vector Vector::Add(const Vector &pV) const
{
	return Vector(x + pV.x, y + pV.y, z + pV.z);
}

Vector Vector::Subtract(const Vector &pV) const
{
	return Vector(x - pV.x, y - pV.y, z - pV.z);
}

Vector Vector::Multiply(const Vector &pV) const
{
	return Vector(x * pV.x, y * pV.y, z * pV.z);
}

Vector Vector::Divide(const Vector &pV) const
{
	return Vector(x / pV.x, y / pV.y, z / pV.z);
}

Vector Vector::Scale(const float fScale) const
{
	return Vector(x * fScale, y * fScale, z * fScale);
}

float Vector::DotProduct(const Vector &pV) const
{
	return (x * pV.x) + (y * pV.y) + (z * pV.z);
}

Vector Vector::CrossProduct(const Vector &pV) const
{
	return Vector((y * pV.z) - (pV.y * z), (z * pV.x) - (pV.z * x), (x * pV.y) - (pV.x * y));
}

Vector operator - (const Vector &pV)
{
	return pV.Flip();
}

Vector Vector::operator * (const Matrix &pMat)
{
	Vector v;

	v.x = (x * pMat._11) + (y * pMat._21) + (z * pMat._31) + pMat._41;
	v.y = (x * pMat._12) + (y * pMat._22) + (z * pMat._32) + pMat._42;
	v.z = (x * pMat._13) + (y * pMat._23) + (z * pMat._33) + pMat._43;

	return v;
}