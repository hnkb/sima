
#include "stdafx.h"
#include "proc_window.h"
#include "utility.h"

using sima::ui::proc_window;


proc_window::proc_window() : window(L"sima", L"sima processor", 200, 200, 400, 500), code_editor(nullptr)
{
	code_editor = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 100, 30, 300, 350, handle, nullptr, (HINSTANCE)GetWindowLongPtrW(handle, GWLP_HINSTANCE), nullptr);
	if (!code_editor) throw windows_error("Creation of processor window");
	
	LOGFONTW lf = {};
	lf.lfHeight = -MulDiv(10, GetDeviceCaps(GetDC(handle), LOGPIXELSY), 72);
	lf.lfWeight = 400;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfQuality = CLEARTYPE_NATURAL_QUALITY;
	StringCchCopyW(lf.lfFaceName, 32, L"Consolas");
	if (font_fixed = CreateFontIndirectW(&lf))
		SendMessageW(code_editor, WM_SETFONT, WPARAM(font_fixed), FALSE);
	
	SetWindowTextW(code_editor, L"COPY [0], 42\r\nCOPY [1], 12\r\n");
}

proc_window::~proc_window()
{
	if (font_fixed) DeleteObject(font_fixed);
}


LRESULT proc_window::proc(const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		MoveWindow(code_editor, 100, 30, LOWORD(lParam) - 100, HIWORD(lParam) - 150, TRUE);
		return 0;
	}

	return window::proc(message, wParam, lParam);
}
