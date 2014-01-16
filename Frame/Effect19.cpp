/*
	
	Southside Variations - Effect19

	Description:

	Transition:

	part 1: 6 bars

	status 0: 
	status 1: 
	status 2: 
	status 3: 

*/

#include "Main.h"

#include "Effect19.h"

void Effect19::Do(float timer, int pos, int row) 
{
	float offset = -300.f + timer * 0.7f; 

	if (offset > 600) return;

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	for (int i = 0; i < 3; i++)
	{
		float x1 = (800 / 6.f) * i;
		float x2 = x1 + (800 / 6.f);

		float y1 = offset + ((2 - i) * 150.f);
		float y2 = 600;

		drawer2D->Draw(x1, y1, 0xffffff,
			  		   x2, y1, 0xffffff, 
					   x1, y2, 0xffffff,
					   x2, y2, 0xffffff);
	}

	for (int i = 0; i < 3; i++)
	{
		float x1 = 400.f + (800 / 6.f) * i;
		float x2 = x1 + (800 / 6.f);

		float y1 = 0;;
		float y2 = 600 - offset - (i * 150.f);

		drawer2D->Draw(x1, y1, 0xffffff,
			  		   x2, y1, 0xffffff, 
					   x1, y2, 0xffffff,
					   x2, y2, 0xffffff);
	}

	drawer2D->EndScene();
}