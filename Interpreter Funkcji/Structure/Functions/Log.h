#pragma once


#include "Function.h"

namespace Structure {

	class Log :
		public Function {
	public:
		Log(std::vector<Element> arguments) :
			Function(arguments) { }

		double evaluate(VariablePackage package) override;
		std::string to_string();
	};
}
