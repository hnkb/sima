
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

	// Create toolbar
	{
		toolbar = CreateWindowExW(0, TOOLBARCLASSNAMEW, nullptr, WS_CHILD | TBSTYLE_LIST | TBSTYLE_WRAPABLE, 0, 0, 0, 0, handle, nullptr, hinst, nullptr);
		if (!toolbar) throw windows_error("Creation of processor window");

		TBBUTTON buttons[] =
		{
			{ MAKELONG(STD_FILENEW, 0), 1, TBSTATE_ENABLED, BTNS_AUTOSIZE, {}, 0, INT_PTR(L"Run") }
		};

		auto il = ImageList_Create(16, 16, ILC_COLOR32 | ILC_MASK, sizeof(buttons) / sizeof(TBBUTTON), 0);
		SendMessageW(toolbar, TB_SETIMAGELIST, 0, LPARAM(il));
		SendMessageW(toolbar, TB_LOADIMAGES, IDB_STD_SMALL_COLOR, LPARAM(HINST_COMMCTRL));

		SendMessageW(toolbar, TB_BUTTONSTRUCTSIZE, WPARAM(sizeof(TBBUTTON)), 0);
		SendMessageW(toolbar, TB_ADDBUTTONS, WPARAM(sizeof(buttons) / sizeof(TBBUTTON)), LPARAM(&buttons));

		SendMessageW(toolbar, TB_AUTOSIZE, 0, 0);
		ShowWindow(toolbar, SW_SHOW);
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
	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->hwndFrom == toolbar && ((LPNMHDR)lParam)->code == NM_CLICK)
		{
			switch (((LPNMMOUSE)lParam)->dwItemSpec)
			{
			case 1:
				program_run();
				return 0;
			}
		}
		break;

	case WM_SIZE:
		resize_children(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}

	return window::proc(message, wParam, lParam);
}

void proc_window::resize_children(const WORD width, const WORD height)
{
	SendMessageW(toolbar, TB_AUTOSIZE, 0, 0);
	
	RECT rect;
	GetWindowRect(toolbar, &rect);
	MoveWindow(code_editor, 48, rect.bottom - rect.top + 4, width - 48, height - 150, TRUE);
}


void proc_window::program_run()
{

}
