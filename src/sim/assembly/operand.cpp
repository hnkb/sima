
#include "stdafx.h"
#include "operand.h"
#include "sim/execution_error.h"
#include "sim/computer.h"

using sima::computer::assembly::operand;


operand::operand(const std::wstring& code) : source(code)
{
	std::wregex rmem(L"\\[(\\d+)\\]");
	std::wregex rimm(L"(-?\\d+)");
	std::wsmatch m;

	if (std::regex_match(code, m, rmem) && m.size() == 2)
	{
		type = operand_type::memory;
		val = std::stoi(m[1]);
	}
	else if (std::regex_match(code, m, rimm) && m.size() == 2)
	{
		type = operand_type::immediate;
		val = std::stoi(m[1]);
	}
	else
	{
		throw execution_error(L"syntaxt error", code);
	}
}

int& operand::ref(sima::computer::computer& target)
{
	if (type != operand_type::memory)
		throw execution_error(L"destination must be a memory location", source);

	chack_address_validity(target);

	return target.memory[val];
}

int operand::value(sima::computer::computer& target) const
{
	chack_address_validity(target);
	return type == operand_type::memory ? target.memory[val] : val;
}

void operand::chack_address_validity(sima::computer::computer& target) const
{
	if (type == operand_type::memory && val >= target.memory.size())
		throw execution_error(std::wstring(L"memory location ") + std::to_wstring(val) + L" is invalid", source);
}
