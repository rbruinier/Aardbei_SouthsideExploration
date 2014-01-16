/*
	
	Pyramid System - Pyramid Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#ifndef __Pyramid_H__
#define __Pyramid_H__

#include <windows.h>

//#include <vector>
//#include <string>
//using namespace std;

//#include "Adapter.h"

#include <d3d9.h>

#define _PI  3.1415926535897f
#define _2PI 6.2831853071795f

#define LOG_FILENAME	"log.html"
#define LOG_TITLE		"robnoys screensavers - log file"

enum SYSTEMINIT_PARAMETERS
{
	SYS_WVR = 1,
	SYS_LOG = 2,
	SYS_WIN = 4
};

enum CLEAR_PARAMETERS
{
	CLEAR_SCREEN  = 1,
	CLEAR_ZBUFFER = 2,
};

enum CULL_MODE
{
	CULL_NONE = D3DCULL_NONE,
	CULL_CW   = D3DCULL_CW,
	CULL_CCW  = D3DCULL_CCW
};

enum BLEND_MODE
{
	BLEND_NONE     = 0,
	BLEND_ADD      = 1,
	BLEND_SUBTRACT = 2,
	BLEND_MODULATE = 3,
	BLEND_ALPHA    = 4,
	BLEND_INVERT   = 5
};

class Pyramid
{
public:
	IDirect3DDevice9*	d3dDevice;

	friend class Matrix;
	friend class Vector;
	friend class Texture;
	friend class Material;
	friend class Light;
	friend class IndexBuffer;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;

	Pyramid();
	~Pyramid();

	int InitSystem(HWND hWindowHandle, DWORD iWidth, DWORD iHeight, DWORD iVideoBPP, DWORD iInitParameters);
	int Destroy();

	//Adapter* GetAdapterInfo();

	int SwitchFullscreen();

	int ClearBuffers(DWORD iClearParameters, DWORD iColor);
	int ShowBuffers();

	void ShowError(char* pMessage);

	int BeginScene();
	int EndScene();

	int SetTexture(Texture* pTexture, DWORD uiStage = 0);

	int SetRenderState(D3DRENDERSTATETYPE uiType, DWORD uiState);
	int SetTextureStageState(DWORD uiStage, D3DTEXTURESTAGESTATETYPE uiType, DWORD uiState);

	int SetSamplerState(DWORD uiStage, D3DSAMPLERSTATETYPE  uiType, DWORD uiState);

	int SetViewMatrix(Matrix &pMatrix);
	int SetWorldMatrix(Matrix &pMatrix);
	int SetProjectionMatrix(Matrix &pMatrix);

	int GetViewMatrix(Matrix &pMatrix);
	int GetWorldMatrix(Matrix &pMatrix);
	int GetProjectionMatrix(Matrix &pMatrix);

	int GetWidth();
	int GetHeight();

	int SetFogLinear(float fStart, float fEnd, bool pixel = false);
	int SetFogExp(float fDensity, bool pixel = false);
	int SetFogExp2(float fDensity, bool pixel = false);
	int SetFogNone();
	int SetFogColor(DWORD uiColor);
	int SetFogRangeBased(bool bEnabled);

	int SetCullMode(CULL_MODE uiCullMode);

	int SetD3DLighting(bool bEnabled);

	int SetPointSpriteEnable(bool bEnabled);

	int SetPointSpriteSize(float fSize);

	int Set2DEnable(bool bEnabled);

	int SetWriteZBufferEnable(bool bEnabled);

	int SetMaterial(Material &pMaterial);
	int SetLight(Light &pLight, DWORD uiIndex);
	int SetLightEnable(DWORD uiIndex, bool bEnabled);

	int SetTransparency(BLEND_MODE uiBlendMode);

	int SetAmbientLight(DWORD uiColor);

	int CreateTexture(DWORD uiWidth, DWORD uiHeight, DWORD iBPP, bool bMipMap, bool bDynamic, 
			bool bRenderTarget, Texture **pTexture, bool bMultisample = false);

	int CreateVertexBuffer(DWORD uiNrVertices, DWORD uiVertexSize, DWORD uiFVF, bool bDynamic, bool bPointSprites, VertexBuffer **pVertexBuffer);
	int CreateIndexBuffer(DWORD uiNrFaces, bool b32Bit, bool bDynamic, IndexBuffer **pIndexBuffer);

	//int CreateVertexShader(DWORD* pSource, D3DVERTEXELEMENT9* pDecl, VertexShader** pVertexShader);
	int CreatePixelShader(DWORD* pSource, PixelShader** pPixelShader);

	int SetVertexStream(VertexBuffer* pVertexBuffer, int nStreamNumber = 0);
	int SetIndexStream(IndexBuffer* pIndexBuffer);

	//int SetVertexShader(VertexShader *pVertexShader);
	int SetPixelShader(PixelShader *pPixelShader);

	//int SetVertexShaderConstantF(DWORD uiStartReg, float* pData, DWORD uiNrVectors);
	//int SetVertexShaderConstantB(DWORD uiStartReg, BOOL* pData, DWORD uiNrBooleans);
	//int SetVertexShaderConstantI(DWORD uiStartReg, int* pData, DWORD uiNrVectors);

	int SetPixelShaderConstantF(DWORD uiStartReg, float* pData, DWORD uiNrVectors);
	int SetPixelShaderConstantB(DWORD uiStartReg, BOOL* pData, DWORD uiNrBooleans);
	int SetPixelShaderConstantI(DWORD uiStartReg, int* pData, DWORD uiNrVectors);

	int SetViewport(RECT &pRect);
	int GetViewport(RECT &pRect);

	int SetRenderTarget(Texture* pTexture);
	int ResetRenderTarget();

	int DrawIndexedPrimitiveList(DWORD uiMinIndex, DWORD uiNrVertices, DWORD uiStartIndex, DWORD uiNrPrimitives);
	int DrawPrimitiveList(DWORD uiMinIndex, DWORD uiNrPrimitives);
	int DrawPrimitiveStrip(DWORD uiMinIndex, DWORD uiNrPrimitives);
	int DrawPrimitiveFan(DWORD uiMinIndex, DWORD uiNrPrimitives);
	int DrawLineList(DWORD uiMinIndex, DWORD uiNrLines);
	int DrawLineStrip(DWORD uiMinIndex, DWORD uiNrLines);
	int DrawPointList(DWORD uiMinIndex, DWORD uiNrVertices);

	void ResetTimer();
	DWORD GetTimer();

	void OpenLog();
	void CloseLog();
	void WriteLog(int iLevel, char *pText, ...);

private:
	//friend class Adapter;

	int TempDestroy();
	int Restore();

	int SetDefaultRenderStates();

	IDirect3D9*			d3dInterface;

	IDirect3DSurface9*	d3dRenderTarget;
	IDirect3DSurface9*	d3dDepthStencil;

	Texture* textureList[512];
	IndexBuffer* indexBufferList[65535];
	VertexBuffer* vertexBufferList[65535];
	PixelShader* pixelShaderList[512];

	int textureListCount;
	int indexBufferListCount;
	int vertexBufferListCount;
	int pixelShaderListCount;

	//vector <Texture*> textureList;
	//vector <IndexBuffer*> indexBufferList;
	//vector <VertexBuffer*> vertexBufferList;
	//vector <VertexShader*> vertexShaderList;
	//vector <PixelShader*> pixelShaderList;

	D3DPRESENT_PARAMETERS d3dPPWindowed;
	D3DPRESENT_PARAMETERS d3dPPFullscreen;
	D3DDEVTYPE d3dDeviceType;
	DWORD d3dBehaviorFlags;
	DWORD d3dAdapter;

	D3DVIEWPORT9 viewportRender;
	D3DVIEWPORT9 viewportAll;

	HWND windowHandle;

	//Adapter adapter;

	//PYRAMID_DISPLAYMODE currentDisplayMode;

	bool timerHPSupported;

	DWORD timerLPStart;
	LARGE_INTEGER timerHPCounter;
	LARGE_INTEGER timerHPFrequency;
	LARGE_INTEGER timerHPStart;

	bool windowed;
	bool waitRetrace;

	DWORD zFunction;

	DWORD cullMode;
	DWORD d3dLighting;
	DWORD fogColor;

	BLEND_MODE blendMode;

	float fogStart;
	float fogEnd;
	float fogDensity;

	DWORD fogMode;
	bool fogPixel;
	bool fogRangeBased;

	int width, height;
};

#endif