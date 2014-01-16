/*
	
	Southside Variations - Effect03

	Description:

	"Marching" cubes, letterlijk. Een 2D grid houdt de positie bij van de kubussen. Ze kunnen klimmen
	en vallen, maar ze lopen rond door het veld, steeds een paar, random geselecteerd.

*/

#include "Main.h"

#include <stack>
using namespace std;

#include "Effect03.h"

#define CUBE_ROTATION_TIME 1000.f

#define CUBEGRID_SIZE_X 60
#define CUBEGRID_SIZE_Z 60

#define CUBEGRID_CUBE_COUNT 1000

#define MOVING_CUBES_COUNT 50

struct CubeGridItem
{
public:
	float x;
	float z;

	bool active;

	stack <Object*> cubeStack;

	CubeGridItem()
	{
		active = false;
		cubeStack.empty();
	}
};

struct MovingCube
{
public:
	CubeGridItem* startGrid;
	CubeGridItem* stopGrid;

	Object* obj;

	float startTimer;

	int direction;

	int status;

	Vector rotStart;

	Vector locStart;

	MovingCube()
	{
		Set(NULL, NULL, NULL, -1, 0);
	}

	Set(CubeGridItem* start, CubeGridItem* stop, Object* cube, int dir, float timer)
	{
		startGrid = start;
		stopGrid = stop;
		obj = cube;
		direction = dir;
		startTimer = timer;

		status = 0;

		if (cube != NULL)
		{
			locStart = cube->location;
		}

		if ((startGrid != NULL) && (stopGrid != NULL))
		{
			startGrid->active = true;
			stopGrid->active = true;
		}

	}

	bool Update(float timer)
	{
		if (status == 2)
		{
			return false;
		}

		float timeDif = timer - startTimer;

		if (timeDif < 0) return false;

		float x = obj->location.x;
		float y = obj->location.y;
		float z = obj->location.z;

		float baseY = ((startGrid->cubeStack.size() - 1) * 2.f) + 1.f;

		if (direction == 5)
		{
			obj->location.y = locStart.y + (timeDif * timeDif * 0.00002f);

			return false;
		}

		if (status == 0)
		{
			x = startGrid->x;
			z = startGrid->z;

			float difX = stopGrid->x - startGrid->x;
			float difZ = stopGrid->z - startGrid->z;

			x = startGrid->x + ((difX / CUBE_ROTATION_TIME) * timeDif);
			z = startGrid->z + ((difZ / CUBE_ROTATION_TIME) * timeDif);

			switch (direction)
			{
			case 0:
				obj->SetRotation(timeDif * (-90.f / CUBE_ROTATION_TIME), 0, 0);
				break;
			case 1:
				obj->SetRotation(timeDif * ( 90.f / CUBE_ROTATION_TIME), 0, 0);
				break;
			case 2:
				obj->SetRotation(0, 0, timeDif * ( 90.f / CUBE_ROTATION_TIME));
				break;
			case 3:
				obj->SetRotation(0, 0, timeDif * (-90.f / CUBE_ROTATION_TIME));
				break;
			}

			obj->SetLocation(x, sin(timeDif * (_PI / CUBE_ROTATION_TIME)) * 0.40f + baseY, z);

			if (timeDif >= CUBE_ROTATION_TIME)
			{
				if (((startGrid->cubeStack.size() - 1) == (stopGrid->cubeStack.size())))
				{
					obj->SetLocation(stopGrid->x, baseY, stopGrid->z);

					obj->SetRotation(0, 0, 0);

					status = 2;

					return true;
				}

				status = 1;
			}
		}

		if (status == 1)
		{
			timeDif -= CUBE_ROTATION_TIME;

			y = baseY - (timeDif * timeDif * 0.00002f);
			
			float stopY = (((int)stopGrid->cubeStack.size() - 0) * 2.f) + 1.f;

			if (y <= stopY)
			{
				obj->SetLocation(stopGrid->x, stopY, stopGrid->z);

				obj->SetRotation(0, 0, 0);

				status = 2;

				return true;
			}

			obj->SetLocation(stopGrid->x, y, stopGrid->z);
		}

		return false;
	}
};

CubeGridItem cubeGrid[CUBEGRID_SIZE_Z][CUBEGRID_SIZE_X];

MovingCube movingCube[MOVING_CUBES_COUNT];

MovingCube movingUpCube[CUBEGRID_CUBE_COUNT];
int movingUpCubeCount = 0;

void SelectCubeMoveUp(int cubeNr, float timer)
{
	int x, z, toX = -1, toZ = -1, dir;

	int counter = 100;

	do
	{
		x = (rand() % (CUBEGRID_SIZE_X >> 1)) + (CUBEGRID_SIZE_X >> 2);
		z = (rand() % (CUBEGRID_SIZE_Z >> 1)) + (CUBEGRID_SIZE_Z >> 2);

		if ((cubeGrid[z][x].cubeStack.size() < 1) || cubeGrid[z][x].active)
		{
			continue;
		}

		if (cubeGrid[z - 1][x].active || cubeGrid[z + 1][x].active || 
			cubeGrid[z][x - 1].active || cubeGrid[z][x + 1].active)
		{
			continue;
		}

		movingUpCube[movingUpCubeCount].Set(&cubeGrid[z][x], NULL, cubeGrid[z][x].cubeStack.top(), 
			5, timer);

		cubeGrid[z][x].cubeStack.pop();

		movingUpCubeCount++;

		return;
	} while (--counter > 0);

	for (int z = 0; z < CUBEGRID_SIZE_Z; z++)
	{
		for (int x = 0; x < CUBEGRID_SIZE_X; x++)
		{
			if (cubeGrid[z][x].cubeStack.size() > 0)
			{
				movingUpCube[movingUpCubeCount].Set(&cubeGrid[z][x], NULL, cubeGrid[z][x].cubeStack.top(), 
							5, timer);

				cubeGrid[z][x].cubeStack.pop();

				movingUpCubeCount++;

				return;
			}
		}
	}
}

void SelectCube(int cubeNr, float timer)
{
	int x, z, toX = -1, toZ = -1, dir;

	do
	{
		x = (rand() % (CUBEGRID_SIZE_X >> 1)) + (CUBEGRID_SIZE_X >> 2);
		z = (rand() % (CUBEGRID_SIZE_Z >> 1)) + (CUBEGRID_SIZE_Z >> 2);

		if ((cubeGrid[z][x].cubeStack.size() < 1) || cubeGrid[z][x].active)
		{
			continue;
		}

		dir = rand() % 4;

		int counter = 4;

		do
		{
			dir = (dir + 1) % 4;

			switch (dir)
			{
			case 0:
				if (((cubeGrid[z][x].cubeStack.size() - 1) >= cubeGrid[z - 1][x].cubeStack.size()) && !cubeGrid[z - 1][x].active)
				{
					toX = x; toZ = z - 1;					
				}
				break;
			case 1:
				if (((cubeGrid[z][x].cubeStack.size() - 1) >= cubeGrid[z + 1][x].cubeStack.size()) && !cubeGrid[z + 1][x].active)
				{
					toX = x; toZ = z + 1;
				}
				break;
			case 2:
				if (((cubeGrid[z][x].cubeStack.size() - 1) >= cubeGrid[z][x - 1].cubeStack.size()) && !cubeGrid[z][x - 1].active)
				{
					toX = x - 1; toZ = z;
				}
				break;
			case 3:
				if (((cubeGrid[z][x].cubeStack.size() - 1) >= cubeGrid[z][x + 1].cubeStack.size()) && !cubeGrid[z][x + 1].active)
				{
					toX = x + 1; toZ = z;
				}
				break;
			}
		} while ((counter-- != 0) && ((toX != -1) && (toZ != -1)));
	} while ((toX == -1) && (toZ == -1));

	movingCube[cubeNr].Set(&cubeGrid[z][x], &cubeGrid[toZ][toX], cubeGrid[z][x].cubeStack.top(), 
		dir, timer);
}

void Effect03::Init() 
{
	scene = new Scene(); 

	srand(24);

	// create the grid
	for (int z = 0; z < CUBEGRID_SIZE_Z; z++)
	{
		for (int x = 0; x < CUBEGRID_SIZE_X; x++)
		{
			cubeGrid[z][x].x = (x - (CUBEGRID_SIZE_X / 2.f)) * 2.f;
			cubeGrid[z][x].z = (z - (CUBEGRID_SIZE_Z / 2.f)) * 2.f;
		}
	}

	// create the cubes
	for (int i = 0; i < CUBEGRID_CUBE_COUNT; i++)
	{
		Object* obj = Primitives::Cube(1, 1.f); 

		obj->SetTexture(textureLoader->GetTexture("cubes"));

		while (true)
		{
			int x = (rand() % 30) + (CUBEGRID_SIZE_X >> 1) - 15;
			int z = (rand() % 30) + (CUBEGRID_SIZE_Z >> 1) - 15;

			if (cubeGrid[z][x].cubeStack.size() < 5)
			{
				float xx = cubeGrid[z][x].x;
				float yy = cubeGrid[z][x].cubeStack.size() * 2.f + 1.f;
				float zz = cubeGrid[z][x].z;

				cubeGrid[z][x].cubeStack.push(obj);

				obj->SetLocation(xx, yy, zz);

				break;
			}
		}

		obj->Finish(false);

		scene->AddObject(obj);
	}

	for (int i = 0; i < MOVING_CUBES_COUNT; i++)
	{
		SelectCube(i, ((float)i / MOVING_CUBES_COUNT) * CUBE_ROTATION_TIME);
	}

	scene->AddLight(new Light());

	scene->light[0]->SetLocation(20, 10, -20);



	Object* plane = Primitives::Plane(10, 10, 100.f, 100.f);

	plane->ScaleUV(40, 40);


	plane->SetTexture(textureLoader->GetTexture("cubesfloor"));

	plane->Finish(false);

	scene->AddObject(plane);
}

void Effect03::Do(float timer, int pos, int row) 
{
	pyramid->SetAmbientLight(0x101010);
	pyramid->SetFogNone();

	scene->camera->SetFarPlane(110);
	scene->camera->SetNearPlane(5);

	pyramid->SetFogLinear(50, 80, true);

	for (int i = 0; i < MOVING_CUBES_COUNT; i++)
	{
		if (movingCube[i].Update(timer))
		{
			// update grid
			Object* cube = movingCube[i].startGrid->cubeStack.top();

			movingCube[i].startGrid->cubeStack.pop();
			movingCube[i].startGrid->active = false;

			movingCube[i].stopGrid->cubeStack.push(cube);
			movingCube[i].stopGrid->active = false;

			// select new cube to move around
			if (status == 0)
			{
				SelectCube(i, timer);
			}
		}
	}
	
	int cubeAddCount = (timer - tempTimer[40]) * 0.2f;

	tempTimer[40] = timer;

	if (status >= 1)
	{
		for (int i = 0; i < cubeAddCount; i++)
		{
			SelectCubeMoveUp(i, timer);
		}

		for (int i = 0; i < movingUpCubeCount; i++)
		{
			movingUpCube[i].Update(timer);
		}
	}

	scene->light[0]->SetLocation(cos(timer / 2000.f) * 20.f, 15, cos(timer / 2500.f) * 20.f);

	/*if (status == 1)
	{*/
		float dif = timer * 0.0005f;

		float y = 5;

		if (dif < (_PI * 0.5f))
		{
			y = 35.f - sin(dif) * 30.f;
		}

		scene->camera->SetTarget(0, y, 0);
	//}

	float camX = 30.f;
	float camZ = 50.f;

	if (status == 1)
	{
		camX += (timer - tempTimer[1]) * 0.002f;
		camZ += (timer - tempTimer[1]) * 0.002f;
	}

	scene->camera->SetLocation(sin(timer / 3000.f) * camX, 20, cos(timer / 3000.f) * camZ);

	pyramid->SetRenderTarget(renderChain->GetOriginal());

	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	scene->Render();

	pyramid->ResetRenderTarget();

	postProcessor->psBrightPass->SetLuminance(0.03f);
	postProcessor->psBloom->SetBloomScale(1.1f);

	postProcessor->chainGlow01->Render();

	pyramid->SetTexture(renderChain->GetSource(), 0);
	drawer2D->BeginScene(BLEND_NONE);
	drawer2D->DrawFullscreen();
	drawer2D->EndScene();
}

void Effect03::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}