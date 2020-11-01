#pragma once
#include "Element.h"
namespace Structure {
	class Linear :
		public Element
	{
	public:
		Linear() {}

		double operator()(double x) {
			return x;
		}

		std::string to_string() {
			return "x";
		}
	};
}
