/*
	
	Pyramid Tools - Script System

	2006, Robert Jan Bruinier (rob / aardbei)

	info:

		SCRIPT_MUSICSTART:
			pat1

		SCRIPT_RESETALL:
			pat1, row1

		SCRIPT_SEND:
			handle, pat1, row1, 4 bytes of data

		SCRIPT_NONE:

		SCRIPT_RESET:
			handle, pat1, row1

		SCRIPT_RUN:
			handle, pat1, row1, pat2, row2, layer

		SCRIPT_QUIT:
			pat1, row1

*/

#include "Main.h"

#include "Script.h"

#include "Effect.h"

#include "FMod.h"


//#define SCRIPT_OUTPUT "script_debug.txt"

#ifdef SCRIPT_OUTPUT

#include "Stdio.h"

void StartScriptOutput()
{
	FILE* logfile;

	logfile = fopen(SCRIPT_OUTPUT, "w+");

	fclose(logfile);
}

void WriteScriptOutput(char *pText, ...)
{
	FILE* logfile;

	logfile = fopen(SCRIPT_OUTPUT, "a+");

	char buffer[2000];
	va_list argptr;
	va_start(argptr, pText) ;
	vsprintf(buffer, pText, argptr );

	fprintf(logfile, buffer);

	fclose(logfile);
}

int scriptFrameCounter = 0;

#endif

class ScriptLayer 
{
public:
	int	handle;
	int oldHandle;
};

class ScriptMessage 
{
public:
	byte pat1, pat2;
	byte row1, row2;
	byte layer;
	byte handle;
	byte task;
	byte extra;
}; 

#define SCRIPT_MUSICSTART	249
#define SCRIPT_RESETALL		250
#define SCRIPT_SEND			251
#define SCRIPT_NONE			252
#define SCRIPT_RESET		253
#define SCRIPT_RUN			254
#define SCRIPT_QUIT			255

ScriptLayer	scrLayer[256];
ScriptMessage* scrMessage;

int scrNrLayers   = 0;
int	scrNrMessages = 0;

Effect*	scrEffect[256];
int	scrNrEffects = 0;

bool musicIsPlaying = false;

void scriptRegisterEffect(Effect* effect, int handle) 
{
	if (scrNrEffects == 0)
	{
		for (int i = 0; i < 256; i++)
		{
			scrEffect[i] = NULL;
		}
	}

	scrEffect[handle] = effect;

	scrNrEffects++;
}

void scriptInitFile(char *filename) 
{
	DWORD tmp;
	HANDLE FH;

	FH = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (FH != INVALID_HANDLE_VALUE) 
	{
		int size = GetFileSize(FH, &tmp);
		byte *data = new byte[size];
		ReadFile(FH, data, size, &tmp, NULL );
		CloseHandle( FH );
		scriptInit(data);
	}
}

void scriptInit(byte script[]) 
{
	scrNrMessages = *(DWORD*)script;

	scrMessage = (ScriptMessage*) ((byte*)script + 4);

	for (int i = 0; i < 256; i++) 
	{
		if (scrEffect[i])
		{
			scrEffect[i]->scriptTimer = 0;
		}
	}

	for (i = 0; i < 256; i++) 
	{
		scrLayer[i].handle    = 0;
		scrLayer[i].oldHandle = 0;
	}
}

void scriptInitEffects() 
{
	#ifdef SCRIPT_OUTPUT
		StartScriptOutput();
	#endif

	for (int i = 0; i < 256; i++) 
	{
		if (scrEffect[i])
		{
			scrEffect[i]->Init();

			#ifdef SCRIPT_OUTPUT
				WriteScriptOutput("effect initialized: %03i\n", i);
			#endif
		}
	}
} 

void scriptRun() 
{
	int pat1, pat2, row1, row2, handle, layer, run, extra;
	int pos, row, sync;

	float timer = pyramid->GetTimer();

	pos  = -1;
	row  = -1;
	sync = -1;

	if (musicIsPlaying)
	{
		fmodGetInfo(pos, row, sync);

		//float sec = (timer + 20) * 0.001f;

		//const float bps = 125.f;
		//const float tpb = 60.f / bps;
		//const float tpp = 4 * 4 * tpb;

		//pos = (int)(sec / tpp);
		//row = (int)((sec / tpb) * 4.f) % 64;
	}

	for (int i = 0; i < 256; i++) 
	{
		scrLayer[i].oldHandle = scrLayer[i].handle;

		scrLayer[i].handle = 0;
	}

	#ifdef SCRIPT_OUTPUT
		WriteScriptOutput("\n%06i: %03i.%03i (%06i) - SCRIPTRUN\n", scriptFrameCounter, pos, row, (int)timer);
	#endif

	for (i = 0; i < scrNrMessages; i++) 
	{
		int msg = scrMessage[i].task;

		switch(msg) 
		{
		case SCRIPT_NONE:
			break;
		
		case SCRIPT_QUIT:
			pat1 = scrMessage[i].pat1;
			row1 = scrMessage[i].row1;

			if (((pos >= pat1) && (row >= row1)) || (pos > pat1))
			{
				//for (int j = 0; j < 256; j++)
				//{
				//	if (scrEffect[j])
				//	{
				//		scrEffect[j]->Destroy();
				//		delete scrEffect[j];
				//	}
				//}

				#ifdef SCRIPT_OUTPUT
					WriteScriptOutput("  quit (%03i.%03i)\n", pat1, row1);
				#endif


				INTRO_OVER = true;
			}

			

			break;

		case SCRIPT_RESETALL:
			pat1 = scrMessage[i].pat1;
			row1 = scrMessage[i].row1;

			#ifdef SCRIPT_OUTPUT
				WriteScriptOutput("  reset all (%03i.%03i)\n", pat1, row1);
			#endif

			if (((pos >= pat1) && (row >= row1)) || (pos > pat1))
			{
				for (int j = 0; j < 256; j++)
				{
					if (scrEffect[j])
					{
						scrEffect[j]->scriptTimer = timer;
					}
				}
				scrMessage[i].task = SCRIPT_NONE;
			}

			break;

		case SCRIPT_MUSICSTART:
			pat1 = scrMessage[i].pat1;

			#ifdef SCRIPT_OUTPUT
				WriteScriptOutput("  music start (%03i)\n", pat1);
			#endif

			fmodPlay(pat1);

			scrMessage[i].task = SCRIPT_NONE;

			musicIsPlaying = true;

			pos = row = 0;

			pyramid->ResetTimer();

			break;

		case SCRIPT_RUN:
			handle = scrMessage[i].handle;
			pat1   = scrMessage[i].pat1;
			row1   = scrMessage[i].row1;
			pat2   = scrMessage[i].pat2;
			row2   = scrMessage[i].row2;
			layer  = scrMessage[i].layer;

			run = false;

			if ((pos >= pat1) && (pos <= pat2)) run = true;
			if ((pos == pat1) && (row  < row1)) run = false;
			if ((pos == pat2) && (row >= row2)) run = false;

			if (run)
			{
				#ifdef SCRIPT_OUTPUT
					WriteScriptOutput("  run: %03i (%03i.%03i - %03i.%03i)\n", handle, pat1, row1, pat2, row2);
				#endif

				scrLayer[layer].handle = handle;
			}

		break;

		case SCRIPT_SEND:
			handle = scrMessage[i].handle;
			pat1   = scrMessage[i].pat1;
			row1   = scrMessage[i].row1;
			pat2   = scrMessage[i].pat2;
			row2   = scrMessage[i].row2;
			layer  = scrMessage[i].layer;
			extra  = scrMessage[i].extra;

			if (((pos >= pat1) && (row >= row1)) || (pos > pat1)) 
			{
				#ifdef SCRIPT_OUTPUT
					WriteScriptOutput("  send: %03i (%03i.%03i -> %03i %03i %03i %03i; %06i - %06i = %06i)\n", handle, pat1, row1, pat2, row2, layer, extra, (int)timer, (int)scrEffect[handle]->scriptTimer, (int)(timer - scrEffect[handle]->scriptTimer));
				#endif

				scrEffect[handle]->Receive((pat2 << 24) + (row2 << 16) + (layer << 8) + extra, timer - scrEffect[handle]->scriptTimer, pos, row);	
				
				scrMessage[i].task = SCRIPT_NONE;
			}

		break;

		case SCRIPT_RESET:
			pat1   = scrMessage[i].pat1;
			row1   = scrMessage[i].row1;
			handle = scrMessage[i].handle;

			if (((pos >= pat1) && (row >= row1)) || (pos > pat1)) 
			{
				#ifdef SCRIPT_OUTPUT
					WriteScriptOutput("  reset: %03i (%03i.%03i)\n", handle, pat1, row1);
				#endif

				scrEffect[handle]->scriptTimer = timer;				
				scrMessage[i].task = SCRIPT_NONE;
			}

			break;

		}

	}

	#ifdef SCRIPT_OUTPUT
		WriteScriptOutput("  walking through layers:\n");
	#endif

	for (i = 0; i < 256; i++) 
	{
		handle = scrLayer[i].handle;

		if (handle != 0)
		{
			if (handle != scrLayer[i].oldHandle)
			{
				if (scrEffect[handle]->doResetOnPlay)
				{
					scrEffect[handle]->scriptTimer = timer;
				}
			}

			#ifdef SCRIPT_OUTPUT
				WriteScriptOutput("    do effect: %03i on layer %03i (%06i - %06i = %06i)\n", handle, i, (int)timer, (int)scrEffect[handle]->scriptTimer, (int)(timer - scrEffect[handle]->scriptTimer));
			#endif

			scrEffect[handle]->Do(timer - scrEffect[handle]->scriptTimer);
		}
	}

	#ifdef SCRIPT_OUTPUT
		scriptFrameCounter++;
	#endif
}

