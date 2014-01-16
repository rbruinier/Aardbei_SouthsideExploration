#include "Main.h"

#include "..\FMod\lib\minifmod.h"

//#define FMOD_FROM_FILE

FMUSIC_MODULE	*fmodMod = NULL;
void			*fmodData;
int				fmodLength;
int				fmodPos;
unsigned char	fmodMusic;

#ifdef FMOD_FROM_FILE

unsigned int memopen(char *name)
{
	return (unsigned int)fopen(name, "rb");
}

void memclose(unsigned int handle)
{
	fclose((FILE *)handle);
}

int memread(void *buffer, int size, unsigned int handle)
{
	return fread(buffer, 1, size, (FILE *)handle);
}

void memseek(unsigned int handle, int pos, signed char mode)
{
	fseek((FILE *)handle, pos, mode);
}

int memtell(unsigned int handle)
{
	return ftell((FILE *)handle);
}

#else

unsigned int memopen(char * name) 
{
	fmodPos    = 0;
	return 1;
}

void memclose(unsigned int handle) 
{
}

int memread(void *buffer, int size, unsigned int handle) 
{
	if (fmodPos + size >= fmodLength)
		size = fmodLength - fmodPos;

	memcpy(buffer, (char *)fmodData+fmodPos, size);
	fmodPos += size;
	
	return size;
}

void memseek(unsigned int handle, int pos, signed char mode) 
{
	if (mode == SEEK_SET) 
		fmodPos = pos;
	else if (mode == SEEK_CUR) 
		fmodPos += pos;
	else if (mode == SEEK_END)
		fmodPos = fmodLength;

	if (fmodPos > fmodLength)
		fmodPos = fmodLength;
}
 
int memtell(unsigned int handle) 
{
	return fmodPos;
}

#endif


void fmodLoadMod(void* data, int length) 
{
	fmodData   = data;
	fmodLength = length;

	FSOUND_File_SetCallbacks(memopen, memclose, memread, memseek, memtell);

	if (!FSOUND_Init(44100, 0)) 
	{
		return;
		//uniQuit("Your soundcard is... gone?!");
	}

	fmodMod = FMUSIC_LoadSong((char*)data, NULL);

	if (!fmodMod) 
	{
		return;
		//uniQuit("Unable to load XM");
	}
}

void fmodPlay(int iOrder) 
{
	if (!fmodMod)
	{
		return;
	}

	FMUSIC_PlaySong(fmodMod, iOrder);
}

void fmodStop() 
{
	if (!fmodMod)
	{
		return;
	}

	FMUSIC_FreeSong(fmodMod);
	FSOUND_Close();
}

void fmodGetInfo(int &order, int &row, int &sync) 
{
	if (!fmodMod)
	{
		return;
	}

	FMUSIC_GetOrderAndRow(fmodMod, &order, &row);

	//order = FMUSIC_GetOrder(fmodMod);
	//row   = FMUSIC_GetRow(fmodMod);
	//sync  = FMUSIC_GetTime(fmodMod);


}