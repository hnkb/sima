
#include "application.h"

using sima::ui::application;


int application::run()
{
	MSG msg;

	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return (int)msg.wParam;
}
