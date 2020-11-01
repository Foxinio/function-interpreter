#pragma once
#include "Element.h"
namespace Structure {
	class Addition :
		public Element
	{
	public:
		Element left;
		Element right;

		Addition(Element left, Element right) {
			this->left = left;
			this->right = right;
		}

		double operator()(double x) {
			return left(x) + right(x);
		}

		std::string to_string() {
			return "(" + left.to_string() + "+" + right.to_string() + ")";
		}

	};
}