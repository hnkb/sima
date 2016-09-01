
#pragma once

#include <string>


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

				int& ref(computer& target);
				int value(computer& target) const;

				void chack_address_validity(computer& target) const;

			private:
				enum class operand_type
				{
					pointer_memory, memory, immediate
				} type;

				int val;
				std::wstring source;
			};

		}
	}
}
