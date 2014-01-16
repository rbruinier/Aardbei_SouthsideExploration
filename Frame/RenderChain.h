/*
	
	Pyramid Tools - RenderTarget Chain Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __RenderTarget_H__
#define __RenderTarget_H__

#include <windows.h>

class Texture;

class RenderChain
{
public:
	RenderChain();
	~RenderChain();

	void Flip();

	Texture* GetOriginal();
	Texture* GetSource();
	Texture* GetTarget();

private:
	Texture* original;
	Texture* targetList[2];

	int index;
};

#endif