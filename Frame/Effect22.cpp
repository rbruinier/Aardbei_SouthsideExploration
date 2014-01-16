/*
	
	Southside Variations - Effect18

	Description:

	Black sperm

*/

#include "Main.h"

#include "Effect22.h"

#define FX22_SPERM_COUNT 1
#define FX22_SPRITE_COUNT 40

#define FX22_PATH_SIZE 60

Vector fx22Location[FX22_PATH_SIZE];
Vector fx22Rotation[FX22_PATH_SIZE];

void Effect22::Init() 
{
	scene = new Scene();

	for (int j = 0; j < FX22_SPERM_COUNT; j++)
	{
		SpriteList* sp = new SpriteList(FX22_SPRITE_COUNT, 0.3f, textureLoader->GetTexture("sperm"), BLEND_ADD);

		for (int i = 1; i < FX22_SPRITE_COUNT; i++)
		{
			sp->sprite[i].diffuse = MixColor(0.75f + ((i / 4.f) / (float)FX22_SPRITE_COUNT), 0xffffff, 0x000000);
		}

		sp->Finish(true);

		scene->AddSpriteList(sp);
	}

	Vector rotation(0, 0, 0);
	Vector location(-10, 0, 0);

	int index = 0;

	for (int i = 0; i < 60; i++)
	{
		fx22Location[index] = Vector(0, -8.0f + (i * 0.1f), -6.f + (i * 0.3f));
		fx22Rotation[index] = Vector(0, 0, 0);

		index++;
	}

	scene->camera->SetFarPlane(30.f);
	scene->camera->SetNearPlane(1.f);

	Object* cartoon = Primitives::Plane(1, 1, 0.45f * 1.5f, 0.2f * 1.5f);

	cartoon->ScaleUV(0.9f, 0.9f);

	cartoon->SetRotation(-90, 0, 0);

	cartoon->SetTexture(textureLoader->GetTexture("cartoon2"));
	cartoon->SetTransparency(BLEND_ADD);

	scene->AddObject(cartoon);
}

void MoveSpermCell22(SpriteList* sp, float timer, Vector pos)
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
		if (key1 >= FX22_PATH_SIZE - 2) key1 = FX22_PATH_SIZE - 2;

		int key2 = key1 + 1;

		float timer2 = (int)timer % (int)keyLength;

		Vector loc, rot;

		if (i > 0)
		{
			loc.x = sin((i * 0.3f) - (timer3 * 0.02f)) * 0.15f;
		}

		loc.z -= 0.f;

		loc.x += fx22Location[key1].x + ((fx22Location[key2].x - fx22Location[key1].x) / keyLength) * timer2;
		loc.y += fx22Location[key1].y + ((fx22Location[key2].y - fx22Location[key1].y) / keyLength) * timer2;
		loc.z += fx22Location[key1].z + ((fx22Location[key2].z - fx22Location[key1].z) / keyLength) * timer2;

		sp->sprite[i].x = loc.x;
		sp->sprite[i].y = loc.y;
		sp->sprite[i].z = loc.z;

		timer -= 50.f * speed;
	}


}

void Effect22::Do(float timer, int pos, int row) 
{
	pyramid->SetAmbientLight(0xffffff);

	for (int i = 0; i < FX22_SPERM_COUNT; i++)
	{
		MoveSpermCell22(scene->spriteList[i], timer * 1.f, Vector(0, 0, 0));
	}


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
			scene->object[0]->SetEnabled(true);
		}
		else
		{
		}
	}

	scene->object[0]->location.x = scene->spriteList[0]->sprite[0].x - 0.8f;
	scene->object[0]->location.y = scene->spriteList[0]->sprite[0].y + 0.4f;
	scene->object[0]->location.z = scene->spriteList[0]->sprite[0].z;

	scene->camera->SetLocation(0, 4, -10.f);

	scene->Render();
}

void Effect22::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}