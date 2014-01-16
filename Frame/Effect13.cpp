/*
	
	Southside Variations - Effect13

	Description:

	Transition:

	part 5: credits (white lines and purple background)

	status 0: incoming white lines
	status 1: scrolling purple background from the top
	status 2: scrolling lines from the left
	status 3: 

*/

#include "Main.h"

#include "Effect13.h"

void Effect13::Do(float timer, int pos, int row) 
{
	//if (timer >  2000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  4000 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  6000 && status == 2) Receive(3, timer, 0, 0);

	float fadeOut = 0;

	if (status == 3)
	{
		fadeOut = (timer - tempTimer[3]) * 0.00045f;
	}

	background = 0;

	const DWORD color1 = 0x91853B;
	const DWORD color2 = 0xCBB330;

	float x1 = 10;
	float y1 = 20;

	float x2 = 800 - x1;
	float y2 = 600 - y1;

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	float xOffset = (x2 - x1) * timer * 0.0005f;
	float yOffset = (y2 - y1) * timer * 0.0005f;

	if (xOffset > (x2 - x1)) xOffset = x2 - x1;
	if (yOffset > (y2 - y1)) yOffset = y2 - y1;

	if (status >= 1)
	{
		DWORD color = MixColor(fadeOut, color1, 0x000000);

		float yy = y1 + (timer - tempTimer[1]) * 0.3f;

		if (yy > y2) yy = y2;

		drawer2D->Draw(x1, y1, color,
			x2, y1, color, 
			x1, yy, color,
			x2, yy, color);
	}

	if (status >= 2)
	{
		DWORD color = MixColor(fadeOut, color2, 0x000000);

		for (int i = 0; i < 139; i++)
		{
			float yy = y1 + (i * 4) + 4;

			float xx = x1 + (timer - tempTimer[2]) * 0.3f;

			if (xx > x2) xx = x2;

			drawer2D->Draw(x1, yy, color,
				xx, yy, color, 
				x1, yy + 1, color,
				xx, yy + 1, color);
		}
	}

	DWORD color = MixColor(fadeOut, 0xffffff, 0x000000);

	drawer2D->Draw(x1, y1, color,
				   x1 + xOffset, y1, color,
				   x1, y1 + 1, color,
				   x1 + xOffset, y1 + 1, color);

	drawer2D->Draw( x2 - xOffset, y2 - 1, color,
					x2, y2 - 1, color,
					x2 - xOffset, y2, color,
					x2, y2, color);

	drawer2D->Draw(x1, y1, color,
				   x1 + 1, y1, color,
				   x1, y1 + yOffset, color,
				   x1 + 1, y1 + yOffset, color);

	drawer2D->Draw(x2 - 1, y2 - yOffset, color,
				   x2, y2 - yOffset, color,
				   x2 - 1, y2, color,
				   x2, y2, color);


	
	drawer2D->EndScene();
}