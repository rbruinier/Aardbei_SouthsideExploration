#include "Main.h" 

BYTE keyInput[256];

WNDCLASSEX windowClass;

static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
    case WM_KEYDOWN:
		keyInput[wParam] = true;
        switch(wParam) 
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
            break;
        }
        break;
    case WM_KEYUP:
		keyInput[wParam] = false;
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND InitWindow(int clientWidth, int clientHeight, char* className, char* windowCaption)
{
	// register window class
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = MsgProc;
	windowClass.cbClsExtra = 0L;
	windowClass.cbWndExtra = 0L;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hIcon = LoadIcon (NULL, MAKEINTRESOURCE (IDI_APPLICATION));
	windowClass.hCursor = LoadCursor (NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = NULL;

	RegisterClassEx(&windowClass);

	// create the window
	//long winParam = WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	//HWND hWnd = CreateWindowEx (0, windowClass.lpszClassName, windowCaption, winParam, 
	//	CW_USEDEFAULT, CW_USEDEFAULT, clientWidth + 6, clientHeight + 25, GetDesktopWindow(), 
	//	NULL, windowClass.hInstance, NULL);
	
	long winParam = WS_POPUP;

	HWND hWnd = CreateWindowEx (0, windowClass.lpszClassName, windowCaption, winParam, 
		CW_USEDEFAULT, CW_USEDEFAULT, clientWidth, clientHeight , GetDesktopWindow(), 
		NULL, windowClass.hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);

	UpdateWindow(hWnd);

	return hWnd;
}

void DeinitWindow()
{
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}