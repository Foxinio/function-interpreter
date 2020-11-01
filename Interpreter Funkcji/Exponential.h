#pragma once
#include "Element.h"
#include <cmath>
namespace Structure {
	class Exponential :
		public Element
	{
	public:
		Element base;
		Element power;

		Exponential(Element base, Element power) {
			this->base = base;
			this->power = power;
		}

		double operator()(double x) {
			return std::pow(base(x), power(x));
		}

		std::string to_string() {
			return "(" + base.to_string() + "^" + power.to_string() + ")";
		}
	};
}