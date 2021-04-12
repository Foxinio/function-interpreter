#pragma once
#include "BinaryOperator.h"
namespace Structure {
	class Division :
		public BinaryOperator
	{
	public:

		Division(Element first, Element second) :
			BinaryOperator(first, second, BinaryOperator::Multiplication) {	}

		double evaluate(VariablePackage package) override {
			return first->evaluate(package) / second->evaluate(package);
		}

		std::string to_string() override {
			return "(" + first->to_string() + "/" + second->to_string() + ")";
		}
	};

}