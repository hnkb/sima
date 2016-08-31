
#pragma once

#include <string>
#include <Windows.h>


namespace sima
{
	namespace ui
	{
		class application;

		class window
		{
		public:
			window(application& owner) : window(L"sima", L"sima", CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, owner) {}
			window(const std::wstring className, const std::wstring title, const int x, const int y, const int width, const int height, application& owner);

			window(const window& other) = delete;
			window(window&& other) = delete;
			window& operator=(const window& other) = delete;
			window& operator=(window&& other) = delete;

			virtual ~window();

			void set_title(const std::wstring title);
			std::wstring get_title() const;

		protected:
			virtual LRESULT proc(const UINT message, const WPARAM wParam, const LPARAM lParam);
			static LRESULT CALLBACK proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			HWND handle;
			application& app;
		};
	}
}
