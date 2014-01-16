/*
	
	Southside Variations - Effect04

	Description:

	Retro lijnen, dus gebend, maar dan 3 of 4 om een centrale heen gebonden.

*/

#include "Main.h"

#include "Effect04.h"

#define SPERM_COUNT 40

Vector spermLocation[SPERM_COUNT];

#define TUBE_SEGMENTX 20
#define TUBE_SEGMENTY 100

#define TUBE_RADIUS 0.25f

#define TUBE_COUNT 5

Vector middleList[TUBE_SEGMENTY + 1];
Vector rotationList[TUBE_SEGMENTY + 1];

float GetRed(DWORD color)
{
	return ((color & 0xff0000) >> 16) / 255.f;
}

float GetGreen(DWORD color)
{
	return ((color & 0x00ff00) >> 8) / 255.f;
}

float GetBlue(DWORD color)
{
	return ((color & 0x0000ff)) / 255.f;
}

void Effect04::MoveTubes(float timer)
{
	Vector centerPoint(0, 0, 0);
	Vector direction(0, 0.7f, 0);
	Vector rotation(0, 0, 0);

	Vector centerPointDif[] =
	{
		Vector(0, 0, 0),
		Vector(0.5f, 0, 0),
		Vector(-0.5f, 0, 0),
		Vector(0, 0, 0.5f),
		Vector(0, 0, -0.5f)
	};

	Vector centerPointRot[TUBE_COUNT];

	int index = 0;
	float tubeRot = timer / -400.f;
	for (int j = 0; j < TUBE_SEGMENTY + 1; j++)
	{
		middleList[j] = centerPoint;
		rotationList[j] = rotation;

		Matrix matRotation = Matrix::RotateZ(rotation.z) * Matrix::RotateY(rotation.y) *
			Matrix::RotateX(rotation.x);

		Matrix matTubeRot = Matrix::RotateY(tubeRot + (sin((j * 0.1f) + (timer / 500.f)) * 0.7f));

		tubeRot += 0.5f;

		float scale = 1.2f + sin((j * 0.2f) + (timer / 250.f)) * 0.2f;

		for (int k = 0; k < TUBE_COUNT; k++)
		{
			centerPointRot[k] = centerPointDif[k];// * matTubeRot;
		}

		Matrix matFinal = matTubeRot * matRotation;

		for (int i = 0; i < TUBE_SEGMENTX + 1; i++)
		{

			for (int k = 0; k < TUBE_COUNT; k++)
			{
				float x = (sin((float)i * _2PI / TUBE_SEGMENTX) * TUBE_RADIUS * scale) + (centerPointRot[k].x * scale);
				float y = centerPointRot[k].y * scale;
				float z = (cos((float)i * _2PI / TUBE_SEGMENTX) * TUBE_RADIUS * scale) + (centerPointRot[k].z * scale);

				Vector vertex(x, y, z);

				vertex = (vertex * matFinal) + centerPoint;

				*(Vector*)&scene->object[k]->vertex[index] = vertex;
			}

			index++;
		}

		centerPoint += direction * matRotation;

		rotation.x = sin((j * 0.13f) + (timer / 10000000000.f)) * (sin(j * 0.13f) * 1.2f);
		rotation.y = cos(j * 0.11f) * 0.4f;
		rotation.z = cos((j * 0.11f) + (timer / 10000000000.f)) * 1.1f;
	}
}

void Effect04::Init() 
{
	scene = new Scene();

	scene->AddLight(new Light());

	Object* tube1 = Primitives::Tube(TUBE_SEGMENTX, TUBE_SEGMENTY, 1.f, 10.f);
	Object* tube2 = Primitives::Tube(TUBE_SEGMENTX, TUBE_SEGMENTY, 1.f, 10.f);
	Object* tube3 = Primitives::Tube(TUBE_SEGMENTX, TUBE_SEGMENTY, 1.f, 10.f);
	Object* tube4 = Primitives::Tube(TUBE_SEGMENTX, TUBE_SEGMENTY, 1.f, 10.f);
	Object* tube5 = Primitives::Tube(TUBE_SEGMENTX, TUBE_SEGMENTY, 1.f, 10.f);

	scene->AddObject(tube1);
	scene->AddObject(tube2);
	scene->AddObject(tube3);
	scene->AddObject(tube4);
	scene->AddObject(tube5);

	DWORD color1 = 0x759D60;
	DWORD color2 = 0x54A96C;
	DWORD color3 = 0x67BC9F;
	DWORD color4 = 0x72D0CF;
	
	tube1->SetAmbient(1, 1, 1);

	tube2->SetAmbient(GetRed(color1), GetGreen(color1), GetBlue(color1));
	tube3->SetAmbient(GetRed(color2), GetGreen(color2), GetBlue(color2));
	tube4->SetAmbient(GetRed(color3), GetGreen(color3), GetBlue(color3));
	tube5->SetAmbient(GetRed(color4), GetGreen(color4), GetBlue(color4));

	tube2->SetDiffuse(GetRed(color1), GetGreen(color1), GetBlue(color1));
	tube3->SetDiffuse(GetRed(color2), GetGreen(color2), GetBlue(color2));
	tube4->SetDiffuse(GetRed(color3), GetGreen(color3), GetBlue(color3));
	tube5->SetDiffuse(GetRed(color4), GetGreen(color4), GetBlue(color4));

	for (int i = 0; i < 5; i++)
	{
		scene->object[i]->SetTexture(textureLoader->GetTexture("tube2"));
		scene->object[i]->ScaleUV(1, 20);
	}

	scene->object[0]->SetTexture(textureLoader->GetTexture("tube1"));

	tube1->Finish(true);
	tube2->Finish(true);
	tube3->Finish(true);
	tube4->Finish(true);
	tube5->Finish(true);

	const int nrSprites = 40;

	for (int j = 0; j < SPERM_COUNT; j++)
	{
		SpriteList* sp = new SpriteList(nrSprites, 0.3f, textureLoader->GetTexture("sperm"), BLEND_ADD);

		for (int i = 1; i < nrSprites; i++)
		{
			sp->sprite[i].diffuse = MixColor(0.75f + ((i / 4.f) / (float)nrSprites), 0xffffff, 0x000000);
		}

		sp->Finish(true);

		scene->AddSpriteList(sp);

		float t = rand() % 1000;

		spermLocation[j].x = sin((t / 500.f) * _PI) * 1.8f;
		spermLocation[j].y = 0.0f;
		spermLocation[j].z = cos((t / 500.f) * _PI) * 1.8f;
	}
}

void MoveSpermCell(SpriteList* sp, float timer, Vector pos)
{
	timer += 2000;

	const float speed = 0.5f;
	const int nrSprites = 40;
	const float keyLength = 400 * speed;
	//Vector pos(2, 0, 0);

	float timer3 = timer;

	for (int i = 0; i < nrSprites; i++)
	{
		int key1 = timer / keyLength;

		if (key1 < 0) key1 = 0;
		if (key1 > TUBE_SEGMENTY) key1 = TUBE_SEGMENTY;

		int key2 = key1 + 1;

		key1 = ((TUBE_SEGMENTY + 1) - key1) % (TUBE_SEGMENTY + 1);
		key2 = (key1 - 1) % (TUBE_SEGMENTY + 1);

		float timer2 = (int)timer % (int)keyLength;

		Vector loc, rot;
	
		rot.x = rotationList[key1].x + ((rotationList[key2].x - rotationList[key1].x) / keyLength) * timer2;
		rot.y = rotationList[key1].y + ((rotationList[key2].y - rotationList[key1].y) / keyLength) * timer2;
		rot.z = rotationList[key1].z + ((rotationList[key2].z - rotationList[key1].z) / keyLength) * timer2;

		Matrix matRotation = Matrix::RotateZ(rot.z) * Matrix::RotateY(rot.y) * Matrix::RotateX(rot.x);

		if (i > 0)
		{
			Matrix matY = Matrix::RotateY(sin((i * 0.3f) - (timer3 * 0.02f)) * 0.05f);

			matRotation = matY * matRotation;
		}

		loc = pos * matRotation;

		loc.x += middleList[key1].x + ((middleList[key2].x - middleList[key1].x) / keyLength) * timer2;
		loc.y += middleList[key1].y + ((middleList[key2].y - middleList[key1].y) / keyLength) * timer2;
		loc.z += middleList[key1].z + ((middleList[key2].z - middleList[key1].z) / keyLength) * timer2;

		sp->sprite[i].x = loc.x;
		sp->sprite[i].y = loc.y;
		sp->sprite[i].z = loc.z;

		timer -= 40.f * speed;
	}


	//for (int i = 1; i < nrSprites; i++)
	//{
	//	sp->sprite[i].x = i * 0.07f;
	//	sp->sprite[i].y = 0 + sin((i * 0.3f) - (timer * 0.01f)) * 0.1f;
	//	sp->sprite[i].z = 0;

	//	sp->sprite[i].diffuse = MixColor(0.75f + ((i / 4.f) / (float)nrSprites), 0xffffff, 0x000000);
	//}
}

void Effect04::Do(float timer, int pos, int row) 
{
	//timer += 10000;

	pyramid->SetAmbientLight(0x202020);
	pyramid->SetFogNone();

	MoveTubes(timer);


	for (int i = 0; i < SPERM_COUNT; i++)
	{
		MoveSpermCell(scene->spriteList[i], timer - (i * 400), spermLocation[i]);
	}


	scene->camera->SetLocation(1, 15, 2);
	scene->camera->SetTarget(1.1f, 14.0, 18);
	scene->camera->SetRoll(-90);

	pyramid->SetRenderTarget(renderChain->GetOriginal());

	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	scene->Render();

	pyramid->ResetRenderTarget();

	postProcessor->psBrightPass->SetLuminance(0.017f);
	postProcessor->psBloom->SetBloomScale(1.15f);


	postProcessor->chainGlow01->Render();

	pyramid->SetTexture(renderChain->GetSource(), 0);
	drawer2D->BeginScene(BLEND_ADD);
	drawer2D->DrawFullscreen();
	drawer2D->EndScene();
}

void Effect04::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}