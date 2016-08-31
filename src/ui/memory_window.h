
#pragma once

#include "window.h"


namespace sima
{
	namespace ui
	{

		class memory_window : public window
		{
		public:
			memory_window(application& owner);

			~memory_window();

			virtual LRESULT proc(const UINT message, const WPARAM wParam, const LPARAM lParam) override;

		protected:
			void draw_memview(HDC hdc, RECT& rect);
			void draw_dataview(HDC hdc, RECT& rect);

			HFONT font_fixed;
		};

	}
}
