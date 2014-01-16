#ifndef __Effect17_H__
#define __Effect17_H__

#include "Effect.h"

class Scene;

class Effect17 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);

private:
	Scene* scene;
};

#endif