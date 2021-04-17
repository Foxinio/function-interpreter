#pragma once

#include <numeric>
#include <regex>

#include "../Element.h"


namespace Structure {
	class BinaryOperator : public Element {
	protected:
		std::shared_ptr<Element> first;
		std::shared_ptr<Element> second;
		static std::int32_t priority;


		BinaryOperator(Element first, Element second) :
			first(std::make_shared<Element>(first)), 
			second(std::make_shared<Element>(second)) { }

	public:
		enum Priority {
			Addition = 0,
			Multiplication = 1,
			Exponential = 2,
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
			using std::string_literals::operator""s;
			return std::regex_match(string, std::regex("^("s + getRegex() + ")$"));
			//if (std::find(std::begin(allBinaryOperators), std::end(allBinaryOperators), [string](std::string elem) { return elem[0] == string[0]; })
			//	== std::end(allBinaryOperators)) {
			//	return false;
			//}
			//return true;
		}

		virtual double evaluate(VariablePackage package);
		virtual std::string to_string();

		static std::int32_t priorityFromString(std::string input);

		static BinaryOperator& getBinaryOperator(std::string binaryOperator, Element first, Element second);
	};

}