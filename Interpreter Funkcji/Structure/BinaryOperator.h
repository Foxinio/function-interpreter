#pragma once

#include <numeric>

#include "Element.h"


namespace Structure {
	class BinaryOperator : public Element {
	protected:
		std::shared_ptr<Element> first;
		std::shared_ptr<Element> second;
		static std::int32_t priority;


		BinaryOperator(Element first, Element second, std::int32_t priority) :
			first(std::make_shared<Element>(first)), 
			second(std::make_shared<Element>(second)) { }

	public:
		enum Priority {
			Addition = 0,
			Multiplication = 1,
			Power = 2,
			Count = 3
		};

		static const std::vector<std::string> allBinaryOperators;
		static std::string getRegex() {
			std::string result = std::accumulate(
				std::begin(allBinaryOperators),
				std::end(allBinaryOperators),
				std::string(),
				[](std::string init, std::string elem) {
					return init + elem + "|";
				});
			return result.substr(0, result.length() - 1);
		}
		static bool isBinaryOperator(std::string string) {
			if (std::find(std::begin(allBinaryOperators), std::end(allBinaryOperators), [string](std::string elem) { return elem[0] == string[0]; })
				== std::end(allBinaryOperators)) {
				return false;
			}
			return true;
		}

		static std::int32_t getPriority() {
			return priority;
		}

		static std::int32_t priorityFromString(std::string input);

		static BinaryOperator getBinaryOperator(std::string binaryOperator, Element first, Element second);
	};

}