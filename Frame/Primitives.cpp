/*
	
	Pyramid Tools - Primitives Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Primitives.h"

#include "../Engine/Object.h"

#include <math.h>

Object* Primitives::Plane(int iSegments, float fRadius)
{
	return Plane(iSegments, iSegments, fRadius, fRadius);
}

Object* Primitives::Plane(int iSegmentsX, int iSegmentsZ, float fRadiusX, float fRadiusZ)
{
	int iSegmentsX2 = iSegmentsX + 1;
	int iSegmentsZ2 = iSegmentsZ + 1;

	Object* object = new Object();

	object->Create(iSegmentsX2 * iSegmentsZ2, iSegmentsX * iSegmentsZ * 2);

	int i, x, z;

	i = 0;
	for (z = 0; z < iSegmentsZ2; z++)
	{
		for (x = 0; x < iSegmentsX2; x++)
		{
			float xx, yy, zz, u, v;

			yy = 0;

			xx = -fRadiusX + (x * (fRadiusX / iSegmentsX) * 2.f);
			zz =  fRadiusZ - (z * (fRadiusZ / iSegmentsZ) * 2.f);

			u = (float)x / iSegmentsX;
			v = (float)z / iSegmentsZ;

			object->vertex[i].x = xx;
			object->vertex[i].y = yy;
			object->vertex[i].z = zz;

			object->vertex[i].u = u;
			object->vertex[i].v = v;

			i++;
		}
	}

	i = 0;
	for (z = 0; z < iSegmentsZ; z++)
	{
		for (x = 0; x < iSegmentsX; x++)
		{
			int a, b, c, d;

			a = (z * iSegmentsX2) + x;
			b = a + 1;
			c = a + iSegmentsX2;
			d = c + 1;

			object->face[i].a = a;
			object->face[i].b = c;
			object->face[i].c = b;

			i++;

			object->face[i].a = b;
			object->face[i].b = c;
			object->face[i].c = d;

			i++;
		}
	}

	for (i = 0; i < object->nrVertices; i++)
	{
		object->vertex[i].l = object->vertex[i].u;
		object->vertex[i].m = object->vertex[i].v;
	}

	return object;
}

Object* Primitives::Cube(int iSegments, float fRadius)
{
	int iSegments2 = iSegments + 1;

	int sideSizeV = iSegments2 * iSegments2;
	int sideSizeF = iSegments * iSegments * 2;

	Object* object = new Object();

	object->Create(sideSizeV * 6, sideSizeF * 6);

	int i, x, y, k;

	i = 0;
    for (y = 0; y < iSegments2; y++) 
	{
        for (x = 0; x < iSegments2; x++) 
		{
			float xx, yy, zz, u, v;

            xx = -fRadius + (x * (fRadius / (float)iSegments) * 2.f);
            yy =  fRadius - (y * (fRadius / (float)iSegments) * 2.f);
            zz = -fRadius;

			u = x / (float)iSegments;
			v = y / (float)iSegments;

            object->vertex[i].x = xx;
            object->vertex[i].y = yy;
            object->vertex[i].z = zz;
			object->vertex[i].u = u;
			object->vertex[i].v = v;

            object->vertex[i + sideSizeV].x =  xx;
            object->vertex[i + sideSizeV].y =  yy;
            object->vertex[i + sideSizeV].z = -zz;
			object->vertex[i + sideSizeV].u = u;
			object->vertex[i + sideSizeV].v = v;

            object->vertex[i + (sideSizeV * 2)].x = -zz;
            object->vertex[i + (sideSizeV * 2)].y =  yy;
            object->vertex[i + (sideSizeV * 2)].z =  xx;
            object->vertex[i + (sideSizeV * 2)].u = u;
            object->vertex[i + (sideSizeV * 2)].v = v;

            object->vertex[i + (sideSizeV * 3)].x =  zz;
            object->vertex[i + (sideSizeV * 3)].y =  yy;
            object->vertex[i + (sideSizeV * 3)].z =  xx;
            object->vertex[i + (sideSizeV * 3)].u = u;
            object->vertex[i + (sideSizeV * 3)].v = v;

            object->vertex[i + (sideSizeV * 4)].x = yy;
            object->vertex[i + (sideSizeV * 4)].y = zz;
            object->vertex[i + (sideSizeV * 4)].z = xx;
            object->vertex[i + (sideSizeV * 4)].u = u;
            object->vertex[i + (sideSizeV * 4)].v = v;

            object->vertex[i + (sideSizeV * 5)].x =  yy;
            object->vertex[i + (sideSizeV * 5)].y = -zz;
            object->vertex[i + (sideSizeV * 5)].z =  xx;
            object->vertex[i + (sideSizeV * 5)].u = u;
            object->vertex[i + (sideSizeV * 5)].v = v;

            i++;
        }
    }

	i = 0;
	for (k = 0; k < 3; k++) 
	{
		i = sideSizeF * k * 2;
		for (y = 0; y < iSegments; y++) 
		{
			for (x = 0; x < iSegments; x++) 
			{
				int a, b, c, d;

	            a = (y * iSegments2) + x + (sideSizeV * 2 * k);
				b = a + 1;
				c = a + iSegments2;
				d = c + 1;

				object->face[i].a = a;
				object->face[i].b = d;
				object->face[i].c = b;

				object->face[i + sideSizeF].a = a + sideSizeV;
				object->face[i + sideSizeF].b = b + sideSizeV;
				object->face[i + sideSizeF].c = d + sideSizeV;

			    i++;

				object->face[i].a = a;
				object->face[i].b = c;
				object->face[i].c = d;

				object->face[i + sideSizeF].a = a + sideSizeV;
				object->face[i + sideSizeF].b = d + sideSizeV;
				object->face[i + sideSizeF].c = c + sideSizeV;

			    i++;
	        }
		}
	}

	for (i = 0; i < object->nrVertices; i++)
	{
		object->vertex[i].l = object->vertex[i].u;
		object->vertex[i].m = object->vertex[i].v;
	}

	return object;
}

Object* Primitives::Sphere(int iSegments, float fRadius)
{
	Object* object = Cube(iSegments, fRadius);

	for (int i = 0; i < object->nrVertices; i++)
	{
		float x = object->vertex[i].x;
		float y = object->vertex[i].y;
		float z = object->vertex[i].z;

		float l = sqrt((x * x) + (y * y) + (z * z));

		x = (x / l) * fRadius;
		y = (y / l) * fRadius;
		z = (z / l) * fRadius;

		object->vertex[i].x = x;
		object->vertex[i].y = y;
		object->vertex[i].z = z;
	}

	return object;
}

Object* Primitives::Tube(int iSegmentsX, int iSegmentsZ, float fRadius, float fLength)
{
	int iSegmentsX2 = iSegmentsX + 1;
	int iSegmentsZ2 = iSegmentsZ + 1;

	Object* object = new Object();

	object->Create(iSegmentsX2 * iSegmentsZ2, iSegmentsX * iSegmentsZ * 2);

	int i, x, z;

	i = 0;
    for (z = 0; z < iSegmentsZ2; z++) 
	{
        for (x = 0; x < iSegmentsX2; x++) 
		{
			float xx, yy, zz, u, v;

            xx = sin((x / (float)iSegmentsX) * _2PI) * fRadius;
            yy = cos((x / (float)iSegmentsX) * _2PI) * fRadius;
            zz = (fLength / 2.f) - ((fLength / iSegmentsZ) * z);

			u = x / (float)iSegmentsX;
			v = z / (float)iSegmentsZ;

            object->vertex[i].x = xx;
            object->vertex[i].y = yy;
            object->vertex[i].z = zz;

			object->vertex[i].u = u;
			object->vertex[i].v = v;

			i++;
		}
	}

	i = 0;
	for (z = 0; z < iSegmentsZ; z++)
	{
		for (x = 0; x < iSegmentsX; x++)
		{
			int a, b, c, d;

			a = (z * iSegmentsX2) + x;
			b = a + 1;
			c = a + iSegmentsX2;
			d = c + 1;

			object->face[i].a = a;
			object->face[i].b = c;
			object->face[i].c = b;

			i++;

			object->face[i].a = b;
			object->face[i].b = c;
			object->face[i].c = d;

			i++;
		}
	}

	for (i = 0; i < object->nrVertices; i++)
	{
		object->vertex[i].l = object->vertex[i].u;
		object->vertex[i].m = object->vertex[i].v;
	}

	return object;
}
//
//Object* Primitives::Toroid(int iSegments, int iRings, float r0, float r1)
//{
//	return Toroid(iSegments, iRings, r0, r1, 1, 1);
//}
//
//Object* Primitives::Toroid(int iSegments, int iRings, float r0, float r1, float n1, float n2) 
//{
//	int iSegments2 = iSegments + 1;
//	int iRings2 = iRings + 1;
//
//	Object* object = new Object();
//
//	object->Create(iSegments2 * iRings2, iSegments * iRings * 2);
//
//	int x, y;
//
//	float pi2 = 2 * 3.14159f;
//	float m1  = _2PI / iSegments;
//	float m2  = _2PI / iRings;
//	float tm1 = 1.0f / iSegments;
//	float tm2 = 1.0f / iRings;
//
//	for (x = 0; x < iSegments2; x++) 
//	{
//		for (y = 0; y < iRings2; y++) 
//		{
//			float th1 = x * m1;
//			float th2 = y * m2;
//			int num = (x * iRings2) + y;
//
//			float th1cos = (float) cos(th1);
//			float th1sin = (float) sin(th1);
//			float th2cos = (float) cos(th2);
//			float th2sin = (float) sin(th2);
//
//			float xflip = 1;
//			float yflip = 1;
//			float zflip = 1;
//			float aflip = 1;
//
//			if (th1cos<=0.f) { th1cos = -th1cos; xflip = -xflip; }
//			if (th1sin<=0.f) { th1sin = -th1sin; yflip = -yflip; }
//			if (th2cos<=0.f) { th2cos = -th2cos; aflip = -aflip; }
//			if (th2sin<=0.f) { th2sin = -th2sin; zflip = -zflip; }
//
//			float a = (float) pow(th2cos,n2); a = a * aflip;
//			float xx = (float) pow(th1cos,n1) * (r0 + (r1 * a));
//			float yy = (float) pow(th1sin,n1) * (r0 + (r1 * a));
//			float zz = r1 * (float) pow(th2sin,n2);
//
//			xx = xx * xflip;
//			yy = yy * yflip;
//			zz = zz * zflip;
//
//			float u = x * tm1;
//			float v = y * tm2;
//
//			if (y == iRings) 
//			{
//				object->vertex[num].x = object->vertex[num - (iRings)].x;
//				object->vertex[num].y = object->vertex[num - (iRings)].y;
//				object->vertex[num].z = object->vertex[num - (iRings)].z;
//			} 
//			else 
//			{
//				object->vertex[num].x = xx;
//				object->vertex[num].y = yy;
//				object->vertex[num].z = zz;
//			}
//
//			object->vertex[num].u = u;
//			object->vertex[num].v = v;
//		}
//	}
//	
//	for (x = 0; x < iSegments; x++) {
//		for (y = 0; y < iRings; y++) {
//			int num = (x * iRings + y) * 2;
//
//			object->face[num].a = ((x + 1)) * iRings2 + ((y + 1));
//			object->face[num].b = x * iRings2 + y;
//			object->face[num].c = x * iRings2 + ((y + 1));
//
//			num++;
//
//			object->face[num].a = ((x + 1)) * iRings2 + y;
//			object->face[num].b = x * iRings2 + y;
//			object->face[num].c = ((x + 1)) * iRings2 + ((y + 1));
//		}
//	}
//
//	for (int i = 0; i < object->nrVertices; i++)
//	{
//		object->vertex[i].l = object->vertex[i].u;
//		object->vertex[i].m = object->vertex[i].v;
//	}
//
//	return object;
//}