/*
	
	Southside Variations - Effect10

	Description:

	Transition:

	part 2: exploding ball (room)

	status 0: fullscreen fade from white to blue
	status 1: drawing of 4 bars
	status 2: fading bars to black
	status 3: incoming sidebars
	status 4: back wall moving
	status 5: outer walls moving

*/

#include "Main.h"

#include "Effect10.h"

void Effect10::Do(float timer, int pos, int row) 
{


	//if (timer >  100 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  200 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  300 && status == 2) Receive(3, timer, 0, 0);
	//if (timer >	 1000 && status == 3) Receive(4, timer, 0, 0);
	//if (timer >	 2000 && status == 4) Receive(5, timer, 0, 0);

	const DWORD color1 = 0xFF3B7691; // light blue back ground
	const DWORD color2 = 0xFF405F6D; // darker blue wall

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_ALPHA);

	DWORD color = 0xffffffff;

	if (status >= 0)
	{
		color = MixColor(timer * 0.0005f, color, color1, true);

		//drawer2D->DrawFullscreen(color, color, color, color);

		pyramid->SetTexture(NULL, 0);


		float sizeOfHole = 0.f;

		if (status == 4)
		{
			sizeOfHole = (timer - tempTimer[4]) * 0.15f;

			if (sizeOfHole > 80.f) sizeOfHole = 80.f;
		}

		if (status == 5)
		{
			sizeOfHole = 80.f - (timer - tempTimer[4]) * 0.15f;

			if (sizeOfHole < 0.f) sizeOfHole = 0.f;
		}

		float x1 = 400 - sizeOfHole;
		float x2 = 400 + sizeOfHole;

		float y1 = 300 - sizeOfHole;
		float y2 = 300 + sizeOfHole;

		// top & bottom
		drawer2D->Draw(0, 0, color, 800, 0, color, 0, y1, color, 800, y1, color);
		drawer2D->Draw(0, y2, color, 800, y2, color, 0, 600, color, 800, 600, color);

		// left & right
		drawer2D->Draw(0, y1, color, x1, y1, color, 0, y2, color, x1, y2, color);
		drawer2D->Draw(x2, y1, color, 800, y1, color, x2, y2, color, 800, y2, color);

		if (sizeOfHole > 0)
		{
			pyramid->SetTexture(textureLoader->GetTexture("hole"), 0);

			drawer2D->Draw(x1, y1, x2, y1, x1, y2, x2, y2);
		}
	}

	pyramid->SetTexture(NULL, 0);

	drawer2D->EndScene();

	drawer2D->BeginScene(BLEND_NONE);

	if (status >= 1)
	{
		color = 0xffffff;

		if (status >= 2)
		{
			color = MixColor((timer - tempTimer[2]) * 0.0005f, 0xffffff, 0x000000);
		}

		float moveTimer = (timer - tempTimer[1]) * 0.8f;

		// vertical
		float x1 = 0;
		float x2 = moveTimer;

		float y1 = 0;
		float y2 = 96;

		if (x2 > 800) x2 = 800;

		drawer2D->Draw(x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

		if (moveTimer >= 800)
		{
			moveTimer -= 800;

			x1 = 800 - 96;
			x2 = 800;

			y1 = 96;
			y2 = y1 + moveTimer;

			if (y2 > 600) y2 = 600;

			drawer2D->Draw(x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

			if (moveTimer >= 600 - 96)
			{
				moveTimer -= 600 - 96;

				x1 = 800 - 96 - moveTimer;;
				x2 = 800;

				y1 = 600 - 96;
				y2 = 600;

				if (x1 < 0) x1 = 0;

				drawer2D->Draw(x1, y1, color,
					x2, y1, color,
					x1, y2, color,
					x2, y2, color);

				if (moveTimer >= 800 - 96)
				{
					moveTimer -= 800 - 96;

					x1 =  0;
					x2 = 96;

					y1 = 600 - 96 - moveTimer;
					y2 = 600 - 96;

					if (y1 < 96) y1 = 96;

					drawer2D->Draw(x1, y1, color,
						x2, y1, color,
						x1, y2, color,
						x2, y2, color);
				}
			}
		}
	}

	if (status >= 3)
	{
		float moveTimer = (timer - tempTimer[3]) * 0.1f;

		//if (status >= 5)
		//{
		//	moveTimer = (960 - (timer - tempTimer[5])) * 0.1f;
		//}

		float x1 = -96 + moveTimer;

		if (x1 >= 0) x1 = 0;

		float x2 = x1 + 96;

		float y1 = 96;
		float y2 = 600 - 96;

		if (x2 > 800) x2 = 800;

		drawer2D->Draw(x1,   0, color2,
					   x2,  y1, color2,
					   x1, 600, color2,
					   x2,  y2, color2);

		x2 = 896 - moveTimer;

		if (x2 <= 800) x2 = 800;

		x1 = x2 - 96;

		drawer2D->Draw(x1,  y1, color2,
					   x2,  0, color2,
					   x1, y2, color2,
					   x2,  600, color2);

		//x2 = x1 + ((x2 - x1) * 0.5f);

		//float holeSize = 40.f;

		//float perspective = 2.0f;

		//float ly1 = y1;
		//float ly2 = y2;

		//float ry1 = y1 + ((0 - y1) * 0.5f);
		//float ry2 = y2 + ((600 - y2) * 0.5f);

		//float lx = x1;
		//float rx = x1 + ((x2 - x1) * 0.5f);

		/*float lmy1 = 300;
		float lmy2 = lmy1;

		lmy1 -= holeSize;
		lmy2 += holeSize;

		float rmy1 = 300;
		float rmy2 = rmy1;

		rmy1 -= holeSize * perspective;
		rmy2 += holeSize * perspective;

		drawer2D->Draw(lx, ly1, color2,
					   rx, ry1, color2,
					   lx, lmy1, color2,
					   rx, rmy1, color2);

		drawer2D->Draw(lx, lmy2, color2,
					   rx, rmy2, color2,
					   lx, ly2, color2,
					   rx, ry2, color2);

		float mx = rx - holeSize;

		drawer2D->Draw(lx, lmy1, color2,
					   mx, rmy1, color2,
					   lx, lmy2, color2,
					   mx, rmy2, color2);

		if (holeSize > 0)
		{
			pyramid->SetTexture(textureLoader->GetTexture("hole"), 0);

			drawer2D->Draw(mx, lmy1, 0, 0, 
				rx, rmy1, 0.5f, 0, 
				mx, lmy2, 0, 1.0f,
				rx, rmy2, 0.5f, 1.f);
		}*/


		//drawer2D->Draw(lx, ly1, color2,
		//			   rx, ry1, color2,
		//			   lx, ly2, color2,
		//			   rx, ry2, color2);
	}

	drawer2D->EndScene();
}
