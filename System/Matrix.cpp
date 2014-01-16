/*
	
	Pyramid System - Matrix Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Matrix.h"

#include <memory.h>
#include <math.h>

Matrix::Matrix()
{
	_11 = _22 = _33 = _44 = 1.0f;
	_12 = _13 = _14 = _21 = 0.0f;
	_23 = _24 = _31 = _32 = 0.0f;
	_34 = _41 = _42 = _43 = 0.0f;
}

Matrix::~Matrix()
{
}

Matrix &Matrix::operator = (Matrix &vM)
{
	memcpy(this, &vM, sizeof(Matrix));

	return *this;
}

Matrix Matrix::operator * (Matrix &vM)
{
	return Multiply(vM);
}

Matrix Matrix::Identity()
{
	return Matrix();
}

Matrix Matrix::RotateX(float fRad)
{
	Matrix mat;
	
    mat._22 =  (float) cos(fRad);
    mat._23 =  (float) sin(fRad);
    mat._32 = -(float) sin(fRad);
    mat._33 =  (float) cos(fRad);

	return mat;
}

Matrix Matrix::RotateY(float fRad)
{
	Matrix mat;
	
    mat._11 =  (float) cos(fRad);
    mat._13 = -(float) sin(fRad);
    mat._31 =  (float) sin(fRad);
    mat._33 =  (float) cos(fRad);

	return mat;
}

Matrix Matrix::RotateZ(float fRad)
{
	Matrix mat;
	
    mat._11  =  (float) cos(fRad);
    mat._12  =  (float) sin(fRad);
    mat._21  = -(float) sin(fRad);
    mat._22  =  (float) cos(fRad);

	return mat;
}

Matrix Matrix::Translation(float fTransX, float fTransY, float fTransZ)
{
	Matrix mat;

	mat._41 = fTransX;
	mat._42 = fTransY;
	mat._43 = fTransZ;

	return mat;
}

Matrix Matrix::Scale(float fScaleX, float fScaleY, float fScaleZ)
{
	Matrix mat;

	mat._11 = fScaleX;
	mat._22 = fScaleY;
	mat._33 = fScaleZ;

	return mat;
}

Matrix Matrix::Multiply(Matrix &vM)
{
	Matrix mat;

    for (int j = 0; j < 4; j++)
	{
        for (int i = 0; i < 4; i++)
		{
			mat.m[i][j] = m[i][0] * vM.m[0][j] + 
				          m[i][1] * vM.m[1][j] +
				          m[i][2] * vM.m[2][j] + 
						  m[i][3] * vM.m[3][j];
		}
	}

	return mat;
}

Matrix Matrix::Transpose()
{
	Matrix mat;

	mat._11 = _11;
	mat._21 = _12;
	mat._31 = _13;
	mat._41 = _14;

	mat._12 = _21;
	mat._22 = _22;
	mat._32 = _23;
	mat._42 = _24;

	mat._13 = _31;
	mat._23 = _32;
	mat._33 = _33;
	mat._43 = _34;

	mat._14 = _41;
	mat._24 = _42;
	mat._34 = _43;
	mat._44 = _44;

	return mat;
}

Matrix Matrix::Inverse()
{
	Matrix mat;

    float fDetInv = 1.0f / (_11 * (_22 * _33 - _23 * _32) -
                            _12 * (_21 * _33 - _23 * _31) +
                            _13 * (_21 * _32 - _22 * _31));

    mat._11 =  fDetInv * (_22 * _33 - _23 * _32);
    mat._12 = -fDetInv * (_12 * _33 - _13 * _32);
    mat._13 =  fDetInv * (_12 * _23 - _13 * _22);
    mat._14 = 0.0f;

    mat._21 = -fDetInv * (_21 * _33 - _23 * _31);
    mat._22 =  fDetInv * (_11 * _33 - _13 * _31);
    mat._23 = -fDetInv * (_11 * _23 - _13 * _21);
    mat._24 = 0.0f;

    mat._31 =  fDetInv * (_21 * _32 - _22 * _31);
    mat._32 = -fDetInv * (_11 * _32 - _12 * _31);
    mat._33 =  fDetInv * (_11 * _22 - _12 * _21);
    mat._34 = 0.0f;

    mat._41 = -(_41 * mat._11 + _42 * mat._21 + _43 * mat._31);
    mat._42 = -(_41 * mat._12 + _42 * mat._22 + _43 * mat._32);
    mat._43 = -(_41 * mat._13 + _42 * mat._23 + _43 * mat._33);
    mat._44 = 1.0f;

	return mat;
}


