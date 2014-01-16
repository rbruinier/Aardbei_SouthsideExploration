/*
	
	Southside Variations - Effect01

	Description:


*/

#include "Main.h"

#include "Effect01.h"

Object* src;

void Effect01::Init() 
{
	// create a new scene
	scene = new Scene();						

	// create an object, a primitive sphere in this case
	Object *obj = Primitives::Sphere(20, 3);

	// set the texture for this object
	obj->SetTexture((*textureLoader)["tex01"]);

	// create important buffers, true means that it will be dynamic vertex data
	obj->Finish(true);							

	// add the object to the scene
	scene->AddObject(obj);						

	// add a light to the scene
	scene->AddLight(new Light());	
	
	scene->light[0]->SetDiffuse(0.4f, 0.4f, 0.4f);
	scene->light[0]->SetDiffuse(-1, -1, -1);

	// set the fov of the camera to a wide angle
	scene->camera->SetFov(1.2f);

	// create a source object (not used for rendering)
	src = Primitives::Sphere(20, 3);
}

void Effect01::Do(float timer, int pos, int row) 
{
	// set the ambient light level
	pyramid->SetAmbientLight(0x303030);
	pyramid->SetAmbientLight(0xffffff);

	// disable fog
	pyramid->SetFogNone();

	// get pointer to object
	Object *obj = scene->object[0];

	// manipulate vertex data
	for (int i = 0; i < obj->nrVertices; i++)
	{
		Vector *v = (Vector*) &src->vertex[i];

		float scale = sin((v->x * 1.7f) + (timer * 0.003f)) + 
			          cos((v->y * 1.2f) + (timer * 0.0035f)) +
					  sin((v->z * 2.9f) + (timer * 0.0027f));

		scale = 1.0f + (scale * 0.2f);

		obj->vertex[i].x = v->x * scale;
		obj->vertex[i].y = v->y * scale;
		obj->vertex[i].z = v->z * scale;
	}


	// create some nice camera movement
	Vector v;

	v.x = sin(timer / 2000.f) * 10.f;
	v.y = cos(timer / 3300.f) * 10.f;
	v.z = sin(timer / 2200.f) * 10.f;

	v = v.Normalize() * 7;

	// set camera location
	scene->camera->SetLocation(v.x, v.y, v.z);

	// set light position
	scene->light[0]->SetLocation(v.x, v.y, v.z);

	// render the scene (engine automatically does everything)
	scene->Render();
}

void Effect01::Destroy() 
{
	// clean up
	scene->Destroy();
	src->Destroy();

	delete scene;
	delete src;
}