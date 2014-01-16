/*
	
	Southside Variations - Effect13

	Description:

	Transition:

	part 6: greetings (squares)

	status 0: 
	status 1: 
	status 2: 
	status 3: 

*/

#include "Main.h"

#include "Effect15.h"

int fx15Colors[42];

float fx15Durations[42];
float fx15Phases[42];

void Effect15::Init() 
{
	for (int i = 0; i < 42; i++)
	{
		fx15Colors[i] = (int)MixColor((rand()%1000) / 1000.f, 0x83301F , 0x441910);

		fx15Durations[i] = (rand() % 500) + 800.f;
		fx15Phases[i] = (rand() % 6000) / 1000.f;
	}
}

void Effect15::Do(float timer, int pos, int row) 
{
	//if (timer >  2000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  4000 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  6000 && status == 2) Receive(3, timer, 0, 0);

	background = 0;

	const DWORD color1 = 0x312221;


	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	int color = MixColor(timer / 2000.f, 0x000000, color1);

	if (status == 1)
	{
		color = MixColor((timer - tempTimer[1]) / 2000.f, color1, 0x000000);
	}

	for (int i = 0; i < 7; i++)
	{
		float x1 = 0;
		float x2 = 800;

		float y1 = i * 98;
		float y2 = y1 + 12;

		drawer2D->Draw(x1, y1, color,
			  		   x2, y1, color, 
					   x1, y2, color,
					   x2, y2, color);
	}

	for (int i = 0; i < 8; i++)
	{
		float x1 = i * 112.571428f;
		float x2 = x1 + 12;

		float y1 = 0;
		float y2 = 600;

		drawer2D->Draw(x1, y1, color,
			  		   x2, y1, color, 
					   x1, y2, color,
					   x2, y2, color);
	}


	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			//color = MixColor(timer / 2000.f, 0x000000, fx15Colors[j * 7 + i]);

			color = MixColor(sin((timer / fx15Durations[j * 7 + i]) + fx15Phases[j * 7 + i]) * 0.5f + 0.5f, 0x5b2115 , 0x33130c);

			color = MixColor(timer / 2000.f, 0x000000, color);

			if (status == 1)
			{
				color = MixColor((timer - tempTimer[1]) / 2000.f, color, 0x000000);
			}

			float x1 = 12.f + i * 112.571428f;
			float x2 = x1 + 112.571428f - 12.f;

			float y1 = 12.f + j * 98;
			float y2 = y1 + + 98 - 12.f;

			drawer2D->Draw(x1, y1, color,
			  			   x2, y1, color, 
						   x1, y2, color,
						   x2, y2, color);
		}
	}

	drawer2D->EndScene();
}