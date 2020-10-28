#pragma once
#include "Function.h"
#include <cmath>
namespace Structure {
	class Exponential :
		public Function
	{
	public:
		Function base;
		Function power;

		Exponential(Function base, Function power) {
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