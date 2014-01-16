/*
	
	Pyramid Tools - 2D Drawer Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __2DDrawer_H__
#define __2DDrawer_H__

class VertexBuffer;

#include <windows.h>

#include "../System/Pyramid.h"

#define Drawer2DVertexFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2)

struct Drawer2DVertex 
{
public:
    float	x, y, z;
	float	rhw;
	DWORD	diffuse;   
    float   u, v;
	float   l, m;

	Drawer2DVertex()
	{
	}

	Drawer2DVertex(float x, float y, float z, float rhw, DWORD diffuse, float u, float v, float l, float m)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->rhw = rhw;
		this->diffuse = diffuse;
		this->u = u;
		this->v = v;
		this->l = l;
		this->m = m;
	}

	void Set(float x, float y, float z, float rhw, DWORD diffuse, float u, float v, float l, float m)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->rhw = rhw;
		this->diffuse = diffuse;
		this->u = u;
		this->v = v;
		this->l = l;
		this->m = m;
	}
};

class Drawer2DBatch
{
public:
	Drawer2DVertex* vertex;
	VertexBuffer* vb;
	int nrPolys;
	bool dynamic;
	bool updated;

	void Draw(int polyNr, float x1, float y1, DWORD color1, float x2, float y2, DWORD color2,
		float x3, float y3, DWORD color3, float x4, float y4, DWORD color4);
};

class Drawer2D
{
public:
	Drawer2D();
	~Drawer2D();

	Drawer2DBatch* CreateBatch(int count, bool dynamic);
	void DrawBatch(Drawer2DBatch* batch);

	void DrawFullscreen();
	void DrawFullscreen(DWORD c1, DWORD c2, DWORD c3, DWORD c4);
	void DrawFullscreen(float u1, float v1, float u2, float v2, 
						float u3, float v3, float u4, float v4);
	void DrawFullscreen(float u1, float v1, DWORD c1, float u2, float v2, DWORD c2, 
						float u3, float v3, DWORD c3, float u4, float v4, DWORD c4);

	void Draw(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	void Draw(float x1, float y1, DWORD c1, float x2, float y2, DWORD c2, 
			  float x3, float y3, DWORD c3, float x4, float y4, DWORD c4);

	void Draw(float x1, float y1, float u1, float v1, float x2, float y2, float u2, float v2,
	          float x3, float y3, float u3, float v3, float x4, float y4, float u4, float v4);

	void Draw(float x1, float y1, float u1, float v1, DWORD c1,
		      float x2, float y2, float u2, float v2, DWORD c2,
	          float x3, float y3, float u3, float v3, DWORD c3,
			  float x4, float y4, float u4, float v4, DWORD c4);

	void Start(BLEND_MODE blendMode);
	void Stop();

	void BeginScene(BLEND_MODE blendMode);
	void EndScene();

private:
	VertexBuffer *vertexBuffer;
};

#endif