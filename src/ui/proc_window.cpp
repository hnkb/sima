
#include "stdafx.h"
#include "proc_window.h"
#include "application.h"
#include "utility.h"

using sima::ui::proc_window;


proc_window::proc_window(sima::ui::application& owner) : window(L"sima", L"sima processor", 200, 200, 400, 500, owner), code_editor(nullptr)
{
	auto hinst = HINSTANCE(GetWindowLongPtrW(handle, GWLP_HINSTANCE));

	// Create code editor control
	{
		code_editor = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, 0, 0, handle, nullptr, hinst, nullptr);
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
		SetFocus(code_editor);
	}
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
