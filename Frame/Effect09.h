#ifndef __Effect09_H__
#define __Effect09_H__

#include "Effect.h"

class Scene;

class Effect09 : public Effect
{
public:
	void Do(float timer, int pos = 0, int row = 0);

private:
	Scene* scene;
};

#endif