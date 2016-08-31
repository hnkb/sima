
#pragma once

#include "proc_window.h"
#include "memory_window.h"
#include "utility.h"


namespace sima
{
	namespace ui
	{

		class application
		{
		public:
			application() {}

			application(const application& other) = delete;
			application(application&& other) = delete;
			application& operator=(const application& other) = delete;
			application& operator=(application&& other) = delete;

			virtual ~application() {}

			int run();

		private:
			utility::com_initialize com_init;
			proc_window proc;
			memory_window memory;
		};

	}
}
