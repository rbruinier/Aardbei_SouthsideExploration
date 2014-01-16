/*
	
	Pyramid Tools - Font Class

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __FontSystem_H__
#define __FontSystem_H__

class Texture;

class FontSystem
{
public:
	FontSystem();

	void Write(int x, int y, char *text, ...);

private:
	Texture* texture;
};

#endif