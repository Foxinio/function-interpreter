#pragma once

#include <numeric>
#include <algorithm>
#include <regex>

#include "../Element.h"

namespace Structure {
	class UnaryOperator :
		public Element
	{
	public:
		enum class UnaryOperatorType {
			negative,
			sinh,
			sech,
			cosh,
			csch,
			ctgh,
			tgh,
			sin,
			sec,
			cos,
			csc,
			ctg,
			tg,
			asin,
			asec,
			acos,
			acsc,
			actg,
			atg,
			ln,
			exp,
			log,
			sqrt,
			cbrt,
			sign,
			floor,
			ceil,
			round,
			fact,
			abs
		};

	protected:
		std::shared_ptr<Element> arg;

		UnaryOperator(Element argument) :
			arg(std::make_shared<Element>(argument)) { }
	public:
		const static std::unordered_map<std::string, UnaryOperatorType> stringToTypeConverter;
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
			using std::string_literals::operator""s;
			return std::regex_match(string, std::regex("^("s + getRegex() + ")$"));
			//if (std::find(std::begin(allUnaryOperators), std::end(allUnaryOperators), [string](std::string elem) { return elem[0] == string[0]; })
			//	== std::end(allUnaryOperators)) {
			//	return false;
			//}
			//return true;
		}

		static UnaryOperatorType getType(std::string unaryOperatorName) {
			if (std::find(allUnaryOperators.begin(), allUnaryOperators.end(), unaryOperatorName) != allUnaryOperators.end()) {
				throw std::invalid_argument("Unknown " + unaryOperatorName + " UnaryOperator");
			}
			return stringToTypeConverter.at(unaryOperatorName);
		}

		static UnaryOperator getUnaryOperator(std::string unaryOperator, Element arg);
	};

}
