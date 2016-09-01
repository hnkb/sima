
#include "stdafx.h"
#include "instruction.h"
#include "sim/execution_error.h"

using sima::computer::assembly::instruction;


instruction::instruction(const std::wstring& code) : op1(L"0"), op2(L"0")
{
	std::wregex re(L"\\s*(\\S+)\\s+([^\\s,]+),\\s*([^\\s]+)\\s*");
	std::wsmatch m;
	if (!std::regex_match(code, m, re) || m.size() != 4) throw execution_error(L"syntax error", code);

	mnemonic = m[1];
	std::transform(mnemonic.begin(), mnemonic.end(), mnemonic.begin(), tolower);

	op1 = operand(m[2]);
	op2 = operand(m[3]);
}


void instruction::execute(sima::computer::computer& target)
{
	int& a = op1.ref(target);
	int b = op2.value(target);

	if (mnemonic == L"copy")
		a = b;
	else if (mnemonic == L"add")
		a += b;
	else if (mnemonic == L"sub")
		a -= b;
	else if (mnemonic == L"mul")
		a *= b;
	else
		throw execution_error(L"invalid instruction mnemonic", mnemonic);
}
