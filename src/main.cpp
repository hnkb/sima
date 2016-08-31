
#include "stdafx.h"
#include "ui/application.h"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
	try
	{
		sima::ui::application app;
		return app.run();
	}
	catch (std::exception e)
	{
		// Remove WM_QUIT messages from queue, if any, so MessageBox works correctly
		MSG msg;
		while (PeekMessageW(&msg, HWND(-1), WM_QUIT, WM_QUIT, PM_REMOVE));
		
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR);
		return -1;
	}
}
