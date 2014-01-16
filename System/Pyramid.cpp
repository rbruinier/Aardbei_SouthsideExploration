/*
	
	Pyramid System - Pyramid Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Pyramid.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
//#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "Matrix.h"
#include "Material.h"

#include "Stdio.h"
#include "Time.h"

// initialises common attributes
Pyramid::Pyramid()
{
	d3dInterface = NULL;
	d3dDevice    = NULL;
	windowHandle = NULL;

	windowed    = false;
	waitRetrace = false;

	fogColor = 0x0;

	textureListCount = 0;
	indexBufferListCount = 0;
	vertexBufferListCount = 0;
	pixelShaderListCount = 0;

	OpenLog();

	ResetTimer();
}

// destroys the Pyramid system class from memory
Pyramid::~Pyramid()
{
	CloseLog();
}

// generates adapter information (type, videomodes, etc)
//Adapter *Pyramid::GetAdapterInfo()
//{
//	if (d3dInterface != NULL)
//	{
//		return &adapter;
//	}
//	else
//	{
//		if (FAILED(d3dInterface = Direct3DCreate9(D3D_SDK_VERSION)))
//		{
//			ShowError("For this screensaver you need DirectX 9 installed on your system\n\nyou can download it at www.microsoft.com/directx/");
//			return NULL;
//		}
//
//		Adapter *retValue = NULL;
//
//
//		if (FAILED(adapter.GetAdapterInformation(d3dInterface, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL)))
//		{
//			ShowError("No supported 3D harware found");
//			return NULL;
//		}
//		else
//		{
//			retValue = &adapter;
//		}
//		
//		if (d3dInterface != NULL)
//		{
//			d3dInterface->Release();
//		}
//
//		return retValue;
//	}
//}

// initializes the Direct3D 9.0 interface with the given parameters
int Pyramid::InitSystem(HWND hWindowHandle, DWORD iWidth, DWORD iHeight, DWORD iVideoBPP, DWORD iInitParameters)
{
	windowHandle = hWindowHandle;

	//WriteLog(0, "<b>Initiliasing DirectX 9</b><br>");

	if (iInitParameters & SYS_WIN)
	{
		windowed = true;
	}

	if (iInitParameters & SYS_WVR)
	{
		waitRetrace = true;
	}

	width  = iWidth;
	height = iHeight;

	if (FAILED(d3dInterface = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		ShowError("For this screensaver you need DirectX 9 installed on your system\n\nyou can download it at www.microsoft.com/directx/");
		return E_FAIL;
	}

	//WriteLog(1, "DirectX 9 found<br>");

	d3dAdapter    = D3DADAPTER_DEFAULT;
	d3dDeviceType = D3DDEVTYPE_HAL;

	//WriteLog(1, "Retrieving information about display adapter(s)<br>");

	//if (FAILED(adapter.GetAdapterInformation(d3dInterface, d3dAdapter, d3dDeviceType)))
	//{
	//	ShowError("No supported 3D harware found");
	//	return E_FAIL;
	//}

	//PYRAMID_DISPLAYMODE displayMode;

	//if (FAILED(adapter.GetBestDisplayMode(displayMode, iWidth, iHeight, iVideoBPP)))
	//{
	//	if (!windowed)
	//	{
	//		ShowError("Unable to find a suitable fullscreen video mode");
	//		return E_FAIL;
	//	}
	//}

	//currentDisplayMode = displayMode;

	ZeroMemory(&d3dPPFullscreen, sizeof(d3dPPFullscreen));

	d3dPPFullscreen.BackBufferWidth  = iWidth;
	d3dPPFullscreen.BackBufferHeight = iHeight;
	d3dPPFullscreen.BackBufferFormat = D3DFMT_A8R8G8B8;//displayMode.d3dBackBufferFormat;
	d3dPPFullscreen.BackBufferCount  = 1;

	d3dPPFullscreen.MultiSampleType  = D3DMULTISAMPLE_NONMASKABLE;
	d3dPPFullscreen.MultiSampleQuality = 1;

	d3dPPFullscreen.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	d3dPPFullscreen.hDeviceWindow    = hWindowHandle;
	d3dPPFullscreen.Windowed         = false;
	d3dPPFullscreen.Flags            = 0;

	d3dPPFullscreen.EnableAutoDepthStencil          = true;
	d3dPPFullscreen.AutoDepthStencilFormat          = D3DFMT_D24S8;//displayMode.d3dZBufferFormat;
	d3dPPFullscreen.FullScreen_RefreshRateInHz      = D3DPRESENT_RATE_DEFAULT; //displayMode.d3dDisplayMode.RefreshRate;
	d3dPPFullscreen.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dPPWindowed = d3dPPFullscreen;

	d3dPPWindowed.Windowed         = true;

	//d3dPPWindowed.BackBufferWidth  = 0;
	//d3dPPWindowed.BackBufferHeight = 0;
	d3dPPWindowed.BackBufferFormat = D3DFMT_A8R8G8B8;//adapter.displayModeDesktop.d3dBackBufferFormat;

	d3dPPWindowed.FullScreen_RefreshRateInHz      = 0;
	d3dPPWindowed.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dPPWindowed.AutoDepthStencilFormat          = D3DFMT_D24S8;//adapter.displayModeDesktop.d3dZBufferFormat;

	if (waitRetrace)
	{
		d3dPPFullscreen.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}

	d3dBehaviorFlags = D3DCREATE_MULTITHREADED;

	//if (adapter.supportsHardwareTnL)
	//{
	//	if (adapter.supportsPointSprites)
	//	{
			d3dBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		/*}
		else
		{
			d3dBehaviorFlags |= D3DCREATE_MIXED_VERTEXPROCESSING;
		}
	}
	else
	{
		d3dBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}*/

	if (windowed)
	{
		//WriteLog(1, "Creating DirectX 9 Device (windowed)<br>");

		if (FAILED(d3dInterface->CreateDevice(d3dAdapter, 
			                                  d3dDeviceType, 
											  hWindowHandle, 
											  d3dBehaviorFlags, 
											  &d3dPPWindowed, 
											  &d3dDevice)))
		{
			ShowError("Failed to create DirectX 9 Device");
			return E_FAIL;
		}

		//currentDisplayMode = adapter.displayModeDesktop;
	}
	else
	{
		//WriteLog(1, "Creating DirectX 9 Device (fullscreen)<br>");

		if (FAILED(d3dInterface->CreateDevice(d3dAdapter, 
			                                  d3dDeviceType, 
											  hWindowHandle, 
											  d3dBehaviorFlags, 
											  &d3dPPFullscreen, 
											  &d3dDevice)))
		{
			ShowError("Failed to create DirectX 9 Device");
			return E_FAIL;
		}
	}

	SetDefaultRenderStates();

	if (FAILED(d3dDevice->GetRenderTarget(0, &d3dRenderTarget)))
	{
		ShowError("Failed to get render target");
		return E_FAIL;
	}

	if (FAILED(d3dDevice->GetDepthStencilSurface(&d3dDepthStencil)))
	{
		ShowError("Failed to get zbuffer surface");
		return E_FAIL;
	}

	viewportAll.X = 0; 
	viewportAll.Y = 0;
	viewportAll.Width = GetWidth();
	viewportAll.Height = GetHeight();
	viewportAll.MinZ = 0;
	viewportAll.MaxZ = 1;

	viewportRender = viewportAll;

	ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);
	ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);
	ClearBuffers(CLEAR_SCREEN | CLEAR_ZBUFFER, 0x0);

	//WriteLog(0, "<b>DirectX 9 is correctly initiliased</b><br><br>");

	return D3D_OK;
}

// destroys all created Direct3D buffers and interfaces
int Pyramid::Destroy()
{
	DWORD i;

	d3dRenderTarget->Release();
	d3dDepthStencil->Release();

	for (i = 0; i < vertexBufferListCount; i++)
	{
		vertexBufferList[i]->Destroy();

		delete vertexBufferList[i];
	}

	for (i = 0; i < indexBufferListCount; i++)
	{
		indexBufferList[i]->Destroy();

		delete indexBufferList[i];
	}

	for (i = 0; i < textureListCount; i++)
	{
		textureList[i]->Destroy();
		
		delete textureList[i];
	}

	//for (i = 0; i < vertexShaderList.size(); i++)
	//{
	//	vertexShaderList[i]->Destroy();

	//	delete vertexShaderList[i];
	//}

	for (i = 0; i < pixelShaderListCount; i++)
	{
		pixelShaderList[i]->Destroy();

		delete pixelShaderList[i];
	}

	if (d3dDevice != NULL)
	{
		d3dDevice->Release();
	}

	if (d3dInterface != NULL)
	{
		d3dInterface->Release();
	}

	return D3D_OK;
}

// shows an error message on the screen
void Pyramid::ShowError(char *pMessage)
{
	MessageBox(windowHandle, pMessage, "Screensaver Error", MB_OK);
}

// tells Direct3D to start a scene
int Pyramid::BeginScene()
{
	if (FAILED(d3dDevice->BeginScene()))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// tells Direct3D to end a scene
int Pyramid::EndScene()
{
	if (FAILED(d3dDevice->EndScene())) 
	{
		return E_FAIL;
	}

//	d3dDevice->SetViewport(&viewportAll);

	return D3D_OK;
}

// switch from windowed to fullscreen, and vicaversa
int Pyramid::SwitchFullscreen()
{
	TempDestroy();

	windowed = !windowed;

	if (windowed)
	{
		if (FAILED(d3dDevice->Reset(&d3dPPWindowed)))
		{
			ShowError("Failed to switch to windowed mode");
			return E_FAIL;
		}
	}
	else
	{
		if (FAILED(d3dDevice->Reset(&d3dPPFullscreen)))
		{
			ShowError("Failed to switch to fullscreen mode");
			return E_FAIL;
		}
	}

	Restore();

	return D3D_OK;
}

// sets some common Direct3D renderstate options
int Pyramid::SetDefaultRenderStates()
{
	for (int i = 0; i < 8; i++)
	{

		d3dDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		d3dDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		d3dDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}

	SetCullMode(CULL_CW);
	SetD3DLighting(true);

	return D3D_OK;
}

// destroys Direct3D buffers in the default pool, this is important when changing video mode
int Pyramid::TempDestroy()
{
	DWORD i;

	for (i = 0; i < vertexBufferListCount; i++)
	{
		VertexBuffer *vb = vertexBufferList[i];

		if (vb->pool == D3DPOOL_DEFAULT)
		{
			vb->TempDestroy();
		}
	}

	for (i = 0; i < indexBufferListCount; i++)
	{
		IndexBuffer *ib = indexBufferList[i];

		if (ib->pool == D3DPOOL_DEFAULT)
		{
			ib->TempDestroy();
		}
	}

	for (i = 0; i < textureListCount; i++)
	{
		Texture* texture = textureList[i];

		if (texture->pool == D3DPOOL_DEFAULT)
		{
			texture->TempDestroy();
		}
	}

	d3dRenderTarget->Release();
	d3dDepthStencil->Release();

	return D3D_OK;
}

// recreates all destroyed Direct3D buffers in the default pool
int Pyramid::Restore()
{
	DWORD i;

	for (i = 0; i < vertexBufferListCount; i++)
	{
		VertexBuffer *vb = vertexBufferList[i];

		if (vb->pool == D3DPOOL_DEFAULT)
		{
			if (FAILED(d3dDevice->CreateVertexBuffer(vb->size, 
				                                     vb->usage,
													 vb->fvf, 
													 vb->pool, 
													 &vb->d3dVertexBuffer,
													 NULL)))
			{
				ShowError("Failed to restore vertex buffer");
				return E_FAIL;
			}

			vb->Restore();
		}
	}

	for (i = 0; i < indexBufferListCount; i++)
	{
		IndexBuffer *ib = indexBufferList[i];

		if (ib->pool == D3DPOOL_DEFAULT)
		{
			if (FAILED(d3dDevice->CreateIndexBuffer(ib->size, 
				                                    ib->usage,
													ib->format, 
													ib->pool, 
													&ib->d3dIndexBuffer,
													NULL)))
			{
				ShowError("Failed to recreate index buffer");
				return E_FAIL;
			}

			ib->Restore();
		}
	}

	for (i = 0; i < textureListCount; i++)
	{
		Texture* texture = textureList[i];

		if (texture->pool == D3DPOOL_DEFAULT)
		{

			if (FAILED(d3dDevice->CreateTexture(texture->width, 
				                                texture->height,
												texture->levels,
												texture->usage,
												texture->format,
												texture->pool,
												&texture->d3dTexture,
												NULL)))
			{
				ShowError("Failed to recreate texture");
				return E_FAIL;
			}

			if (FAILED(d3dDevice->CreateDepthStencilSurface(texture->width, 
			                                                texture->height, 
															D3DFMT_D24S8,//currentDisplayMode.d3dZBufferFormat, 
															D3DMULTISAMPLE_NONE,
															0,
															true,
															&texture->d3dDepthStencil,
															NULL)))
			{
				ShowError("Failed to create render target zbuffer");
				return E_FAIL;
			}

			texture->Restore();
		}
	}

	SetDefaultRenderStates();

	SetRenderState(D3DRS_CULLMODE, cullMode);
	SetRenderState(D3DRS_LIGHTING, d3dLighting);
	SetTransparency(blendMode);

	SetFogColor(fogColor);
	SetFogRangeBased(fogRangeBased);

	switch (fogMode)
	{
	case D3DFOG_NONE:
		SetFogNone();
		break;
	case D3DFOG_LINEAR:
		SetFogLinear(fogStart, fogEnd, fogPixel);
		break;
	case D3DFOG_EXP:
		SetFogExp(fogDensity, fogPixel);
		break;
	case D3DFOG_EXP2:
		SetFogExp2(fogDensity, fogPixel);
		break;
	}

	if (FAILED(d3dDevice->GetRenderTarget(0, &d3dRenderTarget)))
	{
		ShowError("Failed to get render target");
		return E_FAIL;
	}

	if (FAILED(d3dDevice->GetDepthStencilSurface(&d3dDepthStencil)))
	{
		ShowError("Failed to get zbuffer surface");
		return E_FAIL;
	}

	return D3D_OK;
}

// clears zbuffer and/or backbuffer
int Pyramid::ClearBuffers(DWORD iClearParameters, DWORD iColor)
{
	DWORD parameters = 0;
	
	if (iClearParameters & CLEAR_ZBUFFER)
	{
		parameters |= D3DCLEAR_ZBUFFER;
	}

	if (iClearParameters & CLEAR_SCREEN)
	{
		parameters |= D3DCLEAR_TARGET;
	}

	if (FAILED(d3dDevice->Clear(0, NULL, parameters, iColor, 1.0f, 0))) 
	{
		ShowError("Failed to clear backbuffer and zbuffer");
		return E_FAIL;
	}

	return D3D_OK;
}

// updates the backbuffers and frontbuffer
int Pyramid::ShowBuffers()
{
	HRESULT result = d3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST)
	{
		result = d3dDevice->TestCooperativeLevel();

		if (result == D3DERR_DEVICENOTRESET) 
		{
			windowed = !windowed;

			SwitchFullscreen();
		} 
		else
		{
		} 
	}

	return D3D_OK;
}

// sets the given Direct3D renderstate
int Pyramid::SetRenderState(D3DRENDERSTATETYPE uiType, DWORD uiState) 
{
	if (FAILED(d3dDevice->SetRenderState(uiType, uiState)))
	{
		ShowError("Failed to set render state");
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the given Direct3D texture stage state
int Pyramid::SetTextureStageState(DWORD uiStage, D3DTEXTURESTAGESTATETYPE uiType, DWORD uiState)
{
	if (FAILED(d3dDevice->SetTextureStageState(uiStage, uiType, uiState)))
	{
		ShowError("Failed to set texture stage state");
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the given Direct3D texture sampler state
int Pyramid::SetSamplerState(DWORD uiStage, D3DSAMPLERSTATETYPE uiType, DWORD uiState)
{
	if (FAILED(d3dDevice->SetSamplerState(uiStage, uiType, uiState)))
	{
		ShowError("Failed to set sampler state");
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the current Direct3D view matrix
int Pyramid::SetViewMatrix(Matrix &pMatrix)
{
	if (FAILED(d3dDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&pMatrix)))
	{
		ShowError("Failed to set view matrix");
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the current Direct3D world matrix
int Pyramid::SetWorldMatrix(Matrix &pMatrix)
{
	if (FAILED(d3dDevice->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&pMatrix)))
	{
		ShowError("Failed to set world matrix");
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the current Direct3D projection matrix
int Pyramid::SetProjectionMatrix(Matrix &pMatrix)
{
	if (FAILED(d3dDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&pMatrix)))
	{
		ShowError("Failed to set projection matrix");
		return E_FAIL;
	}

	return D3D_OK;
}

// gets the current Direct3D view matrix
int Pyramid::GetViewMatrix(Matrix &pMatrix)
{
	if (FAILED(d3dDevice->GetTransform(D3DTS_VIEW, (D3DMATRIX*)&pMatrix)))
	{
		ShowError("Failed to get view matrix");
		return E_FAIL;
	}

	return D3D_OK;
}

// gets the current Direct3D world matrix
int Pyramid::GetWorldMatrix(Matrix &pMatrix)
{
	if (FAILED(d3dDevice->GetTransform(D3DTS_WORLD, (D3DMATRIX*)&pMatrix)))
	{
		ShowError("Failed to get world matrix");
		return E_FAIL;
	}

	return D3D_OK;
}

// gets the current Direct3D projection matrix
int Pyramid::GetProjectionMatrix(Matrix &pMatrix)
{
	if (FAILED(d3dDevice->GetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&pMatrix)))
	{
		ShowError("Failed to get projection matrix");
		return E_FAIL;
	}

	return D3D_OK;
}

// returns current render buffer width
int Pyramid::GetWidth()
{
	return width;
}

// returns current render buffer height
int Pyramid::GetHeight()
{
	return height;
}

// creates a vertex buffer with the given parameters and returns an interface to it
int Pyramid::CreateVertexBuffer(DWORD uiNrVertices, DWORD uiVertexSize, DWORD uiFVF, bool bDynamic, bool bPointSprites, VertexBuffer **pVertexBuffer)
{
	*pVertexBuffer = NULL;

	VertexBuffer *vb = new VertexBuffer();

	vb->size            = uiNrVertices * uiVertexSize;
	vb->vertexSize      = uiVertexSize;
	vb->fvf             = uiFVF;

	vb->usage |= D3DUSAGE_WRITEONLY;

	if (bDynamic)
	{
		vb->usage |= D3DUSAGE_DYNAMIC;
		vb->pool   = D3DPOOL_DEFAULT;
	}
	else
	{
		vb->pool = D3DPOOL_MANAGED;
	}

	if (bPointSprites)
	{
		vb->usage |= D3DUSAGE_POINTS;
	}

	//WriteLog(1, "Creating Vertex Buffer (size:%iB pool:%i dynamic:%i pointsprites:%i)<br>", vb->size, vb->pool, bDynamic, bPointSprites);

	if (FAILED(d3dDevice->CreateVertexBuffer(vb->size, 
		                                     vb->usage,
											 vb->fvf, 
											 vb->pool, 
											 &vb->d3dVertexBuffer,
											 NULL)))
	{
		ShowError("Failed to create vertex buffer");
		return E_FAIL;
	}

	//vertexBufferList.push_back(vb);
	vertexBufferList[vertexBufferListCount++] = vb;

	*pVertexBuffer = vb;

	return D3D_OK;
}

// creates a index buffer with the given parameters and returns an interface to it
int Pyramid::CreateIndexBuffer(DWORD uiNrFaces, bool b32Bit, bool bDynamic, IndexBuffer **pIndexBuffer)
{
	*pIndexBuffer = NULL;

	IndexBuffer *ib = new IndexBuffer();

	if (b32Bit)
	{
		ib->size   = uiNrFaces * 12;
		ib->format = D3DFMT_INDEX32;
	}
	else
	{
		ib->size   = uiNrFaces * 6;
		ib->format = D3DFMT_INDEX16;
	}

	ib->usage |= D3DUSAGE_WRITEONLY;

	if (bDynamic)
	{
		ib->usage |= D3DUSAGE_DYNAMIC;
		ib->pool   = D3DPOOL_DEFAULT;
	}
	else
	{
		ib->pool = D3DPOOL_MANAGED;
	}

	//WriteLog(1, "Creating Index Buffer (size:%iB pool:%i dynamic:%i)<br>", ib->size, ib->pool, bDynamic);

	if (FAILED(d3dDevice->CreateIndexBuffer(ib->size, 
		                                    ib->usage,
											ib->format, 
											ib->pool, 
											&ib->d3dIndexBuffer,
											NULL)))
	{
		ShowError("Failed to create index buffer");
		return E_FAIL;
	}

	//indexBufferList.push_back(ib);
	indexBufferList[indexBufferListCount++] = ib;

	*pIndexBuffer = ib;

	return D3D_OK;
}
//
//int Pyramid::CreateVertexShader(DWORD *pSource, D3DVERTEXELEMENT9 *pDecl, VertexShader **pVertexShader)
//{
//	*pVertexShader = NULL;
//
//	VertexShader *vs = new VertexShader();
//
//	if (FAILED(d3dDevice->CreateVertexDeclaration(pDecl, &vs->d3dVertexDeclaration)))
//	{
//		ShowError("Failed to create vertex declaration");
//		return E_FAIL;
//    }
//
//	if (FAILED(d3dDevice->CreateVertexShader(pSource, &vs->d3dVertexShader)))
//	{
//		ShowError("Failed to create vertex shader");
//		return E_FAIL;
//	}
//
////	vertexShaderList.push_back(vs);
//
//	*pVertexShader = vs;
//
//	return D3D_OK;
//}

int Pyramid::CreatePixelShader(DWORD *pSource, PixelShader **pPixelShader)
{
	*pPixelShader = NULL;

	PixelShader *ps = new PixelShader();

	if (FAILED(d3dDevice->CreatePixelShader(pSource, &ps->d3dPixelShader)))
	{
		ShowError("Failed to create pixel shader");
		return E_FAIL;
	}

	//pixelShaderList.push_back(ps);
	pixelShaderList[pixelShaderListCount++] = ps;

	*pPixelShader = ps;

	return D3D_OK;
}


// sets the current Direct3D vertex buffer
int Pyramid::SetVertexStream(VertexBuffer *pVertexBuffer, int nStreamNumber)
{
	if (pVertexBuffer == NULL)
	{
		if (FAILED(d3dDevice->SetStreamSource(nStreamNumber, NULL, 0, 0)))
		{
			ShowError("Failed to reset vertex stream source");
			return E_FAIL;
		}
		return D3D_OK;
	}

	if (FAILED(d3dDevice->SetStreamSource(nStreamNumber, pVertexBuffer->d3dVertexBuffer, 0, pVertexBuffer->vertexSize)))
	{
		ShowError("Failed to set vertex stream source");
		return E_FAIL;
	}

	if (FAILED(d3dDevice->SetFVF(pVertexBuffer->fvf)))
	{
		ShowError("Failed to set vertex shader");
		return E_FAIL;
	}

	if (pVertexBuffer->fvf != 0)
	{
		if (FAILED(d3dDevice->SetVertexShader(NULL)))
		{
			ShowError("Failed to reset vertex shader");
			return E_FAIL;
		}
	}

	return D3D_OK;
}

// sets the current Direct3D index buffer
int Pyramid::SetIndexStream(IndexBuffer *pIndexBuffer)
{
	if (pIndexBuffer == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(d3dDevice->SetIndices(pIndexBuffer->d3dIndexBuffer)))
	{
		ShowError("Failed to set index stream source");
		return E_FAIL;
	}

	return D3D_OK;
}

//
//int Pyramid::SetVertexShader(VertexShader *pVertexShader)
//{
//	if (pVertexShader == NULL)
//	{
//		if (FAILED(d3dDevice->SetVertexShader(NULL)))
//		{
//			ShowError("Failed to reset vertex shader");
//			return E_FAIL;
//		}
//
//		return D3D_OK;
//	}
//
//	if (FAILED(d3dDevice->SetVertexDeclaration(pVertexShader->d3dVertexDeclaration)))
//	{
//		ShowError("Failed to set vertex declaration");
//		return E_FAIL;
//	}
//
//	if (FAILED(d3dDevice->SetVertexShader(pVertexShader->d3dVertexShader)))
//	{
//		ShowError("Failed to set vertex shader");
//		return E_FAIL;
//	}
//
//	return D3D_OK;
//}
//
//int Pyramid::SetVertexShaderConstantF(DWORD uiStartReg, float *pData, DWORD uiNrVectors)
//{
//	return d3dDevice->SetVertexShaderConstantF(uiStartReg, pData, uiNrVectors);
//}
//
//int Pyramid::SetVertexShaderConstantB(DWORD uiStartReg, BOOL *pData, DWORD uiNrBooleans)
//{
//	return d3dDevice->SetVertexShaderConstantB(uiStartReg, pData, uiNrBooleans);
//}
//
//int Pyramid::SetVertexShaderConstantI(DWORD uiStartReg, int *pData, DWORD uiNrVectors)
//{
//	return d3dDevice->SetVertexShaderConstantI(uiStartReg, pData, uiNrVectors);
//}

int Pyramid::SetPixelShader(PixelShader *pPixelShader)
{
	if (pPixelShader == NULL)
	{
		if (FAILED(d3dDevice->SetPixelShader(NULL)))
		{
			ShowError("Failed to reset pixel shader");
			return E_FAIL;
		}

		return D3D_OK;
	}

	if (FAILED(d3dDevice->SetPixelShader(pPixelShader->d3dPixelShader)))
	{
		ShowError("Failed to set pixel shader");
		return E_FAIL;
	}

	return D3D_OK;
}

int Pyramid::SetPixelShaderConstantF(DWORD uiStartReg, float *pData, DWORD uiNrVectors)
{
	return d3dDevice->SetPixelShaderConstantF(uiStartReg, pData, uiNrVectors);
}

int Pyramid::SetPixelShaderConstantB(DWORD uiStartReg, BOOL *pData, DWORD uiNrBooleans)
{
	return d3dDevice->SetPixelShaderConstantB(uiStartReg, pData, uiNrBooleans);
}

int Pyramid::SetPixelShaderConstantI(DWORD uiStartReg, int *pData, DWORD uiNrVectors)
{
	return d3dDevice->SetPixelShaderConstantI(uiStartReg, pData, uiNrVectors);
}

// renders the given indexed primitive list
int Pyramid::DrawIndexedPrimitiveList(DWORD uiMinIndex, DWORD uiNrVertices, DWORD uiStartIndex, DWORD uiNrPrimitives)
{
	if (FAILED(d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, uiMinIndex, uiNrVertices, uiStartIndex, uiNrPrimitives)))
	{
		return E_FAIL;
	}

	return D3D_OK;
};

// renders the given primitive list
int Pyramid::DrawPrimitiveList(DWORD uiMinIndex, DWORD uiNrPrimitives)
{
	if (FAILED(d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, uiMinIndex, uiNrPrimitives)))
	{
		return E_FAIL;
	}

	return D3D_OK;
};

// renders the given primitive strip
int Pyramid::DrawPrimitiveStrip(DWORD uiMinIndex, DWORD uiNrPrimitives)
{
	if (FAILED(d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, uiMinIndex, uiNrPrimitives)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// renders the given primitive fan
int Pyramid::DrawPrimitiveFan(DWORD uiMinIndex, DWORD uiNrPrimitives)
{
	if (FAILED(d3dDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, uiMinIndex, uiNrPrimitives)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// renders the given line list
int Pyramid::DrawLineList(DWORD uiMinIndex, DWORD uiNrLines)
{
	if (FAILED(d3dDevice->DrawPrimitive(D3DPT_LINELIST, uiMinIndex, uiNrLines)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// renders the given line strip
int Pyramid::DrawLineStrip(DWORD uiMinIndex, DWORD uiNrLines)
{
	if (FAILED(d3dDevice->DrawPrimitive(D3DPT_LINESTRIP, uiMinIndex, uiNrLines)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// renders the given points
int Pyramid::DrawPointList(DWORD uiMinIndex, DWORD uiNrVertices)
{
	if (FAILED(d3dDevice->DrawPrimitive(D3DPT_POINTLIST, uiMinIndex, uiNrVertices)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// creates a texture buffer with the given parameters and returns an interface to it
int Pyramid::CreateTexture(DWORD uiWidth, DWORD uiHeight, DWORD iBPP, bool bMipMap, bool bDynamic, bool bRenderTarget, 
		Texture **pTexture, bool bMultisample)
{
	*pTexture = NULL;

	Texture *texture = new Texture();

	texture->width  = uiWidth;
	texture->height = uiHeight;
	texture->size   = uiWidth * uiHeight;
	texture->levels = 1;
	texture->usage  = 0;
	texture->bpp    = iBPP;
	texture->pool   = D3DPOOL_MANAGED;
	texture->format = D3DFMT_UNKNOWN;

	texture->multisample = bMultisample;

	if (bMipMap && bRenderTarget)
	{
		ShowError("Invalid parameters given for texture creation");
		return E_FAIL;
	}

	//if (iBPP == 32)
	//{
	//	if (currentDisplayMode.d3dTextureFormat32 != D3DFMT_UNKNOWN)
	//	{
			texture->format = D3DFMT_A8R8G8B8;//currentDisplayMode.d3dTextureFormat32;
		/*}
		else
		{
			texture->format = currentDisplayMode.d3dTextureFormat16;
		}
	}
	else
	{
		if (currentDisplayMode.d3dTextureFormat16 != D3DFMT_UNKNOWN)
		{
			texture->format = currentDisplayMode.d3dTextureFormat16;
		}
		else
		{
			texture->format = currentDisplayMode.d3dTextureFormat32;
		}
	}*/

	if (bMipMap)
	{
		texture->levels = 0;
	}

	if (bDynamic)
	{
	}

	if (texture->format == D3DFMT_UNKNOWN)
	{
		ShowError("Failed to find format for texture");
		return E_FAIL;
	}

	if (bRenderTarget)
	{
		DWORD multiSampleType    = D3DMULTISAMPLE_NONE;
		DWORD multiSampleQuality = 0;

		//if (bMultisample)
		//{
		//	multiSampleType    = d3dPPFullscreen.MultiSampleType;
		//	multiSampleQuality = d3dPPFullscreen.MultiSampleQuality;
		//}

		texture->usage  = D3DUSAGE_RENDERTARGET;
		texture->pool   = D3DPOOL_DEFAULT;
		texture->format = D3DFMT_A8R8G8B8;//currentDisplayMode.d3dBackBufferFormat;

		if (FAILED(d3dDevice->CreateDepthStencilSurface(texture->width, 
		                                                texture->height, 
														D3DFMT_D24S8,//currentDisplayMode.d3dZBufferFormat, 
														(D3DMULTISAMPLE_TYPE)multiSampleType,
														multiSampleQuality,
														true,
														&texture->d3dDepthStencil,
														NULL)))
		{
			ShowError("Failed to create render target zbuffer");
			return E_FAIL;
		}

		//if (bMultisample)
		//{
		//	if (FAILED(d3dDevice->CreateRenderTarget(texture->width, 
		//                                             texture->height, 
		//										     this->d3dPPFullscreen.BackBufferFormat, 
		//											 (D3DMULTISAMPLE_TYPE)multiSampleType,
		//											 multiSampleQuality,
		//											 false,
		//											 &texture->d3dSurface,
		//											 NULL)))
		//	{
		//		ShowError("Failed to create render target multisample surface");
		//		return E_FAIL;
		//	}
		//}
	}

	//WriteLog(1, "Creating Texture Surface (width:%i height:%i levels:%i rendertarget:%i dynamic:%i)<br>", texture->width, texture->height, texture->levels, bRenderTarget, bDynamic);

	if (FAILED(d3dDevice->CreateTexture(texture->width, 
		                                texture->height,
										texture->levels,
										texture->usage,
										texture->format,
										texture->pool,
										&texture->d3dTexture,
										NULL)))
	{
		ShowError("Failed to create texture");
		return E_FAIL;
	}

	texture->localData = new DWORD[texture->size];

	//textureList.push_back(texture);
	textureList[textureListCount++] = texture;

	*pTexture = texture;

	return D3D_OK;
}

// sets the current Direct3D texture
int Pyramid::SetTexture(Texture *pTexture, DWORD uiStage)
{
	if (pTexture == NULL)
	{
		if (FAILED(d3dDevice->SetTexture(uiStage, NULL)))
		{
			ShowError("Failed to show texture");
			return E_FAIL;
		}
		else
		{
			return D3D_OK;
		}
	}

	if (FAILED(d3dDevice->SetTexture(uiStage, pTexture->d3dTexture)))
	{
		ShowError("Failed to show texture");
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the current Direct3D fog mode to LINEAR mode
int Pyramid::SetFogLinear(float fStart, float fEnd, bool pixel)
{
	fogMode  = D3DFOG_LINEAR;
	fogStart = fStart;
	fogEnd   = fEnd;

	SetRenderState(D3DRS_FOGENABLE, true);
	SetRenderState(D3DRS_FOGSTART, *(DWORD*) (&fStart));
	SetRenderState(D3DRS_FOGEND,   *(DWORD*) (&fEnd));

	if (pixel)
	{
		fogPixel = true;
		SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_LINEAR);
		SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	}
	else
	{
		fogPixel = false;
		SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_NONE);
		SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
	}

	return D3D_OK;
}

// sets the current Direct3D fog mode to EXP mode
int Pyramid::SetFogExp(float fDensity, bool pixel)
{
	fogMode    = D3DFOG_EXP;
	fogDensity = fDensity;

	SetRenderState(D3DRS_FOGENABLE, true);
	SetRenderState(D3DRS_FOGDENSITY, *(DWORD*) (&fDensity));

	if (pixel)
	{
		fogPixel = true;
		SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_EXP);
		SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	}
	else
	{
		fogPixel = false;
		SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_NONE);
		SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_EXP);
	}

	return D3D_OK;
}

// sets the current Direct3D fog mode to EXP2 mode
int Pyramid::SetFogExp2(float fDensity, bool pixel)
{
	fogMode    = D3DFOG_EXP2;
	fogDensity = fDensity;

	SetRenderState(D3DRS_FOGENABLE, true);
	SetRenderState(D3DRS_FOGDENSITY, *(DWORD*) (&fDensity));

	if (pixel)
	{
		fogPixel = true;
		SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_EXP2);
		SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	}
	else
	{
		fogPixel = false;
		SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_NONE);
		SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_EXP2);
	}

	return D3D_OK;
}

// disables Direct3D fog
int Pyramid::SetFogNone()
{
	fogMode = D3DFOG_NONE;

	SetRenderState(D3DRS_FOGENABLE, false);

	SetRenderState(D3DRS_FOGTABLEMODE,  D3DFOG_NONE);
	SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);

	return D3D_OK;
}

// sets the current fog color
int Pyramid::SetFogColor(DWORD uiColor)
{
	fogColor = uiColor;

	return SetRenderState(D3DRS_FOGCOLOR,  fogColor);
}

// enables/disables Direct3D range based fog (a bit slower, but nicer)
int Pyramid::SetFogRangeBased(bool bEnabled)
{
	fogRangeBased = bEnabled;

	return SetRenderState(D3DRS_RANGEFOGENABLE, bEnabled);
}

// sets the current Direct3D cull mode
int Pyramid::SetCullMode(CULL_MODE uiCullMode)
{
	cullMode = uiCullMode;

	return SetRenderState(D3DRS_CULLMODE, uiCullMode);
}

// sets transparency setting
int Pyramid::SetTransparency(BLEND_MODE uiBlendMode)
{
	blendMode = uiBlendMode;

	switch (blendMode)
	{
	case BLEND_NONE:
		SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		break;
	case BLEND_ADD:
		SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case BLEND_SUBTRACT:
		SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_ZERO);
		SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
		SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		break;
	case BLEND_MODULATE:
		SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		// NOG NIET COMPLEET !!!
		break;
	case BLEND_ALPHA:
		SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		break;
	case BLEND_INVERT:
		SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_INVDESTCOLOR );
		SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		break;
	}

	return D3D_OK;
}

int Pyramid::SetViewport(RECT &pRect)
{
	viewportRender.X = pRect.left;
	viewportRender.Y = pRect.top;

	viewportRender.Width  = pRect.right - pRect.left;
	viewportRender.Height = pRect.bottom - pRect.top;

	viewportRender.MinZ = 0;
	viewportRender.MaxZ = 1;

	d3dDevice->SetViewport(&viewportRender);

	return D3D_OK;
}

int Pyramid::GetViewport(RECT &pRect)
{
	pRect.left  = viewportRender.X;
	pRect.right = viewportRender.X + viewportRender.Width;

	pRect.top    = viewportRender.Y;
	pRect.bottom = viewportRender.Y + viewportRender.Height;

	return D3D_OK;
}
//
//Texture* tempRenderTarget;
//IDirect3DSurface9* d3dRenderTarget2 = NULL;

int Pyramid::SetRenderTarget(Texture* pTexture)
{
	//tempRenderTarget = pTexture;

	//if (!pTexture->multisample)
	//{
		IDirect3DSurface9* surface = NULL;

		if (FAILED(pTexture->d3dTexture->GetSurfaceLevel(0, &surface)))
		{
			return E_FAIL;
		}

		if (FAILED(d3dDevice->SetRenderTarget(0, surface)))
		{
			return E_FAIL;
		}

		surface->Release();
	//}
	//else
	//{

		//if (d3dRenderTarget2 == NULL)
		//{
		//	if (FAILED(d3dDevice->GetBackBuffer(0, 1, D3DBACKBUFFER_TYPE_MONO, &d3dRenderTarget2)))
		//{
		//	ShowError("Failed to get render target");
		//		return E_FAIL;
		//	}
		//}

	//	if (FAILED(d3dDevice->SetRenderTarget(0, pTexture->d3dSurface)))
	//	{
	//		this->ShowError("Failed to set render target");
	//		return E_FAIL;
	//	}
	//}

	if (FAILED(d3dDevice->SetDepthStencilSurface(pTexture->d3dDepthStencil)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

int Pyramid::ResetRenderTarget()
{
	if (FAILED(d3dDevice->SetRenderTarget(0, d3dRenderTarget)))
	{
		ShowError("Failed to reset render target");
		return E_FAIL;
	}

	if (FAILED(d3dDevice->SetDepthStencilSurface(d3dDepthStencil)))
	{
		ShowError("Failed to reset depth stencil buffer");
		return E_FAIL;
	}

	d3dDevice->SetViewport(&viewportRender);

	//if (tempRenderTarget->multisample)
	//{
	//	IDirect3DSurface9* surface = NULL;

	//	if (FAILED(tempRenderTarget->d3dTexture->GetSurfaceLevel(0, &surface)))
	//	{
	//		return E_FAIL;
	//	}

	//	if (FAILED(d3dDevice->StretchRect(
	//		d3dRenderTarget, NULL,
	//		surface, NULL,
	//		D3DTEXF_LINEAR)))
	//	{
	//		ShowError("Failed to reset depth stencil buffer");
	//		return E_FAIL;
	//	}

	//	surface->Release();
	//}

	return D3D_OK;
}

// enables/disables Direct3D lighting engine
int Pyramid::SetD3DLighting(bool bEnabled)
{
	d3dLighting = bEnabled;

	return SetRenderState(D3DRS_LIGHTING, bEnabled);
}

// sets the current Direct3D material
int Pyramid::SetMaterial(Material &pMaterial)
{
	if (FAILED(d3dDevice->SetMaterial((D3DMATERIAL9*)&pMaterial)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// sets the light properties of the given light index
int Pyramid::SetLight(Light &pLight, DWORD uiIndex)
{
	if (FAILED(d3dDevice->SetLight(uiIndex, (D3DLIGHT9*)&pLight)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// enables/disables a Direct3D light on the given index
int Pyramid::SetLightEnable(DWORD uiIndex, bool bEnabled)
{
	if (FAILED(d3dDevice->LightEnable(uiIndex, bEnabled)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// enables/disables writing to zbuffer
int Pyramid::SetWriteZBufferEnable(bool bEnabled)
{
	if (FAILED(d3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, bEnabled)))
	{
		return E_FAIL;
	}

	return D3D_OK;
}

// enables/disables Direct3D point sprite rendering
int Pyramid::SetPointSpriteEnable(bool bEnabled)
{
	if (bEnabled)
	{
		float zero = 0, one = 1;

		SetRenderState(D3DRS_POINTSPRITEENABLE, true);
		SetRenderState(D3DRS_POINTSCALEENABLE,  true);

		SetRenderState(D3DRS_POINTSIZE_MIN, *((DWORD*) &zero));
		SetRenderState(D3DRS_POINTSCALE_A,  *((DWORD*) &zero));
		SetRenderState(D3DRS_POINTSCALE_B,  *((DWORD*) &zero));
		SetRenderState(D3DRS_POINTSCALE_C,  *((DWORD*) &one));
	}
	else
	{
		SetRenderState(D3DRS_POINTSPRITEENABLE, false);
		SetRenderState(D3DRS_POINTSCALEENABLE,  false);
	}

	return D3D_OK;
}

// sets point sprite size
int Pyramid::SetPointSpriteSize(float fSize)
{
	SetRenderState(D3DRS_POINTSIZE, *(DWORD*) &fSize);

	return D3D_OK;
}

// enabled/disables 2D rendering
int Pyramid::Set2DEnable(bool bEnabled)
{
	if (bEnabled)
	{
		if (FAILED(d3dDevice->GetRenderState(D3DRS_ZFUNC, &zFunction)))
		{
			return E_FAIL;
		}

		SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		SetRenderState(D3DRS_ZWRITEENABLE, false);

		SetRenderState(D3DRS_LIGHTING, false);

		SetRenderState(D3DRS_CULLMODE, CULL_NONE);

		SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		SetFogNone();
	}
	else
	{
		SetRenderState(D3DRS_ZFUNC, zFunction);
		SetRenderState(D3DRS_ZWRITEENABLE, true);

		SetRenderState(D3DRS_LIGHTING, true);
	}

	return D3D_OK;
}

// sets the ambient light level
int Pyramid::SetAmbientLight(DWORD uiColor)
{
	return SetRenderState(D3DRS_AMBIENT, uiColor);
}

// resets timer (uses high precision timer when available)
void Pyramid::ResetTimer()
{
	if (QueryPerformanceCounter(&timerHPStart))
	{
		timerHPSupported = true;

		QueryPerformanceFrequency(&timerHPFrequency);
	}
	else
	{
		timerHPSupported = false;

		timerLPStart = timeGetTime();
	}
}

// gets current timer value (timer runs at 1000 HZ)
DWORD Pyramid::GetTimer()
{
	if (timerHPSupported)
	{
		QueryPerformanceCounter(&timerHPCounter);

		return (DWORD) (((timerHPCounter.QuadPart - timerHPStart.QuadPart) / (float)timerHPFrequency.QuadPart) * 1000.f);
	}
	else
	{
		return timeGetTime() - timerLPStart;
	}
}

void Pyramid::OpenLog()
{/*
	FILE *logfile;

	logfile = fopen(LOG_FILENAME, "w+");

	fprintf(logfile, "<html><head><title>%s</title></head><body><font face=""tahoma"" size=""1"">", LOG_TITLE);

	time_t ltime = time(&ltime);
	fprintf(logfile, "<br><b>log opened on %s</b><br><br>", ctime(&ltime));

	fclose(logfile);*/
}

void Pyramid::CloseLog()
{	/*
	FILE *logfile;

	logfile = fopen(LOG_FILENAME, "a+");

	time_t ltime = time(&ltime);
	fprintf(logfile, "<br><b>log stopped on %s</b>", ctime(&ltime));

	fprintf(logfile, "</font><body></html>");

	fclose(logfile);*/
}

void Pyramid::WriteLog(int iLevel, char *pText, ...)
{/*
	FILE *logfile;

	logfile = fopen(LOG_FILENAME, "a+");

	for (int i = 0; i < iLevel; i++)
	{
		fprintf(logfile, "&nbsp;&nbsp;&nbsp;");
	}

	char buffer[800];
	va_list argptr;
	va_start(argptr, pText) ;
	vsprintf(buffer, pText, argptr );

	fprintf(logfile, buffer);

	fclose(logfile);*/
}
