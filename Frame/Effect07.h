#ifndef __Effect07_H__
#define __Effect07_H__

#include "Effect.h"

class Scene;

class Effect07 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;
};

#endif