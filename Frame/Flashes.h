#ifndef __Flashes_H__
#define __Flashes_H__

#include "Effect.h"

class WhiteFlash : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
};

class BlackFade : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
};

#endif