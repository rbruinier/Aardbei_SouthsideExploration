#define PLAY_SCRIPT
//#define FMOD_PLAY 0

#include "Main.h"
#include "WindowInit.h"
#include "Script.h"
#include "FMod.h"
#include "Music.h"
#include "Textures.h"
#include "DemoScript.h"

#include "ClearBackBuffer.h"

//#include "Effect01.h"
#include "Effect02.h"
#include "Effect03.h"
#include "Effect04.h"
#include "Effect05.h"
#include "Effect06.h"
#include "Effect07.h"
#include "Effect08.h"
#include "Effect09.h"
#include "Effect10.h"
#include "Effect11.h"
#include "Effect12.h"
#include "Effect13.h"
#include "Effect14.h"
#include "Effect15.h"
#include "Effect16.h"
#include "Effect17.h"
//#include "Effect18.h"
#include "Effect19.h"
#include "Effect20.h"
#include "Effect21.h"
#include "Effect22.h"

#include "Flashes.h"

Pyramid* pyramid = NULL;

TextureLoader* textureLoader;
FontSystem* fontSystem;
Drawer2D* drawer2D;
RenderChain* renderChain;
PostProcessor* postProcessor;

//Effect* effect01;
Effect* effect02;
Effect* effect03;
Effect* effect04;
Effect* effect05;
Effect* effect06;
Effect* effect07;
Effect* effect08;
Effect* effect09;
Effect* effect10;
Effect* effect11;
Effect* effect12;
Effect* effect13;
Effect* effect14;
Effect* effect15;
Effect* effect16;
Effect* effect17;
//Effect* effect18;
Effect* effect19;
Effect* effect20;
Effect* effect21;
Effect* effect22;

Effect* whiteFlash;
Effect* blackFade;

Effect* clearBackBuffer;


bool INTRO_OVER = false;

#define CLEARBACKBUFFER	 10

#define FX_GRIDBLOB    20
#define FX_TUBE        21
#define FX_BALL        22
#define FX_CUBES       23
#define FX_GREETINGS   24
#define FX_COLORBLOCKS 25
#define FX_PURPLELINES 26
#define FX_CREDITS     27
#define FX_CUBE		   28
#define FX_WOBSPERM	   29
#define FX_GRTSPERM	   30

#define TRANSITION_PART1 50
#define TRANSITION_PART2 51
#define TRANSITION_PART3 52
#define TRANSITION_PART4 53
#define TRANSITION_PART5 54
#define TRANSITION_PART6 55

#define LOGO_AARDBEI   60
#define LOGO_SOUTHSIDE 61

#define FLASH_WHITE 80
#define FADE_BLACK 82

DWORD background = 0x000000;

#define APPLICATION_CLASSNAME     "aardbei machine"
#define APPLICATION_WINDOWCAPTION "southside exploration"

#define APPLICATION_WIDTH	800
#define APPLICATION_HEIGHT  600

#ifdef PLAY_SCRIPT
#ifndef FMOD_PLAY
#define FMOD_PLAY 0
#endif
#endif

extern DWORD* loadATSFromMem(byte* atsMem, int &width, int &height);

int fps = 0;
float oldTimer = 0;
int frames = 0;

void LoadTextures()
{
	textureLoader->Load(explorat_ats, "exploration", false, 0);

	textureLoader->Load(wobbler_ats, "wobbler", true, 0);

	textureLoader->Load(rasmus_ats, "rasmus", true, 0);

	textureLoader->Load(sperm_ats, "sperm", true, 0);
	textureLoader->Load(innert_ats, "tube1", true, 0);
	textureLoader->Load(outert_ats, "tube2", true, 0);

	textureLoader->Load(cubes_ats, "cubes", true, 0);
	textureLoader->Load(cubesfl_ats, "cubesfloor", true, 0);

	textureLoader->Load(credits_ats, "credits", true, 1);

	textureLoader->Load(text_ats, "letters", true, 0);
	textureLoader->Load(cirkel_ats, "cirkel", true, 0);

	textureLoader->Load(cartoon_ats, "cartoon", false, 0);
	textureLoader->Load(cartoon2_ats, "cartoon2", false, 0);

	textureLoader->Load(_music_ats, "sign01", false, 0);
	textureLoader->Load(_4_plus_ats, "sign02", false, 0);
	textureLoader->Load(_booze_ats, "sign03", false, 0);
	textureLoader->Load(_comput_ats, "sign04", false, 0);
	textureLoader->Load(_likame_ats, "sign05", false, 0);
	textureLoader->Load(_heart_ats, "sign06", false, 0);

	textureLoader->Load(hole_ats, "hole", false, 0x3B7691);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, IN LPSTR lpCmdLine, IN int nShowCmd)
{
	memset(keyInput, 0, 256);

	HWND hWnd = InitWindow(APPLICATION_WIDTH, APPLICATION_HEIGHT, APPLICATION_CLASSNAME,
		APPLICATION_WINDOWCAPTION);

	ShowCursor(false);

	bool windowed = false; 

	// initialize directx 9.0
	pyramid = new Pyramid();

	pyramid->InitSystem(hWnd, APPLICATION_WIDTH, APPLICATION_HEIGHT, 32, 0);

	// start with a white loading screen
	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	pyramid->ShowBuffers();

	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	pyramid->ShowBuffers();
 
	// some tools
	textureLoader = new TextureLoader();
	//fontSystem = new FontSystem();
	drawer2D = new Drawer2D();
	renderChain = new RenderChain();
	postProcessor = new PostProcessor();

	/*textureLoader->Load("exploration.bmp", "exploration", false);

	textureLoader->Load("wobbler.bmp", "wobbler", true);

	textureLoader->Load("rasmus.bmp", "rasmus", true);

	textureLoader->Load("sperm.bmp", "sperm", true);
	textureLoader->Load("tube1.bmp", "tube1", true);
	textureLoader->Load("tube2.bmp", "tube2", true);

	textureLoader->Load("cubes.bmp", "cubes", true);
	textureLoader->Load("cubesfloor.bmp", "cubesfloor", true);

	textureLoader->Load("credits.bmp", "credits", true);

	textureLoader->Load("text.bmp", "letters", true);
	textureLoader->Load("cirkel.bmp", "cirkel", true);

	textureLoader->Load("cartoon.bmp", "cartoon", false);
	textureLoader->Load("cartoon2.bmp", "cartoon2", false);

	textureLoader->Load("sign01.bmp", "sign01", false);
	textureLoader->Load("sign02.bmp", "sign02", false);
	textureLoader->Load("sign03.bmp", "sign03", false);
	textureLoader->Load("sign04.bmp", "sign04", false);
	textureLoader->Load("sign05.bmp", "sign05", false);
	textureLoader->Load("sign06.bmp", "sign06", false);

	Image* image = new Image("hole.bmp");*/

	//if (image->valid)
	//{
	//	for (int i = 0; i < image->height * image->width; i++)
	//	{
	//		if ((image->data[i] & 0xffffff) == 0x3B7691)
	//		{
	//			image->data[i] = 0xff000000 | (image->data[i] & 0xffffff);
	//		}
	//		else
	//		{
	//			image->data[i] = 0x00000000 | (image->data[i] & 0xffffff);
	//		}
	//	}
	//}

	//textureLoader->Load(image->data, image->width, image->height, "hole", false);

	ShowCursor(false);

	LoadTextures();

	//// create the example effect
	//effect01 = new Effect01();
	effect02 = new Effect02();
	effect03 = new Effect03();
	effect04 = new Effect04();
	effect05 = new Effect05();
	effect06 = new Effect06();
	effect07 = new Effect07();
	effect08 = new Effect08();
	effect09 = new Effect09();
	effect10 = new Effect10();
	effect11 = new Effect11();
	effect12 = new Effect12();
	effect13 = new Effect13();
	effect14 = new Effect14();
	effect15 = new Effect15();
	effect16 = new Effect16();
	effect17 = new Effect17();
	//effect18 = new Effect18();
	effect19 = new Effect19();
	effect20 = new Effect20();
	effect21 = new Effect21();
	effect22 = new Effect22();

	whiteFlash = new WhiteFlash();
	blackFade = new BlackFade();

	clearBackBuffer = new ClearBackBuffer();

#ifdef FMOD_PLAY
	//fmodLoadMod((void*)"DECSYS.XM", 0);
	fmodLoadMod(decsys_xm, 58997);
#endif

#ifndef PLAY_SCRIPT
	//// init effects
	//effect01->Init();
	effect02->Init();
	effect03->Init();
	effect04->Init();
	effect05->Init();
	effect06->Init();
	effect07->Init();
	effect08->Init();
	effect14->Init();
	effect15->Init();
	effect17->Init();
	//effect18->Init();
	effect20->Init();
	effect21->Init();
	effect22->Init();

	whiteFlash->Init();
	blackFade->Init();


#ifdef FMOD_PLAY
	fmodPlay(FMOD_PLAY);
#endif

#else

	scriptRegisterEffect(clearBackBuffer, CLEARBACKBUFFER);

	scriptRegisterEffect(effect02, FX_GRIDBLOB);
	scriptRegisterEffect(effect04, FX_TUBE);
	scriptRegisterEffect(effect05, FX_BALL);
	scriptRegisterEffect(effect03, FX_CUBES);
	scriptRegisterEffect(effect06, FX_GREETINGS);
	scriptRegisterEffect(effect16, FX_COLORBLOCKS);
	scriptRegisterEffect(effect17, FX_PURPLELINES);
	scriptRegisterEffect(effect07, FX_CREDITS);
	scriptRegisterEffect(effect20, FX_CUBE);
	scriptRegisterEffect(effect21, FX_WOBSPERM);
	scriptRegisterEffect(effect22, FX_GRTSPERM);

	scriptRegisterEffect(effect09, TRANSITION_PART4);
	scriptRegisterEffect(effect10, TRANSITION_PART2);
	scriptRegisterEffect(effect19, TRANSITION_PART1);
	scriptRegisterEffect(effect12, TRANSITION_PART3);
	scriptRegisterEffect(effect13, TRANSITION_PART5);
	scriptRegisterEffect(effect15, TRANSITION_PART6);

	scriptRegisterEffect(effect14, LOGO_AARDBEI);
	scriptRegisterEffect(effect08, LOGO_SOUTHSIDE);

	scriptRegisterEffect(whiteFlash, FLASH_WHITE);
	scriptRegisterEffect(blackFade, FADE_BLACK);

	scriptInitEffects();

	//scriptInitFile("script.usc");
	scriptInit(script_usc);


	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0xffffff);

	pyramid->ShowBuffers();

	Sleep(1000);

#endif

	pyramid->ResetTimer();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while ((msg.message != WM_QUIT) && !INTRO_OVER)
	{ 
		if (PeekMessage (&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
		else	
		{
		}

		// this can be deleted: press space to switch between windowed and fullscreen
		/*if (keyInput[' '])
		{
			keyInput[' '] = false;

			windowed = !windowed;

			if (windowed)
			{
				SetWindowPos(hWnd, 0,
							 0, 0,
							 APPLICATION_WIDTH + 6, APPLICATION_HEIGHT + 25,
							 SWP_SHOWWINDOW);

				ShowCursor(true);
			}
			else
			{
				ShowCursor(false);
			}

			if (FAILED(pyramid->SwitchFullscreen()))
			{
				msg.message = WM_QUIT;
			}
		} */

		
		float timer = (float)pyramid->GetTimer();

#ifdef PLAY_SCRIPT

		scriptRun();

#else

		pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

		//pyramid->SetTexture(textureLoader->GetTexture("exploration"), 0);

		//drawer2D->BeginScene(BLEND_NONE);

		//drawer2D->DrawFullscreen();

		//drawer2D->EndScene();


	//	logo01->Do(timer);

		//effect08->Do(timer);
		//effect11->Do(timer

		//effect06->Do(timer);
		//effect05->Do(timer);

		//effect06->Do(timer);


#endif

		//if (timer - oldTimer > 1000)
		//{
		//	fps = frames;
		//	oldTimer = timer;
		//	frames = 0;
		//}

//		frames++;
//
//		fontSystem->Write(0, 0, "fps:%03i", fps);
//
//#ifdef FMOD_PLAY
		//int row, pos, sync;



		//fmodGetInfo(pos, row, sync);

		//fontSystem->Write(0, 16, "pos:%03i:%03i:%06i", pos, row, sync);

		// 7200
		//float sec = (timer + 20) * 0.001f;

		//const float bps = 125.f;
		//const float tpb = 60.f / bps;
		//const float tpp = 4 * 4 * tpb;

		//pos = (int)(sec / tpp);
		//row = (int)((sec / tpb) * 4.f) % 64;

		//fontSystem->Write(0, 32, "pos:%03i:%03i:%06i", pos, row,(int)timer);

//#endif

		pyramid->ShowBuffers();

		//Sleep(1);
	}

#ifdef FMOD_PLAY
	fmodStop();
#endif

#ifndef PLAY_SCRIPT

	//effect01->Destroy();
	//effect02->Destroy();
	//effect03->Destroy();
	//effect04->Destroy();
	//effect05->Destroy();
	//effect06->Destroy();
	effect07->Destroy();
	effect08->Destroy();
	effect14->Destroy();

//	delete effect01;
	delete effect02;
	delete effect03;
	delete effect04;
	delete effect05;
	delete effect06;
	delete effect07;
	delete effect08;
	delete effect09;
	delete effect10;
	delete effect11;
	delete effect12;
	delete effect13;
	delete effect14;

#endif

	pyramid->Destroy();

	delete pyramid;

	DeinitWindow();

	return 0;
}

DWORD FadeColor(float f, DWORD color)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;

	DWORD r = ((color >> 16) & 255) * f;
	DWORD g = ((color >>  8) & 255) * f;
	DWORD b = ((color >>  0) & 255) * f;

	return (r << 16) | (g << 8) | b;
}

DWORD MixColor(float f, DWORD color1, DWORD color2, bool alpha)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;

	int a1 = ((color1 >> 24) & 255);
	int r1 = ((color1 >> 16) & 255);
	int g1 = ((color1 >>  8) & 255);
	int b1 = ((color1 >>  0) & 255);

	int a2 = ((color2 >> 24) & 255);
	int r2 = ((color2 >> 16) & 255);
	int g2 = ((color2 >>  8) & 255);
	int b2 = ((color2 >>  0) & 255);

	a1 += (a2 - a1) * f;
	r1 += (r2 - r1) * f;
	g1 += (g2 - g1) * f;
	b1 += (b2 - b1) * f;

	if (alpha)
	{
		return (a1 << 24) | (r1 << 16) | (g1 << 8) | b1;
	}
	else
	{
		return (r1 << 16) | (g1 << 8) | b1;
	}
}