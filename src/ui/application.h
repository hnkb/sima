
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
			application() : memory(*this), proc(*this) {}

			application(const application& other) = delete;
			application(application&& other) = delete;
			application& operator=(const application& other) = delete;
			application& operator=(application&& other) = delete;

			virtual ~application() {}

			int run();

			sim::computer& get_computer() { return computer; }
			memory_window& get_memwindow() { return memory; }

		private:
			utility::com_initialize com_init;
			sim::computer computer;
			memory_window memory;
			proc_window proc;
		};

	}
}
