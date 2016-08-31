
#include "stdafx.h"
#include "memory_window.h"

using sima::ui::memory_window;


memory_window::memory_window(sima::sim::computer& comp) : window(L"sima", L"sima memory", 610, 200, 800, 500, comp)
{
	LOGFONTW lf = {};
	lf.lfHeight = -MulDiv(10, GetDeviceCaps(GetDC(handle), LOGPIXELSY), 72);
	lf.lfWeight = 400;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfQuality = CLEARTYPE_NATURAL_QUALITY;
	StringCchCopyW(lf.lfFaceName, 32, L"Consolas");
	font_fixed = CreateFontIndirectW(&lf);
}

memory_window::~memory_window()
{
	if (font_fixed) DeleteObject(font_fixed);
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
		auto font_default = SelectObject(hdc, font_fixed);

		for (int i = 0, y = 10; i < computer.memory.size() && y < ps.rcPaint.bottom; i++, y += 20)
		{
			RECT r{ 10, y, 30, y + 20 };
			SetTextColor(hdc, 0xfec16e);
			DrawTextW(hdc, std::to_wstring(i).c_str(), -1, &r, DT_RIGHT | DT_TOP);

			r.left = 40;
			r.right = 70;
			SetTextColor(hdc, 0);
			DrawTextW(hdc, std::to_wstring(computer.memory[i]).c_str(), -1, &r, DT_RIGHT | DT_TOP);
		}

		TextOutW(hdc, 400, 100, L"DATA VIEW", 11);

		SelectObject(hdc, font_default);
		EndPaint(handle, &ps);
		return 0;
	}
	}

	return window::proc(message, wParam, lParam);
}
