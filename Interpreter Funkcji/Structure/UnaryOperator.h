#pragma once

#include <numeric>
#include <algorithm>

#include "Element.h"
namespace Structure {
	class UnaryOperator :
		public Element
	{
	protected:
		std::shared_ptr<Element> arg;

		UnaryOperator(Element argument) :
			arg(std::make_shared<Element>(argument)) { }
	public:
		static const std::vector<std::string> allUnaryOperators;
		static std::string getRegex() {
			std::string result = std::accumulate(
				std::begin(allUnaryOperators),
				std::end(allUnaryOperators), 
				std::string(),
				[](std::string init, std::string elem) {
					return init + elem + "|";
				});
			return result.substr(0, result.length() - 1);
		}

		static bool isUnaryOperator(std::string string) {
			if (std::find(std::begin(allUnaryOperators), std::end(allUnaryOperators), [string](std::string elem) { return elem[0] == string[0]; })
				== std::end(allUnaryOperators)) {
				return false;
			}
			return true;
		}

		static UnaryOperator getUnaryOperator(std::string unaryOperator, Element arg) {
			switch (unaryOperator[0]) {
			default:
				throw std::invalid_argument("Not implemented");
			}
		}
	};

}
