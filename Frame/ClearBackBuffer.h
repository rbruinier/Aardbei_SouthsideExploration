#ifndef __ClearBackBuffer_H__
#define __ClearBackBuffer_H__

#include "Effect.h"

class Scene;

class ClearBackBuffer : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
};

#endif