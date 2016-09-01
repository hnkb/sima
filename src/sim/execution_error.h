
#pragma once

#include <stdexcept>
#include <string>


namespace sima
{
	namespace computer
	{

		class execution_error : public std::exception
		{
		public:
			execution_error(std::wstring msg) : message(msg) {}
			std::wstring message;
		};

	}
}
