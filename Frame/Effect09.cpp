/*
	
	Southside Variations - Effect09

	Description:

	Transition:

	part 4: cubes (frame, like a painting)

	status 0: building the inner frame
	status 1: 
	status 2: 
	status 3: 

*/

#include "Main.h"

#include "Effect09.h"

void Effect09::Do(float timer, int pos, int row) 
{
	//if (timer >  3000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  7000 && status == 1) Receive(2, timer, 0, 0);

	const DWORD color1 = 0x78913B;
	const DWORD color2 = 0x606D40;

	const DWORD width1 = 18;

	// outer border first
	float loc1[5][4] =
	{
		{  0,   0, 368,  18},
		{428,   0, 800,  18},
		{  0,   0,  18, 600},
		{782,   0, 800, 600},
		{  0, 582, 800, 600}
	};

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	if (status >= 1)
	{
		DWORD color = MixColor((timer - tempTimer[1]) * 0.0005f, 0x000000, color2);

		if (status == 2)
		{
			color = MixColor((timer - tempTimer[2]) * 0.0005f, color2, 0x000000);
		}

		for (int i = 0; i < 5; i++)
		{
			float y1 = loc1[i][1], y2 = loc1[i][3];
			float x1 = loc1[i][0], x2 = loc1[i][2];

			drawer2D->Draw(x1, y1, color,
						x2, y1, color,
						x1, y2, color,
						x2, y2, color);
		}
	}


	DWORD color = color1;

	if (status == 2)
	{
		color = MixColor((timer - tempTimer[2]) * 0.0005f, color1, 0x000000);
	}

	timer *= 0.4f;

	// 2 upper vertical
	float x1 = 368;
	float x2 = x1 + width1;

	float y1 = 0;
	float y2 = timer;

	if (y2 > width1 * 2) y2 = width1 * 2;

	drawer2D->Draw(x1, y1, color,
				   x2, y1, color,
				   x1, y2, color,
				   x2, y2, color);

	x2 = 428;
	x1 = x2 - width1;

	drawer2D->Draw(x1, y1, color,
				   x2, y1, color,
				   x1, y2, color,
				   x2, y2, color);

	if (timer >= 36)
	{
		timer -= 36;

		// horizontal
		x2 = 368;
		x1 = x2 - timer;

		if (x1 < width1) x1 = width1;

		y1 = width1;
		y2 = y1 + width1;

		drawer2D->Draw(x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

		
		x1 = 428;
		x2 = x1 + timer;

		if (x2 > 800 - width1) x2 = 800 - width1;

		y1 = width1;
		y2 = y1 + width1;

		drawer2D->Draw(x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

		if (timer >= (368 - width1))
		{
			timer -= (368 - width1);

			// vertical
			x1 = width1;
			x2 = x1 + width1;

			y1 = width1 * 2;
			y2 = y1 + timer;

			if (y2 > 600 - width1) y2 = 600 - width1;

			drawer2D->Draw(x1, y1, color,
						x2, y1, color,
						x1, y2, color,
						x2, y2, color);

			x1 = 800 - width1 * 2;
			x2 = x1 + width1;

			drawer2D->Draw(x1, y1, color,
						x2, y1, color,
						x1, y2, color,
						x2, y2, color);

			if (timer >= 600 - y1 - width1)
			{
				timer -= 600 - y1 - width1;

				// horizontal
				x1 = width1 * 2;
				x2 = x1 + timer;

				if (x2 > 400) x2 = 400;

				y1 = 600 - width1 * 2;
				y2 = y1 + width1;

				drawer2D->Draw(x1, y1, color,
							x2, y1, color,
							x1, y2, color,
							x2, y2, color);

				x2 = 800 - width1 * 2;
				x1 = x2 - timer;

				if (x1 < 400) x1 = 400;

				drawer2D->Draw(x1, y1, color,
							x2, y1, color,
							x1, y2, color,
							x2, y2, color);
			}
		}
	}

	drawer2D->EndScene();
}