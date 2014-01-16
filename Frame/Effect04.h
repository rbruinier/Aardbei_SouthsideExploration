#ifndef __Effect04_H__
#define __Effect04_H__

#include "Effect.h"

class Scene;
class Object;

class Effect04 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;

	void MoveTubes(float timer);
};

#endif