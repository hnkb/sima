
#include "program.h"
#include "../execution_error.h"

using sima::computer::assembly::program;


program::program(const std::wstring& code, std::vector<std::wstring>& log)
{
	std::wistringstream source(code);
	std::wstring s;

	try
	{
		while (std::getline(source, s)) statements.emplace_back(s);
	}
	catch (execution_error e)
	{
		log.push_back(std::wstring(L"Error at line #") + std::to_wstring(statements.size()) + L": " + e.message);
		if (e.source.size()) log.push_back(std::wstring(L"  in " + e.source));
		log.emplace_back(L"Assembly failed.");
		throw e;
	}

}
