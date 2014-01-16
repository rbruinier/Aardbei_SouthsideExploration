/*
	
	Southside Variations - Effect18

	Description:

	Black sperm

*/

#include "Main.h"

#include "Effect18.h"

#define FX18_SPERM_COUNT 40
#define FX18_SPRITE_COUNT 40

#define FX18_PATH_SIZE 40

Vector fx18Location[FX18_PATH_SIZE];
Vector fx18Rotation[FX18_PATH_SIZE];

Vector fx18Position[FX18_SPERM_COUNT];

void Effect18::Init() 
{
	scene = new Scene();

	for (int j = 0; j < FX18_SPERM_COUNT; j++)
	{
		SpriteList* sp = new SpriteList(FX18_SPRITE_COUNT, 0.3f, textureLoader->GetTexture("sperm"), BLEND_SUBTRACT);

		for (int i = 1; i < FX18_SPRITE_COUNT; i++)
		{
			sp->sprite[i].diffuse = MixColor(0.75f + ((i / 4.f) / (float)FX18_SPRITE_COUNT), 0xffffff, 0x000000);
		}

		sp->Finish(true);

		scene->AddSpriteList(sp);

		fx18Position[j].x = (rand()%1000) * 0.005f;
		fx18Position[j].y = (rand()%1000) * 0.005f;
		fx18Position[j].z = (rand()%1000) * 0.005f;
	}

	Vector rotation(0, 0, 0);
	Vector location(-10, 0, 0);

	for (int i = 0; i < FX18_PATH_SIZE; i++)
	{
		Matrix matRot = Matrix::RotateZ(rotation.z);

		fx18Location[i] = location;

		location += Vector(0.5f, 0, 0) * matRot;

		rotation.z += sin(i * 1.6f) * 0.2f;
	}
}

void Effect18::Do(float timer, int pos, int row) 
{
	float timer2 = timer;

	const float speed = 0.5f;
	const float keyLength = 400 * speed;

	for (int j = 0; j < FX18_SPERM_COUNT; j++)
	{
		float timer3 = timer2;

		SpriteList* sp = scene->spriteList[j];

		Vector pos(1, 0, 0);

		for (int i = 0; i < FX18_SPRITE_COUNT; i++)
		{
			int key1 = timer3 / keyLength;

			if (key1 < 0) key1 = 0;
			if (key1 >= FX18_PATH_SIZE - 1) key1 = FX18_PATH_SIZE - 1;

			int key2 = key1 + 1;

			//key1 = ((TUBE_SEGMENTY + 1) - key1) % (TUBE_SEGMENTY + 1);
			//key2 = (key1 - 1) % (TUBE_SEGMENTY + 1);

			float timer4 = (int)timer3 % (int)keyLength;

			Vector loc, rot;
		
			//rot.x = rotationList[key1].x + ((rotationList[key2].x - rotationList[key1].x) / keyLength) * timer4;
			//rot.y = rotationList[key1].y + ((rotationList[key2].y - rotationList[key1].y) / keyLength) * timer4;
			rot.z = fx18Rotation[key1].z + ((fx18Rotation[key2].z - fx18Rotation[key1].z) / keyLength) * timer4;

			Matrix matRotation = Matrix::RotateZ(rot.z) * Matrix::RotateY(rot.y) * Matrix::RotateX(rot.x);

			if (i > 0)
			{
				Matrix matZ = Matrix::RotateZ(sin((i * 0.3f) - (timer3 * 0.02f)) * 0.05f);

				matRotation = matZ * matRotation;
			}

			loc = fx18Position[j] * matRotation;

			loc.x += fx18Location[key1].x + ((fx18Location[key2].x - fx18Location[key1].x) / keyLength) * timer4;
			loc.y += fx18Location[key1].y + ((fx18Location[key2].y - fx18Location[key1].y) / keyLength) * timer4;
			loc.z += fx18Location[key1].z + ((fx18Location[key2].z - fx18Location[key1].z) / keyLength) * timer4;

			sp->sprite[i].x = loc.x;
			sp->sprite[i].y = loc.y;
			sp->sprite[i].z = loc.z;

			timer3 -= 40.f * speed;
		}

		timer2 -= 400;
	}

	scene->Render();
}

void Effect18::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}