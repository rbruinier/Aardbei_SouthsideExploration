#ifndef __Effect12_H__
#define __Effect12_H__

#include "Effect.h"

class Scene;

class Effect12 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Receive(DWORD message, float timer, int pos, int row);

private:
	Scene* scene;
};

#endif