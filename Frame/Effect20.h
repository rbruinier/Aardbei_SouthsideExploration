#ifndef __Effect20_H__
#define __Effect20_H__

#include "Effect.h"

class Scene;

class Effect20 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;

	VertexBuffer* lineVB;
};

#endif