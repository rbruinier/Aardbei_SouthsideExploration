/*
	
	Southside Variations - Effect16

	Description:

	Transition:

	part 0: 8 blocks, first pattern, before the aardbei logo

	status 0: 
	status 1: 
	status 2: 
	status 3: 

*/

#include "Main.h"

#include "Effect16.h"

int fx16Colors[6] =
{
	0x5c30cb,
	0x309ccb,
	0x30cb35,
	0x9fcb30,
	0xcbb330,
	0xcb4930
};

// 96 - 43 = 106
// 6 white pixels
// 112
// 800 - 112 * 6 / 2 = 64
// 18

void Effect16::Do(float timer, int pos, int row) 
{
	//if (timer >  2000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  4000 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  6000 && status == 2) Receive(3, timer, 0, 0);

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_SUBTRACT);

	int loop = status - 2;

	if (loop > 6) loop = 6;

	for (int i = 0; i < loop; i++)
	{
		int color = 0xffffff - fx16Colors[i];

		if (status == 10)
		{
			color = MixColor((timer - tempTimer[10]) * 0.001f, color, 0x000000);
		}

		float x1 = 64 + i * 112;
		float x2 = x1 + 106;

		float y1 = 250;//247;
		float y2 = y1 + 100;

		drawer2D->Draw(x1, y1, color,
			  		   x2, y1, color, 
					   x1, y2, color,
					   x2, y2, color);
	}

	int color = 0xffffff;

	if (status == 10)
	{
		color = MixColor((timer - tempTimer[10]) * 0.001f, color, 0x000000);
	}

	float x1 = 64 - 18 - 6;
	float x2 = x1 + 18;

	float y1 = 250;
	float y2 = y1 + 100;

	if (status >= 1)
	{
		drawer2D->Draw(x1, y1, color,
			  		   x2, y1, color, 
					   x1, y2, color,
					   x2, y2, color);
	}

	x1 = 64 + 6 * 112;
	x2 = x1 + 18;

	if (status >= 2)
	{
		drawer2D->Draw(x1, y1, color,
				  	   x2, y1, color, 
					   x1, y2, color,
					   x2, y2, color);
	}


	drawer2D->EndScene();
}