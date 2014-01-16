#ifndef __FMod_H__
#define __FMod_H__

extern void fmodLoadMod(void* data, int length);
extern void fmodPlay(int iOrder);
extern void fmodStop();
extern void fmodGetInfo(int &order, int &row, int &sync);

#endif