
#include "proc_window.h"
#include "application.h"
#include "utility.h"

using sima::ui::proc_window;


proc_window::proc_window(sima::ui::application& owner) : window(L"sima", L"sima processor", 200, 200, 400, 500, owner), code_editor(nullptr)
{
	auto hinst = HINSTANCE(GetWindowLongPtrW(handle, GWLP_HINSTANCE));

	// Create fixed-width font
	{
		LOGFONTW lf = {};
		lf.lfHeight = -MulDiv(10, GetDeviceCaps(GetDC(handle), LOGPIXELSY), 72);
		lf.lfWeight = 400;
		lf.lfCharSet = DEFAULT_CHARSET;
		lf.lfQuality = CLEARTYPE_NATURAL_QUALITY;
		StringCchCopyW(lf.lfFaceName, 32, L"Consolas");
		font_fixed = CreateFontIndirectW(&lf);
	}

	// Create code editor control
	{
		code_editor = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL, 0, 0, 0, 0, handle, nullptr, hinst, nullptr);
		if (!code_editor) throw windows_error("Creation of processor window");

		SendMessageW(code_editor, WM_SETFONT, WPARAM(font_fixed), FALSE);
		SetWindowTextW(code_editor, L"COPY [0], 42\r\nADD [1], 13\r\nSUB [2], 2\r\nCOPY [3], [1]\r\nMUL [3], [2]\r\n\r\ncopy [10], 5\r\nadd [11], 1\r\nsub [10], 1\r\njnz [10], 7\r\n");
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

	// Create log window
	{
		log = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, 0, 0, 0, 0, handle, nullptr, hinst, nullptr);
		if (!log) throw windows_error("Creation of processor window");

		SendMessageW(log, WM_SETFONT, WPARAM(font_fixed), FALSE);
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
	constexpr int edit_left = 48;
	constexpr int edit_border = 2;
	constexpr int edit_margin = 6;
	constexpr int log_height = 150;

	auto add_margin = [](HWND hwnd, const int margin)
	{
		RECT r;
		SendMessageW(hwnd, EM_SETRECT, 0, 0);
		SendMessageW(hwnd, EM_GETRECT, 0, LPARAM(&r));
		r.left += margin; r.top += margin; r.bottom -= margin; r.right -= margin;
		SendMessageW(hwnd, EM_SETRECT, 0, LPARAM(&r));
	};

	SendMessageW(toolbar, TB_AUTOSIZE, 0, 0);

	RECT rect;
	GetWindowRect(toolbar, &rect);

	auto edit_top = rect.bottom - rect.top + edit_border;
	MoveWindow(code_editor, edit_left, edit_top, width - edit_left, height - log_height - edit_border - edit_top, TRUE);
	add_margin(code_editor, edit_margin);

	MoveWindow(log, 0, height - log_height, width, log_height, TRUE);
	add_margin(log, edit_margin);
}

void proc_window::update_log(const std::wstring& update)
{
	int index = GetWindowTextLengthW(log);
	SendMessageW(log, EM_SETSEL, WPARAM(index), LPARAM(index));
	SendMessageW(log, EM_REPLACESEL, 0, LPARAM(update.c_str()));
	SendMessageW(log, EM_REPLACESEL, 0, LPARAM(L"\r\n"));
}

void proc_window::update_log(const std::vector<std::wstring>& updates)
{
	for (const auto& u : updates) update_log(u);
}


void proc_window::program_run()
{
	std::vector<std::wstring> messages;

	try
	{
		computer::assembly::program p(utility::get_win32_text(code_editor), messages);
		app.get_computer().execute(p, messages);
	}
	catch (...) {}

	update_log(messages);
	update_log(L"");

	app.get_memwindow().redraw();
}
