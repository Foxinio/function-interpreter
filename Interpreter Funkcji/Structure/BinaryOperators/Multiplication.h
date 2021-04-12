#pragma once
#include "BinaryOperator.h"
namespace Structure {
	class Multiplication :
		public BinaryOperator
	{
	public:

		Multiplication(Element first, Element second) :
			BinaryOperator(first, second, BinaryOperator::Multiplication) { }

		double evaluate(VariablePackage package) override {
			return first->evaluate(package) * second->evaluate(package);
		}

		std::string to_string() {
			return "(" + first->to_string() + "*" + second->to_string() + ")";
		}
	};

	std::int32_t Multiplication::priority = Multiplication::Priority::Multiplication;
}
