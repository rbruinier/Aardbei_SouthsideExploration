#ifndef __Effect05_H__
#define __Effect05_H__

#include "Effect.h"

class Scene;
class Object;


#define FX05_CUBE_GRID_SIZE 4

#define FX05_CUBE_COUNT (FX05_CUBE_GRID_SIZE * FX05_CUBE_GRID_SIZE * FX05_CUBE_GRID_SIZE)

class Effect05 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;

	Vector locations[FX05_CUBE_COUNT];
};

#endif