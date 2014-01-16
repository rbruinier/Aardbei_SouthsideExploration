/*
	
	Pyramid Tools - Script System

	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Script_H__
#define __Script_H__

class Effect;

void scriptInit(byte script[]);
void scriptRun();

void scriptInitFile(char* filename);

void scriptInitEffects();
void scriptRegisterEffect(Effect* effect, int handle);

#endif
