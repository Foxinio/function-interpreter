#pragma once
#include "Function.h"
namespace Structure {
	class Division :
		public Function
	{
	public:
		Function left;
		Function right;

		Division(Function left, Function right) {
			this->left = left;
			this->right = right;
		}

		double operator()(double x) {
			return left(x) / right(x);
		}

		std::string to_string() {
			return "(" + left.to_string() + "/" + right.to_string() + ")";
		}
	};

}