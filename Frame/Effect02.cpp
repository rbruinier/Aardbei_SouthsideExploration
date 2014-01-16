/*

	2D volume mesh generation

	grid corners and sides:

		1 -- 1 -- 2
		|         |
		|         |
		2         4
		|         |
		|         |
		4 -- 8 -- 8

*/


#include "Main.h"

#include "Effect02.h"

#include "Effect17.h";
#include "Effect21.h";

extern Effect* effect17;
extern Effect* effect21;

#define GRID_SIZE_X	128
#define GRID_SIZE_Y	128

#define GRID_WIDTH  10.f
#define GRID_HEIGHT 10.f

#define ISO_CLIP 0.7f

struct GRID_NODE
{
	float x, y;
	float nx, ny;
	float iso;

	int vertexIndex1; // point
	int vertexIndex2; // horizontal
	int vertexIndex3; // vertical

	int index;

	int created[4];
	int createdCount;
};

float randTab[128];

GRID_NODE grid2D[GRID_SIZE_X * GRID_SIZE_Y];

Object *mesh = NULL;

void Effect02::ClearGrid()
{
	int i = 0;

	for (int y = 0; y < GRID_SIZE_Y; y++)
	{
		for (int x = 0; x < GRID_SIZE_X; x++)
		{
			grid2D[i].iso =  0;
			grid2D[i].nx = 0.5f;
			grid2D[i].ny = 0.5f;

			grid2D[i].vertexIndex1 = -1;
			grid2D[i].vertexIndex2 = -1;
			grid2D[i].vertexIndex3 = -1;

			grid2D[i].index = 0;

			grid2D[i].createdCount = 0;

			i++;
		}
	}
};

void Effect02::PrepareGrid()
{
	int i = 0;

	for (int y = 0; y < GRID_SIZE_Y; y++)
	{
		for (int x = 0; x < GRID_SIZE_X; x++)
		{
			grid2D[i].x = ((x / (float) GRID_SIZE_X) * GRID_WIDTH) - (GRID_WIDTH / 2.f);
			grid2D[i].y = ((y / (float) GRID_SIZE_Y) * GRID_HEIGHT) - (GRID_HEIGHT / 2.f);

			i++;
		}
	}
}

void AddCircle(float xx, float yy, float radius)
{
	int mx = (int) xx;
	int my = (int) yy;

	int sx = xx - radius;
	int sy = yy - radius;

	int ex = xx + radius;
	int ey = yy + radius;

	for (int y = sy; y < ey; y++)
	{
		int offy = y * GRID_SIZE_X;
		for (int x = sx; x < ex; x++)
		{
			int offset = offy + x;

			float xxx = (float)x - xx;
			float yyy = (float)y - yy;

			float l = sqrt((yyy * yyy) + (xxx * xxx));

			l = 1.f - (l * ((0.20f / radius) * 6.0f));

			l = sin(l * _PI / 2.f) * 1.f;

			if (l < 0)
			{
				l = 0;
			}

			float iso = grid2D[offset].iso;

			iso += l;

			grid2D[offset].iso = iso;
		}
	}
}

inline float GetHeight(float iso)
{
	//return 0.2;

	float height = 0.8f - cos((iso - ISO_CLIP) * _PI / 1.0f) * 0.8f;

	if ((iso - ISO_CLIP) > 0.5)
	{
		height = 0.8f;
	}

	return sin((iso - ISO_CLIP) * 0.5f) * 0.8f + 0.0f;
}

OBJECT_VERTEX CreateVertex(GRID_NODE &g1)
{
	OBJECT_VERTEX v;

	v.x = g1.x;
	v.y = GetHeight(g1.iso);
	v.z = g1.y;

	v.nx = g1.nx;
	v.ny = 0;
	v.nz = g1.ny;

	return v;
}

OBJECT_VERTEX CreateVertex(GRID_NODE &g1, GRID_NODE &g2)
{
	OBJECT_VERTEX v;

	float m = (ISO_CLIP - g1.iso) / (g2.iso - g1.iso);

	v.x = g1.x + (m * (g2.x - g1.x));
	v.y = GetHeight(g1.iso + (m * (g2.iso - g1.iso)));
	v.z = g1.y + (m * (g2.y - g1.y));

	v.nx = g1.nx + (m * (g2.nx - g1.nx));
	v.ny = 0;
	v.nz = g1.ny + (m * (g2.ny - g1.ny));

	return v;
}

int edgeTable[] =
{
	0,	// 00
	1 + 2,	// 01			(1 point)
	1 + 4,	// 02			(1 point)
	2 + 4,	// 03			(2 points)
	2 + 8,	// 04			(1 point)
	1 + 8,	// 05			(2 points)
	1 + 2 + 4 + 8,	// 06				(2 points (diagonaal))
	4 + 8,	// 07			(3 points)
	4 + 8,	// 08			(1 point)
	1 + 2 + 4 + 8,	// 09				(2 points (diagonaal))
	1 + 8,	// 10			(2 points)
	2 + 8,	// 11			(3 points)
	2 + 4,	// 12			(2 points)
	1 + 4,	// 13			(3 points)
	1 + 2,	// 14			(3 points)
	0	// 15
};

int faceTable[] =
{
	-1, -1, -1,   -1, -1, -1,   -1, -1, -1,	-1,	// 00
	 0,  5,  4,   -1, -1, -1,   -1, -1, -1,	-1,		// 01		(1 point  YEP)
	 4,  6,  1,   -1, -1, -1,   -1, -1, -1,	-1,		// 02		(1 point  YEP)
	 0,  5,  1,    1,  5,  6,   -1, -1, -1,	-1,		// 03		(2 points YEP)
	 5,  2,  7,   -1, -1, -1,   -1, -1, -1,	-1,		// 04		(1 point  YEP)
	 0,  2,  4,    4,  2,  7,   -1, -1, -1,	-1,		// 05		(2 points YEP)
	 4,  6,  1,    7,  5,  2,   -1, -1, -1,	-1,		// 06		(2 points (diagonaal))
	 0,  2,  1,    1,  2,  6,    6,  2,  7,	-1,		// 07		(3 points YEP)
	 7,  3,  6,   -1, -1, -1,   -1, -1, -1,	-1,		// 08		(1 point  YEP)
	 0,  5,  4,    7,  3,  6,   -1, -1, -1,	-1,		// 09		(2 points (diagonaal))
	 4,  7,  1,    1,  7,  3,   -1, -1, -1,	-1,		// 10		(2 points YEP)
	 0,  3,  1,    0,  5,  3,    5,  7,  3,	-1,		// 11		(3 points YEP)
	 5,  2,  6,    6,  2,  3,   -1, -1, -1,	-1,		// 12		(2 points YEP)
	 0,  2,  3,    0,  3,  4,    4,  3,  6,	-1,		// 13		(3 points YEP)
	 1,  2,  3,    4,  2,  1,    2,  4,  5,	-1,		// 14		(3 points YEP)
	 0,  2,  1,    1,  2,  3,   -1, -1, -1,	-1		// 15		(4 points)
};

void Effect02::Receive(DWORD message, float timer, int pos, int row) 
{
	status = message;

	if (status < 50)
	{
		tempTimer[status] = timer;
	}

	if (status == 2)
	{
		effect17->Receive(5, timer, 0, 0);
	}

}

void GenerateMesh(float timer)
{
	int vList[8];

	int vi = 0;
	int fi = 0;

	for (int y = 0; y < GRID_SIZE_Y - 1; y++)
	{
		for (int x = 0; x < GRID_SIZE_X - 1; x++)
		{
			int h1 = y * GRID_SIZE_X + x;
			int h2 = h1 + 1;
			int h3 = h1 + GRID_SIZE_X;
			int h4 = h3 + 1;

			int index = 0;

			if (grid2D[h1].iso > ISO_CLIP) index |= 1;
			if (grid2D[h2].iso > ISO_CLIP) index |= 2;
			if (grid2D[h3].iso > ISO_CLIP) index |= 4;
			if (grid2D[h4].iso > ISO_CLIP) index |= 8;

			// opslaan
			grid2D[h1].index = index;

			// "vaste" vertices
			if (index & 1)
			{
				if (grid2D[h1].vertexIndex1 != -1)
				{
					vList[0] = grid2D[h1].vertexIndex1; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h1]);
					grid2D[h1].vertexIndex1 = vi;
					vList[0] = vi++;
				}
			}

			if (index & 2)
			{
				if (grid2D[h2].vertexIndex1 != -1)
				{
					vList[1] = grid2D[h2].vertexIndex1; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h2]);
					grid2D[h2].vertexIndex1 = vi;
					vList[1] = vi++;
				}
			}

			if (index & 4)
			{
				if (grid2D[h3].vertexIndex1 != -1)
				{
					vList[2] = grid2D[h3].vertexIndex1; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h3]);
					grid2D[h3].vertexIndex1 = vi;
					vList[2] = vi++;
				}
			}

			if (index & 8)
			{
				if (grid2D[h4].vertexIndex1 != -1)
				{
					vList[3] = grid2D[h4].vertexIndex1; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h4]);
					grid2D[h4].vertexIndex1 = vi;
					vList[3] = vi++;
				}
			}

			// geinterpoleerde vertices
			int edgeCut = edgeTable[index];

			if (edgeCut & 1)
			{
				if (grid2D[h1].vertexIndex2 != -1)
				{
					vList[4] = grid2D[h1].vertexIndex2;
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h1], grid2D[h2]);
					grid2D[h1].vertexIndex2 = vi;
					vList[4] = vi++;
				}

				grid2D[h1].created[grid2D[h1].createdCount++] = vList[4];
			}

			if (edgeCut & 2)
			{
				if (grid2D[h1].vertexIndex3 != -1)
				{
					vList[5] = grid2D[h1].vertexIndex3; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h1], grid2D[h3]);
					grid2D[h1].vertexIndex3 = vi;
					vList[5] = vi++;
				}

				grid2D[h1].created[grid2D[h1].createdCount++] = vList[5];
			}

			if (edgeCut & 4)
			{
				if (grid2D[h2].vertexIndex3 != -1)
				{
					vList[6] = grid2D[h2].vertexIndex3; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h2], grid2D[h4]);
					grid2D[h2].vertexIndex3 = vi;
					vList[6] = vi++;
				}

				grid2D[h1].created[grid2D[h1].createdCount++] = vList[6];
			}

			if (edgeCut & 8)
			{
				if (grid2D[h3].vertexIndex2 != -1)
				{
					vList[7] = grid2D[h3].vertexIndex2; 
				}
				else
				{
					mesh->vertex[vi] = CreateVertex(grid2D[h3], grid2D[h4]);
					grid2D[h3].vertexIndex2 = vi;
					vList[7] = vi++;
				}

				grid2D[h1].created[grid2D[h1].createdCount++] = vList[7];
			}

			// faces
			int *tri_lookup = (int*) faceTable + (index * 10);

			for (; *(tri_lookup) != -1;) {
				mesh->face[fi].a = vList[*(tri_lookup++)];
				mesh->face[fi].c = vList[*(tri_lookup++)];
				mesh->face[fi].b = vList[*(tri_lookup++)];
				fi++;
			}
		}
	}

	for (int i = 0; i < vi; i++)
	{
		mesh->vertex[i].u = mesh->vertex[i].x;
		mesh->vertex[i].v = mesh->vertex[i].z;
	}

	// now duplicate this object

	// vertices
	for (int i = 0; i < vi; i++)
	{
		mesh->vertex[vi + i] = mesh->vertex[i];

		mesh->vertex[vi + i].y = -mesh->vertex[vi + i].y;
	}

	// faces
	for (int i = 0; i < fi; i++)
	{
		mesh->face[fi + i].a = mesh->face[i].a + vi;
		mesh->face[fi + i].b = mesh->face[i].c + vi;
		mesh->face[fi + i].c = mesh->face[i].b + vi;
	}


	mesh->nrVertices = (vi * 2);
	mesh->nrFaces = (fi * 2);

	timer = 0;
	// do the bend thing
	for (int i = 0; i < mesh->nrVertices; i++)
	{
		//Vector xx(mesh->vertex[i].x, mesh->vertex[i].y, mesh->vertex[i].z);

		float amp = 1.f;

		float xrot = sin((mesh->vertex[i].x * 0.3f)) * amp;
		float yrot = 0;//cos((timer / 5000.f) + (xx.y * 0.3f)) * amp;
		float zrot = sin((mesh->vertex[i].z * 0.3f)) * amp;

		*(Vector*)&mesh->vertex[i] = *(Vector*)&mesh->vertex[i] * (Matrix::RotateZ(zrot) * Matrix::RotateX(zrot));
		//xx = xx * (Matrix::RotateZ(zrot) * Matrix::RotateX(zrot));

		//mesh->vertex[i].x = xx.x;
		//mesh->vertex[i].y = xx.y;
		//mesh->vertex[i].z = xx.z;
	}
}

void Effect02::Init()
{
	int i;

	scene = new Scene();

	mesh = new Object();

	mesh->SetCalculateNormals(false);

	mesh->Create(30000, 30000);

	mesh->Finish(true);

	mesh->SetCalculateNormals(true);

	mesh->nrVertices = 0;
	mesh->nrFaces    = 0;

	mesh->SetCullMode(CULL_NONE);

	mesh->SetTexture(textureLoader->GetTexture("wobbler"));

	scene->AddLight(new Light());

	scene->AddObject(mesh);

	scene->camera->SetFarPlane(20.f);
	scene->camera->SetNearPlane(1.f);
	Object* plane = Primitives::Plane(1, 1, 20, 20);

	//plane->SetTexture(texture["tex01"]);

	//scene->AddObject(plane);

	plane->ScaleUV(10, 10);

	plane->SetEmissive(0.5f, 0.5f, 0.5f);

	for (i = 0; i < 128; i++)
	{
		randTab[i] = (rand() % 20000) / 20000.f;
	}

	PrepareGrid();
	ClearGrid();

}

void Effect02::Do(float timer, int pos, int row)
{
	int i;

	//status = 1;
	
	if (status >= 1)
	{
		ClearGrid();

		for (i = 0; i < 20; i++)
		{
			int   r1 = randTab[(i + 41) % 128] * 65536.f;
			float r2 = randTab[i % 128] * 2000.f + 3500.f;
			float r3 = randTab[(i + 55) % 128] * 2000.f + 2500.f;

			AddCircle(sin((timer + r1) / r2) * 30.f + 64.f, cos((timer + r1) / r3) * 30.f + 64.f, 16.f);
		}

		GenerateMesh(timer);

		background = 0xffffff;

		//scene->camera->SetLocation(sin(timer / 2600.f) * 6.f, cos(timer / 2600.f) * 2.f - 2.f, cos(timer / 2600.f) * 6.f);
		scene->camera->SetLocation(0, cos(timer / 2600.f) * 2.f - 2.f, -6.f);

		scene->object[0]->SetRotation(0, -timer * 0.03f, 0);

		pyramid->SetAmbientLight(0x303030);


		float dif = (timer - tempTimer[1]) * 0.0005f;

		float xx = 0;

		if (dif < (_PI * 0.5f))
		{
			float scale = 20.f;

			xx = -scale + sin(dif) * scale;
		}

		if (status >= 3)
		{
			dif = timer - tempTimer[3];

			xx += (dif * dif) * 0.000005f;
		}

		scene->object[0]->SetLocation(xx, 1, 0);

		scene->light[0]->SetDiffuse(1, 1, 1);
		scene->light[0]->SetAttenuation(0.7f, 0, 0);
		scene->light[0]->SetLocation(sin(timer / 2600.f) * 0.f, cos(timer / 2600.f) * 0.f, cos(timer / 2600.f) * 0.f);
	}

	pyramid->SetRenderTarget(renderChain->GetOriginal());
	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	effect17->Do(timer);

	if (status >= 1)
	{
		scene->Render();
	}

	pyramid->ResetRenderTarget();

	postProcessor->psBrightPass->SetLuminance(0.04f);
	postProcessor->psBloom->SetBloomScale(1.5f);

	postProcessor->chainGlow01->Render();

	pyramid->SetTexture(renderChain->GetSource(), 0);
	drawer2D->BeginScene(BLEND_ADD);
	drawer2D->DrawFullscreen();
	drawer2D->EndScene();

	effect21->Do(timer - 3900);

	// info
	//fontSystem->Write(1, 32, "NFO:%05i:%05i", mesh->nrVertices, mesh->nrFaces);
}

void Effect02::Destroy()
{
	scene->Destroy();

	delete scene;
}