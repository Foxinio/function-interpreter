#pragma once
#include "Element.h"
namespace Structure {
	class Constant :
		public Element
	{
	public:
		double value;

		Constant(double value) {
			this->value = value;
		}

		double operator()(double x) {
			return value;
		}

		std::string to_string() {
			return std::to_string(value);
		}
	};

}