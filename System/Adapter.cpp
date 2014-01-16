/*
	
	Pyramid System - (Display) Adapter Class


	2006, Robert Jan Bruinier (rob / aardbei)

*/

#include "Adapter.h"

#include "Pyramid.h"

extern Pyramid *pyramid;

// initiliases common attributes
Adapter::Adapter()
{
}

// destroys the object
Adapter::~Adapter()
{
}

// creates a profile of the current 3D hardware available (videomodes, hwTnL, etc)
int Adapter::GetAdapterInformation(IDirect3D9 *pD3DInterface, DWORD iD3DAdapter, D3DDEVTYPE iD3DDeviceType)
{
	int i;

	D3DDISPLAYMODE d3dDisplayMode;
	
	d3dAdapter    = iD3DAdapter;
	d3dDeviceType = iD3DDeviceType;

	if (FAILED(pD3DInterface->GetAdapterIdentifier(d3dAdapter, 0, &d3dAdapterIdentifier)))
	{
		MessageBox(NULL, "pD3DInterface->GetAdapterIdentifier(d3dAdapter, 0, &d3dAdapterIdentifier)", "Error - DEBUG", MB_OK);
		return E_FAIL;
	}

	driver = d3dAdapterIdentifier.Driver;
	description = d3dAdapterIdentifier.Description;

//	pyramid->WriteLog(2, "<b>%s</b><br>", description);

	// get current desktop video mode

	if (FAILED(pD3DInterface->GetAdapterDisplayMode(d3dAdapter, &d3dDisplayMode)))
	{
		MessageBox(NULL, "pD3DInterface->GetAdapterDisplayMode(d3dAdapter, &d3dDisplayMode)", "Error - DEBUG", MB_OK);
		return E_FAIL;
	}

	displayModeDesktop.d3dDisplayMode = d3dDisplayMode;
	displayModeDesktop.videoBPP       = GetBPPFromD3DFormat(d3dDisplayMode.Format);
	displayModeDesktop.number         = 0;

	if (FAILED(FindFormats(pD3DInterface, displayModeDesktop)))
	{
		MessageBox(NULL, "FindFormats(pD3DInterface, displayModeDesktop)", "Error - DEBUG", MB_OK);
		return E_FAIL;
	}

	if (FAILED(pD3DInterface->CheckDeviceType(d3dAdapter, 
	                                          d3dDeviceType,
					   						  displayModeDesktop.d3dDisplayMode.Format,
					 						  displayModeDesktop.d3dBackBufferFormat,
											  true)))
	{
		MessageBox(NULL, "CheckDeviceType(d3dAdapter, d3dDeviceType, displayModeDesktop.d3dDisplayMode.Format, displayModeDesktop.d3dBackBufferFormat, true)", "Error - DEBUG", MB_OK);
		return E_FAIL;
	}

	//pyramid->WriteLog(3, "windowed:<br>");
	//pyramid->WriteLog(4, "video mode: %ix%ix%i (%i HZ, zb:%i bb:%i t16:%i t32:%i)<br>", 
	//	              displayModeDesktop.d3dDisplayMode.Width, displayModeDesktop.d3dDisplayMode.Height, 
	//				  displayModeDesktop.videoBPP, displayModeDesktop.d3dDisplayMode.RefreshRate,
	//				  displayModeDesktop.d3dZBufferFormat, displayModeDesktop.d3dBackBufferFormat,
	//				  displayModeDesktop.d3dTextureFormat16, displayModeDesktop.d3dTextureFormat32);
	
	// get all available modes

	//pyramid->WriteLog(3, "fullscreen:<br>");

	int nr16BitVideoModes = pD3DInterface->GetAdapterModeCount(d3dAdapter, D3DFMT_R5G6B5);
	//pyramid->WriteLog(4, "nr of video modes (16 bit): %i<br>", nr16BitVideoModes);

	int nr32BitVideoModes = pD3DInterface->GetAdapterModeCount(d3dAdapter, D3DFMT_X8R8G8B8);
	//pyramid->WriteLog(4, "nr of video modes (32 bit): %i<br>", nr32BitVideoModes);
 
	for (i = 0; i < nr16BitVideoModes; i++)
	{
		if (FAILED(pD3DInterface->EnumAdapterModes(d3dAdapter, D3DFMT_R5G6B5, i, &d3dDisplayMode)))
		{
			MessageBox(NULL, "pD3DInterface->EnumAdapterModes(d3dAdapter, i, &d3dDisplayMode)", "Error - DEBUG", MB_OK);
			return E_FAIL;
		}

		PYRAMID_DISPLAYMODE displayMode;

		displayMode.d3dDisplayMode = d3dDisplayMode;
		displayMode.videoBPP       = GetBPPFromD3DFormat(d3dDisplayMode.Format);
		displayMode.number         = i;

		if (FAILED(FindFormats(pD3DInterface, displayMode)))
		{
			//pyramid->WriteLog(4, "NO FORMAT: video mode: %ix%ix%i<br>", 
							  //d3dDisplayMode.Width, d3dDisplayMode.Height, displayMode.videoBPP);
			continue;
		}

		if (!FAILED(pD3DInterface->CheckDeviceType(d3dAdapter, 
												  d3dDeviceType,
					   							  displayMode.d3dDisplayMode.Format,
					 							  displayMode.d3dBackBufferFormat,
												  false)))
		{
			/*pyramid->WriteLog(4, "video mode: %ix%ix%i (%i HZ, zb:%i bb:%i t16:%i t32:%i)<br>", 
				              displayMode.d3dDisplayMode.Width, displayMode.d3dDisplayMode.Height, 
							  displayMode.videoBPP, displayMode.d3dDisplayMode.RefreshRate,
							  displayMode.d3dZBufferFormat, displayMode.d3dBackBufferFormat,
							  displayMode.d3dTextureFormat16, displayMode.d3dTextureFormat32);*/

			displayModeList.push_back(displayMode);
		}
		else
		{
			/*pyramid->WriteLog(4, "NOT OK: video mode: %ix%ix%i (%i HZ, zb:%i bb:%i t16:%i t32:%i)<br>", 
				              displayMode.d3dDisplayMode.Width, displayMode.d3dDisplayMode.Height, 
							  displayMode.videoBPP, displayMode.d3dDisplayMode.RefreshRate,
							  displayMode.d3dZBufferFormat, displayMode.d3dBackBufferFormat,
							  displayMode.d3dTextureFormat16, displayMode.d3dTextureFormat32);*/
		}
	}

	for (i = 0; i < nr32BitVideoModes; i++)
	{
		if (FAILED(pD3DInterface->EnumAdapterModes(d3dAdapter, D3DFMT_X8R8G8B8, i, &d3dDisplayMode)))
		{
			MessageBox(NULL, "pD3DInterface->EnumAdapterModes(d3dAdapter, i, &d3dDisplayMode)", "Error - DEBUG", MB_OK);
			return E_FAIL;
		}

		PYRAMID_DISPLAYMODE displayMode;

		displayMode.d3dDisplayMode = d3dDisplayMode;
		displayMode.videoBPP       = GetBPPFromD3DFormat(d3dDisplayMode.Format);
		displayMode.number         = i;

		if (FAILED(FindFormats(pD3DInterface, displayMode)))
		{
		/*	pyramid->WriteLog(4, "NO FORMAT: video mode: %ix%ix%i<br>", 
							  d3dDisplayMode.Width, d3dDisplayMode.Height, displayMode.videoBPP);*/
			continue;
		}

		if (!FAILED(pD3DInterface->CheckDeviceType(d3dAdapter, 
												  d3dDeviceType,
					   							  displayMode.d3dDisplayMode.Format,
					 							  displayMode.d3dBackBufferFormat,
												  false)))
		{
	/*		pyramid->WriteLog(4, "video mode: %ix%ix%i (%i HZ, zb:%i bb:%i t16:%i t32:%i)<br>", 
				              displayMode.d3dDisplayMode.Width, displayMode.d3dDisplayMode.Height, 
							  displayMode.videoBPP, displayMode.d3dDisplayMode.RefreshRate,
							  displayMode.d3dZBufferFormat, displayMode.d3dBackBufferFormat,
							  displayMode.d3dTextureFormat16, displayMode.d3dTextureFormat32);*/

			displayModeList.push_back(displayMode);
		}
		else
		{
			//pyramid->WriteLog(4, "NOT OK: video mode: %ix%ix%i (%i HZ, zb:%i bb:%i t16:%i t32:%i)<br>", 
			//	              displayMode.d3dDisplayMode.Width, displayMode.d3dDisplayMode.Height, 
			//				  displayMode.videoBPP, displayMode.d3dDisplayMode.RefreshRate,
			//				  displayMode.d3dZBufferFormat, displayMode.d3dBackBufferFormat,
			//				  displayMode.d3dTextureFormat16, displayMode.d3dTextureFormat32);
		}
	}

	D3DCAPS9 d3dCaps;

	if (FAILED(pD3DInterface->GetDeviceCaps(d3dAdapter, iD3DDeviceType, &d3dCaps)))
	{
		MessageBox(NULL, "pD3DInterface->GetDeviceCaps(d3dAdapter, iD3DDeviceType, &d3dCaps)", "Error - DEBUG", MB_OK);
		return E_FAIL;
	}

	if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		supportsHardwareTnL = true;

		if (d3dCaps.DevCaps & D3DDEVCAPS_PUREDEVICE)
		{
			supportsPureDevice = true;
		}
		else
		{
			supportsPureDevice = false;
		}
	}
	else
	{
		supportsHardwareTnL = false;
	}

	if (d3dCaps.MaxPointSize > 0.0f)
	{
		supportsPointSprites = true;
	}
	else
	{
		supportsPointSprites = false;
	}

	//pyramid->WriteLog(3, "capabilities:<br>");
	//pyramid->WriteLog(4, "hardware TnL: %i<br>", supportsHardwareTnL);
	//pyramid->WriteLog(4, "pure device: %i<br>", supportsPureDevice);
	//pyramid->WriteLog(4, "point sprites: %i (%f)<br>", supportsPointSprites, d3dCaps.MaxPointSize);
	
	return D3D_OK;
}

// search and returns the best video mode looking to the desired parameters
int Adapter::GetBestDisplayMode(PYRAMID_DISPLAYMODE &pDisplayMode, int iWidth, int iHeight, int iVideoBPP)
{
	int modeNumber  = -1;
	DWORD refreshRate =  0;

	for (DWORD i = 0; i < displayModeList.size(); i++)
	{

		if ((displayModeList[i].d3dDisplayMode.Width == iWidth) &&
			(displayModeList[i].d3dDisplayMode.Height == iHeight) &&
			(displayModeList[i].videoBPP == iVideoBPP) &&
			(displayModeList[i].d3dDisplayMode.RefreshRate >= refreshRate))
		{
			modeNumber  = i;
			refreshRate = displayModeList[i].d3dDisplayMode.RefreshRate;
		}
	}

	if (modeNumber == -1)
	{
		if (iVideoBPP == 32)
		{
			return GetBestDisplayMode(pDisplayMode, iWidth, iHeight, 16);
		}
		return E_FAIL;
	}
	else
	{
		pDisplayMode = displayModeList[modeNumber];

		return D3D_OK;
	}

}

// converts a Direct3D pixel format to 16 or 32 bit format
int Adapter::GetBPPFromD3DFormat(D3DFORMAT pD3DFormat)
{
	switch (pD3DFormat) 
	{
	case D3DFMT_A4R4G4B4:
		return 16;
	case D3DFMT_X4R4G4B4:
		return 16;
	case D3DFMT_X1R5G5B5:
		return 16;
	case D3DFMT_A1R5G5B5:
		return 16;
	case D3DFMT_R5G6B5:
		return 16;
	case D3DFMT_A8R3G3B2:
		return 16;
	case D3DFMT_X8R8G8B8:
		return 32;
	case D3DFMT_A8R8G8B8:
		return 32;
	case D3DFMT_R8G8B8:
		return 32;
	default:
		return -1;
	}
}

// searches for the best surface formats for the given display mode
int Adapter::FindFormats(IDirect3D9 *pD3DInterface, PYRAMID_DISPLAYMODE &pDisplayMode)
{
	pDisplayMode.d3dTextureFormat16  = D3DFMT_UNKNOWN;
	pDisplayMode.d3dTextureFormat32  = D3DFMT_UNKNOWN;
	pDisplayMode.d3dBackBufferFormat = D3DFMT_UNKNOWN;
	pDisplayMode.d3dZBufferFormat    = D3DFMT_UNKNOWN;

	// 16 bit texture format (from good to bad, so we have the best one available)
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												0,
							                    D3DRTYPE_TEXTURE, 
												D3DFMT_R5G6B5)))
	{
		pDisplayMode.d3dTextureFormat16 = D3DFMT_R5G6B5;
	}
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												0,
							                    D3DRTYPE_TEXTURE, 
												D3DFMT_A8R3G3B2)))
	{
		pDisplayMode.d3dTextureFormat16 = D3DFMT_A8R3G3B2;
	}
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												0,
							                    D3DRTYPE_TEXTURE, 
												D3DFMT_A4R4G4B4)))
	{
		pDisplayMode.d3dTextureFormat16 = D3DFMT_A4R4G4B4;
	}
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												0,
							                    D3DRTYPE_TEXTURE, 
												D3DFMT_A1R5G5B5)))
	{
		pDisplayMode.d3dTextureFormat16 = D3DFMT_A1R5G5B5;
	}

	// 32 bit texture format (from good to bad, so we have the best one available)
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												0,
							                    D3DRTYPE_TEXTURE, 
												D3DFMT_X8R8G8B8)))
	{
		pDisplayMode.d3dTextureFormat32 = D3DFMT_X8R8G8B8;
	}
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												0,
							                    D3DRTYPE_TEXTURE, 
												D3DFMT_A8R8G8B8)))
	{
		pDisplayMode.d3dTextureFormat32 = D3DFMT_A8R8G8B8;
	}

	// backbuffer format (from good to bad, so we have the best one available)
	if (pDisplayMode.videoBPP == 16)
	{
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_R5G6B5)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_R5G6B5;
		}
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_A8R3G3B2)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_A8R3G3B2;
		}
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_A4R4G4B4)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_A4R4G4B4;
		}
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_A1R5G5B5)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_A1R5G5B5;
		}
	}
	else
	{
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_R8G8B8)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_R8G8B8;
		}
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													pDisplayMode.d3dDisplayMode.Format)))
		{
			pDisplayMode.d3dBackBufferFormat = pDisplayMode.d3dDisplayMode.Format;
		}
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_X8R8G8B8)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_X8R8G8B8;
		}
		if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
			                                        d3dDeviceType, 
													pDisplayMode.d3dDisplayMode.Format, 
													D3DUSAGE_RENDERTARGET,
								                    D3DRTYPE_SURFACE, 
													D3DFMT_A8R8G8B8)))
		{
			pDisplayMode.d3dBackBufferFormat = D3DFMT_A8R8G8B8;
		}
	}

	// zbuffer format (from good to bad, so we have the best one available)
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												D3DUSAGE_DEPTHSTENCIL,
							                    D3DRTYPE_SURFACE, 
												D3DFMT_D16)))
	{
		pDisplayMode.d3dZBufferFormat = D3DFMT_D16;
	}
	if (!FAILED(pD3DInterface->CheckDeviceFormat(d3dAdapter, 
	                                            d3dDeviceType, 
												pDisplayMode.d3dDisplayMode.Format, 
												D3DUSAGE_DEPTHSTENCIL,
							                    D3DRTYPE_SURFACE, 
												D3DFMT_D24S8)))
	{
		pDisplayMode.d3dZBufferFormat = D3DFMT_D24S8;
	}

	if ((pDisplayMode.d3dZBufferFormat != D3DFMT_UNKNOWN) && (pDisplayMode.d3dBackBufferFormat != D3DFMT_UNKNOWN) &&
		((pDisplayMode.d3dTextureFormat16 != D3DFMT_UNKNOWN) || (pDisplayMode.d3dTextureFormat32 != D3DFMT_UNKNOWN)))
	{
		return D3D_OK;
	}
	else
	{
		return E_FAIL;
	}

	return D3D_OK;
}