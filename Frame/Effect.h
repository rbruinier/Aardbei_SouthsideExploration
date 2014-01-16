/*
	
	Pyramid Script - Effect Super Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Effect_H__
#define __Effect_H__

#include <windows.h>

class Effect
{
public:
	Effect();
	virtual	~Effect();

	virtual	void Init();
	virtual	void Do(float timer, int pos = 0, int row = 0);
	virtual	void Destroy();

	virtual void Receive(DWORD message, float timer, int pos, int row);

	float scriptTimer;
	bool  doResetOnPlay;

protected:
	int status;

	float tempTimer[50];
};


#endif