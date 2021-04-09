#pragma once
#include "BinaryOperator.h"
namespace Structure {
	class Subtraction :
		public BinaryOperator
	{
	public:

		Subtraction(Element first, Element second) :
			BinaryOperator(first, second, BinaryOperator::Addition) { }

		double evaluate(VariablePackage package) override {
			return first->evaluate(package) - second->evaluate(package);
		}

		std::string to_string() {
			return "(" + first->to_string() + "-" + second->to_string() + ")";
		}
	};
}