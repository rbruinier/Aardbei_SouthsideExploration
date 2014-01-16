/*
	
	Southside Variations - Effect17

	Description:

	Background:

	part 1: bars behind the wobbler

*/

#include "Main.h"

#include "Effect17.h"

int fx17Colors[6] =
{
	0x34255B,
	0x2B243D,
	0x221F2B,
	0x9fcb30,
	0xcbb330,
	0xcb4930
};

struct fx17Line
{
	float startPos;
	float width;
	int colorIndex;
	int orientation;
};

fx17Line fx17Lines[1024];

Drawer2DBatch* fx17Batch;

int nrFx17Lines = 0;

DWORD fx17FinalColors[1024];


void Effect17::Init() 
{
	int startPos = 0;

	srand(10);

	while (startPos < 800)
	{
		startPos += (rand() % 10) + 5;

		fx17Lines[nrFx17Lines].startPos = startPos;
		fx17Lines[nrFx17Lines].width = (rand() % 2) + 2;
		fx17Lines[nrFx17Lines].colorIndex = rand() % 3;
		fx17Lines[nrFx17Lines].orientation = 0;

		startPos += fx17Lines[nrFx17Lines].width;

		nrFx17Lines++;
	}

	startPos = 0;

	while (startPos < 600)
	{
		startPos += (rand() % 10) + 5;

		fx17Lines[nrFx17Lines].startPos = startPos;
		fx17Lines[nrFx17Lines].width = (rand() % 2) + 2;
		fx17Lines[nrFx17Lines].colorIndex = rand() % 3;
		fx17Lines[nrFx17Lines].orientation = 1;

		startPos += fx17Lines[nrFx17Lines].width;

		nrFx17Lines++;
	}

	fx17Batch = drawer2D->CreateBatch(nrFx17Lines, true);

	int index = 0;
	for (int j = 0; j < 3; j++)
	{
		int color = fx17Colors[j];

		for (int i = 0; i < nrFx17Lines; i++)
		{
			if (fx17Lines[i].colorIndex != j) continue;

			float x1 = fx17Lines[i].startPos;
			float x2 = x1 + fx17Lines[i].width;

			float y1 = 0;
			float y2 = 600;

			if (fx17Lines[i].orientation == 1)
			{
				y1 = fx17Lines[i].startPos;
				y2 = x1 + fx17Lines[i].width;
				
				x1 = 0;
				x2 = 800;
			}

			fx17FinalColors[index] = fx17Colors[fx17Lines[i].colorIndex];

			fx17Batch->Draw(index++, 
				            x1, y1, color,
			  			    x2, y1, color, 
						    x1, y2, color,
						    x2, y2, color);
		}
	}

}

void Effect17::Do(float timer, int pos, int row) 
{
	if (status == 5)
	{
		int index = 0;
		for (int i = 0; i < nrFx17Lines; i++)
		{
			DWORD color = MixColor((timer - tempTimer[5]) * 0.0005f, fx17FinalColors[i], 0xffffff);

			fx17Batch->vertex[index++].diffuse = color;
			fx17Batch->vertex[index++].diffuse = color;
			fx17Batch->vertex[index++].diffuse = color;
			fx17Batch->vertex[index++].diffuse = color;
		}
	}

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	drawer2D->DrawBatch(fx17Batch);

	drawer2D->EndScene();
}