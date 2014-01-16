/*
	
	Southside Variations - Effect18

	Description:

	Black sperm

*/

#include "Main.h"

#include "Effect21.h"

#define FX21_SPERM_COUNT 1
#define FX21_SPRITE_COUNT 40

#define FX21_PATH_SIZE 60

Vector fx21Location[FX21_PATH_SIZE];
Vector fx21Rotation[FX21_PATH_SIZE];

Vector fx21Position[FX21_SPERM_COUNT];

void Effect21::Init() 
{
	scene = new Scene();

	for (int j = 0; j < FX21_SPERM_COUNT; j++)
	{
		SpriteList* sp = new SpriteList(FX21_SPRITE_COUNT, 0.3f, textureLoader->GetTexture("sperm"), BLEND_ADD);

		for (int i = 1; i < FX21_SPRITE_COUNT; i++)
		{
			sp->sprite[i].diffuse = MixColor(0.75f + ((i / 4.f) / (float)FX21_SPRITE_COUNT), 0xffffff, 0x000000);
		}

		sp->Finish(true);

		scene->AddSpriteList(sp);
	}

	Vector rotation(0, 0, 0);
	Vector location(-10, 0, 0);

	int index = 0;

	for (int i = 0; i < 60; i++)
	{
		fx21Location[index] = Vector(10.f - (i * 0.3f), sin(i * 0.2f) * 0.5f - 4.0f, -1.f);
		fx21Rotation[index] = Vector(0, 0, 0);

		index++;
	}

	scene->camera->SetFarPlane(20.f);
	scene->camera->SetNearPlane(1.f);

	Object* cartoon = Primitives::Plane(1, 1, 0.45f, 0.2f);

	cartoon->ScaleUV(0.9f, 0.9f);

	cartoon->SetRotation(-90, 0, 0);

	cartoon->SetTexture(textureLoader->GetTexture("cartoon"));
	cartoon->SetTransparency(BLEND_ADD);

	scene->AddObject(cartoon);

	//scene->AddSpriteList(new SpriteList(1, 1.f, textureLoader->GetTexture("cartoon"), BLEND_ADD));

	//scene->spriteList[1]->Finish(true);
}

void MoveSpermCell21(SpriteList* sp, float timer, Vector pos)
{
	
	//timer += 2000;

	const float speed = 0.5f;
	const int nrSprites = 40;
	const float keyLength = 400 * speed;
	//Vector pos(2, 0, 0);

	float timer3 = timer;

	for (int i = 0; i < nrSprites; i++)
	{
		int key1 = timer / keyLength;

		if (key1 < 0) key1 = 0;
		if (key1 >= FX21_PATH_SIZE - 2) key1 = FX21_PATH_SIZE - 2;

		int key2 = key1 + 1;

		float timer2 = (int)timer % (int)keyLength;

		Vector loc, rot;
	
		rot.x = fx21Rotation[key1].x + ((fx21Rotation[key2].x - fx21Rotation[key1].x) / keyLength) * timer2;
		rot.y = fx21Rotation[key1].y + ((fx21Rotation[key2].y - fx21Rotation[key1].y) / keyLength) * timer2;
		rot.z = fx21Rotation[key1].z + ((fx21Rotation[key2].z - fx21Rotation[key1].z) / keyLength) * timer2;

		if (i > 0)
		{
			loc.z = sin((i * 0.3f) - (timer3 * 0.02f)) * 0.2f;
		}

		loc.z -= 0.f;

		loc.x += fx21Location[key1].x + ((fx21Location[key2].x - fx21Location[key1].x) / keyLength) * timer2;
		loc.y += fx21Location[key1].y + ((fx21Location[key2].y - fx21Location[key1].y) / keyLength) * timer2;
		loc.z += fx21Location[key1].z + ((fx21Location[key2].z - fx21Location[key1].z) / keyLength) * timer2;

		sp->sprite[i].x = loc.x;
		sp->sprite[i].y = loc.y;
		sp->sprite[i].z = loc.z;

		timer -= 50.f * speed;
	}
}

void Effect21::Do(float timer, int pos, int row) 
{
	pyramid->SetAmbientLight(0xffffff);

	scene->object[0]->SetEnabled(false);


	scene->object[0]->SetAmbient(1, 1, 1);

	if (timer > 4000)
	{
		if (timer < 4500)
		{
			float c = MixColor((timer - 4300) / 300.f, 0x00, 0xff)  / 255.f;
			
			scene->object[0]->SetAmbient(c, c, c);
		}

		if (timer > 5500)
		{
			float c = MixColor((timer - 5500) / 300.f, 0xff, 0x00)  / 255.f;
			
			scene->object[0]->SetAmbient(c, c, c);
		}

		if (timer < 6000)
		{
			timer = 4000 + ((timer - 4000) / 2.f);

			scene->object[0]->SetEnabled(true);
		}
		else
		{
			timer = 5000 + (timer - 6000);
		}
	}

	for (int i = 0; i < FX21_SPERM_COUNT; i++)
	{
		MoveSpermCell21(scene->spriteList[i], timer * 1.f, Vector(0, 0, 0));
	}

	scene->object[0]->location.x = scene->spriteList[0]->sprite[0].x - 0.6f;
	scene->object[0]->location.y = scene->spriteList[0]->sprite[0].y + 0.3f;
	scene->object[0]->location.z = scene->spriteList[0]->sprite[0].z;

	scene->camera->SetLocation(0, (cos(timer / 2600.f) * 2.f - 2.f) * 2.f, -6.f * 2.f);

	scene->Render();
}

void Effect21::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}