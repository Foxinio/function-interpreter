#pragma once
#include <memory>
#include "Function.h"
namespace Structure {
	struct Variable{
		char symbol;
		double value;

		Variable(char symbol, double value) {
			this->symbol = symbol;
			this->value = value;
		}
	};

	class Parameter :
		public Function
	{
	public:
		std::shared_ptr<Variable> variable_ptr;

		Parameter(std::shared_ptr<Variable> variable_ptr) {
			this->variable_ptr = variable_ptr;
		}

		std::string to_string() {
			return std::to_string(variable_ptr->symbol);
		}
	};
}
