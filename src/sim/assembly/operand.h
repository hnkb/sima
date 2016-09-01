
#pragma once

#include <string>
#include <vector>


namespace sima
{
	namespace computer
	{
		class computer;

		namespace assembly
		{

			class operand
			{
			public:
				operand(const std::wstring& code);

				void set(const int value, computer& target);
				int get(computer& target) const;
				void chack_address_validity(computer& target) const;

			private:
				enum class operand_type
				{
					memory, immediate
				} type;

				int val;
				std::wstring source;
			};

		}
	}
}
