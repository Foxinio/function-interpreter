#pragma once
#include "BinaryOperator.h"
#include <cmath>
namespace Structure {
	class Exponential :
		public BinaryOperator
	{
	public:

		Exponential(Element first, Element second) :
			BinaryOperator(first, second, BinaryOperator::Power) {	}

		double evaluate(VariablePackage package) override {
			return std::pow(first->evaluate(package), second->evaluate(package));
		}

		std::string to_string() {
			return "(" + first->to_string() + "^" + second->to_string() + ")";
		}
	};
}