
#include "stdafx.h"
#include "computer.h"
#include "execution_error.h"

using sima::computer::computer;


void computer::execute(sima::computer::assembly::program& prog, std::vector<std::wstring>& log)
{
	log.push_back(std::wstring(L"Executing ") + std::to_wstring(prog.statements.size()) + L" statements.");
	
	auto start = std::chrono::steady_clock::now();
	size_t count = 0;
	auto report_count = [&]() { log.push_back(std::to_wstring(count) + L" instructions executed."); };

	try
	{
		for (instruction_pointer = 0; instruction_pointer < prog.statements.size(); count++)
		{
			prog.statements[instruction_pointer].execute(*this);

			if (std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() > 1)
			{
				log.emplace_back(L"System hanged. Execution stopped after 1 second.");
				report_count();
				return;
			}
		}

		report_count();
		log.emplace_back(L"Completed successfully.");
	}
	catch (execution_error e)
	{
		log.push_back(std::wstring(L"Error at line #") + std::to_wstring(instruction_pointer) + L": " + e.message);
		if (e.source.size()) log.push_back(std::wstring(L"  in " + e.source));
		report_count();
		log.emplace_back(L"Execution failed.");
	}
}
