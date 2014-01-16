/*
	
	Southside Variations - Effect12

	Description:

	Transition:

	part 3: bending tube & sperm (two moving bars)

	status 0: two bars coming in from the left (fullscreen)
	status 1: both bars moving up and down
	status 2: both bars moving down and up again
	status 3: the bars move to the right, out of the screen

*/

#include "Main.h"

#include "Effect12.h"

int currentSymbol = -1;

void Effect12::Receive(DWORD message, float timer, int pos, int row)
{
	if (message < 30)
	{
		status = message;

		if (message < 50)
		{
			tempTimer[message] = timer;
		}
	}
	else
	{
		currentSymbol = message - 30;

		tempTimer[30] = timer;
	}


}

void Effect12::Init()
{
	tempTimer[30] = -2000;
}

void Effect12::Do(float timer, int pos, int row) 
{

	//timer += 5000;
	//if (timer >  3000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  7000 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  8000 && status == 2) Receive(3, timer, 0, 0);

	const DWORD color1 = 0x406D42;
	const DWORD color2 = 0x384D39;

	background = 0;

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	float offset = 800;//timer * 0.5f;

	float yOffset = 0;

	if (status == 2 || status == 3)
	{
		yOffset = (timer - tempTimer[2]) * 0.25f;

		if (yOffset > (300 - 48)) // 96
		{
			yOffset = 300 - 48;
		}

		if (status == 3)
		{
			yOffset -= (timer - tempTimer[3]) * 0.25f;

			if (yOffset < 0) yOffset = 0;
		}
	}

	DWORD color = MixColor(timer * 0.00075f, 0xffffff, color2);

	float x1 = 0;
	float x2 = offset;

	if (x2 > 800) x2 = 800;

	float y1 = 0;
	float y2 = 300 - yOffset;

	if (status == 4)
	{
		x1 = (timer - tempTimer[4]) * 0.6f;
	}

	drawer2D->Draw( x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

	y1 = 300 + yOffset;
	y2 = 600;

	drawer2D->Draw( x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

	drawer2D->EndScene();


	// draw symbols

	if (status >= 2)
	{
		switch (currentSymbol)
		{
		case 0:
			pyramid->SetTexture(textureLoader->GetTexture("sign01"), 0);
			break;
		case 1:
			pyramid->SetTexture(textureLoader->GetTexture("sign02"), 0);
			break;
		case 2:
			pyramid->SetTexture(textureLoader->GetTexture("sign03"), 0);
			break;
		case 3:
			pyramid->SetTexture(textureLoader->GetTexture("sign02"), 0);
			break;
		case 4:
			pyramid->SetTexture(textureLoader->GetTexture("sign04"), 0);
			break;
		case 5:
			pyramid->SetTexture(textureLoader->GetTexture("sign05"), 0);
			break;
		case 6:
			pyramid->SetTexture(textureLoader->GetTexture("sign06"), 0);
			break;
		}

		drawer2D->BeginScene(BLEND_ALPHA);

		DWORD color = MixColor(1.f - (timer - tempTimer[30]) * 0.001f, 0x003b913e, 0xFF3b913e, true);

		for (int j = 0; j < 2; j++)
		{
			for (int i = 0; i < 21; i++)
			{
				x1 = 5 + i * 40;
				x2 = x1 + 32;

				y1 =  6 + (j * 554);
				y2 = y1 + 32;

				drawer2D->Draw( x1, y1, color,
								x2, y1, color,
								x1, y2, color,
								x2, y2, color);
			}
		}

		drawer2D->EndScene();


	}

	// draw diagonal lines
	/*if (status >= 2)
	{
		drawer2D->BeginScene(BLEND_ALPHA);

		DWORD alpha = 255 - (timer - tempTimer[30]);

		if (alpha > 255) alpha = 0;

		alpha <<= 24;

		for (int j = 0; j < 2; j++)
		{
			DWORD color10 = color2 | alpha;
			DWORD color20 = MixColor(0.8f, color2, color1) | alpha;

			for (int i = 0; i < 21; i++)
			{
				x1 = 15 + i * 40;
				x2 = x1 - 18;

				y1 =  4 + (j * 554);
				y2 = 24 + (j * 554);

				drawer2D->Draw( x1, y1, color10,
								x1 + 20, y1, color10,
								x2, y2, color20,
								x2 + 20, y2, color20);

				x1 -= 18; x2 -= 18;

				y1 += 20; y2 += 20;

				drawer2D->Draw( x1, y1, color20,
								x1 + 20, y1, color20,
								x2, y2, color10,
								x2 + 20, y2, color10);
			}
		}

		drawer2D->EndScene();
	}*/
}
