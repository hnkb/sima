
#pragma once

#include "window.h"


namespace sima
{
	namespace ui
	{

		class memory_window : public window
		{
		public:
			memory_window();

			~memory_window();

			virtual LRESULT proc(const UINT message, const WPARAM wParam, const LPARAM lParam) override;
		};

	}
}
