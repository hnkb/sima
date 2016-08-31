
#include "stdafx.h"
#include "ui/application.h"

#pragma comment(lib, "Comctl32.lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
	try
	{
		InitCommonControls();

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
