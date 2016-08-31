
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
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR);
		return -1;
	}
}
