#pragma once
#include "BinaryOperator.h"
namespace Structure {
	class Division :
		public BinaryOperator
	{
	public:
		constexpr static std::int32_t priority = BinaryOperator::Multiplication;

		Division(Element first, Element second) :
			BinaryOperator(first, second) {	}

		double evaluate(VariablePackage package) override {
			return first->evaluate(package) / second->evaluate(package);
		}

		std::string to_string() override {
			return "(" + first->to_string() + "/" + second->to_string() + ")";
		}
	};

}