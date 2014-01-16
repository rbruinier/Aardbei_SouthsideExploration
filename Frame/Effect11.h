#ifndef __Effect11_H__
#define __Effect11_H__

#include "Effect.h"

class Scene;

class Effect11 : public Effect
{
public:
	void Do(float timer, int pos = 0, int row = 0);

private:
	Scene* scene;
};

#endif