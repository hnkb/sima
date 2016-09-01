
#pragma once

#include "window.h"
#include <vector>


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
			void update_log(const std::wstring& update);
			void update_log(const std::vector<std::wstring>& updates);

			void program_run();

			HWND code_editor;
			HWND toolbar;
			HWND log;
			HFONT font_fixed;
		};

	}
}
