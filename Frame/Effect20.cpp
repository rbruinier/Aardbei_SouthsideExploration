/*
	
	Southside Variations - Effect20

	Description:

	Cube built of lines

*/

#include "Main.h"

#include "Effect20.h"

#include "../System/VertexBuffer.h"

#define FX20_LINES_PER_SIDE	20
#define FX20_LINES_TOTAL (FX20_LINES_PER_SIDE * 12)

struct FX20_LINE_VERTEX
{
	float x, y, z;
	DWORD diffuse;
};

FX20_LINE_VERTEX fx20Vertices[FX20_LINES_TOTAL * 2];

#define FX20_LINE_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

Camera fx20Cam;

void Effect20::Init() 
{
	scene = new Scene();

	Vector cubes[8] =
	{
		Vector(-10,  10, -10),
		Vector( 10,  10, -10),
		Vector(-10, -10, -10),
		Vector( 10, -10, -10),
		Vector(-10,  10,  10),
		Vector( 10,  10,  10),
		Vector(-10, -10,  10),
		Vector( 10, -10,  10)
	};

	int lines[12][2] =
	{
		{0, 1},
		{0, 2},
		{0, 4},
		{1, 5},
		{1, 3},
		{2, 3},
		{2, 6},
		{3, 7},
		{4, 5},
		{4, 6},
		{5, 7},
		{6, 7}
	};

	pyramid->CreateVertexBuffer(FX20_LINES_TOTAL * 2, sizeof(FX20_LINE_VERTEX), FX20_LINE_VERTEX_FVF, 
		true, false, &lineVB);

	int index = 0;
	for (int j = 0; j < 12; j++)
	{
		for (int i = 0; i < FX20_LINES_PER_SIDE; i++)
		{
			Vector v1 = cubes[lines[j][0]];
			Vector v2 = cubes[lines[j][1]];

			v1 += Vector(((rand() % 2000) / 1000.f) - 1.0f, ((rand() % 2000) / 1000.f) - 1.0f, ((rand() % 2000) / 1000.f) - 1.0f);
			v2 += Vector(((rand() % 2000) / 1000.f) - 1.0f, ((rand() % 2000) / 1000.f) - 1.0f, ((rand() % 2000) / 1000.f) - 1.0f);

			*(Vector*)&fx20Vertices[index] = v1;
			fx20Vertices[index].diffuse = 0xffffffff;

			index++;

			*(Vector*)&fx20Vertices[index] = v2;
			fx20Vertices[index].diffuse = 0xffffffff;

			index++;
		}
	}

	lineVB->Update(fx20Vertices);
}

void Effect20::Do(float timer, int pos, int row) 
{
	DWORD color = MixColor(timer * 0.001f, 0xffffff, 0xdedede);

	if (status == 1)
	{
		color = MixColor((timer - tempTimer[1]) * 0.001f, 0xdedede, 0xffffff);
	}

	for (int i = 0; i < FX20_LINES_TOTAL * 2; i++)
	{
		fx20Vertices[i].diffuse = color;
	}

	lineVB->Update(fx20Vertices);

	pyramid->SetWorldMatrix(Matrix::RotateY(timer * 0.0005f));

	// render lines
	pyramid->BeginScene();

	pyramid->SetTexture(NULL, 0);
	
	pyramid->SetVertexStream(lineVB, 0);
	pyramid->SetTransparency(BLEND_NONE);

	pyramid->SetD3DLighting(false);

		fx20Cam.SetLocation(50, 0, -25);

	fx20Cam.Update();

	for (int i = 0; i < FX20_LINES_TOTAL; i++)
	{
		pyramid->DrawLineStrip(i * 2, 1);
	}

	pyramid->EndScene();

	pyramid->SetD3DLighting(true);

}

void Effect20::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}