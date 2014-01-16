/*
	
	Pyramid System - (Display) Adapter Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Adapter_H__
#define __Adapter_H__

#include <vector>
using namespace std;

#include <d3d9.h>

struct PYRAMID_DISPLAYMODE
{
	D3DDISPLAYMODE d3dDisplayMode;
	D3DFORMAT d3dTextureFormat16;
	D3DFORMAT d3dTextureFormat32;
	D3DFORMAT d3dBackBufferFormat;
	D3DFORMAT d3dZBufferFormat;
	DWORD videoBPP;
	DWORD number;
};

class Adapter
{
public:

	Adapter();
	~Adapter();

	int GetAdapterInformation(IDirect3D9 *pD3DInterface, DWORD iD3DAdapter, D3DDEVTYPE iD3DDeviceType);
	int GetBestDisplayMode(PYRAMID_DISPLAYMODE &pDisplayMode, int iWidth, int iHeight, int iVideoBPP);

	vector <PYRAMID_DISPLAYMODE> displayModeList;

	PYRAMID_DISPLAYMODE displayModeDesktop;

	bool supportsPureDevice;	
	bool supportsHardwareTnL;
	bool supportsPointSprites;

	char *driver;
	char *description;
	
private:
	int GetBPPFromD3DFormat(D3DFORMAT pD3DFormat);
	int FindFormats(IDirect3D9 *pD3DInterface, PYRAMID_DISPLAYMODE &pDisplayMode);

	D3DADAPTER_IDENTIFIER9 d3dAdapterIdentifier;

	DWORD d3dAdapter;
	D3DDEVTYPE d3dDeviceType;
};

#endif