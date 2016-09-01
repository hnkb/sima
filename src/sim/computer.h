
#pragma once

#include "assembly/program.h"
#include <string>
#include <vector>


namespace sima
{
	namespace computer
	{

		class computer
		{
		public:
			computer() : memory(100) {}

			void execute(assembly::program& prog, std::vector<std::wstring>& log);

			size_t instruction_pointer;
			std::vector<int> memory;

		};

	}
}
