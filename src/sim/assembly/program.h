
#pragma once

#include "instruction.h"
#include <vector>


namespace sima
{
	namespace computer
	{

		namespace assembly
		{

			class program
			{
			public:
				program(const std::wstring& code, std::vector<std::wstring>& log);

				std::vector<instruction> statements;
			};

		}
	}
}
