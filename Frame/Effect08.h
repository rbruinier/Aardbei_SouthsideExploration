#ifndef __Effect08_H__
#define __Effect08_H__

#include "Effect.h"

class Scene;

class Effect08 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;
};

#endif