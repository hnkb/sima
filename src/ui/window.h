
#pragma once

#include <string>
#include <Windows.h>


namespace sima
{
	namespace ui
	{

		class window
		{
		public:
			window() : window(L"sima", L"sima") {}
			window(const std::wstring className, const std::wstring title);

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
		};
	}
}
