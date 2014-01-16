/*
	
	Southside Variations - Effect06

	Description:

	Greetings.. iets met letters, dunno wat

*/

#include "Main.h"

#include "Effect06.h"

#include "Effect22.h"

extern Effect* effect22;

#include "../System/VertexBuffer.h"


void Effect06::GetLetterU(char letter, float& u1, float& u2)
{
	// position of letters in texture (x loc)
	short letterPos[] =
	{
		4, 25, 45, 66, 87, // a .. e
		104, 122, 143, 161, 174, // f .. j
		190, 208, 227, 252, 273, // k .. o
		294, 315, 333, 350, 369, // p .. t
		385, 405, 426, 449, 467, // u .. y
		486 // z
	};

	if (letter == ' ')
	{
		u1 = 600;
	}
	else
	{
		u1 = letterPos[letter - 97] / 1024.f;
	}

	u2 = u1 + (22.f / 1024.f);

	if (letter == 'i' || letter == 'j' || letter == 't' || letter == 'l')
	{
		u2 = u1 + (18.f / 1024.f);
	}
}

Greeting* conspiracy;

Greeting* greetingList[50];

void Effect06::Init() 
{
	scene = new Scene();

	srand(50);

	// generate a bunch of random sprites with letters
	for (int i = 0; i < NR_LETTERS; i++)
	{
		letterList[i].vertices = &LettersVertices[i * 4];

		char letter = rand() % 27;

		if (letter == 26)
		{
			letter = ' ';
		}
		else
		{
			letter += 97;
		}

		letterList[i].letter = letter;

		float u1, u2;

		GetLetterU(letter, u1, u2);

		letterList[i].vertices[0].u = u1;
		letterList[i].vertices[0].v = 1;

		letterList[i].vertices[1].u = u2;
		letterList[i].vertices[1].v = 1;

		letterList[i].vertices[2].u = u1;
		letterList[i].vertices[2].v = 0;

		letterList[i].vertices[3].u = u2;
		letterList[i].vertices[3].v = 0;

		DWORD color = 0x181818;

		color = MixColor(0.6f, 0xcb4930, 0x000000);

		letterList[i].vertices[0].diffuse = color;
		letterList[i].vertices[1].diffuse = color;
		letterList[i].vertices[2].diffuse = color;
		letterList[i].vertices[3].diffuse = color;

		letterList[i].original.x = ((rand() % 10000) - 5000) * 0.001f;
		letterList[i].original.y = ((rand() % 10000) - 5000) * 0.001f;
		letterList[i].original.z = ((rand() % 10000) - 5000) * 0.001f;
	}

	// vertex buffer for letters
	pyramid->CreateVertexBuffer(NR_LETTERS * 4, sizeof(LETTER_VERTEX), LETTER_VERTEX_FVF, 
		true, false, &vb);

	// vertex buffer for 
	pyramid->CreateVertexBuffer(50, sizeof(LETTER_LINE_VERTEX), LETTER_LINE_VERTEX_FVF, 
		true, false, &lineVB);

	// create sprite list
	spriteList  = new SpriteList(50, 0.8f, textureLoader->GetTexture("cirkel"), BLEND_ADD);

	spriteList->Finish(true);

	greetingList[0] = new Greeting(letterList, "");
	greetingList[1] = new Greeting(letterList, "conspiracy");
	greetingList[2] = new Greeting(letterList, "tpolm");
	greetingList[3] = new Greeting(letterList, "mfx");
	greetingList[4] = new Greeting(letterList, "farbrausch");
	greetingList[5] = new Greeting(letterList, "asd tad");
	greetingList[6] = new Greeting(letterList, "cocoon");
	greetingList[7] = new Greeting(letterList, "fairlight");
	greetingList[8] = new Greeting(letterList, "plastic");
	greetingList[9] = new Greeting(letterList, "");
	greetingList[10] = new Greeting(letterList, "");
	greetingList[11] = new Greeting(letterList, "");

}

int Effect06::GetColor(float timer, int letterNR)
{
	if (timer < 500)
	{
		return MixColor((timer / 500.f) * 1.0f, 0xffffff, 0x000000);
	}
	else
	{
		timer -= 500;
		timer -= letterNR * 300.f;

		return MixColor((timer / 1000.f) * 0.5f, 0x000000, 0xffffff);
	}
}

void Effect06::Do(float timer, int pos, int row) 
{
	//timer += 4000;

	//if (timer >  4000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  8000 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  13000 && status == 2) Receive(3, timer, 0, 0);
	//if (timer >  17000 && status == 3) Receive(4, timer, 0, 0);

	// camera location
	//camera.SetLocation(sin(timer / 2000.f) * 15.f, sin(timer / 1400.f) * 15.f, cos(timer / 2000.f) * 15.f);
	float backupTimer = timer;

	float z = -20;

	if (status >= 0)
	{
		float dif = (timer - 2000) * 0.0004f;

		if (dif < (_PI * 0.5f))
		{
			z = 10 - sin(dif) * 30.f;
		}
	}

	if (status == 11)
	{
		float dif = (timer - tempTimer[11]) * 0.001f;

		z = -20.f - ((dif * dif) * 5.5f);
	}

	camera.SetLocation(0, 0, z);
	camera.SetTarget(0, 0, z + 20);

	camera.Update();

	
	Matrix matLocRot = Matrix::RotateY(timer * 0.001f);

	// recalculate timer for greetings
	timer = timer - tempTimer[status];

	pyramid->SetWorldMatrix(Matrix::Identity());

	// calculate inverse of camera and transform letters
	Matrix camMatrix;

	pyramid->GetViewMatrix(camMatrix);

	camMatrix._14 = 0;
	camMatrix._41 = 0;
	camMatrix._42 = 0;
	camMatrix._43 = 0;
	camMatrix._44 = 0;

	Matrix matRot = camMatrix.Inverse();

	#define size 0.2f

	Vector v1 = Vector(-size, -size, 0);
	Vector v2 = Vector( size, -size, 0);
	Vector v3 = Vector(-size,  size, 0);
	Vector v4 = Vector( size,  size, 0);

	v1 = v1 * matRot;	
	v2 = v2 * matRot;	
	v3 = v3 * matRot;
	v4 = v4 * matRot;


	for (int i = 0; i < NR_LETTERS; i++)
	{
		letterList[i].location = letterList[i].original * matLocRot;

		*(Vector*)&letterList[i].vertices[0] = v1 + letterList[i].location;
		*(Vector*)&letterList[i].vertices[1] = v2 + letterList[i].location;
		*(Vector*)&letterList[i].vertices[2] = v3 + letterList[i].location;
		*(Vector*)&letterList[i].vertices[3] = v4 + letterList[i].location;
	}


	int greetingNr = status;

	if (timer < 600 && status >= 1) greetingNr--;

	Greeting* currentGreeting = greetingList[greetingNr];

	// update cirkel sprites
	for (int i = 0; i < 50; i++)
	{
		spriteList->sprite[i].diffuse = 0;
	}

	for (int i = 0; i < currentGreeting->lettersSize; i++)
	{
		spriteList->sprite[i].x = currentGreeting->letters[i]->location.x;
		spriteList->sprite[i].y = currentGreeting->letters[i]->location.y;
		spriteList->sprite[i].z = currentGreeting->letters[i]->location.z;

		DWORD color = GetColor(timer, i);

		spriteList->sprite[i].diffuse = color;

		currentGreeting->letters[i]->vertices[0].diffuse = color;
		currentGreeting->letters[i]->vertices[1].diffuse = color;
		currentGreeting->letters[i]->vertices[2].diffuse = color;
		currentGreeting->letters[i]->vertices[3].diffuse = color;
	}

	spriteList->nrSprites = currentGreeting->lettersSize;

	// calculate lines
	for (int i = 0; i < currentGreeting->lettersSize - 1; i++)
	{
		int index1 = i;
		int index2 = i + 1;

		Vector location(currentGreeting->letters[i]->location.x, 
			currentGreeting->letters[i]->location.y,
			currentGreeting->letters[i]->location.z);

		Vector target(currentGreeting->letters[i + 1]->location.x,
			currentGreeting->letters[i + 1]->location.y,
			currentGreeting->letters[i + 1]->location.z);

		Vector direction = target - location;

		direction = direction.Normalize() * 0.4f;

		lineVertices[i * 2].x = currentGreeting->letters[i]->location.x + direction.x;
		lineVertices[i * 2].y = currentGreeting->letters[i]->location.y + direction.y;
		lineVertices[i * 2].z = currentGreeting->letters[i]->location.z + direction.z;
		lineVertices[i * 2].diffuse = GetColor(timer, i);

		lineVertices[i * 2 + 1].x = currentGreeting->letters[i + 1]->location.x - direction.x;
		lineVertices[i * 2 + 1].y = currentGreeting->letters[i + 1]->location.y - direction.y;
		lineVertices[i * 2 + 1].z = currentGreeting->letters[i + 1]->location.z - direction.z;
		lineVertices[i * 2 + 1].diffuse = GetColor(timer, i + 1);
	}

	// update vertex buffers
	vb->Update(LettersVertices);
	lineVB->Update(lineVertices);

	// some render states
	pyramid->SetAmbientLight(0xffffff);
	pyramid->SetFogNone();
	pyramid->SetD3DLighting(false);
	pyramid->SetWriteZBufferEnable(false);

	// enable bloom
	pyramid->SetRenderTarget(renderChain->GetOriginal());
	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	pyramid->BeginScene();

	// render letters
	pyramid->SetTexture(textureLoader->GetTexture("letters"));
	pyramid->SetTransparency(BLEND_ADD);

	pyramid->SetVertexStream(vb, 0);

	for (int i = 0; i < NR_LETTERS; i++)
	{
		pyramid->DrawPrimitiveStrip(i * 4, 2);
	}

	// render cirkel sprites
	pyramid->SetPointSpriteEnable(true);

	spriteList->Render();

	pyramid->SetPointSpriteEnable(false);

	pyramid->EndScene();

	// perform bloom
	pyramid->ResetRenderTarget();

	postProcessor->psBrightPass->SetLuminance(0.020f);
	postProcessor->psBloom->SetBloomScale(1.0f + sin(backupTimer / 1000.f) * 0.2f);
	postProcessor->chainGlow01->Render();

	pyramid->SetTexture(renderChain->GetSource(), 0);
	drawer2D->BeginScene(BLEND_ADD);
	drawer2D->DrawFullscreen();
	drawer2D->EndScene();

	// render lines
	pyramid->BeginScene();

	pyramid->SetTexture(NULL, 0);
	
	pyramid->SetVertexStream(lineVB, 0);
	pyramid->SetTransparency(BLEND_ADD);

	pyramid->SetD3DLighting(false);

	for (int i = 0; i < currentGreeting->lettersSize - 1; i++)
	{
		pyramid->DrawLineStrip(i * 2, 1);
	}

	pyramid->EndScene();

	// reset some renderstates for whatever comes next
	pyramid->SetD3DLighting(true);
	pyramid->SetWriteZBufferEnable(true);
	pyramid->SetD3DLighting(true);

	effect22->Do(backupTimer - 36500.f, pos, row);


}

void Effect06::Destroy() 
{
	// clean up
	scene->Destroy();

	delete scene;
}