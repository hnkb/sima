
#include "stdafx.h"
#include "memory_window.h"

using sima::ui::memory_window;


memory_window::memory_window() : window(L"sima", L"sima memory", 610, 200, 800, 500)
{

}

memory_window::~memory_window()
{

}


LRESULT memory_window::proc(const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle, &ps);
		FillRect(hdc, &ps.rcPaint, HBRUSH(COLOR_WINDOW + 1));
		TextOutW(hdc, 100, 100, L"MEMORY VIEW", 11);
		TextOutW(hdc, 400, 100, L"DATA VIEW", 11);
		EndPaint(handle, &ps);
		return 0;
	}
	}

	return window::proc(message, wParam, lParam);
}
