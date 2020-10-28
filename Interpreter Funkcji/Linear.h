#pragma once
#include "Function.h"
namespace Structure {
	class Linear :
		public Function
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
