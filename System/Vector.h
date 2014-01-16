/*
	
	Pyramid System - Vector Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Vector_H__
#define __Vector_H__

class Matrix;

class Vector
{
public:
	Vector();
	Vector(float fX, float fY, float fZ);
	~Vector();

	Vector &operator = (const Vector &pV);

	Vector operator - (const Vector &pV) const;
	Vector operator + (const Vector &pV) const;
	Vector operator * (const Vector &pV) const;
	Vector operator * (const float fScale) const;
	Vector operator / (const Vector &pV) const;
	Vector operator / (const float fScale) const;

	Vector &operator -= (const Vector &pV);
	Vector &operator += (const Vector &pV);
	Vector &operator *= (const Vector &pV);
	Vector &operator *= (const float fScale);
	Vector &operator /= (const Vector &pV);

	float  Magnitude() const;
	Vector Flip() const;
	Vector Normalize() const;
	Vector Add(const Vector &pV) const;
	Vector Subtract(const Vector &pV) const;
	Vector Multiply(const Vector &pV) const;
	Vector Divide(const Vector &pV) const;
	Vector Scale(const float fScale) const;
	float  DotProduct(const Vector &pV) const;
	Vector CrossProduct(const Vector &pV) const;

//	friend Vector operator - (Vector &pV);

	Vector Vector::operator * (const Matrix &pMat);

	//friend Vector operator * (Vector &pV, Matrix &pM);

	float x;
	float y;
	float z;
};

#endif
