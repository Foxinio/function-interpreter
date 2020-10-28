#pragma once
#include "Function.h"
namespace Structure {
	class Subtraction :
		public Function
	{
	public:
		Function left;
		Function right;

		Subtraction(Function left, Function right) {
			this->left = left;
			this->right = right;
		}

		double operator()(double x) {
			return left(x) - right(x);
		}

		std::string to_string() {
			return "(" + left.to_string() + "-" + right.to_string() + ")";
		}
	};
}
