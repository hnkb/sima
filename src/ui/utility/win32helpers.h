
#pragma once

#include <string>
#include <Windows.h>


namespace sima
{
	namespace ui
	{
		namespace utility
		{

			inline std::wstring get_win32_text(const HWND handle)
			{
				std::wstring text(GetWindowTextLengthW(handle) + 1, 0);
				GetWindowTextW(handle, &text[0], (int)text.size());
				text.resize(text.size() - 1);
				return text;
			}

		}
	}
}
