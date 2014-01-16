/*
	
	Pyramid Engine - Sprite List Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __SpriteList_H__
#define __SpriteList_H__

#include <windows.h>

#include "../System/Pyramid.h"

class VertexBuffer;
class Texture;

struct SPRITE_VERTEX
{
	float x, y, z;
	DWORD diffuse;
};

#define SPRITE_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

class SpriteList
{
public:
	SpriteList(int iSprites, float fSize = 1.0f, Texture *pTexture = NULL, BLEND_MODE uiBlendMode = BLEND_ADD);
	~SpriteList();

	void Finish(bool bIsDynamic);

	void SetSize(float fSize);
	void SetTexture(Texture *pTexture);
	void SetBlendMode(BLEND_MODE uiBlendMode);

	void Render();

	SPRITE_VERTEX *sprite;

	int nrSprites;

protected:

private:
	void Refresh();

	bool isFinished;
	bool isDynamic;

	float size;

	BLEND_MODE blendMode;

	Texture *texture;

	VertexBuffer *vertexBuffer;
};

#endif