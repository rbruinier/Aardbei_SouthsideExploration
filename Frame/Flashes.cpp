/*
	
	Southside Variations - Flashes

	Description:

*/

#include "Main.h"

#include "Flashes.h"

void WhiteFlash::Init()
{
	doResetOnPlay = true;
}

void WhiteFlash::Do(float timer, int pos, int row) 
{
	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_ALPHA);

	int alpha = 255 - timer * 0.3f;

	if (alpha < 0) alpha = 0;

	DWORD color = ((DWORD)alpha << 24) | 0xffffff;

	drawer2D->DrawFullscreen(color, color, color, color);
	
	drawer2D->EndScene();
}

void BlackFade::Init()
{
	doResetOnPlay = true;
}

void BlackFade::Do(float timer, int pos, int row) 
{
	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_ALPHA);

	int alpha = timer * 0.15f;

	if (alpha > 255) alpha = 255;

	DWORD color = ((DWORD)alpha << 24) | 0x000000;

	drawer2D->DrawFullscreen(color, color, color, color);
	
	drawer2D->EndScene();
}