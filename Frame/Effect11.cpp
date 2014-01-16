/*
	
	Southside Variations - Effect11

	Description:

	Transition:

	part 1: fake blobs (traingle 2d object on the right)

	status 0: moving the white poly things to the right, showing the purple bars
	status 1: fading the purple bars to black
	status 2: fading black background to white
	status 3: moving the white poly things out of the screen

*/

#include "Main.h"

#include "Effect11.h"

void Effect11::Do(float timer, int pos, int row) 
{
	//if (timer >  4000 && status == 0) Receive(1, timer, 0, 0);
	//if (timer >  7000 && status == 1) Receive(2, timer, 0, 0);
	//if (timer >  7500 && status == 2) Receive(3, timer, 0, 0);

	const DWORD color1 = 0x4D406D;
	const DWORD color2 = 0x3E384D;
	const DWORD color3 = 0x4D406D;
	const DWORD color4 = 0x543B91;
	const DWORD color5 = 0x3E384D; 

	float blocks[19][4] =
	{
		{352,   0, 340,  12},
		{322,  13, 359,  50},
		{340,  51, 379,  89},
		{323,  90, 326,  93},
		{357,  94, 342, 109},
		{355, 110, 342, 123},
		{309, 124, 286, 147},
		{317, 148, 294, 173},
		{240, 174, 236, 178},
		{309, 179, 299, 189},
		{312, 190, 307, 195},
		{279, 196, 284, 201},
		{324, 202, 319, 207},
		{307, 208, 320, 221},
		{325, 222, 331, 227},
		{377, 228, 348, 257},
		{370, 258, 366, 262},
		{325, 263, 338, 276},
		{367, 277, 345, 300}
	};

	float blocks2[3][6] =
	{
		{
			327,  94, 334,
			330,  97, 337
		},
		{
			300,  98, 337,
			304, 102, 341
		},	
		{
			246, 168, 247,
			241, 173, 252
		}
	};

	DWORD barColor[5] =
	{
		color1,
		color2,
		color3,
		color4, 
		color5
	};

	float bars[5][2] =
	{
		{0, 91},
		{91, 124}, 
		{124, 190},
		{190, 223},
		{223, 400}
	};

	background = 0;

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	DWORD color;

	// purple bars
	//for (int i = 0; i < 5; i++)
	//{
	//	color = barColor[i];

	//	if (status == 1)
	//	{
	//		color = MixColor((timer - tempTimer[1]) * 0.0005f, color, 0x000000);
	//	}
	//	else if (status >= 2)
	//	{
	//		color = MixColor((timer - tempTimer[2]) * 0.0005f, 0x000000, 0xffffff);
	//	}

	//	if (color != 0x000000)
	//	{
	//		drawer2D->Draw(  0, bars[i][0] * 2.f, color,
	//					800, bars[i][0] * 2.f, color,
	//				  		0, bars[i][1] * 2.f, color,
	//					800, bars[i][1] * 2.f, color);
	//	}
	//}

	int yOffsetList[] =
	{
		20, -20, 0
	};

	int colorList[] =
	{
		0x3E384D, 0x4D406D, 0xffffff
	};

	for (int j = 0; j < 3; j++)
	{
		color = colorList[j];

		for (int i = 0; i < 19; i++)
		{
			float offset = -800 + timer * 0.3f;

			if (i >= 3 && i <= 13)
			{
				if (i >= 6 && i <= 10)
				{
					if (offset > 130) offset = 130;
				}
				else
				{
					if (offset > 50) offset = 50;
				}
			}
			else
			{
				if (offset > 0) offset = 0;
			}

			if (status == 3)
			{
				offset += (timer - tempTimer[3]) * 0.3f;
			}

			// vertical
			float x1 = blocks[i][0] * 2.f + offset;
			float x2 = blocks[i][2] * 2.f + offset;

			float y1 = blocks[i][1] * 2.f - 1 + yOffsetList[j];
			float y2 = blocks[i][3] * 2.f + 1 + yOffsetList[j];

			drawer2D->Draw( x1, y1, color,
						800, y1, color,
							x2, y2, color,
						800, y2, color);
		}

		for (int i = 0; i < 3; i++)
		{
			float offset = -800 + timer * 0.3f;

			if (i == 2)
			{
				if (offset > 130) offset = 130;
			}
			else
			{
				if (offset > 50) offset = 50;
			}

			if (status == 3)
			{
				offset += (timer - tempTimer[3]) * 0.3f;
			}

			// vertical
			float x1 = blocks2[i][0] * 2.f - 2 + offset;
			float x2 = blocks2[i][2] * 2.f - 2 + offset;
			float x3 = blocks2[i][3] * 2.f - 2 + offset;
			float x4 = blocks2[i][5] * 2.f - 2 + offset;

			float y1 = blocks2[i][1] * 2.f - 1 + yOffsetList[j];
			float y2 = blocks2[i][4] * 2.f + 1 + yOffsetList[j];

			drawer2D->Draw( x1, y1, color,
							x2, y1, color,
							x3, y2, color,
							x4, y2, color);
		}
	}

	drawer2D->EndScene();
}