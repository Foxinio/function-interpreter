#pragma once
#include <string>
namespace Structure {
	class Element
	{
	public:
		double virtual operator()(double x);
		std::string virtual to_string();
	};
}
