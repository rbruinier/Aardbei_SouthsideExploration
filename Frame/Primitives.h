/*
	
	Pyramid Tools - Primitives Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Primitives_H__
#define __Primitives_H__

class Object;

class Primitives
{
public:
	static Object* Plane(int iSegments, float fWidth);
	static Object* Plane(int iSegmentsX, int iSegmentsZ, float fWidth, float fDepth);

	static Object* Cube(int iSegments, float fRadius);

	static Object* Sphere(int iSegments, float fRadius);

	static Object* Tube(int iSegmentsX, int iSegmentsZ, float fRadius, float fLength);

	//static Object* Toroid(int iSegments, int iRings, float r0, float r1);
	//static Object* Toroid(int iSegments, int iRings, float r0, float r1, float n1, float n2);
};

#endif