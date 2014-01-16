#ifndef __Effect14_H__
#define __Effect14_H__

#include "Effect.h"

class Effect14 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

	void Receive(DWORD message, float timer, int pos, int row);
};

#endif