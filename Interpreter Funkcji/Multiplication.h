#pragma once
#include "Element.h"
namespace Structure {
	class Multiplication :
		public Element
	{
	public:
		Element left;
		Element right;

		Multiplication(Element left, Element right) {
			this->left = left;
			this->right = right;
		}

		double operator()(double x) {
			return left(x) * right(x);
		}

		std::string to_string() {
			return "(" + left.to_string() + "*" + right.to_string() + ")";
		}
	};
}
