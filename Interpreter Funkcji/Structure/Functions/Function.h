#pragma once

#include <numeric>
#include <memory>
#include <stdexcept>

#include "../Element.h"
#include "Function_pch.h"

namespace Structure {

	class Function :
		public Element
	{
	public:
		enum class FunctionType {
			log
		};

	private:
		const static std::unordered_map<std::string, FunctionType> stringToTypeConverter;
		const static std::vector<std::string> allFunctions;

	public:
		const static unsigned int aridity;

		std::vector<std::shared_ptr<Element>> arguments;
		static std::string getRegex() {
				std::string result = std::accumulate(std::begin(allFunctions), std::end(allFunctions), std::string(), [](std::string init, std::string elem) {
				return init + elem + "|";
			});
				return result.substr(0, result.length() - 1);
		}
		static FunctionType getType(std::string functionName) {
			if (std::find(allFunctions.begin(), allFunctions.end(), functionName) != allFunctions.end()) {
				throw std::invalid_argument("Function " + functionName + " doesn't exist");
			}
			return stringToTypeConverter.at(functionName);
		}

		Function(std::vector<Element> arguments) :
			arguments(arguments.size()) {
			std::for_each(arguments.begin(), arguments.end(), [this](const Element& elem) {
				this->arguments.push_back(std::make_shared<Element>(elem));
			});
		}

		static Function getFunction(std::string functionName, std::vector<Element> arguments) {
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
	};
}