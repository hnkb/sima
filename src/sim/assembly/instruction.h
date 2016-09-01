
#pragma once

#include "operand.h"
#include <string>


namespace sima
{
	namespace computer
	{
		class computer;

		namespace assembly
		{

			class instruction
			{
			public:
				instruction(const std::wstring& code);

				void execute(computer& target);

			private:
				std::wstring mnemonic;
				operand op1;
				operand op2;
			};

		}
	}
}
