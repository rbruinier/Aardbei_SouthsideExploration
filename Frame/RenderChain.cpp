/*
	
	Pyramid Tools - RenderChain Chain Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Main.h"

RenderChain::RenderChain()
{
	index = 0;

	RECT r;

	pyramid->GetViewport(r);

	char buffer[512];

	if (pyramid->CreateTexture(r.right - r.left, r.bottom - r.top, 32, false, true, true, &original) ==
		E_FAIL)
	{
		pyramid->ShowError("failed");
	}

	if (pyramid->CreateTexture(r.right - r.left, r.bottom - r.top, 32, false, true, true, &targetList[0]) ==
		E_FAIL)
	{
		pyramid->ShowError("failed");
	}

	if (pyramid->CreateTexture(r.right - r.left, r.bottom - r.top, 32, false, true, true, &targetList[1]) ==
		E_FAIL)
	{
		pyramid->ShowError("failed");
	}
}

RenderChain::~RenderChain()
{
}

void RenderChain::Flip()
{
	index = (index + 1) & 1;
}

Texture* RenderChain::GetOriginal()
{
	return original;
}

Texture* RenderChain::GetSource()
{
	return targetList[index];
}

Texture* RenderChain::GetTarget()
{
	return targetList[(index + 1) & 1];
}