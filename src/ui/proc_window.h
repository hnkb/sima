
#pragma once

#include "window.h"


namespace sima
{
	namespace ui
	{

		class proc_window : public window
		{
		public:
			proc_window();

			virtual ~proc_window();

			virtual LRESULT proc(const UINT message, const WPARAM wParam, const LPARAM lParam) override;

		protected:
			HWND code_editor;
			HFONT font_fixed;
		};

	}
}
