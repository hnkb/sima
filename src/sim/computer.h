
#pragma once

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

			void execute_program(const std::wstring program, std::vector<std::wstring>& log);
			void execute_instruction(const std::wstring statement);
			void execute_instruction(std::wstring instruction, std::wstring op1, std::wstring op2);

			std::vector<int> memory;

		};

	}
}
