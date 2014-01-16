#ifndef __Effect21_H__
#define __Effect21_H__

#include "Effect.h"

class Scene;

class Effect21 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;
};

#endif