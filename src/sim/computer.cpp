
#include "stdafx.h"
#include "computer.h"
#include "execution_error.h"

using sima::computer::computer;


void computer::execute(sima::computer::assembly::program& prog, std::vector<std::wstring>& log)
{
	log.push_back(std::wstring(L"Executing ") + std::to_wstring(prog.statements.size()) + L" statements.");

	int i = 0;
	try
	{
		for (i = 0; i < prog.statements.size(); i++)
		{
			prog.statements[i].execute(*this);
		}

		log.emplace_back(L"Completed successfully.");
	}
	catch (execution_error e)
	{
		log.push_back(std::wstring(L"Error at line #") + std::to_wstring(i) + L": " + e.message);
		if (e.source.size()) log.push_back(std::wstring(L"  in " + e.source));
		log.emplace_back(L"Execution failed.");
	}
}
