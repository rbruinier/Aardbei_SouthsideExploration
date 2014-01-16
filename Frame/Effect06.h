#ifndef __Effect06_H__
#define __Effect06_H__

#include "Effect.h"

class Scene;
class Object;

#define NR_LETTERS 5000

struct LETTER_VERTEX
{
	float x, y, z;
	DWORD diffuse;
	float u, v;
};

struct LETTER_LINE_VERTEX
{
	float x, y, z;
	DWORD diffuse;
};

#define LETTER_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE)
#define LETTER_LINE_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct Letter
{
public:
	LETTER_VERTEX* vertices;
	Vector location;
	Vector rotation;
	Vector original;
	char letter;
};


class Greeting
{
public:
	Greeting(Letter* letterList, char* name)
	{
		lettersSize = (int)strlen(name);

		for (int i = 0; i < lettersSize; i++)
		{
			char letter = name[i];

			int index = rand() % NR_LETTERS;

			while (true)
			{
				if (letterList[index].letter == letter)
				{
					letters[i] = &letterList[index];
					break;
				}

				index = (index + 1) % NR_LETTERS;
			}
		}
	}

	Letter* letters[50];

	int lettersSize;
};

class Effect06 : public Effect
{
public:
	void Init();
	void Do(float timer, int pos = 0, int row = 0);
	void Destroy();

private:
	Scene* scene;

	SpriteList* spriteList;

	LETTER_VERTEX LettersVertices[NR_LETTERS * 4];
	LETTER_LINE_VERTEX lineVertices[50];

	Letter letterList[NR_LETTERS];

	VertexBuffer* vb;
	VertexBuffer* lineVB;

	Camera camera;

	void GetLetterU(char letter, float& u1, float& u2);
	int GetColor(float timer, int letterNR);
};

#endif