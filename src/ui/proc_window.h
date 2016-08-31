
#pragma once

#include "window.h"


namespace sima
{
	namespace ui
	{

		class proc_window : public window
		{
		public:
			proc_window(application& owner);

			virtual ~proc_window();

			virtual LRESULT proc(const UINT message, const WPARAM wParam, const LPARAM lParam) override;

		protected:
			void resize_children(const WORD width, const WORD height);

			void program_run();

			HWND code_editor;
			HWND toolbar;
			HFONT font_fixed;
		};

	}
}
