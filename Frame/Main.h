#ifndef __Main_H__
#define __Main_H__

#pragma warning ( disable : 4244 )

#include <windows.h> 
#include <math.h>

#include "../System/Pyramid.h"

#include "../System/Texture.h"
#include "../System/Light.h"
#include "../System/Matrix.h"

#include "../Engine/Scene.h"
#include "../Engine/Object.h"
#include "../Engine/Camera.h"
#include "../Engine/SpriteList.h"

#include "Primitives.h"
#include "Image.h"
#include "TextureLoader.h"
#include "Drawer2D.h"
#include "FontSystem.h"
#include "RenderChain.h"
#include "PostProcessor.h"

extern Pyramid* pyramid;

extern TextureLoader* textureLoader;
extern FontSystem* fontSystem;
extern Drawer2D* drawer2D;
extern RenderChain* renderChain;
extern PostProcessor* postProcessor;

extern DWORD background;

extern DWORD FadeColor(float f, DWORD color);
extern DWORD MixColor(float f, DWORD color1, DWORD color2, bool alpha = false);

extern bool INTRO_OVER;


#endif