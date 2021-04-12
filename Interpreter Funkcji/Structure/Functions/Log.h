#pragma once

#include <algorithm>

#include "Function.h"
namespace Structure {
	class Log :
		public Function {
	public:
		Log(std::vector<Element> arguments) :
			Function(arguments) { }

		double evaluate(VariablePackage package) override {
			//return std::sin(arg->evaluate(package));
			return log(arguments[0]->evaluate(package)) / log(arguments[1]->evaluate(package));
		}

		std::string to_string() {
			using std::string_literals::operator""s;
			std::string result = "log(";
			std::for_each(std::begin(arguments), std::end(arguments), [&result](std::shared_ptr<Element> elem) {
				result += elem->to_string() + ",";
			});
			result[result.length() - 1] = ')';
			return result;
		}
	};
}
