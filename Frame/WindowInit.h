#ifndef __WindowInit_H__
#define __WindowInit_H__

extern HWND InitWindow(int clientWidth, int clientHeight, char* className, char* windowCaption);
void DeinitWindow();

extern BYTE keyInput[256];

#endif