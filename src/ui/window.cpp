
#include "stdafx.h"
#include "window.h"
#include "utility.h"

using sima::ui::window;


window::window(const std::wstring className, const std::wstring title) : handle(nullptr)
{
	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.hInstance = GetModuleHandleW(nullptr);
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.lpszClassName = className.c_str();
	wcex.lpfnWndProc = proc;
	RegisterClassExW(&wcex);

	handle = CreateWindowExW(0, wcex.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, wcex.hInstance, nullptr);
	if (!handle) throw windows_error("CreateWindow");

	SetWindowLongPtrW(handle, GWLP_USERDATA, LONG_PTR(this));
	ShowWindow(handle, SW_SHOWDEFAULT);
}

window::~window()
{
	if (handle) DestroyWindow(handle);
}


LRESULT window::proc(const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_ERASEBKGND:
		// This handler is not necessary. The window class was created with hbrBackground set to nullptr,
		// so the default processing (by DefWindowProcW) is to do nothing.
		return TRUE;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handle, &ps);
		FillRect(hdc, &ps.rcPaint, HBRUSH(COLOR_WINDOW + 1));
		EndPaint(handle, &ps);
		return 0;
	}

	case WM_DESTROY:
		handle = nullptr;
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(handle, message, wParam, lParam);
}

LRESULT CALLBACK window::proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto wnd = (window*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
	return (wnd && wnd->handle == hWnd) ? wnd->proc(message, wParam, lParam) : DefWindowProcW(hWnd, message, wParam, lParam);
}


void window::set_title(const std::wstring title)
{
	SetWindowTextW(handle, title.c_str());
}

std::wstring window::get_title() const
{
	std::wstring text(GetWindowTextLengthW(handle) + 1, 0);
	GetWindowTextW(handle, &text[0], text.size());
	text.resize(text.size() - 1);
	return text;
}
