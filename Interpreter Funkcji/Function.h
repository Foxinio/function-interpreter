#pragma once
#include <string>
namespace Structure {
	class Function
	{
	public:
		double virtual operator()(double x);
		std::string virtual to_string();
	};
}
