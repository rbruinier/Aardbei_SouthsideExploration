/*
	
	Southside Variations - Effect07

	Description:

	The credits

*/

#include "Main.h"

#include "Effect07.h"

int oyiseer[] = // 25x5 = 125
{
	1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 
	1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 
	1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 
	1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 
	1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1
};

int rob[] = // 11x5 = 55
{
	1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 
	0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 
	1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 
	1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 
	1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1 
};

int zabutom[] = // 27x5 = 135
{
	1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 
	0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 
	0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 
	1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 
	1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1
};

Vector* fx07Centers;
Vector* fx07Directions;

void Effect07::Init() 
{
	// calculate sprites
	int nrSprites = 0;

	for (int i = 0; i < 125; i++)
	{
		if (oyiseer[i]) nrSprites++;
	}

	for (int i = 0; i < 55; i++)
	{
		if (rob[i]) nrSprites++;
	}

	for (int i = 0; i < 135; i++)
	{
		if (zabutom[i]) nrSprites++;
	}

	// create a new scene

	float offset[3] = {1.15f, 0.25f, -0.65f};

	scene = new Scene();	

	SpriteList* spriteList = new SpriteList(nrSprites, 0.1f, textureLoader->GetTexture("credits"), BLEND_ALPHA);

	int index = 0;

	// oyiseer
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 25; x++)
		{
			if (oyiseer[(y * 25) + x])
			{
				spriteList->sprite[index].x = ((-25 / 2.f) + x) * 0.1f;
				spriteList->sprite[index].y = (y * -0.1f) + offset[1];
				spriteList->sprite[index].z = 0;

				index++;
			}
		}
	}

	// rob
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 11; x++)
		{
			if (rob[(y * 11) + x])
			{
				spriteList->sprite[index].x = ((-11 / 2.f) + x) * 0.1f;
				spriteList->sprite[index].y = (y * -0.1f) + offset[0];
				spriteList->sprite[index].z = 0;

				index++;
			}
		}
	}

	// zabotum
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 27; x++)
		{
			if (zabutom[(y * 27) + x])
			{
				spriteList->sprite[index].x = ((-27 / 2.f) + x) * 0.1f;
				spriteList->sprite[index].y = (y * -0.1f) + offset[2];
				spriteList->sprite[index].z = 0;

				index++;
			}
		}
	}

	spriteList->Finish(true);

	fx07Centers = new Vector[spriteList->nrSprites];
	fx07Directions = new Vector[spriteList->nrSprites];

	srand(456);

	for (int i = 0; i < spriteList->nrSprites; i++)
	{
		fx07Centers[i].x = spriteList->sprite[i].x;
		fx07Centers[i].y = spriteList->sprite[i].y;

		float period = rand() % 1000;

		fx07Directions[i].x = sin((period / 1000.f) * _2PI) * 1.f;
		fx07Directions[i].y = cos((period / 1000.f) * _2PI) * 1.f;
	}

	scene->AddSpriteList(spriteList);
}

void Effect07::Do(float timer, int pos, int row) 
{
	DWORD color = MixColor(timer * 0.0004f, 0x00000000, 0xffffffff, true);

	color |= (DWORD)0xffffff;
	
	for (int i = 0; i < scene->spriteList[0]->nrSprites; i++)
	{
		scene->spriteList[0]->sprite[i].diffuse = color;
	}

	float z = -4;

	if (status == 1)
	{
		float timeDif = (timer - tempTimer[1]) * 0.001f;

		z += (timeDif * timeDif) * 0.7f;

		for (int i = 0; i < scene->spriteList[0]->nrSprites; i++)
		{
			scene->spriteList[0]->sprite[i].x = fx07Centers[i].x;
			scene->spriteList[0]->sprite[i].y = fx07Centers[i].y;

			scene->spriteList[0]->sprite[i].x += fx07Directions[i].x * (timeDif * timeDif) * 0.3f;
			scene->spriteList[0]->sprite[i].y += fx07Directions[i].y * (timeDif * timeDif) * 0.3f;
		}

	}

	scene->camera->SetLocation(0, 0, z);
	scene->camera->SetTarget(0, 0, z + 4);


	//pyramid->SetRenderTarget(renderChain->GetOriginal());
	//pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	scene->Render();

	//pyramid->ResetRenderTarget();

	//postProcessor->psBrightPass->SetLuminance(0.02f);
	//postProcessor->psBloom->SetBloomScale(0.8f);

	//postProcessor->chainGlow01->Render();

	//pyramid->SetTexture(renderChain->GetSource(), 0);
	//drawer2D->BeginScene(BLEND_ADD);
	//drawer2D->DrawFullscreen();
	//drawer2D->EndScene();
}

void Effect07::Destroy() 
{
	// clean up
	scene->Destroy();

	// so long, farewell, goodbye
	delete scene;
}