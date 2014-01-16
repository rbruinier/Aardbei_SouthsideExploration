/*
	
	Pyramid System - Matrix Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Matrix_H__
#define __Matrix_H__

class Matrix
{
public:
	Matrix();
	~Matrix();

	Matrix &operator = (Matrix &vM);

	Matrix operator * (Matrix &vM);

	static Matrix Identity();

	static Matrix RotateX(float fRad);
	static Matrix RotateY(float fRad);
	static Matrix RotateZ(float fRad);

	static Matrix Translation(float fTransX, float fTransY, float fTransZ);

	static Matrix Scale(float fScaleX, float fScaleY, float fScaleZ);

	Matrix Multiply(Matrix &vM);

	Matrix Transpose();
	Matrix Inverse();

	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

#endif
