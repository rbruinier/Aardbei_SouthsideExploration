/*
	
	Pyramid Engine - Sprite List Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#include "SpriteList.h"

#include "../System/VertexBuffer.h"

extern Pyramid *pyramid;

SpriteList::SpriteList(int iSprites, float fSize, Texture* pTexture, BLEND_MODE uiBlendMode)
{
	isFinished = false;

	nrSprites = iSprites;

	size = fSize;

	blendMode = uiBlendMode;

	sprite = new SPRITE_VERTEX[nrSprites];

	for (int i = 0; i < nrSprites; i++)
	{
		sprite[i].x = sprite[i].y = sprite[i].z = 0;
		sprite[i].diffuse = 0xffffffff;
	}

	SetTexture(pTexture);
}

SpriteList::~SpriteList()
{
	if (sprite != NULL)
	{
		delete [] sprite;
	}
}

void SpriteList::Refresh()
{
	vertexBuffer->Update(sprite);
}

void SpriteList::Finish(bool bIsDynamic)
{
	if (isFinished)
	{
		return;
	}

	isDynamic = bIsDynamic;

	pyramid->CreateVertexBuffer(nrSprites, sizeof(SPRITE_VERTEX), SPRITE_VERTEX_FVF, 
		                        isDynamic, true, &vertexBuffer);

	vertexBuffer->Update(sprite);

	isFinished = true;
}


void SpriteList::SetSize(float fSize)
{
	size = fSize;
}

void SpriteList::SetTexture(Texture* pTexture)
{
	texture = pTexture;
}

void SpriteList::SetBlendMode(BLEND_MODE uiBlendMode)
{
	blendMode = uiBlendMode;
}


void SpriteList::Render()
{
	if (!isFinished)
	{
		Finish(false);
	}

	if (isDynamic)
	{
		Refresh();
	}

	pyramid->SetTexture(texture);

	pyramid->SetTransparency(blendMode);

    pyramid->SetPointSpriteSize(size);

	pyramid->SetVertexStream(vertexBuffer);

	pyramid->DrawPointList(0, nrSprites);

	pyramid->SetTransparency(BLEND_NONE);
}
