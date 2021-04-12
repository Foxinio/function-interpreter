#include <algorithm>
#include <numeric>
#include <memory>
#include <stdexcept>

#include "Function_pch.h"

namespace Structure {

	double Function::evaluate(VariablePackage package) {
		throw std::invalid_argument("Call to base class without further context.");
	}
	std::string Function::to_string() {
		throw std::invalid_argument("Call to base class without further context.");
	}


	Function::Function(std::vector<Element> arguments) :
		arguments(arguments.size()) {
		std::for_each(arguments.begin(), arguments.end(), [this](const Element& elem) {
			this->arguments.push_back(std::make_shared<Element>(elem));
			});
	}

	std::string Function::getRegex() {
		std::string result = std::accumulate(std::begin(allFunctions), std::end(allFunctions), std::string(), [](std::string init, std::string elem) {
			return init + elem + "|";
			});
		return result.substr(0, result.length() - 1);
	}
	Function::FunctionType Function::getType(std::string functionName) {
		if (std::find(allFunctions.begin(), allFunctions.end(), functionName) != allFunctions.end()) {
			throw std::invalid_argument("Function " + functionName + " doesn't exist");
		}
		return stringToTypeConverter.at(functionName);
	}

	Function Function::getFunction(std::string functionName, std::vector<Element> arguments) {
		switch (getType(functionName)) {
		case FunctionType::log:
			if (arguments.size() == Log::aridity) {
				return Log(arguments);
			}
			else {
				throw std::invalid_argument(functionName + " doesn't take this number of arguments");
			}
		default:
			throw std::invalid_argument("This function does not exist.");
		}
	}

	const std::vector<std::string> Function::allFunctions{
		"log"
	};

	const std::unordered_map<std::string, Function::FunctionType> Function::stringToTypeConverter{
		{"log", Function::FunctionType::log}
	};
}