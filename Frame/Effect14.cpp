/*
	
	Southside Variations - Effect14

	Description:

	The aardbei logo, build of some moving 2D sprites

*/

#include "Main.h"

#include "Effect14.h"

#pragma pack(1)

struct Logo01Sprite
{
	float x, y;
	float w, h;
};

#define LOGO01_DISTANCE1  0
#define LOGO01_DISTANCE2 18
#define LOGO01_DISTANCE3 50

#define LOGO01_LETTER_DISTANCE 75

#define LOGO01_LETTER_X 160

#define LOGO01_LETTER1_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 0)
#define LOGO01_LETTER2_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 1)
#define LOGO01_LETTER3_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 2)
#define LOGO01_LETTER4_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 3)
#define LOGO01_LETTER5_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 4)
#define LOGO01_LETTER6_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 5)
#define LOGO01_LETTER7_X LOGO01_LETTER_X + (LOGO01_LETTER_DISTANCE * 6)

#define LOGO01_LETTER_Y 250

#define LOGO01_HEIGHT1  0 // top
#define LOGO01_HEIGHT2 43 // middle bar
#define LOGO01_HEIGHT3 85 // bottom bar
#define LOGO01_HEIGHT4 17 // sub vertical bar 1
#define LOGO01_HEIGHT5 60 // sub vertical bar 2

#define LOGO01_BAR_HEIGHT1 100
#define LOGO01_BAR_HEIGHT2  15
#define LOGO01_BAR_HEIGHT3  23
#define LOGO01_BAR_HEIGHT4  40
#define LOGO01_BAR_HEIGHT5  66
#define LOGO01_BAR_HEIGHT6  20
#define LOGO01_BAR_HEIGHT7  83

Logo01Sprite logo01SpriteList[] =
{
	// A 00 .. 03
	{LOGO01_LETTER1_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER1_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER1_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER1_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT2, 29, LOGO01_BAR_HEIGHT2},

	// A 04 .. 07
	{LOGO01_LETTER2_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER2_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER2_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER2_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT2, 29, LOGO01_BAR_HEIGHT2},

	// R 08 .. 12
	{LOGO01_LETTER3_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER3_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT4, 15, LOGO01_BAR_HEIGHT3},
	{LOGO01_LETTER3_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT5, 15, LOGO01_BAR_HEIGHT4},
	{LOGO01_LETTER3_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER3_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT2, 29, LOGO01_BAR_HEIGHT2},

	// D 13 .. 16
	{LOGO01_LETTER4_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER4_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT4, 15, LOGO01_BAR_HEIGHT5},
	{LOGO01_LETTER4_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER4_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT3, 29, LOGO01_BAR_HEIGHT2},

	// B 17 .. 22
	{LOGO01_LETTER5_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER5_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT4, 15, LOGO01_BAR_HEIGHT3},
	{LOGO01_LETTER5_X + LOGO01_DISTANCE3, LOGO01_LETTER_Y + LOGO01_HEIGHT5, 15, LOGO01_BAR_HEIGHT3},

	{LOGO01_LETTER5_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER5_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT2, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER5_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT3, 29, LOGO01_BAR_HEIGHT2},

	// E 23 .. 26
	{LOGO01_LETTER6_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT1},
	{LOGO01_LETTER6_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 47, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER6_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT2, 29, LOGO01_BAR_HEIGHT2},
	{LOGO01_LETTER6_X + LOGO01_DISTANCE2, LOGO01_LETTER_Y + LOGO01_HEIGHT3, 47, LOGO01_BAR_HEIGHT2},

	// I 27 .. 28
	{LOGO01_LETTER7_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT4, 15, LOGO01_BAR_HEIGHT7},
	{LOGO01_LETTER7_X + LOGO01_DISTANCE1, LOGO01_LETTER_Y + LOGO01_HEIGHT1, 15, LOGO01_BAR_HEIGHT2}
};

Logo01Sprite* logo01SpriteListMoved;

int logo01Group01[] = 
{
	3, 7, 12, 21, 25
};

int logo01Group02[] =
{
	0, 4, 8, 13, 17, 23
};

int logo01Group03[] =
{
	16, 22, 26
};

int logo01Group04[] =
{
	1, 5, 9, 10, 14, 18, 19, 27
};

int logo01Group05[] =
{
	2, 6, 11, 15, 20, 24
};

void Effect14::Init() 
{
	int nrSprites = sizeof(logo01SpriteList) / (sizeof(float) * 4);

	logo01SpriteListMoved = new Logo01Sprite[nrSprites];

	for (int i = 0; i < nrSprites; i++)
	{
		logo01SpriteListMoved[i] = logo01SpriteList[i];

		logo01SpriteListMoved[i].x += 800;
	}

	tempTimer[30] = -2000;
}

void Effect14::Receive(DWORD message, float timer, int pos, int row)
{
	if (message != 30)
	{
		status = message;
	}

	if (message < 50)
	{
		tempTimer[message] = timer;
	}
}

void Effect14::Do(float timer, int pos, int row) 
{
	int nrSprites = sizeof(logo01SpriteList) / (sizeof(float) * 4);

	float speed = 0.2f;

	// group 01
	int xAdd = 0, yAdd = 0;

	if (status >= 0)
	{
		xAdd = 650 - (timer * speed);

		if (xAdd < 0) xAdd = 0;

		yAdd = -43;

		for (int i = 0; i < (sizeof(logo01Group01) / 4); i++)
		{
			int index = logo01Group01[i];

			logo01SpriteListMoved[index].x = logo01SpriteList[index].x + xAdd;
			logo01SpriteListMoved[index].y = logo01SpriteList[index].y + yAdd;
		}
	}

	if (status >= 1)
	{
		yAdd = -350 + ((timer - tempTimer[1]) * speed);

		if (yAdd > 0) yAdd = 0;

		for (int i = 0; i < (sizeof(logo01Group02) / 4); i++)
		{
			int index = logo01Group02[i];
			logo01SpriteListMoved[index].x = logo01SpriteList[index].x;
			logo01SpriteListMoved[index].y = logo01SpriteList[index].y + yAdd;
		}
	}

	if (status >= 2)
	{
		xAdd = 400 - ((timer - tempTimer[2]) * speed);

		if (xAdd < 0) xAdd = 0;

		for (int i = 0; i < (sizeof(logo01Group03) / 4); i++)
		{
			int index = logo01Group03[i];

			logo01SpriteListMoved[index].x = logo01SpriteList[index].x + xAdd;
		}
	}

	if (status >= 3)
	{
		yAdd = 350 +- ((timer - tempTimer[3]) * speed);

		if (yAdd < 0) yAdd = 0;

		for (int i = 0; i < (sizeof(logo01Group04) / 4); i++)
		{
			int index = logo01Group04[i];
			logo01SpriteListMoved[index].x = logo01SpriteList[index].x;
			logo01SpriteListMoved[index].y = logo01SpriteList[index].y + yAdd;
		}
	}

	if (status >= 4)
	{
		yAdd = -43 + ((timer - tempTimer[4]) * speed * 0.5f);

		if (yAdd > 0) yAdd = 0;

		for (int i = 0; i < (sizeof(logo01Group01) / 4); i++)
		{
			int index = logo01Group01[i];
			
			logo01SpriteListMoved[index].y = logo01SpriteList[index].y + yAdd;
		}
	}

	if (status >= 5)
	{
		xAdd = -650 + ((timer - tempTimer[5]) * speed);

		if (xAdd > 0) xAdd = 0;

		for (int i = 0; i < (sizeof(logo01Group05) / 4); i++)
		{
			int index = logo01Group05[i];

			logo01SpriteListMoved[index].x = logo01SpriteList[index].x + xAdd;
		}
	}

	pyramid->SetTexture(NULL, 0);

	drawer2D->BeginScene(BLEND_NONE);

	int color = 0x000000;

	if (status == 10)
	{
		color = MixColor((timer - tempTimer[10]) * 0.001f, color, 0xffffff);
	}

	color = MixColor((timer - tempTimer[30]) * 0.001f, 0xA0A0A0, color);

	for (int i = 0; i < nrSprites; i++)
	{
		Logo01Sprite* sprite = &logo01SpriteListMoved[i];

		drawer2D->Draw(sprite->x, sprite->y, color,
			sprite->x + sprite->w, sprite->y, color,
			sprite->x, sprite->y + sprite->h, color,
			sprite->x + sprite->w, sprite->y + sprite->h, color);
	}

	// draw the dot
	if (status >= 6)
	{
		float x1 = LOGO01_LETTER7_X;
		float y1 = LOGO01_LETTER_Y;
		float x2 = x1 + 15;
		float y2 = y1 + 15;

		DWORD color = MixColor((timer - tempTimer[6]) * 0.0003f, 0xffffff, 0x000000);

		if (status == 10)
		{
			color = MixColor((timer - tempTimer[10]) * 0.001f, color, 0xffffff);
		}

		color = MixColor((timer - tempTimer[30]) * 0.001f, 0xA0A0A0, color);

		drawer2D->Draw(x1, y1, color,
			x2, y1, color,
			x1, y2, color,
			x2, y2, color);
	}

	drawer2D->EndScene();
}

void Effect14::Destroy() 
{
	delete [] logo01SpriteListMoved;
}