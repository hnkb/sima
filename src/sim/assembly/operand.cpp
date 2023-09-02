
#include "operand.h"
#include "../execution_error.h"
#include "../computer.h"

using sima::computer::assembly::operand;


operand::operand(const std::wstring& code) : source(code)
{
	std::wregex rptr(L"\\[\\[(\\d+)\\]\\]");
	std::wregex rmem(L"\\[(\\d+)\\]");
	std::wregex rimm(L"(-?\\d+)");
	std::wsmatch m;

	if (std::regex_match(code, m, rptr) && m.size() == 2)
	{
		type = operand_type::pointer_memory;
		val = std::stoi(m[1]);
	}
	else if (std::regex_match(code, m, rmem) && m.size() == 2)
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
	chack_address_validity(target);
	
	if (type == operand_type::memory)
		return target.memory[val];
	
	if (type == operand_type::pointer_memory)
		return target.memory[target.memory[val]];

	throw execution_error(L"destination must be a memory location", source);
}

int operand::value(sima::computer::computer& target) const
{
	chack_address_validity(target);

	if (type == operand_type::memory)
		return target.memory[val];

	if (type == operand_type::pointer_memory)
		return target.memory[target.memory[val]];

	return  val;
}

void operand::chack_address_validity(sima::computer::computer& target) const
{
	if ((type == operand_type::memory || type == operand_type::pointer_memory) && val >= target.memory.size())
		throw execution_error(std::wstring(L"memory location ") + std::to_wstring(val) + L" is invalid", source);

	if (type == operand_type::pointer_memory && target.memory[val] >= target.memory.size())
		throw execution_error(std::wstring(L"memory location ") + std::to_wstring(target.memory[val]) + L" is invalid", source);
}
