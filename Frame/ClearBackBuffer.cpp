/*
	
	Southside Variations - ClearBackBuffer

	Description:

	Clears the backbuffer 

*/

#include "Main.h"

#include "ClearBackBuffer.h"

void ClearBackBuffer::Init()
{
	status = 0xffffff;
}

void ClearBackBuffer::Do(float timer, int pos, int row) 
{
	pyramid->ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, status);
}