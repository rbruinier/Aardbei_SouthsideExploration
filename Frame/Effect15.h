#ifndef __Effect15_H__
#define __Effect15_H__

#include "Effect.h"

class Scene;

class Effect15 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);

private:
	Scene* scene;
};

#endif