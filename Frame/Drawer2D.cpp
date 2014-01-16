/*
	
	Pyramid Tools - 2D Drawer Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Drawer2D.h"

#include "../System/Pyramid.h"
#include "../System/VertexBuffer.h"

extern Pyramid *pyramid;

void Drawer2DBatch::Draw(int polyNr, float x1, float y1, DWORD c1, float x2, float y2, DWORD c2,
	float x3, float y3, DWORD c3, float x4, float y4, DWORD c4)
{
	int vertexNr = polyNr * 4;

	vertex[vertexNr++].Set(x1 - 0.5f, y1 - 0.5, 0.5f, 0.5f, c1, 0, 0, 0, 0);
	vertex[vertexNr++].Set(x2 - 0.5f, y2 - 0.5, 0.5f, 0.5f, c2, 1, 0, 1, 0);
	vertex[vertexNr++].Set(x3 - 0.5f, y3 - 0.5, 0.5f, 0.5f, c3, 0, 1, 0, 1);
	vertex[vertexNr++].Set(x4 - 0.5f, y4 - 0.5, 0.5f, 0.5f, c4, 1, 1, 1, 1);
}

Drawer2D::Drawer2D()
{
	vertexBuffer = NULL;

	pyramid->CreateVertexBuffer(4, sizeof(Drawer2DVertex), Drawer2DVertexFVF, 
		true, false, &vertexBuffer);
}

Drawer2D::~Drawer2D()
{
}

Drawer2DBatch* Drawer2D::CreateBatch(int count, bool dynamic)
{
	Drawer2DBatch* batch = new Drawer2DBatch();

	batch->nrPolys = count;
	batch->vertex = new Drawer2DVertex[count * 4];
	batch->dynamic = dynamic;
	batch->updated = false;

	pyramid->CreateVertexBuffer(count * 4, sizeof(Drawer2DVertex), Drawer2DVertexFVF, 
		dynamic, false, &batch->vb);

	return batch;
}

void Drawer2D::DrawBatch(Drawer2DBatch* batch)
{
	if (batch->dynamic || !batch->updated)
	{
		batch->vb->Update(batch->vertex);
		batch->updated = true;
	}

	pyramid->SetVertexStream(batch->vb);

	for (int i = 0; i < batch->nrPolys; i++)
	{
		pyramid->DrawPrimitiveStrip(i * 4, 2);
	}
}

void Drawer2D::DrawFullscreen()
{
	DrawFullscreen(0, 0, 0xffffffff,
		           1, 0, 0xffffffff,
		           0, 1, 0xffffffff,
		           1, 1, 0xffffffff);
}

void Drawer2D::DrawFullscreen(DWORD c1, DWORD c2, DWORD c3, DWORD c4)
{
	DrawFullscreen(0, 0, c1,
				   1, 0, c2,
				   0, 1, c3,
				   1, 1, c4);	
}

void Drawer2D::DrawFullscreen(float u1, float v1, float u2, float v2, 
	float u3, float v3, float u4, float v4)
{
	DrawFullscreen(u1, v1, 0xffffffff,
				   u2, v2, 0xffffffff,
				   u3, v3, 0xffffffff,
				   u4, v4, 0xffffffff);
}

void Drawer2D::DrawFullscreen(float u1, float v1, DWORD c1, float u2, float v2, DWORD c2, 
	float u3, float v3, DWORD c3, float u4, float v4, DWORD c4)
{
	RECT r;

	pyramid->GetViewport(r);

	float x1 = (float)r.left;
	float x2 = (float)r.right;

	float y1 = (float)r.top;
	float y2 = (float)r.bottom;

	Draw(x1, y1, u1, v1, c1,
		 x2, y1, u2, v2, c2,
		 x1, y2, u3, v3, c3,
		 x2, y2, u4, v4, c4);
}

void Drawer2D::Draw(float x1, float y1, 
					float x2, float y2, 
					float x3, float y3, 
					float x4, float y4)
{
	Draw(x1, y1, 0xffffffff,
		 x2, y2, 0xffffffff,
		 x3, y3, 0xffffffff,
		 x4, y4, 0xffffffff);
}

void Drawer2D::Draw(float x1, float y1, DWORD c1,
					float x2, float y2, DWORD c2, 
					float x3, float y3, DWORD c3, 
					float x4, float y4, DWORD c4)
{
	Draw(x1, y1, 0, 0, c1,
		 x2, y2, 1, 0, c2,
		 x3, y3, 0, 1, c3,
		 x4, y4, 1, 1, c4);
}

void Drawer2D::Draw(float x1, float y1, float u1, float v1,
					float x2, float y2, float u2, float v2,
					float x3, float y3, float u3, float v3,
					float x4, float y4, float u4, float v4)
{
	Draw(x1, y1, u1, v1, 0xffffffff,
		 x2, y2, u2, v2, 0xffffffff,
		 x3, y3, u3, v3, 0xffffffff,
		 x4, y4, u4, v4, 0xffffffff);
}

void Drawer2D::Draw(float x1, float y1, float u1, float v1, DWORD c1,
	  		        float x2, float y2, float u2, float v2, DWORD c2,
					float x3, float y3, float u3, float v3, DWORD c3,
				    float x4, float y4, float u4, float v4, DWORD c4)
{
	Drawer2DVertex vertices[4];
	
	vertices[0].Set(x1 - 0.5f, y1 - 0.5f, 0.5f, 0.5f, c1, u1, v1, 0, 0);
	vertices[1].Set(x2 - 0.5f, y2 - 0.5f, 0.5f, 0.5f, c2, u2, v2, 1, 0);
	vertices[2].Set(x3 - 0.5f, y3 - 0.5f, 0.5f, 0.5f, c3, u3, v3, 0, 1);
	vertices[3].Set(x4 - 0.5f, y4 - 0.5f, 0.5f, 0.5f, c4, u4, v4, 1, 1);

	vertexBuffer->Update(vertices);

	pyramid->SetVertexStream(vertexBuffer);

	pyramid->DrawPrimitiveStrip(0, 2);
}

void Drawer2D::Start(BLEND_MODE blendMode)
{
	pyramid->SetTransparency(blendMode);

	pyramid->Set2DEnable(true);
}

void Drawer2D::Stop()
{
	pyramid->Set2DEnable(false);
}

void Drawer2D::BeginScene(BLEND_MODE blendMode)
{
	pyramid->SetTransparency(blendMode);

	pyramid->Set2DEnable(true);

	pyramid->BeginScene();
}

void Drawer2D::EndScene()
{
	pyramid->EndScene();

	pyramid->Set2DEnable(false);
}


