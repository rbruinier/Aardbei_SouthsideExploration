/*
	
	Pyramid Script - Effect Super Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Effect.h"

Effect::Effect() 
{
	doResetOnPlay = true;

	scriptTimer = 0;

	status = 0;

	for (int i = 0; i < 50; i++) tempTimer[i] = 0;
}

Effect::~Effect() {
}

void Effect::Init() 
{
}

void Effect::Do(float timer, int pos, int row) 
{
}

void Effect::Destroy() 
{
}

void Effect::Receive(DWORD message, float timer, int pos = 0, int row = 0) 
{
	status = message;

	if (status < 50)
	{
		tempTimer[status] = timer;
	}
}
