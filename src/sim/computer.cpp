
#include "stdafx.h"
#include "computer.h"
#include "execution_error.h"
#include "assembly/instruction.h"

using sima::computer::computer;


void computer::execute_program(const std::wstring program, std::vector<std::wstring>& log)
{
	std::vector<std::wstring> lines;

	std::wistringstream p(program);
	std::wstring s;
	while (std::getline(p, s)) lines.push_back(s);

	log.push_back(std::wstring(L"Executing ") + std::to_wstring(lines.size()) + L" lines of code");

	int i = 0;
	try
	{
		for (i = 0; i < lines.size(); i++)
		{
			assembly::instruction(lines[i]).execute(*this);
		}

		log.emplace_back(L"Completed successfully");
	}
	catch (execution_error e)
	{
		log.push_back(std::wstring(L"Error at line #") + std::to_wstring(i) + L": " + e.message);
		if (e.source.size()) log.push_back(std::wstring(L"  in " + e.source));
		log.emplace_back(L"Execution failed");
	}
}
