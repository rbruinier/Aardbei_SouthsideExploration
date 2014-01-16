/*
	
	Southside Variations - Effect08

	Description:

	The southside logo

*/

#include "Main.h"

#include "Effect08.h"

int southside_s[] = 
{
	0, 1, 1,
	1, 0, 0,
	1, 1, 0,
	0, 1, 1,
	0, 1, 1,
	1, 1, 0
};

int southside_o[] = 
{
	0, 1, 0,
	1, 0, 1,
	1, 0, 1,
	1, 1, 1,
	1, 1, 1,
	0, 1, 0
};

int southside_u[] = 
{
	1, 0, 1,
	1, 0, 1,
	1, 0, 1,
	1, 1, 1,
	1, 1, 1,
	0, 1, 0
};

int southside_t[] = 
{
	1, 1, 1,
	0, 1, 0,
	0, 1, 0,
	0, 1, 1,
	0, 1, 1,
	0, 0, 1
};

int southside_h[] = 
{
	1, 0, 1,
	1, 0, 1,
	1, 1, 1,
	1, 1, 1,
	1, 0, 1,
	1, 0, 1
};

int southside_i[] = 
{
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 1,
	0, 1, 1,
	0, 0, 1
};

int southside_d[] = 
{
	1, 1, 0,
	1, 0, 1,
	1, 0, 1,
	1, 1, 1,
	1, 1, 1,
	1, 1, 0
};

int southside_e[] = 
{
	0, 1, 1,
	1, 0, 0,
	1, 1, 1,
	1, 0, 0,
	1, 1, 0,
	0, 1, 1
};

struct SouthSideLetter
{
	Vector location;
	float startTimer;
	Vector dots[18];
	int nrDots;

	SouthSideLetter()
	{
		startTimer = 0;
		nrDots = 0;
	}
};

SouthSideLetter southsideLetters[9];

void Effect08::Init() 
{
	int index = 0;

	const float horX = 20.f;
	const float horY = 20.f;

	int locX = 0;

	// s
	SouthSideLetter* l = &southsideLetters[0];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 0;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_s[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_s[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}

	// o
	locX += 4 * 20;
	l = &southsideLetters[1];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 2000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_o[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_o[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}

	// u
	locX += 4 * 20;
	l = &southsideLetters[2];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 4000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_u[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_u[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
	// t
	locX += 4 * 20;
	l = &southsideLetters[3];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 6000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_t[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_t[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
	// h
	locX += 4 * 20;
	l = &southsideLetters[4];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 8000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_h[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_h[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
	// s
	locX += 4 * 20;
	l = &southsideLetters[5];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 7000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_s[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_s[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
	// i
	locX += 3 * 20;
	l = &southsideLetters[6];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 5000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_i[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_i[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
	// d
	locX += 4 * 20;
	l = &southsideLetters[7];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 3000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_d[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_d[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
	// e
	locX += 4 * 20;
	l = &southsideLetters[8];
	l->location.x = locX; l->location.y = 0;
	l->startTimer = 1000;
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 3; x++)
			if (y & 1) {
				if (southside_e[(y * 3) + x]) {l->dots[l->nrDots].x = x * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			} else {
				if (southside_e[(y * 3) + 2 - x]) {l->dots[l->nrDots].x = (2 - x) * horX; l->dots[l->nrDots].y = y * horY; l->nrDots++; }
			}
}

void Effect08::Do(float timer, int pos, int row) 
{
	timer *= 2.0f;
	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_SUBTRACT);

	const float ww = 14;
	const float hh = 14;

	DWORD color = 0xffffff;

	if (status == 10)
	{
		color = MixColor(((timer * 0.5f) - tempTimer[10]) * 0.001f, color, 0x000000);
	}

	for (int j = 0; j < 9; j++)
	{
		SouthSideLetter* l = &southsideLetters[j];

		for (int i = 0; i < l->nrDots; i++)
		{
			float t = timer - (i * 200) - l->startTimer;

			float x = l->dots[i].x + l->location.x +  63.f;
			float y = l->dots[i].y + l->location.y + 213.f;

			float w = (t * 0.02f);
			float h = (t * 0.02f);

			if (w < 0) w = 0; if (w > 14) w = ww;
			if (h < 0) h = 0; if (h > 14) h = hh;

			w /= 2.f;
			h /= 2.f;

			drawer2D->Draw(x - w, y - h, color, 
				           x + w, y - h, color, 
						   x - w, y + h, color, 
						   x + w, y + h, color);
		}
	}

	if (status >= 1)
	{
		pyramid->SetTexture(textureLoader->GetTexture("exploration"));

		float x = 52, y = 340;

		color = MixColor(((timer * 0.5f) - tempTimer[1]) * 0.0002f, 0x000000, 0xffffff);

		if (status == 10)
		{
			color = MixColor(((timer * 0.5f) - tempTimer[10]) * 0.001f, color, 0x000000);
		}

		drawer2D->Draw(x, y, color, x + 1024, y, color, x, y + 128, color, x + 1024, y + 128, color);
	}


	drawer2D->EndScene();
}

void Effect08::Destroy() 
{
}