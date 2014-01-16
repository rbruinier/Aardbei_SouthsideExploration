#ifndef __Effect16_H__
#define __Effect16_H__

#include "Effect.h"

class Scene;

class Effect16 : public Effect
{
public:
	void Do(float timer, int pos = 0, int row = 0);

private:
	Scene* scene;
};

#endif