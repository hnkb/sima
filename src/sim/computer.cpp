
#include "stdafx.h"
#include "computer.h"

using sima::computer::computer;


void computer::execute_program(const std::wstring program)
{
	std::wistringstream p(program);
	std::wstring s;
	while (std::getline(p, s))
	{
		execute_instruction(s);
	}
}

void computer::execute_instruction(const std::wstring statement)
{
	std::wregex re(L"\\s*(\\S+)\\s+([^\\s,]+),\\s*([^\\s]+)\\s*");
	std::wsmatch m;

	if (std::regex_match(statement, m, re))
	{
		if (m.size() != 4) throw std::runtime_error("Regex result unexpected!");
		execute_instruction(m[1], m[2], m[3]);
	}
}

void computer::execute_instruction(std::wstring instruction, std::wstring op1, std::wstring op2)
{
	std::transform(instruction.begin(), instruction.end(), instruction.begin(), tolower);
	
	std::wregex rmem(L"\\[(\\d+)\\]");
	std::wregex rimm(L"(\\d+)");
	std::wsmatch m;

	if (!std::regex_match(op1, m, rmem) || m.size() != 2) throw std::runtime_error("dest must be memory");
	int dest = std::stoi(m[1]);

	int src = 0;
	if (std::regex_match(op2, m, rmem) && m.size() == 2)
		src = memory[std::stoi(m[1])];
	else if (std::regex_match(op2, m, rimm) && m.size() == 2)
		src = std::stoi(m[1]);
	else throw std::runtime_error("src must be memory or immediate");

	if (instruction == L"copy")
		memory[dest] = src;
	else if (instruction == L"add")
		memory[dest] += src;
	else if (instruction == L"sub")
		memory[dest] -= src;
	else if (instruction == L"mul")
		memory[dest] *= src;
	else
		throw std::runtime_error("Instruction not recognized");
}
