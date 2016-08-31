
#pragma once

#include "sim/computer.h"
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
			application() : proc(computer), memory(computer) {}

			application(const application& other) = delete;
			application(application&& other) = delete;
			application& operator=(const application& other) = delete;
			application& operator=(application&& other) = delete;

			virtual ~application() {}

			int run();

		private:
			utility::com_initialize com_init;
			sim::computer computer;
			proc_window proc;
			memory_window memory;
		};

	}
}
