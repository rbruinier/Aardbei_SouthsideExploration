#ifndef __Effect02_H__
#define __Effect02_H__

#include "Effect.h"

class Scene;


class Effect02 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();
	void Receive(DWORD message, float timer, int pos = 0, int row = 0);

private:
	Scene* scene;

	void ClearGrid();
	void PrepareGrid();
};

#endif