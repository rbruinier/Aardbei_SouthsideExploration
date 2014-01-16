/*
	
	Pyramid Engine - Scene Class

	2003, Robert Jan Bruinier (rob / aardbei)

*/

#include "Scene.h"

#include "../System/Pyramid.h"
#include "../System/Light.h"
#include "../System/Matrix.h"

#include "Camera.h"
#include "Object.h"
#include "SpriteList.h"

extern Pyramid *pyramid;

// initialises all atributes to default values
Scene::Scene()
{
	camera = new Camera();

	objectCount = 0;
	lightCount = 0;
	spriteListCount = 0;
}

// clears all used dynamic memory
Scene::~Scene()
{
}

// adds an given Mesh Object to the meshObject vector
void Scene::AddObject(Object *pObject)
{
	//object.push_back(pObject);
	object[objectCount++] = pObject;
}

// adds an given Light object to the light vector
void Scene::AddLight(Light *pLight)
{
	//light.push_back(pLight);
	light[lightCount++] = pLight;
}

// adds an given SpriteList object to the light vector
void Scene::AddSpriteList(SpriteList *pSpriteList)
{
	//spriteList.push_back(pSpriteList);
	spriteList[spriteListCount++] = pSpriteList;
}

// renders the complete scene
void Scene::Render()
{
	DWORD i;

	camera->Update();

	// activate lights
	for (i = 0; i < lightCount; i++)
	{
		pyramid->SetLight(*light[i], i);
		pyramid->SetLightEnable(i, true);
	}

	pyramid->SetRenderState(D3DRS_LIGHTING, true);
	pyramid->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pyramid->SetRenderState(D3DRS_ZWRITEENABLE, true);

	pyramid->BeginScene();

	// render all mesh objects
	for (i = 0; i < objectCount; i++)
	{
		object[i]->Render();
	}

	// deactivate lights
	for (i = 0; i < lightCount; i++)
	{
		pyramid->SetLightEnable(i, false);
	}

	// render alle sprite lists
	pyramid->SetWorldMatrix(Matrix::Identity());

	pyramid->SetPointSpriteEnable(true);
	pyramid->SetD3DLighting(false);
	pyramid->SetCullMode(CULL_NONE);
	pyramid->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (i = 0; i < spriteListCount; i++)
	{
		spriteList[i]->Render();
	}

	pyramid->SetPointSpriteEnable(false);
	pyramid->SetD3DLighting(true);
	pyramid->SetRenderState(D3DRS_ZWRITEENABLE, true);

	pyramid->EndScene();
}

// destroys scene
void Scene::Destroy()
{
	DWORD i;

	for (i = 0; i < objectCount; i++)
	{
		object[i]->Destroy();

		delete object[i];
	}

	for (i = 0; i < lightCount; i++)
	{
		delete light[i];
	}

	for (i = 0; i < spriteListCount; i++)
	{
		delete spriteList[i];
	}

	//object.clear();
	//light.clear();

	delete camera;
}