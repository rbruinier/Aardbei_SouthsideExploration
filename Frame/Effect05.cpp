/*
	
	Southside Variations - Effect05

	Description:

	Een bol opgebouwd uit kubussen. Als dat eenmaal lukt uit elkaar bewegen, etc

*/

#include "Main.h"

#include "Effect05.h"

void Effect05::Init() 
{
	scene = new Scene();

	for (int a = 0; a < FX05_CUBE_GRID_SIZE; a++)
	{
		for (int b = 0; b < FX05_CUBE_GRID_SIZE; b++)
		{
			for (int c = 0; c < FX05_CUBE_GRID_SIZE; c++)
			{
				Object* cube = Primitives::Cube(4, 1.f);

				cube->SetTexture(textureLoader->GetTexture("rasmus"));

				cube->SetLocation((b - (FX05_CUBE_GRID_SIZE >> 1) + 0.5f) * 2.f,
					(a - (FX05_CUBE_GRID_SIZE >> 1) + 0.5f) * 2.f,
					(c - (FX05_CUBE_GRID_SIZE >> 1) + 0.5f) * 2.f);

				scene->AddObject(cube);
			}
		}
	}

	float sphereSize = 2.8f;

	for (int j = 0; j < FX05_CUBE_COUNT; j++)
	{
		Object* cube = scene->object[j];

		bool out = false;
		bool in = false;

		for (int i = 0; i < cube->nrVertices; i++)
		{
			float xDif = cube->vertex[i].x + cube->location.x;
			float yDif = cube->vertex[i].y + cube->location.y;
			float zDif = cube->vertex[i].z + cube->location.z;

			float distance = sqrt((xDif * xDif) + (yDif * yDif) + (zDif * zDif));

			if (distance >= sphereSize)
			{
				out = true;
			}
			else
			{
				in = true;
			}
		}

		if (out && !in)
		{
			cube->SetEnabled(false);
		}
		else if (!out && in)
		{
		}
		else
		{
			for (int i = 0; i < cube->nrVertices; i++)
			{
				float xDif = cube->vertex[i].x + cube->location.x;
				float yDif = cube->vertex[i].y + cube->location.y;
				float zDif = cube->vertex[i].z + cube->location.z;

				float distance = sqrt((xDif * xDif) + (yDif * yDif) + (zDif * zDif));

				if (distance >= sphereSize)
				{
					float newX = (xDif / distance) * sphereSize;
					float newY = (yDif / distance) * sphereSize;
					float newZ = (zDif / distance) * sphereSize;

					cube->vertex[i].x = newX - cube->location.x;
					cube->vertex[i].y = newY - cube->location.y;
					cube->vertex[i].z = newZ - cube->location.z;
				}
			}
		}

		
		locations[j] = cube->location;

	//		cube->SetSpecular(1, 1, 1);
	//cube->SetPower(20.f);
	}

	scene->camera->SetNearPlane(2.f);
	scene->camera->SetFarPlane(120.f);

	scene->AddLight(new Light());

	//scene->light[0]->SetSpecular(1, 1, 1, 0.8f);

	//this->doResetOnPlay = false;
	


}

void Effect05::Do(float timer, int pos, int row) 
{
	pyramid->SetAmbientLight(0x202020);
	pyramid->SetFogNone();

	if (status >= 1)
	{
		timer += tempTimer[1];
	}

	float camScale = 12.5f;

	if (timer - 1500 >= 0)
	{
		float dif = (timer - 1500) * 0.0008f;

		if (dif < (_PI * 0.5f))
		{
			camScale = 102.5f - sin(dif) * 90.f;
		}
	}
	else
	{
		camScale = 102.5f;
	}

	tempTimer[10] = timer;
	//timer *= 2.2f;

	for (int j = 0; j < FX05_CUBE_COUNT; j++)
	{
		//if (((int)timer % 6000) < 4000)
		if (status >= 2)
		{
			float timer2 = (timer - tempTimer[1] - tempTimer[2]) * 2.2f;

			if (timer2 < 4000)
			{
				scene->object[j]->location = locations[j] * (-cos((timer2 / 2000.f) * _PI) * 0.5f + 1.5f);

				//timer2 *= 2.2f;
				if (timer2 > 1000 && timer2 < 3000)
				{
					timer2 -= 1000;

					//scene->object[j]->rotation.y = (((int)(timer2 - 1500) % 1000) / 1000.f) * _2PI;

					scene->object[j]->rotation.y = -cos(timer2 / 2000.f * _PI) * _PI + _PI;
				}
				else
				{
					scene->object[j]->rotation.y = 0;
				}
				//scene->object[j]->rotation.y = (((int)timer2 % 4000) / 4000.f) * _2PI;
				//scene->object[j]->rotation.z = (((int)timer2 % 4000) / 4000.f) * _2PI;
			}
			else
			{
				scene->object[j]->location = locations[j];
				scene->object[j]->rotation.y = 0;
				scene->object[j]->rotation.z = 0; 
			}
		}
		else
		{
			scene->object[j]->location = locations[j];
			scene->object[j]->rotation.y = 0;
			scene->object[j]->rotation.z = 0; 
		}
	}

	if (status >= 2)
	{
		float scale = 0.25f - (timer - tempTimer[1] - tempTimer[2]) * 0.0003f;

		if (scale < 0) scale = 0;

		Vector camKick(sin(timer / 30.f) * scale, cos(timer / 40.f) * scale, sin(timer / 25.f) * scale);

		for (int j = 0; j < FX05_CUBE_COUNT; j++)
		{
			scene->object[j]->location += camKick;
		}
	}

	timer = tempTimer[10];

	scene->camera->SetLocation(sin(timer / 1000.f) * camScale, 10, cos(timer / 1000.f) * camScale);

//	scene->light[0]->SetLocation(sin(timer / 500.f) * 1.f, sin(timer / 500.f) * 1.f, cos(timer / 500.f) * 1.f);
	scene->light[0]->SetLocation(scene->camera->location.x / 3.f, scene->camera->location.y / 3.f, scene->camera->location.z / 3.f);

	scene->Render();
}

void Effect05::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}