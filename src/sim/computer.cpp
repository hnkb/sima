
#include "stdafx.h"
#include "computer.h"
#include "execution_error.h"
#include "assembly/operand.h"

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
			execute_instruction(lines[i]);
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

void computer::execute_instruction(const std::wstring statement)
{
	std::wregex re(L"\\s*(\\S+)\\s+([^\\s,]+),\\s*([^\\s]+)\\s*");
	std::wsmatch m;
	if (!std::regex_match(statement, m, re) || m.size() != 4) throw execution_error(L"syntax error", statement);

	execute_instruction(m[1], m[2], m[3]);
}

void computer::execute_instruction(std::wstring instruction, std::wstring op1, std::wstring op2)
{
	std::transform(instruction.begin(), instruction.end(), instruction.begin(), tolower);
	
	std::wregex rmem(L"\\[(\\d+)\\]");
	std::wregex rimm(L"(\\d+)");
	std::wsmatch m;

	auto n1 = assembly::operand(op1),
		n2 = assembly::operand(op2);

	if (instruction == L"copy")
		n1.set(n2.get(*this), *this);
	else if (instruction == L"add")
		n1.set(n1.get(*this) + n2.get(*this), *this);
	else if (instruction == L"sub")
		n1.set(n1.get(*this) - n2.get(*this), *this);
	else if (instruction == L"mul")
		n1.set(n1.get(*this) * n2.get(*this), *this);
	else
		throw execution_error(L"Instruction not recognized");
}
