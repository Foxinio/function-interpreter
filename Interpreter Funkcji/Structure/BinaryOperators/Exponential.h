#pragma once
#include "BinaryOperator.h"
#include <cmath>
namespace Structure {
	class Exponential :
		public BinaryOperator
	{
	public:
		constexpr static std::int32_t priority = BinaryOperator::Exponential;

		Exponential(Element first, Element second) :
			BinaryOperator(first, second) {	}

		double evaluate(VariablePackage package) override {
			return std::pow(first->evaluate(package), second->evaluate(package));
		}

		std::string to_string() {
			return "(" + first->to_string() + "^" + second->to_string() + ")";
		}
	};
}