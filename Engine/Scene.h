/*
	
	Pyramid Engine - Scene Class


	2003, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Scene_H__
#define __Scene_H__

//#include <vector>
//using namespace std;

class Object;
class Light;
class Frustum;
class Camera;
class SpriteList;

class Scene
{
public:
	Scene();
	~Scene();

	void AddObject(Object* pObject);
	void AddLight(Light* pLight);
	void AddSpriteList(SpriteList* pSpriteList);

	void Render();

	void Destroy();

	Camera *camera;

	//vector <Object*> object;
	//vector <Light*> light;
	//vector <SpriteList*> spriteList;

	Object* object[65535];
	Light* light[512];
	SpriteList* spriteList[512];

	int objectCount;
	int lightCount;
	int spriteListCount;

protected:

private:
	Frustum* frustum;
};

#endif